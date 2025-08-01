#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);



int find_set(int v,vector<int>& parent) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v],parent); 
    /*
    This line makes the paths for all those nodes shorter, 
    by setting the parent of each visited vertex directly to root node.
    This process first finds the representative of the set 
    (root vertex), and then in the process of stack unwinding,
    the visited nodes are attached directly to the representative.
    */
    }

void union_sets(int a, int b,vector<int>& parent,vector<int>& size) {
    a = find_set(a,parent);
    b = find_set(b,parent);
    if (a != b) {
        if (size[a] < size[b])
            swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        size[b]=0; //since component b's all elements are merged/connected to a, so we set size of the previous b's component to zero
    }
}

vector<int> disjoint_sets(int n, int c_lib, int c_road, vector<vector<int>> cities){
    vector<int> parent(n+1);
    iota(parent.begin(), parent.end(), 0);
    /* This function does the same task as the following loop. 
    for(int i=0;i<=n;i++) parent[i]=i;
    This iota function takes a value (here zero=0),
    and increments this value from parent.begin() and finishes before
    parent.end() function. */
    
    
    
    vector<int> size(n+1,1); size[0]=0;//the zero index don't mean anything. So we have set it to zero.
    /*
    This code is for disjoin sets union by size. So we take a vector 
    named size and initialize its initial value as 1.
    We can use rank in stead of size, if we want to use 
     union by rank in stead of union by size.
    Just declare any vector/list namely rank and initialize it 
    by assigning it any random value like 0,1 as initial rank value
    */
    
    for(auto& road:cities){
        union_sets(road[0], road[1], parent, size);
    }
  
    return size ;
}


long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {
     long total_cost=0;
    vector<int>components=disjoint_sets(n, c_lib, c_road,cities);
    
//Now calculating the minimal cost for our problem   
for (auto& comp : components) {
    int m=comp;if(!m) continue;
    
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
