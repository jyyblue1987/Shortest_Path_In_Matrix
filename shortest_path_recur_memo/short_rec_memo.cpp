#include<iostream>
using namespace std;

#define MAX_VAL 2147483648

int cost(int i, int j, int **weight, int rows, int cols, int *path, int **memo, int ***memo_path) { // i is the row, j is the column
																	  //base case
	if (j == 0)
	{
		path[j] = i;
		return weight[i][0];
	}
	int x = 0, y = 0;
	// recursive call		
	x = j - 1;
	y = (i - 1 + rows) % rows;
	int up = memo[y][x];
	if (up == MAX_VAL)
		up = cost(y, x, weight, rows, cols, path, memo, memo_path);
	else
		memcpy(path, memo_path[y][x], j * sizeof(int));

	int min = up;

	int *path1 = new int[j];	
	
	y = i;
	int left = memo[y][x];
	if( up == MAX_VAL )
		up = cost(y, x, weight, rows, cols, path1, memo, memo_path);
	else
		memcpy(path1, memo_path[y][x], j * sizeof(int));

	if (up < min)
	{
		min = up;
		memcpy(path, path1, j * sizeof(int));
	}

	y = (i + 1 + rows) % rows;
	int down = memo[y][x];

	if (down == MAX_VAL)
		down = cost(y, x, weight, rows, cols, path1, memo, memo_path);
	else
		memcpy(path1, memo_path[y][x], j * sizeof(int));

	if (down < min)
	{
		min = down;
		memcpy(path, path1, j * sizeof(int));
	}

	delete path1;

	path[j] = i;
	memo[i][j] = min + weight[i][j];
	memcpy(memo_path[i][j], path, (j + 1) * sizeof(int));

	// find min among left up down
	return memo[i][j];
}
int main() {
	//int rows, cols;	
	//cin >> rows >> cols;
	//int **weight = new int*[rows];
	//for (int i = 0; i<rows; i++)
	//	weight[i] = new int[cols];
	//for (int i = 0; i<rows; i++)
	//	for (int j = 0; j<cols; j++)
	//		cin >> weight[i][j];

	int rows = 5, cols = 6;
	//int weight1[][6] = {
	//	{ 3,4,1,2,8,6 },
	//	{ 6,1,8,2,7,4 },
	//	{ 5,9,3,9,9,5 },
	//	{ 8,4,1,3,2,6 },
	//	{ 3,7,2,8,6,4 }
	//};

	int weight1[][6] = {
		{ 3,4,1,2,8,6 },
		{ 6,1,8,2,7,4 },
		{ 5,9,3,9,9,5 },
		{ 8,4,1,3,2,6 },
		{ 3,7,2,1,2,3 }
	};
	int **weight = new int*[rows];
	for (int i = 0; i<rows; i++)
		weight[i] = new int[cols];


	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			weight[i][j] = weight1[i][j];
	

	int *path = new int[cols];
	int *path1 = new int[cols];

	// memo
	int **memo = new int*[rows];
	for (int i = 0; i<rows; i++)
		memo[i] = new int[cols];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			memo[i][j] = MAX_VAL;

	// memo path
	int ***memo_path = new int**[rows];
	for (int i = 0; i<rows; i++)
		memo_path[i] = new int*[cols];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			memo_path[i][j] = new int[cols];

	// get the shortest path out of each cell on the right
	int min = 0;
	for (int i = 0; i < rows; i++)
	{
		int cost1 = cost(i, cols - 1, (int **)weight, rows, cols, path1, memo, memo_path);
		if (i == 0)
		{
			min = cost1;
			memcpy(path, path1, cols * sizeof(int));
		}
		else
		{
			if (cost1 < min)
			{
				min = cost1;
				memcpy(path, path1, cols * sizeof(int));
			}
		}
	}

	cout << min << endl;
	for (int i = 0; i < cols; i++)
	{
		if (i > 0)
			cout << " ";

		cout << (path[i] + 1);
	}

	cout << endl;

	for (int i = 0; i < rows; i++)
		delete weight[i];

	delete weight;

	for (int i = 0; i < rows; i++)
		delete memo[i];

	delete memo;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			delete memo_path[i][j];
		}
		delete memo_path[i];
	}

	delete memo_path;

	delete path;
	delete path1;

	return 0;
}
