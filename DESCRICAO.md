# Descrição do sistema

A ideia era fazer um sistema que o controle de gastos que roda em mode texto. Permite cadastrar categorias e lançar gastos do cotidiano, e depois consultar totais por categoria, os maiores gastos e quais categorias passaram do limite.

## Nome e ideia

Sistema de controle de gastos pessoais. Serve, basicamente, para registrar gastos por categoria, assim como também acomapmhar limites definidos por categoria.

## O que o sistema guarda

Guarda gasto, onde possui descrição, valor, data, nome da categoria. Guarda categoria, onde possui nome, limite opcional (0=sem limite), total gasto. guarda a carteira que possui todas as categorias e todos os gastos.

## O que dá para fazer

1. Cadastrar categoria
2. Listar categorias
3. Cadastrar gasto
4. Listar gastos
5. Total por categoria
6. Categorias estouradas
7. Maiores gastos
0. Sair

## Regras

Não pode valor do gasto ser menor ou igual a que 0
Não pode haver duas categorias com o mesmo nome
Gasto só pode ser lançado em categoria que existe.
Data no formato AAAA-MM-DD
Limite é opcional, pois sem limite a categoria nunca estoura.
Se N>numero de gastos, mostrar todos.

## Quando algo dá errado

Categoria duplicada
Gasto em categoria Inexistente
Lista vazia
Texto onde se espera numero: mensagem volta ao menu, sem travar

## Classes que eu imagino

Gasto: dadps de um gasto e operator < por valor
Categoria: Nome, limite, e total gasto nela.
Carteira: guarda categorias e gastos, e responde consultas.
## Exemplo de uso

> 1
Nome: Alimentacao
Limite: 500
Categoria cadastrada.

> 1
Nome: Transporte
Limite:
Categoria cadastrada.

> 3
Descricao: Almoco
Valor: 35.90
Data: 2026-10-18
Categoria: Alimentacao
Gasto cadastrado.

> 3
Descricao: Uber
Valor: 22.00
Data: 2026-10-18
Categoria: Transporte
Gasto cadastrado.

> 5
Alimentacao: R$ 35.90
Transporte: R$ 22.00

> 7
N: 1
 Almoco - R$ 35.90

> 0
Ate logo.