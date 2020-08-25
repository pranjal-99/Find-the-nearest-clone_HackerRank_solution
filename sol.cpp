#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

int bfs(map<int,vector<int>> r,int check[1000001],vector<int> v,int d,int c,int val,vector<long int> ids) {
    for(int i=0;i<v.size();i++) {
        if(ids[v[i]-1]==val & check[v[i]]!=1){
            check[v[i]]=1;
            d=std::min(d,c+1);
            return d;
        } 
        if(check[v[i]]!=1) {
            check[v[i]]=1;
                
            return std::min(d,bfs(r,check,r[v[i]],d,c+1,val,ids));
        }
    }
    return 1e9;
}


int findShortest(int graph_nodes, vector<int> graph_from, vector<int> graph_to, vector<long> ids, int val) {
    int arr[1000001]={};
    int ind=0;
    for(int i=0;i<graph_nodes;i++) {
        if(ids[i]==val){
            arr[ind]=i+1;
            ind++;
        }
    }
    if(ind<=1)return -1;
    map<int,vector<int>> Map;
    for(int i=0;i<graph_from.size();i++) {
        Map[graph_from[i]].push_back(graph_to[i]);
        Map[graph_to[i]].push_back(graph_from[i]);
    }
    int ans=1e9;
    for(int i=0;i<ind;i++) {
        int c=0;
        int check[1000001]={};
        static int d=1e9;
        check[arr[i]]=1;
        c=bfs(Map,check,Map[arr[i]],d,c,val,ids);
        ans=std::min(ans,c);
    }
    return ans;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int graph_nodes;
    int graph_edges;

    cin >> graph_nodes >> graph_edges;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> graph_from(graph_edges);
    vector<int> graph_to(graph_edges);

    for (int i = 0; i < graph_edges; i++) {
        cin >> graph_from[i] >> graph_to[i];
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string ids_temp_temp;
    getline(cin, ids_temp_temp);

    vector<string> ids_temp = split_string(ids_temp_temp);

    vector<long> ids(graph_nodes);

    for (int i = 0; i < graph_nodes; i++) {
        long ids_item = stol(ids_temp[i]);

        ids[i] = ids_item;
    }

    int val;
    cin >> val;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int ans = findShortest(graph_nodes, graph_from, graph_to, ids, val);

    fout << ans << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
