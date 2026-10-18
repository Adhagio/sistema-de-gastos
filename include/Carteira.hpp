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

private:
  // map: busca pelo nome e ja sai em ordem alfabetica
  std::map<std::string, Categoria> categorias;
  // list: guarda a ordem dos lancamentos (vazia ate a etapa 3)
  std::list<Gasto> gastos;
};

#endif
