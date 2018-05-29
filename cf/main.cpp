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
 * n=5,k=3
 * 0123456789
 * 112233445567899,l=3,n*k=15|15-8=7bad
 *         m
 * num_bad=5*3-8=7
 * M=7
 * for n=0
 *   ta=4
 *   if_0 {
 *     num_bad-=(2)=5,M=6
 *   }
 *   ANS=4
 * for n=1
 *   ta=4
 *   if_0 {
 *     num_bad-=(2)=3,M=5
 *   }
 *   ANS=4+4
 * for n=2
 *   ta=3
 *   if_0 {
 *     num_bad-=(2)=1,M=4
 *   }
 *   ANS=4+4+3
 * for n=3
 *   ta=3
 *   if_1 {
 *     j=3-1-1=1,M=3
 *     num_bad=0
 *     for i=3,i>=0&j>0;i--,j--,M-- {
 *       i=3,j=1:::ta=min(3,2)=2,M=2
 *     }
 *   }
 *   ANS=4+4+3+2
 * for n=4
 *   ta=2
 *   if_2 {
 *     M=1
 *     for i=1,kk=2;i>=0&kk>0,i--,kk--,M-- {
 *       i=1,kk=2,M=1:::ta=min(2,1)=1,i=0,kk=1,M=0
 *       i=0,kk=1,M=0:::ta=min(1,1)=1,i=-,kk=0,M=-
 *     }
 *   }
 *   ANS=4+4+3+2+1
 * END
 * 112 2 3 3 4 4
 *
 * 112 23x 3xx 4xx 4xx
 *
 * 112 235 356 478 499      
 *
 * for nn
 *
 * n->4,3,min(2-1), idk about m...n because ik it's divisible
 * --------------------------
 *  112|333
 *      *
 *  m<n:0
 *  ans = am-1 + am-2 + min(am-i..a0)
 *  or
 *  ans = min(am-1,am..am+k-1)+min(am-2,am+k..am+2*k-1)+...+
 * --------------------------
 * 4 U (any ai higher than l)
 * 3 U (any ai higher than l)
 * 2 U (any ai higher than l)
 * 1 U (any ai higher than l)
 * --------------------------
 * take n lowest, match them with highest
 *
 * CARE IF K=1
 * --------------------------
 * ptr = 0
 * ans = 0
 * n,k,l,m;
 * num_bad = n*k-m
 * M = m-1
 * for nn = 0 ... n {
 *   toadd = aM
 *   if ( num_bad >= k-1 ) {
 *     num_bad -= (k-1),M--
 *   } else if ( num_bad > 0 ) {
 *     j = k-num_bad-1,M--
 *     num_bad = 0
 *     for i=M;i>=0 and j>0;i--,j--,M-- {
 *       toadd = min(toadd,ai)
 *     }
 *   } else {
 *     M--;
 *     for i=M,kk=k-1;i>=0 and kk>0;i--,kk--,M-- {
 *       toadd = min(toadd,ai)
 *     }
 *   }
 *   ans += toadd
 * }
 * 1 2|2 2|2 2|3 3
 *       h x x x x
 *        
 * 3-2=2
 * 3-2=2
 * 2-2=2
 * 2-1=1
 *
 * 3-1=1
 * 3-2=2
 * 2-2=2
 * 2-2=2
 *
 * */
void solve() {
    sort(a, a + n*k);

    int m = -1;
    for (int i = 1; i < n*k; i++) {
        if (a[i] > a[0]+l) {
            m = i; break;
        }
    }

    if (m != -1 && m < n) {
        cout << 0 << endl;
        return;
    }

    if (m == -1) m = n*k;
    int num_bad = n*k-m;
    int M = m-1;
    LL ans = 0;
    for (int i = 0; i < n; i++) {
        int toadd = a[M];
        if (num_bad >= k-1) {
            num_bad -= (k-1), M--;
        } else if (num_bad > 0) {
            num_bad = 0, M--;
            for (int j = M, kk = k-num_bad-1; j >= 0 && kk > 0; j--, kk--, M--) {
                toadd = min(toadd, a[j]);
            }
        } else {
            M--;
            for (int j = M, kk = k-1; j >= 0 && kk > 0; j--, kk--, M--) {
                toadd = min(toadd, a[j]);
            }
        }
        ans += 1LL * toadd;
    }
    cout << ans << endl;
}

int main() {
    while (read()) {
        solve();
    }

    return 0;
}
