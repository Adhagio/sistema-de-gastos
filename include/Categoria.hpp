#ifndef CATEGORIA_HPP
#define CATEGORIA_HPP

#include <string>

class Categoria {
public:
  Categoria(const std::string &nome, double limite = 0.0);
  
  const std::string &getNome() const;
  double getLimite() const;
  double getTotalGasto() const;
  
  void registrarGasto(double valor);
  bool temLimite() const;
  bool estourou() const;

private:
  std::string nome;
  double limite;
  double totalGasto;
};

#endif