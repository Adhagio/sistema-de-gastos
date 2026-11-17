#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include <string>

// declaracao antecipada: o header so guarda referencias, nao precisa do
// conteudo de Carteira (quem precisa e o .cpp)
class Carteira;

class Arquivo {
public:
  void salvar(const Carteira& carteira, const std::string& nomeArquivo);
  bool carregar(Carteira& carteira, const std::string& nomeArquivo);
};

#endif
