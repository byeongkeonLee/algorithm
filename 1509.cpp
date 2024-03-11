#include <stdio.h>
#include <string.h>

bool palindrome[2501][2501];
int ans[2501];
int main(){
    char str[2501];
    int len = 0;
    scanf("%s", str);
    len = strlen(str);

    for (int i = 0; i < len; i++) {
        palindrome[i][i] = true;
        ans[i] = 2501;
    }

    for (int j = 1; j < len; j++) {
        for (int i = 0; i < j; i++) {
            bool match = str[i] == str[j];
            if (!match) 
                continue;
            palindrome[i][j] = j - i == 1 ? true : palindrome[i+1][j-1];
        }
    }

    for (int j = 0; j < len; j++) {
        for (int i = 0; i <= j; i++) {
            if (!palindrome[i][j])
                continue;
            if (i == 0) {
                ans[j] = 1;
            } else if (ans[j] > ans[i-1] + 1) {
                ans[j] = ans[i-1] + 1;
            }
        }
    }

    printf("%d\n", ans[len-1]);
    return 0;
}
