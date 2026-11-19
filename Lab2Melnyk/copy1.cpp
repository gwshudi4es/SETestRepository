#include <iostream> // Input/Output Stream
#include <sstream> 
#include <iomanip> // Input/Output Manipulators
#include <cmath> // C++ Math
#include <limits> // Provides properties and extrema of fundamental data types
// Used here to determine the maximum buffer size for input stream cleaning
#include <string> // Introduces the std::string class and support functions
// To manage, store, and manipulate sequences of text characters easily.

using namespace std;

// Clears buffer if user inputs invalid characters when user chooses option "Retry"
void clearInputBuffer() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool readDouble(double& value) {
	string line;
	if (!getline(cin, line)) return false;

	istringstream iss(line);
	char leftover;
	if ((iss >> value) && !(iss >> leftover)) {
		return true;
	}
	return false;
}

bool readInt(int& value) {
	string line;
	if (!getline(cin, line)) return false;

	istringstream iss(line);
	char leftover;
	if ((iss >> value) && !(iss >> leftover)) {
		return true;
	}
	return false;
}

// When user inputs invalid character, program gives him a choice:
// Retry to enter the parameter or return to Main Menu
// Return true to retry, false to return to Main Menu
bool askRetryOrExit() {
	int choice = 0;
	while (true) {
		cout << "\nDo you want to retry, or exit to main menu?\n";
		cout << "1. Retry\n";
		cout << "2. Exit to the main menu\n";
		cout << "Select option [1-2]: ";

		if (readInt(choice)) {
			if (choice == 1) {
				return true; // Retry
			}
			else if (choice == 2) {
				return false; // Exit to the main menu
			}
		}
		cout << "[!] Invalid choice. Please enter 1 or 2.\n";
	}
}

// First parameter: Range start 'a'
bool inputParamA(double& outA) {
	while (true) {
		cout << "\nEnter range start (a): ";
		if (readDouble(outA)) {
			cout << "[OK] a = " << outA << "\n";
			return true;
		}
		else {
			cout << "[!] Error: Value of 'a' must be a valid number.\n";
			if (!askRetryOrExit()) {
				return false;
			}
		}
	}
}

// Second Parameter: Range end 'b'
bool inputParamB(double a, double& outB) {
	while (true) {
		cout << "\nEnter range end (b) [b >= a]: ";
		if (readDouble(outB)) {
			if (outB >= a) {
				cout << "[OK] b = " << outB << "\n";
				return true;
			}
			else {
				cout << "[!] Error: 'b' must be greater than or equal to 'a' (" << a << ").\n";
			}
		}
		else {
			cout << "[!] Error: Value of 'b' must be a valid number.\n";
		}

		if (!askRetryOrExit()) {
			return false;
		}
	}
}

// Third Parameter: Step
bool inputParamStep(double& outStep) {
	while (true) {
		cout << "\nEnter step (step > 0): ";
		if (readDouble(outStep)) {
			if (outStep > 0.0) {
				cout << "[OK] Step = " << outStep << "\n";
				return true;
			}
			else {
				cout << "[!] Error: Step must be strictly greater than 0.\n";
			}
		}
		else {
			cout << "[!] Error: Step must be a valid number.\n";
		}

		if (!askRetryOrExit()) {
			return false;
		}
	}
}

// Fourth Parameter: Parameter 'n'
bool inputParamN(int& outN) {
	while (true) {
		cout << "\nEnter parameter n (n >= 5): ";
		if (readInt(outN)) {
			if (outN >= 5) {
				cout << "[OK] n = " << outN << "\n";
				return true;
			}
			else {
				cout << "[!] Error: 'n' must be an integer >= 5.\n";
			}
		}
		else {
			cout << "[!] Error: 'n' must be an integer.\n";
		}

		if (!askRetryOrExit()) {
			return false;
		}
	}
}

// Mathematical calculation for my Variant #14 (Task 1 Branch)
double calculateY(double x, int n) {
	if (x < -4.0) {
		// Branch 1
		double prodPart = 1.0;
		for (int j = -1; j <= 3; j++) {
			prodPart *= (static_cast<double>(j + 2) * x);
		}

		double sumPart = 0.0;
		for (int i = 3; i <= n; i++) {
			sumPart += (12.0 * static_cast<double>(i) + (1.0 / x));
		}

		return prodPart + 3.0 * sumPart;
	}
	else {
		// Branch 2
		double totalSum = 0.0;
		for (int i = 0; i <= n + 1; i++) {
			double innerProd = 1.0;
			for (int j = 1; j <= n - 3; j++) {
				double term = static_cast<double>(i) + static_cast<double>(j) + (static_cast<double>(i) / static_cast<double>(j));
				innerProd *= pow(term, 2);
			}
			totalSum += innerProd;
		}
		return totalSum;
	}
}

