#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cassert>

using namespace std;

struct Vector {
    char *arr = (char *) malloc(sizeof(char) * 1);
    int size = 1;
    int top = 0;

    void push(char x) {
        if (top == size) {
            char *temp = (char *) malloc(sizeof(char) * size);
            memcpy(temp, arr, sizeof(char) * size);
            free(arr);
            arr = (char *) malloc(sizeof(char) * size * 2);
            memcpy(arr, temp, sizeof(char) * size);
            free(temp);
            size *= 2;
        }
        arr[top] = x;
        top++;
    }

    char pop() {
        assert(top != 0);
        top--;
        char ans = arr[top];
        if (size > 1 && top == size / 2) {
            char *temp = (char *) malloc(sizeof(char) * size / 2);
            memcpy(temp, arr, sizeof(char) * size / 2);
            free(arr);
            arr = (char *) malloc(sizeof(char) * size / 2);
            memcpy(arr, temp, sizeof(char) * size / 2);
            free(temp);
            size /= 2;
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    string s;
    while (getline(cin, s)) {
        Vector a;
        if (s == "") {
            cout << "YES\n";
            continue;
        }
        bool p = true;
        for (size_t i = 0; i < s.size(); i++) {
            if (s[i] == '(' || s[i] == '[') {
                a.push(s[i]);
            } else {
                if (a.top == 0) {
                    cout << "NO\n";
                    p = false;
                    break;
                }
                char c = a.pop();
                if ((s[i] == ']' && c == '(') || (s[i] == ')' && c == '[')) {
                    cout << "NO\n";
                    p = false;
                    break;
                }
            }
        }
        if (!p) {
            continue;
        }
        if (a.top != 0) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
    }
}
