#pragma once
#include<math.h>

//FUNCTION TO RETURN THE MANHATTEN DISTANCE
int heuristic(int curr_x, int curr_y, int& d_x, int& d_y)
{
    return abs(curr_x - d_x) + abs(curr_y - d_y);
}

//FUNCTION TO CHECK VALIDITY OF A BLOCK
bool isValid(int& row, int& col, int& numRows, int& numCols, vector<vector<int>>& grid)
{
    return (row >= 0 && row < numRows && col >= 0 && col < numCols&&grid[row][col]!=-1);
}

//FUNCTION TO RETURN THE SHORTEST DISTANCE USING A* ALGORITHM
void shortestpath(int &numRows,int &numCols,int p_x, int p_y,vector<pair<int, int>>& path, vector<vector<int>>&grid)
{
    int x, y;
    cout << "Enter coordinates to reach" << endl;
    cin >> x >> y;
    p_x = p_x / 25;
    p_y = p_y / 25;
    int d_x = y / 25;
    int d_y = x / 25;

    if (grid[d_x][d_y] == -1)
    {
        cout << "Invalid Block"<<endl;
        shortestpath(numRows, numCols, p_x, p_y, path, grid);
    }
        
    priority_queue <pair<int, pair<int, int>>>q;
    q.push({ 0, { p_x,p_y } });
    vector<vector<pair<int, int>>> came_from(numRows, vector<pair<int, int>>(numCols, { -1, -1 }));
    vector<vector<int>> cost_so_far(numRows, vector<int>(numCols,10000));
    cost_so_far[p_x][p_y] = 0;
    came_from[p_x][p_y] = { -1,-1 };
    while (!q.empty())
    {
        pair<int, pair<int, int>>curr = q.top();
        int curr_x = curr.second.first;
        int curr_y = curr.second.second;
        q.pop();

        if (curr_x == d_x && curr_y == d_y)
        {
            while (curr_x != -1 && curr_y != -1)
            {
                path.push_back({ curr_x, curr_y });
                int next_x = came_from[curr_x][curr_y].first;
                int next_y = came_from[curr_x][curr_y].second;
                curr_x = next_x;
                curr_y = next_y;
            }
        }

        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };

        for (int i = 0; i < 4; i++)
        {
            int n_x = curr_x + dx[i];
            int n_y = curr_y + dy[i];

            if (isValid(n_x, n_y, numRows, numCols,grid))
            {              
                int new_cost = cost_so_far[curr_x][curr_y] + grid[n_x][n_y];

                if (new_cost < cost_so_far[n_x][n_y])
                {
                    cost_so_far[n_x][n_y] = new_cost;
                    came_from[n_x][n_y] = { curr_x,curr_y };
                    int priority = new_cost + heuristic(n_x, n_y, d_x, d_y);
                    q.push({-priority,{n_x,n_y} });
                } 
            }
        } 
    }
}
