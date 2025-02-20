#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

void help() {
  std::cout << "to-do <operation> [value]" << std::endl;
  std::cout << std::endl;
  std::cout << "<add> [value] | aggiunge l'[elemento] nella todo list"
            << std::endl;
  std::cout << "<rm> [value]  | rimuove l'[elemento] dalla todo list"
            << std::endl;
  std::cout << "<ls>          | visualizza tutti gli elementi della todo list"
            << std::endl;
  std::cout << "< --help>     | visualizza questa schermata" << std::endl;
  std::cout << std::endl;
  std::cout << "per [value] non sono ammessi spazi" << std::endl;
  std::cout << std::endl;
  std::cout << "Es..." << std::endl;
  std::cout << std::endl;
  std::cout << "./a.out add palestra" << std::endl;
  std::cout << "./a.out rm palestra" << std::endl;
  std::cout << "..." << std::endl;
  exit(0);
}

void add(std::string path, int argc, std::string argv) {
  if (argc > 2) {
    std::ofstream file(path, std::ios::app);
    file << argv << std::endl;
    file.close();
  } else
    std::cout << "Sintassi sbagliata controlla --help" << std::endl;
}

void ls(std::string path) { system(("cat " + path).c_str()); }

void checkArg(int argc, char *argv[]) {
  if (argc > 1) {
    std::string argv1 = argv[1];
    if (argv1 != "add" && argv1 != "--help" && argv1 != "ls" && argv1 != "rm") {
      std::cout << "Sintassi sbagliata controlla --help" << std::endl;
    } else {
      if (argv1 == "ls")
        ls("to-do.txt");
      else if (argv1 == "add") {
        std::string argv2 = argv[2];
        add("to-do.txt", argc, argv2);
      } else if (argv1 == "--help")
        help();
      else if (argv1 == "rm")
        std::cout << "rm";
    }
    exit(0);
  } else {
    std::cout << "Wrong sintax check --help";
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  checkArg(argc, argv);
  return 0;
}
