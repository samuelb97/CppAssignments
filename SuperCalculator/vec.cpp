#include "myvec.h"

using namespace std;

vec::vec() {
	int size = 0;
	arr = new int[0];
}

vec::vec(int s) {
	int size = s;
	arr = new int[size];
}

void vec::clear() {
	size = 0;
	arr = new int[0];
}

bool vec::is_empty() {
	if (size == 0) return 1;
	else return 0;
}

void vec::push_back(int x) {
	if (arr[size - 1] == NULL)
		arr[size - 1] = x;
	else {
		int n_size = size * 2;
		int * temp = new int[n_size];
		for (int i = 0; i < n_size; i++)
		{
			if (i >= size) temp[i] = NULL;
			else temp[i] = arr[i];
		}
		arr = new int[n_size];
		for (int i = 0; i < n_size; i++)
		{
			arr[i] = temp[i];
		}
		arr[n_size - 1] = x;
		size = n_size;
	}
}

int vec::pop_back() {
	if (arr[size - 1] == NULL) {
		for (int i = 1; i <= size; i++)
		{
			if (arr[size - i] != NULL)
			{
				int k = arr[size - i];
				arr[size - i] = NULL;
				return k;
			}
		}
		return arr[0];
	}
	else {
		int k = arr[size - 1];
		arr[size - 1] = NULL;
		return k;
	}
}

int vec::back() {
	if (arr[size - 1] == NULL) {
		for (int i = 1; i < size; i++)
		{
			if (arr[size - i] != NULL)
			{
				int k = arr[size - i];
				return k;
			}
		}
		return -1;
	}
	else {
		int k = arr[size - 1];
		return k;
	}
}

int vec::get(int i) {
	if (i > size) return 0;
	if (arr[i - 1] == NULL) return 0;
	int x = arr[i - 1];
	return x;
}

void vec::set(int i, int x) {
	if (i > size) {
		int n_size = i;
		int * temp = new int[n_size];
		for (int j = 0; j < n_size; j++)
		{
			if (j >= size) temp[j] = NULL;
			else temp[j] = arr[j];
		}
		arr = new int[n_size];
		for (int j = 0; j < n_size; j++)
		{
			arr[j] = temp[j];
		}
		arr[n_size - 1] = x;
		size = n_size;
		//cout << "size: " << size << endl;
	}
	else if (i < 0) cout << "Invalid Address\n";
	else {
		arr[i - 1] = x;
	}
}


int vec::get_size() {
	return size;
}
