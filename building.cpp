//Tóm tắt :
//Cho n hình chữ nhật trên hệ trục tọa độ.
//Mỗi hình chữ nhật cho tọa độ 2 đỉnh trái trên và phải dưới.
//2 hình chữ nhật gọi là kề nhau nếu có chung ít nhất 1 đỉnh.
//Lưu ý: không có 2 hình chữ nhật nào cắt nhau hoặc bao nhau.
//
//Mỗi hình chữ nhật tượng trưng cho 1 đỉnh.
//Giá trị của mỗi cạnh cầu u - v là abs( f[v] - (dem - f[v]) )
//
//Tìm cầu có giá trị nhỏ nhất. Nếu không có cầu nào thì xuất -1

// Solution:
//- Nhận thấy rằng, ta chỉ cần duyệt mỗi hình chữ nhật với các hình chữ nhật kề nó và không để có dư là được. Hay nói cách khác là duyệt vừa đủ.
//- Vì các hình chữ nhật không cắt hoặc bao nhau nên với mỗi hình chữ nhật, ta sẽ xét các hình chữ nhật có cạnh đóng giao với cạnh trái hoặc trên của hình chữ nhật đang xét.
 
// Cách thực hiện tìm giao nhau với cạnh trái. ( Duyệt sweepline theo tọa độ x ). Cách làm với cạnh trên cũng giống thế nhưng là sweepline theo Oy
//  - Quy định : Vector ke[x][i] sẽ chứa tọa độ của 2 cạnh trên và dưới của hcn có cạnh đóng là x.
//  - Với mỗi hình chữ nhật, ta sẽ chia ra 2 cạnh đóng và mở theo tọa độ x.
//  - Khi gặp 1 cạnh đóng với tọa độ x thì ta sẽ:
//    + Thêm 1 phần tử vào vector ke[x]. 
//        * Ví dụ 1 hcn với tọa độ trái trên là (1;5) và phải dưới là (2;3). Thì ta sẽ push ( { 3 ; 5 } ) vào vector.
//    + Nhận xét rằng. Vì các hình chữ nhật không cắt hoặc bao nhau. => Các đoạn trong vector sẽ không bị cắt nhau. 
//        * Ví dụ : {3 ; 6} và { 4 ; 7 } sẽ không có trong cùng 1 vector.
//    + Để dễ quản lý thì ta sẽ sort lại các phần tử này theo chiều tăng dần của giá trị thứ nhất.
//  - Khi gặp 1 cạnh mở với tọa độ x thì ta sẽ:
//    + Xét các hình chữ nhật có cạnh đóng là x ( đã được lưu lại trong vector ke[x] ) để tìm các hình chữ nhật giao và thêm cạnh
//    + Việc này là khá đơn giản khi ta đã sort các giá trị trong vector này lại. Điều cần làm chỉ là chặt vị trí bắt đầu và duyệt qua các phần tử kề nó cho tới khi nào 
//      không còn thỏa.
// Như các bước trên này thì việc xây đồ thị đã hoàn tất và không cần khó nữa. Xin để dành phần còn lại cho các bạn đọc.

#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define db double
#define maxn 100005
#define LT "building"
#define For(i , a , b) for(int i = int(a) ; i <= int(b) ; i++)
#define FOr(i , a , b) for(int i = int(a) ; i >= int(b) ; i--)
#define fi first
#define se second

typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

int i , j , n , m , k;

struct hcn
{
    int x1 , y1;
    int x2 , y2;
    int id;
};
hcn a[maxn];

struct canh
{
    int x , y1 , y2;
    int loai , id;

    bool operator < ( canh a )
    {
        if( x < a.x ) return true;
        if( x > a.x ) return false;
        if( loai > a.loai ) return true;
        if( loai < a.loai ) return false;
        if( y1 < a.y1 ) return true;
        if( y1 > a.y1 ) return false;
        return true;
    }
};
vector<canh> U;

struct ii
{
    int x , y , id;
};
vector<ii> ds[maxn * 4];
vector<int> dsk[maxn];
vii cau;

int low[maxn] , num[maxn] , cnt = 0 ;
int f[maxn]; /// f[i] là số lượng nút con trong nhánh i
int ans = 1e9 , dem = 0;

void nhap()
{
    cin >> n;
    For( i , 1 , n )
    {
        int x1 , y1 , x2 , y2;
        cin >> x1 >> y1 >> x2 >> y2;
        a[i] = { x1 , y1 , x2 , y2 , i };
    }
}

