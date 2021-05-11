// wilson's loop erased random walk
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "maze3gen.h"

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

    int in; // 0 not in maze, 1 in maze, 2 in random walk
    bool up;
    bool left;
    int prevx, prevy;

};

void savebmp(int xspecial, int yspecial, int xsize, int ysize, std::vector<std::vector<cell>> maze, int numIn);
void MapPrint(int xsize, int ysize, std::vector<std::vector<cell>> maze, int numIn);

int MazeMain(int rowsprov, int columnsprov){

    std::cout<<"HERE";

    // if(argc!=3){

    //     std::cout<<"Input format should be ./maze2 rows columns";
    //     return 0;

    // }

    // if(!isInteger(argv[1]) || !isInteger(argv[2])){

    //     std::cout<<"Invalid row/column size";
    //     return 0;

    // }

    // int rows = std::stoi(argv[1]);
    // int columns = std::stoi(argv[2]);

    int rows = rowsprov;
    int columns = columnsprov;

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
    //savebmp(0,0,rows+ROW_PADDING,columns+COL_PADDING,maze,0);

    int numIn = 1; // number of cells in the maze currently
    int num = 1;
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

        while(maze[xcur][ycur].in){
            xcur = rand()%(rows+ROW_PADDING);
            ycur = rand()%(columns+COL_PADDING);
            // std::cout<<148;
            //savebmp(xcur,ycur,rows+ROW_PADDING,columns+COL_PADDING,maze, num);
            num++;
        }

        maze[xcur][ycur].in=2;
        maze[xcur][ycur].prevx=-1;
        success = 0;

        while(!success){
        
            side = (wall)(rand()%4);
            // std::cout<<"\n";
            // std::cout<<side<<"\n";
            // std::cout<<xcur<<"\n";
            // std::cout<<ycur<<"\n";
            // std::cout<<maze[xcur][ycur].in<<"\n";
            // std::cout<<maze[xcur-1][ycur].in<<"\n";
            // std::cout<<maze[xcur][ycur-1].in<<"\n";
            // std::cout<<maze[xcur+1][ycur].in<<"\n";
            // std::cout<<maze[xcur][ycur+1].in<<"\n";
            switch(side){
                case(LEFT):
                    if(/*!(maze[xcur][ycur-1].in==2) &&  */ycur!=1){
                        if(maze[xcur][ycur-1].in==1){
                            success=1;
                            maze[xcur][ycur].left=0;
                        }
                        else if(maze[xcur][ycur-1].in==2){
                            std::cout<<"HI\n\n\n\n";
                            int rx=xcur;
                            int ry=ycur-1;
                            while(rx!=xcur || ry!=ycur){
                                std::cout<<"LO\n";
                                maze[xcur][ycur].in=0;
                                if(maze[xcur][ycur].prevx==xcur-1){
                                    maze[xcur][ycur].up=1;
                                }
                                else if(maze[xcur][ycur].prevx==xcur+1){
                                    maze[xcur+1][ycur].up=1;
                                }
                                else if(maze[xcur][ycur].prevy==ycur-1){
                                    maze[xcur][ycur].left=1;
                                }
                                else{
                                    maze[xcur][ycur+1].left=1;
                                }
                                int t = maze[xcur][ycur].prevx;
                                ycur = maze[xcur][ycur].prevy;
                                xcur=t;
                            }
                        }
                        else{
                            maze[xcur][ycur].left=0;
                            maze[xcur][ycur-1].prevx = xcur;
                            maze[xcur][ycur-1].prevy = ycur;
                            maze[xcur][ycur-1].in=2;
                            ycur--;
                        }
                    }
                    break;

                case(UP):
                    if(/* !(maze[xcur - 1][ycur].in==2) &&  */xcur!=1){

                        if(maze[xcur-1][ycur].in==1){
                            success=1;
                            maze[xcur][ycur].up = 0;
                        }
                        else if(maze[xcur-1][ycur].in==2){
                            std::cout<<"HI\n\n\n\n";
                            int rx=xcur-1;
                            int ry=ycur;
                            while(rx!=xcur || ry!=ycur){
                                std::cout<<"LO\n";
                                maze[xcur][ycur].in=0;
                                if(maze[xcur][ycur].prevx==xcur-1){
                                    maze[xcur][ycur].up=1;
                                }
                                else if(maze[xcur][ycur].prevx==xcur+1){
                                    maze[xcur+1][ycur].up=1;
                                }
                                else if(maze[xcur][ycur].prevy==ycur-1){
                                    maze[xcur][ycur].left=1;
                                }
                                else{
                                    maze[xcur][ycur+1].left=1;
                                }
                                int t = maze[xcur][ycur].prevx;
                                ycur = maze[xcur][ycur].prevy;
                                xcur=t;
                            }
                        }
                        else{
                            maze[xcur][ycur].up = 0;
                            maze[xcur - 1][ycur].prevx = xcur;
                            maze[xcur - 1][ycur].prevy = ycur;
                            maze[xcur-1][ycur].in=2;
                            xcur--;
                        }
                    
                    }
                    break;
                
                case(RIGHT):
                    if(/* !(maze[xcur][ycur + 1].in==2) &&  */ycur!=columns){
                        if(maze[xcur][ycur+1].in==1){
                            success=1;
                            maze[xcur][ycur+1].left=0;
                        }
                        else if(maze[xcur][ycur+1].in==2){
                            std::cout<<"HI\n\n\n\n";
                            int rx=xcur;
                            int ry=ycur+1;
                            while(rx!=xcur || ry!=ycur){
                                std::cout<<"LO\n";
                                maze[xcur][ycur].in=0;
                                if(maze[xcur][ycur].prevx==xcur-1){
                                    maze[xcur][ycur].up=1;
                                }
                                else if(maze[xcur][ycur].prevx==xcur+1){
                                    maze[xcur+1][ycur].up=1;
                                }
                                else if(maze[xcur][ycur].prevy==ycur-1){
                                    maze[xcur][ycur].left=1;
                                }
                                else{
                                    maze[xcur][ycur+1].left=1;
                                }
                                int t = maze[xcur][ycur].prevx;
                                ycur = maze[xcur][ycur].prevy;
                                xcur=t;
                            }
                        }
                        else{
                            maze[xcur][ycur + 1].left = 0;
                            maze[xcur][ycur + 1].prevx = xcur;
                            maze[xcur][ycur + 1].prevy = ycur;
                            maze[xcur][ycur+1].in=2;
                            ycur++;
                            
                        }
                        

                    }
                    break;
                
                case(DOWN):
                    if(/* !(maze[xcur + 1][ycur].in==2) &&  */xcur!=rows){
                        if(maze[xcur+1][ycur].in==1){
                            success=1;
                            maze[xcur+1][ycur].up=0;
                        }
                        else if(maze[xcur+1][ycur].in==2){
                            std::cout<<"HI\n\n\n\n";
                            int rx=xcur+1;
                            int ry=ycur;
                            while(rx!=xcur || ry!=ycur){
                                std::cout<<"LO\n";
                                maze[xcur][ycur].in=0;
                                if(maze[xcur][ycur].prevx==xcur-1){
                                    maze[xcur][ycur].up=1;
                                }
                                else if(maze[xcur][ycur].prevx==xcur+1){
                                    maze[xcur+1][ycur].up=1;
                                }
                                else if(maze[xcur][ycur].prevy==ycur-1){
                                    maze[xcur][ycur].left=1;
                                }
                                else{
                                    maze[xcur][ycur+1].left=1;
                                }
                                int t = maze[xcur][ycur].prevx;
                                ycur = maze[xcur][ycur].prevy;
                                xcur=t;
                            }
                        }
                        else{
                        maze[xcur + 1][ycur].up = 0;
                        maze[xcur + 1][ycur].prevx = xcur;
                        maze[xcur + 1][ycur].prevy = ycur;
                        maze[xcur+1][ycur].in=2;
                        xcur++;
                        }
                    }
                    break;
                
                default:
                    break;
            }
            // std::cout<<"289";
            //savebmp(xcur,ycur,rows+ROW_PADDING,columns+COL_PADDING,maze, num);
            num++;
        }
        maze[xcur][ycur].in=1;
        numIn++;
        // std::cout<<296;
        //savebmp(xcur,ycur,rows+ROW_PADDING,columns+COL_PADDING,maze, num);
        num++;
        while(maze[xcur][ycur].prevx!=-1){
            int t = maze[xcur][ycur].prevx;
            ycur = maze[xcur][ycur].prevy;
            xcur = t;
            maze[xcur][ycur].in=1;
            numIn++;
            // std::cout<<305;
            //savebmp(xcur,ycur,rows+ROW_PADDING,columns+COL_PADDING,maze, num);
            num++;
        }

    }
    std::cout << "Hello";
    // savebmp(0,0,rows+ROW_PADDING,columns+COL_PADDING,maze,numIn);
    savebmp(xcur,ycur,rows+ROW_PADDING,columns+COL_PADDING,maze, num);
    MapPrint(rows+ROW_PADDING,columns+COL_PADDING,maze, num);
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
	
	sprintf(filename, "MazeAlgos/maze.bmp", "maze3", xsize, ysize, numIn);
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

