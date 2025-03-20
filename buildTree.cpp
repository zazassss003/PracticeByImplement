#include<iostream>
#include<vector>

using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution{
    public:
        TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder){
            TreeNode *node = new TreeNode();
            node = buildSubtree(0, preorder.size()-1, 0, inorder.size()-1, preorder, inorder);
            return node;
        }
        TreeNode *buildSubtree(int pL, int pR, int iL, int iR,vector<int> &preorder, vector<int> &inorder){

            if(pL>pR || iL>iR) return NULL;
            int i;
            for(i=iL; i<=iR; ++i){
                if(preorder[pL] == inorder[i]) break;
            }
            TreeNode *cur = new TreeNode(preorder[pL]);
            cur->left = buildSubtree(pL + 1, pL + (i - iL), iL, i - 1, preorder, inorder);
            cur->right = buildSubtree(pL + (i - iL) + 1, pR, i + 1, iR, preorder, inorder);

            return cur;

        }
        void preorderTraversal(TreeNode *root){
            if(root==NULL) return;
            cout<<root->val<<" ";
            preorderTraversal(root->left);
            preorderTraversal(root->right);
        }
};

int main(){
    Solution s;
    vector<int> preorder = {3,9,20,15,7};
    vector<int> inorder = {9,3,15,20,7};
    TreeNode *root = s.buildTree(preorder, inorder);
    s.preorderTraversal(root);

}