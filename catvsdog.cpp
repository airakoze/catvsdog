// Group Members: Esuga Yacim, Andy Florian Irakoze 

#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <cstddef>
#include <cstring>
#include <climits>
#include <queue>

using namespace std;

// struct to easily store likes and dislikes votes of viewers
struct Viewer {
    string viewerLike;
    string viewerDislike;
};

// Function to generate a graph from user's input
// Graph is going to be used while the Ford-Fulkerson Algorithm is running
vector< vector<int> > generateGraph(int totalVertices, int numberCatLovers, int numberDogLovers, vector<Viewer> catLoversVector, vector<Viewer> dogLoversVector) {
	
    vector< vector<int> > graph(totalVertices, vector<int>(totalVertices, 0));
	
    for (int i = 0; i < totalVertices; i++) 
		for (int j = 0; j < totalVertices; j++){
			// Connecting source vertex to cat lovers vertices
            if ((j > 0 && j <= numberCatLovers) && i == 0) graph[i][j] = 1;

            // Connecting dog lovers vertices to sink vertex
            if ((i > numberCatLovers && i < (totalVertices - 1)) && j == (totalVertices - 1)) graph[i][j] = 1;
            
            // Connecting conflicting viewers
            if (i > 0 && i <= numberCatLovers && (j > numberCatLovers && j < (totalVertices - 1))) 
                if ((catLoversVector[i - 1].viewerDislike == dogLoversVector[j - numberCatLovers - 1].viewerLike) || (catLoversVector[i - 1].viewerLike == dogLoversVector[j - numberCatLovers - 1].viewerDislike))
                    graph[i][j] = 1;
		}
    
	return graph;
}

// Function to check if there exists any path that can be augmented
// To be called when the Ford-Fulkerson Algorithm is running
bool augmentPathExist(vector< vector<int> > residualGraph, int sourceIndex, int sinkIndex, int parent[], int totalVertices) {
    bool visitedArray[totalVertices];
    memset(visitedArray, 0, totalVertices); // Initializing visited array to 0

    // Queue to manage the vertices that are going to used
    queue<int> q;
    q.push(sourceIndex);
    visitedArray[sourceIndex] = true;
    parent[sourceIndex] = -1;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
 
        for (int i = 0; i < totalVertices; i++) {
            if (visitedArray[i] == false && residualGraph[u][i] > 0) {
                if (i == sinkIndex) {
                    parent[i] = u;
                    return true;
                }
                q.push(i);
                parent[i] = u;
                visitedArray[i] = true;
            }
        }
    }
    return false;
}

// Function to get the max flow using the Ford-Fulkerson Algorithm 
// Traces the viewers that were kept on the show and the happy viewers as well
int getMaxFlow(vector< vector<int> > graph, int sourceIndex, int sinkIndex, int totalVertices, vector<Viewer> verticesList) {
    
    vector< vector<int> > residualGraph = graph; // Initializing the residual graph to be used in Ford-Fulkerson Algorithm 
 
    int parent[totalVertices]; 
 
    int maxFlow = 0; 

    while (augmentPathExist(residualGraph, sourceIndex, sinkIndex, parent, totalVertices)) {
        int pathFlow = INT_MAX;

        for (int i = sinkIndex; i != sourceIndex; i = parent[i]) 
            pathFlow = min(pathFlow, residualGraph[parent[i]][i]);

        for (int j = sinkIndex; j != sourceIndex; j = parent[j]) {
            residualGraph[parent[j]][j] -= pathFlow;
            residualGraph[j][parent[j]] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {

    int numberLines, numberCats, numberDogs, numberViewers, totalVertices;
    string choice1, choice2;
    vector<Viewer> catLovers; // Vector containing cat lovers
    vector<Viewer> dogLovers; // Vector containing dog lovers
    vector<Viewer> verticesList; // Vector containing all vertices

    cin >> numberLines;

    for (int i = 0; i < numberLines; i++) {
        cin >> numberCats >> numberDogs >> numberViewers; // Getting user input for the number of cats, dogs, and viewers
        totalVertices = numberViewers + 2; // Total number of vertices with the source and sink vertices

        // Checking if the number of cats or dogs are between the correct boundary
        if (!(1 <= numberCats && numberCats <= 100) || !(1 <= numberDogs && numberDogs <= 100)) return 0;
        
        // Getting all viewers vote and storing them in corresponding vectors
        for (int j = 0; j < numberViewers; j++) {
            cin >> choice1 >> choice2;
            
            if (choice1.at(0) == 'C'){
                // In case the viewer is a cat lover
				Viewer catLover;
				catLover.viewerLike = choice1;
				catLover.viewerDislike = choice2;
				catLovers.push_back(catLover);
                verticesList.push_back(catLover);
			} else {
				Viewer dogLover;
				dogLover.viewerLike = choice1;
				dogLover.viewerDislike = choice2;
				dogLovers.push_back(dogLover);
                verticesList.push_back(dogLover);
			}
        }

        int numberCatLovers = catLovers.size();
		int numberDogLovers = dogLovers.size();
	
		vector< vector<int> > graph = generateGraph(totalVertices, numberCatLovers, numberDogLovers, catLovers, dogLovers);
		
        int sourceIndex = 0;
        int sinkIndex = (totalVertices - 1);
		int maxFlow = getMaxFlow(graph, sourceIndex, sinkIndex, totalVertices, verticesList); 
	
		cout << numberViewers - maxFlow << endl; 
	
		catLovers.clear();
		dogLovers.clear();
    }

    return 0;
}