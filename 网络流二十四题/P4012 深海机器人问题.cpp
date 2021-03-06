#include <cstring>
#include <iostream>
#include <queue>
#include <stdio.h>
using namespace std;
const int N = 1e6 + 50;
const int M = 1e6 + 50;
#define inf 0x3f3f3f3f
#define ll long long
int S, T, tot = 1;
int head[N], ver[M], nxt[M], edge[M], cost[M], dis[N], incf[N], pre[N];
bool vis[N];
void add(int x, int y, int z, int c)
{
    ver[++tot] = y, nxt[tot] = head[x], head[x] = tot, edge[tot] = z, cost[tot] = c;
    ver[++tot] = x, nxt[tot] = head[y], head[y] = tot, edge[tot] = 0, cost[tot] = -c;
}
bool SPFA_max()
{
    memset(dis, 0xcf, sizeof(dis)); //inf
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    dis[S] = 0, vis[S] = 1, incf[S] = 1 << 30;
    q.push(S);
    while (q.size())
    {
        int x = q.front();
        q.pop();
        vis[x] = 0;
        for (int i = head[x]; i; i = nxt[i])
        {
            if (edge[i])
            {
                int y = ver[i];
                if (dis[y] < dis[x] + cost[i])
                {
                    dis[y] = dis[x] + cost[i];
                    incf[y] = min(incf[x], edge[i]);
                    pre[y] = i;
                    if (!vis[y])
                        q.push(y), vis[y] = 1;
                }
            }
        }
    }
    if (dis[T] == 0xcfcfcfcf)
        return false;
    return true;
}
ll max_flow, ans;
void Update()
{
    int x = T;
    while (x != S)
    {
        int i = pre[x];
        edge[i] -= incf[T];
        edge[i ^ 1] += incf[T];
        x = ver[i ^ 1];
    }
    max_flow += incf[T];
    ans += incf[T] * dis[T];
}
int p, q;
int H(int x, int y)
{
    return y * (q + 1) + x;
}
int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    scanf("%d%d", &p, &q);
    int k, r, x, y;
    S = H(20, 20), T = H(21, 21);
    int value;
    for (int i = 0; i <= p; i++)
        for (int j = 0; j < q; j++)
            scanf("%d", &value), add(H(j, i), H(j + 1, i), 1, value), add(H(j, i), H(j + 1, i), inf, 0);
    for (int i = 0; i <= q; i++)
        for (int j = 0; j < p; j++)
            scanf("%d", &value), add(H(i, j), H(i, j + 1), 1, value), add(H(i, j), H(i, j + 1), inf, 0);
    for (int i = 0; i < a; i++)
    {
        scanf("%d%d%d", &k, &y, &x);
        add(S, H(x, y), k, 0);
    }
    for (int i = 0; i < b; i++)
    {
        scanf("%d%d%d", &r, &y, &x);
        add(H(x, y), T, r, 0);
    }
    max_flow = ans = 0;
    while (SPFA_max())
        Update();
    printf("%lld\n", ans);
    //system("pause");
    return 0;
}