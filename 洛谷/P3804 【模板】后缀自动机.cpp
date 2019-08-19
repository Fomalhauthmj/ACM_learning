#include <cstring>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
#define ll long long
const int MAXLEN = 1e6 + 50;
ll sze[MAXLEN * 2];
ll ans;
namespace SAM
{
struct state
{
    int len, link, next[26];
} st[MAXLEN * 2];
int sz, last;
int head[MAXLEN * 2], ver[MAXLEN * 2], nxt[MAXLEN * 2], tot;
void add(int x, int y)
{
    ver[++tot] = y, nxt[tot] = head[x], head[x] = tot;
}
void SAM_Init()
{
    st[0].len = 0, st[0].link = -1;
    sz++, last = 0;
}
void SAM_Extend(int c)
{
    int cur = sz++;
    sze[cur] = 1;
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].next[c])
    {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1)
        st[cur].link = 0;
    else
    {
        int q = st[p].next[c];
        if (st[q].len == st[p].len + 1)
            st[cur].link = q;
        else
        {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            memcpy(st[clone].next, st[q].next, sizeof(st[clone].next));
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q)
            {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}
void BuildLinkTree()
{
    for (int i = 1; i < sz; i++)
        add(st[i].link, i);
}
void DFS(int x)
{
    for (int i = head[x]; i; i = nxt[i])
    {
        int y = ver[i];
        DFS(y);
        sze[x] += sze[y];
    }
    if (sze[x] != 1)
        ans = max(ans, sze[x] * st[x].len);
}
int id[MAXLEN * 2], c[MAXLEN * 2];
void Topo()
{
    //计数排序
    for (int i = 1; i < sz; i++)
        c[st[i].len]++;
    for (int i = 1; i < MAXLEN; i++)
        c[i] += c[i - 1];
    for (int i = 1; i < sz; i++)
        id[c[st[i].len]--] = i;
    for (int i = sz - 1; i >= 1; i--)
    {
        sze[st[id[i]].link] += sze[id[i]];
        if (sze[id[i]] > 1)
            ans = max(ans, sze[id[i]] * st[id[i]].len);
    }
}
} // namespace SAM
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    string str;
    cin >> str;
    SAM::SAM_Init();
    for (int i = 0; i < str.length(); i++)
        SAM::SAM_Extend(str[i] - 'a');
    ans = 0;
    /*
    SAM::BuildLinkTree();
    SAM::DFS(0);
    */
    SAM::Topo();
    cout << ans << endl;
    //system("pause");
    return 0;
}