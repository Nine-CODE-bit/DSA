#include<bits/stdc++.h>
using namespace std;

const int MAX_NOTES = 1e5;

struct Node
{
    char style;
    int last=-1,o_deg=0,i_deg=0,visited=0;
}node[MAX_NOTES];

struct edge
{
    int u,v,next=-1;
}e[MAX_NOTES];

int num = 0, color[25];

void add_edge(int u, int v)
{
    e[num].u = u;
    e[num].v = v;
    e[num].next = node[u].last;
    node[u].last = num;
    node[u].o_deg++;
    node[v].i_deg++;
    num++;
    return;
}

int into_num(string s)
{
    int res = 0;
    for(int i=0; i<s.size(); i++)
    {
        res = res * 10 + (s[i] - '0');
    }
    return res;
}

int dfs(int u, int ans);

int main()
{
    string style, path;
    cin >> style;
    int n=style.size();
    n=n-2;
    for(int i=0; i<n; i++)
    {
        node[i].style = style[i+1];
    }
    // Build the graph
    cin >> path;
    int u, v, i=0;
    while(i < path.size())
    {
        while(path[i] == '[')
        {
            i++;
        }
        u=0,v=0;
        string su="",sv="";
        while(i < path.size() && path[i] != ',')
        {
            su += path[i];
            i++;
        }
        if(path[i]==',')i++;
        while(i < path.size() && path[i] != ']')
        {
            sv += path[i];
            i++;
        }
        i+=2;
        u = into_num(su);
        v = into_num(sv);
        if(u == v)
        {
            cout << -1;
            return 0;
        }
        add_edge(u, v);
    }
    int ans = 0, source = 0;
    for(int i=0; i < n; i++)
    {
        if(node[i].i_deg == 0)
        {
            source++;
            int res = dfs(i, ans);
            if(res == -1)
            {
                cout << -1;
                return 0;
            }
            ans = max(ans, res);
        }
    }
    if(source == 0)
    {
        cout << -1;
        return 0;
    }
    cout << ans;
    return 0;
}

int dfs(int u, int ans)
{
    color[node[u].style - 'a']+=1;
    node[u].visited = 1;
    int res = ans;
    if(node[u].o_deg == 0)
    {
        for(int i=0; i < 25; i++)
        {
            res = max(res, color[i]);
        }
        node[u].visited = 0;
        color[node[u].style - 'a'] -= 1;
        return res;
    }
    for(int i = node[u].last; i != -1; i = e[i].next)
    {
        int v = e[i].v;
        if(node[v].visited == 0)
        {
            int _res = dfs(v, ans);
            if(_res == -1)
            {
                return -1;
            }
            res = max(res, dfs(v, _res));
        }
        else
        {
            return -1;
        }
    }
    node[u].visited = 0;
    color[node[u].style - 'a'] -= 1;
    return res;
}