

/*
 *
 * Sort the nums and find the result of target subs the elements by order
 * Time complexity O(nlogn)
 */
#include <vector>
#include <algorithm>
class Solution {
public:
	std::vector<int> twoSum(std::vector<int>& nums, int target) {
		bool first = false, second = false;
		std::vector<int> sortedNums(nums);
		std::vector<int> result;
		std::vector<int>::iterator begin = sortedNums.begin();
		std::vector <int>::iterator end = sortedNums.end();
		std::sort(begin, end);
		std::vector<int>::iterator iter = sortedNums.begin();
		std::vector<int>::iterator iterTarget;
		while (iter != sortedNums.end()) {
			iterTarget = std::lower_bound(iter + 1, end, target - *iter);
			if (iterTarget != sortedNums.end()) {
				if (*iterTarget + *iter == target)
					break;
			}
			iter++;
		}
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] == *iter && !first) {
				result.push_back(i);
				first = true;
			} else if (nums[i] == *iterTarget && !second) {
				result.push_back(i);
				second = true;
			}
			if (first && second) {
				break;
			}
		}
		return result;
	}

};