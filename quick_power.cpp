#include <iostream>
using namespace std;

template <typename T>
T quick_power(const T& elem, size_t pow)
{
	if (!pow){
		return T(); //default constructor for complex types needed
	}
	if (pow == 1){
		return elem;
	}

	if (pow & 1){ //odd pow
		return elem * quick_power(elem, pow - 1);
	}else{ //even pow
		T res = quick_power(elem, pow / 2);
		return res * res;
	}
}


int main ()
{
	double a;
	size_t p;
	cin >> a >> p;
	cout << a << '^' << p << '=' << quick_power(a, p) << endl;
	
	int b;
	cin >> b >> p;
	cout << b << '^' << p << '=' << quick_power(b, p) << endl;

	return 0;
}
