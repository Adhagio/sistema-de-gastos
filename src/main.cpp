#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "Carteira.hpp"
#include "Categoria.hpp"
#include "Gasto.hpp"

int main() {
  Carteira carteira;
  bool rodando = true;

  while (rodando) {
    std::cout << "=== Sistema de gastos ===" << std::endl;
    std::cout << "1) Cadastrar categoria" << std::endl;
    std::cout << "2) Listar categorias" << std::endl;
    std::cout << "3) Lancar gasto" << std::endl;
    std::cout << "4) Listar gastos" << std::endl;
    std::cout << "5) Total por categoria" << std::endl;
    std::cout << "6) Categorias que passaram do limite" << std::endl;
    std::cout << "0) Sair" << std::endl;
    std::cout << "> ";

    int opcao;
    if (!(std::cin >> opcao)) {
      // texto onde se espera numero: nao deixa o menu travar
      if (std::cin.eof()) {
        std::cout << std::endl << "Entrada encerrada." << std::endl;
        break;
      }
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      std::cout << "Entrada invalida: digite um numero." << std::endl;
      continue;
    }
    // descarta o resto da linha, para o getline abaixo ler a proxima
    std::cin.ignore(1000, '\n');

    if (opcao == 0) {
      std::cout << "Ate logo." << std::endl;
      rodando = false;

    } else if (opcao == 1) {
      std::cout << "Nome: ";
      std::string nome;
      std::getline(std::cin, nome);

      std::cout << "Limite (0 = sem limite): ";
      double limite;
      if (!(std::cin >> limite)) {
        if (std::cin.eof()) {
          std::cout << std::endl << "Entrada encerrada." << std::endl;
          break;
        }
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Entrada invalida: limite deve ser um numero." << std::endl;
        continue;
      }
      std::cin.ignore(1000, '\n');

      if (carteira.cadastrarCategoria(nome, limite)) {
        std::cout << "Categoria cadastrada." << std::endl;
      } else {
        std::cout << "Erro: ja existe categoria com esse nome (ou nome vazio)."
                  << std::endl;
      }

    } else if (opcao == 2) {
      std::vector<Categoria> categorias = carteira.listarCategorias();
      if (categorias.empty()) {
        std::cout << "Nenhuma categoria cadastrada." << std::endl;
      }
      for (size_t i = 0; i < categorias.size(); ++i) {
        std::cout << "  " << categorias[i].getNome();
        if (categorias[i].temLimite()) {
          std::cout << " - limite R$ " << categorias[i].getLimite();
        } else {
          std::cout << " - sem limite";
        }
        std::cout << std::endl;
      }

    } else if (opcao == 3) {
      std::cout << "Descricao: ";
      std::string descricao;
      std::getline(std::cin, descricao);

      std::cout << "Valor: ";
      double valor;
      if (!(std::cin >> valor)) {
        if (std::cin.eof()) {
          std::cout << std::endl << "Entrada encerrada." << std::endl;
          break;
        }
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Entrada invalida: valor deve ser um numero." << std::endl;
        continue;
      }
      std::cin.ignore(1000, '\n');

      std::cout << "Data (AAAA-MM-DD): ";
      std::string data;
      std::getline(std::cin, data);

      std::cout << "Categoria: ";
      std::string categoria;
      std::getline(std::cin, categoria);

      if (carteira.lancarGasto(descricao, valor, data, categoria)) {
        std::cout << "Gasto cadastrado." << std::endl;
      } else {
        std::cout << "Erro: descricao vazia, valor <= 0, data invalida ou "
                     "categoria inexistente."
                  << std::endl;
      }

    } else if (opcao == 4) {
      std::vector<Gasto> gastos = carteira.listarGastos();
      if (gastos.empty()) {
        std::cout << "Nenhum gasto lancado." << std::endl;
      }
      // 2 casas decimais, como no exemplo do DESCRICAO.md
      std::cout << std::fixed << std::setprecision(2);
      for (size_t i = 0; i < gastos.size(); ++i) {
        std::cout << "  " << gastos[i].getDescricao() << " - "
                  << gastos[i].getData() << " - R$ " << gastos[i].getValor()
                  << " - " << gastos[i].getCategoria() << std::endl;
      }
      // volta ao formato normal para as proximas saidas (ex.: limites)
      std::cout.unsetf(std::ios::floatfield);
      std::cout.precision(6);

    } else if (opcao == 5) {
      // mostra todas as categorias, inclusive as com total zero;
      // o total vem guardado na Categoria (copia feita por listarCategorias)
      std::vector<Categoria> categorias = carteira.listarCategorias();
      if (categorias.empty()) {
        std::cout << "Nenhuma categoria cadastrada." << std::endl;
      }
      std::cout << std::fixed << std::setprecision(2);
      for (size_t i = 0; i < categorias.size(); ++i) {
        std::cout << "  " << categorias[i].getNome() << ": R$ "
                  << categorias[i].getTotalGasto();
        if (categorias[i].temLimite()) {
          std::cout << " (limite R$ " << categorias[i].getLimite() << ")";
        } else {
          std::cout << " (sem limite)";
        }
        std::cout << std::endl;
      }
      std::cout.unsetf(std::ios::floatfield);
      std::cout.precision(6);

    } else if (opcao == 6) {
      std::vector<Categoria> estouradas = carteira.categoriasEstouradas();
      if (estouradas.empty()) {
        std::cout << "Nenhuma categoria passou do limite." << std::endl;
      }
      std::cout << std::fixed << std::setprecision(2);
      for (size_t i = 0; i < estouradas.size(); ++i) {
        std::cout << "  " << estouradas[i].getNome() << ": R$ "
                  << estouradas[i].getTotalGasto() << " (limite R$ "
                  << estouradas[i].getLimite() << ")" << std::endl;
      }
      std::cout.unsetf(std::ios::floatfield);
      std::cout.precision(6);

    } else {
      std::cout << "Opcao invalida." << std::endl;
    }
  }

  return 0;
}
