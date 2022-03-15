#include "classic.h"
#include "doughnut.h"
#include "mirror.h"
#include "fileio.h"
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <algorithm>
#include <ctime>
#include<algorithm>
#include<stdio.h>


/*
Main method uses a number of for loops, objects (classes), if statements and more to do the
overall job for the Game of Life.

It starts by asking the User a number of questions (Gamemode, Input, Output, Pause, etc), 
and stores the responses in variables.
*/

int main(int argc, char** argv){
    string random;
    string gamemode;
    string output_type;
    string content;
    string outfile;
    int rows, columns;
    int counter = 0;
    FileIO file1;

    cout << "Random Generated Plot or File Input: " << endl;
    cout << "Respond 'Random' or 'File'" << endl;        
    cin >> random;
    cout << endl;

/* If user wants to use input file, the contents use the FileIO Class, and gets a string returned.
The string uses .erase and remove to get rid of the newline characters. */
    if(random=="File"||random=="file"||random=="FILE"){
        string infile;
        cout << "Enter Input File Name: " << endl;
        cin >> infile;
        cout << endl;
        content = file1.process(infile); //using FileIO class "process" method to get a string of the file
        if(content=="unsuccessful"){ //Program will not continue as the file input had something wrong with it
            return -1; //either the txt file was formatted wrong or did not exist.
        }
        rows = file1.getRows();
        columns = file1.getColumns();
        content.erase(remove(content.begin(), content.end(), '\n'), content.end()); //Takes away newline characters from string
    }

/* The user wants to use random configuration instead. They are asked for row, columns, and Population Density
I use a method srand and rand to that I researched online, and will give the grid a random plot using the 
density the user wants.
*/
    else{
        int alive, randomNum;
        int count = 0;
        float pop;
        cout << "Enter Number of Rows: " << endl;
        cin >> rows;
        cout << endl;
        cout << "Enter Number of Columns: " << endl;
        cin >> columns;
        cout << endl;
        cout << "Enter Decimal for Population Density: " << endl;
        cin >> pop;
        cout << endl;
        int cells = rows*columns;
        alive = cells * pop; //This is the amount of cells that will start alives
        char randomArray[cells];
        srand(time(NULL)); //starting for random generator I am using.
        for(int i=0; i<cells; ++i){ //This for loop creates an array of only '-' prior to placing alive cells
            randomArray[i] = '-';
        }
        while(count<alive){ //this loop will place random alive cells 'X' in the 1d array.
            randomNum = rand() % cells;
            if(randomArray[randomNum]!='X'){ //This is for checking to make sure the random number is unique
                    randomArray[randomNum] = 'X';
                    count++;
            }
        }
        for(int f=0; f<cells; f++){ //creating the content string from the 1d array
            content = content + randomArray[f];
        }
    }
    cout << endl;
    cout << "Classic, Doughnut, or Mirror: " << endl;
    cout << "Respond 'Classic', 'Doughnut', or 'Mirror'" << endl;
    cin >> gamemode;
    cout << endl;
    cout << "Pause, Delay, Output File, or Terminal: " << endl;
    cout << "Respond 'Pause', 'Delay', 'Output', or 'Terminal'" << endl;
    cin >> output_type;
    if(output_type=="Output"||output_type=="output"||output_type=="OUTPUT"){
        cout << "Enter Output File Name: " << endl;
        cin >> outfile;
        cout << endl;
    }

/*
Here are where the three gamemodes split into their own classes.
For each, the content from the input file or random configuration is 
inserted into each individual cell for the gamemode.
Depending on the output type of the game, it will vary. 
However it goes through the generation, and then prints to either the screen
or the output file that the user specified. If the game is not a infitie game, then
the exit message is displayed, and the the specified gamemode is destructed.
*/
    if(gamemode=="Classic"||gamemode=="classic"||gamemode=="CLASSIC"){
        Classic *cla = new Classic(rows,columns); //creating the class type
        for(int i=0; i<rows; ++i){
            for(int y=0; y<columns; ++y){
                char temp = content[counter];
                counter++;
                cla->insertChar(i,y,temp); //inserting from our 1d array, to make a 2d array in the class
            }
        }
        if(output_type!="output" && output_type!="Output" && output_type!="OUTPUT"){
                cla->printGame(); //If the user wants output file, then The contents will not print on the terminal
        }

        string gametostring = cla->stringGame();  //this is unique to output file method.
        string total_contents;

        while(cla->empty()!=1 && cla->stable()!=1){ //The loop will continue until it is empty or stable
            if(output_type=="Pause"||output_type=="PAUSE"||output_type=="pause"){
                system("read -p 'Press Enter to continue...' var"); //makes the user click 'enter' to continue
                cla->generation(); //new generation is generated from the class
                cla->printGame(); //genreration is printed to terminal
                continue;
            }
            else if(output_type=="Delay"||output_type=="delay"||output_type=="DELAY"){
                sleep(2); //This will make a 2 second delay until the next line of code
                cla->generation(); //new generation is generated from the class
                cla->printGame(); //genreration is printed to terminal
                continue;
            }
            else if(output_type=="output"||output_type=="Output"||output_type=="OUTPUT"){
                total_contents = total_contents + gametostring;
                cla->generation();
                gametostring = cla->stringGame();
                total_contents = total_contents + gametostring;
                gametostring = "";
                file1.writeTo(outfile,total_contents);
                continue;

            }
            else{ //This is assuming that we are using terminal, and it is continually printed onto the screen
                cla->generation(); 
                cla->printGame();
                continue;
            }
        }
        system("read -p 'Press Enter to Exit...' var");
        cla->~Classic();
    }

    else if(gamemode=="Doughnut"||gamemode=="doughnut"||gamemode=="DOUGHNUT"||gamemode=="Donut"||gamemode=="donut"){
        Doughnut *don = new Doughnut(rows,columns);
        for(int i=0; i<rows; ++i){
            for(int y=0; y<columns; ++y){
                char temp = content[counter];
                counter++;
                don->insertChar(i,y,temp);
            }
        }
        if(output_type!="output" && output_type!="Output" && output_type!="OUTPUT"){
                don->printGame();
        }

        string gametostring = don->stringGame();
        string total_contents;

        while(don->empty()!=1 && don->stable()!=1){
            if(output_type=="Pause"||output_type=="PAUSE"||output_type=="pause"){
                system("read -p 'Press Enter to continue...' var");
                don->generation();
                don->printGame();
                continue;
            }
            else if(output_type=="Delay"||output_type=="delay"||output_type=="DELAY"){
                sleep(2);
                don->generation();
                don->printGame();
                continue;
            }
            else if(output_type=="output"||output_type=="Output"||output_type=="OUTPUT"){
                total_contents = total_contents + gametostring;
                don->generation();
                gametostring = don->stringGame();
                total_contents = total_contents + gametostring;
                gametostring = "";
                file1.writeTo(outfile,total_contents);
                continue;

            }
            else{
                don->generation();
                don->printGame();
                continue;
            }
        }
        system("read -p 'Press Enter to Exit...' var");
        don->~Doughnut();
    }

    else{
        Mirror *mir = new Mirror(rows,columns);
        for(int i=0; i<rows; ++i){
            for(int y=0; y<columns; ++y){
                char temp = content[counter];
                counter++;
                mir->insertChar(i,y,temp);
            }
        }
        if(output_type!="output" && output_type!="Output" && output_type!="OUTPUT"){
                mir->printGame();
        }

        string gametostring = mir->stringGame();
        string total_contents;

        while(mir->empty()!=1 && mir->stable()!=1){
            if(output_type=="Pause"||output_type=="PAUSE"||output_type=="pause"){
                system("read -p 'Press Enter to continue...' var");
                mir->generation();
                mir->printGame();
                continue;
            }
            else if(output_type=="Delay"||output_type=="delay"||output_type=="DELAY"){
                sleep(2);
                mir->generation();
                mir->printGame();
                continue;
            }
            else if(output_type=="output"||output_type=="Output"||output_type=="OUTPUT"){
                total_contents = total_contents + gametostring;
                mir->generation();
                gametostring = mir->stringGame();
                total_contents = total_contents + gametostring;
                gametostring = "";
                file1.writeTo(outfile,total_contents);
                continue;

            }
            else{
                mir->generation();
                mir->printGame();
                continue;
            }
        }
        system("read -p 'Press Enter to Exit...' var");
        mir->~Mirror();
    }

    return 1;
}
        
