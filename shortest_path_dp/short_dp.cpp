#include <iostream>
#include <limits>
using namespace std;

void sort_array(int index[], int len)
{
	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			if (index[i] > index[j])
			{
				int temp = index[i];
				index[i] = index[j];
				index[j] = temp;
			}
		}
	}
}

int main() {
	int rows, cols;	
	cin >> rows >> cols;
	int **weight = new int*[rows];
	for (int i = 0; i<rows; i++)
		weight[i] = new int[cols];
	for (int i = 0; i<rows; i++)
		for (int j = 0; j<cols; j++)
			cin >> weight[i][j];

	//int rows = 5, cols = 6;
	//int weight1[][6] = {
	//	{ 3,4,1,2,8,6 },
	//	{ 6,1,8,2,7,4 },
	//	{ 5,9,3,9,9,5 },
	//	{ 8,4,1,3,2,6 },
	//	{ 3,7,2,8,6,4 }
	//};

	//int weight1[][6] = {
	//	{ 3,4,1,2,8,6 },
	//	{ 6,1,8,2,7,4 },
	//	{ 5,9,3,9,9,5 },
	//	{ 8,4,1,3,2,6 },
	//	{ 3,7,2,1,2,3 }
	//};

	//int **weight = new int*[rows];
	//for (int i = 0; i<rows; i++)
	//	weight[i] = new int[cols];


	//for (int i = 0; i < rows; i++)
	//	for (int j = 0; j < cols; j++)
	//		weight[i][j] = weight1[i][j];


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
	int y_array[3];
	for (int j = 1; j < cols; j++)
	{
		// complete next column
		for (int i = 0; i < rows; i++)
		{
			// up
			int x = j - 1;

			y_array[0] = (i - 1 + rows) % rows;
			y_array[1] = i;
			y_array[2] = (i + 1 + rows) % rows;

			sort_array(y_array, 3);

			int min = INT_MAX;
			for (int k = 0; k < 3; k++)
			{
				int y = y_array[k];

				int value = memo[y][x];
				if( value < min )
				{
					min = value;
					memcpy(path, memo_path[y][x], j * sizeof(int));
				}
			
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

	for (int i = 0; i < cols; i++)
	{
		if (i > 0)
			cout << " ";

		cout << (path[i] + 1);
	}

	cout << endl;

	cout << min << endl;


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
