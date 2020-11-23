///Tóm tắt : Cho 2 dãy số a và b lần lượt có n và m phần tử.
///- Tìm Cmin được ghép từ các phần tử trong A. Nếu A toàn 0 thì xuất 0
///- Tìm Dmax được ghép bởi các phần tử khác nhau trong A và B

#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define db double
#define pb push_back
#define fi first
#define se second
#define For(i , a , b) for(int i = int(a) ; i <= int(b) ; i++)
#define FOr(i , a , b) for(int i = int(a) ; i >= int(b) ; i--)
#define LT "ghepso"
#define maxn 100005

typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vii;

int i , j , n , m , k;
vii a , b;
ll lt[15];
int d[maxn];
int kt;

int demcs( int s )
{
    if( s == 0 ) return 1;
    int ans = 0;
    while(s > 0) ans++ , s/= 10;
    return ans;
}

void nhap()
{
    cin >> n >> m;
    For( i , 0 , n - 1 )
    {
        int x; cin >> x;
        a.pb( { x , demcs(x) } );
    }

    For( i , 0 , m - 1 )
    {
        int x; cin >> x;
        b.pb( { x , demcs(x) } );
    }
}

/// Thêm 1 số 0 vào sau xong ss
bool comp_min1( pii a , pii b )
{
    /// check = 1 thì a > b
    bool check = 0;
    if( a.fi > b.fi ) check = 1;

    int dist = abs( a.se - b.se );
    if( dist > kt ) dist = kt;

    if( a.fi < b.fi ) a.fi = a.fi * lt[dist] , a.se += dist;
    else if( a.fi > b.fi ) b.fi = b.fi * lt[dist] , b.se += dist;

    ll res1 = lt[b.se] * a.fi + b.fi;
    ll res2 = lt[a.se] * b.fi + a.fi;

    if( res1 < res2 ) return true;
    if( res1 == res2) return check;
    return false;
}

/// Không thêm số 0
bool comp_min( pii a , pii b )
{
    ll res1 = lt[b.se] * a.fi + b.fi;
    ll res2 = lt[a.se] * b.fi + a.fi;
    return res1 < res2;
}

bool comp_max( pii a , pii b )
{
    ll res1 = lt[b.se] * a.fi + b.fi;
    ll res2 = lt[a.se] * b.fi + a.fi;
    return res1 > res2;
}

void Find_min()
{
    kt = 0;
    For( i , 0 , n - 1 ) if( a[i].fi == 0 ) kt++;
    if( kt == n ) { cout << 0 << endl; return; }

    /// kt là số lượng số 0 có trong dãy a
    vii u;

    int vt = -1;
    if( kt > 0 )
    {
        sort( a.begin() , a.end() , comp_min1 );
        For( i , 0 , n - 1 ) if( a[i].fi != 0 ) { vt = i; break; }
        cout << a[vt].fi;
        For( i , 0 , vt - 1 ) cout << a[i].fi;
        For( i , vt + 1 , n - 1 ) u.pb(a[i]);
    }
    else u = a;

    sort( u.begin() , u.end() , comp_min );
    for( pii tam : u ) cout << tam.fi;
    cout << endl;
}

void Find_max()
{
    vii u;
    For( i , 0 , n - 1 )
    {
        if( d[a[i].fi] == 0 )
        {
            u.pb( a[i] );
            d[a[i].fi] = 1;
        }
    }

    For( i , 0 , m - 1 )
    {
        if( d[b[i].fi] == 0 )
        {
            u.pb( b[i] );
            d[b[i].fi] = 1;
        }
    }

    sort( u.begin() , u.end() , comp_max );

    if( u[0].fi == 0 ) { cout << 0 << endl; return; }
    for( pii tam : u ) cout << tam.fi;
    cout << endl;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen(LT".inp","r",stdin);
    freopen(LT".out","w",stdout);

    lt[0] = 1;
    For( i , 1 , 10 ) lt[i] = lt[i - 1] * 10;

    nhap();
    Find_min();
    Find_max();
}
