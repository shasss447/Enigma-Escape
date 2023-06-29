#pragma once
#include<vector>
using namespace std;
void createmap(vector<vector<int>>&grid,int &numRows,int &numCols)
{
	grid.resize(numRows, vector<int>(numCols,10000));
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			if (i == 0 || j == 0||i==numRows-1||j==numCols-1)
				grid[i][j] = 10000;
		}
	}

    // Setting valid cells
    grid[0][1] = 1;
    grid[1][1] = 1;
    grid[2][1] = 1;
    grid[2][2] = 1;
    grid[2][3] = 1;
    grid[2][4] = 1;
    grid[3][4] = 1;
    grid[4][4] = 1;
    grid[5][4] = 1;
    grid[6][4] = 1;
    grid[7][4] = 1;
    grid[8][4] = 1;
    grid[9][4] = 1;
    grid[9][3] = 1;
    grid[9][2] = 1;
    grid[9][1] = 1;
    grid[10][1] = 1;
    grid[11][1] = 1;
    grid[11][2] = 1;
    grid[11][3] = 1;
    grid[11][4] = 1;
    grid[11][5] = 1;
    grid[11][6] = 1;
    grid[11][7] = 1;
    grid[11][8] = 1;
    grid[11][9] = 1;
    grid[11][10] = 1;
    grid[11][11] = 1;
    grid[11][12] = 1;
    grid[11][13] = 1;
    grid[11][14] = 1;
    grid[11][15] = 1;
    grid[11][16] = 1;
    grid[11][17] = 1;
    grid[11][18] = 1;
    grid[11][19] = 1;
    grid[11][20] = 1;
    grid[11][21] = 1;
    grid[11][22] = 1;
    grid[11][23] = 1;
    grid[11][24] = 1;
    grid[11][25] = 1;
    grid[11][26] = 1;
    grid[11][27] = 1;
    grid[11][28] = 1;
    grid[11][29] = 1;
    grid[11][30] = 1;
    grid[11][31] = 1;
    grid[12][31] = 1;
    grid[13][31] = 1;
    grid[14][31] = 1;
    grid[15][31] = 1;
    grid[16][31] = 1;
    grid[17][31] = 1;
    grid[18][31] = 1;
    grid[19][31] = 1;
    grid[20][31] = 1;
    grid[21][31] = 1;
    grid[22][31] = 1;
    grid[22][30] = 1;
    grid[22][29] = 1;
    grid[22][28] = 1;
    grid[22][27] = 1;
    grid[22][26] = 1;
    grid[22][25] = 1;
    grid[22][24] = 1;
    grid[22][23] = 1;
    grid[22][22] = 1;
    grid[22][21] = 1;
    grid[22][20] = 1;
    grid[22][19] = 1;
    grid[22][18] = 1;
    grid[22][17] = 1;
    grid[22][16] = 1;
    grid[22][15] = 1;
    grid[22][14] = 1;
    grid[22][13] = 1;
    grid[22][12] = 1;
    grid[22][11] = 1;
    grid[22][10] = 1;
    grid[22][9] = 1;
    grid[22][8] = 1;
    grid[22][7] = 1;
    grid[22][6] = 1;
    grid[22][5] = 1;
    grid[22][4] = 1;
    grid[22][3] = 1;
    grid[22][2] = 1;
    grid[22][1] = 1;
    grid[23][1] = 1;

	
}