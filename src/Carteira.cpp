#include "Carteira.hpp"

bool Carteira::cadastrarCategoria(const std::string &nome, double limite) {
  if (nome.empty()) {
    return false;
  }

  // insert nao troca o que ja esta la:
  // se o nome ja existe, resultado.second vem false
  std::pair<std::map<std::string, Categoria>::iterator, bool> resultado =
      categorias.insert(std::make_pair(nome, Categoria(nome, limite)));

  return resultado.second;
}

std::vector<Categoria> Carteira::listarCategorias() const {
  std::vector<Categoria> resposta;
  for (std::map<std::string, Categoria>::const_iterator it = categorias.begin();
       it != categorias.end(); ++it) {
    resposta.push_back(it->second);
  }
  return resposta;
}

bool Carteira::lancarGasto(const std::string &descricao, double valor,
                           const std::string &data,
                           const std::string &categoria) {
  // regras: descricao vazia, valor <= 0, data invalida e categoria
  // inexistente fazem o lancamento falhar
  if (descricao.empty() || valor <= 0) {
    return false;
  }
  if (!Gasto::dataValida(data)) {
    return false;
  }

  std::map<std::string, Categoria>::iterator it = categorias.find(categoria);
  if (it == categorias.end()) {
    return false;
  }

  // deu certo: guarda o gasto (no fim, para manter a ordem) e
  // soma o valor ao total da categoria
  gastos.push_back(Gasto(descricao, valor, data, categoria));
  it->second.registrarGasto(valor);
  return true;
}

std::vector<Gasto> Carteira::listarGastos() const {
  // copia a list para um vector, na ordem dos lancamentos
  std::vector<Gasto> resposta(gastos.begin(), gastos.end());
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
