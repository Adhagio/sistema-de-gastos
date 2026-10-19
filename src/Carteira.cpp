#include "Carteira.hpp"

#include <algorithm>

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

std::vector<Gasto> Carteira::maioresGastos(int n) const {
  // N <= 0 nao tem o que mostrar
  if (n <= 0) {
    return std::vector<Gasto>();
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
