# Simple Maze Solver

This is a simple Maze Solver algorithm that solves given maze.

A maze is a 2 dimensional array filled with 1 and 0. 1 defines a wall/block while 0 defines a path. It also allows you to set custom goal coordinate. That is, let's say my goal is at center and not at the last. You can pass the co-ordinate as argument to the solve function

```cpp
void solve(vector<vector<int>> maze, int goal_i, int goal_j);
// considering maze[goal_i][goal_j] == 0 and is the goal
```

## To Run

It has a Debug Feature, if the Macro ```DEBUG``` is defined all logging would be activated.

A make file is included to make the executable. Use the following command:

``$ make out``

and an executable named `a.out` would be generated

**OR**

You can compile and run the program manually.


## Explanation


Variables:

**stack:** holds the co-ordinates of last point where multiple paths to choose were available

**moves_available:** holds the co-ordinates of all the paths available on the point pushed in stack

The algorithm works in three phases:

### Move

first we change the current positions value to 2, so that it does not collide with rest of the process. It also marks the path you have chosen.

We look around, one point in every direction from current position. To see if there is a path, and if there is the *only* path.

if it is the only path then we Move to it and again call ```move()```

if there is no path, then we call ```go_back()```

but if there is more than one path we call ```search_path(int curr_i, int curr_j)``` to find next path.

### Search Path

when search is called, it looks around one point from current direction. Pushes the current co-ordinate to the ```stack``` and put all paths co-ordinates in a ```vector``` and pushes it in another stack ```moves_available``` after this the driver function will choose the last element as the path to go with and pop it out from ```moves_available``` and sets the current co-ordinates to that one.

### Go Back

when there is a blockade, it checks, if the last position in stack has more paths that were not considered, if there are it will pop that one out and sets current co-ordinates to those co-ordinates and will ```move```. But if no unchecked paths are available it will pop one from both ```move_available``` and ```stack``` and set the current co-ordinates to the one popped from ```stack```

### Driver function

```solve(<vector<vector<int>> maze, int goal_i, int goal_j)``` is the driver function and is responsible for the execution loop and controlling above methods to find the solution.
