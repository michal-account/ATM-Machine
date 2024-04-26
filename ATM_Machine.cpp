#include <iostream>

using namespace std;

class User {
    public:
        string m_name;
        int m_password;
        int m_balance;
        User(const string name, int password, int balance) : m_name{name}, m_password{password}, m_balance{balance}
        {}

        void checkBalance() const {
            cout << "Balance: " << m_balance << " $" << endl;
        }

        void deposit(double amount) {
            m_balance += amount;
            //cout << "Deposit successfull. New balance: " << m_balance << " $" << endl;
        }

        bool withdraw(double amount) {
            if (amount <= m_balance) {
                m_balance -= amount;
                //cout << "Withdraw successfull. New balance: " << m_balance << " $" << endl;
                return true;
            } else {
                cout << "Not enough money in the account!" << endl;
                return false;
            }
        }

        void transfer(User& receiver, double amount) {
            if (withdraw(amount)) {
                receiver.deposit(amount);
                cout << "Transfer successfull!" << endl;
            } else {
                cout << "Transfer failed!" << endl;
            }
        }
};

bool logIn(User* user) {
    string name;
    int password;
    cout << "Enter your name: "; cin >> name;
    cout << "Enter your password: "; cin >> password;

    if (name == user->m_name && password == user->m_password) {
        system("cls");
        cout << "Login successfull!" << endl;
        return true;
    } else {
        cout << "Invalid name or password! Please try again." << endl;
        return false;
    }

}


void showMenu() {
    cout << "**********MENU**********" << endl;
    cout << "1. Check balance" << endl;
    cout << "2. Deposit" << endl;
    cout << "3. Withdraw" << endl;
    cout << "4. Transfer money to another user" << endl;
    cout << "5. Log Out" << endl;
    cout << "6. Quit" << endl;
    cout << "************************" << endl;
}

void accounts() {
    cout << "Hello. There are 2 possible accounts to Log In. Enter name and password to succsessfully log in: " << endl << endl;
    cout << "User1:" << endl << "Name: Peter" << endl << "Password: 1234" << endl;
    cout << "User2:" << endl << "Name: Mark" << endl << "Password: 5678" << endl << endl;
}

int main() 
{
    accounts();

    // check balance, deposit, withdraw, show menu
    int choice;
    int userChoice;

    User user1("Peter", 1234, 10000);
    User user2("Mark", 5678, 8000);

    User* loggedInUser = nullptr;
    bool loggedIn = false;

    do {
        if (!loggedIn) {
            cout << "Please log in: " << endl;
            cout << "Enter 1 for User1, 2 for User2: ";
            cin >> userChoice;
            if (userChoice == 1 && logIn(&user1)) {
                loggedIn = true;
                loggedInUser = &user1;
            } else if (userChoice == 2 && logIn(&user2)) {
                loggedIn = true;
                loggedInUser = &user2;
            } else {
                cout << "You couldn't log in. Please try again!" << endl;
            }
        } else {
            showMenu();

            cout << "Option: ";
            cin >> choice;
            system("cls");

            switch(choice) {
                case 1:
                    loggedInUser ->checkBalance();
                    break;
                case 2:
                    double depositAmount;
                    cout << "Deposit amount: ";
                    cin >> depositAmount;
                    loggedInUser ->deposit(depositAmount);
                    break;
                case 3:
                    double withdrawAmount;
                    cout << "Withdraw amount: ";
                    cin >> withdrawAmount;
                    loggedInUser ->withdraw(withdrawAmount);     
                    break;
                case 4:
                    double amountMoneyToTransfer;
                    if (loggedInUser == &user1) {
                        cout << "How much money would you like to send?" << endl;
                        cin >> amountMoneyToTransfer;
                        user1.transfer(user2, amountMoneyToTransfer);
                    } else if (loggedInUser == &user2){
                        cout << "How much money would you like to send?" << endl;
                        cin >> amountMoneyToTransfer;
                        user2.transfer(user1, amountMoneyToTransfer);
                    }                    
                    break;
                case 5:
                    loggedIn = false;
                    system("cls");
                    accounts();
                    break;
                case 6:
                    cout << "Exiting program..." << endl;
                    break;
                default:
                   cout << "Inavlid operation!" << endl;
            }       
        }
    } while(choice != 6);

    system("pause>0");
}