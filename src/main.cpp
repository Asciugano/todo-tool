#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string getPath() {
  std::ifstream file("./src/path.txt");
  if (!file) {
    std::cerr << "Errore: impossibile aprire path.txt\n";
    return "";
  }
  std::string path;
  std::getline(file, path);
  return path;
}

void help() {
  std::cout << "todo <operation> [value]\n\n"
            << "<add> [value]   | Aggiunge un elemento alla todo list\n"
            << "<rm> [value]    | Rimuove un elemento dalla todo list\n"
            << "<rm> [-a|--all] | Rimuove tutti gli elementi\n"
            << "<ls>            | Visualizza tutti gli elementi\n"
            << "<--help>        | Mostra questa schermata\n\n"
            << "Esempi:\n"
            << "./a.out add palestra\n"
            << "./a.out rm palestra\n\n";
}

void add(const std::string &path, const std::string &argv) {
  std::ofstream file(path, std::ios::app);
  if (!file) {
    std::cerr << "Errore: impossibile aprire " << path << "\n";
    return;
  }
  file << argv << "\n";
}

void ls(const std::string &path) {
  std::ifstream file(path);
  if (!file) {
    std::cerr << "Errore: impossibile aprire " << path << "\n";
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::cout << line << "\n";
  }
}

void rm(const std::string &path, const std::string &argv) {
  if (argv == "--all" || argv == "-a") {
    std::ofstream outFile(path, std::ios::trunc);
    outFile.close();
    return;
  }

  std::ifstream file(path);
  if (!file) {
    std::cerr << "Errore: impossibile aprire " << path << "\n";
    return;
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();

  std::string content = buffer.str();
  size_t pos = 0;
  while ((pos = content.find(argv, pos)) != std::string::npos) {
    size_t endPos = content.find("\n", pos);
    if (endPos != std::string::npos)
      content.erase(pos, endPos - pos + 1);
    else
      content.erase(pos);
  }

  std::ofstream outFile(path);
  outFile << content;
}

void checkArg(int argc, char *argv[]) {
  std::vector<std::string> options = {"add", "--help", "ls",    "rm",
                                      "-n",  "--new",  "change"};

  if (argc > 1) {
    std::string argv1 = argv[1];
    if (std::find(options.begin(), options.end(), argv1) == options.end()) {
      std::cout << "Sintassi sbagliata, controlla --help\n";
      return;
    }

    std::string path = getPath();
    if (argv1 == "ls")
      ls(path);
    else if (argv1 == "add" && argc > 2)
      add(path, argv[2]);
    else if (argv1 == "--help")
      help();
    else if (argv1 == "rm" && argc > 2)
      rm(path, argv[2]);
    else if ((argv1 == "-n" || argv1 == "--new") && argc > 2)
      std::cout << "new";
    else if (argv1 == "change" && argc > 2)
      std::cout << "change";
    else {
      std::cout << "Sintassi sbagliata, controlla --help\n";
    }
  }
}

int main(int argc, char *argv[]) {
  checkArg(argc, argv);
  return 0;
}
