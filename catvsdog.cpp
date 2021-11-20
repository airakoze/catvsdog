#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <cstddef>
#include <cstring>

using namespace std;

struct Node{
	string like;
	string dislike;
	//int flow = 1
	};

vector<Node> catVect;
vector<Node> dogVect;

vector<vector<int>> gr(int v, int c, int d, vector<Node> catV, vector<Node> dogV) {

	vector<vector<int>> g(c, vector<int>(d, 0));
	vector<int> vec;
	for (int i = 0; i < c; i++){
		for (int j = 0; j < d; j++){//find which cats and dogs are connectable

			if ((catV[i].dislike == dogV[j].like) or (catV[i].like == dogV[j].dislike)){
				//vec.push_back(1);
				//g.push_back(vec);
				g[i][j] = 1;	
			}
			else{

				//vec.push_back(0);
				//g.push_back(vec);
				g[i][j] = 0;
			}		
		}
	}

	for (int i = 0; i < c; i++){
		for (int j = 0; j < d; j++){
			cout << g[i][j];
		}
		cout << endl;
	}

	return g;
}

int minVert(int v, int c, int d, vector<vector<int>> g){

	int connected[v] = {0}; 
	int catConn[v] = {0};

	for (int i = 0; i < c; i++){//for number of cats
		bool connected[c] = {false};

		for (int j = 0; j < d; j++){
			if((g[i][j] == 1) and (connected[i] == false)){//if graph is matchable and cat hasn't been con
				connected[i] = true;//connected
				if(catConn[j] == 0 ){//if there is another connection possible consider new connection
					catConn[j] = 1;
					return 1;

				}
			}		
	
		}

	}	                                              
                        	
    return 0;                                                                                                                                                                              
}


int maxFlow(int v, int c, int d, vector<vector<int>> g){	
	//maximum matching

	int max = 0;
	for (int i = 0; i < c; i++){
		int searched[d] = {0};
		if (minVert(v, c, d, g) == 1){
			max++;

		}

	}               
	return max;                                                                                                         
}


int main() {

	int n, c, d, v;
	vector<vector<int>> graph;

	string in1, in2;
	cin >> n;

	vector<Node> catVect;//cat and dog vect to compare in bipartite graph and find which viewers match
	vector<Node> dogVect;

	for (int i = 0; i < n; i++) {
		cin >> c >> d >> v;
	
		for (int j = 0; j < v; j++) {
			cin >> in1 >> in2;

			if (in1.at(0) == 'C'){
				//printf("cat-lover\n");
				Node cat;
		
				cat.like = in1;
				cat.dislike = in2;
				catVect.push_back(cat);
			}
			else{
				//printf("dog-lover\n");
				Node dog;

				dog.like = in1;
				dog.dislike = in2;
				dogVect.push_back(dog);
			}

		}

		int catSize = catVect.size();
		int dogSize = dogVect.size();

		graph = gr(v, c, d, catVect, dogVect);

		int ans = maxFlow(v, c, d, graph);	
		cout << ans << endl;

	
		//catVect.clear();
		//dogVect.clear();
	}

	return 0;
}
