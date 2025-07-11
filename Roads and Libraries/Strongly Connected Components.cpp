#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

void dfs(int v, vector<vector<int>> const& adj, vector<int> &output,vector<bool> &visited) {
    visited[v] = true;
   
    for (auto u : adj[v])
        {if (!visited[u])
            dfs(u, adj, output,visited);}
    output.push_back(v);
}
long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {
    vector<vector<int>> adj(n+1);
    vector<vector<int>>components;
    vector<vector<int>> adj_cond;
    vector<int> order;
    vector<bool> visited;
    visited.assign(n+1, false);
    long total_cost=0;
    
    for(auto& road:cities){
       adj[road[0]].push_back(road[1]);
       adj[road[1]].push_back(road[0]);
    
    }
    for (int v = 1; v <= n; v++)
        {if (!visited[v])
            dfs(v, adj, order,visited);}
    
    visited.assign(n+1, false);
    
    reverse(order.begin(), order.end());
    vector<int> roots(n+1, 0);
    for (auto v : order){
        if (v && !visited[v]) {
            std::vector<int> component;
            dfs(v, adj, component,visited);
            components.push_back(component);
            int root = *min_element(begin(component), end(component));
            
            for (auto u : component)
                roots[u] = root;
        }}
    adj_cond.assign(n+1, {});
    for (int v = 1; v <= n; v++)
        for (auto u : adj[v])
            if (roots[v] != roots[u])
                adj_cond[roots[v]].push_back(roots[u]);
    
   
    //cout << "SCCs:" << endl;
    
for (auto& comp : components) {
    int m=comp.size();
    if(c_lib<c_road)
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
