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
