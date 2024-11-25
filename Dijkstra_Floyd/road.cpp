#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<pair<ll, ll>, ll> type_edge;

const ll inf = 0x3f3f3f3f3f3f3f3f;

vector<type_edge> Prim(vector<vector<ll>> matrix, vector<type_edge> edges);
vector<type_edge> Krusal(vector<vector<ll>> matrix, vector<type_edge> edges);
bool cmp1(type_edge x, type_edge y);
bool cmp2(type_edge x, type_edge y);

int main()
{
    cout << "Krusal请按1\nPrim请按2\n";
    ll type;
    cin >> type;

    freopen("input.txt", "r", stdin);

    ll i, j;
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> matrix(n + 1, vector<ll>(n + 1, inf));
    vector<type_edge> edges(m);
    for (i = 0; i < m; i++)
    {
        cin >> edges[i].first.first >> edges[i].first.second >> edges[i].second;
        if (edges[i].first.first > edges[i].first.second)
            swap(edges[i].first.first, edges[i].first.second);
        matrix[edges[i].first.first][edges[i].first.second] = edges[i].second;
        matrix[edges[i].first.second][edges[i].first.first] = edges[i].second;
    }

    vector<type_edge> tree;
    switch (type)
    {
    case 1:
        tree = Krusal(matrix, edges);
        break;
    case 2:
        tree = Prim(matrix, edges);
    default:
        break;
    }

    for (i = 0; i < tree.size(); i++)
    {
        if (tree[i].first.first > tree[i].first.second)
            swap(tree[i].first.first, tree[i].first.second);
    }
    sort(tree.begin(),tree.end(),cmp2);

    if (tree.size() != n - 1)
    {
        cout << "该图不存在最小生成树\n";
    }
    else
    {
        cout<<"最小生成树生成成功\n";
        freopen("output.txt","w",stdout);
        cout<<tree.size()<<'\n';
        for(i=0;i<tree.size();i++)
        {
            cout<<tree[i].first.first<<' ';
            cout<<tree[i].first.second<<' ';
            cout<<tree[i].second<<'\n';
        }
    }
    return 0;
}

vector<type_edge> Prim(vector<vector<ll>> matrix, vector<type_edge> edges)
{
    ll i, j;

    vector<bool> vis(matrix.size(), false);

    vis[1] = true;
    vector<type_edge> now;
    type_edge road;
    for (i = 1; i < matrix.size(); i++)
    {
        if (matrix[1][i] != inf)
        {
            road = make_pair(make_pair(1, i), matrix[1][i]);
            now.push_back(road);
        }
    }

    vector<type_edge> tree;
    while (!now.empty())
    {
        ll min_len = inf, min_pos;
        for (i = 0; i < now.size(); i++)
        {
            if (now[i].second < min_len)
            {
                min_len = now[i].second;
                min_pos = i;
            }
        }

        tree.push_back(now[min_pos]);
        vis[now[min_pos].first.second] = true;

        i = 0;
        while (i < now.size())
        {
            if (vis[now[i].first.second])
                now.erase(now.begin() + i);
            else
                i++;
        }
    }

    return tree;
}

vector<type_edge> Krusal(vector<vector<ll>> matrix, vector<type_edge> edges)
{
    ll i, j;
    vector<pair<ll, ll>> dsu(matrix.size());
    for (i = 0; i < matrix.size(); i++)
    {
        dsu[i].first = i;
        dsu[i].second = i;
    }
    sort(edges.begin(), edges.end(), cmp1);

    vector<type_edge> tree;
    for (i = 0; i < edges.size(); i++)
    {
        ll now[2] = {0}, root[2];
        root[0] = edges[i].first.first;
        root[1] = edges[i].first.second;

        while (now[0] != root[0])
        {
            now[0] = root[0];
            root[0] = dsu[root[0]].second;
        }
        while (now[1] != root[1])
        {
            now[1] = root[1];
            root[1] = dsu[root[1]].second;
        }

        if (root[0] != root[1])
        {
            tree.push_back(edges[i]);
            root[1] = root[0];
        }

        if (tree.size() == matrix.size() - 2)
            break;
    }

    return tree;
}

bool cmp1(type_edge x, type_edge y)
{
    return x.second < y.second;
}

bool cmp2(type_edge x, type_edge y)
{
    if (x.first.first < y.first.first)
        return true;
    if (x.first.first > y.first.first)
        return false;
    return x.first.second < y.first.second;
}
