#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<pair<int, int>> bfs(vector<vector<char>>& grid, pair<int, int> start, pair<int, int> end)
{
    //DEFINED QUEUE, VISITED AND PARENT. THIS IS BFS BASIC.
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
    vector<vector<pair<int, int>>> parent(grid.size(), vector<pair<int, int>>(grid[0].size(), {-1, -1}));
    
    q.push(start);
    visited[start.first][start.second] = true;

    vector<vector<int>> directions(6, vector<int>(2)); //DIRECTIONS FOR HEXAGONAL SHAPE

    while(!q.empty())
    {
        auto[x, y] = q.front();
        q.pop();

        if(x % 2 != 0)
        {
            directions = {{-1, 0}, {-1, +1}, {0, -1}, {0, 1}, {1, 0}, {1, 1}};
        } else {
            directions = {{-1, -1}, {-1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 0}};
        }
        
        if(x == end.first && y == end.second) //IF WE REACH TO THE END, TRAVERSING TO THE S
        {
            for(int i = 0; i < grid.size(); i++)
            {
                vector<pair<int, int>> path;
                for(pair<int, int> current = {x, y}; current != make_pair(-1, -1); current = parent[current.first][current.second])
                {
                    path.push_back(current);
                }
                reverse(path.begin(), path.end());
                return path;
            }
        }

        for(int d = 0; d < 6; d++) //TRAVERSING EACH DIRECTION AND CHECK PERIODIC TRAVERSE
        {
            int nx = x + directions[d][0];
            int ny = y + directions[d][1];

            if(nx < 0)
            {
                nx = grid.size() - 1;
            }
            if(nx >= grid.size())
            {
                nx = 0;
            }
            if(ny < 0)
            {
                ny = grid[0].size() - 1;
            }
            if(ny >= grid[0].size())
            {
                ny = 0;
            }
            if(visited[nx][ny] == false && grid[nx][ny] != '#')
            {
                visited[nx][ny] = true;
                parent[nx][ny] = {x, y};
                q.push({nx, ny});
            }
        }
    }
    return {};
}

int main()
{
    int w;
    int h;
    cin >> w >> h; cin.ignore();

    vector<vector<char>> grid(h); //HOLD EACH CELL IN THIS GRID

    pair<int, int> start, end; //STORE S AND E CHARACTER INDEXES 
    
    for (int i = 0; i < h; i++) { //FILL THE GRID AND START END PAIRS
        string row;
        getline(cin, row);
        for(int j = 0; j < w; j++)
        {
            grid[i].push_back(row[j]);
            if(row[j] == 'S')
            {
                start.first = i;
                start.second = j;
            } else if(row[j] == 'E')
            {
                end.first = i;
                end.second = j;
            }
        }
    }

    vector<pair<int, int>> path = bfs(grid, start, end); //CALL BFS FUNCTION AND ASSIGN RETURN VALUE TO PATH

    if(!path.empty()) //TRAVERSING THE PATH AND PUT DOT CHARACTERS IN THE GRID
    {
        for(pair<int, int> single : path)
        {
            if(grid[single.first][single.second] != 'S' && grid[single.first][single.second] != 'E')
            {
                grid[single.first][single.second] = '.';
            }
        }
    }

    for(int i = 0; i < h; i++) //PRINT GRID
    {
        for(int j = 0; j < w; j++)
        {
            cout << grid[i][j];
        }
        cout << endl;
    }
}
