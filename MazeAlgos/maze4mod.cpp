// prim's algorithm
#include<iostream>
#include <stdlib.h>
#include <time.h>
#include<vector>

struct cell{
	bool in;  //Is this cell in the maze?
	bool up;  //Does the wall above this cell exist?
	bool left;//Does the wall to the left of this cell exist?
	int prevx, prevy; //The coordinates of the previous cell, used for backtracking.
};
void savebmp(int xspecial, int yspecial, int xsize, int ysize, int numin, std::vector<std::vector<cell>> maze);
enum wall{
    LEFT,
    UP,
    RIGHT,
    DOWN
};

bool isInteger(std::string s){

    for(int i = 0; i < s.length(); ++i){

        if(!isdigit(s[i])){

            return false;
        
        }

    }

    return true;
}

int main(int argc, char* argv[]){
    srand((unsigned int)time(NULL));
    if(argc!=3){

        std::cout<<"Input format should be ./maze2 rows columns";
        return 0;

    }

    if(!isInteger(argv[1]) || !isInteger(argv[2])){

        std::cout<<"Invalid row/column size";
        return 0;

    }

    int rows = std::stoi(argv[1]);
    int columns = std::stoi(argv[2]);
    std::vector<std::vector<cell>> maze;
    for(int i=0;i<rows+2;++i){
        std::vector<cell> temp;
        for(int j=0;j<columns+2;++j){
            cell c;
            temp.push_back(c);
        }
        maze.push_back(temp);
    }
    std::vector<std::pair<int,int>> visited;

    for(int i=0;i<rows+2;++i){
        for(int j=0;j<columns+2;++j){
            maze[i][j].in=(i==0 || j==0 || i==rows+1 || j==columns+1)?1:0;
            maze[i][j].up=(i==0 || j==0 || j==columns+1)?0:1;
            maze[i][j].left=(i==0 || i==rows+1 || j==0)?0:1;
        }
    }


    int numIn=1;
    int totIn = rows*columns;
    int xcur=1;
    int ycur=1;
    maze[xcur][ycur].in=1;
    visited.push_back(std::pair<int,int>(xcur,ycur));
    bool success;
    wall side;

    while(numIn<totIn){
        std::pair<int,int> p=visited[rand()%visited.size()];
        xcur=p.first;
        ycur=p.second;
        while(maze[xcur][ycur-1].in && maze[xcur+1][ycur].in && maze[xcur][ycur+1].in && maze[xcur-1][ycur].in){
            std::pair<int,int> p=visited[rand()%visited.size()];
            xcur=p.first;
            ycur=p.second;
        }
        // savebmp(xcur, ycur, rows+2, columns+2, numIn, maze);
        success=0;
        while(!success){
            side = (wall)(rand()%4);
            switch(side){
                case(LEFT):
                    if(!maze[xcur][ycur-1].in){
                        success=1;
                        maze[xcur][ycur].left=0;
                        maze[xcur][ycur-1].in=1;
                        maze[xcur][ycur-1].prevx=xcur;
                        maze[xcur][ycur-1].prevy=ycur;
                        ycur--;
                    }
                    break;
                case(UP):
                    if(!maze[xcur-1][ycur].in){
                        success=1;
                        maze[xcur][ycur].up=0;
                        maze[xcur-1][ycur].in=1;
                        maze[xcur-1][ycur].prevx=xcur;
                        maze[xcur-1][ycur].prevy=ycur;
                        xcur--;
                    }
                    break;
                case(RIGHT):
                    if(!maze[xcur][ycur+1].in){
                        success=1;
                        maze[xcur][ycur+1].left=0;
                        maze[xcur][ycur+1].in=1;
                        maze[xcur][ycur+1].prevx;
                        maze[xcur][ycur+1].prevy;
                        ycur++;
                    }
                    break;
                case(DOWN):
                    if(!maze[xcur+1][ycur].in){
                        success=1;
                        maze[xcur+1][ycur].up=0;
                        maze[xcur+1][ycur].in=1;
                        maze[xcur+1][ycur].prevx=xcur;
                        maze[xcur+1][ycur].prevy=ycur;
                        xcur++;
                    }
                    break;
            }
        }
        numIn++;
        visited.push_back(std::pair<int,int>(xcur,ycur));
        
    }

    // random loop add -> improve algo
    int r = rand()%((rows+2)*(columns+2)/2);
    for(int i=0;i<r;++i){
        int x = 0, y = 0;
        while(x==0 || x==rows+1 || y==0 || y==columns+1){
            x= rand()%(rows+2);
            y= rand()%(columns+2);
        }

        bool success = false;
        
        while(!success){

            wall side = (wall)(rand()%4);

            switch(side){
                case LEFT:
                if(y!=1){
                    maze[x][y].left = 0;
                    success=true;
                }
                break;
                case UP:
                    if(x!=1){
                        maze[x][y].up = 0;
                        success=true;
                    }
                    break;
                case RIGHT:
                    if(y!=columns){
                        maze[x][y+1].left = 0;
                        success = true;
                    }
                    break;
                case DOWN:
                    if(x!=rows){
                        maze[x+1][y].up = 0;
                        success = true;
                    }
                    break;
            }
        }
    }

    savebmp(xcur, ycur, rows+2, columns+2, numIn, maze);


}

