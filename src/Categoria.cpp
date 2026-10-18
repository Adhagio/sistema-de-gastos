#include "Categoria.hpp"

Categoria::Categoria(const std::string &nome, double limite)
  : nome(nome), limite(limite), totalGasto(0.0) {}

const std::string &Categoria::getNome() const {
  return nome;
}

double Categoria::getLimite() const {
  return limite;
}

double Categoria::getTotalGasto() const {
  return totalGasto;
}

void Categoria::registrarGasto(double valor) {
  totalGasto += valor;
}

bool Categoria::temLimite() const {
  return limite > 0.0;
}

bool Categoria::estourou() const {
  return temLimite() && totalGasto > limite;
}