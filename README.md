# NSH
NSH is a simple UNIX shell written in C. It supports built-in commands such as `cd`, `help`, `pwd`, `echo`, and `exit`, along with the ability to execute other system commands.

# Demo
[Live Demo](https://asciinema.org/a/Rh9Mroqr49rpgwklI0n9Nr5x6)

# Getting Started
Follow these instructions to clone, build, and run NSH.

## Prerequisites
- GCC or any C compiler installed on your system.

### Installation
1. Clone the repository:
```shell
git clone https://github.com/nicolas-iskandar/nsh.git
cd nsh
```
2. Compile the program using the provided `Makefile`:
```shell
make
```
If `make` is not available, you can compile manually:
```shell
gcc -o nsh src/main.c src/builtins.c src/execute.c src/utils.c
```
3. Run the program:
```shell
./nsh
```

# License
This project is licensed under the [MIT License](LICENSE).