#include <iostream>
using namespace std;

#define MAXV 10

int graph[MAXV][MAXV];
int count[MAXV];
int max;
int parent[MAXV];
int level[MAXV];

//queue - for BFS
class Queue {
	int size;
	int max;
	int* arr;
	int* front;
	int* rear;
	bool full;
	bool empty;
public:
	//TODO: queue to initialize with ZEROs
	Queue(int sz) : max(sz) { arr=new int[sz]; front=arr; rear=arr; empty=true; full=false; size=0; }
	bool isFull() { return full; }
	bool isEmpty() { return empty; }
	void setEmptyFull() { empty = (size == 0)?true:false; full = (size==max)?true:false; }
	void enq(int val) { 
		if( !isFull() ) {
			//cout << "qPush: " << val << endl;
			*rear++ = val;
			size++;
			setEmptyFull();
			return;
		}
		cout << "warn: Queue is Full!\n";
	}
	int deq() {
		if( !isEmpty() ) {
			int retVal = *front;
			for(int i=0;i<size;i++)
				arr[i] = arr[i+1];
			rear--;
			size--;
			setEmptyFull();
			//cout << "qPop: " << retVal << endl;
			return retVal;
		}
		cout << "warn: Queue is Empty!\n";
		return -1;
	}
};


void init() {
	::max = -1;
	for(int i=0;i<MAXV;i++) {
		count[i] = 0;
		parent[i] = -1;
		level[i] = -1;
		for(int j=0;j<MAXV;j++)
			graph[i][j] = -1;
	}
}

void addEdge(int src, int dest, int wt=1) {
	//forth
	graph[src][count[src]] = dest;
	count[src]++;

	//back
	//graph[dest][count[dest]] = src;
	//count[dest]++;

	//calc max vertex
	::max = (src>=dest)?src:dest;
}

void printGraph() {
	for(int i=0;i<= ::max;i++) {
		cout << "[" << i << "] -> ";
		for(int j=0;j<count[i];j++)
			cout << graph[i][j] << " -> ";
		cout << endl;
	}
}

//BFS START
void bfs(int s) {
	Queue q(::max);
	bool* visited = new bool[::max+1];
	for(int i=0;i< ::max+1;i++)
		visited[i] = false;
	// Mark the current node as visited and enqueue it
	visited[s] = true;
	//cout << "Marked Visited [" << s << "]\n"; 
	q.enq(s);

	while( !q.isEmpty() ) {
		s = q.deq(); //deq
		cout << s << " ";
		for(int cn=0;cn<count[s];cn++) {
			int v = graph[s][cn];
			//cout << "[" << s << "]:" << v << endl;
			if(v>=0) {
				//cout << "visited[" << v << "] ? " << visited[v] << endl;
				if( !visited[v] ) {
					visited[v] = true;
					//cout << "Marked Visited [" << v << "]\n"; 
					q.enq(v);
				}
			}
		}
	}
}
//BFS ENDS

//DFS START
void dfsUtil(int v, bool visited[]) {
	visited[v] = true;
	cout << v << " ";
	for(int cn=0;cn<count[v];cn++) {
		int x = graph[v][cn];
		//cout << "[" << s << "]:" << v << endl;
		if(x>=0) {
			//cout << "visited[" << v << "] ? " << visited[v] << endl;
			if( !visited[x] ) {
				dfsUtil(x, visited);
			}
		}
	}
}

void dfs(int v) {
	bool* visited = new bool[::max+1];
	for(int i=0;i< ::max+1;i++)
		visited[i] = false;
	dfsUtil(v, visited);
}
//DFS ENDS

//Dijkstras algo for shortest path
void dijk() {}

int main () {
	init();
	addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 2);
    addEdge(2, 0);
    addEdge(2, 3);
    addEdge(3, 3);
	//printGraph();
	bfs(2);
	//dfs(2);
}
