#include <iostream>
#include <string>
using namespace std;

int main()
{
	// Declaring constants
	const int BASE_COST_BASE = 33;
	const int BASE_COST_LUXURY = 61;
	const double COST_PER_FIRST_HUNDRED = 0.27;
	const double COST_PER_NEXT_300_NONWINTER = 0.21;
	const double COST_PER_NEXT_300_WINTER = 0.27;
	const double COST_PAST_400 = 0.19;

	// Declaring parameter variables
	int odoStart;
	int odoEnd;
	int days;
	string name;
	string luxury;
	int month;

	// Declaring (and initializing if neccessary) values calculated by the program
	int milesDriven;
	double totalCost = 0;

	// Setting output decimal precision to two digits because the program is working with currency
	cout.setf(ios::fixed);
	cout.precision(2);

	// Asking for and setting the starting value of the odometer
	cout << "Odometer at start: ";
	cin >> odoStart;
	if (odoStart < 0) {
		cout << "---\nThe starting odometer reading must be nonnegative." << endl;
		return 1;
	}

	// Asking for and setting the ending value of the odometer
	cout << "Odometer at end: ";
	cin >> odoEnd;
	if (odoEnd < odoStart) {
		cout << "---\nThe final odometer reading must be at least as large as the starting reading." << endl;
		return 2;
	}

	// Asking for and setting the number of days the vehicle was rented for
	cout << "Rental days: ";
	cin >> days;
	if (days < 1) {
		cout << "---\nThe number of rental days must be positive." << endl;
		return 3;
	}

	// Asking for and setting the customer's name
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Using numeric_limits<streamsize>::max() to make sure the entire buffer is ignored
	cout << "Customer name: ";
	getline(cin, name);
	if (name == "") {
		cout << "---\nYou must enter a customer name." << endl;
		return 4;
	}

	// Asking for and setting whether or not the vehicle was a luxury vehicle
	cout << "Luxury car? (y/n): ";
	getline(cin, luxury);
	if (luxury != "y" && luxury != "n") {
		cout << "---\nYou must enter y or n." << endl;
		return 5;
	}

	// Asking for and setting the month rented during
	cout << "Month (1=Jan, 2=Feb, etc.): ";
	cin >> month;
	if (month < 1 || month > 12) {
		cout << "---\nThe month number must be in the range 1 through 12." << endl;
		return 6;
	}
	
	// Calculating the miles driven during the rental period
	milesDriven = odoEnd - odoStart;

	// Adding the base charge per day using a ternary operator to choose whether each day costs $33 or $61 based on the luxury string
	// Uses a ternary operator to determine whether to charge $33 or $61 per day
	totalCost += ((luxury == "y") ? BASE_COST_LUXURY : BASE_COST_BASE) * days;

	// Adding the additional cost based on miles driven

	/* Logic works by first checking if miles driven is over or under 100
	 * If it is under, add the cost of the miles and exit
	 * If it is over, add the cost of the first hundred miles
	 * then check if miles driven is under or over 400
	 * If it is under, add the cost of mile 100 to the ending mile and exit
	 * If it is over, add the cost of miles 100 to 400
	 * then add the cost of the remaining miles
	 */

	if (milesDriven > 100) {
		totalCost += 100 * COST_PER_FIRST_HUNDRED;
		if (milesDriven > 400) {
			totalCost += (300) * ((month == 12 || month <= 3) ? COST_PER_NEXT_300_WINTER : COST_PER_NEXT_300_NONWINTER);
			totalCost += (milesDriven - 400) * COST_PAST_400;
		} else {
			totalCost += (milesDriven - 100) * ((month == 12 || month <= 3) ? COST_PER_NEXT_300_WINTER : COST_PER_NEXT_300_NONWINTER);
		}
	} else {
		totalCost += milesDriven * COST_PER_FIRST_HUNDRED;
	}

	//Prints out the rental charge
	cout << "---\nThe rental charge for " << name << " is $" << totalCost << endl;
	return 0;
}