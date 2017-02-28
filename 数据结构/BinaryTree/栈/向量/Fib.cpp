#include "Fib.h"
CFib::CFib(int x) :n(x)
{
	fib = new int[n];
	fib[0] = 1;
	fib[1] = 1;
	init();
}
int CFib::init()
{
	for (int i = 2; i < n; i++)
		fib[i] = fib[i - 1] + fib[i - 2];
	return 0;
}
int CFib::prev()
{
	if (n = 1) return 0;
	n -= 1;
	return n;
}
int CFib::get()
{
	return fib[n-1];
}
CFib::~CFib()
{
	delete[] fib;
	fib = NULL;
	n = 0;
}