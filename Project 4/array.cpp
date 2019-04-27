#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value) {
	if (n < 0) // returns -1 if arguments are invalid
		return -1;
	for (int i = 0; i < n; i++) {
		a[i] += value; // appends value to each element
	}
	return n; // returns n as given
}

int lookup(const string a[], int n, string target) {
	for (int i = 0; i < n; i++) { // iterates through the array until n
		if (a[i] == target)
			return i; // returns the current index if it equals the target
	}
	return -1; // returns -1 if the target is not found (also catches invalid arguments)
}

int positionOfMax(const string a[], int n) {
	if (n <= 0)
		return -1; // returns -1 if arguments are invalid or no interesting elements
	int maxPos = 0; // sets the index of the largest value so far as the first index
	for (int i = 0; i < n; i++) {
		if (a[i] > a[maxPos])
			maxPos = i; // if a value is larger than the current max, change index of max to current index
	}
	return maxPos; // returns the index of the max value found
}

int rotateLeft(string a[], int n, int pos) {
	if (n < 0 || pos > n - 1 || pos < 0)
		return -1; // returns -1 if arguments are invalid
	string left = a[pos]; // stores the first value being overwritten
	for (int i = pos; i < n - 1; i++) {
		a[i] = a[i + 1]; // moves each value left one index
	}
	a[n - 1] = left; // resets the end of the array to equal the stored first value
	return pos; // returns original position of value moved to the end
}

int countRuns(const string a[], int n) {
	if (n < 0)
		return -1; // returns -1 if arguments are invalid
	if (n == 0)
		return 0; // returns 0 if size of given array is 0

	// counts number of times the element changes
	int changes = 0;
	for (int i = 0; i < n - 1; i++) {
		if (a[i] != a[i + 1])
			changes++;
	}
	return changes + 1; // returns number of changes + 1 which equals the number of runs
}

int flip(string a[], int n) {
	if (n < 0)
		return -1; // returns -1 if the arguments are invalid;
	for (int i = 0; i < n/2; i++) { // iterates through the first half of the array, swapping it with its respective member
		string temp = a[i];
		a[i] = a[n - i - 1];
		a[n - i - 1] = temp;
	}
	return n; // returns n as given
}

int differ(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0)
		return -1; // returns -1 if the arguments are invalid;
	for (int i = 0; i < n1; i++) {
		if (i > n2 - 1 || a1[i] != a2[i])
			return i; // returns the index if has surpassed n2 or if the arrays differ
	}
	return n1; // returns n1 if the function doesn't find any difference until n1
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0)
		return -1;
	if (n2 == 0)
		return 0;
	for (int i = 0; i < n1 - n2 + 1; i++) { // iterates through a1
		bool fail = false;
		for(int c = 0; c < n2; c++) {
			if(a1[i+c] != a2[c])
				fail = true;
		}
		if(!fail)
			return i;
	}
	return -1; // returns -1 if subsequence is not found (also catches invalid arguments)
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
	for (int i = 0; i < n1; i++) { // iterates through each element in a1
		for (int c = 0; c < n2; c++) { // iterates through each element in a2
			if (a1[i] == a2[c]) // compares each value of a2 to each value of a1
				return i; // returns the index of the first value of a2 found in a1
		}
	}
	return -1; // returns -1 if not found (also catches invalid arguments)
}

int divide(string a[], int n, string divider) {
	if (n < 0)
		return -1; // returns -1 if argument is invalid

	// bubble sort to order the array up through n
	bool sorted = false;
	while (!sorted) {
		sorted = true;
		for (int i = 0; i < n - 1; i++) {
			if (a[i] > a[i + 1]) {
				string temp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = temp;
				sorted = false;
			}
		}
	}

	// searches for when the values in the array equal or pass that of divider
	for (int i = 0; i < n; i++) {
		if (!(a[i] < divider))
			return i;
	}

	return n; // if the divider is greater than all values in the array, returns n
}

