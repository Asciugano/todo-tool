A simple todo list from terminal.

todo <operation> [value]

<add> [value]                | Aggiunge un elemento alla todo list
<rm> [value]                 | Rimuove un elemento dalla todo list
<rm> [-a|--all]              | Rimuove tutti gli elementi
<rm> [-f] [value]            | Rivuove la lista [value]
<ls>                         | Visualizza tutti gli elementi
<ls> [-l | --list]           | Visualizza tutte le liste
<-n | --new> [value]         | Crea una nuova lista con nome [value]
<change> [value]             | Cambia dalla lista corrente a quella [value]
<-nc | --new-change> [value] | Fa il new e il change insime
<--help>                     | Mostra questa schermata

La lista default e to-do

Esempi:
todo add palestra
todo rm palestra

to use insert:
export PATH="$PATH:/your/path/to-do_list/"
export PATH="$PATH:your/path/bin"
in yours .zshrc
after run: 
source ~/.zshrs
cd path/to/to-do_list
g++ -std=c++20 src/main.cpp -o todo
mv todo ~/bin/
and use the to-do tool  
