#include "get_power.h"

vector<pair<int,int> > visited;

bool used[30][30];

void dfs(int i, int j)
{
    used[i][j]=1;
    visited.pb({i,j});

    for (auto to:object[i][j].reb)
    if (!used[to.fir][to.sec])
    {
        dfs(to.fir,to.sec);
    }
}

void solve()
{
    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
        {
            used[i][j]=0;
        }
    for (int i=1;i<feel_size;i++)
        for (int j=1;j<feel_size;j++)
            if (!used[i][j])
            {
                dfs(i,j);
                visited.clear();
            }
}
