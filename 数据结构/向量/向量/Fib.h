#pragma once
#define NULL 0
class CFib
{
private: 
	int n;
	int* fib;
	int init();
public:
	CFib(int x);
	~CFib();
	int get();
	int prev();
};