#include <cstring>
#include <iostream>
#include <stdio.h>
using namespace std;
const int N = 1e5 + 50;
const int M = 2e5 + 50;
#define ll long long
#define inf 0x3f3f3f3f
int temp[N], weight[N];
int head[N], ver[M], nxt[M], tot;
int fa[N], dep[N], sze[N], son[N], top[N], dfn[N], rnk[N], dfn_tot;
struct SegmentTree
{
    int l, r;
    ll sum, max_val;
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define l(x) tree[x].l
#define r(x) tree[x].r
#define sum(x) tree[x].sum
#define max_val(x) tree[x].max_val
} tree[N << 2];
void PushUp(int rt)
{
    sum(rt) = sum(ls(rt)) + sum(rs(rt));
    max_val(rt) = max(max_val(ls(rt)), max_val(rs(rt)));
}
void SegmentTree_Build(int rt, int l, int r)
{
    l(rt) = l, r(rt) = r;
    if (l == r)
    {
        max_val(rt) = sum(rt) = weight[l];
        return;
    }
    int mid = (l + r) >> 1;
    SegmentTree_Build(ls(rt), l, mid);
    SegmentTree_Build(rs(rt), mid + 1, r);
    PushUp(rt);
    //向上更新
}
void Update(int rt, int x, int d)
{
    if (l(rt) == r(rt))
    {
        sum(rt) = max_val(rt) = d;
        return;
    }
    int mid = (l(rt) + r(rt)) >> 1;
    if (x <= mid)
        Update(ls(rt), x, d);
    else
        Update(rs(rt), x, d);
    PushUp(rt);
}
ll Query_sum(int rt, int l, int r)
{
    if (l(rt) >= l && r(rt) <= r)
    {
        return sum(rt);
    }
    ll ret = 0;
    int mid = (l(rt) + r(rt)) >> 1;
    if (l <= mid)
        ret += Query_sum(ls(rt), l, r);
    if (r > mid)
        ret += Query_sum(rs(rt), l, r);
    return ret;
}
ll Query_max(int rt, int l, int r)
{
    if (l(rt) >= l && r(rt) <= r)
    {
        return max_val(rt);
    }
    ll ret = -inf;
    int mid = (l(rt) + r(rt)) >> 1;
    if (l <= mid)
        ret = max(ret, Query_max(ls(rt), l, r));
    if (r > mid)
        ret = max(ret, Query_max(rs(rt), l, r));
    return ret;
}
/*
    重链剖分
        fa[x] 表示节点x在树上的父亲
        dep[x]表示节点x在树上的深度
        sze[x]表示节点x的子树的节点个数
        son[x]表示节点x的重儿子
        top[x]表示节点x所在重链的顶部节点（深度最小）
        dfn[x]表示节点x的DFS序 ，也是其在线段树中的编号
        rnk[x]表示DFS序所对应的节点编号，有rnk[dfn[x]]=x
 */
void Add(int x, int y)
{
    ver[++tot] = y, nxt[tot] = head[x], head[x] = tot;
}
void Build(int x, int pre, int depth)
{
    son[x] = -1, sze[x] = 1, dep[x] = depth;
    for (int i = head[x]; i; i = nxt[i])
    {
        int y = ver[i];
        if (y == pre)
            continue;
        Build(y, x, depth + 1);
        sze[x] += sze[y], fa[y] = x;
        if (son[x] == -1 || sze[son[x]] < sze[y])
            son[x] = y;
    }
}
void Decomposition(int x, int t)
{
    top[x] = t, dfn[x] = ++dfn_tot, rnk[dfn_tot] = x;
    if (son[x] == -1)
        return;
    Decomposition(son[x], t);
    for (int i = head[x]; i; i = nxt[i])
    {
        int y = ver[i];
        if (y != son[x] && y != fa[x])
            Decomposition(y, y);
    }
}
ll Path_Sum(int x, int y)
{
    ll ret = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        ret += Query_sum(1, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    ret += Query_sum(1, dfn[x], dfn[y]);
    return ret;
}
ll Path_Max(int x, int y)
{
    ll ret = -inf;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        ret = max(ret, Query_max(1, dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    ret = max(ret, Query_max(1, dfn[x], dfn[y]));
    return ret;
}
int main()
{
    int n;
    scanf("%d", &n);
    int x, y;
    for (int i = 1; i <= n - 1; i++)
        scanf("%d%d", &x, &y), Add(x, y), Add(y, x);
    for (int i = 1; i <= n; i++)
        scanf("%d", &temp[i]);
    Build(1, 0, 1);
    Decomposition(1, 1);
    for (int i = 1; i <= n; i++)
        weight[i] = temp[rnk[i]];
    SegmentTree_Build(1, 1, dfn_tot);
    int q;
    scanf("%d",&q);
    char op[10];
    for (int i = 1; i <= q; i++)
    {
        scanf("%s", op);
        int x, y, z;
        if (op[1] == 'H')
        {
            scanf("%d%d", &x, &z);
            Update(1, dfn[x], z);
        }
        else if (op[1] == 'M')
        {
            scanf("%d%d", &x, &y);
            printf("%lld\n", Path_Max(x, y));
        }
        else if(op[1]=='S')
        {
            scanf("%d%d", &x, &y);
            printf("%lld\n", Path_Sum(x, y));
        }
    }
    //system("pause");
    return 0;
}