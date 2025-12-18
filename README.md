# Journal Overflow

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)  
[![Linguagem: C](https://img.shields.io/badge/C-100%25-blue?logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))

**Repositório de estudos.**

Este repositório está organizado em torno do aprendizado da linguagem de programação C, baseado no clássico "The C Programming Language" de Brian Kernighan e Dennis Ritchie (K&R).

## Conteúdo

### Capítulos

Cada capítulo do livro K&R é explorado com exercícios e exemplos práticos:

* **[ch0X](https://github.com/snake-outerheaven/journal-overflow/tree/main/ch01)**: Exercícios e código do Capítulo X do K&R.

### Projetos

Projetos adicionais para estender o aprendizado, aplicando os conceitos do K&R:

* **[projects](https://github.com/snake-outerheaven/journal-overflow/tree/main/projects)**: Aplicações práticas e código experimental.

---

## Começando

### Pré-requisitos para Windows

Certifique-se de ter o **MSVC (Microsoft Visual C++)** e o **CRT (C Runtime Library)** instalados.

* Baixe e instale o **Visual Studio Build Tools** [aqui](https://visualstudio.microsoft.com/visual-cpp-build-tools/).

#### Compilar no Windows

Abra o **Developer Command Prompt** do Visual Studio e use os comandos abaixo para compilar e executar:

```
cl /Fe:output_filename input_file.c
output_filename.exe
```

### Pré-requisitos para Ambientes Unix-like

Certifique-se de ter um compilador de C instalado. As opções mais comuns incluem:

* [GCC](https://gcc.gnu.org/)
* [Clang](https://clang.llvm.org/)

#### Compilar em Unix-like

Use os comandos abaixo no terminal para compilar e executar:

```
gcc -o output_filename input_file.c
./output_filename
```

---

## Licença

Este projeto está licenciado sob os termos da [GNU GPL v3](LICENSE).