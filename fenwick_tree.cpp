// fenwick tree or Binary Index Tree
// operation foc : removing the right  most set bit from the number and returning the number
// Steps to do foc
// 2's Complement
// & with original number
// subtract from original number
// range for each index(1 indexed) i = (1+foc(i),i)
// The range tells the sum of the numbers from left to right in the range

// 2's Complement
// & with original number
// add to original number
// Above three steps can be written in one equation as  i = i + (i & (-i))

#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> fen;

void update(int i, int add) {
    while(i <= n) {
        fen[i] += add;
        i += (i & -i);
    }
}

int sum(int i) {
    int s = 0;
    while(i > 0) {
        s += fen[i];
        i -= (i & -i);
    }
    return s;
}

int rangeSum(int l, int r) {
    return sum(r) - sum(l - 1);
}

int main() {
    cin >> n;
    fen.assign(n + 1, 0); // 1-indexed
    vector<int> arr(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> arr[i];
        update(i, arr[i]);
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++) {
        int a, b, c;
        cin >> a >> b >> c;  // Queries are also one based
        if(a == 0) update(b, c); // add c to index b 
        else cout << rangeSum(b, c) << endl;
    }
}
