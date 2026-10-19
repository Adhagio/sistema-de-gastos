#ifndef CARTEIRA_HPP
#define CARTEIRA_HPP

#include <list>
#include <map>
#include <string>
#include <vector>

#include "Categoria.hpp"
#include "Gasto.hpp"

class Carteira {
public:
  bool cadastrarCategoria(const std::string &nome, double limite);
  std::vector<Categoria> listarCategorias() const;

  bool lancarGasto(const std::string &descricao, double valor,
                   const std::string &data, const std::string &categoria);
  std::vector<Gasto> listarGastos() const;

  std::vector<Gasto> maioresGastos(int n) const;
  std::vector<Categoria> categoriasEstouradas() const;

private:
  // map: busca pelo nome e ja sai em ordem alfabetica
  std::map<std::string, Categoria> categorias;
  // list: guarda a ordem dos lancamentos (push_back no fim, leitura no fim)
  std::list<Gasto> gastos;
};

#endif
