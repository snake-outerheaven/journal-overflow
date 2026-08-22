# Projeto de Matemática Discreta

## Objetivos

Construir uma aplicação de linha de comando em C capaz de realizar operações
com progressões aritméticas.

### Funcionalidades matemáticas

- Calcular o enésimo termo de uma progressão aritmética (P.A.).
- Calcular a soma de `n` termos de uma P.A.
- Interpolar `k` números entre dois termos de uma P.A.
- Gerar uma progressão aritmética de ordem `n` a partir de `n + 1` termos
	iniciais.

### Interface e organização

- Disponibilizar um menu para o usuário escolher a operação desejada.
- Implementar cada operação em uma função específica sempre que necessário.
- Separar a lógica matemática da entrada e saída do programa.
- Compilar e executar o projeto por meio de um `Makefile`.

## Entregáveis implementados

- [x] Função `pa_termo` para calcular o enésimo termo de uma P.A.
- [x] Função `pa_soma` para calcular a soma de `n` termos de uma P.A.
- [x] Função `pa_gerar_ordem` para gerar uma P.A. de ordem `n`.
- [x] Header `pa.h` com a interface das funções de P.A.
- [x] Testes das funções usando a biblioteca `assert`.
- [x] Geração da biblioteca compartilhada `libpa.so`.

## Pendências

- [x] Implementar o menu interativo da aplicação.
- [x] Implementar a interpolação de `k` números em uma P.A.
- [x] Implementar a geração de uma P.A. de ordem `n` a partir dos termos iniciais.
- [ ] Criar um pacote de números aleatórios para gerar casos de teste e verificar a eficácia das funções matemáticas.

### Entrega

- Validar as funcionalidades antes da entrega.
- Enviar o trabalho concluído pelo AVA.

### Compilação

No Linux ou com GNU Make no Windows:

```sh
make test
make run
```

No prompt de ferramentas do Visual Studio, usando `nmake`:

```bat
nmake /f Makefile.win test
nmake /f Makefile.win run
```

O `Makefile` identifica Windows pela variável `OS=Windows_NT` e ajusta as
bibliotecas, extensões dos executáveis e comandos de execução. O
`Makefile.win` é específico do `nmake` e usa `cl.exe`.
