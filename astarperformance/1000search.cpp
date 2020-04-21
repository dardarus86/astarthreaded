

#include <iostream>
#include <iomanip>
#include <queue>
#include <list>
#include <string>
#include <math.h>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <fstream>

const int width = 1000;
const int height = 1000;
bool foundExit = false;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

struct Coord {
	Coord(int nx, int ny)
	{
		x = nx;
		y = ny;
	}

	int x;
	int y;
};
std::list<Coord> coord;

struct node
{
	node()
	{
		fCost = 0;
		gCost = 0;
		hCost = 0;
	}
	node(int x, int y, int xpar, int ypar, int g, int f, int h)
	{
		xPos = x, yPos = y, xParent = xpar, yParent = ypar, fCost = f, gCost = g, hCost = h;
	}
	int weght = 0;
	int xPos, yPos;
	int xParent, yParent;
	int fCost, gCost, hCost;
	bool closed;

	int getFcost() { return fCost; }

	void setFcost(int& xDest, int& yDest)
	{
		fCost = gCost + getHcost(xDest, yDest);
	}

	int getHcost(int& xDest, int& yDest)
	{
		int xD, yD, d;
		xD = xDest - xPos;
		yD = yDest - yPos;

		d = abs(xD) + abs(yD);
		return(d);

	}

};

node gridArray[width][height];
struct priorityOrder {
	;
	bool operator()(node& a, node& b)
	{
		return a.getFcost() > b.getFcost();
	}
};

std::priority_queue<node, std::vector<node>, priorityOrder> openList;

void clearPriorityQueue()
{
	while (!openList.empty())
		openList.pop();
}

void initialiseGrid(node grid[width][height])
{

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			gridArray[i][j].gCost = 1;
			gridArray[i][j].closed = false;
			gridArray[i][j].xPos = i;
			gridArray[i][j].yPos = j;
		}
	}

	for (int i = 0; i < (height * width) / 6; i++)
	{
		gridArray[rand() % 1 + (width - 1)][rand() % 1 + (height - 1)].closed = true;
	}


}

