#include "Arquivo.hpp"

#include "Carteira.hpp"
#include "Categoria.hpp"
#include "Gasto.hpp"

#include <cerrno>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

// funcoes auxiliares: so existem dentro deste .cpp

std::string numeroParaTexto(double valor) {
  std::ostringstream stream;
  // 15 digitos significativos: suficiente para dinheiro, sem mostrar o
  // "lixo" que o double tem nas casas decimais mais afastadas
  stream << std::setprecision(15) << valor;
  return stream.str();
}

std::vector<std::string> separarCampos(const std::string& linha) {
  std::vector<std::string> campos;
  std::istringstream stream(linha);
  std::string campo;
  while (std::getline(stream, campo, ';')) {
    campos.push_back(campo);
  }
  return campos;
}

}  // namespace

void Arquivo::salvar(const Carteira& carteira, const std::string& nomeArquivo) {
  std::ofstream arquivo(nomeArquivo.c_str());
  if (!arquivo.is_open()) {
    throw std::runtime_error("Nao foi possivel abrir o arquivo para escrita: " +
                             nomeArquivo);
  }

  // primeiro as categorias: ao carregar, um gasto so entra se a categoria
  // correspondente ja existir na carteira
  std::vector<Categoria> categorias = carteira.listarCategorias();
  for (size_t i = 0; i < categorias.size(); ++i) {
    arquivo << "C;" << categorias[i].getNome() << ';'
            << numeroParaTexto(categorias[i].getLimite()) << ';'
            << numeroParaTexto(categorias[i].getTotalGasto()) << '\n';
  }

  std::vector<Gasto> gastos = carteira.listarGastos();
  for (size_t i = 0; i < gastos.size(); ++i) {
    arquivo << "G;" << gastos[i].getDescricao() << ';'
            << numeroParaTexto(gastos[i].getValor()) << ';'
            << gastos[i].getData() << ';' << gastos[i].getCategoria() << '\n';
  }

  if (!arquivo) {
    throw std::runtime_error("Erro ao escrever no arquivo: " + nomeArquivo);
  }
}

void Arquivo::carregar(Carteira& carteira, const std::string& nomeArquivo) {
  errno = 0;
  std::ifstream arquivo(nomeArquivo.c_str());
  if (!arquivo.is_open()) {
    // a STL nao tem "existeArquivo()": ENOENT distingue "nao existe" de
    // "existe, mas nao abre"
    if (errno == ENOENT) {
      throw std::runtime_error("Arquivo nao encontrado: " + nomeArquivo);
    }
    throw std::runtime_error("Nao foi possivel abrir o arquivo para leitura: " +
                             nomeArquivo);
  }

  std::string linha;
  while (std::getline(arquivo, linha)) {
    if (linha.empty()) {
      continue;
    }

    std::vector<std::string> campos = separarCampos(linha);
    if (campos[0] == "C" && campos.size() == 4) {
      // campos[3] e o totalGasto salvo: so informacao. Quem recalcula o
      // total e lancarGasto, somando os gastos
      carteira.cadastrarCategoria(campos[1], std::stod(campos[2]));
    } else if (campos[0] == "G" && campos.size() == 5) {
      // campos[4] e o NOME da categoria, nao uma copia da categoria
      carteira.lancarGasto(campos[1], std::stod(campos[2]), campos[3],
                           campos[4]);
    } else {
      // prefixo desconhecido ou campos faltando: a excecao sobe ate o main
      throw std::runtime_error("Linha invalida no arquivo: " + linha);
    }
  }

  if (arquivo.bad()) {
    throw std::runtime_error("Erro ao ler o arquivo: " + nomeArquivo);
  }
}
