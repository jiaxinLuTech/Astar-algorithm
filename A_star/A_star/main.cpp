#include "A_star.h"
#include <iostream>
using namespace A_star;

#define Max_X 10
#define Max_Y 10

void printMap(char map[Max_X][Max_Y], int width, int height)
{
	for (int i = 0; i<width; i++)
	{
		for (int j = 0; j<height; j++)
		{
			printf("%c\t", map[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	char mapdata[Max_X][Max_Y] =
	{
		{ '1','0','0','1','0','1','1','1','1','1' },
		{ '1','1','1','1','0','1','1','1','1','1' },
		{ '0','0','0','1','0','1','1','1','1','1' },
		{ '1','0','0','1','0','1','1','1','1','0' },
		{ '1','1','1','1','0','1','1','1','1','1' },
		{ '1','1','0','0','1','1','1','1','1','1' },
		{ '1','1','1','1','1','1','1','1','1','1' },
		{ '1','0','0','1','1','1','1','1','1','1' },
		{ '1','1','0','0','1','1','1','1','1','1' },
		{ '1','0','1','1','1','1','1','1','1','1' },
	};

	printMap(mapdata, Max_X, Max_Y);
	Point size(Max_X, Max_Y);
	Map Map_;
	Map_.Set_size(size);
	for (int i = 0; i<Max_X; i++)
	{

		for (int j = 0; j<Max_Y; j++)
		{
			Point point(i, j); 
			if (mapdata[i][j] == '0')
			{
				Map_.addCollision(point);
			}
		}
	}
	Map_.Set_diag_move(true);
	vector<Point> path;
	path = Map_.findPath({ 0, 0 }, { 4, 1});
	for (auto& coordinate : path) {
		std::cout << coordinate.x << " " << coordinate.y << "\n";
	}
	system("pause");
}
