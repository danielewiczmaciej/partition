#include <iostream>

using namespace std;

bool check_prime(int n) {
	if(n==0||n==1)return false;
	for (int i = 2; i <= n/2; ++i) if (n % i == 0) return false;
	return true;
}

int* convert(int n) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (check_prime(i)) { count++; }
	}
	int* primes = new int[count + 1];
	primes[0] = n;
	int ind = 1;
	for (int i = 1; i <= n; i++) {
		if (check_prime(i)) {
			primes[ind] = i;
			ind++;
		}
	}
	return primes;
}

void part(int n, int k, int* output, int ind, int* primes) {
	int left = n - k;
	output[ind] = k;
	if (left == 0) {
		for (int i = 1; i < ind + 1; i++) {
			if (i != ind) cout << output[i] << "+";
			else cout << output[i];
		}
		cout << endl;
	}
	else if (left > 0) {
		for (int i = 1; i <= output[0]; i++) {
			if (primes[i] <= k) part(left, primes[i], output, ind + 1, primes);
		}
	}
}

void input(int n, int* numbers, int* dividers) {
	for (int i = 0; i < n; i++) {
		cin >> numbers[i];
		cin >> dividers[i];
	}
}

void resize(int* numbers, int* dividers, int* maxsize, int i, int* result) {
	if (numbers[i] - dividers[i] / 2 + 1 > *maxsize) {
		delete[] result;
		*maxsize = *maxsize * 2;
		result = new int[*maxsize];
	}
}

void finish(int* result, int* numbers, int* dividers, int* primes) {
	delete[] result;
	delete[] numbers;
	delete[] dividers;
	delete[] primes;
}

int main()
{
	int n;
	cin >> n;
	int maxsize = 100;

	int* numbers = new int[n];

	int* dividers = new int[n];

	int* result = new int[100];

	int* primes = convert(100);

	input(n, numbers, dividers);
	
	for (int i = 0; i < n; i++) {
		if (check_prime(dividers[i])) {
			if (primes[0] < dividers[i]) {
				delete[] primes;
				primes = convert(dividers[i]);
			}
			resize(numbers, dividers, &maxsize, i, result);
			int ind = 0;
			for (int j = 0; j < numbers[i]; j++) {
				if (primes[j] == dividers[i]) ind = j;
			}
			result[0] = ind;
			part(numbers[i], dividers[i], result, 1, primes);
		}
		
	}
	finish(result, numbers, dividers, primes);
	return 0;
}