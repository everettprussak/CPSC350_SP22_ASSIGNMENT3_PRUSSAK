#include "doughnut.h"

Doughnut::Doughnut(){}

Doughnut::~Doughnut(){
    delete[] gameArray;
}

/*
Overloaded Constructor that takes in two ints, and stores
them in Columns and Rows.
We also give our other private variables some starting values that will
be switched during some of the main methods in the class.
We also create two 2d arrays, one being our main gameArray, 
and our other one which will copy the contents of gameArray 
when needed.
*/

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

/*
printGame is a method to print out each individual cell (element), inside
our main gameArray. It is of type void, so it will be directly printed to the terminal
when called.
*/

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

/*
insertChar is a method to simply store a character in our main gameArray.
*/

void Doughnut::insertChar(int ro, int col, char z){
    gameArray[ro][col] = z;
}

/*
copyGame is used to copy the main gameArray into our unused copyArray.
This is used because we want to keep a copy of the previous generation, so that
when switching the values in our current gameArray, we can use copyArray to get values of the
previous generation.
*/

void Doughnut::copyGame(){
    char copyArray[rows][columns];
    for(int i=0; i<rows; i++){
        for(int t=0; t<columns; t++){
            copyArray[i][t] = gameArray[i][t];
        }
    cout << endl;
    }
}

/*
empty is a method that tells us if any of the cells in our gameArray are being occupied
by the character 'X'. If it is, then it is not empty.
*/

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

/*
This method returns our private variable stablizer. Stablizer is 
defined more clearly later, but if its true, then the generation is "stable"
and the code can end.
*/

bool Doughnut::stable(){
    return stablizer;
}

/*
getChar is a method that uses our copyArray, and gets the character of a certain
cell, with two int parameters. One represents our row, and the other is our
column. It then returns whatever is in the cell being asked for.
*/

char Doughnut::getChar(int a, int b){
    return copyArray[a][b];
}

/*
generation is the main method in this class. 
It starts off by copying each cell of gameArray into
the same corresponding element in copyArray.

It then keeps an int variable to keep track of if the generation is stable
and goes through a nested for loop.
This nested for loop will use a method called "alive" multiple times, which is explained later.
If alive() of whichever values given is true, 1 will be added.
This is used to count the neighbors around the specific cell we are currently in.
After summing the neighbors of a specific cell, it 
follows the game rules and uses a number of if statements to 
determine if this cell should be dead or alive.
After that it will add 1 to our generation, and determine if the 
generation is stable or not. Then the loop will continue to do this continually.
*/


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

/*
alive is method that we use in the method generation that will determine if the copyArray
cell is alive 'X' or dead '-'. If it is alive, 1 is returned, else 0 is returned for dead.
*/

int Doughnut::alive(int a, int b){
    if(copyArray[a][b]=='X'){
        return 1;
    }
    return 0;
} 

/*
stringGame is a method that I used for when writing to a file. It is very similar
to printGame, but instead of printing to the terminal, it collects it as
a large string and returned.
*/

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