#include <fstream>
#include <iostream>
#include <string>

void checkArg(int argc, char *argv[]) {
  if (argc >= 1) {
    std::string argv1 = argv[1];
    if (argv1 != "add" && argv1 != "--help" && argv1 != "ls") {
      std::cout << "Wrong syntax check --help" << std::endl;
    } else {
      if (argv1 == "ls")
        std::cout << "ls";
      else if (argv1 == "add")
        std::cout << "add";
      else if (argv1 == "--help")
        std::cout << "help";
    }
    exit(0);
  }
  std::cout << "Wrong sintax check --help";
  exit(1);
}

int main(int argc, char *argv[]) {
  checkArg(argc, argv);
  return 0;
}
