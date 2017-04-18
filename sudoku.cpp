#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> y[729]; //options -> cons
vector<int> soln;
int solution[10][10];
map<int, set<int> > x, tx; //cons -> options
void select(map<int, set<int> >& tx, int opt){
    set<int> rops;
    set<int>::iterator j;
    for(int i=0; i<y[opt].size(); i++){
        int sc = y[opt][i];
        for(j = tx[sc].begin(); j != tx[sc].end(); j++){
            rops.insert(*j);
        }
    }
    for(j = rops.begin(); j != rops.end(); j++){
        for(int i=0; i<y[*j].size(); i++){
            int con = y[*j][i];
            tx[con].erase(*j);
        }
    }
}
int find_min(map<int, set<int> >& tx){
    int res = -1;
    int ls = INT_MAX;
    for(int i=0; i<243; i++){
        int cs = tx[i].size();
        if(cs != 0 && (res == -1 || ls > cs)){
            res = i;
            ls = cs;
        }
    }
    return res;
}
void construct_solution(){
    for(int i=0; i<soln.size(); i++){
        int r = soln[i]/81;
        int c = (soln[i]%81)/9;
        int v = soln[i]%9;
        solution[r+1][c+1] = v+1;
    }
}
void print_solution(){
    for(int i=1; i<=9; i++){
        for(int j=1; j<=9; j++){
            cout << solution[i][j];
        }
        cout << endl;
    }
}
bool stop;
void solve(map<int, set<int> >& tx){
    if(stop) return;
    if(soln.size() == 81){
        construct_solution();
        stop = true;
        return;
    }
    int con = find_min(tx);
    if(con == -1) return;
    set<int>::iterator j;
    for(j = tx[con].begin(); j != tx[con].end(); j++){
        int op = *j;
        map<int, set<int> > ttx = tx;
        select(ttx, op);
        soln.push_back(op);
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
    int t;

    scanf("%d", &t);
    getchar();
    for(int k=1; k<=t; k++){
        soln.clear();
        stop = false;
        tx = x;
        getchar();
        for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
                int c = getchar();
                if(c != '.'){
                    int v = c-'0'-1;
                    soln.push_back(81*i+9*j+v);
                    select(tx, 81*i+9*j+v);
                }
            }
            getchar();
        }
        solve(tx);
        printf("Case %d:\n", k);
        print_solution();
    }

    return 0;
}
