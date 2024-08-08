
import java.util.*;

class TestClass {
    static class pair{
        int u,dist;
        pair(int u,int dist){
            this.u=u;
            this.dist=dist;
        }
    }
    private static void bfs( List<Integer>[] graph,int[] vis,int [] dist,int src){
        LinkedList<pair>q=new LinkedList<>();
        q.addLast(new pair(src,0));
        while(q.size()>0){
            pair rem=q.removeFirst();
            if(vis[rem.u]==1) continue;
            vis[rem.u]=1;
            dist[rem.u]=rem.dist;
            for(Integer nbr:graph[rem.u]){
                if(vis[nbr]==0){
                    q.addLast(new pair(nbr,rem.dist+1));
                }
            }
        }

    }
    public static void main(String args[] ) throws Exception {
        Scanner sc=new Scanner(System.in);
        int n=sc.nextInt();
        int m=sc.nextInt();
        List<Integer>[] graph=new ArrayList[n+1];
        for(int i=1;i<n+1;i++){
            graph[i]=new ArrayList<>();
        }
        for(int i=0;i<m;i++){
            int u=sc.nextInt();
            int v=sc.nextInt();
            graph[u].add(v);
            graph[v].add(u);
        }
        int src=sc.nextInt();
        int[] vis=new int[n+1];
        int[] dist=new int[n+1];
        bfs(graph,vis,dist,src);
        for(int i=1;i<n+1;i++){
            System.out.print(dist[i]+" ");
        }

    }
}
