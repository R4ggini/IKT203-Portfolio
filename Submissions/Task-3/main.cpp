#include <iostream>
#include <string>

// 1.1: Natural numbers recursively
// Time: O(n), Space: O(n)
void printNaturalNumbers(int n) {
	if (n < 1) return; // base case

	printNaturalNumbers(n - 1);
	std::cout << n << std::endl;
}

// 1.2: Factorial calculation
// Time: O(n), Space: O(n)
int calculateFactorial(int n) {
	if (n < 0) return 0; // OoB failsafe
	if (n <= 1) return 1; // base case
	return n * calculateFactorial(n - 1);
}

// 2.3: Power calculation
// Time: O(log n), Space: O(log n)
int power(int base, int exponent) {
	if (exponent == 0) return 1; // base case

	int core = power(base, exponent / 2);
	if (exponent % 2 == 0) {
		return core * core;
	}
	return base * core * core;
}

// 2.4: Fibonacci sequence
// Time: O(2^n), Space: O(n)
/* This kind of recursion is inefficient as every +1 roughly doubles time complexity
 * fibonacci(n) calls fibonacci(n-1) and fibonacci(n-2). fibonacci(n-1) then calls
 * fibonacci(n-2) again. Avoiding calculating the same functions by storing values
 * would reduce time complexity to O(n).
 */
int fibonacci(int n) {
	if (n < 0) return 0;
	if (n <= 1) return n; // base case

	return fibonacci(n - 1) + fibonacci(n - 2);
}

// 2.5: Count occurences of a character in a string
// Time: O(n log n), Space: O(n)
int countOccurrences(std::string s, char c) {
	if (s.empty()) return 0; // failsafe if string is empty
	if (s.length() == 1) {	// base case
		if (s.front() == c) return 1;
		return 0;
	}

	int middle = static_cast<int>(s.length() / 2);
	std::string s1 = s.substr(0, middle);
	std::string s2 = s.substr(middle);

	return countOccurrences(s1, c) + countOccurrences(s2, c);
}

// 3.6: Largest element in an array
// Time O(n), Space: O(log n)
int findLargestElement(int arr[], int size) {
	if (size == 0) return 0; // safeguard
	if (size == 1) return arr[0]; // base case

	int midpoint = size / 2;

	int leftHalf = findLargestElement(arr, midpoint);
	int rightHalf = findLargestElement(arr + midpoint, size - midpoint);

	if (leftHalf > rightHalf) return leftHalf;
	return rightHalf;
}

// 3.7 ASCII table traversal
// Time: O(n), Space: O(n)
/* The output is first the stack building from the start char to the end char.
 * When it hits the base case the output reverses as the stack unwinds. */
void traverseAsciiTable(char start, char end) {
	if (start > end) return; // base case

	std::cout << start << std::endl; // printed on the way down
	traverseAsciiTable(start + 1, end);
	std::cout << start << std::endl; // printed as the stack unwinds
}

int main()
{
	{
		std::cout << "1.1: Natural numbers recursively" << std::endl;
		printNaturalNumbers(20);
	}

	{
		std::cout << "1.2: Factorial Calculation" << std::endl;
		std::cout << calculateFactorial(5) << std::endl;
	}

	{
		std::cout << "2.3: Power Calculation" << std::endl;
		std::cout << power(2, 8) << std::endl;
	}

	{
		std::cout << "2.4: Fibonacci Sequence" << std::endl;
		std::cout << fibonacci(5) << std::endl;
	}

	{
		std::cout << "2.5: Count occurences of a character in a string" << std::endl;
		std::cout << countOccurrences("Hello World!", 'l') << std::endl;
	}

	{
		std::cout << "3.6: Largest element in an array" << std::endl;
		int arr[100000];
		for (int& x : arr) x = rand() % 1000000;
		std::cout << findLargestElement(arr, 100000) << std::endl;
	}

	{
		std::cout << "3.7: ASCII table traversal" << std::endl;
		traverseAsciiTable('A', 'Z');
	}

	return 0;
}