void savebmp(int xspecial, int yspecial, int xsize, int ysize, int numin, std::vector<std::vector<cell>> maze){
	//save a bitmap file! the xspecial, yspecial pixel is coloufprintf(outfile, "%c%c%c", 0,0,255) fprintf(outfile, "%c%c%c", 0,0,255).
	FILE * outfile;
	int extrabytes, paddedsize;
	int x, y, n;
	int width=(xsize-1)*2-1;
	int height=(ysize-1)*2-1;

	extrabytes = (4 - ((width * 3) % 4))%4; 

	char filename[200];
	
	sprintf(filename, "%s_%dx%d_n%d.bmp", "maze4mod", xsize, ysize, numin);
	paddedsize = ((width * 3) + extrabytes) * height;

	unsigned int headers[13] = {paddedsize + 54, 0, 54, 40, width, height, 0, 0, paddedsize, 0, 0, 0, 0};

	outfile = fopen(filename, "wb");
	fprintf(outfile, "BM");

	for (n = 0; n <= 5; n++){
	   fprintf(outfile, "%c", headers[n] & 0x000000FF);
	   fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
	   fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
	   fprintf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
	}

	fprintf(outfile, "%c", 1);fprintf(outfile, "%c", 0);
	fprintf(outfile, "%c", 24);fprintf(outfile, "%c", 0);

	for (n = 7; n <= 12; n++){
	   fprintf(outfile, "%c", headers[n] & 0x000000FF);
	   fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
	   fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
	   fprintf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
	}

	//Actual writing of data begins here:
	for(y = 0; y <= height - 1; y++){
		for(x = 0; x <= width - 1; x++){
			if(x%2 == 1 && y%2 == 1){
				if(x/2+1 == xspecial && y/2+1 == yspecial) fprintf(outfile, "%c%c%c", 0,0,255);
				else{
					if(maze[x/2+1][y/2+1].in) fprintf(outfile, "%c%c%c", 255,255,255); else fprintf(outfile, "%c%c%c", 0,0,0);
				}
			}else if(x%2 == 0 && y%2 == 0){
				fprintf(outfile, "%c%c%c", 0,0,0);
			}else if(x%2 == 0 && y%2 == 1){
				if(maze[x/2+1][y/2+1].up) fprintf(outfile, "%c%c%c", 0,0,0); else fprintf(outfile, "%c%c%c", 255,255,255);
			}else if(x%2 == 1 && y%2 == 0){
				if(maze[x/2+1][y/2+1].left) fprintf(outfile, "%c%c%c", 0,0,0); else fprintf(outfile, "%c%c%c", 255,255,255);
			}
		}
		if (extrabytes){     // See above - BMP lines must be of lengths divisible by 4.
			for (n = 1; n <= extrabytes; n++){
				fprintf(outfile, "%c", 0);
			}
		}
	}
	printf("file printed: %s\n", filename); 
	fclose(outfile);
	return;
}
