#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int m = board[0].size();
        int n = board.size();
        
        for(int i=0;i<m;++i){
            if(board[0][i]=='O') DFS(board, 0, i);
        }
        for(int i=1;i<n;++i){
            if(board[i][m-1]=='O') DFS(board, i, m-1);
        }
        for(int i=m-2;i>=0;--i){
            if(board[n-1][i]=='O') DFS(board, n-1, i);
        }
        for(int i=n-2;i>0;--i){
            if(board[i][0]=='O') DFS(board, i, 0);
        }
        for(int i=1;i<m-1;++i){
            for(int j=1;j<n-1;++j){
                if(board[i][j]=='O') board[i][j]='X';
            }
            
        }
        for(int i=0;i<m;++i){
            for(int j=0;j<n;++j){
                cout<<board[i][j];
                if(board[i][j]=='.') board[i][j]='O';
                
            }
            cout<<endl;
        }
    }


    void DFS(vector<vector<char>>& board, int x, int y){
        if(x==board[0].size() || y==board.size() || x<0 || y<0 || board[x][y]=='X' || board[x][y] == '.') return;
        board[x][y] = '.';
        DFS(board, x+1, y);
        DFS(board, x-1, y);
        DFS(board, x, y+1);
        DFS(board, x, y-1);

    }
};

int main(){
    Solution s;
    vector<vector<char>> v={{'O','O','O'},{'O','O','O'},{'O','O','O'}};
    s.solve(v);

};