void nen()
{
    vi u;
    For( i , 1 , n )
    {
        u.pb( a[i].x1 );
        u.pb( a[i].x2 );
        u.pb( a[i].y1 );
        u.pb( a[i].y2 );
    }
    sort( u.begin() , u.end() );
    u.resize( unique( u.begin() , u.end() ) - u.begin() );
    m = u.size();
    For( i , 1 , n )
    {
        a[i].x1 = lower_bound( u.begin() , u.end() , a[i].x1 ) - u.begin() + 1;
        a[i].x2 = lower_bound( u.begin() , u.end() , a[i].x2 ) - u.begin() + 1;
        a[i].y1 = lower_bound( u.begin() , u.end() , a[i].y1 ) - u.begin() + 1;
        a[i].y2 = lower_bound( u.begin() , u.end() , a[i].y2 ) - u.begin() + 1;
    }
}

/// a giao b thì trả về 2
/// a không giao b và nằm trên b thì trả về 1
/// a không giao b và nằm dưới b thì trả về 0
int check( ii a , ii b )
{
    int kt = 0;
    if( a.x > b.x )
    {
        kt = 1;
        swap( a , b );
    }

    if( a.y >= b.x ) return 2;
    return kt;
}

/// Tìm vị trí nhỏ nhất mà giao với a trong vector tọa độ x
int chat( int x , ii a )
{
    int l = 0 , r = ds[x].size() - 1;
    while( l <= r )
    {
        int mid = (l + r) >> 1;
        ii tam = ds[x][mid];
        int gt = check( tam , a );
        if( gt == 0 ) l = mid + 1;
        else r = mid - 1;
    }
    return r + 1;
}

/// Tìm các đỉnh kề với danh sách các cạnh là U. Đơn giản là với 1 cạnh mở thì ta sẽ chặt tìm vị trí nhỏ nhất mà giao với cạnh này xong ta sẽ đi for để tìm
/// phần còn lại
void solve()
{
    /// khoi tao
    For( i , 1 , m ) ds[i].clear();

    for( canh tam : U )
    {
        int loai = tam.loai;

        ii tmp = { tam.y1 , tam.y2 , tam.id };

        /// cạnh đóng
        if( loai == 1 )
        {
            ds[tam.x].pb( tmp );
            continue;
        }

        /// canh mo
        if( int( ds[tam.x].size() ) == 0 ) continue;
        int vt = chat( tam.x , tmp );

        while( vt < ds[tam.x].size() )
        {
            if( check( tmp , ds[tam.x][vt] ) == 2 )
            {
                int u = tmp.id , v = ds[tam.x][vt].id;
                dsk[u].pb(v);
                dsk[v].pb(u);
                vt++;
            }
            else break;
        }
    }
}

void Build_graph()
{
    /// Sweep line với hoành độ. Cố định x.
    
    For( i , 1 , n )
    {
        int x1 = a[i].x1 , x2 = a[i].x2 , y1 = a[i].y1 , y2 = a[i].y2;
        U.pb( { x1 , y2 , y1 , 0 , i } );  /// 0 là cạnh mở
        U.pb( { x2 , y2 , y1 , 1 , i } );  /// 1 là cạnh đóng
    }
    sort( U.begin() , U.end() );
    solve();

    /// Sweep line với tung độ. Cố định y.
    U.clear();
    For( i , 1 , n )
    {
        int x1 = a[i].x1 , x2 = a[i].x2 , y1 = a[i].y1 , y2 = a[i].y2;
        U.pb( { y2 , x1 , x2 , 0 , i } );
        U.pb( { y1 , x1 , x2 , 1 , i } );
    }
    sort( U.begin() , U.end() );
    solve();
}

void dfs( int u , int p )
{
    dem++;
    low[u] = num[u] = ++cnt;
    for( int v : dsk[u] )
    {
        if( v == p ) continue;
        if( num[v] == 0 )
        {
            dfs( v , u );
            low[u] = min( low[u] , low[v] );
            f[u] += f[v];
            if( low[v] > num[u] ) cau.pb( { u , v } );
        }
        else low[u] = min( low[u] , num[v] );
    }
}

void xuli()
{
    For( i , 1 , n ) f[i] = 1;
    For( i , 1 , n )
    {
        if( num[i] == 0 )
        {
            dem = 0;
            cau.clear();
            dfs(i , i);

            for( pii tam : cau )
            {
                int u = tam.fi , v = tam.se;
                ans = min( ans , abs( f[v] - ( dem - f[v] ) ) );
            }
        }
    }

    if( ans == 1e9 )  { cout << -1 << endl; return  ; }
    cout << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen(LT".inp","r",stdin);
    freopen(LT".out","w",stdout);

    nhap();
    nen();
    Build_graph();
    xuli();
    return 0;
}
