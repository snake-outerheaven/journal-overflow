# Como gerar a documentação

A documentação do código (referência da API) é gerada pelo
[Doxygen](https://www.doxygen.nl/) a partir dos comentários `/** ... */`. Esta
mesma pasta `docs/` entra como páginas.

## Instalar

    winget install DimitriVanHeesch.Doxygen

Opcional: o Graphviz (`winget install Graphviz.Graphviz`) habilita os grafos de
chamadas e de inclusão. Sem ele, o Doxygen funciona normalmente, só sem grafos.

## Gerar

Na pasta `projects/squidsql`:

    doxygen Doxyfile

A saída fica em `docs\api\html`; abra `docs\api\html\index.html`.

O `Doxyfile` está configurado para tratar aviso como erro: qualquer entidade
sem documentação, parâmetro sem `@param` ou link quebrado faz o comando falhar
(código de saída diferente de zero). Isso mantém a documentação em dia.

## Como comentar o código

Use blocos Javadoc em C89 (`/** ... */`, nunca `//`):

    /**
     * @brief Uma linha dizendo o que a função faz.
     *
     * Detalhes, se precisar.
     *
     * @param nome  O que é.
     * @return O que devolve (e quando é erro).
     */

- Todo arquivo começa com `@file` e `@brief`.
- Campos de `struct` e valores de `enum` usam `/**< ... */` ao lado.
- Funções públicas ficam documentadas no `.h`; funções `static` no `.c`.