void MapPrint(int xsize, int ysize, std::vector<std::vector<cell>> maze, int numIn){
	//save a test file

	FILE * outfile;
	int extrabytes, paddedsize;
	int x, y, n;
	int width=(xsize-1)*2-1;
	int height=(ysize-1)*2-1;

	extrabytes = (4 - ((width * 3) % 4))%4; 

	char filename[200];
	
	sprintf(filename, "MazeAlgos/maze.txt", "maze3", xsize, ysize, numIn);
	paddedsize = ((width * 3) + extrabytes) * height;

	unsigned int headers[13] = {paddedsize + 54, 0, 54, 40, width, height, 0, 0, paddedsize, 0, 0, 0, 0};

	outfile = fopen(filename, "wb");
	//fprintf(outfile, "w");

	// for (n = 0; n <= 5; n++){
	//    fprintf(outfile, "%c", headers[n] & 0x000000FF);
	//    fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
	//    fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
	//    fprintf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
	// }

	// fprintf(outfile, "%c", 1);fprintf(outfile, "%c", 0);
	// fprintf(outfile, "%c", 24);fprintf(outfile, "%c", 0);

	// for (n = 7; n <= 12; n++){
	//    fprintf(outfile, "%c", headers[n] & 0x000000FF);
	//    fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
	//    fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
	//    fprintf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
	// }

	//Actual writing of data begins here:
	for(y = 0; y <= height - 1; y++){
		for(x = 0; x <= width - 1; x++){
			if(x%2 == 1 && y%2 == 1){
				// if(x/2+1 == xspecial && y/2+1 == yspecial) fprintf(outfile, "%c%c%c", 0,0,255);
				// else{
				// 	if(maze[x/2+1][y/2+1].in) fprintf(outfile, "%c%c%c", 255,255,255); else fprintf(outfile, "%c%c%c", 0,0,0);
				// }
				if(maze[x/2+1][y/2+1].in) fprintf(outfile, "%d ", 1); else fprintf(outfile, "%d ", 1);
			}else if(x%2 == 0 && y%2 == 0){
				fprintf(outfile, "%d ", 0);
			}else if(x%2 == 0 && y%2 == 1){
				if(maze[x/2+1][y/2+1].up) fprintf(outfile, "%d ", 0); else fprintf(outfile, "%d ", 1);
			}else if(x%2 == 1 && y%2 == 0){
				if(maze[x/2+1][y/2+1].left) fprintf(outfile, "%d ", 0); else fprintf(outfile, "%d ", 1);
			}
		}
        fprintf(outfile, "\n");
		// if (extrabytes){     // See above - BMP lines must be of lengths divisible by 4.
		// 	for (n = 1; n <= extrabytes; n++){
		// 		fprintf(outfile, "%d", 0);
		// 	}
		// }
	}
	printf("file printed: %s\n", filename); 
	fclose(outfile);
	return;
}