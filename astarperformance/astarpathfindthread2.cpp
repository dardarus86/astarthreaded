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
#include <thread>
#include <mutex>

const int width = 50;
const int height = 50;
const int numOfThreads = 25;

int xStart = 0;
int	yStart = 0;
int xEnd = 0;
int yEnd = 0;
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
int offset[8][2] =
{
	{-1, -1}, //NW
	{ 0, -1}, //N
	{ 1, -1}, //NE
	{ 1,  0}, //E
	{ 1,  1}, //SE
	{ 0,  1}, //S
	{-1,  1}, //SW
	{-1,  0}, //W
};

int progressCounter = 0;
bool foundExit = false;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;
std::thread threads[numOfThreads];
std::thread Testthread;
std::mutex mu;
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

void IncrementProgress()
{
	mu.lock();
	progressCounter++;
	std::cout << " Progress:" << progressCounter << std::endl;
	mu.unlock();
}

void SingleGridThread(int lowX, int highX, int lowY, int highY)
{
	for (int i = lowX; i < highX; i++)
	{
		for (int j = lowY; j < highY; j++)
		{
			gridArray[i][j].gCost = 1;
			gridArray[i][j].closed = false;
			gridArray[i][j].xPos = i;
			gridArray[i][j].yPos = j;
		}
	}

	for (int i = 0; i < (highY - lowY) * (highX - lowX) / 6; i++)
	{
		gridArray[rand() % 1 + ((highX - lowX) - 1)][rand() % 1 + ((highY - lowY) - 1)].closed = true;
	}
	IncrementProgress();

}


void SinglePathfindThread(int parentx, int parenty, int offsetx, int offsety)
{


	gridArray[parentx + offsetx][parenty + offsety].gCost += gridArray[xStart][yStart].gCost;
	//then calculate the hcost and add it to the g cost which gives me the f cost
	gridArray[parentx + offsetx][parenty + offsety].hCost = gridArray[parentx + offsetx][parenty + offsety].getHcost(xEnd, yEnd);
	gridArray[parentx + offsetx][parenty + offsety].setFcost(xEnd, yEnd);

	gridArray[parentx + offsetx][parenty + offsety].xParent = parentx;
	gridArray[parentx + offsetx][parenty + offsety].yParent = parenty;
	mu.lock();
	openList.push(gridArray[parentx + offsetx][parenty + offsety]);
	mu.unlock();

}

void initialiseGrid()
{
	int threadnum = 0;
	for (int i = 0; i < 25; i++)
	{
		threads[threadnum++] = std::thread(SingleGridThread, i * height / 25, (i + 1) * height / 25, 0, width);
	}

	for (int i = 0; i < numOfThreads; i++)
	{
		threads[i].join();
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

		  /*if (x > 0 && x < width - 1 && y > 0 && y < height - 1)
		  {*/

		int threadnum = 0;
		for (int i = 0; i < 8; i++)
		{
			if (x + offset[i][0] >= 0 && x + offset[i][0] < width && y + offset[i][1] >= 0 && y + offset[i][1] < height
				&& gridArray[x + offset[i][0]][y + offset[i][1]].closed == false)
				threads[threadnum++] = std::thread(SinglePathfindThread, x, y, offset[i][0], offset[i][1]);
		}

		for (int i = 0; i < threadnum; i++)
		{
			threads[i].join();
		}

		//get PQ.top
		gridArray[x][y].closed = true;
		//std::cout << "X,Y: " << openList.top().xPos << " , " << openList.top().yPos << std::endl;
		if (openList.empty()) {
			continue;
		}
		if (!openList.empty()) {
			x = openList.top().xPos;
			y = openList.top().yPos;
			openList.pop();
		}
		coord.push_back(currentPos);
		//	}

	}



}

typedef std::chrono::steady_clock the_clock;

int main()
{

	srand(time(NULL));
	int numOfSearches = 0;
	int totaliterations = 5;
	float averagems = 0;

	std::ofstream my_file("aStar1000threadonX.csv");
	for (int i = 0; i < totaliterations; i++)
	{
		// randomly select start and finish locations
		int xStart = rand() % 5 + 1;
		int	yStart = rand() % 5 + 1;
		int xEnd = width - rand() % 8 - 2;
		int yEnd = height - rand() % 8 - 2;
		clearPriorityQueue();

		initialiseGrid();
		the_clock::time_point start = the_clock::now();
		pathfind(xStart, yStart, xEnd, yEnd);
		the_clock::time_point end = the_clock::now();
		foundExit = false;
		auto time_taken = duration_cast<milliseconds>(end - start).count();

		char delemeter = ',';
		std::cout << "single ms = " << time_taken << std::endl;

		my_file << " Iteration: ";
		my_file << numOfSearches;
		my_file << " ms: ";
		my_file << time_taken << std::endl;

		averagems = averagems + time_taken;

		progressCounter = 0;
		numOfSearches++;
	}
	std::cout << "Average ms = " << averagems / totaliterations << std::endl;

}
