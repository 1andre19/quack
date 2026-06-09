<img width="150" height="auto" alt="image" src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTxrXEG-jMu6jANZBfWWCXI9jJqEYLufE-Hyg&s" /> </br>
Proyecto de compilador para la clase TC3002B. Desarrollado en C++.

## Dependencias

Requiere: `g++` (C++17), `bison`, `flex`

```bash
sudo dnf install gcc-c++ bison flex   # Fedora
sudo apt install g++ bison flex       # Ubuntu/Debian
brew install bison flex               
```

## Cómo correr

```bash
git clone https://github.com/1andre19/quack
cd quack
cd src
make
```

Esto genera un ejecutable llamado `quack`. Para usarlo:

```bash
./quack source.pat
```

