#include "classic.h"
#include "doughnut.h"
#include "mirror.h"
#include "fileio.h"
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <algorithm>
#include <ctime>

int main(int argc, char** argv){

    string random;
    FileIO *file1 = new FileIO();
    cout << "Random Configuration? (Answer in: YES or NO)" << endl;
    cin >> random;
    cout << endl;
    if(random=="YES" || random=="Yes" || random=="YEs" || random == "yes"){
        srand(time(NULL));
        int row, column, ro, co;
        float density;
        int cells;
        string gamemode;
        string outputting;
        cout << "Enter Number of Rows: " << endl;
        cin >> row;
        cout << endl;
        cout << "Enter Numbr of Columns: " << endl;
        cin >> column;
        cout << endl;
        cout << "Enter Starting Density between 0 and 1: " << endl;
        cin >> density;
        cout << endl;
        cout << "Classic, Doughnut, or Mirror: " << endl;
        cin >> gamemode;
        cout << endl;
        cout << "Pause, Delay, or Output? (Type as seen): " << endl;
        cin >> outputting;
        cout << endl;
        string outfile;
        if(outputting=="Output"||outputting=="output"){
            cout << "Outputing File Name: " << endl;
            cin >> outfile;
        }
        cells = density * row * column;
        if(gamemode=="Classic" || gamemode=="classic" || gamemode=="CLASSIC"){
            Classic *c = new Classic(row,column);
            string total_contents;
            for(int t=0; t<row; ++t){
                for(int r=0; r<column; ++r){
                    c->insertChar(t,r,'-');
                }
            }
            for(int i=0; i<cells+1; ++i){
                ro = rand() % row;
                co = rand() % column;
                while(c->alive(ro,co)){
                    ro = rand() % row;
                    co = rand() % column;
                }
                c->insertChar(ro,co,'X');
            }
            
            if(outputting!="output" && outputting!="Output" && outputting!="OUTPUT"){
                c->printGame();
            }
            string gametostring;
            gametostring = c->stringGame();

            while(c->empty()!=1 && c->stable()!=1){
                if(outputting=="pause"||outputting=="Pause"||outputting=="PAUSE"){
                    system("read -p 'Press Enter to continue...' var");
                    c->generation();
                    c->printGame();
                    continue;
                }

                else if(outputting=="delay"||outputting=="Delay"||outputting=="DELAY"){
                    sleep(2);
                    c->generation();
                    c->printGame();
                    continue;
                }
                else if(outputting=="output" || outputting=="OUTPUT" || outputting=="Output"){
                    total_contents = total_contents + gametostring;
                    c->generation();
                    gametostring = c->stringGame();
                    total_contents = total_contents + gametostring;
                    gametostring = "";
                    file1->writeTo(outfile,total_contents);
                    continue;
                }

                else{
                    c->generation();
                    c->printGame();
                    continue;
                }
            }
            c->~Classic();
        }
        else if(gamemode=="Mirror" || gamemode=="mirror" || gamemode=="MIRROR"){
            Mirror *m = new Mirror(row,column);
            string total_contents;
            for(int t=0; t<row; ++t){
                for(int r=0; r<column; ++r){
                    m->insertChar(t,r,'-');
                }
            }
            for(int i=0; i<cells+1; ++i){
                ro = rand() % row;
                co = rand() % column;
                while(m->alive(ro,co)){
                    ro = rand() % row;
                    co = rand() % column;
                }
                m->insertChar(ro,co,'X');
            }
            
            if(outputting!="output" && outputting!="Output" && outputting!="OUTPUT"){
                m->printGame();
            }
            string gametostring;
            gametostring = m->stringGame();

            while(m->empty()!=1 && m->stable()!=1){
                if(outputting=="pause"||outputting=="Pause"||outputting=="PAUSE"){
                    system("read -p 'Press Enter to continue...' var");
                    m->generation();
                    m->printGame();
                    continue;
                }

                else if(outputting=="delay"||outputting=="Delay"||outputting=="DELAY"){
                    sleep(2);
                    m->generation();
                    m->printGame();
                    continue;
                }

                else if(outputting=="output" || outputting=="OUTPUT" || outputting=="Output"){
                    total_contents = total_contents + gametostring;
                    m->generation();
                    gametostring = m->stringGame();
                    total_contents = total_contents + gametostring;
                    gametostring = "";
                    file1->writeTo(outfile,total_contents);
                    continue;
                }

                else{
                    m->generation();
                    m->printGame();
                    continue;
                }
            }
            m->~Mirror();
        }
        else{
            Doughnut *d = new Doughnut(row,column);
            string total_contents;
            for(int t=0; t<row; ++t){
                for(int r=0; r<column; ++r){
                    d->insertChar(t,r,'-');
                }
            }
            for(int i=0; i<cells+1; ++i){
                ro = rand() % row;
                co = rand() % column;
                while(d->alive(ro,co)){
                    ro = rand() % row;
                    co = rand() % column;
                }
                d->insertChar(ro,co,'X');
            }
            if(outputting!="output" && outputting!="Output" && outputting!="OUTPUT"){
                d->printGame();
            }
            string gametostring;
            gametostring = d->stringGame();

            while(d->empty()!=1 && d->stable()!=1){
                if(outputting=="pause"||outputting=="Pause"||outputting=="PAUSE"){
                    system("read -p 'Press Enter to continue...' var");
                    d->generation();
                    d->printGame();
                    continue;
                }

                else if(outputting=="delay"||outputting=="Delay"||outputting=="DELAY"){
                    sleep(2);
                    d->generation();
                    d->printGame();
                    continue;
                }
                else if(outputting=="output" || outputting=="OUTPUT" || outputting=="Output"){
                    total_contents = total_contents + gametostring;
                    d->generation();
                    gametostring = d->stringGame();
                    total_contents = total_contents + gametostring;
                    gametostring = "";
                    file1->writeTo(outfile,total_contents);
                    continue;
                }

                else{
                    d->generation();
                    d->printGame();
                    continue;
                }
            }
            d->~Doughnut();
        }

    }
    else{
        string file;
        cout << "Enter File Name (ex: myfile.txt)" << endl;
        cin >> file;
        cout << endl;
        FileIO *file1 = new FileIO();
        string content = file1->process(file);
        string mode;
        cout << "Classic, Doughnut, or Mirror" << endl;
        cin >> mode;
        cout << endl;
        string pause;
        cout << "Pause? (Answer: YES or NO)" << endl;
        cin >> pause;
        cout << endl;
        string delay;
        string output;
        string out_file;
        if(pause=="no"||pause=="No"||pause=="NO"){
            
            cout << "Small Delay? (Answer: YES or NO)" << endl;
            cin >> delay;
            cout << endl;
            if(delay=="NO"||delay=="No"||delay=="no"){
                cout << "Output File? (Answer YES or NO)" << endl;
                cin >> output;
                cout << endl;
                if(output=="YES"||output=="Yes"||output=="yes"){
                    cout << "Output File Name: (ex:output.txt)" << endl;
                    cin >> out_file;
                    cout << endl;
                }
            }
        }
        int rows = file1->getRows();
        int cols = file1->getColumns();
        string gametostring;
        content.erase(remove(content.begin(), content.end(), '\n'), content.end());
        if(mode=="Classic"||mode=="classic"){
            Classic *c = new Classic(rows,cols);
            string total_contents;
            int count = 0;
            for(int i=0; i<rows; i++){
                for(int b=0; b<cols; b++){
                    c->insertChar(i,b,content[count]);
                    count = count + 1;
                }
            }

            if(output!="Yes" && output!="YES" && output!="yes"){
                c->printGame();
            }

            gametostring = c->stringGame();

            while(c->empty()!=1 && c->stable()!=1){
                if(pause=="YES"||pause=="Yes"||pause=="yes"){
                    system("read -p 'Press Enter to continue...' var");
                    c->generation();
                    c->printGame();
                    continue;
                }

                else if(delay=="Yes"||delay=="YES"||delay=="yes"){
                    sleep(2);
                    c->generation();
                    c->printGame();
                    continue;
                }
                else if(output=="Yes" || output=="YES" || output=="yes"){
                    total_contents = total_contents + gametostring;
                    c->generation();
                    gametostring = c->stringGame();
                    total_contents = total_contents + gametostring;
                    gametostring = "";
                    file1->writeTo(out_file,total_contents);
                    continue;
                }

                else{
                    c->generation();
                    c->printGame();
                    continue;
                }
            }

             system("read -p 'Press Enter to Exit...' var");
             c->~Classic();
        }

        else if(mode=="Doughnut"||mode=="doughnut"){
            Doughnut *d = new Doughnut(file1->getRows(), file1->getColumns());
            int count = 0;
            string total_contents;
            for(int i=0; i<rows; i++){
                for(int b=0; b<cols; b++){
                   d->insertChar(i,b,content[count]);
                    count = count + 1;
                }
            }

            if(output!="Yes" && output!="YES" && output!="yes"){
                d->printGame();
            }

            gametostring = d->stringGame();

            while(d->empty()!=1 && d->stable()!=1){
                if(pause=="YES"||pause=="Yes"||pause=="yes"){
                    system("read -p 'Press Enter to continue...' var");
                    d->generation();
                    d->printGame();
                    continue;
                }

                else if(delay=="Yes"||delay=="YES"||delay=="yes"){
                    sleep(2);
                    d->generation();
                    d->printGame();
                    continue;
                }
                else if(output=="Yes" || output=="YES" || output=="yes"){
                    total_contents = total_contents + gametostring;
                    d->generation();
                    gametostring = d->stringGame();
                    total_contents = total_contents + gametostring;
                    gametostring = "";
                    file1->writeTo(out_file,total_contents);
                    continue;
                }

                else{
                    d->generation();
                    d->printGame();
                    continue;
                }

            }
             system("read -p 'Press Enter to Exit...' var");
             d->~Doughnut();
        }

        else{
            Mirror *m = new Mirror(file1->getRows(), file1->getColumns());
            int count = 0;
            string total_contents;
            for(int i=0; i<rows; i++){
                for(int b=0; b<cols; b++){
                    m->insertChar(i,b,content[count]);
                    count = count + 1;
                }
            }
            if(output!="Yes" && output!="YES" && output!="yes"){
                m->printGame();
            }

            gametostring = m->stringGame();

            while(m->empty()!=1 && m->stable()!=1){
                if(pause=="YES"||pause=="Yes"||pause=="yes"){
                    system("read -p 'Press Enter to continue...' var");
                    m->generation();
                    m->printGame();
                    continue;
                }

                else if(delay=="Yes"||delay=="YES"||delay=="yes"){
                    sleep(2);
                    m->generation();
                    m->printGame();
                    continue;
                }
                else if(output=="Yes" || output=="YES" || output=="yes"){
                    total_contents = total_contents + gametostring;
                    m->generation();
                    gametostring = m->stringGame();
                    total_contents = total_contents + gametostring;
                    gametostring = "";
                    file1->writeTo(out_file,total_contents);
                    continue;
                }

                else{
                    m->generation();
                    m->printGame();
                    continue;
                }
            }
             system("read -p 'Press Enter to Exit...' var");
             m->~Mirror();
        }
    }

    return 0;
}