#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <sys/resource.h>

using namespace std;

double get_cpu_time(){
	struct rusage ruse;
	getrusage(RUSAGE_SELF, &ruse);
	return (ruse.ru_utime.tv_sec+ruse.ru_utime.tv_usec/1000000.0 +
		ruse.ru_stime.tv_sec+ruse.ru_stime.tv_usec/1000000.0);
}

void swap(string A[], int b, int c){
//	cout << "LLL\n";
	string t = A[b];
	A[b] = A[c];
	A[c] = t;
}
int partition(string A[], int low, int high){
	int i = low - 1;
	int j = low;
	string pivot = A[high];
	while(j < high){
		if(A[j] < pivot){
			i++;
//			printf("	i: %s\n", i);	
			swap(A, j, i);
		}	
		j++;
//		printf("j: %d\n", j);
	}
	i++;
//	printf("FINAL i = %d\n", i);
	swap(A, i, high);
	return i;
}
void quicksort(string A[], int low, int high){
	int mid;
	if(low < high){
		mid = partition(A, low, high);
		quicksort(A, low, mid - 1);
		quicksort(A, mid + 1, high);
	}
}

void Merge(string A[], int low, int high, int mid){
	int i, j, k;
	string temp[high - low + 1];
	i = low;
	k = 0;
	j = mid + 1;
	while(i <= mid && j <= high){
		if (A[i] < A[j]){
			temp[k] = A[i];
			k++;
			i++;
		}
		else{
			temp[k] = A[j];
			k++;
			j++;
		}		
	}
//	cout << "PPP\n";
	while(i <= mid){
//		cout << "WWW\n";
		temp[k] = A[i];
//		cout << "XXX\n";
		k++;
		i++;
	}
//	cout << "VVV\n";
	while(j <= high){
		temp[k] = A[j];
		k++;
		j++;
	}
//	cout << "TTT\n";
	for(i = low; i <= high; i++){
		A[i] = temp[i-low];
//		cout << "QQQ\n";
	}
}
void MergeSort(string A[], int low, int high){
	int mid;
	if(low < high){
		mid = (low + high)/2;
		MergeSort(A, low, mid);
		MergeSort(A, mid + 1, high);
//		cout << "LLL\n";
		Merge(A, low, high, mid);
	}
}
const string AtoZ = "abcdefghijklmnopqrstuvwxyz";

string RandString(){
	int length = rand() % 10;		
	char str[13] = "            ";
	for(int j = 0; j < length; j++){
		int x = rand();
		x = x % 26;
		char y = AtoZ[x];
		str[j] = y;
	}
//	cout << str << "::::\n";
	return str;
}

void printArray(string A[], int size){
	int i;
	for(i = 0; i < size; i++){
		cout << i << ": " << A[i] << endl;
	}
}
int main(){
	cout << "How Large to make  Array?\n";
	int b;
	cin >> b;
	string Arr1[b];
	string Arr2[b];
	for(int i = 0; i < b; i++){
		Arr1[i] = RandString(); 
	}	
	for(int i = 0; i < b; i++){
		Arr2[i] = Arr1[i];
	}
//	cout << "Arr1:\n";

	double Q = get_cpu_time();
	quicksort(Arr1, 0, b-1);
	double Q2 = get_cpu_time();
	Q2 = Q2 -Q;
//	printArray(Arr1, b);


//	cout << "K\n";
	double M = get_cpu_time();
	MergeSort(Arr2, 0, b-1);		
	double M2 = get_cpu_time();
	M2 = M2 - M;
//	printArray(Arr2, b);
	cout << "Merge: " << M2 << endl;
	cout << "Quick: " << Q2 << endl;
}
