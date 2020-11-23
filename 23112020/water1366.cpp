/// Tóm tắt: có 2 công ty cấp nước.
/// Công ty A cấp nước từ trái sang phải
/// Công ty B cấp nước từ trên xuống dưới
/// 2 công ty này không được nối đường ống giao nhau

/// Cho chi phí từng ô tính riêng theo từng công ty.
/// Hỏi chi phí nhỏ nhất

#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define db double
#define pb push_back
#define fi first
#define se second
#define For(i , a , b) for(int i = int(a) ; i <= int(b) ; i++)
#define FOr(i , a , b) for(int i = int(a) ; i >= int(b) ; i--)
#define LT "water"
#define maxn 1000005

#define a(i , j) a[(i - 1) * m + j]
#define b(i , j) b[(i - 1) * m + j]
#define f(i , j) f[(i - 1) * m + j]
#define h(i , j) h[(i - 1) * m + j]
#define c(i , j) c[(i - 1) * m + j]

typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vii;

int i , j , n , m , k;
int a[maxn] , b[maxn];
ll h[maxn] , c[maxn];
ll f[maxn] , vc = 1e16;

void nhap()
{
    cin >> n >> m;
    For( i , 1 , n ) For( j , 1 , m ) cin >> a(i , j);
    For( i , 1 , n ) For( j , 1 , m ) cin >> b(i , j);
}

void process()
{
    For( i , 1 , n )
    {
        For( j , 1 , m )
        {
            if( j == 1 ) h(i , j) = a(i , j);
            else h(i , j) = h(i , j - 1) + a(i , j);
        }
    }

    For( j , 1 , m )
    {
        For( i , 1 , n )
        {
            if( i == 1 ) c(i , j) = b(i , j);
            else c(i , j) = c(i - 1, j) + b(i , j);
        }
    }

    For( i , 1 , n ) For( j , 1 , m ) f(i , j) = vc;
}

void xuli()
{
    For( i , 1 , n )
    {
        For( j , 1 , m )
        {
            ll res = 0;

            /// hàng
            res = h(i , j);
            if( i > 1 ) res += f( i-1 , j );
            f(i , j) = min( f(i , j) , res );

            /// Cột
            res = c(i , j);
            if( j > 1 ) res += f( i , j-1 );
            f(i , j) = min ( f(i , j), res );
        }
    }
    cout << f(n , m) << endl;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen(LT"1366.inp","r",stdin);
    freopen(LT"1366.out","w",stdout);
    nhap();
    process();
    xuli();
}
