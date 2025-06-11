#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
const int INF=1e9;
int place[N],vis[N];
set<int> nodes;
queue<int> preorder_result,inorder_result,postorder_result,right_view_result;

class Stack
{
    private:
        int top;
        int* arr;
    public:
        Stack(int size){
            arr = new int[size];
            top = -1;
        }
        int pop(){
            if (top == -1){
                return -1;
            }
            return arr[top--];
        }
        void push(int x){
            arr[++top] = x;
        }
        int size(){
            return top + 1;
        }
        void empty(){
            top = -1;
        }
};

struct TreeNode
{
    int depth,left=-1,right=-1,parent=-1;
}tree[N];

void depth_initialize(int root,int depth)
{
    tree[root].depth = depth;
    if(tree[root].left != -1) depth_initialize(tree[root].left,depth+1);
    if(tree[root].right != -1) depth_initialize(tree[root].right,depth+1);
    return;
}

void preorder(int root)
{
    preorder_result.push(root);
    if(tree[root].left != -1) preorder(tree[root].left);
    if(tree[root].right != -1) preorder(tree[root].right);
    return;
}

void inorder(int root)
{
    if(tree[root].left != -1) inorder(tree[root].left);
    inorder_result.push(root);
    if(tree[root].right != -1) inorder(tree[root].right);
    return;
}

void postorder(int root)
{
    if(tree[root].left != -1) postorder(tree[root].left);
    if(tree[root].right != -1) postorder(tree[root].right);
    postorder_result.push(root);
    return;
}

void right_view(int root)
{
    if(root == -1)return;
    if(vis[tree[root].depth] == 0)
    {
        right_view_result.push(root);
        vis[tree[root].depth] = 1;
    }
    right_view(tree[root].right);
    right_view(tree[root].left);
    return;
}

int LCA(int a,int b)
{
    if(tree[a].depth < tree[b].depth) swap(a,b);
    while(tree[a].depth != tree[b].depth) a = tree[a].parent;
    while(a != b) a = tree[a].parent, b = tree[b].parent;
    return a;
}

int min_light(int root)
{
    if(root == -1)return 0;  
    if(tree[root].left == -1 && tree[root].right == -1)
    {
        if(tree[root].parent == root)
        {
            return 1;
        }
        return 0;
    }
    int left = min_light(tree[root].left);
    int right = min_light(tree[root].right);
    if(vis[tree[root].left]==0 || vis[tree[root].right]==0)
    {
        vis[root] = 1;
        vis[tree[root].left] = 1;
        vis[tree[root].right] = 1;
        vis[tree[root].parent] = 1;
        return 1 + left + right;
    }
    if(vis[root]==0)
    {
        if(tree[root].parent == root)
        {
            return 1 + left + right;
        }
    }
    return left + right;
}

int main()
{
    string line;
    char direction;
    int parent,child;
    while(getline(cin,line))
    {
        if(line.empty())break;
        if(isalpha(line[0])) break;
        stringstream ss(line);
        ss >> parent >> direction >> child;
        if(parent < 0 || parent >= N || child < 0 || child >= N)
        {
            cout << "false";
            return 0;
        }
        // 记忆树上的节点
        nodes.insert(parent);
        nodes.insert(child);
        // 建树
        if(direction == 'L')
        {
            if(tree[parent].left != -1)
            {
                cout << "false";
                return 0;
            }
            tree[parent].left = child;
            if(tree[child].parent != -1)
            {
                cout << "false";
                return 0;
            }
            tree[child].parent = parent;
        }
        else
        {
            if(tree[parent].right != -1)
            {
                cout << "false";
                return 0;
            }
            tree[parent].right = child;
            if(tree[child].parent != -1)
            {
                cout << "false";
                return 0;
            }
            tree[child].parent = parent;
        }
    }
    // 确定树的根节点
    int root = -1;
    for(int node : nodes)
    {
        if(tree[node].parent == -1)
        {
            if(root != -1)
            {
                cout << "false";
                return 0;
            }
            root = node;
            tree[root].parent = root;
        }
    }
    if(root == -1)
    {
        cout << "false";
        return 0;
    }
    // 初始化各节点深度
    depth_initialize(root,0);
    // 处理遍历方式
    for(int i = 0; i<=line.size();i+=2)
    {
        if(line[i] == 'A')
        {
            preorder(root);
            while(!preorder_result.empty())
            {
                cout << preorder_result.front();
                preorder_result.pop();
                if(!preorder_result.empty())
                {
                    cout << " ";
                }
            }
        }
        else if(line[i] == 'B')
        {
            inorder(root);
            while(!inorder_result.empty())
            {
                cout << inorder_result.front();
                inorder_result.pop();
                if(!inorder_result.empty())
                {
                    cout << " ";
                }
            }
        }
        else if(line[i] == 'C')
        {
            postorder(root);
            while(!postorder_result.empty())
            {
                cout << postorder_result.front();
                postorder_result.pop();
                if(!postorder_result.empty())
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
    Stack s(N);
    int num;
    int flag;
    while(cin >> num)
    {
        if(flag == -1) continue;
        flag = 0;
        for(int node : nodes)
        {
            if(node == num)
            {
                flag=1;
                break;
            }
        }
        if(flag == 0)
        {
            flag = -1;
            cout << "-1"<<endl;
            continue;
        }
        s.push(num);
    }
    while(s.size() > 0 && flag != -1)
    {
        if(s.size() == 1)
        {
            break;
        }
        int a,b;
        a = s.pop();
        b = s.pop();
        s.push(LCA(a,b));
    }
    if(flag != -1)
    {
        cout << s.pop() << endl;
    }
    right_view(root);
    while(!right_view_result.empty())
    {
        cout << right_view_result.front();
        right_view_result.pop();
        if(!right_view_result.empty())
        {
            cout << " ";
        }
    }
    cout << endl;
    for(int i = 0; i < N; i++)
    {
        vis[i] = 0;
    }
    cout << min_light(root) << endl;
    return 0;
}