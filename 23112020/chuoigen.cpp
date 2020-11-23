/// Tóm tắt : Cho m dãy. Mỗi dãy là 1 hoán vị từ 1 -> n.
/// Tìm dãy con chung dài nhất của m dãy.

/// Nhận xét : Với những đỉnh nối được với nhau thì ta nối.
/// Ví dụ : Nối cạnh u -> v thì trong m dãy thì u đều phải đứng trước v.
/// Cái này ta có thể giải quyết đơn giản bằng mảng đếm

/// Sau khi xây đồ thị xong thì ta có thêm 1 nhận xét là u -> v thì sẽ không bao giờ
/// tồn tại cạnh v -> u hoặc đi lên tổ tiên u. Như vậy thì đây là đồ thị DAG

/// => Bài toán chuyển thành tìm đường đi dài nhất trên đồ thị DAG/

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
#define LT "chuoigen"
#define maxn 105
#define sz(A) int( A.size() )

typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

int i , j , n , m , k;
vector<int> a[15];
int d[maxn][maxn];
int f[maxn];
vi ke[maxn];

void nhap()
{
    cin >> n >> m;  /// m xâu độ dài n
    For(i , 1 , m)
    {
        For( j , 1 , n )
        {
            int x; cin >> x;
            a[i].pb(x);
        }
    }
}

void Build_graph( vi u )
{
    For( i , 0 , n - 1 )
        For( j , i + 1 , n - 1 )
            d[u[i]][u[j]]++;
}

void dfs( int u )
{
    f[u] = 1;
    for( int v : ke[u] )
    {
        if( f[v] == -1 ) dfs(v);
        f[u] = max( f[u] , f[v] + 1 );
    }
}

void xuli()
{
    For( i , 1 , n )
        For( j , 1 , n )
            if( d[i][j] == m ) ke[i].pb(j);

    For( i , 1 , n ) f[i] = -1;
    For( i , 1 , n ) if( f[i] == -1 ) dfs(i);
    cout << *max_element( f + 1 , f + n + 1 ) << endl;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen(LT".inp","r",stdin);
    freopen(LT".out","w",stdout);
    nhap();
    For( i , 1 , m ) Build_graph( a[i] );
    xuli();
}
