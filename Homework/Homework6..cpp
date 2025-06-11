#include<bits/stdc++.h>
using namespace std;

struct Node
{
    int num=0;
    char word;
}node[24];

int cmp(const Node &a, const Node &b)
{
    if(a.num == b.num)
    {
        return a.word < b.word;
    }
    return a.num > b.num;
}

int main()
{
    string line;
    getline(cin, line);
    int k;
    cin >> k;
    int n = line.size();
    for(int i=0; i < n; i++)
    {
        node[line[i] - 'A'].num++;
    }
    for(int i=0; i<24; i++)
    {
        node[i].word = 'A' + i;
    }
    sort(node, node + 24, cmp);
    cout << node[k-1].word;
    return 0;
}