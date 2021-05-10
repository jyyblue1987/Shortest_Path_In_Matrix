#include<iostream>
using namespace std;

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

	// memo
	int **memo = new int*[rows];
	for (int i = 0; i<rows; i++)
		memo[i] = new int[cols];

	// memo path
	int ***memo_path = new int**[rows];
	for (int i = 0; i<rows; i++)
		memo_path[i] = new int*[cols];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			memo_path[i][j] = new int[j + 1];

	// complete first column
	for (int i = 0; i < rows; i++)
	{
		memo_path[i][0][0] = i;
		memo[i][0] = weight[i][0];
	}


	int min = 0;
	for (int j = 1; j < cols; j++)
	{
		// complete next column
		for (int i = 0; i < rows; i++)
		{
			// up
			int x = j - 1;
			int y = (i - 1 + rows) % rows;

			int up = memo[y][x];
			int min = up;
			memcpy(path, memo_path[y][x], j * sizeof(int));

			// left
			y = i;
			int left = memo[y][x];
			if (left < min)
			{
				min = left;
				memcpy(path, memo_path[y][x], j * sizeof(int));
			}

			// down
			y = (i + 1 + rows) % rows;
			int down = memo[y][x];
			if (down < min)
			{
				min = down;
				memcpy(path, memo_path[y][x], j * sizeof(int));
			}

			memo[i][j] = min + weight[i][j];
			path[j] = i;
			memcpy(memo_path[i][j], path, (j + 1) * sizeof(int));
		}			
	}

	// check last column
	int x = cols - 1;
	min = memo[0][x];
	memcpy(path, memo_path[0][x], cols * sizeof(int));
	for (int i = 0; i < rows; i++)
	{
		if (memo[i][x] < min)
		{
			min = memo[i][x];
			memcpy(path, memo_path[i][x], cols * sizeof(int));
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

	return 0;
}
