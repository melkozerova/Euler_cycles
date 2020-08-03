#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void dfs (int n, int V, const vector<vector<int>> & G, vector<bool> & used) {
	used[n] = true;
	for (int i = 0; i < V; i++)
		if((G[n][i] != 0) && (used[i] == 0))
			dfs (i, V, G, used);
}
 
bool simply_connected_graph(int V, const vector<vector<int>> & G) {
    int count = 0;
	vector <bool> used (V, 0);
	
	for (int i = 0; i < V; i++)
		if (! used[i]) {
			dfs (i, V, G, used);
			count++;
		}
    
    return (count == 1) ? true : false;
}

bool euler_criterion(int V, const vector<vector<int>> & G) {
    if (V == 1)
        return true;
    
    vector<int> deg (V, 0);
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			deg[i] += G[i][j];
	
	for (int i = 0; i < V; i++)
	    if (deg[i] % 2 == 1)
	        return false;
	
	return true;        
}

void find_euler_path(int n, int V, vector<vector<int>> & G, vector<int> & path) {
    if (V == 1) {
        path.push_back(0);
        return;
    }
    
	vector<int> deg (V, 0);
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			deg[i] += G[i][j];
	
	stack <int> st;
	st.push(n);
	while (!st.empty()) {
	    n = st.top();
        if (deg[n] != 0) {
            for (int j = 0; j < V; j++)
                if (G[n][j] != 0) {
                    st.push(j);
                    --G[n][j]; --G[j][n];
                    --deg[n]; --deg[j];
                    
                    /*if (simply_connected_graph(V, G))
                        cout << n << " - " << j << ' ' << "oksel" << '\n';
                    else
                        cout << n << " - " << j << ' ' << "po popke" << '\n';*/
                    break;
                }
	    }
	    else {
	        st.pop();
	        path.push_back(n);
	    }
	}
}

int main() {

	int V, E;
	cin >> V >> E;
	vector <vector<int>> G (V, vector<int> (V, 0));
    
	for (int  i = 0; i < E; i++) {
	    int a, b;
	    cin >> a >> b;
	    G[a - 1][b - 1] = G[b - 1][a - 1] += 1;
	} 
    
    if (!simply_connected_graph(V, G) || !euler_criterion(V, G)) {
        cout << "NONE";
        return 0;
    }    
    
    vector <int> path;
	find_euler_path(0, V, G, path);
	for (int i = 0; i < path.size() - 1; i ++)
	    cout << path[i] + 1 << ' ';

}
