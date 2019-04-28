#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
#define N 200010
int n;
//�������߶��߶��� ��ɢ��
long long tree[N << 2];
//���轨�� ��ʼ�߶�Ϊ0
//���ά����
void push_down(int rt)
{
    if (tree[rt])
    {
        //���¸���
        tree[rt << 1] = max(tree[rt << 1], tree[rt]);
        tree[rt << 1 | 1] = max(tree[rt << 1 | 1], tree[rt]);
        tree[rt] = 0;
        //��0
    }
}
//��ʱ������ϸ��� ���¸���
//ά��������� �������ϸ���
//�������
void update(long long val, int start, int end, int left, int right, int rt)
{
    if (start <= left && right <= end)
    {
        //ֱ�Ӹ���
        tree[rt] = max(tree[rt], val);
        return;
    }
    push_down(rt);
    //����һ������ǰ ���Ʊ����
    int mid = (left + right) >> 1;
    if (mid >= start)
    {
        update(val, start, end, left, mid, rt << 1);
    }
    if (mid < end)
    {
        update(val, start, end, mid + 1, right, rt << 1 | 1);
    }
}
long long query(int x, int left, int right, int rt)
{
    if (left == right) //�����ѯ
    {
        return tree[rt];
    }
    push_down(rt);//���Ʊ�Ҫ
    int mid = (left + right) >> 1;
    if (x <= mid)
    {
        query(x, left, mid, rt << 1);
    }
    else
    {
        query(x, mid + 1, right, rt << 1 | 1);
    }
}
struct seg
{
    long long left;
    long long right;
    long long height;
};
seg segs[N];
long long xpos[2 * N];
int cnt;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n;
    cnt = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> segs[i].height >> segs[i].left >> segs[i].right;
        xpos[cnt++] = segs[i].left;
        xpos[cnt++] = segs[i].right;
    }
    sort(xpos, xpos + cnt);
    cnt = unique(xpos, xpos + cnt) - xpos;
    //���� ȥ�� ��ɢ��
    memset(tree, 0, sizeof(tree));
    //��ʼΪ0
    for (int i = 0; i < n; i++)
    {
        int left = lower_bound(xpos, xpos + cnt, segs[i].left) - xpos;
        int right = lower_bound(xpos, xpos + cnt, segs[i].right) - xpos;
        update(segs[i].height, left, right - 1, 0, cnt - 1, 1);
        //�������
        //Ϊʲô��r-1�� ������������߶Ȳ�ͬ
    }
    //�����ѯ
    long long pre_max = 0;
    long long cur_max;
    vector<pair<long long, long long>> v;
    for (int i = 0; i < cnt; i++)
    {
        cur_max = query(i, 0, cnt - 1, 1);
        if (cur_max != pre_max)
        {
            v.push_back(make_pair(xpos[i], pre_max));
            v.push_back(make_pair(xpos[i], cur_max));
        }
        pre_max = cur_max;
    }
    int len = v.size();
    cout << len << endl;
    for (int i = 0; i < len; i++)
    {
        cout << v[i].first << " " << v[i].second << endl;
    }
    return 0;
}
