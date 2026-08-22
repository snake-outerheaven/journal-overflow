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
- Compilar, testar e executar o projeto por meio do CMake.

## Entregáveis implementados

- [x] Função `pa_termo` para calcular o enésimo termo de uma P.A.
- [x] Função `pa_soma` para calcular a soma de `n` termos de uma P.A.
- [x] Função `pa_gerar_ordem` para gerar uma P.A. de ordem `n`.
- [x] Header `pa.h` com a interface das funções de P.A.
- [x] Testes das funções usando a biblioteca `assert`.
- [x] Geração da biblioteca compartilhada da P.A.

## Pendências

- [x] Implementar o menu interativo da aplicação.
- [x] Implementar a interpolação de `k` números em uma P.A.
- [x] Implementar a geração de uma P.A. de ordem `n` a partir dos termos iniciais.
- [ ] Criar um pacote de números aleatórios para gerar casos de teste e verificar a eficácia das funções matemáticas.

### Entrega

- Validar as funcionalidades antes da entrega.
- Enviar o trabalho concluído pelo AVA.

### Compilação

Configure o projeto a partir da pasta `T1-Discrete-Math`:

```sh
cmake -S . -B build -DBUILD_TESTING=ON
```

Compile o projeto:

```sh
cmake --build build
```

Execute os testes:

```sh
ctest --test-dir build --output-on-failure
```

Execute a aplicação compilada:

```sh
./build/pa
```

No Windows, o executável pode ser encontrado em `build/Debug/pa.exe` quando
o gerador do CMake utiliza configurações Debug/Release.
