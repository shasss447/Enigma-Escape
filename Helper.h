#pragma once
#include<math.h>
int heuristic(int curr_x, int curr_y, int& d_x, int& d_y)
{
    return abs(curr_x - d_x) + abs(curr_y - d_y);
}

bool isValid(int& row, int& col, int& numRows, int& numCols)
{
    return (row >= 0 && row < numRows && col >= 0 && col < numCols);
}

void shortestpath(int &numRows,int &numCols,int p_x, int p_y,int offsetx,int offsety, vector<pair<int, int>>& path, vector<vector<int>>&grid)
{
    int x, y;
    cout << "enter coord" << endl;
    cin >> x >> y;
    p_x = p_x / 25;
    p_y = p_y / 25;
    int d_x = (y + offsety) / 25;
    int d_y = (x + offsetx) / 25;
    priority_queue <pair<int, pair<int, int>>>q;
    q.push({ 0, { p_x,p_y } });
    vector<vector<pair<int, int>>> came_from(numRows, vector<pair<int, int>>(numCols));
    vector<vector<int>> cost_so_far(numRows, vector<int>(numCols,10000));
    cost_so_far[p_x][p_y] = 0;
    came_from[p_x][p_y] = { p_x, p_y };
    while (!q.empty())
    {
        pair<int, pair<int, int>>curr = q.top();
        int curr_x = curr.second.first;
        int curr_y = curr.second.second;
        cout << curr_x << " " << curr_y << " " << came_from[curr_x][curr_y].first << " " << came_from[curr_x][curr_y].second <<" "<<cost_so_far[curr_x][curr_y]<< endl;
        q.pop();
        if (curr_x == d_x && curr_y == d_y)
            break;
        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };
        for (int i = 0; i < 4; i++)
        {
            int n_x = curr_x + dx[i];
            int n_y = curr_y + dy[i];
            if (isValid(n_x, n_y, numRows, numCols))
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
    int a = d_x;
    int b = d_y;
    path.push_back({ a,b });
    while (a != p_x && b != p_y)
    {
        path.push_back({ came_from[a][b].first,came_from[a][b].second });
            a = came_from[a][b].first;
            b = came_from[a][b].second;
    }
    path.push_back({ p_x,p_y });  
}
