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
  std::cout << "Es..." << std::endl;
  std::cout << std::endl;
  std::cout << "./a.out add palestra" << std::endl;
  std::cout << "./a.out rm palestra" << std::endl;
  std::cout << "..." << std::endl;
  exit(0);
}

void checkArg(int argc, char *argv[]) {
  if (argc > 1) {
    std::string argv1 = argv[1];
    if (argv1 != "add" && argv1 != "--help" && argv1 != "ls" && argv1 != "rm") {
      std::cout << "Wrong syntax check --help" << std::endl;
    } else {
      if (argv1 == "ls")
        std::cout << "ls";
      else if (argv1 == "add")
        std::cout << "add";
      else if (argv1 == "--help")
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
