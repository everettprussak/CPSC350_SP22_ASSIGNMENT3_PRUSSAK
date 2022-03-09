#include "fileio.h"
#include <fstream>

FileIO::FileIO(){
    //nothing
}

string FileIO::process(string filename){
    ifstream infile;
    string line;
    string content;
    string r, c;
    infile.open(filename);
    getline(infile,line);
    r = line;
    rows = stoi(r);
    getline(infile,line);
    c = line;
    columns = stoi(c);
    while(getline(infile,line)){
        content = content + line + "\n";
    }
    infile.close();
    return content;
}

void FileIO::writeTo(string filen, string contents){
    ofstream out_file1;
    out_file1.open(filen);
    out_file1 << contents;
    out_file1.close();
}

int FileIO::getRows(){
    return rows;
}

int FileIO::getColumns(){
    return columns;
}