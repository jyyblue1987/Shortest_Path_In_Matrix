#include<iostream>
using namespace std;

int cost(int i, int j, int **weight, int rows, int cols, int *path) { // i is the row, j is the column
														   //base case
	if (j == 0)
	{
		path[j] = i;
		return weight[i][0];
	}
	// recursive call	
	int left = cost(i, j - 1, weight, rows, cols, path);
	int min = left;

	int *path1 = new int[j];
	int up = cost((i - 1 + rows) % rows, j - 1, weight, rows, cols, path1);
	if (up < min)
	{
		min = up;
		memcpy(path, path1, j * sizeof(int));
	}

	int down = cost((i + 1 + rows) % rows, j - 1, weight, rows, cols, path1);
	if (down < min)
	{
		min = down;
		memcpy(path, path1, j * sizeof(int));
	}

	delete path1;

	path[j] = i;

	// find min among left up down
	return min + weight[i][j];
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
	int weight1[][6] = {
		{ 3,4,1,2,8,6 },
		{ 6,1,8,2,7,4 },
		{ 5,9,3,9,9,5 },
		{ 8,4,1,3,2,6 },
		{ 3,7,2,8,6,4 }
	};

	int **weight = new int*[rows];
	for (int i = 0; i<rows; i++)
		weight[i] = new int[cols];


	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			weight[i][j] = weight1[i][j];

	int *path = new int[cols];
	int *path1 = new int[cols];

	// get the shortest path out of each cell on the right
	int min = 0;
	for (int i = 0; i < rows; i++)
	{		
		int cost1 = cost(i, cols - 1, (int **)weight, rows, cols, path1);
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
	delete path;
	delete path1;

	return 0;
}
