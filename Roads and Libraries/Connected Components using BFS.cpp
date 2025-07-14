#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

void bfs(int node,vector<bool>& visited,vector<int>& component, vector<vector<int>>& adj){
    queue<int>q; 
    visited[node] = true ;
    q.push(node);
    while(!q.empty()){
        
        int vertex=q.front();
        
        q.pop();
        component.push_back(vertex);
        for(auto& adj_node:adj[vertex]){
            if(!visited[adj_node]){
                visited[adj_node] = true ;
                q.push(adj_node);
        }
    }
}}

vector<vector<int>> connected_components_using_bfs(int n, int c_lib, int c_road, vector<vector<int>> cities, vector<vector<int>>& adj){
    
    vector<bool> visited(n+1,false);
    vector<vector<int>> components;
    vector<int> component;
    for(int city=1;city<=n;city++){
        if(!visited[city]){
            component.clear();
            bfs(city,visited,component,adj);
            components.push_back(component);
            
        }
    }
     
    return components ;
}


long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {
     long total_cost=0;
     vector<vector<int>> adj(n+1);
      for(auto& road:cities){
        adj[road[0]].push_back(road[1]);
        adj[road[1]].push_back(road[0]);
     }
     
     vector<vector<int>> components=connected_components_using_bfs(n, c_lib, c_road,cities,adj);
     
    
//Now calculating the minimal cost for our problem   
for (auto& comp : components) {
    int m=comp.size();
    
    if(c_lib<=c_road)
    {
        total_cost+= (m*c_lib);
        continue;
    }
    total_cost+= ((m-1)*c_road+c_lib);
    
}  
return total_cost;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        int c_lib = stoi(first_multiple_input[2]);

        int c_road = stoi(first_multiple_input[3]);

        vector<vector<int>> cities(m);

        for (int i = 0; i < m; i++) {
            cities[i].resize(2);

            string cities_row_temp_temp;
            getline(cin, cities_row_temp_temp);

            vector<string> cities_row_temp = split(rtrim(cities_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int cities_row_item = stoi(cities_row_temp[j]);

                cities[i][j] = cities_row_item;
            }
        }

        long result = roadsAndLibraries(n, c_lib, c_road, cities);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
