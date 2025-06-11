#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    int left = -1;
    int right = -1;
    int parent = -1;
};

vector<TreeNode> tree;
vector<int> summaries, BST;
int nodeCount = 0;
int maxBSTSum = 0;

int createNode(int val) {
    TreeNode node;
    node.val = val;
    node.left = -1;
    node.right = -1;
    node.parent = -1;
    tree.push_back(node);
    summaries.push_back(0);
    BST.push_back(1);
    return nodeCount++;
}

tuple<bool,int,int> check_BST(int node);

int cal_BST_Sum(int node);

int findMaxBSTSum(int node,int ans);

int main()
{
    string line;
    map <int, int> NodeMap;
    while(getline(cin, line)) {
        if(line.empty()) break;
        stringstream ss(line);
        int parentVal, childVal;
        char direction;
        ss >> parentVal >> direction >> childVal;
        
        // 获取或创建父节点
        int parentIndex;
        if(NodeMap.find(parentVal) == NodeMap.end()) {
            parentIndex = createNode(parentVal);
            NodeMap[parentVal] = parentIndex;
        } else {
            parentIndex = NodeMap[parentVal];
        }
        
        // 创建子节点
        int childIndex = createNode(childVal);
        NodeMap[childVal] = childIndex;
        
        // 连接父子节点
        if(direction == 'L') {
            tree[parentIndex].left = childIndex;
        } else {
            tree[parentIndex].right = childIndex;
        }
        tree[childIndex].parent = parentIndex;
    }
    // 确定树的根节点
    int rootIndex = -1;
    for (int i = 0; i < tree.size(); i++) {
        if (tree[i].parent == -1) {
            rootIndex = i;
            break;
        }
    }
    // 检查并标记每个节点是否为BST
    check_BST(rootIndex);
    // 计算每个节点的子树和
    cal_BST_Sum(rootIndex);
    // 找到最大的BST子树和
    int maxSum = findMaxBSTSum(rootIndex, 0);
    cout << maxSum;
    return 0;
}

tuple<bool, int, int> check_BST(int node) {
    if (node == -1) {
        return make_tuple(true, INT_MAX, INT_MIN);
    }
    tuple<bool, int, int> leftResult = check_BST(tree[node].left);
    bool leftIsBST = get<0>(leftResult);
    int leftMin = get<1>(leftResult);
    int leftMax = get<2>(leftResult);
    
    tuple<bool, int, int> rightResult = check_BST(tree[node].right);
    bool rightIsBST = get<0>(rightResult);
    int rightMin = get<1>(rightResult);
    int rightMax = get<2>(rightResult);

    int currentVal = tree[node].val;   
    // 检查BST性质
    bool isBST = leftIsBST && rightIsBST && (tree[node].left == -1 || leftMax < currentVal) && (tree[node].right == -1 || rightMin > currentVal);
    
    BST[node] = isBST ? 1 : 0;
    
    if (isBST) {
        int minVal = (tree[node].left == -1) ? currentVal : leftMin;
        int maxVal = (tree[node].right == -1) ? currentVal : rightMax;
        return make_tuple(true, minVal, maxVal);
    }
    
    return make_tuple(false, 0, 0);
}


int cal_BST_Sum(int node)
{
    if(node == -1)
    {
        return 0;
    }
    int left = tree[node].left;
    int right = tree[node].right;
    int leftSum = cal_BST_Sum(left);
    int rightSum = cal_BST_Sum(right);
    int currentSum = tree[node].val + leftSum + rightSum;
    summaries[node] = currentSum;
    return currentSum;
}

int findMaxBSTSum(int node,int ans)
{
    int maxSum = ans;
    if (BST[node] == 1)
    {
        maxSum = max(maxSum, summaries[node]);
        return maxSum;
    }
    int left = tree[node].left;
    int right = tree[node].right;
    if (left != -1)
    {
        maxSum = max(maxSum, findMaxBSTSum(left, ans));
    }
    if (right != -1)
    {
        maxSum = max(maxSum, findMaxBSTSum(right, ans));
    }
    return maxSum;
}