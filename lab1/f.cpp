#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cassert>

using namespace std;

struct Vector {
    int *arr = (int *) malloc(sizeof(int) * 1);
    int size = 1;
    int top = 0;

    void push(int x) {
        if (top == size) {
            int *temp = (int *) malloc(sizeof(int) * size);
            memcpy(temp, arr, sizeof(int) * size);
            free(arr);
            arr = (int *) malloc(sizeof(int) * size * 2);
            memcpy(arr, temp, sizeof(int) * size);
            free(temp);
            size *= 2;
        }
        arr[top] = x;
        top++;
    }

    int pop() {
        assert(top != 0);
        top--;
        int ans = arr[top];
        if (size > 1 && top == size / 2) {
            int *temp = (int *) malloc(sizeof(int) * size / 2);
            memcpy(temp, arr, sizeof(int) * size / 2);
            free(arr);
            arr = (int *) malloc(sizeof(int) * size / 2);
            memcpy(arr, temp, sizeof(int) * size / 2);
            free(temp);
            size /= 2;
        }
        return ans;
    }
};

int main() {
    char s[2000];
    Vector a;
    while (scanf("%s", s) != EOF) {
        if (s[0] == '+') {
            assert(a.top >= 2);
            int x = a.pop() + a.pop();
            a.push(x);
        } else {
            if (s[0] == '*') {
                assert(a.top >= 2);
                int x = a.pop() * a.pop();
                a.push(x);
            } else {
                if (s[0] == '-') {
                    assert(a.top >= 2);
                    int x = (a.pop() - a.pop());
                    x = -x;
                    a.push(x);
                } else {
                    int x = atoi(s);
                    a.push(x);
                }
            }
        }
    }
    printf("%d", a.pop());
}
