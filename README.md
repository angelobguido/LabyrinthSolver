# LabyrinthSolver

### Motivação
Este projeto foi desenvolvido para a disciplina SSC0601 - Laboratório de Introdução à Ciência da Computação da Universidade de São Paulo. Ele consiste de um resolvedor de labirintos com um sistema próprio de gerenciamento de arquivos e display de informações.

### Compilação
O programa vem com um MakeFile simples para facilitar a compilação, portanto, em sistemas com o 'make' instalado, basta digitar o seguinte comando no diretório no qual o arquivo está localizad:

```
make
```

Caso o 'make' não esteja instalado, pode-se compilar o programa digitando o seguinte comando:

```
gcc -o resolvedor_de_labirintos maze.c display.c file_routines.c main.c
```