int testerFunction(int c) {

	string a1[] = { "hello", "goodbye", "goodbye", "yes", "no", "yes" };
	string a2[] = { "hello", "goodbye", "goodbye", "yes", "no", "yes" };
	string a3[] = { "goodbye", "goodbye", "yes", "no", "yes" };
	string a4[] = { "hello", "goodbye", "yes", "no", "yes" };
	string a5[] = { "yellow", "green", "blue" };

	switch (c) {
	case 1:
		if (appendToAll(a1, 0, "!") != 0 || a1[0] != "hello" || a1[1] != "goodbye") return c;
		break;
	case 2:
		if (appendToAll(a1, 2, "") != 2 || a1[0] != "hello" || a1[1] != "goodbye") return c;
		break;
	case 3:
		if (appendToAll(a1, -12, "#") != -1 || a1[0] != "hello" || a1[1] != "goodbye") return c;
		break;
	case 4:
		if (appendToAll(a1, 3, "yes") != 3 || a1[0] != "helloyes" || a1[3] != "yes") return c;
		break;
	case 5:
		if (lookup(a1, 0, "hello") != -1) return c;
		break;
	case 6:
		if (lookup(a1, 2, "") != -1) return c;
		break;
	case 7:
		if (lookup(a1, -12, "#") != -1) return c;
		break;
	case 8:
		if (lookup(a1, 6, "yes") != 3) return c;
		break;
	case 9:
		if (positionOfMax(a1, 0) != -1) return c;
		break;
	case 10:
		if (positionOfMax(a1, 1) != 0) return c;
		break;
	case 11:
		if (positionOfMax(a1, -12) != -1) return c;
		break;
	case 12:
		if (positionOfMax(a1, 6) != 3) return c;
		break;
	case 13:
		if (rotateLeft(a1, 0, 0) != -1 || a1[0] != "hello") return c;
		break;
	case 14:
		if (rotateLeft(a1, 3, 3) != -1 || a1[2] != "goodbye" || a1[3] != "yes") return c;
		break;
	case 15:
		if (rotateLeft(a1, -12, 2) != -1 || a1[0] != "hello") return c;
		break;
	case 16:
		if (rotateLeft(a1, 5, 2) != 2 || a1[1] != "goodbye" || a1[2] != "yes" || a1[4] != "goodbye") return c;
		break;
	case 17:
		if (countRuns(a1, 0) != 0) return c;
		break;
	case 18:
		if (countRuns(a1, 1) != 1) return c;
		break;
	case 19:
		if (countRuns(a1, -12) != -1) return c;
		break;
	case 20:
		if (countRuns(a1, 4) != 3) return c;
		break;
	case 21:
		if (flip(a1, 0) != 0 || a1[0] != "hello") return c;
		break;
	case 22:
		if (flip(a1, 1) != 1 || a1[0] != "hello") return c;
		break;
	case 23:
		if (flip(a1, -12) != -1 || a1[0] != "hello") return c;
		break;
	case 24:
		if (flip(a1, 5) != 5 || a1[0] != "no" || a1[4] != "hello" || a1[1] != "yes" || a1[2] != "goodbye") return c;
		break;
	case 25:
		if (differ(a1, 0, a2, 0) != 0) return c;
		break;
	case 26:
		if (differ(a1, 2, a2, 0) != 0) return c;
		break;
	case 27:
		if (differ(a1, 0, a2, 2) != 0) return c;
		break;
	case 28:
		if (differ(a1, 3, a2, 2) != 2) return c;
		break;
	case 29:
		if (differ(a1, 2, a2, 3) != 2) return c;
		break;
	case 30:
		if (differ(a1, 6, a4, 5) != 2) return c;
		break;
	case 31:
		if (subsequence(a1, 0, a2, 0) != 0) return c;
		break;
	case 32:
		if (subsequence(a1, 2, a2, 0) != 0) return c;
		break;
	case 33:
		if (subsequence(a1, 5, a4, 3) != -1) return c;
		break;
	case 34:
		if (subsequence(a1, 6, a3, 5) != 1) return c;
		break;
	case 35:
		if (subsequence(a1, 6, a4, 1) != 0) return c;
		break;
	case 36:
		if (subsequence(a1, -1, a3, 0) != -1) return c;
		break;
	case 37:
		if (subsequence(a1, 3, a3, -1) != -1) return c;
		break;
	case 38:
		if (lookupAny(a1, 0, a2, 0) != -1) return c; // check if this is correct
		break;
	case 39:
		if (lookupAny(a1, 2, a2, 0) != -1) return c; // same as 48
		break;
	case 40:
		if (lookupAny(a1, 6, a5, 3) != -1) return c;
		break;
	case 41:
		if (lookupAny(a1, 0, a2, 2) != -1) return c;
		break;
	case 42:
		if (lookupAny(a1, 6, a3, 4) != 1) return c;
		break;
	case 43:
		if (divide(a5, 0, "new") != 0) return c; // check if this is correct
		break;
	case 44:
		if (divide(a5, 3, "z") != 3) return c;
		break;
	case 45:
		if (divide(a5, 3, "a") != 0) return c;
		break;
	case 46:
		if (divide(a5, 3, "new") != 2 || (a5[0] != "blue" && a5[0] != "green") || (a5[1] != "blue" && a5[1] != "green") || a5[2] != "yellow") return c;
		break;
	default:
		cerr << "Invalid value given for case (" << c << ").\n";
	}

	return 0;
}

int main()
{
	bool fail = false;

	for (int i = 1; i <= 46; i++) {
		if (testerFunction(i) != 0) {
			cerr << "Test " << i << " failed.\n";
			fail = true;
		}
	}

	if (!fail)
		cerr << "---\nAll tests successfully completed." << endl;
	else
		cerr << "---\nAll tests completed with at least one failure." << endl;
}