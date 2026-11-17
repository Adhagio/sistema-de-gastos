#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Arquivo.hpp"
#include "Carteira.hpp"
#include "Categoria.hpp"
#include "Gasto.hpp"

namespace {

// Le a linha inteira para converter com stoi/stod. false = entrada acabou.
bool lerLinha(const std::string& rotulo, std::string& texto) {
  std::cout << rotulo;
  if (!std::getline(std::cin, texto)) {
    std::cout << std::endl << "Entrada encerrada." << std::endl;
    return false;
  }
  return true;
}

}  // namespace

int main() {
  Carteira carteira;
  Arquivo arquivo;
  const std::string nomeArquivo = "dados.txt";
  bool rodando = true;

  // carrega no inicio: qualquer falha e tratada aqui, no main
  try {
    arquivo.carregar(carteira, nomeArquivo);
  } catch (const std::exception& e) {
    std::cout << "Erro ao carregar: " << e.what() << std::endl;
  }

  while (rodando) {
    try {
      std::cout << "=== Sistema de gastos ===" << std::endl;
      std::cout << "1) Cadastrar categoria" << std::endl;
      std::cout << "2) Listar categorias" << std::endl;
      std::cout << "3) Lancar gasto" << std::endl;
      std::cout << "4) Listar gastos" << std::endl;
      std::cout << "5) Total por categoria" << std::endl;
      std::cout << "6) Categorias que passaram do limite" << std::endl;
      std::cout << "7) Maiores gastos" << std::endl;
      std::cout << "0) Sair" << std::endl;

      std::string linhaOpcao;
      if (!lerLinha("> ", linhaOpcao)) {
        break;
      }
      size_t posOpcao = 0;
      int opcao = std::stoi(linhaOpcao, &posOpcao);
      if (posOpcao != linhaOpcao.size()) {
        throw std::invalid_argument("Opcao com caracteres invalidos: " +
                                    linhaOpcao);
      }

      if (opcao == 0) {
        try {
          arquivo.salvar(carteira, nomeArquivo);
        } catch (const std::exception& e) {
          std::cout << "Erro ao salvar: " << e.what() << std::endl;
        }
        std::cout << "Ate logo." << std::endl;
        rodando = false;

      } else if (opcao == 1) {
        std::string nome;
        if (!lerLinha("Nome: ", nome)) {
          break;
        }

        std::string textoLimite;
        if (!lerLinha("Limite (0 = sem limite): ", textoLimite)) {
          break;
        }
        size_t posLimite = 0;
        double limite = std::stod(textoLimite, &posLimite);
        if (posLimite != textoLimite.size()) {
          throw std::invalid_argument("Limite com caracteres invalidos: " +
                                      textoLimite);
        }

        carteira.cadastrarCategoria(nome, limite);
        std::cout << "Categoria cadastrada." << std::endl;

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
        std::string descricao;
        if (!lerLinha("Descricao: ", descricao)) {
          break;
        }

        std::string textoValor;
        if (!lerLinha("Valor: ", textoValor)) {
          break;
        }
        size_t posValor = 0;
        double valor = std::stod(textoValor, &posValor);
        if (posValor != textoValor.size()) {
          throw std::invalid_argument("Valor com caracteres invalidos: " +
                                      textoValor);
        }

        std::string data;
        if (!lerLinha("Data (AAAA-MM-DD): ", data)) {
          break;
        }

        std::string categoria;
        if (!lerLinha("Categoria: ", categoria)) {
          break;
        }

        carteira.lancarGasto(descricao, valor, data, categoria);
        std::cout << "Gasto cadastrado." << std::endl;

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

      } else if (opcao == 7) {
        std::string textoN;
        if (!lerLinha("N: ", textoN)) {
          break;
        }
        size_t posN = 0;
        int n = std::stoi(textoN, &posN);
        if (posN != textoN.size()) {
          throw std::invalid_argument("N com caracteres invalidos: " + textoN);
        }

        std::vector<Gasto> maiores = carteira.maioresGastos(n);
        if (maiores.empty()) {
          std::cout << "Nenhum gasto lancado." << std::endl;
        }
        // maior primeiro (o sort fica crescente, entao os maiores estao no fim)
        std::cout << std::fixed << std::setprecision(2);
        for (size_t i = 0; i < maiores.size(); ++i) {
          std::cout << "  " << maiores[i].getDescricao() << " - R$ "
                    << maiores[i].getValor() << std::endl;
        }
        std::cout.unsetf(std::ios::floatfield);
        std::cout.precision(6);

      } else {
        throw std::invalid_argument("Opcao invalida: digite de 0 a 7.");
      }
    } catch (const std::exception& e) {
      std::cout << "Erro: " << e.what() << std::endl;
    }
  }

  return 0;
}
