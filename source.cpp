//Patricio Leal 
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int const N =9;
int const n = sqrt(N);

void printBoard(vector<vector<int>> board){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout<<board [i][j]<< " ";
        }
        cout<<endl;
    }
}
/* didn't need rn
bool checkVec(vector<int> vec){
    int arr[N];
    for(int i=0;i<N;i++){
        arr[i]==vec[i];
      }
      sort(arr, arr+N);
      for(int j=1;j<N;j++){
        if(arr[j]==0) continue;
        if(arr[j]==arr[j-1]) return false;
      }
      return true;
}*/



bool checkBoard(vector<vector<int>> board){
    vector<int> row; //temporary vector for row
    vector<vector<int>> col(N); //temporary 2d vector for col 
    vector<vector<int>> box(N); //temporary 2d vector for box

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){

            if(board[i][j]!=0){
                //compare and add value to row
                
                if(find(row.begin(), row.end(), board[i][j]) !=row.end()){ //check if new value is in row
                    return false;
                }else{
                    row.push_back(board[i][j]);  //if new value isn't in row, add it
                }

                //compare and add value to col

                if(find(col[j].begin(), col[j].end(), board[i][j]) !=col[j].end()){ //check if new value is in col
                    return false;
                }else{
                    col[j].push_back(board[i][j]);  //if new value isn't in col, add it
                }
        
                //compare and add value to box

                int quadrant= ((i/n)*3)+(j/3);  //equation to number quadrants
                if(find(box[quadrant].begin(), box[quadrant].end(), board[i][j]) !=box[quadrant].end()){    //check if new value is in box
                    return false;
                }else{
                    box[quadrant].push_back(board[i][j]);   //if new value isn't in box, add it
                }
            }
        }

        row.clear(); //clear row once it's checked
    }
    return true;    //return true if we go through every value
}

int findNextSpace(vector<vector<int>> board){
    for(int i=0;i<N*N;i++){
        if(board[i/N][i%N] == 0) return i;
    }return -1;
}
void insertBoard(vector<vector<int>> &board, int index, int num){
    board[index/N][index%N]=num;
}
bool canInsertBoard(vector<vector<int>> board, int nextSpace, int num){
    insertBoard(board, nextSpace, num);
    if(checkBoard(board)) return true;
    else return false;
}
bool solveBoard(vector<vector<int>> &board){
    int nextSpace=findNextSpace(board);
    if(nextSpace==-1) return true;
    for(int i=1;i<=N;i++){
        if(canInsertBoard(board,nextSpace,i)){
            insertBoard(board,nextSpace,i);
            if(solveBoard(board)) return true;    //recursively call until complete
            else insertBoard(board,nextSpace,0); //undo, try again
        }
    }  
    return false;
}

int main () {
    cout<<"Enter sudoku board to solve: "<<endl;
    vector<vector<int>> board(N);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            int input;
            cin>>input;
            if(input>=0 && input<=N) board[i].push_back(input);
            else {
                cout<<"Invalid input. Try again"<<endl;
                j--;
            }
        }
    }
    cout<<endl;
    if(solveBoard(board)){
        cout<<"\nSolved board: "<<endl;
        printBoard(board);
    } 
    else cout<<"\nNot solvable."<<endl;
}
