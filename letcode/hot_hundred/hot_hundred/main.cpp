#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
	
};

// 二叉树节点
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
	
};
// 尾插法合并两个链表
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
	vector<int> v;
	while (list1 || list2) {
		if (list1 != NULL) {
			v.emplace_back(list1->val);
			list1 = list1->next;
		}
		if (list2 != NULL) {
			v.emplace_back(list2->val);
			list2 = list2->next;
		}
	}
	sort(v.begin(), v.end());		// 排序
	if (v.size() == 0) {
		return NULL;
	}
	ListNode *p = new ListNode(-1, NULL);
	ListNode *head = p;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		if (it == v.begin()) {
			p->val = *it;
		}
		else {
			ListNode *t = new ListNode(-1, NULL);
			t->val = *it;
			p->next = t;
			p = t;
		}
	}
	p->next = NULL;

	return head;
}
// 判断链表是否有环
bool hasCycle1(ListNode *head) {
	vector<ListNode*> v;
	vector<ListNode*>::iterator it;
	while (head != NULL) {
		it = find(v.begin(), v.end(), head);
		if (it != v.end()) {
			return true;
		}
		v.emplace_back(head);
		head = head->next;
	}
	return false;
}
// 快慢指针判断是否有环
bool hasCycle2(ListNode *head) {
	ListNode *p1 = head, *p2 = head;
	if (p1 == NULL) {
		return false;
	}
	while (p1->next && p1->next->next) {
		p1 = p1->next->next;
		p2 = p2->next;
		if (p1 == p2) {
			return true;
		}
	}
	return false;
}

// 二叉树中序遍历:左——>中——>右
vector<int> inorderTraversal(TreeNode* root) {
	vector<int> res;
	inOrder(root, res);	
}

void inOrder(TreeNode* root, vector<int> &v) {
	if (root == nullptr) {
		return;
	}
	inOrder(root->left, v);
	v.emplace_back(root->val);
	inOrder(root->right, v);
}

// 二叉树高度——递归
int maxDepth(TreeNode* root) {
	int ld = 0, rd = 0;
	if (root == nullptr) {
		return 0;
	}
	ld = maxDepth(root->left);
	rd = maxDepth(root->right);
	return ld > rd ? ld + 1 : rd + 1;
}

// 二叉树交换左右子树
TreeNode* invertTree(TreeNode* root) {
	if (root == nullptr) {
		return NULL;
	}
	TreeNode *temp = root->left;
	root->left = root->right;
	root->right = temp;
	invertTree(root->left);
	invertTree(root->right);
	return root;

}


int main() {
	
	system("pause");
	return 0;
}