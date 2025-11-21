#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
#include <iomanip>
#include <algorithm>

using namespace std;

const int INF = INT_MAX;
const int NUM_VERTICES = 10;

int charToIdx(char c) {
    return c - 'a';
}

char idxToChar(int i) {
    return (char)('a' + i);
}

struct IterationState {
    int iterationNum;
    string activeVertex;
    vector<int> distances;
};

int main() {
    // 1. Initialize Adjacency Matrix with Infinity
    int adjMatrix[NUM_VERTICES][NUM_VERTICES];
    for (int i = 0; i < NUM_VERTICES; i++) {
        for (int j = 0; j < NUM_VERTICES; j++) {
            adjMatrix[i][j] = INF;
        }
    }

    // 2. Read inputs from text file
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open input.txt" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        if (line.empty()) continue;
        
        replace(line.begin(), line.end(), ',', ' ');
        
        stringstream ss(line);
        char uVal, vVal;
        int weight;
        
        if (ss >> uVal >> vVal >> weight) {
            int u = charToIdx(uVal);
            int v = charToIdx(vVal);
            adjMatrix[u][v] = weight; 
        }
    }
    inputFile.close();

    // 3. Show the adjacent matrix 
    cout << "--- Adjacency Matrix ---" << endl;
    cout << "  ";
    for(int i=0; i<NUM_VERTICES; ++i) cout << idxToChar(i) << " ";
    cout << endl;
    
    for (int i = 0; i < NUM_VERTICES; i++) {
        cout << idxToChar(i) << " ";
        for (int j = 0; j < NUM_VERTICES; j++) {
            if (adjMatrix[i][j] == INF)
                cout << "-1 ";
            else
                cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // 4. Build Dijkstra Algorithm
    int startNode = charToIdx('d');
    vector<int> dist(NUM_VERTICES, INF);
    vector<bool> visited(NUM_VERTICES, false);
    dist[startNode] = 0;

    vector<IterationState> history;
    
    IterationState initState;
    initState.iterationNum = 0;
    initState.activeVertex = "";
    initState.distances = dist;
    history.push_back(initState);

    for (int count = 0; count < NUM_VERTICES; count++) {
        int min = INF;
        int u = -1;

        for (int v = 0; v < NUM_VERTICES; v++) {
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }
        }

        if (u == -1 || dist[u] == INF) break;

        visited[u] = true;

        for (int v = 0; v < NUM_VERTICES; v++) {
            if (!visited[v] && adjMatrix[u][v] != INF && 
                dist[u] != INF && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
            }
        }

        IterationState currentState;
        currentState.iterationNum = count + 1;
        string active(1, idxToChar(u));
        currentState.activeVertex = active;
        currentState.distances = dist;
        history.push_back(currentState);
    }
    
    cout << "--- Dijkstra Execution Table ---" << endl;

    cout << setw(15) << "iteration: " << setw(6) << "init";
    for (size_t i = 1; i < history.size(); i++) {
        cout << setw(6) << i;
    }
    cout << endl;

    cout << setw(15) << "active vertex: " << setw(6) << " ";
    for (size_t i = 1; i < history.size(); i++) {
        cout << setw(6) << history[i].activeVertex;
    }
    cout << endl;
    
    cout << string(15 + (history.size() * 6), '-') << endl;

    for (int v = 0; v < NUM_VERTICES; v++) {
        cout << setw(13) << idxToChar(v) << " |";
        
        for (size_t i = 0; i < history.size(); i++) {
            int d = history[i].distances[v];
            if (d == INF) {
                cout << setw(6) << "-1";
            } else {
                cout << setw(6) << d;
            }
        }
        cout << endl;
    }

    return 0;
}