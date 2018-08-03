/*
	*	.h file that just creates a basic BST to be used for our programs
	*	Returns a pair containing the root and the height of the tree
*/

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <climits>
using namespace std;
int num;
//Structure of node
struct Node{
	int data;
	int x, y;						//x and y coordinates, y also stores the height of the node
	int modifier;					//amount of shift for the subtree
	struct Node *left, *right;		//left and right subtrees
};

//Creates a new node and returns it
struct Node* getNode(int val, int height){
	struct Node *root = (struct Node*)malloc(sizeof(struct Node));
	root->data = val;
	root->x = root->modifier = 0;
	root->y = height;
	root->left = root->right = NULL;
	return root;
}

//Insert node into BST
struct Node* Insert(struct Node* root, int data, int height){
    if(root == NULL)
        root = getNode(data, height);
    else if(data <= root->data)
        root->left = Insert(root->left, data, height+1);
    else
        root->right = Insert(root->right, data, height+1);
    return root;
}


//Find height of the tree
int findHeight(struct Node *root){
	if(root == NULL) return 0;
	return max(findHeight(root->left), findHeight(root->right)) + 1;
}

//Creates a binary tree and returns its root and height
pair<struct Node*, int> bst_init(){
	struct Node *root = NULL;

	cout<<"Enter number of nodes\n";
	cin>>num;
	if(num==0)
    {
        cout<<"Please enter a number greater that 0\n";
        exit(0);
    }
	int arr[num];
	cout<<"Enter the Nodes\n";
	for(int i=0;i<num;i++)
       {
           cin>>arr[i];
       }

	int n = sizeof(arr)/sizeof(arr[0]);

	//insert all elements in BST
	for(int i=0; i<n; i++)
		root = Insert(root, arr[i], 0);

	//inorder(root);
	int height = findHeight(root);
	pair<struct Node*, int> p = make_pair(root, height);
	return p;
}
