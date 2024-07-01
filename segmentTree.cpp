#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <utility> 
#include <iterator>
#include <set>
using namespace std;
class SegmentTree {
private:
	vector<int> segTree;
	int n;
	void buildAPI(vector<int> &data,int currNode, int leftMargin, int rightMargin) {
		if (leftMargin == rightMargin) {
			segTree[currNode] = data[leftMargin];
		}
		else {
			int mid = (leftMargin + rightMargin) / 2;
			buildAPI(data, 2 * currNode, leftMargin, mid);
			buildAPI(data, 2 * currNode + 1, mid + 1, rightMargin);
			segTree[currNode] = segTree[2 * currNode] + segTree[2 * currNode + 1];
		}
	}
	int sumBetweenRangeAPI(int currNode,int leftMargin,int rightMargin,int l,int r) {
		if (l > r) {
			return 0;
		}
		if (l == leftMargin && r == rightMargin) {
			return segTree[currNode];
		}
		int mid = (leftMargin + rightMargin) / 2;
		return sumBetweenRangeAPI(2 * currNode, leftMargin, mid, l, min(r, mid)) +
			sumBetweenRangeAPI(2 * currNode + 1, mid + 1, rightMargin, max(l, mid + 1), r);
	}
	void updateValueAtPositionAPI(int currNode, int leftMargin, int rightMargin, int position, int newValue) {
		if (leftMargin == rightMargin) {
			segTree[currNode] = newValue;
		}
		else {
			int mid = (leftMargin + rightMargin) / 2;
			if (position <= mid) {
				updateValueAtPositionAPI(2 * currNode, leftMargin, mid, position, newValue);
			}
			else {
				updateValueAtPositionAPI(2 * currNode + 1, mid + 1, rightMargin, position, newValue);
			}
			segTree[currNode] = segTree[2 * currNode] + segTree[2 * currNode + 1];
		}
	}
public:
	SegmentTree(int n, vector<int>& data) {
		segTree.resize(4 * n + 1);
		this->n = n;
		buildAPI(data, 1, 0, n - 1);
	}
	int sum_between_range(int l, int r) {
		return sumBetweenRangeAPI(1, 0, n - 1, l, r);
	}
	void update_value_at_position(int position, int newValue) {
		updateValueAtPositionAPI(1, 0, n - 1, position, newValue);
	}
	void show_segmentTree_array() {
		for (int i = 1; i < segTree.size(); i++) {
			cout << i << " - " << segTree[i]<<endl;
		}
	}
};
int main() {
	vector<int> data = { 1,3,-2,8,-7 };
	SegmentTree* st = new SegmentTree(data.size(),data);
	st->show_segmentTree_array();
}
