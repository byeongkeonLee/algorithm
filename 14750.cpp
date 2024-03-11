#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
class Pos;

int ccw(const Pos& a, const Pos& b, const Pos& c);
bool straight_check(const Pos& a, const Pos& b, const Pos& c, const Pos& d);

class Pos {
    public:
    int x, y;
    Pos(){};
    Pos(int x_, int y_): x(x_), y(y_){};
    bool operator <=(const Pos& other) const {
        if (x == other.x)
            return y <= other.y;
        return x <= other.x;
    }
};
class Line {
    public:
    Pos a, b;
    int mouse, hole;
    int cross_count;
    Line(int x1, int y1, int x2, int y2) {
        a = Pos(x1, y1);
        b = Pos(x2, y2);
        cross_count = 0;
    }

    Line(int x1, int y1, int x2, int y2, int m, int h) {
        a = Pos(x1, y1);
        b = Pos(x2, y2);
        cross_count = 0;
        mouse = m;
        hole = h;
    }

    void cross_check(const Line& other) {
        int abc = ccw(a, b, other.a);
        int abd = ccw(a, b, other.b);
        int acd = ccw(a, other.a, other.b);
        int bcd = ccw(b, other.a, other.b);

        int ab_view = abc * abd;
        int cd_view = acd * bcd;

        bool det = false;

        if (b.x == other.a.x && b.y == other.a.y || b.x == other.b.x && b.y == other.b.y)
            return;
        if (ab_view <= 0 && cd_view <= 0) {
            if (ab_view == 0 && cd_view == 0) {
                det = straight_check(a, b, other.a, other.b);
            } else {
                det = true;
            }
        }else {
            det = false;
        }
        if (det)
            cross_count += 1;
    }
};

bool straight_check(const Pos& a, const Pos& b, const Pos& c, const Pos& d) {
    const Pos& l1_min = a <= b ? a : b;
    const Pos& l2_min = c <= d ? c : d;
    const Pos& l1_max = a <= b ? b : a;
    const Pos& l2_max = c <= d ? d : c;

    return l1_min <= l2_max && l2_min <= l1_max;
}

int ccw(const Pos& a, const Pos& b, const Pos& c) {
    long value = (long) b.x * c.y + (long) a.x * b.y + (long) c.x * a.y \
                    - (long) a.x * c.y - (long) b.x * a.y - (long) c.x * b.y;
    if (value > 0) { 
        return 1;
    } else if (value == 0) {
        return 0;
    } else{
        return -1;
    }
}

int N, K, H, M;

#define MAX_MICE 250
#define MAX_HOLE 50
#define M_AND_H (MAX_MICE + MAX_HOLE)
#define START (M_AND_H + 1)
#define END (START + 1)
#define SIZE (END + 1)

vector<Line> house_lines;
vector<Line> mouse_hole_lines[MAX_MICE];
vector<Pos> holes, mice;

int flow[SIZE][SIZE];
vector<int> adj[SIZE];


void input_processing() {
    int a = 0, b = 0;
    scanf("%d %d %d %d", &N, &K, &H, &M);

    // input house corner
    for (int i=0; i<N; i++) {
        scanf("%d %d", &a, &b);
        house_lines.push_back(Line(a, b, 0, 0));
        if (i != 0) {
            house_lines[i-1].b = Pos(a, b);
        }
        if (i == N-1) {
            house_lines[i].b = house_lines[0].a;
        }
    }

    // input Holes
    for (int i=0; i< H; i++) {
        scanf("%d %d", &a ,&b);
        holes.push_back(Pos(a,b));
    }

    // input Mice
    for (int i=0; i< M; i++) {
        scanf("%d %d", &a ,&b);
        mice.push_back(Pos(a,b));
    }

    // connect Mouse-Hole
    for (int i=0; i< M; i++) {
        for (int j=0; j< H; j++) {
            mouse_hole_lines[i].push_back(Line(mice[i].x, mice[i].y, holes[j].x, holes[j].y, i, j));
        }
    }
}

void line_cross_check() {
    for(int i=0; i< M; i++){
        for(vector<Line>::iterator itr = mouse_hole_lines[i].begin(); itr != mouse_hole_lines[i].end(); itr++) {
            for(vector<Line>::iterator itr2 = house_lines.begin(); itr2 != house_lines.end(); itr2++) {
                itr->cross_check(*itr2);
            }
        }
    }
}

void build_graph() {
    for(int i=0; i< M; i++) {
        adj[START].push_back(i);
        adj[i].push_back(START);
        flow[START][i] = 1;

        for(vector<Line>::iterator itr = mouse_hole_lines[i].begin(); itr != mouse_hole_lines[i].end(); itr++) {
            if(itr->cross_count <= 1) {
                adj[i].push_back(M + itr->hole);
                adj[M + itr->hole].push_back(i);
                flow[i][M + itr->hole] = 1;
            }
        }
    }
    for(int j=0; j< H; j++) {
        adj[M + j].push_back(END);
        adj[END].push_back(M + j);
        flow[M + j][END] = K;
    }
}
int bfs(int start, int end) {
    queue<pair<int, int>> q;
    int cur = start;
    int parent[SIZE];
    bool path_exist = false;
    memset(parent, -1, SIZE * sizeof(int));
    
    q.push(make_pair(cur, -1));

    while(!q.empty()) {
        int cur = q.front().first;
        parent[cur] = q.front().second;
        q.pop();

        if(cur == end) {
            path_exist = true;
            break;
        }
        for (vector<int>::iterator itr = adj[cur].begin(); itr != adj[cur].end(); itr++) {
            if (parent[*itr] != -1 || flow[cur][*itr] == 0)
                continue;
            q.push(make_pair(*itr, cur));
        }
    }
    if (!path_exist)
        return 0;

    cur = end;
    while(cur != start) {
        flow[parent[cur]][cur] -= 1;
        flow[cur][parent[cur]] += 1;
        cur = parent[cur];
    }

    return 1;
}

int network_flow(int start, int end) {
    int final_flow = 0;
    while (bfs(start, end)) {
        final_flow++;
    }
    if (final_flow == M)
        return true;
    return false;
}

int main() {
    input_processing();
    line_cross_check();
    build_graph();
    bool ans = network_flow(START, END);
    printf("%s\n", ans? "Possible" : "Impossible");
    return 0;
}