#include <bits/stdc++.h>

using namespace std;


vector <vector <int> > G;
vector <pair <int,pair <int, int>>> X;

int const N=100005;
int state [N],state1[N],dfs_num[N],comp[N];
 int dfsCounter = 1;
stack <int> ostack;
stack <int> rstack;

/* written by A'laa Aierout */

void Init(vector<vector<int>>& graph){
    /* int dfsCounter = 1; */
    for(int i=0; i<graph.size(); i++){
        state[i] = 0;
        dfs_num[i] = -1;
        comp[i] = -1;
    }

    while(!ostack.empty()){
        ostack.pop();
    }

    while(!rstack.empty()){
        rstack.pop();
    }
}

/* Written by Razan Naddaf & Taj Ismaeel */

void dfs_Gabow(int z)
{
    state[z] = 1;
    dfs_num[z] = dfsCounter;
    dfsCounter++;
    ostack.push(z);
    rstack.push(z);
    for (int w : G[z])
    {
        if (state[w] == 0)
        {
            dfs_Gabow(w);
        }
        else if (state[w] == 1)
        {
            while (dfs_num[w] < dfs_num[rstack.top()])
            {
                rstack.pop();
            }
        }
    }
    state[z] = 2;
    if (z == rstack.top())
    {
        rstack.pop();
        while (true)
        {
            int w = ostack.top();
            ostack.pop();
            comp[w] = z;
            if (w == z)
            {
                break;
            }
        }
    }
}

/* written by Hussain Fateh */

void D_to_Un(vector<vector<int>>& d_g) {
    vector<vector<int>> und_g;

    und_g.resize(d_g.size());

    for (int i = 0; i < d_g.size(); i++) {
        for (int j = 0; j < d_g[i].size(); j++) {
            und_g[j].push_back(i);
        }
    }

    for (int i = 0; i < und_g.size(); i++) {
        for (int j = 0; j < und_g[i].size(); j++) {
            d_g[i].push_back(j);
        }
    }
}

/* Written by Joudy Shehada & Maged Hujira  */

void dfs_jens(vector<vector<int>> &vec, vector<pair<int,pair<int, int>>> &dfs_num_b) {
    int dfsnum=0;
    vector<int> state;
    for (size_t i = 0; i < vec.size(); i++) {
        for (size_t j = 0; j< i; j++){
            if (state[j] == 0){
                state[j] = 1;
                for (auto it = vec.begin(); it != vec.end(); it++) {
                    if (*it == vec[j+1]) { 
                    vec.erase(it);
                break;}}
            dfsnum += 1;} 
            else if (state[j] == 1) {
                dfs_num_b.push_back(pair<int,pair<int, int>>{make_pair(dfsnum,make_pair(j-1, j))});
                for (auto it = vec.begin(); it != vec.end(); it++) {
                if ( *it == vec[j-1]) {
                vec.erase(it);
         break;}}}
        dfs_jens(vec,dfs_num_b);
}}
}

/* Written by Farah Khadam & Karam Anstas */

void cycle(const vector<vector<int>>& G, vector<bool>& visited, int v, int& counter) {
    if (visited[v] ) {
        counter++;
        return;
    }
    visited[v] = true;

    for (int x : G[v]) {
        if (!visited[x]) {
            cycle(G, visited, x, counter);
        } else {
            counter++; 
            break;
        }
    }
}

int chain(const vector<vector<int>>& G, const vector<pair<int, pair<int, int>>>& V) {
    int size = G.size();
    vector<bool> visited(size, false); 
    int counter = 0;

    for (const auto& v : V) {
        if (!visited[v.second.first]) {
            cycle(G, visited, v.second.second, counter);
        }
    }
    return counter;
}

/* Written by Rawan Hnawi & Sara Alghawi */
int main()
{
    int n,m,x,y;
     bool ans=true,t=true;
    cin>>n>>m;
    for (int i=0; i<n; i++){
        cin>>x>>y;
        G[x].push_back(y);
        
    }
    stack <int> s;
    for(int i=0 ; i<G.size() ; i++){
        
        for (int j=0 ; j< G[i].size() ; j++){
                 s.push(j);
        }
           
            
        G[i].clear();
        
         ans=true;
         t=true;
        Init(G);
        for (int j=0 ; j< G.size() ; j++){
            if (state[j] == 0)
                dfs_Gabow(j);
        }
        int a=comp[0];
        for (int j=0; j<G.size();j++)
            if (comp[j]!=a){
                    t=false;
                    break;
            }
        
        if (t){
            int cnt=0;
            D_to_Un(G);
            dfs_jens(G,X);
            sort(X.begin(),X.end());
            cnt = chain(G,X);
            if (cnt >=2){
                t=false;
                break;
            }
        }
        /* G.push_back(i); */
        while (!s.empty()){
            G[i].push_back(s.top());
            s.pop();
            }

        if (!t) {
            ans=false;
            break;
        }
        
        
    }
    
    if (ans ) cout<<"YES";
    else cout<<"NO";
    
    return 0;
}