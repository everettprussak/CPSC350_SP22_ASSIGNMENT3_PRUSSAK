#include "doughnut.h"

Doughnut::Doughnut(){}

Doughnut::~Doughnut(){
    delete[] gameArray;
}

Doughnut::Doughnut(int a, int b){
    columns = b;
    rows = a;
    stablizer = false;
    generation_num=0;
    gameArray = new char* [a];
    for(int r=0; r<rows; r++){
        gameArray[r] = new char[b];
    }
    copyArray = new char* [a];
    for(int ra=0; ra<rows; ra++){
        copyArray[ra] = new char[b];
    }
    
}

void Doughnut::printGame(){
    cout << "Generation Number: " << generation_num << endl;
    for(int i=0; i<rows; i++){
        for(int y=0; y<columns; y++){
            cout << gameArray[i][y] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Doughnut::insertChar(int ro, int col, char z){
    gameArray[ro][col] = z;
}

void Doughnut::copyGame(){
    char copyArray[rows][columns];
    for(int i=0; i<rows; i++){
        for(int t=0; t<columns; t++){
            copyArray[i][t] = gameArray[i][t];
        }
    cout << endl;
    }
}

bool Doughnut::empty(){
    for(int t=0; t<rows; ++t){
        for(int d=0; d<columns; ++d){
            if(gameArray[t][d]=='X'){
                return false;
            }
        }
    }
    return true;
}

bool Doughnut::stable(){
    return stablizer;
}

char Doughnut::getChar(int a, int b){
    return copyArray[a][b];
}

void Doughnut::generation(){
    for(int raw=0; raw<rows; raw++){
        for(int yet=0; yet<columns; yet++){
            copyArray[raw][yet] = gameArray[raw][yet];
        }
    }

    int adding = 0;
    for(int z=0; z<rows; ++z){
        for(int w=0; w<columns; ++w){
            int neighbors = 0;
            if(z==0 && w==0){ //Left Upper Corner
                neighbors = neighbors + alive(0,1);
                neighbors = neighbors + alive(1,1);
                neighbors = neighbors + alive(1,0);
                neighbors = neighbors + alive(rows-1,columns-1);
                neighbors = neighbors + alive(rows-1,1);
                neighbors = neighbors + alive(rows-1,0);
                neighbors = neighbors + alive(0,columns-1);
                neighbors = neighbors + alive(1,columns-1);
            }
            else if(z==0 && w==columns-1){ //Right Upper Corner
                neighbors = neighbors + alive(0,columns-2);
                neighbors = neighbors + alive(1,columns-2);
                neighbors = neighbors + alive(1,columns-1);
                neighbors = neighbors + alive(rows-1,columns-1);
                neighbors = neighbors + alive(0,0);
                neighbors = neighbors + alive(1,0);
                neighbors = neighbors + alive(rows-1,0);
                neighbors = neighbors + alive(rows-1,columns-2);
            }
            else if(z==rows-1 && w==0){ //Left Lower Corner
                neighbors = neighbors + alive(rows-2,0);
                neighbors = neighbors + alive(rows-2,1);
                neighbors = neighbors + alive(rows-1,1);
                neighbors = neighbors + alive(rows-1,columns-1);
                neighbors = neighbors + alive(0,0);
                neighbors = neighbors + alive(0,1);
                neighbors = neighbors + alive(rows-1,columns-1);
                neighbors = neighbors + alive(rows-2,columns-1);
            }
            else if (z==rows-1 && w==columns-1){ //Right Lower Corner
                neighbors = neighbors + alive(z,w-1);
                neighbors = neighbors + alive(z-1,w-1);
                neighbors = neighbors + alive(z-1,w);
                neighbors = neighbors + alive(rows-1,0);
                neighbors = neighbors + alive(0,0);
                neighbors = neighbors + alive(0,columns-2);
                neighbors = neighbors + alive(0,columns-1);
                neighbors = neighbors + alive(rows-2,0);
            }
            else if(z==0){ //1st Row (5 Neighbors)
                neighbors = neighbors + alive(0,w-1);
                neighbors = neighbors + alive(1,w-1);
                neighbors = neighbors + alive(1,w);
                neighbors = neighbors + alive(1,w+1);
                neighbors = neighbors + alive(0,w+1);
                neighbors = neighbors + alive(rows-1,w);  //6
                neighbors = neighbors + alive(rows-1,w+1); //7
                neighbors = neighbors + alive(rows-1,w-1); //8
            }
            else if(w==0){ //1st Column (5 Neighbors)
                neighbors = neighbors + alive(z-1,0);
                neighbors = neighbors + alive(z+1,0);
                neighbors = neighbors + alive(z,1);
                neighbors = neighbors + alive(z+1,1);
                neighbors = neighbors + alive(z-1,1);
                neighbors = neighbors + alive(z,columns-1);  //6
                neighbors = neighbors + alive(z+1,columns-1); //7
                neighbors = neighbors + alive(z-1,columns-1); //8
            }
            else if(z==rows-1){ //Last Row
                neighbors = neighbors + alive(z-1,w);
                neighbors = neighbors + alive(z-1,w+1);
                neighbors = neighbors + alive(z-1,w-1);
                neighbors = neighbors + alive(z,w+1);
                neighbors = neighbors + alive(z,w-1);
                neighbors = neighbors + alive(0,w);  //6
                neighbors = neighbors + alive(0,w+1); //7
                neighbors = neighbors + alive(0,w-1); //8
            }
            else if(w==columns-1){ ///Last Column
                neighbors = neighbors + alive(z-1,w);
                neighbors = neighbors + alive(z+1,w);
                neighbors = neighbors + alive(z,w-1);
                neighbors = neighbors + alive(z-1,w-1);
                neighbors = neighbors + alive(z+1,w-1);
                neighbors = neighbors + alive(z,0);  //6
                neighbors = neighbors + alive(z+1,0); //7
                neighbors = neighbors + alive(z-1,0); //8

            }
            else{ //Has ALL 8 NEIGHBORS
                neighbors = neighbors + alive(z,w-1) + alive(z,w+1) + alive(z+1,w) + alive(z-1,w);
                neighbors = neighbors + alive(z-1,w-1) + alive(z+1,w-1) + alive(z-1,w+1) + alive(z+1,w+1);
            }

            char temp = getChar(z,w);
            if(neighbors<2){
                if(temp!='X'){
                    adding = adding -1;
                }
                insertChar(z,w,'-');
                adding = adding + 1;
            }
            else if(neighbors==3){
                if(temp=='X'){
                    adding = adding - 1;
                }
                insertChar(z,w,'X');
                adding = adding + 1;
            }
            else if(neighbors>3){
                if(temp!='X'){
                    adding = adding - 1;
                }
                insertChar(z,w,'-');
                adding = adding + 1;
            }
        }
    }
    generation_num = generation_num + 1;
    if(adding<1){
        stablizer = true;
    }
}

int Doughnut::alive(int a, int b){
    if(copyArray[a][b]=='X'){
        return 1;
    }
    return 0;
} 

string Doughnut::stringGame(){
    string total;
    total = total + "Generation Number: " + to_string(generation_num) + "\n";
    for(int i=0; i<rows; i++){
        for(int y=0; y<columns; y++){
           total = total + gameArray[i][y] + " ";
        }
        total = total + "\n";
    }
    return total;;
}