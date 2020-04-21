#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

// initializing the function that will be called in main
void spin();

int bet = 0; int credits = 1000; // for the money used in game
int column1[] = { 1,2,3,4,5 }; int column2[] = { 1,2,3,4,5 }; int column3[] = { 1,2,3,4,5 }; // for the 3 rotating columns
int width = 3, height = 3; // H and W of 3x3 array for outputting columns
int n = 5; // used for the size of the array in the kbhits loops below
int qkey; int wkey; int ekey; int key_press; // variables for the kbhits for Q W and E
bool qHit = false; bool wHit = false; bool eHit = false; // bools create for the while loop to see if all 3 columns have stopped rotating
string winner = " "; // string used to output text when comparing columns for winning prizes


bool playAgain = true; bool slotFinished = false; // for the two while loops that make up the main core of the game
char playAgainchar; // for the "do you want to play again Y or N input

void ShowConsoleCursor(bool showFlag) // SetConsoleCursorInfo function to hide the cursor from jumping all over the screen
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void setCursorPosition() // resetting the cursors positiong back to 0,0 instead of using the system("CLS") command that cause blinking of the screen
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { 0,0 };
	SetConsoleCursorPosition(hOut, coord);

}

void spin() // main function used in this program that controls almost everything
{



	while (playAgain == true) // if the user types Y or y then this loop continues, if not exits and goes to a goodbye message
	{// start of playAgain loop
	 //first graphic
		cout << "                                                                                                                                                 " << endl;
		cout << "                                                                                                                                                 " << endl;
		cout << "                                                          3 matching numbers = x20 credits | 2 matching numbers = x5 credits                  " << endl;
		cout << "                                                               NmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmN                         " << endl;
		cout << "                                                              N---:::::::::::::::::::::::::::::::::::::::::::::::--:::-.y                        " << endl;
		cout << "                                                              d./++///++++++++++++++++++++++++++++++++++++++///++//+++/.s                        " << endl;
		cout << "                                                              h./++//                                        //++//+++/.s                        " << endl;
		cout << "                                                              h./++//      You have " << credits << " credits left        //++//+++/.s          " << endl;
		cout << "                                                              h./++//                                        //++//+s+/.s   NysooyN              " << endl;
		cout << "                                                              h./++++++++++++++++++++++++++++++++++++++++++++++++//+h+/.s  d-oyyyo-d             " << endl;
		cout << "                                                              h./++////////////////////////////////////////////++//+h+/.s N:+hhhhh+/             " << endl;
		cout << "                                                              h./++//++++++++++++++++++++++++++++++++++++++++//++//+h+/.os--+yhhhs-h             " << endl;
		cout << "                                                              h./++//+:          :+:          :+:          :+//++//+h+/..-+o+::oosm              " << endl;
		cout << "                                                              h./++//+:    1     :+:     3    :+:     5    :+//++//+h+/:/++:-sN                  " << endl;
		cout << "                                                              h./++//+:          :+:          :+:          :+//++//+s/+++::yN                    " << endl;
		cout << "                                                              h./++//+:    2     :+:     4    :+:     4    :+//++//+oo+:-yN                      " << endl;
		cout << "                                                              h./++//+:          :+:          :+:          :+//++//+s+/.s                        " << endl;
		cout << "                                                              h./++//+:    3     :+:     5    :+:     2    :+//++//+y+/.s                        " << endl;
		cout << "                                                              h./++//+:          :+:          :+:          :+//++//+h+/.s                        " << endl;
		cout << "                                                              h./++/:+++++++++++++++++++++++++++++++++++++++///++//+h+/.s                        " << endl;
		cout << "                                                              h./+++///////////////////////////////////////////++//+h+/.s                        " << endl;
		cout << "                                                              N--/++++++++++++++++++++++++++++++++++++++++++++++++//+h+/.s                       " << endl;
		cout << "                                                            h--/+++/+++++++++/+++/+++++++++/+++/+++++++++/++++++///+s+/.s                        " << endl;
		cout << "                                                         Nh/.:/+++/+hyyyyyyyy+/+/ohyyyyyyyy+/+/ohyyyyyyyy//+++///+++++/.s                        " << endl;
		cout << "                                                        s:.:/+++++++sssssssss+/+++sssssssss+/++osssssssss//++//+++++++/.s                        " << endl;
		cout << "                                                       h`:/+++++++++++++++++++++++++++++++++++++++++++++++++//++++++++/.s                        " << endl;
		cout << "                                                       /-/++++++++++++++++++++++++++++++++++++++++++++++++++//++++++++/.s                        " << endl;
		cout << "                                                       `//++++++++++++++++++++++++++++++++++++++++++++++++++//++++++++/.s                        " << endl;
		cout << "                                                      m`//+++++////////////////////////////////////////+++++//++++++++/.s                        " << endl;
		cout << "                                                      d./+++++//                                      /+++++//++++++++/.s                        " << endl;
		cout << "                                                      d./+++++//                                      :+++++//++++++++/.s                        " << endl;
		cout << "                                                      h./+++++//                                      :+++++//+++++++//.s                        " << endl;
		cout << "                                                      y./+++++++++++++++++++++++++++++++++++++++++++++/+++++//+++++//:-/m                        " << endl;
		cout << "                                                      d`//++++++++++++++++++++++++++++++++++++++++++++++++++//++///:-+d                          " << endl;
		cout << "                                                      N.://////////////////////////////////////////////////////:-:od                             " << endl;
		cout << "                                                       NdyysssssssssssssssssssssssssssssssssssssssssssssssssssydN                                " << endl;
		cout << "                                                                                                                                                 " << endl;
		cout << "                                                                                                                                                 " << endl;
		cout << "                                                                                                                                                 " << endl;
		cout << "                                                                   How much would you like to bet? - ";
		cin >> bet;

		while (slotFinished == false) // will only become true if all 3 buttons have been pushes. Otherwise continues to loops the columns giving the impression of rotating
		{
			setCursorPosition(); // setting cursor to 0,0 to overwrite
			if (_kbhit())
			{
				key_press = _getch();// kbhits used to stop the columns rotating
				if (key_press == 'Q' || key_press == 'q')
					qHit = true;
				if (key_press == 'W' || key_press == 'w')
					wHit = true;
				if (key_press == 'E' || key_press == 'e')
					eHit = true;
			}

			if (qHit != true) // when qhit is not true continue this loop
			{
				int temp = column1[0], i;
				for (i = 0; i < n - 1; i++)
					column1[i] = column1[i + 1];
				column1[i] = temp;

			}

			if (wHit != true)// when whit is not true continue this loop
			{
				int temp1 = column2[0], j;
				for (j = 0; j < n - 1; j++)
					column2[j] = column2[j + 1];
				column2[j] = temp1;
			}

			if (eHit != true)// when ehit is not true continue this loop
			{
				int temp2 = column3[0], k;
				for (k = 0; k < n - 1; k++)
					column3[k] = column3[k + 1];
				column3[k] = temp2;
			}

			int mainSlotArray[3][3] = // The array used to create the outputs in the slot machine below
			{
				{ column1[1],column2[1],column3[1] },
			{ column1[2],column2[2],column3[2] },
			{ column1[3],column2[3],column3[3] },
			};

			// second graphic 
			cout << "                                                                                                                                                 " << endl;
			cout << "                                                                         Press Q, W and E to stop each column                                    " << endl;
			cout << "                                                          3 matching numbers = x20 credits | 2 matching numbers = x5 credits                     " << endl;
			cout << "                                                               NmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmN                         " << endl;
			cout << "                                                              N---:::::::::::::::::::::::::::::::::::::::::::::::--:::-.y                        " << endl;
			cout << "                                                              d./++///++++++++++++++++++++++++++++++++++++++///++//+++/.s                        " << endl;
			cout << "                                                              h./++//                                        //++//+++/.s                        " << endl;
			cout << "                                                              h./++//      Money = " << credits - bet << "   Bet = " << bet << "            //++//+++/.s                         " << endl;
			cout << "                                                              h./++//                                        //++//+s+/.s   NysooyN              " << endl;
			cout << "                                                              h./++++++++++++++++++++++++++++++++++++++++++++++++//+h+/.s  d-oyyyo-d             " << endl;
			cout << "                                                              h./++////////////////////////////////////////////++//+h+/.s N:+hhhhh+/             " << endl;
			cout << "                                                              h./++//++++++++++++++++++++++++++++++++++++++++//++//+h+/.os--+yhhhs-h             " << endl;
			cout << "                                                              h./++//+:          :+:          :+:          :+//++//+h+/..-+o+::oosm              " << endl;
			cout << "                                                              h./++//+:" << "    " << mainSlotArray[0][0] << "     :+:    " << mainSlotArray[0][1] << "     :+:     " << mainSlotArray[0][2] << "    :+//++//+h+/:/++:-sN                    " << endl;
			cout << "                                                              h./++//+:          :+:          :+:          :+//++//+s/+++::yN                    " << endl;
			cout << "                                                              h./++//+:" << "    " << mainSlotArray[1][0] << "     :+:    " << mainSlotArray[1][1] << "     :+:     " << mainSlotArray[1][2] << "    :+//++//+oo+:-yN                        " << endl;
			cout << "                                                              h./++//+:          :+:          :+:          :+//++//+s+/.s                        " << endl;
			cout << "                                                              h./++//+:" << "    " << mainSlotArray[2][0] << "     :+:    " << mainSlotArray[2][1] << "     :+:     " << mainSlotArray[2][2] << "    :+//++//+y+/.s                          " << endl;
			cout << "                                                              h./++//+:          :+:          :+:          :+//++//+h+/.s                        " << endl;
			cout << "                                                              h./++/:+++++++++++++++++++++++++++++++++++++++///++//+h+/.s                        " << endl;
			cout << "                                                              h./+++///////////////////////////////////////////++//+h+/.s                        " << endl;
			cout << "                                                              N--/++++++++++++++++++++++++++++++++++++++++++++++++//+h+/.s                       " << endl;
			cout << "                                                            h--/+++/+++++++++/+++/+++++++++/+++/+++++++++/++++++///+s+/.s                        " << endl;
			cout << "                                                         Nh/.:/+++/+hyyyyyyyy+/+/ohyyyyyyyy+/+/ohyyyyyyyy//+++///+++++/.s                        " << endl;
			cout << "                                                        s:.:/+++++++sssssssss+/+++sssssssss+/++osssssssss//++//+++++++/.s                        " << endl;
			cout << "                                                       h`:/+++++++++++++++++++++++++++++++++++++++++++++++++//++++++++/.s                        " << endl;
			cout << "                                                       /-/++++++++++++++++++++++++++++++++++++++++++++++++++//++++++++/.s                        " << endl;
			cout << "                                                       `//++++++++++++++++++++++++++++++++++++++++++++++++++//++++++++/.s                        " << endl;
			cout << "                                                      m`//+++++////////////////////////////////////////+++++//++++++++/.s                        " << endl;
			cout << "                                                      d./+++++//                                      /+++++//++++++++/.s                        " << endl;
			cout << "                                                      d./+++++//                                      :+++++//++++++++/.s                        " << endl;
			cout << "                                                      h./+++++//                                      :+++++//+++++++//.s                        " << endl;
			cout << "                                                      y./+++++++++++++++++++++++++++++++++++++++++++++/+++++//+++++//:-/m                        " << endl;
			cout << "                                                      d`//++++++++++++++++++++++++++++++++++++++++++++++++++//++///:-+d                          " << endl;
			cout << "                                                      N.://////////////////////////////////////////////////////:-:od                             " << endl;
			cout << "                                                       NdyysssssssssssssssssssssssssssssssssssssssssssssssssssydN                                " << endl;
			cout << "                                                                                                                                                 " << endl;
			cout << "                                                                                                                                                 " << endl;
			cout << "                                                                                                                                                 " << endl;
			cout << "                                                                                                                                                 " << endl;


			if (qHit == true && wHit == true && eHit == true) // if all 3 buttons have been pressed, set slotfinished to true to exit the while loop
			{
				slotFinished = true;
			}


		}// while slotFinished loop end
		setCursorPosition(); // setting to 0,0 clearing the previous output

							 // following functions are used to check winning criteria. if the middle row all match then jackpot, if only 2 match then mini jackpot and if no match then sorry message
		if (column1[2] == column2[2] && column2[2] == column3[2])
		{
			credits = (bet * 20) + credits;
			winner = " YOU WON THE JACKPOT!!!";
		}

		else if (column1[2] == column2[2] || column2[2] == column3[2] || column1[2] == column3[2])
		{
			credits = (bet * 5) + credits;
			winner = " Good Job, mini jackpot";
		}
		else
		{
			winner = " Sorry, no prize this time";
		}
		if (credits < 1) // when the user has no money give them a sorry message and end program
		{
			system("CLS");
			cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t Sorry bro but your all out of cash. Sucks to be you but thanks for coming! \n\n\n\n\n\n\n\n" << endl;
			break;
		}
		// third graphic
		cout << "                                                                                                                                                 " << endl;
		cout << "                                                                                                                                                 " << endl;
		cout << "                                                                           " << winner << "                                                      " << endl;
		cout << "                                                               NmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmN                         " << endl;
		cout << "                                                              N---:::::::::::::::::::::::::::::::::::::::::::::::--:::-.y                        " << endl;
		cout << "                                                              d./++///++++++++++++++++++++++++++++++++++++++///++//+++/.s                        " << endl;
		cout << "                                                              h./++//                                        //++//+++/.s                        " << endl;
		cout << "                                                              h./++//                                        //++//+++/.s                        " << endl;
		cout << "                                                              h./++//                                        //++//+s+/.s   NysooyN              " << endl;
		cout << "                                                              h./++++++++++++++++++++++++++++++++++++++++++++++++//+h+/.s  d-oyyyo-d             " << endl;
		cout << "                                                              h./++////////////////////////////////////////////++//+h+/.s N:+hhhhh+/             " << endl;
		cout << "                                                              h./++//++++++++++++++++++++++++++++++++++++++++//++//+h+/.os--+yhhhs-h             " << endl;
		cout << "                                                              h./++//+:          :+:          :+:          :+//++//+h+/..-+o+::oosm              " << endl;
		cout << "                                                              h./++//+:" << "    " << column1[1] << "     :+:    " << column2[1] << "     :+:     " << column3[1] << "    :+//++//+h+/:/++:-sN                    " << endl;
		cout << "                                                              h./++//+:          :+:          :+:          :+//++//+s/+++::yN                    " << endl;
		cout << "                                                              h./++//+:" << "    " << column1[2] << "     :+:    " << column2[2] << "     :+:     " << column3[2] << "    :+//++//+oo+:-yN                        " << endl;
		cout << "                                                              h./++//+:          :+:          :+:          :+//++//+s+/.s                        " << endl;
		cout << "                                                              h./++//+:" << "    " << column1[3] << "     :+:    " << column2[3] << "     :+:     " << column3[3] << "    :+//++//+y+/.s                          " << endl;
		cout << "                                                              h./++//+:          :+:          :+:          :+//++//+h+/.s                        " << endl;
		cout << "                                                              h./++/:+++++++++++++++++++++++++++++++++++++++///++//+h+/.s                        " << endl;
		cout << "                                                              h./+++///////////////////////////////////////////++//+h+/.s                        " << endl;
		cout << "                                                              N--/++++++++++++++++++++++++++++++++++++++++++++++++//+h+/.s                       " << endl;
		cout << "                                                            h--/+++/+++++++++/+++/+++++++++/+++/+++++++++/++++++///+s+/.s                        " << endl;
		cout << "                                                         Nh/.:/+++/+hyyyyyyyy+/+/ohyyyyyyyy+/+/ohyyyyyyyy//+++///+++++/.s                        " << endl;
		cout << "                                                        s:.:/+++++++sssssssss+/+++sssssssss+/++osssssssss//++//+++++++/.s                        " << endl;
		cout << "                                                       h`:/+++++++++++++++++++++++++++++++++++++++++++++++++//++++++++/.s                        " << endl;
		cout << "                                                       /-/++++++++++++++++++++++++++++++++++++++++++++++++++//++++++++/.s                        " << endl;
		cout << "                                                       `//++++++++++++++++++++++++++++++++++++++++++++++++++//++++++++/.s                        " << endl;
		cout << "                                                      m`//+++++////////////////////////////////////////+++++//++++++++/.s                        " << endl;
		cout << "                                                      d./+++++//                                      /+++++//++++++++/.s                        " << endl;
		cout << "                                                      d./+++++//                                      :+++++//++++++++/.s                        " << endl;
		cout << "                                                      h./+++++//                                      :+++++//+++++++//.s                        " << endl;
		cout << "                                                      y./+++++++++++++++++++++++++++++++++++++++++++++/+++++//+++++//:-/m                        " << endl;
		cout << "                                                      d`//++++++++++++++++++++++++++++++++++++++++++++++++++//++///:-+d                          " << endl;
		cout << "                                                      N.://////////////////////////////////////////////////////:-:od                             " << endl;
		cout << "                                                       NdyysssssssssssssssssssssssssssssssssssssssssssssssssssydN                                " << endl;
		cout << "                                                                                                                                                 " << endl;
		cout << "                                                                                                                                                 " << endl;
		cout << "                                                                                                                                                 " << endl;



		cout << "                                                              Do you want to play again? Y for yes N for no - ";
		cin >> playAgainchar;

		if (playAgainchar == 'Y' || playAgainchar == 'y')
		{
			slotFinished = false;
			qHit = false;
			wHit = false;
			eHit = false;
			playAgain = true;
			credits = credits - bet;
			system("CLS");

		}
		if (playAgainchar == 'N' || playAgainchar == 'n')
		{
			playAgain = false;
			system("CLS");
		}




	} // while playagain end




} // void spin end

int main()
{

	system("mode 200"); // setting window size for console
	ShowConsoleCursor(false); // hiding the cursor



	spin(); // calling the main function for the game

	cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t Your end credits were: " << credits << ". Thank you for playing! \n\n\n\n\n\n\n\n"; // if user hits no, exit loop and display this message

	return 0;

}


