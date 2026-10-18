#ifndef GASTO_HPP
#define GASTO_HPP

#include <string>

class Gasto {
public:
  Gasto(const std::string &descricao, double valor, const std::string &data, const std::string &categoria);
  
  const std::string &getDescricao() const;
  double getValor() const;
  const std::string &getData() const;
  const std::string &getCategoria() const;
  
  bool operator<(const Gasto &outro) const;
  
  static bool dataValida(const std::string &data);

private:
  std::string descricao;
  double valor;
  std::string data;
  std::string categoria;
};

#endif