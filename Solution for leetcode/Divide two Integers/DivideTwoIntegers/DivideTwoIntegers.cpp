
#include <math.h>
#include <iostream>

//first,find the max num which is equal or smaller dividend by two times divisor every time.
//and then divide it by two every time until it turn back to original divisor
class Solution {
public:
	int divide(int dividend, int divisor) {
		if (INT_MIN == dividend && -1 == divisor) {
			return INT_MAX;
		}
		if (0 == divisor) {
			return INT_MIN;
		}
		bool positive = false;
		if ((dividend > 0 && divisor >0) || (dividend < 0 && divisor < 0)) {
			positive = true;
		}
		long long dividendLong = 0;
		long long divisorLong = 0;
		if (INT_MIN == dividend) {
			dividendLong = 2147483648;
		} else {
			dividendLong = abs(dividend);
		}
		if (INT_MIN == divisor) {
			divisorLong = 2147483648;
		} else {
			divisorLong = abs(divisor);
		}
		int k = 0;
		int res = 0;
		long long temp = divisorLong;
		while (dividendLong - temp >= 0) {
			k++;
			temp <<= 1;
		}
		dividendLong -= (temp >>= 1);
		if (0 == k) {
			return 0;
		} else {
			res = (1 << --k);
		}
		while (dividendLong > 0) {
			if (0 == k) {
				break;
			}
			k--;
			temp >>= 1;
			if (dividendLong - temp >= 0) {
				dividendLong -= temp;
				res += (1 << k);
			}
		}

		if (false == positive) {
			res = -res;
		}
		return res;
	}
};