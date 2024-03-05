#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

};

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
	sort(v.begin(), v.end());		// ����
	if (v.size() == 0) {
		return NULL;
	}
	ListNode* p = new ListNode(-1, NULL);
	ListNode* head = p;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		if (it == v.begin()) {
			p->val = *it;
		}
		else {
			ListNode* t = new ListNode(-1, NULL);
			t->val = *it;
			p->next = t;
			p = t;
		}
	}
	p->next = NULL;

	return head;
}

bool hasCycle1(ListNode* head) {
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

bool hasCycle2(ListNode* head) {
	ListNode* p1 = head, * p2 = head;
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

void inOrder(TreeNode* root, vector<int>& v) {
	if (root == nullptr) {
		return;
	}
	inOrder(root->left, v);
	v.emplace_back(root->val);
	inOrder(root->right, v);
}

vector<int> inorderTraversal(TreeNode* root) {
	vector<int> res;
	inOrder(root, res);
	return res;
}




int maxDepth(TreeNode* root) {
	int ld = 0, rd = 0;
	if (root == nullptr) {
		return 0;
	}
	ld = maxDepth(root->left);
	rd = maxDepth(root->right);
	return ld > rd ? ld + 1 : rd + 1;
}


TreeNode* invertTree(TreeNode* root) {
	if (root == nullptr) {
		return NULL;
	}
	TreeNode* temp = root->left;
	root->left = root->right;
	root->right = temp;
	invertTree(root->left);
	invertTree(root->right);
	return root;

}



int Max;

int depth(TreeNode* rt) {
	if (rt == nullptr) {
		return 0;
	}
	int L, R;
	L = depth(rt->left);
	R = depth(rt->right);


	if (L + R > Max) {
		Max = L + R;

	}
	return L > R ? L + 1 : R + 1;
}

int diameterOfbinaryTree(TreeNode* root) {
	Max = 0;
	depth(root);
	return Max;
}

bool compare(TreeNode* left, TreeNode* right) {
	if (left == nullptr && right != nullptr) {
		return false;
	}
	if (left != nullptr && right == nullptr) {
		return false;
	}
	if (left == nullptr && right == nullptr) {
		return true;
	}
	if (left->val != right->val) {
		return false;
	}
	bool out = compare(left->left, right->right);
	bool in = compare(left->right, right->left);
	return out && in;
}

int res = 0;
int dfs(TreeNode* root) {
	if (root == nullptr) {
		return -1;
	}
	int r_deep = 1 + dfs(root->right);
	int l_deep = 1 + dfs(root->left);
	res = r_deep + l_deep > res ? r_deep + l_deep : res;
	return r_deep > l_deep ? r_deep : l_deep;
}

int diameterOfBinaryTree(TreeNode* root) {
	return dfs(root);
}


// 只出现一次的数字
int singleNums(vector<int>& nums) {
	int res = 0;
	for (int i = 0; i < nums.size(); i++) {
		res = nums[i] ^ res;
	}
	return res;
}
// 数组中出现最多中的元素
int majorityElement(vector<int>& nums) {
	sort(nums.begin(), nums.end());
	return nums[nums.size() / 2];
}

int majorityElement2(vector<int>& nums) {
	stack<int> s;
	for (int i = 0; i < nums.size(); i++) {
		// stack is empty,insert element
		if (s.empty()) {
			s.push(nums[i]);
			continue;
		}

		// top equal,insert element
		if (nums[i] == s.top()) {
			s.push(nums[i]);
		}
		// top different,insert element
		else {
			s.pop();
		}
	}
	return s.top();
}

int main() {
	cout << "你好" << endl;
	system("pause");
	return 0;
}