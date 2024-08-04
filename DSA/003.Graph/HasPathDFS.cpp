  class Graph{
    private:
    vector<vector<int>>graph;
    bool dfs( vector<bool>&vis,int src,int dest){
        if(src==dest) return true;
        vis[src]=true;
        for(auto nbr:graph[src]){
            if(vis[nbr]==false){
                bool tres=dfs(vis,nbr,dest);
                if(tres==true) return true;
            }
        }
        return false;
    }
    public:
    Graph(int n, vector<vector<int>>& edges){
        for(int i=0;i<n;i++){
            vector<int>v;
            graph.push_back(v);
        }
        for(auto edge:edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);

        }
     }
     bool haspath(int src,int dest){
        if(src==dest) return true;
        vector<bool>vis(graph.size(),false);
        return dfs(vis,src,dest);
     }
        
    };

class Solution {
  

public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        Graph graph=Graph(n,edges);
        return graph.haspath(source,destination);
    }
};