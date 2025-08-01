// Iterative Inorder, Preorder, Postorder Traversal

// Inorder Traversal:
// Left doesn't exist: Note down node values and move to right
// Left exists:
// If left subtree not traversed (link doesn't exist): Create the link and move to the left
// If left subtree traversed (link exists): Remove the link, note down the value of node and move to right

// Preorder Traversal:
// Left doesn't exist: Note down node values and move to right
// Left exists:
// If left subtree not traversed (link doesn't exist): Note down the value of node create the link and move to the left
// If left subtree traversed (link exists): Remove the link, move to right

#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

vector<int> inorder(TreeNode* root){
    vector<int> ans;
    while(root){
        // Left Part Doesn't Exist
        if(!root->left){
            ans.push_back(root->val);
            root = root->right; 
        }
        // Left Part Exists
        else{
            TreeNode* curr = root->left;
            while(curr->right && curr->right!=root){
                curr = curr->right;
            }
            // If left subtree not traversed
            if(!curr->right){
                curr->right = root;
                root = root->left;
            }
            // If left subtree traversed
            else{
                curr->right = nullptr;
                ans.push_back(root->val);
                root = root->right;
            }
        }
    }
    return ans;
}

vector<int> preorder(TreeNode* root){
    vector<int> ans;
    while(root){
        // Left Part Doesn't Exist
        if(!root->left){
            ans.push_back(root->val);
            root = root->right; 
        }
        // Left Part Exists
        else{
            TreeNode* curr = root->left;
            while(curr->right && curr->right!=root){
                curr = curr->right;
            }
            // If left subtree not traversed
            if(!curr->right){
                ans.push_back(root->val);
                curr->right = root;
                root = root->left;
            }
            // If left subtree traversed
            else{
                curr->right = nullptr;
                root = root->right;
            }
        }
    }
    return ans;
}


int main(){
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    root->left->right->left = new TreeNode(6);
    root->left->right->right = new TreeNode(7);

    root->right->right = new TreeNode(8);

    root->right->right->left = new TreeNode(9);    

    cout<<"Inorder Traversal: ";
    for(auto j : inorder(root)){
        cout<<j<<" ";
    }
    cout<<"\nPreorder Traversal: ";
    for(auto j : preorder(root)){
        cout<<j<<" ";
    }
    // cout<<"\nPostorder Traversal: ";
    // for(auto j : postorder(root)){
    //     cout<<j<<" ";
    // }
    cout<<endl;
}
