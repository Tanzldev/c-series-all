#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<deque>
#include<algorithm>
using namespace std;


class Solution {
public:
	vector<int> rearrangeBarcodes(vector<int>& barcodes) {
		vector<int> res;
		deque<int> d;
		for (int i = 0; i < barcodes.size(); i++) {
			d.push_back(barcodes[i]);
		}
		sort(d.begin(), d.end());
		
		if (barcodes.empty()) {
			return res;
		}

		
		if (d.size() % 2 == 0) {
			while (!d.empty()) {
				res.push_back(d.front());
				res.push_back(d.back());
				d.pop_front();
				d.pop_back();
			}

		}
		else {
			while (d.size() > 1) {
				res.push_back(d.front());
				res.push_back(d.back());
				d.pop_front();
				d.pop_back();
			}
			res.push_back(d.front());
		}

		return res;
	}
};
int main() {

	int i,input;
	vector<int> d;
	vector<int> res;
	Solution s;
	for (i = 0; i < 6; i++) {
		cin >> input;
		d.push_back(input);
	}
	res = s.rearrangeBarcodes(d);

	for (i = 0; i < 6; i++) {
		cout << res[i] << " ";
	}
	system("pause");
	return 0;
}