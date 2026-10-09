# Tutorial: primeiros passos

Neste tutorial você vai compilar o squidsql, criar uma tabela, inserir dados,
consultá-los e apagá-los. Leva uns dez minutos. Você precisa do Visual Studio
com as ferramentas de C++ instaladas.

## 1. Compile

Abra um *Developer Command Prompt* na pasta `projects/squidsql` e rode:

    nmake

No fim aparece `squidsql.exe` na pasta. (Outras formas de compilar estão em
[Compilar e executar](../how-to/compilar-e-executar.md).)

## 2. Abra o REPL

    squidsql.exe

Você verá:

    squidsql 0.1 - type .help for help
    squidsql>

## 3. Crie uma tabela

Digite, terminando com `;`:

    CREATE TABLE usuarios (id INT, nome TEXT, idade INT);

O squidsql responde `table usuarios created`.

## 4. Insira linhas

    INSERT INTO usuarios VALUES (1, 'ana', 31);
    INSERT INTO usuarios VALUES (2, 'bruno', 25);
    INSERT INTO usuarios VALUES (3, 'carla', 40);

Cada comando responde `1 row inserted`.

## 5. Consulte

    SELECT * FROM usuarios;

Resultado:

     id | nome  | idade
    ----+-------+------
     1  | ana   | 31
     2  | bruno | 25
     3  | carla | 40
    (3 rows)

Agora filtre e escolha colunas:

    SELECT nome FROM usuarios WHERE idade >= 30;

## 6. Apague

    DELETE FROM usuarios WHERE id = 2;
    SELECT * FROM usuarios;

A linha do `bruno` desapareceu.

## 7. Cometa um erro de propósito

    SELECT * FROM clientes;

O squidsql imprime `error: no such table: clientes` e continua funcionando:
erros nunca encerram o programa.

## 8. Saia

    .quit

Os dados **não são salvos**: ao sair, tudo some. Para repetir uma sessão,
guarde os comandos num arquivo e rode `squidsql.exe arquivo.sql`.

## Próximos passos

- Todas as formas de comando: [SQL suportado](../reference/sql.md)
- Entender o que acontece por baixo: [Arquitetura](../explanation/arquitetura.md)
