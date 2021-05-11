#include "menu.h"
#include "MazeAlgos/maze3gen.h"

void MazeGen(int x, int y);

void MenuFunction(int x, int y){
    MazeGen(x,y);
}
void MazeGen(int x, int y){
    MazeMain(x,y);
}