#ifndef _VEC_INCLUDED
#define _VEC_INCLUDED yes


#include<iostream>
#include<string>
#include<cmath>

class vec {
protected:
	int size;
	int * arr;

public:
	vec();
	vec(int s);
	void clear();
	bool is_empty();
	void push_back(int x);
	int pop_back();
	int back();
	int get(int i);
	void set(int i, int x);
	int get_size();
};

#endif
