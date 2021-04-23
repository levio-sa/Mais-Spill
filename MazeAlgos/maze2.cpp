// backtracking algorithm using prevx and prevy pointers
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

enum wall {

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

struct cell{

    bool in;
    bool up;
    bool left;
    int prevx, prevy;

};

void savebmp(int xspecial, int yspecial, int xsize, int ysize, std::vector<std::vector<cell>> maze, int numIn);


int main(int argc, char * argv[]){

    std::cout<<"HERE";

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

    const int ROW_PADDING = 2;
    const int COL_PADDING = 2;

    srand((unsigned int)time(NULL));

    // initialize

    std::vector<std::vector<cell>> maze; // the maze

    for(int i = 0; i < rows + ROW_PADDING; ++i){

        std::vector<cell> temp;

        for(int j = 0; j < columns + COL_PADDING; ++j){

            cell c;
            temp.push_back(c);
        }
        
        maze.push_back(temp);
    
    }

    for(int i = 0; i < rows+2; ++i){

        for(int j = 0; j < columns + 2; ++j){

            maze[i][j].in = (i == 0 || i == rows + 1 || j == 0 || j == columns + 1) ? 1 : 0;
            maze[i][j].up = (i == 0 || j == 0 || j == columns + 1) ? 0 : 1;
            maze[i][j].left = (i == 0 || i == rows + 1 || j == 0) ? 0 : 1;

        }

    }
    // std::cout<<"\n";

    // for(int i = 0; i < rows+2; ++i){

    //     for(int j = 0; j < columns + 2; ++j){

    //         (maze[i][j].in) ? std::cout<<'#' : std::cout<<0 ;

    //     }
    //     std::cout<<"\n";

    // }

    // generate
    savebmp(0,0,rows+ROW_PADDING,columns+COL_PADDING,maze,0);

    int numIn = 1; // number of cells in the maze currently

    int totIn = rows * columns; // total number of cells in the maze

    bool success = false; // whether succeeded in growing maze in random trial
    
    wall side = UP; // side chosen in random trial

    int xcur = 1, ycur = 1;
    maze[xcur][ycur].in = 1;

    std::cout<<"HERE";
    
    while(numIn < totIn){

        // std::cout<<"\n";
        // std::cout<<numIn<<"\n"<<"\n";

        // for(int i = 0; i < rows+2; ++i){

        //     for(int j = 0; j < columns + 2; ++j){

        //         (maze[i][j].in) ? ((i==xcur && j==ycur) ? std::cout<<9 : std::cout<<'#') : std::cout<<0 ;

        //     }
        //     std::cout<<"\n";

        // }
        // std::cout<<"\n";

        savebmp(xcur,ycur,rows+ROW_PADDING,columns+COL_PADDING,maze, numIn);

        /* // enable this for no dead ends
        if(maze[xcur - 1][ycur].in && maze[xcur][ycur + 1].in && maze[xcur + 1][ycur].in && maze[xcur][ycur - 1].in){

            success = 0;

            while(!success){

                side = (wall)(rand() % 4);
                std::cout<<side<<'\n';

                switch(side){

                    case(LEFT):
                        if(maze[xcur][ycur].left && ycur!=1){
                            
                            success = 1;
                            maze[xcur][ycur].left = 0;

                        }
                        break;

                    case(UP):
                        if(maze[xcur][ycur].up && xcur!=1){

                            success = 1;
                            maze[xcur][ycur].up = 0;
                        
                        }
                        break;
                    
                    case(RIGHT):
                        if(maze[xcur][ycur + 1].left && ycur!=columns){
                            
                            success = 1;
                            maze[xcur][ycur + 1].left = 0;
                            
                        }
                        break;
                    
                    case(DOWN):
                        if(maze[xcur + 1][ycur].up && xcur!=rows){

                            success = 1;
                            maze[xcur + 1][ycur].up = 0;
                        
                        }
                        break;
                    
                    default:
                        break;

                }
            
            }
        
        } */

        while(maze[xcur - 1][ycur].in && maze[xcur][ycur + 1].in && maze[xcur + 1][ycur].in && maze[xcur][ycur - 1].in){
            
            int t = maze[xcur][ycur].prevx;
            ycur = maze[xcur][ycur].prevy;
            xcur = t;
        
        }

        success = 0;

        while(!success){

            side = (wall)(rand() % 4);

            switch(side){

                case(LEFT):
                    if(!maze[xcur][ycur - 1].in){
                        
                        success = 1;
                        maze[xcur][ycur].left = 0;
                        maze[xcur][ycur - 1].prevx = xcur;
                        maze[xcur][ycur - 1].prevy = ycur;
                        ycur--;

                    }
                    break;

                case(UP):
                    if(!maze[xcur - 1][ycur].in){

                        success = 1;
                        maze[xcur][ycur].up = 0;
                        maze[xcur - 1][ycur].prevx = xcur;
                        maze[xcur - 1][ycur].prevy = ycur;
                        xcur--;
                    
                    }
                    break;
                
                case(RIGHT):
                    if(!maze[xcur][ycur + 1].in){
                        
                        success = 1;
                        maze[xcur][ycur + 1].left = 0;
                        maze[xcur][ycur + 1].prevx = xcur;
                        maze[xcur][ycur + 1].prevy = ycur;
                        ycur++;

                    }
                    break;
                
                case(DOWN):
                    if(!maze[xcur + 1][ycur].in){

                        success = 1;
                        maze[xcur + 1][ycur].up = 0;
                        maze[xcur + 1][ycur].prevx = xcur;
                        maze[xcur + 1][ycur].prevy = ycur;
                        xcur++;
                    
                    }
                    break;
                
                default:
                    break;

            }
        
        }

        numIn++;
        maze[xcur][ycur].in = 1;
    }
    std::cout << "Hello";
    savebmp(0,0,rows+ROW_PADDING,columns+COL_PADDING,maze,numIn);

    return 0;
    
}

void savebmp(int xspecial, int yspecial, int xsize, int ysize, std::vector<std::vector<cell>> maze, int numIn){
	//save a bitmap file! the xspecial, yspecial pixel is coloufprintf(outfile, "%c%c%c", 0,0,255) fprintf(outfile, "%c%c%c", 0,0,255).
	FILE * outfile;
	int extrabytes, paddedsize;
	int x, y, n;
	int width=(xsize-1)*2-1;
	int height=(ysize-1)*2-1;

	extrabytes = (4 - ((width * 3) % 4))%4; 

	char filename[200];
	
	sprintf(filename, "%s_%dx%d_n%d.bmp", "maze", xsize, ysize, numIn);
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



