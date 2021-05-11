#include<iostream>
#include<fstream>

using namespace std;

int main(){
    fstream file;

    file.open("maze.txt",ios::in);
    if(file.is_open() == false){
        cout<<"Bad day\n";
    }
    else{
        cout<<"Good day\n";
    }

}