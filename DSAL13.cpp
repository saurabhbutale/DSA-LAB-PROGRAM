#include <iostream>
#define MAX_VERTICES 100
using namespace std;
int visited[MAX_VERTICES] = {0};
int adjMatrix[MAX_VERTICES][MAX_VERTICES];
int nVertices = -1;
int nEdges = 0;

struct Node {
    int data;
    Node* next;
};

Node* adjList[MAX_VERTICES];

void addEdgeToAdjMatrix(int u, int v) {
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;
}

void addEdgeToAdjList(int u, int v) {
    Node* newNode = new Node();
    newNode->data = v;
    newNode->next = adjList[u];
    adjList[u] = newNode;

    newNode = new Node();
    newNode->data = u;
    newNode->next = adjList[v];
    adjList[v] = newNode;
}

void displayAdjMatrix() {
    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i <= nVertices; i++) {
        for (int j = 0; j <= nVertices; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void displayAdjList() {
    cout << "Adjacency List:" << endl;
    for (int i = 0; i <= nVertices; i++) {
        cout << i << ": ";
        Node* currentNode = adjList[i];
        while (currentNode != nullptr) {
            cout << currentNode->data << " ";
            currentNode = currentNode->next;
        }
        cout << endl;
    }
}

void dfs(int vertex) {
    visited[vertex] = 1;
    cout << vertex << " ";
    for (int i = 1; i <= nVertices; i++) {
        if (adjMatrix[vertex][i] == 1 && visited[i] == 0) {
            dfs(i);
        }
    }
    
}

void bfs(int vertex, int visited[]) {
    int queue[MAX_VERTICES];
    int front = -1;
    int rear = -1;
    visited[vertex] = 1;
    queue[++rear] = vertex;
    while (front != rear) {
        vertex = queue[++front];
        cout << vertex << " ";
        Node* currentNode = adjList[vertex];
        while (currentNode != nullptr) {
            int neighbor = currentNode->data;
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                queue[++rear] = neighbor;
            }
            currentNode = currentNode->next;
        }
    }
}

int main() {
    int choice;
    char addMore;
    int visited[MAX_VERTICES] = {0};
    while (true) {
        cout << "Select an option:" << endl;
        cout << "1. Add an edge" << endl;
        cout << "2. Display adjacency matrix" << endl;
        cout << "3. Display adjacency list" << endl;
        cout << "4. Depth-first search" << endl;
        cout << "5. Breadth-first search" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                int u, v;
                do {
                    cout << "Enter the vertices of the edge (0 to n-1): ";
                    cin >> u >> v;
                    if (u > nVertices) {
                        nVertices = u;
                    }
                    if (v > nVertices) {
                        nVertices=v;
                    }    
                    addEdgeToAdjMatrix(u, v);
                    addEdgeToAdjList(u, v);
                    cout << "Edge added successfully." << endl;
                    cout << "Do you want to add more edges? (y/n) ";
                    cin >> addMore;
                } while (addMore == 'y');
                break;
            case 2:
                displayAdjMatrix();
                break;
            case 3:
                displayAdjList();
                break;
            case 4:
                int startVertex;
                cout << "Enter the starting vertex for DFS: ";
                cin >> startVertex;
                cout << "DFS traversal: ";
                dfs(startVertex);
                cout << endl;

                break;
            case 5:
                cout << "Enter the starting vertex for BFS: ";
                cin >> startVertex;
                cout << "BFS traversal: ";
                bfs(startVertex, visited);
                cout << endl;
                break;
            case 6:
                cout << "Exiting..." << endl;
                exit(0);
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}

