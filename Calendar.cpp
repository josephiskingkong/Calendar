/*********************
*                    *
*   Perelygin Egor   *
*       PI-221       *
*      Calendar      *
*                    *
**********************/

#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

bool isLeapYear (int year) {
	if (year % 400 == 0 or year % 4 == 0) {
        return true;
    } else {
        return false;
    }
}

bool isDigitInput (int input){
	if (isdigit(input)) {
		return true;
	}
	return false; 
}

int dayNumber(int day, int month, int year) {
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1,
                       4, 6, 2, 4 };
    year -= month < 3;
    return ( year + year/4 - year/100 +
             year/400 + t[month-1] + day) % 7;
}

string getMonthName(int monthNumber) {
    string months[] = {"-January--", "-February-", "--March---",
                       "--April---", "---May----", "---June---",
                       "---July---", "--August--", "September-",
                       "-October--", "-November-", "-December-"
                      };
 
    return (months[monthNumber]);
}

int main() {
    
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Console colorize
    
    start:
    int year = 0;
    
    SetConsoleTextAttribute(hConsole, 7); // White
    printf("Enter the year: ");
    cin >> year;
    
    while(cin.fail()) { // Numbers only verification
    	cin.clear();
    	cin.ignore(INT_MAX, '\n');
    	SetConsoleTextAttribute(hConsole, 4); // Red
    	printf("ERROR: You can only enter numbers. Please, try again. \n\n");
    	goto start;
	}

    if (year <= 0) { // Year greater then 0 verification
    	SetConsoleTextAttribute(hConsole, 4); // Red
        printf("ERROR: Invalid year, it should be greater then 0. Please, try again.\n\n");
		goto start;
    }
    
	SetConsoleTextAttribute(hConsole, 160); // Black on green background
    cout << "\n---------Calendar of " << year << "----------\n";    
    SetConsoleTextAttribute(hConsole, 2); // Green
    
	int daysInMonth[12] = { 
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 
    };
    if (isLeapYear(year)) {
        daysInMonth[1] += 1;
    }
    
    int days;
    int current = dayNumber (0, 1, year);
    
    for (int monthIndex = 0; monthIndex < 12; monthIndex++) {
        
        days = daysInMonth[monthIndex];
        
        printf("\n------------%s-------------\n",
               getMonthName (monthIndex).c_str());
        printf("  Mon  Tue  Wed  Thu  Fri  Sat  Sun\n");
 
        int emptyCellMultiplier;
        for (emptyCellMultiplier = 0; emptyCellMultiplier < current; emptyCellMultiplier++)
            printf("     ");
 
        for (int outputDay = 1; outputDay <= daysInMonth[monthIndex]; outputDay++) {
            printf("%5d", outputDay);
 
            if (++emptyCellMultiplier > 6) {
                emptyCellMultiplier = 0;
                printf("\n");
            }
        }
 
        if (emptyCellMultiplier)
            printf("\n");

        current = emptyCellMultiplier;
    }
    printf("\n");
    
    question:   
    SetConsoleTextAttribute(hConsole, 7);  // White
    char answer;
    printf("Do you want to continue? Enter y/n : ");
    cin >> answer;
    
    if (answer == 'y' or answer == 'n') {
    	if (answer == 'y') {
    		system("cls");
    		goto start;
		}
		if (answer == 'n') {
			SetConsoleTextAttribute(hConsole, 14); // Light yellow
			printf("\nSee you later!\n\n");
			SetConsoleTextAttribute(hConsole, 7); // White
			system("pause");
		}
	} else {
		SetConsoleTextAttribute(hConsole, 4); // Red
		printf("\nERROR: Wrong answer! It should be y or n.\n\n");
		goto question;
	}
}
