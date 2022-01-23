#include <iostream>
#include <vector>
#include <string>

// #define DEBUG

using namespace std;

vector<vector<vector<int>>> moves_available;
vector<vector<int>> stack;
int curr_i = 0, curr_j = 0;
vector<vector<int>> maze;
int success = 0;
char stamp = '*';
string success_message = "";

vector<vector<int>> search_path(int curr_i, int curr_j){
    //look around one point in every direction
    int x = curr_i-2;
    vector<vector<int>> av_moves;
    for(int i =0; i < 3; i++){
        x = x+1;
        int y = curr_j - 1;
        for(int j = 0; j< 3;j++){
            if(y >= 0 && x >=0 and x < maze.size() and y < maze[0].size()){
                if(maze[x][y] == 0){
                    av_moves.push_back(vector({x,y}));
                }
            }    
            y = y+1;
        }
    }
    return av_moves;
}

int move(){
    //look around one point in every direction
    int x = curr_i -2;
    vector<vector<int>> ponits;
    for(int i =0; i< 3; i++){
        x = x+1;
        int y = curr_j - 1;
        for(int j = 0; j<3;j++){
            if(y >= 0 && x >= 0 && x < maze.size() && y < maze[0].size()){
                if(maze[x][y] ==0 ) {
                    if(x == curr_i && y == curr_j) {}
                    else ponits.push_back(vector({x, y}));
                }
            }
            y = y+1;
        }
    }
    // if there are more than one point available to move, return 0, need to search path
    // if exactly one point is available, return 1, move to next point
    // if no point is available(block) return 2, need to go back
    if(ponits.size() > 1) {
        maze[curr_i][curr_j] = 2;
        return 0;
    }
    if(ponits.empty()){
        maze[curr_i][curr_j] = 2;
        return 2;
    }
    else {
        maze[curr_i][curr_j] = 2;
        #ifdef DEBUG
            cout<<"move() is modifying curr_i and curr_j to "<< ponits.back()[0] << " "<<ponits.back()[1]<<endl;
        #endif
        curr_i = ponits.back()[0];
        curr_j = ponits.back()[1];
    }
    return 1;
}

void go_back(){
    if(!moves_available.back().empty()){
        curr_i = moves_available.back().back()[0];
        curr_j = moves_available.back().back()[1];
        #ifdef DEBUG 
            cout << "go_back() modified curr_i and curr_j " << curr_i << " " << curr_j <<endl; 
        #endif
        moves_available.back().pop_back();
    }
    else {
        #ifdef DEBUG
            for(int i =0; i < stack.size(); i++){
                cout<< stack[i][0] << " " << stack[i][1] <<endl;
            }
        #endif
        moves_available.pop_back();
        vector<int> previous = stack.back();
        curr_i = previous[0];
        curr_j = previous[1];
        #ifdef DEBUG
            cout << "go_back() modified curr_i and curr_j " << curr_i << " " << curr_j <<endl;
            cout<<"Moving back in stack" <<endl;
        #endif
        stack.pop_back();
    }
}

void solve(vector<vector<int>> p_maze, int goal_i, int goal_j){
    maze = p_maze;
    maze[0][0] = 8;
    while(!success){
        //check if reached goal
        if(curr_i == goal_i-1 && curr_j == goal_j-1) {
            success = 1;
            maze[curr_i][curr_j] = 2;
            break;
        }

        int move_result = move();
        
        if(move_result == 0){
            #ifdef DEBUG
                cout<<"searching path... "<< curr_i << " "<<curr_j<<endl;
            #endif
            
            vector<vector<int>> paths = search_path( curr_i, curr_j);

            #ifdef DEBUG
                cout << "paths.size() " << paths.size() << endl; 
            #endif

            stack.push_back(vector({curr_i, curr_j}));
            curr_i = paths.back()[0];
            curr_j = paths.back()[1];
            #ifdef DEBUG 
                cout << " New Current_i && current_j >>>> " << curr_i << " "<<curr_j << endl; 
            #endif
            paths.pop_back();
            moves_available.push_back(paths);
        } 
        else if(move_result == 2) go_back();
        
        //check if the goal is unreachable
        if(maze[curr_i][curr_j] == 8){
            success = 2;
        }


    }
    
    if(success == 2) cout<<"Goal is unreachable"<<endl;
    else{
        cout<<success_message<<endl;
        //for printing result
        for(int i = 0; i < maze.size(); i++){
            for(int j = 0; j< maze[0].size(); j++){
                if(maze[i][j] == 2) cout<<stamp<< " ";
                else cout <<maze[i][j]<< " ";
            }
            cout<<""<<endl;
        }
    }
}