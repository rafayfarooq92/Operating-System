#ifndef SPLREGISTERS_H
#define SPLREGISTERS_H

#include<iostream>
#include<fstream>
#include <bitset>
#include<allegro.h>
using namespace std;

class splRegisters                                                          //Special Purpose registers
{
  public:
    unsigned short int codeBase,codeLimit,codeCounter;                      //Code Segment Registers
    unsigned short int stackBase,stackCounter,stackLimit;                   //Stack Segment Registers
    unsigned short int flags;                                               //Flags
    unsigned short int dataBase,dataLimit;                                  //DatasegmentRegisters
    unsigned short int myReg[6];
    ofstream out;
    bitset<8>   bits;
    int myF[4];
    splRegisters()                                                          //Constructor for initializations.
    {
        codeBase=0;
        codeLimit=0;
        flags=0;

        stackBase=0;                                                    //Setting code segment to the later part
        stackLimit=0;
        dataBase=0;
        dataLimit=0;                                                        //Setting data segment to the upper part
        stackCounter=stackBase;
        codeCounter=0;
        for(int i=0;i<4;i++)
        myF[i]=0;
        bitset<8> temp(flags);                                              //Making flag to be available to set bits
        bits=temp;
        out.open("Output.txt",ios::app);
        for(int i=10;i<16;i++)
        myReg[i]=0;
    }
    ~splRegisters()
    {
        out.close();
    }
    int getZeroFlag()                                                       //Checking Zero Flag
    {
            return bits[1];
    }
    int getCarryFlag()                                                      //Checking Carry Flag
    {
            return bits[0];
    }
    int getSignFlag()                                                       //Checking Signed Flag
    {
            return bits[2];
    }


    void PrintAllRegsAllegro(BITMAP * fakeDisplay);
    void printFlagAllegro(BITMAP * fakeDisplay);


    int getOvrFlag();                                                        //Checking Overflow Flag


    void setCF(short int myVal)                                             //Setting CF
    {
        bitset<16> myBits(myVal);
        if(myBits[15]==1)                                                   //If MSB is 1 set the carry flag
        {
            bits[0]=1;
            myF[0]=1;
        }
        else
        {
            bits[0]=0;
            myF[0]=0;
        }


    }

    void setS(short int result)                                             //Setting Sign and Zero flag
    {
        if(result<0)                                                        //Checking if the number was negative
        {
            bits.set(2,1);
            myF[2]=1;
        }
        else
        {
            bits.set(2,0);
            myF[2]=0;
        }
        if(result==0)                                                       //Checking if the number was zero
        {
            bits.set(1,1);
            myF[1]=1;
        }
        else{
            bits.set(1,0);
            myF[1]=0;
        }

    }
    void setOF(long int myVal)                                              // Setting Overflow flag.
    {
        if(myVal< -32768 ||myVal>32767)                                     //Checking if the number was getting out of range
        {
            bits[3]=1;
            myF[3]=1;
        }
        else
        {
            bits[3]=0;
            myF[3]=0;
        }
    }
    void printFlag()                                                        // Printing Flag Registers.
    {
        cout<<endl<<endl;
        cout<<"Carry Flag: "<<bits[0]<< "\t\tZero Flag:"<<bits[1]<<endl;
        cout<<"Signed Flag: "<<bits[2]<< "\t\tOverflow Flag:"<<bits[3]<<endl;
        cout<<endl;

    }
    void PrintAllRegs()
    {
            cout<<"CodeCounter:\t"<<codeCounter<<endl;
            cout<<"CodeLimit:\t"<<codeLimit<<endl;
            cout<<"CodeBase:\t"<<codeBase<<endl;
            cout<<"StactCounter:\t"<<stackCounter<<endl;
            cout<<"StactBase:\t"<<stackBase<<endl;
            cout<<"StactLimit:\t"<<stackLimit<<endl;
            cout<<"DataBase:\t"<<dataBase<<endl;
            cout<<"DataLimit:\t"<<dataLimit<<endl;
            out<<"CodeCounter:\t"<<codeCounter<<endl;
            out<<"CodeLimit:\t"<<codeLimit<<endl;
            out<<"CodeBase:\t"<<codeBase<<endl;
            out<<"StactCounter:\t"<<stackCounter<<endl;
            out<<"StactBase:\t"<<stackBase<<endl;
            out<<"StactLimit:\t"<<stackLimit<<endl;
            out<<"DataBase:\t"<<dataBase<<endl;
            out<<"DataLimit:\t"<<dataLimit<<endl;

    }
    void PrintAllRegsAllegro2(BITMAP * fakeDisplay);





};

#endif // SPLREGISTERS_H