// Execution of Option 1 "Calculate function in a range [a,b]"
void calculateFunction() {
	while (true) {
		cout << "\n=======================================================\n";
		cout << "                    INPUT PARAMETERS                   \n";
		cout << "=======================================================\n";

		double a = 0.0;
		double b = 0.0;
		double step = 0.0;
		int n = 0;

		// Step-by-step input with individual validation
		if (!inputParamA(a)) return;
		if (!inputParamB(a, b)) return;
		if (!inputParamStep(step)) return;
		if (!inputParamN(n)) return;

		// Print Results
		cout << "\n=======================================================\n";
		cout << "                  CALCULATION RESULTS                  \n";
		cout << "=======================================================\n";
		cout << setw(8) << "Step"
			<< setw(14) << "x"
			<< setw(20) << "y"
			<< setw(12) << "Branch" << "\n";
		cout << "-------------------------------------------------------\n";

		int stepNumber = 1;
		for (double x = a; x <= b + 1e-9; x += step) {
			double y = calculateY(x, n);
			string branch = (x < -4.0) ? "x < -4" : "x >= -4";

			cout << setw(8) << stepNumber++
				<< setw(14) << fixed << setprecision(4) << x
				<< setw(20) << fixed << setprecision(4) << y
				<< setw(12) << branch << "\n";
		}
		cout << "-------------------------------------------------------\n";
		cout << "Calculation completed.\n";

		// Question: "Do you want to retry, or exit to the main menu?"
		if (!askRetryOrExit()) {
			return; // Go back to the Main Menu
		}
		
	}
}

// Execution of Option 2 "View formula info & constraints"
void showFormulaInfo() {
	cout << "\n=======================================================\n";
	cout << "                  FORMULA INFORMATION                  \n";
	cout << "=======================================================\n";
	cout << " Variant 14 Task:\n";
	cout << " If x < -4:\n";
	cout << "    y = Prod(j=0..n, (j+2)*x) + 3 * Sum(i=0..n, 12i + 1/x)\n";
	cout << " If x >= -4:\n";
	cout << "    y = Sum(i=0..n-1, Prod(j=1..n, (i + j + i/j)^2))\n\n";
	cout << " Constraints:\n";
	cout << " - 'a' and 'b' must be real numbers with b >= a\n";
	cout << " - 'step' must be strictly greater than 0\n";
	cout << " - 'n' must be an integer >= 5\n";
	cout << "=======================================================\n";
	cout << "Press Enter to go to the main menu...";
	clearInputBuffer();
	cin.get();
}

int main() {
	int option = 0;

	while (true) {
		cout << "\n=======================================================\n";
		cout << "                       MAIN MENU                       \n";
		cout << "=======================================================\n";
		cout << " Welcome to My Function Tabulation Program!\n";
		cout << " This software calculates and tabulates a piecewise\n";
		cout << " mathematical function according to My Variant of #14\n";
		cout << " over a given range [a, b] with a fixed step.\n";
		cout << "\n";
		cout << " Features:\n";
		cout << " - Validates user input (range, step and parameter n)\n";
		cout << " - Computes sums and products for branched (x < -4 and x >= -4)\n";
		cout << " - Displays detailed step-by-step results in a formatted table\n";
		cout << "-------------------------------------------------------\n";
		cout << " Please choose an option:\n";
		cout << " (It's recommended to choose option #2 for the first time)\n";
		cout << " 1. Calculate function in a range [a, b]\n";
		cout << " 2. View formula info & constraints\n";
		cout << " 3. Exit\n";
		cout << "-------------------------------------------------------\n";
		cout << "Select option [1-3]: ";

		if (!readInt(option)) {
			cout << "[!] Error: Please, select an option between 1 and 3.\n";
			continue;
		}

		switch (option) {
		case 1:
			calculateFunction();
			break;
		case 2:
			showFormulaInfo();
			break;
		case 3:
			cout << "\n=======================================================\n";
			cout << " Thank You for using My program. I hope You had a great experience.\n";
			cout << " Have a nice day!\n";
			cout << "=======================================================\n";
			return 0; // Terminate program
		default:
			cout << "[!] Error: Invalid choice. Select 1, 2, or 3.\n";
			break;
		}
	}
}