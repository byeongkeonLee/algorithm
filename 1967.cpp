#include<stdio.h>
#include<vector>

using namespace std;

int n;

vector<pair<int, int>> tree[10001];

int ans = 0;

int dfs(int cur) {
    int child, child_val;
    int ret = 0;
    int first_child = 0;
    int second_child = 0;
    if (tree[cur].size() == 0) {
        return 0;
    }
    for(vector<pair<int, int>>::iterator iter = tree[cur].begin(); iter != tree[cur].end(); iter++) {
        child = iter->first;
        child_val = iter->second;
        ret = dfs(child) + child_val; 
        //printf("<%d %d>", child, child_val);
        if (first_child < ret) { 
            second_child = first_child;
            first_child = ret;
        } else if (second_child < ret) {
            second_child = ret;
        }
    }
    if (ans < first_child + second_child) { 
        ans = first_child + second_child;
    }
    //printf("[%d: First. %d, Second. %d, sum. %d]", cur, first_child, second_child, ans);
    return first_child;
}
int main() {
    int a, b, c;
    scanf("%d", &n);
    for (int i=0; i<n-1; i++) {
        scanf("%d %d %d", &a, &b, &c);
        tree[a].push_back(pair<int, int>(b, c));
    }
    dfs(1);
    printf("%d\n", ans);
}