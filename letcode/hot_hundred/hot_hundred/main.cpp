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

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
	vector<int> v;
	while (list1 || list2) {
		if (list1 != NULL) {
			v.emplace_back(list1->val);
		}
		if (list2 != NULL) {
			v.emplace_back(list2->val);
		}
		list1 = list1->next;
		list2 = list2->next;
	}
	sort(v.begin(), v.end());
	ListNode *p = new ListNode(-1, NULL);

}

int main() {


	
	system("pause");
	return 0;
}