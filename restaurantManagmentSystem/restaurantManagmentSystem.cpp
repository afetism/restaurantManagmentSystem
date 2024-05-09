// restaurantManagmentSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<vector>
#include<string>
#include<regex>
#include<fstream>
#include<Windows.h>
#include<conio.h>
#include <unordered_map>
#include <cstdlib>
#include<ctime>
#define disable_feature C4996
enum direction {
	UP = 72,
	DOWN = 80
};


using namespace std;
const int Red = FOREGROUND_RED | FOREGROUND_INTENSITY;
const int White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const int WhiteBackground = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
const int Yellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int Blue = FOREGROUND_BLUE | FOREGROUND_INTENSITY;  
const int BlueBackground = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
const int RedBackground = BACKGROUND_RED | BACKGROUND_INTENSITY;
const int YellowBackground = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;



void setConsoleColor(int textAttributes, int backgroundColor) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, textAttributes | backgroundColor);
}


#include"baseClasies.h"
#include"DerivedClassies.h"
#include"menu.h"
#include"AdminPanel.h"
#include"userPanel.h"
void menu() {
	srand(time(NULL));
	vector<Ingredient*>ingredient;
	Store store(ingredient);
	vector<Ingredient*>stk;
	Basket basket;
	Stock stock(1000, stk);
	
	stock.readFileBudget("budget.txt");
	stock.readFileStoreIngredient("stock.txt");
	int chooseUser = 0;
	vector<string> menuUser = displayMenu(RegisterMenu, chooseUser, "USER OR ADMIN");

	while (true) {
		int num = handleMenu(menuUser, chooseUser, "USER OR ADMIN");


		if (num == 13) {
			if (chooseUser == 0) {
				AdminPanel(stock, store);
			}
			else if (chooseUser == 1) {
				userMenu(stock,basket);
			}
			system("cls");
			displayMenu(RegisterMenu, chooseUser, "USER OR ADMIN");
		}

	}
}

int main()
{
	system("color 17");
	menu();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
