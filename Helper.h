#pragma once
//shortestpath(myplayer.p_pos.second / 25, myplayer.p_pos.first / 25, (de_pos.second + offset.second) / 25, (de_pos.first + offset.first) / 25,path);
struct Compare
{
    bool operator()(const pair<int, pair<int, int>>& p1, const pair<int, pair<int, int>>& p2) const
    {
        return p1.first > p2.first;
    }
};
void shortestpath(int &numRows,int &numCols,int p_x, int p_y,int offsetx,int offsety, vector<pair<int, int>>& path, vector<vector<int>>&grid)
{
    int x, y;
    cout << "enter coord" << endl;
    cin >> x >> y;
    p_x = p_x / 25;
    p_y = p_y / 25;
    int d_x = (y + offsety) / 25;
    int d_y = (x + offsetx) / 25;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, Compare>q;
    q.push({ 0, { p_x,p_y } });
    vector<vector<pair<int, int>>> came_from(numRows, vector<pair<int, int>>(numCols));
    vector<vector<int>> cost_so_far(numRows, vector<int>(numCols, 0));
    came_from[p_x][p_y] = { p_x, p_y };
    cout << d_x << " " << d_y << endl;
    while (!q.empty())
    {
        pair<int, pair<int, int>>curr = q.top();
        int dis = curr.first;
        int curr_x = curr.second.first;
        int curr_y = curr.second.second;
        q.pop();

        cout << dis << " " << curr_x << " " << curr_y << endl;
        if (curr_x == d_x && curr_y == d_y)
            break;
        if (curr_x + 1 < numRows)
        {
            cout << "row+1" << endl;
            int new_cost = dis + grid[curr_x + 1][curr_y];
            if (cost_so_far[curr_x + 1][curr_y] == 0 || new_cost < cost_so_far[curr_x + 1][curr_y])
            {
                cost_so_far[curr_x + 1][curr_y] = new_cost;
                q.push({ new_cost, { curr_x + 1,curr_y } });
                came_from[curr_x + 1][curr_y] = { curr_x,curr_y };
            }
        }
        if (curr_x - 1 >= 0)
        {
            cout << "row-1" << endl;
            int new_cost = dis + grid[curr_x - 1][curr_y];
            if (cost_so_far[curr_x - 1][curr_y] == 0 || new_cost < cost_so_far[curr_x - 1][curr_y])
            {
                cost_so_far[curr_x - 1][curr_y] = new_cost;
                q.push({ new_cost, { curr_x - 1,curr_y } });
                came_from[curr_x - 1][curr_y] = { curr_x,curr_y };
            }
        }
        if (curr_y + 1 < numCols)
        {
            cout << "col+1" << endl;
            int new_cost = dis + grid[curr_x][curr_y + 1];
            if (cost_so_far[curr_x][curr_y + 1] == 0 || new_cost < cost_so_far[curr_x][curr_y + 1])
            {
                cost_so_far[curr_x][curr_y + 1] = new_cost;
                q.push({ new_cost, { curr_x ,curr_y + 1 } });
                came_from[curr_x][curr_y + 1] = { curr_x,curr_y };
            }
        }
        if (curr_y - 1 >= 0)
        {
            cout << "col-1" << endl;
            int new_cost = dis + grid[curr_x][curr_y - 1];
            if (cost_so_far[curr_x][curr_y - 1] == 0 || new_cost < cost_so_far[curr_x][curr_y - 1])
            {
                cost_so_far[curr_x][curr_y - 1] = new_cost;
                q.push({ new_cost, { curr_x ,curr_y - 1 } });
                came_from[curr_x][curr_y - 1] = { curr_x,curr_y };
            }
        }
    }
    while (d_x != p_x && d_y != p_y)
    {
        path.push_back({ came_from[d_x][d_y] });
        cout << came_from[d_x][d_y].first<< came_from[d_x][d_y].second << endl;
        d_x = came_from[d_x][d_y].first;
        d_y = came_from[d_x][d_y].second;
    }
}