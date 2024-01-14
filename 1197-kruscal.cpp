#include<stdio.h>
#include<vector>
#include<algorithm>

using namespace std;

int find_root(int parent[], int a){
    if(parent[a] == a){
        return a;
    }else{
        return parent[a] = find_root(parent, parent[a]);
    }
}

void make_union(int parent[], int a, int b){
    parent[b] = a;
}

bool cmp(int *a, int *b){
    return a[2] < b[2];
}

int main(){
    int v, e;
    scanf("%d %d",&v,&e);
    vector<int*> edges;

    // Input
    for(int i = 0; i < e; i++){
        int a,b,c;
        scanf("%d %d %d", &a, &b, &c);
        edges.push_back(new int[3]{a, b, c});
    }

    // KRUSKAL
    sort(edges.begin(), edges.end(), cmp);
    int parent[10001];
    int ANS = 0;

    for(int i=1 ; i < v+1; i++){
        parent[i] = i;
    }

    for(auto itr : edges){
        int a_root = find_root(parent, itr[0]);
        int b_root = find_root(parent, itr[1]);

        if(a_root != b_root){
            make_union(parent, a_root, b_root);
            ANS += itr[2];
        }
    }
    printf("%d\n", ANS);
}