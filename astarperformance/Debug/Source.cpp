#include <iostream>
#include <time.h>
#include <conio.h>
#include <chrono>
#include <windows.h>
using namespace std;

int credit = 10000;
int answer;
int nr;
int qkey; int wkey; int ekey; int key_press;
bool oneHit = false; bool twohit = false; bool threehit = false;
int arr[3][3]; //initializing my main array
int holder[3][3]; //initializing array which temporarily holds values

void setCursorPosition() // resetting the cursors positiong back to 0,0 instead of using the system("CLS") command that cause blinking of the screen
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { 0,0 };
	SetConsoleCursorPosition(hOut, coord);

}

void replace_Numbers() //replaces numbers in the field using for-loops and putting the previous value into a different array
{
	holder[0][0] = arr[0][0];
	holder[0][1] = arr[0][1];
	holder[0][2] = arr[0][2];
	holder[1][0] = arr[1][0];
	holder[1][1] = arr[1][1];
	holder[1][2] = arr[1][2];
	holder[2][0] = arr[2][0];
	holder[2][1] = arr[2][1];
	holder[2][2] = arr[2][2];


	for (int k = 0; k < 3; k++)
	{
		arr[0][k] = arr[2][k];
		cout << arr[0][k] << " ";
	}
	cout << endl;

	for (int l = 0; l < 3; l++)
	{
		holder[1][l] = arr[0][l];
		cout << arr[1][l] << " ";
	}
	cout << endl;

	for (int m = 0; m < 3; m++)
	{
		holder[2][m] = arr[1][m];
		cout << arr[2][m] << " ";
	}
	cout << endl;

	Sleep(100);
}

void detect_Key()
{

}

void spacing(int spaces) //spaces between text and playing field, also used in clearing screen
{
	for (int g = 0; g < spaces; g++)
	{
		cout << "" << endl;
	}
}

void message()
{
	cout << "Each spin removes 1000 credit.Getting three in a row in the middle column gives 10000 credit, while getting 2 in a row  gives 5000." << endl;
	cout << "Press 1 to stop first column from rotating, 2 to stop second and 3 to stop third. Before starting, press 4 to exit game with current credit or enter any other number to continue." << endl;
}

int main()
{
	srand((unsigned)time(NULL));

	bool game_running = false;

	cout << "Welcome to the game!" << endl;
	cout << "Enter credit to play with. Minimum 1000." << endl; //letting player determine the length of the game
	cin >> credit;
	spacing(1);

	while (credit >= 1000) //only plays while the player has credit
	{
		message();

		cin >> answer;

		if (answer == 4)
		{
			game_running = true;
			break; //game immediately ends when player enters 4
		}
		else
		{
			game_running = false;
		}


		spacing(4);

		for (int a = 0; a < 3; a++) //creating initial playing field of random numbers
		{
			for (int b = 0; b < 3; b++)
			{
				int random = rand() % 3;
				arr[a][b] = random;
				cout << arr[a][b];
				cout << " ";
			}
			cout << endl;
		}

		//Sleep(2000);
		while (!game_running)
		{
		

			if (_kbhit())
			{
				key_press = _getch();// kbhits used to stop the columns rotating
				if (key_press == 1)
					oneHit = true;
				if (key_press == 2)
					twohit = true;
				if (key_press == 3)
					threehit = true;
			}

			while (!oneHit && !twohit && !threehit)
			{
				for (int c = 0; c < 9; c++)
				{
					char(8);
				}
				replace_Numbers(); //creating new playing field and printing it out

				detect_Key();
				Sleep(100);
				setCursorPosition();
			}

			if (arr[0][1] == arr[1][1] || arr[0][1] == arr[2][1] || arr[1][1] == arr[2][1])
			{
				credit += 4000; //increases credit by 4000 compared to before spin (taking into account the 1000 lost for spinning)
			}
			else if (arr[0][1] == arr[1][1] && arr[0][1] == arr[2][1])
			{
				credit += 9000; //increases credit by 9000 compared to before spin (taking into account the 1000 lost for spinning)
			}
			else
			{
				credit -= 1000; //removes 1000 credit for spinning
			}

		}

		cout << "Your current credit is " << credit << "." << endl;
		return 0;
	}
	cout << "You have exited the game with " << credit << " credit." << endl;
}