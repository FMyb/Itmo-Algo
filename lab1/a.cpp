#include <iostream>
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
    int n;
    ios_base::sync_with_stdio(false);
    cin >> n;
    Vector a;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == '-') {
            cout << a.pop() << '\n';
        } else {
            int x;
            cin >> x;
            a.push(x);
        }
    }
}
