#ifndef MIRROR_H
#define MIRROR_H

#include <iostream>
using namespace std;

class Mirror{
    public:
        Mirror();
        Mirror(int a, int b);
        ~Mirror();
        void printGame();
        void copyGame();
        void insertChar(int a, int b, char c);
        bool empty();
        bool stable();
        void generation();
        int alive(int a, int b);
        char getChar(int a, int b);
        string stringGame();
    private:
        char **gameArray;
        char **copyArray;
        int columns;
        int rows;
        bool stablizer;
        int generation_num;
};

#endif