void pathfind(int xStart, int yStart, int xEnd, int yEnd)
{

	int x = xStart;
	int y = yStart;

	node* start = &gridArray[x][y];

	//gcost is already set in the grid initialization
	gridArray[x][y].hCost = start->getHcost(xEnd, yEnd);
	gridArray[x][y].setFcost(xEnd, yEnd);
	gridArray[x][y].fCost = start->getFcost();
	//need to set the fcost, hcost and gcost for the start node,

	while (!foundExit)
	{
		Coord currentPos = { x, y };
		if (x == xEnd && y == yEnd)
		{
			//std::cout << " you reached the end...woooo, your not as dumb as you thought! positive minset!!" << std::endl;
			foundExit = true;
			break;
		}
		/*---------------------
		  |	   |	 |      |
		  |  NW  |  N  |  NE  |
		  |X-1Y-1| Y-1 |X+1Y-1|
		  ---------------------
		  |      |     |      |
		  |   W  |  P  |  E   |
		  |X-1   |     |  X+1 |
		  ---------------------
		  |      |     |      |
		  |  SW  |  S  |  SE  |
		  |X-1Y+1| Y+1 |X+1Y+1|
		  ---------------------*/

		if (x > 0 && x < width - 1 && y > 0 && y < height - 1)
		{

			//then i need to increase the gcost for the nodes next to it by its cost
			//NW
			if (gridArray[x - 1][y - 1].closed == false)
			{
				gridArray[x - 1][y - 1].gCost += gridArray[xStart][yStart].gCost;
				//then calculate the hcost and add it to the g cost which gives me the f cost
				gridArray[x - 1][y - 1].hCost = gridArray[x - 1][y - 1].getHcost(xEnd, yEnd);
				gridArray[x - 1][y - 1].setFcost(xEnd, yEnd);

				gridArray[x - 1][y - 1].xParent = x;
				gridArray[x - 1][y - 1].yParent = y;
				openList.push(gridArray[x - 1][y - 1]);
			}
			//N
			if (gridArray[x][y - 1].closed == false)
			{
				gridArray[x][y - 1].gCost += gridArray[xStart][yStart].gCost;
				gridArray[x][y - 1].hCost = gridArray[x][y - 1].getHcost(xEnd, yEnd);
				gridArray[x][y - 1].setFcost(xEnd, yEnd);
				gridArray[x][y - 1].xParent = x;
				gridArray[x][y - 1].yParent = y;

				openList.push(gridArray[x][y - 1]);
			}

			//NE
			if (gridArray[x + 1][y - 1].closed == false)
			{
				gridArray[x + 1][y - 1].gCost += gridArray[xStart][yStart].gCost;
				gridArray[x + 1][y - 1].hCost = gridArray[x + 1][y - 1].getHcost(xEnd, yEnd);
				gridArray[x + 1][y - 1].setFcost(xEnd, yEnd);
				gridArray[x + 1][y - 1].xParent = x;
				gridArray[x + 1][y - 1].yParent = y;

				openList.push(gridArray[x + 1][y - 1]);
			}

			//E
			if (gridArray[x + 1][y].closed == false)
			{
				gridArray[x + 1][y].gCost += gridArray[xStart][yStart].gCost;
				gridArray[x + 1][y].hCost = gridArray[x + 1][y].getHcost(xEnd, yEnd);
				gridArray[x + 1][y].setFcost(xEnd, yEnd);
				gridArray[x + 1][y].xParent = x;
				gridArray[x + 1][y].yParent = y;

				openList.push(gridArray[x + 1][y]);
			}

			//SE
			if (gridArray[x + 1][y + 1].closed == false)
			{
				gridArray[x + 1][y + 1].gCost += gridArray[xStart][yStart].gCost;
				gridArray[x + 1][y + 1].hCost = gridArray[x + 1][y + 1].getHcost(xEnd, yEnd);
				gridArray[x + 1][y + 1].setFcost(xEnd, yEnd);
				gridArray[x + 1][y + 1].xParent = x;
				gridArray[x + 1][y + 1].yParent = y;

				openList.push(gridArray[x + 1][y + 1]);
			}

			//S
			if (gridArray[x][y + 1].closed == false)
			{
				gridArray[x][y + 1].gCost += gridArray[xStart][yStart].gCost;
				gridArray[x][y + 1].hCost = gridArray[x][y + 1].getHcost(xEnd, yEnd);
				gridArray[x][y + 1].setFcost(xEnd, yEnd);
				gridArray[x][y + 1].xParent = x;
				gridArray[x][y + 1].yParent = y;

				openList.push(gridArray[x][y + 1]);
			}

			//SW
			if (gridArray[x - 1][y + 1].closed == false)
			{
				gridArray[x - 1][y + 1].gCost += gridArray[xStart][yStart].gCost;
				gridArray[x - 1][y + 1].hCost = gridArray[x - 1][y + 1].getHcost(xEnd, yEnd);
				gridArray[x - 1][y + 1].setFcost(xEnd, yEnd);
				gridArray[x - 1][y + 1].xParent = x;
				gridArray[x - 1][y + 1].yParent = y;

				openList.push(gridArray[x - 1][y + 1]);
			}

			//W
			if (gridArray[x - 1][y].closed == false)
			{
				gridArray[x - 1][y].gCost += gridArray[xStart][yStart].gCost;
				gridArray[x - 1][y].hCost = gridArray[x - 1][y].getHcost(xEnd, yEnd);
				gridArray[x - 1][y].setFcost(xEnd, yEnd);
				gridArray[x - 1][y].xParent = x;
				gridArray[x - 1][y].yParent = y;

				openList.push(gridArray[x - 1][y]);
			}
		}

		//get PQ.top
		gridArray[x][y].closed = true;
		//std::cout << "X,Y: " << openList.top().xPos << " , " << openList.top().yPos << std::endl;
		x = openList.top().xPos;
		y = openList.top().yPos;
		openList.pop();
		coord.push_back(currentPos);

	}



}

typedef std::chrono::steady_clock the_clock;

int main()
{

	srand(time(NULL));
	int numOfSearches = 0;
	int totaliterations = 100;
	float averagems = 0;

	std::ofstream my_file("aStar1000nothread.csv");
	for (int i = 0; i < totaliterations; i++)
	{
		// randomly select start and finish locations
		int xStart = rand() % 5 + 1;
		int	yStart = rand() % 5 + 1;
		int xEnd = rand() % 8 + 990;
		int yEnd = rand() % 8 + 990;
		clearPriorityQueue();
		the_clock::time_point start = the_clock::now();
		initialiseGrid(gridArray);
		the_clock::time_point end = the_clock::now();
		pathfind(xStart, yStart, xEnd, yEnd);

		foundExit = false;
		auto time_taken = duration_cast<milliseconds>(end - start).count();

		char delemeter = ',';
		std::cout << "single ms = " << time_taken << std::endl;

		my_file << " Iteration: ";
		my_file << numOfSearches;
		my_file << " ms: ";
		my_file << time_taken << std::endl;

		averagems = averagems + time_taken;


		numOfSearches++;
	}
	std::cout << "Average ms = " << averagems / totaliterations << std::endl;

}
