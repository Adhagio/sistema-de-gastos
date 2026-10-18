#include <iostream>
#include <string>
#include <vector>

#include "Carteira.hpp"
#include "Categoria.hpp"

int main() {
  Carteira carteira;
  bool rodando = true;

  while (rodando) {
    std::cout << "=== Sistema de gastos ===" << std::endl;
    std::cout << "1) Cadastrar categoria" << std::endl;
    std::cout << "2) Listar categorias" << std::endl;
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

    } else {
      std::cout << "Opcao invalida." << std::endl;
    }
  }

  return 0;
}
