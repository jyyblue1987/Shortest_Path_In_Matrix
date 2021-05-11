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

int cost(int i, int j, int **weight, int rows, int cols, int *path) { // i is the row, j is the column
														   //base case
	if (j == 0)
	{
		path[j] = i;
		return weight[i][0];
	}

	int x = j - 1;
	int y_array[3];
	y_array[0] = (i - 1 + rows) % rows;
	y_array[1] = i;
	y_array[2] = (i + 1 + rows) % rows;

	sort_array(y_array, 3);

	// recursive call	
	int *path1 = new int[j];
	int min = INT_MAX;

	for (int k = 0; k < 3; k++)
	{
		int y = y_array[k];
		int val = cost(y, x, weight, rows, cols, path1);
		
		if (val < min)
		{
			min = val;
			memcpy(path, path1, j * sizeof(int));
		}
	}

	delete path1;

	path[j] = i;

	// find min among left up down
	return min + weight[i][j];
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
	////int weight1[][6] = {
	////	{ 3,4,1,2,8,6 },
	////	{ 6,1,8,2,7,4 },
	////	{ 5,9,3,9,9,5 },
	////	{ 8,4,1,3,2,6 },
	////	{ 3,7,2,8,6,4 }
	////};

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
	delete path;
	delete path1;

	return 0;
}
