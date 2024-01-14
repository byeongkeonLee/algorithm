#include<stdio.h>
#include<queue>
#include<vector>

using namespace std;

struct Node{
    unsigned int node;
    int weight;

    Node(unsigned int n, int w): node(n), weight(w){};

    bool operator<(const Node& n) const{
        return this->weight > n.weight;
    }
};


int main(){
    vector<Node> graph[10001];
    int v, e;
    scanf("%d %d",&v,&e);

    // Input
    for(int i = 0; i < e; i++){
        int a,b,c;
        scanf("%d %d %d", &a, &b, &c);
        graph[a].push_back(Node(b, c));
        graph[b].push_back(Node(a, c));
    }

    // PRIM
    priority_queue<Node> heap;
    bool visited[10001] = {0,};
    int ANS = 0;

    heap.push(Node(1, 0));
    while(!heap.empty()){
        unsigned int node = heap.top().node;
        int weight = heap.top().weight;
        heap.pop();

        if(visited[node]) continue;

        ANS += weight;
        visited[node] = true;
        for(auto next : graph[node]){
            if(!visited[next.node]){
                heap.push(Node(next.node, next.weight));
            }
        }
    }
    printf("%d\n",ANS);
}