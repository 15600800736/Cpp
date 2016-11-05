#include <vector>
#include <algorithm>
#include <math.h>
class Solution {
public:
	int myAtoi(string str) {
		int res = 0;
		int start = 0;
		int sign = 0;
		if (!str.empty()) {
			for (int i = 0; i < str.size(); i++) {
				if (32 == str[i]) {
					continue;
				} else {
					start = i;
					break;
				}
			}
			if ('-' == str[start] && str[start + 1] > 47 && str[start + 1] < 58) {
				start++;
				sign = -1;
			} else if ('+' == str[start] && str[start + 1] > 47 && str[start + 1] < 58) {
				start++;
				sign = 1;
			} else if (str[start] > 47 && str[start] < 58) {
				sign = 1;
			}
			int temp = 0;
			for (int i = start; i < str.size(); i++) {
				if (str[i] > 47 && str[i] < 58) {
					temp = 10 * res;
					if (temp / 10 != res) {
						if (1 == sign) {
							return INT_MAX;
						} else if (-1 == sign) {
							return INT_MIN;
						}
					}
					res = temp + str[i] - 48;
					if (1 == sign && (res < str[i] - 48 || res < temp)) {
						return INT_MAX;
					} else if (-1 == sign && (-res > -(str[i] - 48) || -res > -temp)) {
						return INT_MIN;
					}
				} else if (' ' == str[i]) {
					break;
				} else {
					break;
				}
			}
		}
		res = res*sign;
		return res;
	}
};