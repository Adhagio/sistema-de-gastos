#include <iostream>
#include <vector>
#include <algorithm>
#include "Gasto.hpp"
#include "Categoria.hpp"

int main() {
  std::vector<Gasto> gastos;
  gastos.push_back(Gasto("Almoco", 35.90, "2026-10-18", "Alimentacao"));
  gastos.push_back(Gasto("Uber", 22.00, "2026-10-18", "Transporte"));
  gastos.push_back(Gasto("Cafe", 5.00, "2026-10-18", "Alimentacao"));
  
  // Ordena pelo valor usando operator<
  std::sort(gastos.begin(), gastos.end());
  
  std::cout << "Gastos ordenados por valor:" << std::endl;
  for (size_t i = 0; i < gastos.size(); ++i) {
    std::cout << "  " << gastos[i].getDescricao() << " - R$ " << gastos[i].getValor();
    std::cout << " (" << gastos[i].getCategoria() << ")" << std::endl;
  }
  
  Categoria alimentacao("Alimentacao", 500.0);
  alimentacao.registrarGasto(35.90);
  alimentacao.registrarGasto(5.00);
  
  std::cout << "\nCategoria " << alimentacao.getNome();
  std::cout << " - Total: R$ " << alimentacao.getTotalGasto();
  if (alimentacao.temLimite()) {
    std::cout << " (limite: R$ " << alimentacao.getLimite() << ")";
  }
  std::cout << std::endl;
  std::cout << "Estourou? " << (alimentacao.estourou() ? "Sim" : "Nao") << std::endl;
  
  return 0;
}