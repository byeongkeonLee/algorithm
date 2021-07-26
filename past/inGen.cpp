#include <cstdio>
int main() {
    std::puts("1");
    for (int i = 0; i < 1; ++i) {
        std::printf("10000 50000\n");
        for (int j = 1; j <= 10000; ++j) std::printf("50000 50000\n");
        for (int j = 1; j <= 50000; ++j) std::printf("40000 50000 40000 50000\n");
    }
    return 0;
}

