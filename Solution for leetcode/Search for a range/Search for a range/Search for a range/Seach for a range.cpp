#include <vector>
using namespace std;
class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		if (1 == nums.size()) {
			return nums[0] == target ? vector<int>(2, 0) : vector<int>(2, -1);
		}
		vector<int> res;
		int low = 0;
		int high = nums.size() - 1;
		int mid = 0;
		//get start
		while (high - low > 0) {
			if (1 == high - low) {
				if (target == nums[low]) {
					res.push_back(low);
					break;
				} else if (target == nums[high]) {
					res.push_back(high);
					break;
				} else {
					res.push_back(-1);
					res.push_back(-1);
					return res;
				}
			}
			//if nums[mid] >= target,turn left
			//else turn right
			mid = (low + high) >> 1;
			if (nums[mid] > target) {
				high = mid;
			} else if (nums[mid] == target) {
				if (nums[mid - 1] != target) {
					res.push_back(mid);
					break;
				} else {
					high = mid;
				}
			} else {
				low = mid;
			}
		}
		//get end
		low = 0;
		high = nums.size() - 1;
		mid = 0;
		while (high - low > 0) {
			if (1 == high - low) {
				if (target == nums[high]) {
					res.push_back(high);
					break;
				} else if (target == nums[low]) {
					res.push_back(low);
					break;
				}
			}
			//if nums[mid] <= target,turn right
			//else turn left
			mid = (low + high) >> 1;
			if (nums[mid] < target) {
				low = mid;
			} else if (nums[mid] == target) {
				if (nums[mid + 1] != target) {
					res.push_back(mid);
					break;
				} else {
					low = mid;
				}
			} else {
				high = mid;
			}
		}
		return res;
	}
};