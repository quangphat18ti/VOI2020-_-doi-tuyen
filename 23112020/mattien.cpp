/// Tóm tắt : Cho n lô đất. Mỗi lô đất có độ cao lớn nhất là h[i].
/// Mỗi ngôi nhà được xây tối đa trên t lô liên tiếp.
/// Tìm tổng diện tích xây nhà lớn nhất. Biết số lượng nhà xây tối đa là k.

/// Giới hạn : n <= 500

/// Nhận xét :
/// Ta thấy giới hạn n khá nhỏ.
/// Nên ta có thể nghĩ tới việc xây dựng f[i][j] là với i lô đất đầu tiên xây j ngôi nhà.

#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define db double
#define pb push_back
#define INC( i , a , b ) for(int i = int(a) ; i <= int(b) ; i++)
#define For( i , a , b ) for(int i = int(a) ; i <= int(b) ; i++)
#define DEC( i , a , b ) for(int i = int(a) ; i >= int(b) ; i--)
#define FOr( i , a , b ) for(int i = int(a) ; i >= int(b) ; i--)
#define fi first
#define se second
#define mp make_pair
#define LT "mattien"
#define maxn 505
#define sz(A) int( A.size() )

typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

int i , j , n , m , k;
int t;
int h[maxn];
int f[maxn][maxn] , vc = 1e9;

void nhap()
{
    cin >> n >> k >> t;
    For( i , 1 , n ) cin >> h[i];
}

void xuli()
{
    int ans = -vc;

    For( j , 1 , k )
    {
        For( i , 1 , n )
        {
            f[i][j] = max( f[i - 1][j] , f[i][j - 1] );
            int minn = vc;
            FOr( ires , i , 1 )
            {
                minn = min( minn , h[ires] );
                f[i][j] = max( f[i][j] , f[ires - 1][j - 1] + minn * (i - ires + 1) );
            }

            ans = max( ans , f[i][j] );
        }
    }

    cout << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen(LT".inp","r",stdin);
    freopen(LT".out","w",stdout);
    nhap();
    xuli();
}
