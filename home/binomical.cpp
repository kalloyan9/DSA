#include <iostream>
using namespace std;
#define maxN 100

//an array to hold the last line from the triangle
int line[maxN + 1];

int calc_n_over_k(int n, int k)
{
	//first element of the line is always 1...
	line[0] = 1;
	//generete lines
	for (int i = 1; i <= n; ++i){
                //generete lines members
                line[i] = 1; //...last also

                for(int j = i - 1; j; --j){
                        //every other element is a sum
                        //of the two numbers from the previous line
                        line[j] += line[j-1];
                }
	}

	//the result is the k-th element in the n-th line
	return line[k];
}


int main()
{
	int n, k;
	cin >> n >> k;
	cout << "binomical(" << n << ", " << k <<") = " << calc_n_over_k(n, k) << endl;

	return 0;
}
