#include "Fib.h"
#include "iostream"
#include "CVector.cpp"
using namespace std;
void output(int &e);
void(*pout)(int &) = output;
int main()
{
	int Arr[10] = { 3,5,9,7,8,1,2,3,2,10};
	CVector<int>Vector1(Arr, 10);
	CVector<int> Vector2(Vector1,2,5);
	Vector2.sort(MERGE);
	Vector2.traverse(pout);
	return 0;
}
void output(int &e)
{
	cout << e <<endl;
}