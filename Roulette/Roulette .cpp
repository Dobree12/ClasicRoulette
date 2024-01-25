#include <iostream>
#include <cstring>
#include<random>
using namespace std;

//roulette rules: black/red 2x
// even/odd ; 2x
//number ; 35x
//high/low ;2x
class Roulette {
public:
    int random;
    bool found = false;
    int option;
    void generateNumber() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 36);
        random = dis(gen);
    }
    void checkNumber(int random, bool& found) {
        int redArr[] = { 1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36 }; // search just in an array, and if it s not there, that means it's in the other one
        int blackArr[] = { 2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35 };
        int arrSize = sizeof(redArr) / sizeof(redArr[0]);
        for (int i = 0; i < arrSize; i++) {
            if (redArr[i] == random) {
                found = true; //  the number is red
                return;
            }// if found is still false then the number is black
        }
    }
    void playRedBlack(int& balance, int& bet) {

        char color;
        cout << "Red or Black:(R/B)" << endl;
        cin >> color;
        while (color != 'r' && color != 'R' && color != 'b' && color != 'B')
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Chose a valid option" << endl << "Red or Black:(R/B)" << endl;
            cin >> color;
        }
        if (random == 0)
        {
            cout << "Unlucky! The number was 0 (green)";
            balance -= bet;
            return;
        }
        if (((color == 'r') || (color == 'R')) && found)
        {
            cout << "You win!" << random << " the number was red " << endl;
            balance += bet;
        }
        else if (((color == 'r') || (color == 'R')) && !found)
        {
            cout << "You lost!" << random << " the number was black" << endl;
            balance -= bet;

        }
        else if (((color == 'b') || (color == 'B')) && !found)
        {
            cout << "You win!" << random << " the number was black" << endl;
            balance += bet;
        }
        else
            if (((color == 'b') || (color == 'B')) && found)
            {
                cout << "You lost!" << random << " the number was red " << endl;
                balance -= bet;
            }
    }
    void playEvenOdd(int& balance, int& bet) {
        char even_odd;
        cout << "Even/Odd (E/O)" << endl;
        cin >> even_odd;
        while (even_odd != 'E' && even_odd != 'e' && even_odd != 'O' && even_odd != 'o') {
            cout << "Chose a valid option" << endl << "Even / Odd (E/O)" << endl;
            cin >> even_odd;
        }
        if (random == 0)
        {
            cout << "Unlucky! The number was 0 (green)";
            balance -= bet;
            return;
        }
        if (even_odd == 'E' || even_odd == 'e' && (random % 2 == 0))
        {
            cout << "You win! " << random << " the number was even" << endl;
            balance += bet;
        }
        else
            if (even_odd == 'E' || even_odd == 'e' && (random % 2 == 1))
            {
                cout << "You lost! " << random << " the number was odd" << endl;
                balance -= bet;
            }
            else
                if (even_odd == 'O' || even_odd == 'o' && (random % 2 == 1))
                {
                    cout << "You win! " << random << " the number was odd" << endl;
                    balance += bet;
                }
                else
                    if (even_odd == 'O' || even_odd == 'o' && (random % 2 == 0))
                    {
                        cout << "You lost! " << random << " the number was even" << endl;
                        balance -= bet;
                    }
    }
    void playHighLow(int& balance, int& bet) {
        char hi_low;
        cout << "High/Low (H/L)" << endl;
        cin >> hi_low;
        while (hi_low != 'H' && hi_low != 'h' && hi_low != 'L' && hi_low != 'l') {
            cout << "Choose a valid option" << endl << "High / Low (H/L)" << endl;
            cin >> hi_low;
        }
        if ((hi_low == 'H' || hi_low == 'h') && (random <= 18)) {
            cout << "You lost! " << random << " the number was low" << endl;
            balance -= bet;
        }
        else if ((hi_low == 'H' || hi_low == 'h') && (random > 18)) {
            cout << "You win! " << random << " the number was high" << endl;
            balance += bet;
        }
        else if ((hi_low == 'L' || hi_low == 'l') && (random <= 18)) {
            cout << "You win! " << random << " the number was low" << endl;
            balance += bet;
        }
        else if ((hi_low == 'L' || hi_low == 'l') && (random > 18)) {
            cout << "You lost! " << random << " the number was high" << endl;
            balance -= bet;
        }
    }
    void playNumber(int& balance, int& bet) {
        int number;
        cout << " Choose the number to bet on (0 - 36)" << endl;
        cin >> number;
        while (number < 0 && number > 36)
        {
            cout << "Chose a valid option" << endl;
            cin >> number;
        }
        if (number == random)
        {
            cout << "You win! The number was: " << random << endl;
            balance = balance + 35 * bet;
        }
        else
        {
            cout << "You lost! The number was: " << random << endl;
            balance -= bet;
        }
    }
    void checkMessage(int& balance) {
        char choice;
        cout << "Your balance is :" << balance << "$" << endl;
        if (balance == 0)
        {
            cout << "You lost all your money.";
            exit(0);
        }
        cout << "Do you want to place another bet? (Y/N)" << endl;
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            system("CLS || clear");
            cout << "Balance:$ " << balance << endl;
        }
        else
            if (choice == 'N' || choice == 'n')
                exit(0);
    }
    void getUserInput(int& balance, int& bet) {
        generateNumber();
        checkNumber(random, found);
        cout << "1.Red/Black " << endl << "2.Even/Odd" << endl << "3.High/Low (1-18)/(19-36)" << endl << "4.Number" << endl << "Your option:";
        while (!(cin >> option) || (option < 1 || option > 4)) { 
            cin.clear();  // Clear the input error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter 1, 2, 3, or 4" << endl;
        }
        while (true) {
            cout << "How much do you wanna bet?" << endl;
            cout << ":$";
            cin >> bet;
            if (cin.fail() || bet <= 0) {
                cout << "Please enter a valid positive integer for the bet." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                break;
            }
        }
        if (bet > balance) {
            cout << "You don't have enough money, enter a valid amount " << endl;
            cout << "Your balance is: " << balance << "$" << endl;
            cout << ":$";
            cin >> bet;
        }
    }
    void runGame() {
        int balance;
        int bet, ok = 1;
        char balance2[101];
        
        cout << "Welcome to the Roulette Game made by Dobree12!" <<
            endl << "Please insert the amount you want play :$ ";
        cin.getline(balance2, 100);
        
       for (int i = 0; i < strlen(balance2); i++)
           if (!isdigit(balance2[i]))
               ok = 0;

       while (!ok) {
           ok = 1;
           cout << "the input is not valid please enter between 0-999$";
           cin.getline(balance2, 100);
           for (int i = 0; i < strlen(balance2); i++)
               if (!isdigit(balance2[i]))
                   ok = 0;
       }
        if (ok)
           balance = atoi(balance2);
       
        while (balance > 0) {
            getUserInput(balance, bet);
            switch (option) {
            case 1:
                playRedBlack(balance, bet);
                break;
            case 2:
                playEvenOdd(balance, bet);
                break;
            case 3:
                playHighLow(balance, bet);
                break;
            case 4:
                playNumber(balance, bet);
                break;
            }
            checkMessage(balance);
        }
    }
};

int main()
{
    Roulette game;
    game.runGame();

    return 0;
}