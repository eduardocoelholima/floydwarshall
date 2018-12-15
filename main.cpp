/*

#Floyd Warshall
A C++ Implementation of Floyd-Warshall's Minimum Distante Paths for Graphs

Calculates the shortest paths among any two vertices in a graph with no negative cycles.
Input is made through a text file specially formatted.
Code was based on Cormen's pseudocode.

by Eduardo Coelho de Lima

--------------------------------------------------------------------

Universidade Federal do Rio Grande do Norte
Departamento de Informatica e Matematica Aplicada
Programa de Pos Graduacao em Sistemas e Computacao
Disciplina de Algoritmos e Estruturas de Dados


Projeto Algoritmo Floyd-Warshall
--------------------------------

Estudante
Eduardo Coelho de Lima

Professor
Bruno Motta de Carvalho

Requisitos e Respostas
----------------------

O Algoritmo de Floyd-Warshall é um algoritmo usado para calcular os caminhos
mais curtos em um grafo com pesos positivos e negativos que não possua ciclos
negativos. A execução deste algoritmo calcula os valores dos caminhos mais
curtos entre todos os pares de vértices. 

Realize as seguintes tarefas:

1. Escreva um programa em C/C++ que lê um arquivo que contém um número na
primeira linha, que indica o número N de vértices do grafo, seguido de N×N
valores que indicam os pesos associados as arestas que conectam dois vértices,
e implementa o Algoritmo de Floyd-Warshall.

A implementacao do algoritmo esta presente nos seguintes arquivos:

- main.cpp (Programa Principal)
- Matrix.cpp (Classe Matrix usada para armazenar as matrizes D e PI)
- input.txt, input2.txt (Exemplos de arquivo de entrada)
- main.exe (Programa compilado para Windows)
- main (Programa compilado para Linux)
- README.md (Descricao do projeto)

2. Calcule e armazene os caminhos dos menores caminhos para cada vértice.

O resultado final pode ser consultado na matriz D(k=n). Os caminhos podem
ser reconstruidos a partir da matriz PI(k=n).

3. Indique caso existam ciclos negativos.

E' possivel verificar se ha ciclos negativos no grafo consultando a
sua diagonal principal, ou seja, se D[n][i][i], 0<=i<n, possuir elementos
negativos, pode-se afirmar que ha' ciclos negativos no grafo. Esta
verificacao foi implementada no codigo apresentado.

4. Determine a complexidade do seu algoritmo.

O algoritmo possui 3 lacoes 'for' aninhados, com operacoes em tempo
constante sendo executadas dentro do laco. As demais operacoes sao
executadas em no maximo n^2, portanto o laco 'for' triplamente aninhado
domina as demais complexidades e podemos afirmar que o algoritmo como
um todo possui complexidade assimptotica de Theta(n^3).

*/


#include <iostream>
#include <fstream>
#include "Matrix.cpp"
#define INF 999999
#define NIL -999999
using namespace std;


int main(int argc, char const *argv[]) {

	// Checks if filename was specified in the command line,
	// otherwise searches for input.txt in current path
	string filename = "input.txt";
	if (argv[1]==nullptr) cout<<"No file specified. ";
	else filename = string(argv[1]);
	ifstream readfile (filename);

	// Iterates the file stream, file should contain graph's edges,
	// will process first line as the number of vertices n, and
	// each following line should then have n space-separated numerals
	// thus total number of lines on file should be 1+n.
	// While reading input, we assume 9999+ to be infinite
	string word;
	int n;
  	if (readfile.is_open()) {
  		cout<<"Trying to open "<<filename<<"... Success."<<endl;
  		readfile >> word;
  		n = stoi(word);
  	}
  	else cout << "Could not open " << filename << "." << endl; 
  	int W[n][n];
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			readfile>>word;
			if (word.empty()) {
				cout<< "Malformed file."<<endl;
				return 0;
			}
			W[i][j] = stoi(word);
			if (W[i][j]>=9999) W[i][j]=INF;
		}
	}
	readfile.close();


	// Creates a 3-dimentional distance D matrix
	// and a 3-dimentional PI matrix (previous vertex referente).
	// First dimension k represents algorithm iteration count,
	// second dimension i represents source vertix,
	// third dimension j represents destination vertix
	Matrix *D = new Matrix(n);
	Matrix *PI = new Matrix(n);


	// Loads W into D(0,*,*) and PI(0,*,*).
	// pi(0,i,j) will hold value of i, when there is an edge (i,j)
	for (int i=0;i<n;i++) {
			for (int j=0;j<n;j++) {
				D->write(0,i,j,W[i][j]);
				if (i==j||W[i][j]==INF) PI->write(0,i,j,NIL);
				else PI->write(0,i,j,i);
			}
	}


	// Runs floyd-warshall's algorithm
	for (int k=1;k<=n;k++) {
		for (int i=0;i<n;i++) {
			for (int j=0;j<n;j++) {
				if ( (D->read(k-1,i,k-1)!=INF && D->read(k-1,k-1,j)!=INF) && 
					 (D->read(k-1,i,j) > (D->read(k-1,i,k-1) + D->read(k-1,k-1,j) ) ) ) {
					D->write(k,i,j,(D->read(k-1,i,k-1) + D->read(k-1,k-1,j)));
					PI->write(k,i,j,PI->read(k-1,k-1,j));
				}
				else {
					D->write(k,i,j,D->read(k-1,i,j));
					PI->write(k,i,j,PI->read(k-1,i,j));
				}
			}
		}
	}


	// Prints matrices D and PI
	D->print("D",0);
	PI->print("PI",1);


	// Checks if there is any negative cicle in the graph
	for (int i=0;i<n;i++) {
		if (D->read(n,i,i)<0) {
			cout<<"Negative cycle found"<<endl;
			return 0;
		}
	}
	cout<<"Negative cycles were not found."<<endl;
}
