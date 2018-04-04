#include"myvec.h"

using namespace std;

class bigint {
protected:
	int size;
	vec number;
public:
	bigint() {
		size = 0;
		number = vec::vec(0);
	}
	bigint(int s) {
		size = int(floor(log10(s))) + 1;
		number = vec::vec(size);
		for (int i = 1; i <= size; i++)
			number.set(i, s / int(pow(10, i-1)) % 10);
	}
	bigint(string val) {
		size = val.length();
		number = vec::vec(size);
		for (int i = 1; i <= size; i++)
			number.set(i , val[size - i] - '0');
	}
	void print() {
		for (int i = 0; i < size; i++) {
			int x = number.get(size - i);
			cout << x;
		}
		cout << endl;
	}
	void copy(bigint x) {
		size = x.number.get_size();
		number = x.number;
	}
	void add(bigint x) {
		int a = size;
		int b = x.size;
		int one = 0;
		int t = size;
		if(x.size > size) t = x.size;
		for (int i = 1; i <= t; i++) {
				a = number.get(i); if (number.get(i) == NULL) a = 0;
				b = x.number.get(i); if (x.number.get(i) == NULL) b = 0;
				a = a + b + one;
				if (a > 9 && i != t) {
					one = 1;
					a = a - 10;
				}
				else one = 0;
				if (a >= 10 && i == t) {
					t += 1;
					a = a - 10;
					one = 1;
				}
				number.set(i, a);
				size = i;
		}
	}
	void subtract(bigint x) {
		int carry = 0;
		int a = 0;
		int b = 0;
		if (x.size > size) {
			cout << "Unable to Subtract" << endl;
			return;
		}
		if (x.size == size) {
			int i = 0;
			while(a == b) {
				b = x.number.get(x.size - i);
				a = number.get(size - i);
				i += 1;
				if (b > a) {
					cout << "Unable to Subtract" << endl;
					return;
				}
			}
		}
		for (int i = 1; i <= size; i++) {
			a = number.get(i) - carry; 
			b = x.number.get(i); 
			if (a == -1) {
				a = 9;
				carry = 1;
			}
			else if (b > a) {
				a = a + 10;
				carry = 1;
			}
			else carry = 0;
			a = a - b;
			number.set(i, a);
		}
		int k = 0;
		while(number.get(size - k) == 0) {
			k++;
		}
		size = size - k;
	}
	int compare(bigint x) {
		int a = number.get_size();
		int b = x.number.get_size();
		if (a > b) return 1;
		if (a < b) return -1;
		int k = 0;
		while (k < size) {
			a = number.get(size-k);
			b = x.number.get(size-k);
			if (a > b) return 1;
			if (a < b) return -1;
			k++;
		}
		return 0;
	}
	void multiply(int x) {
		int a = 0;
		int b = 0;
		int t = 0;
		int go = size;
		int carry = 0;
		int add_carry = 0;
		bigint hold(x);
		bigint sum;
		t = int(floor(log10(x))) + 1;
		for (int j = 1; j <= t; j++) {
			b = int(x / pow(10, j - 1)) % 10;
			//cout << "b = " << b << endl;
			go = size;
			for (int i = 1; i <= go; i++) {
				a = number.get(i); 
				if (number.get(i) == NULL) a = 0;
				a = a * b + carry;
				//cout << "a = " << a << endl;
				if (a < 10) {
					//cout << "carry reset" << endl;
					carry = 0;
				}
				if (a > 9) {
					if (i == size) 
						go++;
					carry = a / 10;
					a = a % 10;
				}
				hold.number.set(i + add_carry, a);
				hold.size = i + add_carry;
				//cout << "holdsize :" << hold.size << endl;
			}
			//cout << "hold :"; hold.print();
			add_carry++;
			sum.add(hold);
			//cout << "sum: "; sum.print();
			hold.number.clear();
		}
		number = sum.number;
		size = sum.size;
	}
	void shift(int x) {
		for (int i = 1; i <= x; i++) {
			multiply(10);
		}
	}
	void printsize(){
		cout << number.vec::get_size() << endl;
	}
}; 

void main() {
	bigint a(1000);
	bigint b(999);
	a.subtract(b);
	a.print();

	int x;
	cin >> x;
}


/*
void main() {
	int s = 0;
	cout << "Build Your Vector\n";
	cout << "Size?  ";
	cin >> s;
	vec vect(s);
	cout << "Enter " << s << " entries\n";
	int input;
	for (int i = 0; i < s; i++)
	{
		cin >> input;
		vect.set(i + 1, input);
	}
	cout << "C to clear, E to check if empty, P to pushback" <<
		endl << "O to popback,  B to get last number"
		<< endl << "G to get entry by address, S to set new entries"
		<< endl << "A to get size, X to exit\n";
	while (true) {
		char c;
		int inp;
		int entry;
		int output;
		cin >> c;
		if (c == 'c' || c == 'C')
			vect.clear();
		if (c == 'E' || c == 'e')
		{
			cout << vect.is_empty() << endl;
		}
		if (c == 'P' || c == 'p')
		{
			cout << "Entry to pushback: ";
			cin >> inp;
			vect.push_back(inp);
		}
		if (c == 'O' || c == 'o')
		{
			output = vect.pop_back();
			cout << output << endl;
		}
		if (c == 'B' || c == 'b')
		{
			output = vect.back();
			cout << output << endl;
		}
		if (c == 'G' || c == 'g')
		{
			cout << "Get what address: ";
			cin >> inp;
			output = vect.get(inp);
			cout << output << endl;
		}
		if (c == 'S' || c == 's')
		{
			cout << "Address: ";
			cin >> inp;
			cout << "Entry: ";
			cin >> entry;
			vect.set(inp, entry);
		}
		if (c == 'a' || c == 'A')
		{
			cout << vect.get_size() << endl;;
		}
		if (c == 'x' || c == 'X') return;
	}
}
*/

