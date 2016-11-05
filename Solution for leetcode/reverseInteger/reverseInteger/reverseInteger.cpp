#include <vector>
#include <algorithm>
#include <math.h>
class Solution {
public:
	int reverse(int x) {
		int sign = 0;
		if (x > 0) {
			sign = 1;
		} else if (0 == x) {
			sign = 0;
		} else {
			sign = -1;
		}
		int max[] = { 2, 1, 4, 7, 4, 8, 3, 6, 4, 7 };
		int res = 0;
		int tmp = 0;
		bool needCheckOverFlow = false;
		x = abs(x);
		if (x > 1000000000) {
			needCheckOverFlow = true;
		}
		int i = 0;
		while (x != 0) {
			tmp = x - x / 10 * 10;
			if (needCheckOverFlow) {
				if (tmp < max[i]) {
					needCheckOverFlow = false;
				} else if (tmp > max[i]) {
					return 0;
				}
			}
			x = x / 10;
			res = res * 10 + tmp;
			i++;
		}

		res = sign * res;

		return res;
	}
};