# Plano do sistema de controle de gastos

Baseado em `DESCRICAO.md`. C++11, só biblioteca padrão, sem `new`/`delete`
(objetos guardados direto nos containers). Nenhuma classe usa `cin`/`cout`:
quem lê e escreve é a interface, em `src/main.cpp`.

## Arquivos

```text
include/Gasto.hpp      src/Gasto.cpp
include/Categoria.hpp  src/Categoria.cpp
include/Carteira.hpp   src/Carteira.cpp
                       src/main.cpp      interface (menu)
```

O comando de compilação do `README.md` não muda:
`g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema`

## As classes

### Gasto (não muda depois de criada)

Guarda: descrição (`string`), valor (`double`), data (`string` no formato
AAAA-MM-DD), nome da categoria (`string`).

- `Gasto(descricao, valor, data, categoria)` e os quatro getters.
- `bool operator<(const Gasto& outro) const` — compara pelo **valor**, como
  você escreveu na descrição. É ele que o `sort` vai usar.
- `static bool dataValida(const std::string& data)` — checa formato e
  números plausíveis (mês 1–12, dia 1–31). Exemplo: `"2026-13-40"` → `false`.

Por que a data é `string` e não uma classe `Data`: a regra do sistema é só
"formato AAAA-MM-DD". Uma classe nova só para isso pode ser o desafio 1
depois, se você quiser.

### Categoria

Guarda: nome (`string`), limite (`double`; 0 = sem limite), total gasto
(`double`, acumulado a cada gasto lançado).

- `Categoria(nome, limite)` e os getters.
- `void registrarGasto(double valor)` — soma ao total.
- `bool temLimite() const` — `limite > 0`.
- `bool estourou() const` — tem limite **e** `totalGasto() > limite`.

### Carteira (a "cérebro" do sistema)

Guarda os dois containers (abaixo). Nenhum `cin`/`cout`: devolve `bool` e
`vector` e quem imprime é o menu.

- `bool cadastrarCategoria(const string& nome, double limite)` — `false` se
  o nome já existe ou está vazio.
- `bool lancarGasto(const string& descricao, double valor, const string& data, const string& categoria)` —
  `false` se valor ≤ 0, data inválida ou categoria não existe. Se der certo,
  chama `registrarGasto` na categoria.
- `vector<Gasto> listarGastos() const` — na ordem em que foram lançados.
- `vector<Categoria> listarCategorias() const` — todas, ordenadas por nome.
- `vector<Gasto> maioresGastos(int n) const` — os `n` maiores; se `n` for
  maior que o total, devolve todos.
- `vector<Categoria> categoriasEstouradas() const` — só as que `estourou()`.

As consultas devolvem `vector` (cópia) porque a interface só quer **ler** o
resultado — assim ela não pode acidentalmente mexer nos dados guardados.

## Containers da STL e por quê

| Onde | Container | Por quê |
| --- | --- | --- |
| `Carteira`, categorias | `map<string, Categoria>` | Busca pelo nome (`find("Alimentacao")`), que é o jeito de saber se a categoria existe antes de lançar gasto. O nome duplicado já dá erro sozinho: `insert` não troca o que já está lá. E o map sai andando em ordem alfabética, então "listar categorias" já vem ordenado. |
| `Carteira`, gastos | `list<Gasto>` | Guarda a ordem dos lançamentos: entra no fim com `push_back`, percorre de começo a fim e sai na mesma ordem. Não precisamos de índice nem de inserir no meio, então a list basta. É o `list` que a atividade pede. |
| `Carteira::maioresGastos` | `vector<Gasto>` (cópia temporária) | Copia a list para um vector (`vector<Gasto> v(gastos.begin(), gastos.end())`) e chama `sort(v.begin(), v.end())`, que usa o `operator<` do `Gasto`. Depois pega os `n` maiores do fim. Vector porque o `sort` dele é o mais simples e rápido que a gente viu. |

