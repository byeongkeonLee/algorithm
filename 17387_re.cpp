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

    bool cross_check(const Line& other) {
        int abc = ccw(a, b, other.a);
        int abd = ccw(a, b, other.b);
        int acd = ccw(a, other.a, other.b);
        int bcd = ccw(b, other.a, other.b);

        int ab_view = abc * abd;
        int cd_view = acd * bcd;
        bool det = false;
        if (ab_view <= 0 && cd_view <= 0) {
            if (ab_view == 0 && cd_view == 0) {
                return straight_check(a, b, other.a, other.b);
            } else {
                return true;
            }
        }else {
            return false;
        }
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


int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    Line l1(a, b, c, d);
    scanf("%d %d %d %d", &a, &b, &c, &d);
    Line l2(a, b, c, d);
    printf("%d\n", l1.cross_check(l2)? 1 : 0);
    return 0;
}