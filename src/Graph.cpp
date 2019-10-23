#include<iostream>
#include <list>
#define NIL -1
using namespace std;
#include <iomanip>
#include <map>
#include <fstream>
#include<string>
#include <cstdlib>
#include <iterator>
#include <sstream>
class Graph{
    int V;
    list<int> *adj;
    void bridgeUtil(int v, bool visited[], int disc[], int low[],int parent[],std::map<int,int> &NodexNode, fstream &salida);
public:
    Graph(int V);
    void addEdge(int v, int w);
    void bridge(std::map<int,int> &NodexNode,fstream &salida);
    void print();
    void Deletet();
};
Graph::Graph(int V){
    this->V = V;
    adj = new list<int>[V];
}
void Graph::print(){
  for (int v = 1; v < this->V; ++v)
    {
        cout << "\n Adjacency list of vertex "
             << v << "\n head ";
        for (auto x : adj[v])
           cout << "-> " << x;
        printf("\n");
    }
}
void Graph::addEdge(int v, int w){
    adj[v].push_back(w);
}
void Graph::Deletet(){
  delete[] this->adj;
}
void Graph::bridgeUtil(int u, bool visited[], int disc[],int low[], int parent[],std::map<int,int> &NodexNode,fstream &salida){
    static int time = 0;
    visited[u] = true;
    disc[u] = low[u] = ++time;
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;
        if (!visited[v])
        {
            parent[v] = u;
            bridgeUtil(v, visited, disc, low, parent,NodexNode,salida);
            low[u]  = min(low[u], low[v]);
            if (low[v] > disc[u]){
              int Node=NodexNode.at(u);
              int Node2=NodexNode.at(v);
              cout<<Node <<"-" << Node2 << endl;
              salida<<Node <<"-" << Node2 << endl;}
        }
        else if (v != parent[u])
            low[u]  = min(low[u], disc[v]);
    }
}
void Graph::bridge(std::map<int,int> &NodexNode,fstream &salida){
    bool *visited = new bool[V];
    int *disc = new int[V];
    int *low = new int[V];
    int *parent = new int[V];
    for (int i = 0; i < V; i++){
        parent[i] = NIL;
        visited[i] = false;}
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            bridgeUtil(i, visited, disc, low, parent,NodexNode,salida);
    delete[] visited;
    delete[] disc;
    delete[] low;
    delete[] parent;
}
int main(int argc, char const *argv[]){
    string Line;
    fstream newFile;
    int it=0;
    fstream salida;
    salida.open("Salida.txt",fstream::out);
    newFile.open(argv[1]);
    if (!newFile.is_open()) {
      cout<<"Error"<<endl;
    }
    if (newFile.is_open()) {
      while (getline(newFile,Line)) {
        int nodos=stoi(Line);
        Graph g2(nodos);
        map<int, int> NodexNode;
        map<int, int> NodexNode2;
        for (int i = 0; i < nodos; i++) {
          getline(newFile,Line);
          list<int> list;
          for(char c: Line){
            int y=c-'0';
            if (y!=-16) {
              list.push_back(y);}
            }
          int front=list.front();
          if (NodexNode.count(front)==0) {
            NodexNode.insert(pair<int,int>(front,it));
            NodexNode2.insert(pair<int,int>(it,front));
            it++;
          }
          int x=NodexNode.at(front);
          for(int c: list){
            if (c!=front) {
              if (NodexNode.count(c)==0) {
                NodexNode.insert(pair<int,int>(c,it));
                NodexNode2.insert(pair<int,int>(it,c));
                it++;}
              int x2=NodexNode.at(c);
              g2.addEdge(x,x2);
            }
          }
        }
        it=0;
        g2.bridge(NodexNode2,salida);
        g2.Deletet();
      }
    }
    salida.close();
    newFile.close();
    return 0;
}
