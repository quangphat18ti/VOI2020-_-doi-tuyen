/// Tóm tắt : Tìm hình chữ nhật có diện tích lớn nhất có 4 đỉnh là 4 điểm trong n điểm đã cho.
/// Các đường biên và bên trong hình đều không được có điểm.

/// Nhận xét như sau : các cạnh của hình chữ nhật này nếu được sắp xếp thep sweepline thì
/// nó sẽ phải là 2 đỉnh liên tiếp trên 1 sweepline.

/// Như vậy nếu ta duyệt theo sweepline thì ta chỉ cần xét n cạnh.

/// Khi xét tới 1 cạnh u - v của cột tọa độ x thì ta cần làm 2 công việc :
/// - Check xem có tồn tại cặp đỉnh u - v này trước hay chưa
/// - Có tồn tại đỉnh nào nằm trong hcn này hay không
/// - Cái này kiểm tra rất đơn giản bằng cách IT.

/// - Ta sẽ gọi để tìm kiếm vị trí lớn nhất xuất hiện thằng u , v và đoạn u + 1 - > v - 1
/// - Tôi gọi nó là gt cho dễ giải thích
/// - Vậy thì khi nào sẽ tạo được hcn với cạnh từ u -> v từ cột x
///    + Đã có xuất hiện u -> v trước đó và u,v phải trùng cột với nhau ( gt[u] == gt[v] )
///    + Chưa có điểm nào có tọa độ từ u + 1 đến v - 1 xuất hiện trong khoảng này ( gt[u] > gt[u+1 -> v-1] )


#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define fi first
#define se second
#define LT "daoao"
#define maxn 50005
#define For(i , a , b) for( int i = int(a) ; i <= int(b) ; i++ )
#define FOr(i , a , b) for( int i = int(a) ; i >= int(b) ; i-- )

typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

int i , j , n , m ,k;

struct diem
{
    int x , y;

    bool operator < ( diem a )
    {
        return x < a.x || ( x == a.x && y < a.y );
    }
};
diem a[maxn];

vi X , Y;

vector<int> ds[maxn];
int IT[maxn * 4];

void nen()
{
    For( i , 1 , n ) X.pb( a[i].x ) , Y.pb( a[i].y );
    sort( X.begin() , X.end() );
    sort( Y.begin() , Y.end() );
    X.resize( unique( X.begin() , X.end() ) - X.begin() );
    Y.resize( unique( Y.begin() , Y.end() ) - Y.begin() );

    For( i , 1 , n )
    {
        a[i].x = lower_bound( X.begin() , X.end() , a[i].x ) - X.begin();
        a[i].y = lower_bound( Y.begin() , Y.end() , a[i].y ) - Y.begin();
    }
}

void nhap()
{
    cin >> n;
    For( i , 1 , n ) cin >> a[i].x >> a[i].y;
    nen();
    sort( a + 1 , a + n + 1 );
    For( i , 1 , n ) ds[a[i].x].pb( a[i].y );
}

void Build( int id , int l , int r )
{
    if( l == r ) { IT[id] = -1; return; }
    int mid = (l + r) >> 1;
    Build( id*2 , l , mid );
    Build( id*2+1 , mid + 1 , r );
    IT[id] = max( IT[id*2] , IT[id*2+1] );
}

void update( int id, int l, int r, int vt, int gt )
{
    if( l > vt || r < vt ) return;
    if( l == r )
    {
        IT[id] = gt;
        return;
    }

    int mid = (l + r) >> 1;
    update( id*2, l, mid, vt, gt );
    update( id*2 + 1, mid + 1, r, vt, gt );
    IT[id] = max(IT[id*2] , IT[id*2+1]);
}

int get( int id, int l, int r, int u, int v )
{
    if( l > v || r < u ) return -1;
    if( l >= u && r <= v ) return IT[id];
    int mid = (l + r) >> 1;
    return max( get(id*2, l, mid, u, v) , get(id*2+1 , mid+1, r, u, v) );
}

void xuli()
{
    Build( 1 , 0 , n );
    ll ans = 0;

    For( i , 0 , n )
    {
        For( j , 0 , ds[i].size() - 2 )
        {
            int l = ds[i][j] , r = ds[i][j + 1];

            int l_ = get( 1 , 0 , n , l , l );
            int r_ = get( 1 , 0 , n , r , r );
            int tam = get( 1 , 0 , n , l+1 , r-1 );

            if( l_ == r_ && l_ >=0 && l_ > tam )
                ans = max(ans , 1ll * ( X[i] - X[l_] ) * ( Y[r] - Y[l] ) );
        }

        for( int u : ds[i] ) update( 1 , 0 , n , u , i );
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
