#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <assert.h>

using namespace std;

const int INF = INT_MAX;

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
        return ans;
    }

    int last() {
        if (top == 0) {
            return INF;
        }
        return arr[top - 1];
    }
};

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

struct Stack {
    Vector val;
    Vector minim;
    int size = 0;

    void push(int x) {
        if (size == 0) {
            val.push(x);
            minim.push(x);
            size++;
            return;
        }
        size++;
        val.push(x);
        minim.push(min(x, minim.last()));
    }

    int pop() {
        assert(size > 0);
        int ans = val.pop();
        minim.pop();
        size--;
        return ans;
    }

    int min_stack() {
        if (size == 0) {
            return INF;
        }
        return minim.last();
    }
};

struct Queue_min {
    Stack in;
    Stack out;

    void push(int x) {
        in.push(x);
    }

    void pop() {
        if (out.size == 0) {
            while (in.size) {
                int x = in.pop();
                out.push(x);
            }
        }
        out.pop();
    }

    int calc_min() {
        return min(in.min_stack(), out.min_stack());
    }
};

int f(int y) {
    return y;
}

int main() {
    Queue_min queueMin;
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    if (m == 1) {
        if (n == 1) {
            int x;
            scanf("%d", &x);
            printf("%d", x);
            return 0;
        }
        int x_1, x_2;
        scanf("%d%d", &x_2, &x_1);
        long long ans = 0;
        ans += 1LL * x_1 + 1LL * x_2;
        for (int i = 2; i < n; i++) {
            int x;
            if (i < k) {
                scanf("%d", &x);
            } else {
                x = f(a * x_2 + b * x_1 + c);
            }
            ans += 1LL * x;
            x_2 = x_1;
            x_1 = x;
        }
        printf("%I64d", ans);
        return 0;
    }
    int x_1, x_2;
    scanf("%d%d", &x_2, &x_1);
    long long ans = 0;
    queueMin.push(x_2);
    queueMin.push(x_1);
    for (int i = 2; i < n; i++) {
        int x;
        if (i < k) {
            scanf("%d", &x);
        } else {
            x = f(a * x_2 + b * x_1 + c);
        }
        if (i >= m) {
            ans += 1LL * queueMin.calc_min();
            queueMin.pop();
        }
        queueMin.push(x);
        x_2 = x_1;
        x_1 = x;
    }
    ans += 1LL * queueMin.calc_min();
    printf("%I64d", ans);
}