Por que **não** um `set<Gasto>` para os maiores gastos: o `set` compara pelo
`operator<`, que é por valor — dois gastos de valor igual seriam tratados
como o mesmo e um sumiria. Um `multiset` resolveria, mas é um container que
você ainda não viu; copiar para o vector é mais simples.

## Etapas

Cada etapa termina compilando com o comando do `README.md` e com uma parte
do menu testável. Uma etapa por pedido meu, uma por commit seu.

### Etapa 1 — Gasto e Categoria (sem menu ainda)

Cria `include/Gasto.hpp`, `src/Gasto.cpp`, `include/Categoria.hpp`,
`src/Categoria.cpp`, e um `src/main.cpp` provisório só para testar: cria
dois `Gasto`, ordena um `vector` com `sort` e mostra na tela; cria uma
`Categoria` e soma dois gastos nela.

**Você testa:** compara e roda; vê os gastos saírem em ordem decrescente de
valor e o total da categoria batendo.

### Etapa 2 — Carteira com categorias

Cria `include/Carteira.hpp` e `src/Carteira.cpp` com `cadastrarCategoria` e
`listarCategorias` (a list de gastos ainda fica vazia; o mapa entra aqui).
O `main.cpp` vira menu de verdade, com as opções 1 (cadastrar categoria) e
2 (listar categorias), e a opção 0 sai.

**Você testa:** `./sistema < exemplos/categoria1.txt` — cadastra três
categorias, tenta repetir uma, lista. Repetida tem que dar mensagem de erro.

### Etapa 3 — Lançar gasto e listar

Adiciona `lancarGasto` (com as três validações) e `listarGastos` à Carteira.
Menu ganha as opções 3 (lançar gasto) e 4 (listar gastos).

**Você testa:** `exemplos/gasto1.txt` — lança gastos bons e ruins (valor 0,
categoria que não existe, data 2026-13-45) e lista; a lista tem que sair na
ordem dos lançamentos.

### Etapa 4 — Totais e limites

Adiciona `listarCategorias` completa (com o total acumulado) e
`categoriasEstouradas`. Menu ganha as opções 5 (total por categoria) e
6 (categorias que passaram do limite).

**Você testa:** `exemplos/limite1.txt` — uma categoria com limite estourado
e uma sem limite (sem limite nunca aparece como estourada).

### Etapa 5 — Maiores gastos

Adiciona `maioresGastos` (cópia para vector + `sort`). Menu ganha a opção 7,
que pede o N.

**Você testa:** `exemplos/maiores1.txt` — N=1, N=3 e N=999 (mostra todos).

### Etapa 6 — Entrada inválida e fechamento

Testa de propósito o caso que derruba menu em C++: digitar `abc` onde se
espera número. A interface tem que detectar `cin.fail()`, limpar com
`cin.clear()` e ignorar a linha, e voltar ao menu sem travar. Roda todos os
`exemplos/` de novo.

**Você testa:** `exemplos/entrada_ruim.txt` — cheio de texto no lugar de
número; o menu não pode travar.

Obs.: a proteção contra `fail()` já entra desde a etapa 2 no menu; a etapa 6
é o teste dirigido dela e o rodar tudo de novo.

## Pontos que deixei simples — me avise se quiser diferente

1. Nomes de categoria são **sensíveis a maiúsculas**: "Alimentacao" e
   "alimentacao" seriam duas categorias diferentes. O jeito simples é não
   normalizar nada.
2. "Total por categoria" lista **todas** categorias, inclusive as com total
   zero. Só a lista de estouradas filtra.
3. O total fica **guardado** na `Categoria` e é somado a cada lançamento
   (como na sua descrição). Calcular somando os gastos toda vez também
   funcionaria, mas é mais trabalho e fica mais lento.
4. Nomes e descrições vazios não podem ser cadastrados/lançados.
