#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> y[729]; //options -> cons
vector<int> soln;
map<int, set<int> > x, tx; //cons -> options
void select(map<int, set<int> >& tx, int opt){
    set<int> rops;
    set<int>::iterator j;
    for(int i=0; i<y[opt].size(); i++){
        int sc = y[opt][i];
        for(j = x[sc].begin(); j != x[sc].end(); j++){
            rops.insert(*j);
        }
    }
    for(j = rops.begin(); j != rops.end(); j++){
        for(int i=0; i<y[*j].size(); i++){
            int con = y[*j][i];
            x[con].erase(*j);
        }
    }
}
void solve(map<int, set<int> >& tx){
    if(soln.size() == 729){
        //print answer

        return;
    }
    set<int>::iterator j;
    int con = find_min(tx);
    for(j = tx[con].begin(); j != tx[con].end(); j++){
        int op = *j;
        map<int, set<int> > ttx = tx;
        select(ttx, op);
        solve(ttx);
        soln.pop_back();
    }
}
int main()
{
    for(int i=0; i<729; i++){
        int r = i/81;
        int c = (i%81)/9;
        int b = 3*(r/3)+(c/3);
        int v = i%9;
        x[9*r+v].insert(i);
        x[81+9*c+v].insert(i);
        x[2*81+9*b+v].insert(i);
        x[3*81+9*r+c].insert(i);
        y[i].push_back(9*r+v);
        y[i].push_back(81+9*c+v);
        y[i].push_back(2*81+9*b+v);
        y[i].push_back(3*81+9*r+c);
    }
    soln.clear();
    tx = x;
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            int c = getchar();
            if(c != '.'){
                int v = c-'0';
                select(tx, 81*i+9*j+v);
            }
        }
        getchar();
    }
    solve(tx);

    return 0;
}
