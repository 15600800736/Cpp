

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
		std::vector<int> sortedNums(nums);
		std::vector<int> result;
		std::vector<int>::iterator begin = sortedNums.begin();
		std::vector <int>::iterator end = sortedNums.end();
		std::sort(begin, end);
		std::vector<int>::iterator iter = sortedNums.begin();
		std::vector<int>::iterator iterTarget = sortedNums.end();
		while(iter != end){
			iterTarget = std::lower_bound(iter + 1, sortedNums.end(), target - *iter);
			if (iterTarget != sortedNums.end()) {
				break;
			}
			iter++;
		}
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] == *iter) {
				result.push_back(i);
			}
			if (nums[i] == *iterTarget) {
				result.push_back(i);
			}
		}
		return result;
	}

};