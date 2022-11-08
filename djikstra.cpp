/* Joao Lucas Mota Nogueira da Costa
Sua  tarefa  será  construir  um  grafo,  com  20  vértices  cujos  valores  serão  aleatoriamente 
selecinados em um conjunto de inteiros contendo números inteiros entre 1 e 100. Cada vértice terá um 
número aleatório de arestas menor ou igual a três. Cada aresta terá um peso definido por um número 
inteiro positivo aleatoriament definido entre 1 e 20. Você deverá criar este grafo, armazenando estes 
vértices  e  arestas  em  uma  tabela  de  adjacências  ou  em  uma  lista  de  adjacências,  nos  dois  caso 
armazenando o peso definido para cada uma delas. 
Seu  objetivo  será,  usando  o  algoritmo  de  menor  distância  de  Dijkstra,  imprimir  a  lista  de 
menores  distâncias,  destacando  a  ordem  de  visitação  dos  vértices  entre  um  vertice  inicial  da  sua 
escolha e todos os outros 19 vértices deste grafo.  
Para que este programa possa ser verificado, você deverá imprir, além da lista de caminhos e 
do  valor  da  menor  distância  uma  lista  de  pesos  de  cada  aresta  de  cada  um  dos  vértices  segundo  o 
modelo:  [1,2,  19],  neste  conjunto,  o  primeiro  número  indica  o  vertice  1,  o  segundo  o  vertice  2  e  o 
terceiro o peso da aresta entre os vértices 1 e 2.  
*/

#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
using namespace std;

#define INT_MAX 2147483647

class TGrafo {
private:
  int n;
  int m;
  int **mat_adj;

public:
  TGrafo(int n);
  void insereA(int v, int w, int y);
  void show();
  void createFiles();
  void shortestPath(int src);
  ~TGrafo();
};

TGrafo::TGrafo(int n) {
  this->n = n;
  this->m = 0;
  int **mat_adjac = new int *[n];
  for (int i = 0; i < n; i++)
    mat_adjac[i] = new int[n];
  mat_adj = mat_adjac;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      mat_adj[i][j] = 0;
}

TGrafo::~TGrafo() {
  n = 0;
  m = 0;
  delete[] * mat_adj;
}

void TGrafo::insereA(int v, int w, int y) {
  if (mat_adj[v][w] == 0) {
    mat_adj[v][w] = y;
    m++;
  }
}

void TGrafo::show() {
  cout << "Numero de vertices: " << n << endl;
  cout << "Numero de arestas: " << m << endl;
  cout << "\nMatriz de Adjacencia:" << endl;
  cout << "{";
  for (int i = 0; i < n; i++) {
    if (i != 0){
      cout << "\n";
    }
    for (int w = 0; w < n; w++){
      if (i == n){
         cout << mat_adj[i][w];
      }else{
        cout << mat_adj[i][w] << ", ";
      }
    }
  }
  cout << "}" << endl;
  cout << "\nFim da impressao da matriz do grafo." << endl;
  cout << "\nLista de arestas com suas respectivas distancias:" << endl;
  for (int i = 0; i < n; i++) {
    cout << "\n";
    for (int w = 0; w < n; w++){
      if (mat_adj[i][w] != 0){
        cout << "[" << i << "," << w << "]= " << mat_adj[i][w] << " ";
      }
    }
  }
}

void TGrafo::createFiles() {
  ofstream file1;
  file1.open("Dijkstra.txt");

  file1 << "Numero de vertices: " << n << endl;
  file1 << "Numero de arestas: " << m << endl;
  file1 << "\nMatriz de Adjacencia:" << endl;
  file1 << "{";
  for (int i = 0; i < n; i++) {
    if (i != 0){
      file1 << "\n";
    }
    for (int w = 0; w < n; w++){
      if (i == n){
         file1 << mat_adj[i][w];
      }else{
        file1 << mat_adj[i][w] << ", ";
      }
    }
  }
  file1 << "}" << endl;
  file1 << "\nFim da impressao da matriz do grafo." << endl;
  file1 << "\nLista de arestas com suas respectivas distancias:";
  for (int i = 0; i < n; i++) {
    file1 << "\n";
    for (int w = 0; w < n; w++){
      if (mat_adj[i][w] != 0){
        file1 << "[" << i << "," << w << "]= " << mat_adj[i][w] << " ";
      }
    }
  }
}

void TGrafo::shortestPath(int src){
  int dist[20];
  bool sp[20];

  for(int i = 0; i < 20; i++){
    dist[i] = INT_MAX;
    sp[i] = false;
  }
  dist[src] = 0;
  int min = INT_MAX, min_index;
  for (int i = 0; i < 19; i++){
    for (int i=0; i < 20; i++){
      if (sp[i] == false && dist[i] <= min){
        min = dist[i];
        min_index = i;
      }
    }
    int x = min_index;
    sp[x] = true;
    for (int i = 0; i < 20; i++){
      if ((sp[i] == false) && (mat_adj[x][i] && dist[x] != INT_MAX)
           && (dist[x] + mat_adj[x][i] < dist[i])){
        dist[i] = dist[x] + mat_adj[x][i];
      }
    }
  }
  ofstream file;
  file.open("Dijkstra.txt", ios::app);
  cout << "\nMenores distancias do vertice 1:" << endl;
  file << "\nMenores distancias do vertice 1:" << endl;
  cout << "\nVertice \t Menor distancia" << endl;
  file << "\nVertice \t Menor distancia" << endl;
  for (int i = 0; i < 20; i++){
    if (dist[i] == INT_MAX){
      cout << i+1 << "\t\t\t -" << endl;
      if (i+1 < 10){
        file << i+1 << "\t\t\t\t\t -" << endl;
      }else{
        file << i+1 << "\t\t\t\t -" << endl;
      }
    }else{
      cout << i+1 << "\t\t\t " << dist[i] << endl;
      if (i+1 < 10){
        file << i+1 << "\t\t\t\t\t " << dist[i] << endl;
      }else{
        file << i+1 << "\t\t\t\t " << dist[i] << endl;
      }
    }
  }
  file.close();
}

int main() {
  TGrafo g(20);
  random_device a;
  mt19937 gerador(a());
  uniform_int_distribution<int> range(1, 20);
  uniform_int_distribution<int> qtd(1, 3);
  auto start = chrono::steady_clock::now();
  for (int i = 0; i < 20; i++) {
    int q = qtd(gerador);
    for (int j = 0; j < q; j++) {
      int x = range(gerador);
      int y = range(gerador);
      if (i != x){
        g.insereA(i, x, y);
      }
    }
  }
  auto end = chrono::steady_clock::now();
  double tempo =
      chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  g.show();
  cout << "\n\nTempo utilizado para criar a matriz de adjacencias: "
       << tempo << " Nanossegundos" << endl;
  g.createFiles();
  g.shortestPath(0);
}
