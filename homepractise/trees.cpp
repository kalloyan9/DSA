/*
home preparation for exam2
simple recursivley tree problems
(tree and binary search tree)
*/

#include <iostream>
#include <vector>
#include <stack> // dfs
#include <queue> // bfs
using namespace std;

namespace BST
{
	struct Node
	{
		int data;
		Node* left;
		Node* right;

		Node(int& _data, Node* _left = nullptr, Node* _right = nullptr)
			: data(_data), left(_left), right(_right) {	}

		void printInOrder(const Node* root)
		{
			if (!root)
				return;

			printInOrder(root->left);
			cout << root->data << " ";
			printInOrder(root->right);
		}

		void printPreOrder(const Node* root)
		{
			if (!root)
				return;

			cout << root->data << " ";
			printInOrder(root->left);
			printInOrder(root->right);
		}

		void printPostOrder(const Node* root)
		{
			if (!root)
				return;

			printInOrder(root->left);
			printInOrder(root->right);
			cout << root->data << " ";
		}

		bool isValidBST(const Node* root)
		{
			if (!root)
				return true;

			if (root->left && root->data < root->left->data)
				return false;
			
			if (root->right && root->right->data < root->data)
				return false;
			
			if (!isValidBST(root->left) || !isValidBST(root->right))
				return false;
			
			// pasing all that
			return true;
		}

		inline bool isLeaf(const Node* root)
		{
				return root && (!root->left && !root->right);
		}

		void trim(Node* root)
		{
			if (isLeaf(root)) {
				delete root;
				root = nullptr;
			} else {
				if (root->left)
					trim(root->left);
				if (root->right)
					trim(root->right);
			}
		}

		void bloom(Node* root)
		{
			if (isLeaf(root)) {
				root->left = new Node(root->data);
				root->right = new Node(root->data);
			}
			if (root->left) 
				bloom(root->left);
			if (root->right)
				bloom(root->right);
		}

	};
}

namespace TREE
{
	struct Node
	{
		int data;
		vector<Node*> children;

		Node(int _data)
			: data(_data) { }
	};

	int heigh(const Node* root)
	{
		if (!root)
			return 0;

		int best = 0;
		
		for (const Node* it : root->children) {
			int cur = heigh(it);
			if (cur > best)
				best = cur;
		}

		// accumulate with recursion stack
		return 1 + best;
	}

	int branchFactor(const Node* root)
	{
		if (!root)
			return 0;
		
		int factor = root->children.size();
		for (const Node* it : root->children) {
			int childfactor = branchFactor(it);
			if (childfactor > factor)
				factor = childfactor;
		}

		return factor;
	}

	void printLevel(const Node* root, int curLevel, int level)
	{
		if (curLevel == level)
			cout << root->data << " ";

		if (curLevel < level) {
			for (const Node* it : root->children) {
				printLevel(it, curLevel + 1, level);
			}
		}		
	}

	inline bool isLeaf(const Node* root)
	{
		return root && (root->children.empty());
	}

	int countLeafs(const Node* root)
	{
		if (isLeaf(root))
			return 1;
		
		int count = 0;
		for (const Node* it : root->children)
			count += countLeafs(it);
	
		return count;
	}

	bool allNodesEqualSumOfChildren(const Node* root)
	{
		if (root->children.empty())
			return true;

		int sum = 0;
		for (const Node* it : root->children) {
			sum += it->data;
		}
		if (sum != root->data)
			return false;
	
		for (const Node* it : root->children) 
			if (!allNodesEqualSumOfChildren(it))
				return false;

		// all that passed
		return true;
	}

	bool hasPathToLeafWithSum(const Node* root, int n)
	{
		int searchedSum = n - root->data;

		if (searchedSum == 0)
			return true;
		
		if (searchedSum < 0)
			return false;

		for (const Node* it : root->children)
			if (hasPathToLeafWithSum(it, searchedSum))
				return true;

		// none of the above
		return false;
	}

    // find function:
    // bfs implementation
    const Node* find(const Node* root, int searched)
    {
        if (!root)
            return root;
        else {
            queue<const Node*> q;
            q.push(root);
            while (!q.empty()) {
                const Node* curr = q.front();
                q.pop();

                if (curr->data == searched)
                    return curr;
                else {
                    for (const Node* it : curr->children)
                        q.push(it);
                }
            }
        }
        
        return nullptr;
    }

    // dfs implementation
    const Node* find(const Node* root, int searched)
    {
        if (!root)
            return root;
        else {
            stack<const Node*> s;
            s.push(root);
            while (!s.empty()) {
                const Node* curr = s.top();
                s.pop();

                if (curr->data == searched)
                    return curr;
                else {
                    for (const Node* it : curr->children)
                        s.push(it);
                }
            }
        }

        return nullptr;
    }
}

namespace BT
{
	struct Node
	{
		int value;
		Node* left, *right;
	
		Node(int v, Node* l = nullptr, Node* r = nullptr)
			: value(v), left(l), right(r) { }
	};

	void printInOrder(const Node* root)
	{
		if (!root)
			return;

		printInOrder(root->left);
		cout << root->value;
		printInOrder(root->right);
	}

	void leftView(const Node* root, int level, int& lastLevel)
	{
		if (!root)
			return;
		
		// if this is the first node of its level
		if (lastLevel < level) {
			cout << root->value;
			lastLevel = level;
		}

		leftView(root->left, level + 1, lastLevel);
		leftView(root->right, level + 1, lastLevel);
	}

	void leftViewWrapper(const Node* root)
	{
		int lastLevel = 0;
		leftView(Node, 1, lastLevel);
	}

	void rightView(const Node* root, int level, int& lastLevel)
	{
		if (!root)
			return;
		
		// if this is the first node of its level
		if (lastLevel < level) {
			cout << root->value;
			lastLevel = level;
		}

		leftView(root->right, level + 1, lastLevel);
		leftView(root->left, level + 1, lastLevel);
	}

	void rightViewWrapper(const Node* root)
	{
		int lastLevel = 0;
		rightView(Node, 1, lastLevel);
	}

}