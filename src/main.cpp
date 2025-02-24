#include <algorithm>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string getPath() {
  std::ifstream file("/Users/samuelediaferio/Desktop/to-do_list/src/path.txt");
  if (!file) {
    std::cerr << "Errore: impossibile aprire path.txt\n";
    return "";
  }
  std::string path;
  std::getline(file, path);
  return path;
}

void help() {
  std::cout
      << "todo <operation> [value]\n\n"
      << "<add> [value]                | Aggiunge un elemento alla todo list\n"
      << "<rm> [value]                 | Rimuove un elemento dalla todo list\n"
      << "<rm> [-a|--all]              | Rimuove tutti gli elementi\n"
      << "<rm> [-f] [value]            | Rivuove la lista [value]\n"
      << "<ls>                         | Visualizza tutti gli elementi\n"
      << "<ls> [-l | --list]           | Visualizza tutte le liste\n"
      << "<-n | --new> [value]         | Crea una nuova lista con nome "
         "[value]\n"
      << "<change> [value]             | Cambia dalla lista corrente a quella "
         "[value]\n"
      << "<-nc | --new-change> [value] | Fa il new e il change insime\n"
      << "<--help>                     | Mostra questa schermata\n\n"
      << "La lista default e to-do\n\n"
      << "Esempi:\n"
      << "todo add palestra\n"
      << "todo rm palestra\n\n";
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

void newPath(std::string argv) {
  if (argv.find(".txt") == std::string::npos)
    argv.append(".txt");
  std::ofstream newFile(argv);
  std::cout << argv << "file creato" << std::endl;
  newFile.close();
}

void change(std::string argv) {
  if (argv.find(".txt") == std::string::npos)
    argv.append(".txt");
  std::ofstream file(getPath());
  if (!file) {
    std::cerr << "nessun file trovato" << std::endl;
    exit(1);
  }
  file << argv;
  file.close();
}

void rmFile(std::string argv) {
  if (argv.find(".txt") == std::string::npos)
    argv.append(".txt");
  if (remove(argv.c_str()) != 0)
    std::cerr << "non sono riuscito a rimouvere " << argv << std::endl;
  else
    std::cout << argv << " rimosso" << std::endl;
}

void ls_list() {
  for (const auto &entry : std::filesystem::directory_iterator(".")) {
    if (entry.is_regular_file()) {
      std::string ext = entry.path().extension().string();

      if (!ext.empty() && ext == ".txt")
        std::cout << entry.path().filename() << std::endl;
    }
  }
}

void checkArg(int argc, char *argv[]) {
  std::vector<std::string> options = {"add", "--help",      "-h",    "ls",
                                      "rm",  "-n",          "--new", "change",
                                      "-nc", "--new-change"};

  if (argc > 1) {
    std::string argv1 = argv[1];
    if (std::find(options.begin(), options.end(), argv1) == options.end()) {
      std::cout << "Sintassi sbagliata, controlla --help\n";
      return;
    }

    std::string path = getPath();
    if (argv1 == "ls") {
      if (argc > 2) {
        std::string argv2 = argv[2];
        if (argv2 == "-l" || argv2 == "--list")
          ls_list();
        else
          std::cout << "Sintassi sbagliata, controlla --help\n";
      } else
        ls(path);
    } else if (argv1 == "add" && argc > 2)
      add(path, argv[2]);
    else if (argv1 == "--help" || argv1 == "-h")
      help();
    else if (argv1 == "rm" && argc > 2) {
      if (argc > 3) {
        std::string argv2 = argv[2];
        if (argv2 == "-f")
          rmFile(argv[3]);
        else
          std::cout << "Sintassi sbagliata, controlla --help\n";
      }
      rm(path, argv[2]);
    } else if ((argv1 == "-n" || argv1 == "--new") && argc > 2)
      newPath(argv[2]);
    else if (argv1 == "change" && argc > 2)
      change(argv[2]);
    else if ((argv1 == "-nc" || argv1 == "--new-change") && argc > 2) {
      newPath(argv[2]);
      change(argv[2]);
    } else {
      std::cout << "Sintassi sbagliata, controlla --help\n";
    }
  } else
    std::cout << "Sintassi sbagliata, controlla --help\n";
}

int main(int argc, char *argv[]) {
  checkArg(argc, argv);
  return 0;
}
