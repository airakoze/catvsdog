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

struct Node{
	string like;
	string dislike;
	//int flow = 1
	};

vector<Node> catVect;
vector<Node> dogVect;
vector<Node> vList;

vector<vector<int>> gr(int v, int c, int d, vector<Node> catV, vector<Node> dogV) {

	vector<vector<int>> g(c, vector<int>(d, 0));
	vector<int> vec;
	for (int i = 0; i < c; i++){
		for (int j = 0; j < d; j++){//find which cats and dogs are connectable

			if ((catV[i].dislike == dogV[j].like) or (catV[i].like == dogV[j].dislike)){
				g[i][j] = 1;	
			}
			else{

				g[i][j] = 0;
			}		
		}
	}
	return g;
}

bool mtc(vector<vector<int>> graph, int u, bool pass[], int mt[], int v, int c, int d){
                                      	
    for (int i = 0; i < c; i++)
    {
        if (graph[u][i] && !pass[i])
        {
            pass[i] = true;
            if (mt[i] < 0 || mtc(graph, mt[i], pass, mt, v, c, d))
            {
                mt[i] = u;
                return true;
            }
        }
    }
    return false;

}


int mx(vector<vector<int>> graph, int v, int s, int t, int c, int d){

	int mt[v];
	//int mt[c];
	memset(mt, -1, sizeof(mt));
                         
    int result = 0;
    for (int u = 0; u < c; u++)
    {
    	bool pass[v];
    	memset(pass, 0, sizeof(pass));
                                  
    	if (mtc(graph, u, pass, mt, v, c, d)){                                               
			result++;
			//cout << u << endl;	
		}
		else{
			//cout << "outside: " << u << endl;
		}
	}

	string first;
	for (int i = 0; i < v; i++){
		if(mt[i] < 0){
			first = vList[i].like;
			cerr << "Keeping " << first << endl;
			break;
		}
	}
	for(int i = 0; i < v; i++){
		if((mt[i] < 0)){
			cerr <<"Happy Person: +"<< vList[i].like << ", -" << vList[i].dislike << endl;
		}
	}
                                           
    return result;  
}


int main() {
	
	int n, c, d, v;
	vector<vector<int>> graph;

	string in1, in2;
	cin >> n;

//	vector<Node> catVect;//cat and dog vect to compare in bipartite graph and find which viewers match
//	vector<Node> dogVect;

	for (int i = 0; i < n; i++) {
		cin >> c >> d >> v;
	
		for (int j = 0; j < v; j++) {
			cin >> in1 >> in2;

			if (in1.at(0) == 'C'){
				
				Node cat;
		
				cat.like = in1;
				cat.dislike = in2;
				catVect.push_back(cat);
				vList.push_back(cat);
			}
			else{
				Node dog;

				dog.like = in1;
				dog.dislike = in2;
				dogVect.push_back(dog);
				vList.push_back(dog);
			}
		}

		int catSize = catVect.size();
		int dogSize = dogVect.size();
		int s = 0;
	
		graph = gr(v, catSize, dogSize, catVect, dogVect);
		//cout << "new: "<< v - bipartite(graph, catSize, dogSize)-1 << endl;

		int ans1 = mx(graph, v, s, catSize, c, d);
		//int ans1 = mx(graph, v, s, dogSize, catSize, dogSize);
	
		cout << v - ans1 << endl;
	
		catVect.clear();
		dogVect.clear();
	}

	return 0;
}
