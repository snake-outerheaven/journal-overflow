# Armazenamento em disco

Esta página explica *por que* o armazenamento é como é. Para os bytes exatos, veja
o [formato do arquivo](../reference/formato-arquivo.md).

## A ideia: o arquivo é a memória

Em vez de ler e escrever blocos com `fread`/`fwrite`, o squidsql **mapeia o
arquivo inteiro na memória**. Depois disso, o banco é só um grande vetor de bytes
e o sistema operacional cuida de trazer páginas do disco e gravá-las de volta.
As estruturas (tabelas, árvores, linhas) são lidas e alteradas como se fossem
memória comum.

## Camadas

    db.c       tabelas, linhas, SQL
      |
    rbtree.c   árvore rubro-negra (catálogo e linhas)
      |
    arena.c    alocador de blocos dentro do arquivo
      |
    hal.h      arquivo mapeado: hal_win32.c  |  hal_posix.c

A **HAL** (camada de abstração de hardware/SO) é a única que conhece o sistema
operacional. No Windows usa `CreateFileMapping`/`MapViewOfFile`; no POSIX usa
`mmap`/`ftruncate`/`msync`. O `VirtualAlloc` não serve para isso: ele devolve
memória anônima, sem arquivo por trás.

## Offsets em vez de ponteiros

Quando o arquivo precisa crescer, ele é desmapeado e mapeado de novo, e o
endereço-base **muda**. Um ponteiro gravado dentro do arquivo seria inválido
na próxima execução (ou logo após o crescimento). Por isso toda ligação entre
estruturas é um *offset* de 64 bits a partir do início do arquivo, e o código só
converte para ponteiro (`arena_ptr`) no momento de usar.

Consequência prática, e a regra mais importante do código: **nenhum ponteiro
obtido de `arena_ptr` pode ser guardado através de uma chamada que aloca**
(`arena_alloc`, `rb_insert`, e as funções que as usam). Guarde offsets e
converta de novo.

## Por que uma árvore rubro-negra

Ela dá inserção, busca e remoção em O(log n), e a travessia em ordem
(`rb_first`/`rb_next`) devolve as linhas na ordem de inserção. Os nós têm
tamanho fixo (48 bytes), o que se encaixa bem no alocador por listas livres.

A remoção *religa* os nós em vez de copiar chaves. Assim o offset de um nó que
sobrevive nunca muda, e o `DELETE` pode ler o sucessor antes de apagar o nó
atual.

### O que ela não faz bem

Uma árvore binária é uma escolha ruim para disco. Uma busca em um milhão de
linhas toca cerca de 20 nós, e cada um pode estar em uma página diferente; uma
B-tree, com centenas de chaves por página, tocaria 3 ou 4. A árvore fica atrás de
uma interface pequena (`rb_insert`, `rb_find`, `rb_delete`, `rb_first`,
`rb_next`) justamente para poder ser trocada por uma B+tree depois, sem mexer em
`db.c`.

## Alocador

Cada bloco tem um cabeçalho de 16 bytes. Blocos de até 1024 bytes ficam em uma
lista livre por tamanho (16, 32, ...); maiores, em uma lista única com
*first-fit*. Quando não há bloco livre, o alocador pega espaço novo no "topo" do
arquivo, e dobra o arquivo se faltar.

Não há junção de blocos livres vizinhos, então o arquivo pode ficar fragmentado
depois de muitas remoções de tamanhos variados.

## Durabilidade e quedas

`hal_sync` grava as páginas modificadas e espera o disco (`FlushViewOfFile` +
`FlushFileBuffers`, ou `msync` + `fsync`). Por padrão o banco faz isso depois de
cada `CREATE`, `INSERT` e `DELETE`; `.sync off` adia tudo para o fechamento.

**O formato não é à prova de queda.** O sistema operacional pode gravar as
páginas em qualquer ordem, então uma queda de energia no meio de um `INSERT`
pode deixar a árvore inconsistente. O que existe é a *detecção*: o cabeçalho
guarda `clean = 0` enquanto o banco está aberto, e quem abre um arquivo assim
recebe o aviso "was not closed cleanly". Nada é verificado nem reparado.

O caminho para resolver isso (diário de escrita antecipada, ou cópia na escrita
com troca atômica da raiz) é descrito no [roadmap](decisoes.md).

## Acesso exclusivo

O arquivo é aberto com acesso exclusivo (modo de compartilhamento 0 no Windows,
`flock` no POSIX). Um segundo processo que tente abri-lo falha. Há um único
escritor, e não existe controle de concorrência.
