#include "Carteira.hpp"

#include <algorithm>
#include <stdexcept>

void Carteira::cadastrarCategoria(const std::string &nome, double limite) {
  if (nome.empty()) {
    throw std::invalid_argument("Nome da categoria nao pode ser vazio.");
  }

  // insert nao troca o que ja esta la:
  // se o nome ja existe, resultado.second vem false
  std::pair<std::map<std::string, Categoria>::iterator, bool> resultado =
      categorias.insert(std::make_pair(nome, Categoria(nome, limite)));

  if (!resultado.second) {
    throw std::invalid_argument("Ja existe categoria com esse nome: " + nome);
  }
}

std::vector<Categoria> Carteira::listarCategorias() const {
  std::vector<Categoria> resposta;
  for (std::map<std::string, Categoria>::const_iterator it = categorias.begin();
       it != categorias.end(); ++it) {
    resposta.push_back(it->second);
  }
  return resposta;
}

void Carteira::lancarGasto(const std::string &descricao, double valor,
                            const std::string &data,
                            const std::string &categoria) {
  // regras: descricao vazia, valor <= 0, data invalida e categoria
  // inexistente sao dados invalidos
  if (descricao.empty()) {
    throw std::invalid_argument("Descricao do gasto nao pode ser vazia.");
  }
  if (valor <= 0) {
    throw std::invalid_argument("Valor do gasto deve ser maior que zero.");
  }
  if (!Gasto::dataValida(data)) {
    throw std::invalid_argument("Data invalida (use AAAA-MM-DD): " + data);
  }

  std::map<std::string, Categoria>::iterator it = categorias.find(categoria);
  if (it == categorias.end()) {
    throw std::invalid_argument("Categoria inexistente: " + categoria);
  }

  // deu certo: guarda o gasto (no fim, para manter a ordem) e
  // soma o valor ao total da categoria
  gastos.push_back(Gasto(descricao, valor, data, categoria));
  it->second.registrarGasto(valor);
}

std::vector<Gasto> Carteira::listarGastos() const {
  // copia a list para um vector, na ordem dos lancamentos
  std::vector<Gasto> resposta(gastos.begin(), gastos.end());
  return resposta;
}

std::vector<Gasto> Carteira::maioresGastos(int n) const {
  if (n <= 0) {
    throw std::invalid_argument("N deve ser maior que zero.");
  }

  // copia a list para um vector: o sort do vector e o mais simples que a
  // gente viu, e a copia protege os dados guardados (a consulta e const)
  std::vector<Gasto> copia(gastos.begin(), gastos.end());

  // sort em ordem crescente usando Gasto::operator< (compara pelo valor)
  std::sort(copia.begin(), copia.end());

  // se N for maior que o total, devolve todos
  int quantidade = n;
  if (quantidade > static_cast<int>(copia.size())) {
    quantidade = static_cast<int>(copia.size());
  }

  // os maiores ficaram no fim do vector; pegamos de la para tras,
  // assim a resposta ja sai do maior para o menor
  std::vector<Gasto> resposta;
  for (int i = 0; i < quantidade; ++i) {
    resposta.push_back(copia[copia.size() - 1 - i]);
  }
  return resposta;
}

std::vector<Categoria> Carteira::categoriasEstouradas() const {
  std::vector<Categoria> resposta;
  // estourou() usa o total ja guardado na Categoria (somado pelo
  // registrarGasto a cada lancamento) - nao precisa somar os gastos de novo
  for (std::map<std::string, Categoria>::const_iterator it = categorias.begin();
       it != categorias.end(); ++it) {
    if (it->second.estourou()) {
      resposta.push_back(it->second);
    }
  }
  return resposta;
}
