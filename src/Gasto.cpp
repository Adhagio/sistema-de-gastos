#include "Gasto.hpp"
#include <cstddef>
#include <sstream>

Gasto::Gasto(const std::string &descricao, double valor, const std::string &data, const std::string &categoria)
  : descricao(descricao), valor(valor), data(data), categoria(categoria) {}

const std::string &Gasto::getDescricao() const {
  return descricao;
}

double Gasto::getValor() const {
  return valor;
}

const std::string &Gasto::getData() const {
  return data;
}

const std::string &Gasto::getCategoria() const {
  return categoria;
}

bool Gasto::operator<(const Gasto &outro) const {
  return valor < outro.valor;
}

bool Gasto::dataValida(const std::string &data) {
  if (data.length() != 10) {
    return false;
  }
  if (data[4] != '-' || data[7] != '-') {
    return false;
  }
  
  for (int i = 0; i < 4; ++i) {
    if (data[i] < '0' || data[i] > '9') {
      return false;
    }
  }
  for (int i = 5; i < 7; ++i) {
    if (data[i] < '0' || data[i] > '9') {
      return false;
    }
  }
  for (int i = 8; i < 10; ++i) {
    if (data[i] < '0' || data[i] > '9') {
      return false;
    }
  }
  
  int mes = 0, dia = 0;
  mes = (data[5] - '0') * 10 + (data[6] - '0');
  dia = (data[8] - '0') * 10 + (data[9] - '0');
  
  if (mes < 1 || mes > 12) {
    return false;
  }
  if (dia < 1 || dia > 31) {
    return false;
  }
  
  if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) {
    return false;
  }
  if (mes == 2 && dia > 29) {
    return false;
  }
  
  return true;
}