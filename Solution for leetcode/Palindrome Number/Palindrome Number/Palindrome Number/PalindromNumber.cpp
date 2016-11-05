#include <math.h>
class Solution {
public:
	bool isPalindrome(int x) {
		if (x < 0) {
			return false;
		}
		int tmp = x;
		int len = 0;
		while (tmp / 10 != 0) {
			tmp /= 10;
			len++;
		}
		int left = pow((float)10, len);
		int right = 1;
		while (right < left) {
			if (x / left % 10 != x / right % 10) {
				return false;
			}
			left /= 10;
			right *= 10;
		}
		return true;
	}
};