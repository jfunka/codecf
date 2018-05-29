#include <bits/stdc++.h>

#define SE second
#define FI first
#define PB push_back
#define ALL(x) (x).begin(),(x).end()
#define SIZE(x) ((int) (x).size())

#define _ << " " <<
#define TR(x) cout << #x _ x << endl

using namespace std;

typedef pair<int, int> iint;
typedef long long LL;

const int N = 200001;

int n, k, l;
int a[N];

bool read() {
    if (!(cin >> n >> k >> l)) {
        return false;
    }

    memset(a, 0, sizeof a);

    for (int i = 0; i < n*k; i++) {
        cin >> a[i];
    }

    return true;
}

/*
 * n barrels
 * k size
 * l diff vi vj
 *
 * n=3,k=3,l=3
 * 123 456 789
 *  1   4   7 </= l ( 7-1=6 )
 * 147 258 369
 *  1   2   3  <= l ( ans=6 )
 * 123456789,l=3
 *     *
 * 125 367 489
 *  1   3   4  <= l ( ans=8 )
 *
 * n->4,3,min(2-1), idk about m...n because ik it's divisible
 * --------------------------
 *  112|333
 *      *
 *  m<n:0
 *  ans = am-1 + am-2 + min(am-i..a0)
 * --------------------------
 * 4 U (any ai higher than l)
 * 3 U (any ai higher than l)
 * 2 U (any ai higher than l)
 * 1 U (any ai higher than l)
 * --------------------------
 * take n lowest, match them with highest
 * */
void solve() {
    sort(a, a + n*k);

    LL ans = 0;
    int m = -1;
    for (int i = 1; i < n*k; i++) {
        if (a[i] > a[0]+l) {
            m = i; break;
        }
    }
    // if n=1 vol=min(a)
    if (m != -1 && (n > 1) && (n*k - m + 1 > m)) {
        ans = 0;
    } else if (m == -1) {
        for (int i = 0; i < n*k; i+=k) {
            ans += a[i];
        }
    } else {
        // 1 4 1 , 1 2 3 4
        // 4 1 1 , 1 2 3 4
        for (int i = m,j=k-1; i < n*k; i++,j++) {
            TR(m-j _ a[m-j]);
            ans += a[m-j];
        }
        for (int i = 0; i <= m-(n*k-m+1); i+=k) {
            ans += a[i];
        }
    }

    TR(m _ ans);
}

int main() {
    while (read()) {
        solve();
    }

    return 0;
}
