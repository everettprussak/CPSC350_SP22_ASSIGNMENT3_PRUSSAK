#ifndef FILEIO_H
#define FILEIO_H

#include <iostream>
using namespace std;

/*
Simple header class for FileIO
*/

class FileIO{
    public:
        FileIO();
        string process(string fileName);
        void writeTo(string filen, string contents);
        int getRows();
        int getColumns();
        int rows;
        int columns;
};

#endif