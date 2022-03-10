#ifndef DOUGHNUT_H
#define DOUGHNUT_H

#include <iostream>
using namespace std;

/*
Simple Header Class for the Doughnut Variation of Gamemode.
*/

class Doughnut{
    public:
        Doughnut();
        Doughnut(int a, int b);
        ~Doughnut();
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