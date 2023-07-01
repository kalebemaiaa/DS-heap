# Explorador de árvores strify

Nesse repósitorio foi desenvolvido o código de um explorador de árvores em cpp. O principal objetivo é trabalhar com a visualização
de informações e a ordenação de dados, além de comparar tempo de execução e verificar a eficiência de determinados algoritimos. 

## Iniciando

Essas instruções permitirão que você obtenha uma cópia do projeto em sua máquina local para desenvolvimento e testes.

### Pré-requisitos

As bibliotecas utilizadas foram apenas bibliotecas built-in.

> linux & MAC

Para esses sistemas operacionais, não é necessário quase que nenhuma configuração prévia, apenas clone o repositório que eles já possuem compilador próprio.

> Windows

Por outro lado, para máquinas com SO windows, será necessário a instalação de algum compilador para códigos C/C++. O mais utilizado é o MinGw e aqui está o link: https://www.mingw-w64.org/

### Instalação

Varia de pessoa para pessoa, mas o básico é um compilador e uma IDE de sua preferência.


## Compilação e Execução 

### Windows

Para executa o códigio em uma máquina após ter instalado MinGw e configurado a variável de sistema path, digite:

```
g++ main.cpp -o main
```

Em seguida, rode:

```
./main
```

E veja a mágica acontecer.

### Linux and Mac

Nesse caso, fica bem mais simples, basta digitar:

```
make main
```

E ver tudo funcionar

## Funções

Muitas funções são consideradas importantes, entre elas, há as básicas para se trabalhar com arvores, como a função 
```cpp 
void insertNode(Node **ptrRoot, int iValue);
Node *searchValue(Node *ptrRoot, int iValue);
bool isPerfect(Node *ptrRoot);
```
Ou então funções para auxiliar na abertura de arquivos 
```cpp
/**
 * Dado o endereço da raiz, escreve os valores da arvore em um arquivo in order
 * 
 * @param ptrRoot endereço que guarda a raiz
 * @param sFileName nome do arquivo para ser aberto
 * @param iFormat2Write inteiro que indica o formato de escrita, sendo 0(in order) ou 1(complete)
 * @return inteiro que indica a quantidade de elementos escritos
 */
int writeFile(Node *ptrRoot, const char *sFileName, int iFormat2Write)
```
Todas funções possuem comentários prévios que dizem sobre o que elas se tratam e como utilizar, como o exemplo a cima.

## Exemplos de uso

Menu principal 

![image](https://github.com/kalebemaiaa/DS-heap/assets/81570326/f305522d-c94b-4c55-87c9-9a9de1eed7b7)

Erros são sinalizados em vermelho

![image](https://github.com/kalebemaiaa/DS-heap/assets/81570326/15f2d3a8-2661-4604-8212-a7278be0abb8)

Execuções corretas em verde

![image](https://github.com/kalebemaiaa/DS-heap/assets/81570326/3556bab8-9321-4662-a869-ed97f6cd98cd)

## Autores

* **Adrian Castro** - [@adrianfilipe](https://github.com/adrianfilipe)
* **Erique Fernandes** - [@EriqueFernandes](https://github.com/EriqueFernandes)
* **Kalebe Maia** - [@kalebemaiaa](https://github.com/kalebemaiaa)
