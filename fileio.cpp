#include "fileio.h"
#include <fstream>

FileIO::FileIO(){
    //nothing
}

/*
The string method process in FileIO is used to collect the data from an input file.
It uses "stoi" which converts the string number into an int.
It reads all of the content from the text file, and returns it.
*/

string FileIO::process(string filename){
    ifstream infile(filename);
    if(infile.fail()){
        cout << "File Does Not Exist!" << endl;
        return "unsuccessful";
    }
    string line, content, r, c;
    try{
        getline(infile,line);
        r = line;
        rows = stoi(r);
        getline(infile,line);
        c = line;
        columns = stoi(c);
    }
    catch(exception &err){
        cout << "File in Wrong Type!" << endl;
        return "unsuccessful";
    }
    while(getline(infile,line)){
        content = content + line + "\n";
    }
    infile.close();
    return content;
}

/*
writeTo is used to simply write the contents of an entire game
into a file the user specifies.
*/

void FileIO::writeTo(string filen, string contents){
    ofstream out_file1;
    out_file1.open(filen);
    out_file1 << contents;
    out_file1.close();
}


/*
getRows() and getColumns() are both used to return either the rows
or columns. This is used in the main method to collect information
on how many rows and columns the input file had the plot be.
*/
int FileIO::getRows(){
    return rows;
}

int FileIO::getColumns(){
    return columns;
}