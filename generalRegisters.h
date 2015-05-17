#ifndef GENERALREGISTERS_H
#define GENERALREGISTERS_H

#include<iostream>
#include<allegro.h>
#include<fstream>
using namespace std;
class generalRegisters                                                  // General Purpose Register Class
{
  public:
    ofstream out;
    short int myReg[16];
    generalRegisters()                                                // Contructor to set the default values for operations to registers.
    {
     for(int i=0;i<16;i++)
        myReg[i]=0;
        out.open("Output.txt",ios::app);
    }
    ~generalRegisters()
    {
        out.close();
    }
    short int* selectRegisters(int RegCode)                           // Use to select register to perform operation on
     {
        if(RegCode<16)
        {
            return &myReg[RegCode];                                   //Returing the adress of selected registers
        }
        else
        {
            cout<<"Invalid Register Code:  "<<RegCode<<endl;
            cout<<"Register Not Found Error..."<<endl;
            out<<"Invalid Register Code:  "<<RegCode<<endl;
            out<<"Register Not Found Error..."<<endl;

            //exit(0);
        }
    }

    void printRegs();


    void printRegsAllegro(BITMAP * fakeDisplay);
    void printRegsAllegro2(BITMAP * fakeDisplay);                                                  // Register Printing Function after each Instruction

};

#endif // GENERALREGISTERS_H
