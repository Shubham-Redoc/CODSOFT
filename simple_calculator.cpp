#include <iostream>

using namespace std;

void calculator() {
    double num1, num2;
    char operation;
    
    cout << "Enter the first number: ";
    cin >> num1;
    
    cout << "Enter an operation (+, -, *, /): ";
    cin >> operation;
    
    cout << "Enter the second number: ";
    cin >> num2;
    
    switch (operation) {
        case '+':
            cout << "Result: " << num1 + num2 << endl;
            break;
        case '-':
            cout << "Result: " << num1 - num2 << endl;
            break;
        case '*':
            cout << "Result: " << num1 * num2 << endl;
            break;
        case '/':
            if (num2 != 0) {
                cout << "Result: " << num1 / num2 << endl;
            } else {
                cout << "Error: Division by zero is undefined." << endl;
            }
            break;
        default:
            cout << "Error: Invalid operation." << endl;
            break;
    }
}

int main() {
    char choice;
    do {
        calculator();
        cout << "Do you want to perform another calculation? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    
    return 0;
}
