# Nome do sistema

Atividade da Unidade 2 de Linguagem de Programação I. Leia `ENUNCIADO.md`
antes de começar.

Uma frase dizendo o que o sistema faz. A descrição completa está em
`DESCRICAO.md`.

## Arquivos

```text
.
├── AGENTS.md       regras que a IA lê antes de cada pedido
├── DESCRICAO.md    a descrição do sistema, escrita por você
├── ENUNCIADO.md    a atividade
├── PLANO.md        o plano feito com a IA (criado na etapa 3)
├── README.md       este arquivo
├── exemplos/       arquivos de entrada para testar
├── include/        um .hpp por classe
└── src/            um .cpp por classe, mais a interface
```

## Compilar e executar

```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema
./sistema
```

Se o comando mudar, atualize esta seção. Na correção eu vou usar o que
estiver escrito aqui.

## Onde uso a STL

Escreva esta seção sem IA. Para cada container ou algoritmo da STL que o
sistema usa: em que classe ele está, o que guarda, e por que você escolheu
ele e não outro.

| Onde | O quê | Por quê |
| ---- |--- | --- |
|Carteira(categorias)|std::map<std::string, Categoria> |busca por nome com find para saber se existe antes de lançar gasto; o insert não duplica; sai em ordem alfabética na listagem|
|Carteira (gastos)|std::list<Gasto>|preserva a ordem de lançamento; só entra no fim (push_back), nunca no meio|
|Carteira::maioresGastos|std::vector<Gasto> + std::sort|copia a list para um vector, ordena com std::sort (que usa Gasto::operator< por valor) e pega do fim para trás|
Retornos da Carteira|std::vector<...>|devolve cópia para a interface só ler, sem risco de alterar os dados guardados
## Como usei a IA

Escreva com as suas palavras:

- Modelo usado: Big Pickle

- Um pedido que deu certo, e por que você acha que deu certo: Etapa 3, quando escrevi no prompt "ao lançar um gasto, atualize o total da categoria". Deu certo porque a regra estava explícita no pedido.

- Um pedido que deu errado, o que veio errado e como você mudou o pedido: A IA inventou uma opção "listar categorias" no PLANO.md e mudou a numeração do menu. Corrigi atualizando o DESCRICAO.md.

- Uma coisa que a IA sugeriu e você recusou, e por quê: Ela sugeriu set<Gasto> para os maiores gastos; recusei porque set descarta valores iguais. Pedi vector + sort.
