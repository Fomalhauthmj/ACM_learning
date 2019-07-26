//http://codeforces.com/contest/1107/problem/G
#include <iostream>
using namespace std;
#define ll long long
#define inf 0x3f3f3f3f3f3f3f3f
const int N = 3E5 + 50;
int n,a,d[N],s[N],top,l[N],r[N];
ll diff[N],c[N];
struct SegmentTree
{
    ll l, r;
    ll sum, dat, lmax, rmax;
} t[N << 2];
void PushUp(int rt)
{
    //区间最大子段和
    t[rt].sum = t[rt << 1].sum + t[rt << 1 | 1].sum;
    t[rt].lmax = max(t[rt << 1].sum + t[rt << 1 | 1].lmax, t[rt << 1].lmax);
    t[rt].rmax = max(t[rt << 1 | 1].sum + t[rt << 1].rmax, t[rt << 1 | 1].rmax);
    t[rt].dat = max(t[rt << 1].rmax + t[rt << 1 | 1].lmax, max(t[rt << 1].dat, t[rt << 1 | 1].dat));
}
void Build(int rt, int l, int r)
{
    t[rt].l = l;
    t[rt].r = r;
    if (l == r)
    {
        t[rt].dat = t[rt].sum = t[rt].lmax = t[rt].rmax = c[l];
        return;
    }
    int mid = (l + r) >> 1;
    Build(rt << 1, l, mid);
    Build(rt << 1 | 1, mid + 1, r);
    PushUp(rt);
}
SegmentTree Query(int rt, int l, int r)
{
    if (l <= t[rt].l && t[rt].r <= r)
    {
        return t[rt];
    }
    int mid = (t[rt].l + t[rt].r) >> 1;
    SegmentTree a,b,ans;
    a.dat=a.lmax=a.rmax=a.sum=b.dat=b.lmax=b.rmax=b.sum=-inf;
    ans.sum=0;
    if (l <= mid)
    {
        a = Query(rt << 1, l, r);
        ans.sum+=a.sum;
    }
    if (r > mid)
    {
        b= Query(rt << 1 | 1, l, r);
        ans.sum+=b.sum;
    }
    ans.dat=max(max(a.dat,b.dat),a.rmax+b.lmax);
    ans.lmax=max(a.sum+b.lmax,a.lmax);
    ans.rmax=max(b.sum+a.rmax,b.rmax);
    if(l>mid) ans.lmax=max(ans.lmax,b.lmax);
    //为了处理单侧查询导致的错误结果 完全保持正确性
    if(r<=mid) ans.rmax=max(ans.rmax,a.rmax);
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>a;
    ll ans=0;
    for(int i=1;i<=n;i++)
    {
        cin>>d[i]>>c[i];
        c[i]=a-c[i];
        ans=max(ans,c[i]);
    }
    for(int i=1;i<=n-1;i++)
    {
        diff[i]=d[i+1]-d[i];
    }
    //diff[i]作为最大值 维护递减单调栈
    top=0;
    s[0]=0;
    for(int i=1;i<=n-1;i++)
    {
        while(top>0&&diff[s[top]]<=diff[i])
        {
            top--;
        }
        l[i]=s[top]+1;
        s[++top]=i;
    }
    top=0;
    s[0]=n;
    for(int i=n-1;i>=1;i--)
    {
        while(top>0&&diff[s[top]]<=diff[i])
        {
            top--;
        }
        r[i]=s[top];
        s[++top]=i;
    }
    //[l[i],r[i]) diff[i]为最大值的区间
    //for(int i=1;i<=n-1;i++)
        //cout<<l[i]<<" "<<r[i]<<endl;
    Build(1,1,n);
    for(int i=1;i<=n-1;i++)
    {
        ans=max(ans,Query(1,l[i],r[i]).dat-diff[i]*diff[i]);
    }
    cout<<ans<<endl;
    //system("pause");
    return 0;
}