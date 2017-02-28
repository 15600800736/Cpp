#include "Fib.h"
#include "iostream"
#include "CVector.cpp"
using namespace std;
int main()
{
	char A[10] = "abcdefghi";
	CVector<char> Vector1(A, 10);
	Vector1.replace(0, 5, 'a');
	Vector1.deduplicate();
	Vector1.insert(2, 'k');
	for (int i = 0; i < Vector1.size();i++)
	{
		cout << Vector1[i] << endl;
	}

}