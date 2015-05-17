#ifndef MEMORYCLASS_H
#define MEMORYCLASS_H



//Sheikh Muhammad Usama (ID - 2119)
//Rafay Farooq (ID-2257)
//SECTION A
//OS PROJECT


#include<iostream>
#include<fstream>
#include <cstdio>
#include <iomanip>
#include <cstdlib>
#include <bitset>
#include<cmath>
#include<allegro.h>
#include<ctime>
#include<sstream>


#include <cstring>
#include "splRegisters.h"
#include "generalRegisters.h"
//#include "ExtraFunctions.h"
using namespace std;


/************************Circular Left Shift*********************************************
Taking Parameters: integer Temp which carries the values of be set
Returning: Long int after setting the bit of specific position
/*****************************************************************************************/
/*long int cirL(short int temp)                                       //CirL function
{
    bitset<8>   bits(temp);                                         //Set 8 bits of Temp
    temp=temp<<1;                                                   //Shift right by one
    bits=temp;                                                      //Stored 8 bits of temp in bits
    bits.set(0,bits[7]);                                            //Set 0 position with 7th position
    return bits.to_ulong();                                         // Returning Result in long int

}*/




/************************Circular Right Shift*********************************************
Taking Parameters: integer Temp which carries the values of be set
Returning: Long int after setting the bit of specific position
/*****************************************************************************************/
/*
long int cirR(short int temp)                                       //CirR Function
{
    bitset<8>   bits(temp);
    temp=temp>>1;                                                   //Circular Left Shift
    bits=temp;
    bits.set(7,bits[0]);                                              //Changing 7 position bit with 0th position bit
    return bits.to_ulong();                                         // Returning Result in Long int

}*/
/*-------------------------------------Additional Funtion for Easy Conversion of String-----------------*/
/*template< typename T >
string int_to_hex( T i )
{
  string myStr;
  stringstream stream;
  stream
         << setfill ('0') << setw(4)
         << hex << i;
         myStr=stream.str();
         if(i>65535 ||i<0)
         {

            myStr=myStr.substr(myStr.length()-4);

         }
  return myStr;
}*/
/*-----------------------------------Additional Funtion for Easy Sorting of Priority Queue-----------------*/
/*
void bubbleSort(unsigned char *array,int length)                    //Bubble sort function
{
    int i,j;
    for(i=2048;i<2048+length;i++)                                   //Queue start at memory indec 2048
    {
        for(j=2048;j<i;j++)
        {
            if(array[i]<array[j])
            {
                int temp=array[i];                                  //swap
                array[i]=array[j];
                array[j]=temp;
            }

        }

    }

}*/
/*-------------------------------------Additional Funtion for Easy Conversion of String-----------------*/
/*
template< typename M >
string int_to_hex2( M i )
{
  string myStr;
  stringstream stream;
  stream
         << setfill ('0') << setw(2)
         << hex << i;
         myStr=stream.str();
         if(i>65535 ||i<0)
         {

            myStr=myStr.substr(myStr.length()-2);

         }
  return myStr;
}*/

/*-----------------Additional Funtion for Reading two memory refrence and convert it to one-----------------*/

/*unsigned char myConv(char one,char two)
{
    int sum;

    if(one>=48 && one<=57)
    one=(one-48);
    else if(one>=97 && one <=124)
    one=(one-87);
    sum=(int)one;


    if(two>=48 && two<=57)
    two=(two-48);
    else if(two>=97 && two<=124)
    two=(two-87);
    sum=sum+((int)two*16);
    unsigned char myChar=sum;
    return myChar;

}*/
/*----------Additional Funtion for Easy Conversion of String from Char to Short Integer-----------------*/
/*short int StringToIntConverter2(string myChar)                      // Function to convert the Hex string to int
{

    int base=16;
    int count=0,num=0,temp=0;
    short int result=0;
    int stringLength=strlen(myChar.c_str());
    stringLength--;
    while(stringLength>=0)
    {

        num=myChar[stringLength];
        if(num<59 && num >47)
        num -=48;
        else if(num>96 && num<103)
        num -=87;
        temp=pow(base,count);
        result +=    (temp*  num);
        count++;

        stringLength--;

    }

return result;

}*/
/*****************************************Memory Class******************************************************/
class memoryClass
{
    public:
    unsigned char myMemory[65536];
    int pageSize;
    string myStr;
    int PCBcounter;
    int userCounter;
    ifstream myFile;
    ofstream out;                                                //Declaring file object
    BITMAP * buffer;
    short int PQhead;                                                 //Priority Queue of Head and Tail
    short int PQtail;
    short int Pelements;
    bool Pfull;

    int noOfDataFrames;
    int noOfCodeFrames;
    int noOfProcess;
    short int Relements;
    short int rear;
    short int front;
    short int maxSize;

    bool checkStack;
    string goodVal;





/***********************************PCB of Process**************************************************/
    int priority;
    int PID;
    string nameOfProcess;
    splRegisters splRegs;
    generalRegisters regs;
    int execution_time;
    int waiting_time;
    int freePCB[8];
    int processIDs[8];

	friend	istream& operator <<(istream& in, memoryClass memory)
	{
	    in>>memory.nameOfProcess;
	}
	int frameTablePointer;


/***************************************************************************************************/

    /**************************Memory Class Constructor********************/
    memoryClass()
    {

        pageSize=128;                                                // Page Size 128KB
        PQhead=2048;
        PQtail=2048;
        Pfull=false;
        Pelements=0;
        for(int i=0;i<8;i++)
        {
            freePCB[i]=0;
            processIDs[i]=0;
        }
        PCBcounter=0;                                               //PCB counter starting from index 0 of memoryCounter starts at 3200
        userCounter=3200;                                           //User Counter starts at 3200= 19 frames of Kernel Memory * 128 =3200
        frameTablePointer=2176;                                     //Free Frame Table starts at 2176
        maxSize=8;                                                  //Max Size is 8 process
        Relements=0;
        rear=-1;

      //  ExtraFunctions eF;
        front=-1;
        checkStack=false;
        execution_time=0;
        waiting_time=0;
        out.open("Output.txt",ios::app);
        buffer=create_bitmap(800,600);


        for(int i=0;i<65536;i++)
        {
            myMemory[i]='\0';
        }
        for(int i=2176;i<2688;i++)                                  //Initializing 512 Frames of Memory
        {
            myMemory[i]=0;
        }
    }
    int debugOnceAll()
    {
        while(!PisEmpty())
        {
            priority=Premove();
            PCBcounter=0;
                                                     // Representing Priority of Process in a PCB and 0 represent ID
            for(int j=0;j<8;j++)
            {
                if(myMemory[PCBcounter+1]!=priority){
                PCBcounter = ((j+1)*pageSize);
                }
                else{
                if(freePCB[(PCBcounter+1)/pageSize]==1 && myMemory[99+PCBcounter]==0)
                {
                    break;
                }
                }
            }
        BITMAP * fakeDis=create_bitmap(600,500);
        clear_to_color(fakeDis, makecol(170,231,216));
            textprintf_ex(fakeDis,font,0,0,makecol(0,0,0),-1,"Starting Process Of ID : %d",myMemory[PCBcounter]);
            //cout<<"Starting Process of ID: \t"<<proID<<endl;
            //out<<"Starting Process of ID: \t"<<proID<<endl;
            loadIt(PCBcounter);
/*******************************Linear Adress Translation***************************/
            int tempValue=PCBcounter/128;
            int frameNum=(1088+(tempValue*pageSize));
            if(splRegs.codeCounter==0)
            splRegs.codeCounter=myMemory[frameNum]*pageSize;
            while(splRegs.codeCounter<splRegs.codeLimit+splRegs.codeBase){
            int myInt=myMemory[splRegs.codeCounter];
/*************************************************************************************/
            execution_time=execution_time+2;                          //Calculating Execution Time
            waiting_time=waiting_time+2;                              //Calculating Waiting Time
            splRegs.codeCounter++;
            int exception_check=intruction(myInt);                        //Executing instruction specified by the opCODE
/*-----------------------------------Exceptional Checking----------------------------*/

            if(execptionHandling2(exception_check,tempValue)!=0)break;
            //blit(fakeDis,screen,0,0,200,50,600,500);

            regs.printRegsAllegro2(fakeDis);
            splRegs.PrintAllRegsAllegro2(fakeDis);
            if((readkey() >> 8 ) == KEY_E){
                Pinsert(myMemory[(PCBcounter*128)+1]);
                bubbleSort(myMemory,Pelements);
                PCBcounter += 4;
                loadGeneralRegInMemory();
                loadSpecialRegInMemory();
                return 0;
                };
            clear_to_color(fakeDis, makecol(170,231,216));
            }
/*-----------------------------------------------------------------------------------------*/
            //HERE IS IT IS POSSIBLE THAT I WILL CHECK THE CONDITION IF THE MYINT IS EQUALS TO -1 I WILL PRINT THE ERROR OR MAKE THE MEMORY NULL


            deallocation(tempValue);                                //De-Allocation of Memory


            /*-------------------------Printing Waiting and Execution Time-------------------*/
            myStr=int_to_hex(execution_time);
            efficientStore(myStr,(PCBcounter+65));
            myStr=int_to_hex(waiting_time-execution_time);
            efficientStore(myStr,(PCBcounter+67));
            textprintf_ex(fakeDis,font,0,450,makecol(0,0,0),-1,"Execution Time %d",execution_time);
            textprintf_ex(fakeDis,font,0,475,makecol(0,0,0),-1,"Waiting Time %d",waiting_time-execution_time);


           // cout<<"This is Waiting Time "<<waiting_time-execution_time<<endl;

            //out<<"This is Execution Time "<<execution_time<<endl;
            //out<<"This is Waiting Time "<<waiting_time-execution_time<<endl;
                                                   //Setting counter to Zero for next counting
            /**********************************************************************************/
        }
        int counter=0;

        while(!RisEmpty())
        {

            PID=dequeue();

            PCBcounter=0;
                                                     // Representing Priority of Process in a PCB and 0 represent ID
            for(int j=0;j<8;j++)
            {
                if(myMemory[PCBcounter]!=PID){
                PCBcounter = ((j+1)*pageSize);
                }
                else{
                if(freePCB[(PCBcounter+1)/pageSize]==1)
                {
                    break;
                }
                }
            }
        BITMAP * fakeDis=create_bitmap(600,500);
        clear_to_color(fakeDis, makecol(170,231,216));
            textprintf_ex(fakeDis,font,0,0,makecol(0,0,0),-1,"Starting Process Of ID : %d",myMemory[PCBcounter]);
            //cout<<"Starting Process of ID: \t"<<proID<<endl;
            //out<<"Starting Process of ID: \t"<<proID<<endl;
            loadIt(PCBcounter);
/*******************************Linear Adress Translation***************************/
            int tempValue=PCBcounter/128;
            int frameNum=(1088+(tempValue*pageSize));
            if(splRegs.codeCounter==0)
            splRegs.codeCounter=myMemory[frameNum]*pageSize;
            while(splRegs.codeCounter<splRegs.codeLimit+splRegs.codeBase && counter!=8){
            int myInt=myMemory[splRegs.codeCounter];
/*************************************************************************************/
            execution_time=execution_time+2;                          //Calculating Execution Time
            waiting_time=waiting_time+2;                              //Calculating Waiting Time
            splRegs.codeCounter++;
            int exception_check=intruction(myInt);                        //Executing instruction specified by the opCODE
/*-----------------------------------Exceptional Checking----------------------------*/

            //(exception_check,tempValue);
            if(execptionHandling2(exception_check,tempValue)!=0)break;
            /*-----------------------------------------------------------------------------------------*/
            counter += 2;
            regs.printRegsAllegro2(fakeDis);
            splRegs.PrintAllRegsAllegro2(fakeDis);
            if((readkey() >> 8 ) == KEY_E){
                enqueue(myMemory[PCBcounter*128]);
                PCBcounter += 4;
                loadGeneralRegInMemory();
                loadSpecialRegInMemory();
                return 0;
                };
            clear_to_color(fakeDis, makecol(170,231,216));
            }



            myStr=loading2Bytes((PCBcounter+66));
            int prev=StringToIntConverter2(myStr);
            prev += execution_time;
            myStr=int_to_hex(prev);
            efficientStore(myStr,(PCBcounter+66));
            myStr=int_to_hex(waiting_time-execution_time);
            efficientStore(myStr,(PCBcounter+68));                  //68 is the location of  Waiting Time
            textprintf_ex(fakeDis,font,0,450,makecol(0,0,0),-1,"Execution Time %d",execution_time);
            textprintf_ex(fakeDis,font,0,475,makecol(0,0,0),-1,"Waiting Time %d",waiting_time-execution_time);


            if(splRegs.codeCounter==(splRegs.codeBase+splRegs.codeLimit))
            {
                unsigned short int myVar=splRegs.codeCounter;
                myVar -=1;                                            //Talking codeCounter to previous instrction
                if(myMemory[myVar]!=243 )                             //Checking if the last instruction was not END
                {
                    out<<"The Program Could not successfully terminate."<<endl;
                    cout<<"The Program Could not successfully terminate."<<endl;
                }

            deallocation(tempValue);                                 //De-Allocation of Memory

            }
            /*--------------------------------Finish the instrcution when counter==4--------*/

            if(counter==8 && splRegs.codeCounter!=(splRegs.codeBase+splRegs.codeLimit))
            {
                enqueue(myMemory[PCBcounter]);
                PCBcounter += 4;
                loadGeneralRegInMemory();
                loadSpecialRegInMemory();
                execution_time=0;
            }
            counter=0;

            //HERE IS IT IS POSSIBLE THAT I WILL CHECK THE CONDITION IF THE MYINT IS EQUALS TO -1 I WILL PRINT THE ERROR OR MAKE THE MEMORY NULL


            //deallocation(tempValue);                                //De-Allocation of Memory

            /*-------------------------Printing Waiting and Execution Time-------------------*/
           /* myStr=int_to_hex(execution_time);
            efficientStore(myStr,(PCBcounter+65));
            myStr=int_to_hex(waiting_time-execution_time);
            efficientStore(myStr,(PCBcounter+67));*/

           // counter=0;
           // cout<<"This is Waiting Time "<<waiting_time-execution_time<<endl;

            //out<<"This is Execution Time "<<execution_time<<endl;
            //out<<"This is Waiting Time "<<waiting_time-execution_time<<endl;
                                                   //Setting counter to Zero for next counting
            /**********************************************************************************/
        }

        /*******************************Executing Round Robin Queue*************************************/



    }

    void printProcess()
    {
        BITMAP * fakeDis=create_bitmap(600,500);
        BITMAP * image=load_bitmap("Images/MainScreenToWork.bmp",NULL);
        clear_to_color(fakeDis, makecol(170,231,216));
        textprintf_ex(fakeDis,font,0,0,makecol(255,0,0),-1,"All Process Loaded In Memory:");
        textprintf_ex(fakeDis,font,0,20,makecol(0,0,0),-1,"Process In Memory:");
        int height=20;
        for(int i=1;i<9;i++)
        {
            if(processIDs[i-1]!=0)
                textprintf_ex(fakeDis,font,0,(height*i)+20,makecol(0,0,0),-1,"PID: %d",processIDs[i-1]);
        }
        textprintf_ex(fakeDis,font,0,170,makecol(0,0,0),-1,"Process In Priority Queue:");
        int ABlock=0;
        textprintf_ex(fakeDis,font,250,0,makecol(0,0,0),-1,"Blocked Process:");

        for(int j=0;j<8;j++)
            {

                if(freePCB[(ABlock+1)/pageSize]==1 && myMemory[ABlock+99]==1)
                {
                   textprintf_ex(fakeDis,font,250,height*(j+1),makecol(0,0,0),-1,"PID : %d",myMemory[ABlock]);
                }
                ABlock = ((j+1)*pageSize);

            }

        //height=20;
        for(int i=1;i<9;i++)
        {
            int myLocation =(i-1)*128;

            if(myMemory[myLocation+1]>=0 && myMemory[myLocation+1]<=15 && myMemory[myLocation+1]!=0)
                textprintf_ex(fakeDis,font,0,(height*i)+170,makecol(0,0,0),-1,"PID: %d",myMemory[myLocation]);
            /*if(processIDs[i-1]<16 && processIDs[i-1]>0)
                textprintf_ex(fakeDis,font,0,(height*i)+170,makecol(0,0,0),-1,"PID: %d",processIDs[i-1]);*/
        }
        textprintf_ex(fakeDis,font,0,320,makecol(0,0,0),-1,"Process In RoundRobin Queue:");

        for(int i=1;i<9;i++)
        {

            int myLocation =(i-1)*128;

            if(myMemory[myLocation+1]>=16 && myMemory[myLocation+1]<=31 && myMemory[myLocation+1]!=0 )
                textprintf_ex(fakeDis,font,0,(height*i)+320,makecol(0,0,0),-1,"PID: %d",myMemory[myLocation]);


            /*if(processIDs[i-1]>15 && processIDs[i-1]<32 )
                textprintf_ex(fakeDis,font,0,(height*i)+320,makecol(0,0,0),-1,"PID: %d",processIDs[i-1]);*/
        }

        blit(fakeDis,image,0,0,200,50,600,500);
        blit(image,screen,0,0,0,0,800,600);

        readkey();

    }



     bool printPageTable(int proID)
    {

        bool find=false;
        PCBcounter=0;
        BITMAP * fakeDis=create_bitmap(600,500);
        BITMAP * image=load_bitmap("Images/MainScreenToWork.bmp",NULL);
        clear_to_color(fakeDis, makecol(170,231,216));

        for(int j=0;j<8;j++)
            {
                if(myMemory[PCBcounter]!=proID){
                PCBcounter = ((j+1)*pageSize);
                }
                else{
                if(freePCB[(PCBcounter+1)/pageSize]==1 && myMemory[PCBcounter+99]==0)
                {
                    find=true;
                    break;
                }
                }
            }
            if(find){
            textprintf_ex(fakeDis,font,0,0,makecol(0,0,0),-1,"Priting Data Page Table:");
            int tempVal=PCBcounter/pageSize;
            int pageTableCounter=1024+PCBcounter;
            int height=20;
            int i=1;
            while(myMemory[pageTableCounter]!=0)
            {
                textprintf_ex(fakeDis,font,0,height*i,makecol(0,0,0),-1,"Index:%d -- FrameNumb:%d",pageTableCounter,myMemory[pageTableCounter++]);
                textprintf_ex(fakeDis,font,220,height*i,makecol(0,0,0),-1,"Index:%d -- FrameNumb:%d",pageTableCounter,myMemory[pageTableCounter++]);

                i++;
            }
            textprintf_ex(fakeDis,font,0,280,makecol(0,0,0),-1,"Priting CODE Page Table:");

            pageTableCounter=1088+PCBcounter;
            i=1;
            while(myMemory[pageTableCounter]!=0)
            {
                textprintf_ex(fakeDis,font,0,(height*i)+300,makecol(0,0,0),-1,"Index:%d -- FrameNumb:%d",pageTableCounter,myMemory[pageTableCounter++]);
                textprintf_ex(fakeDis,font,220,(height*i)+300,makecol(0,0,0),-1,"Index:%d -- FrameNumb:%d",pageTableCounter,myMemory[pageTableCounter++]);

                i++;
            }


        blit(fakeDis,image,0,0,200,50,600,500);
        blit(image,screen,0,0,0,0,800,600);

        readkey();
    }
        return find;

    }



    void dumpFreeFrame()
    {
        int myInt=frameTablePointer+25;

        BITMAP * fakeDis=create_bitmap(600,500);
        BITMAP * image=load_bitmap("Images/MainScreenToWork.bmp",NULL);
        clear_to_color(fakeDis, makecol(170,231,216));
        textprintf_ex(fakeDis,font,0,0,makecol(255,0,0),-1,"All Free Frames In Memory:");
        textprintf_ex(fakeDis,font,0,20,makecol(0,0,0),-1,"Page1:");
        int height=8;
        bool full=false;
        for(int i=1;i<50;i++)
        {
            if(myInt<2685){
                //if(myMemory[myInt]==0)
                textprintf_ex(fakeDis,font,0,(height*i)+20,makecol(0,0,0),-1,"Frame#: %d | Frame#: %d | Frame#: %d | Frame#: %d ",myInt++,myInt++,myInt++,myInt++);
            }

            else
                full=true;
        }

        blit(fakeDis,image,0,0,200,50,600,500);
        blit(image,screen,0,0,0,0,800,600);

        readkey();
        if(!full){
        clear_to_color(fakeDis, makecol(170,231,216));
        textprintf_ex(fakeDis,font,0,0,makecol(255,0,0),-1,"All Free Frames In Memory:");
        textprintf_ex(fakeDis,font,0,20,makecol(0,0,0),-1,"Page2:");
        /*int myinteger=2176+26;
        for(int i=0;i<487;i++)
        {
            if(myMemory[myinteger]==0)
            cout<<(int)myMemory[myinteger]<<" "<<myinteger++<<endl;

        }*/
       /* for()
        {

        }*/
        for(int i=1;i<50;i++)
        {
                if(myInt<2685)
                textprintf_ex(fakeDis,font,0,(height*i)+20,makecol(0,0,0),-1,"Frame#: %d | Frame#: %d | Frame#: %d | Frame#: %d ",myInt++,myInt++,myInt++,myInt++);
            else
                full=true;
        }

        blit(fakeDis,image,0,0,200,50,600,500);
        blit(image,screen,0,0,0,0,800,600);

        readkey();
        }

    if(!full){
        clear_to_color(fakeDis, makecol(170,231,216));
        textprintf_ex(fakeDis,font,0,0,makecol(255,0,0),-1,"All Free Frames In Memory:");
        textprintf_ex(fakeDis,font,0,20,makecol(0,0,0),-1,"Page3:");

        for(int i=1;i<50;i++)
        {
             if(myInt<2685)
                textprintf_ex(fakeDis,font,0,(height*i)+20,makecol(0,0,0),-1,"Frame#: %d | Frame#: %d | Frame#: %d | Frame#: %d ",myInt++,myInt++,myInt++,myInt++);
            else{
                full=true;
                //return 0;
                }
        }

        blit(fakeDis,image,0,0,200,50,600,500);
        blit(image,screen,0,0,0,0,800,600);

        readkey();
        }


    }


    bool memoryDetails(int proID)
    {
        bool find=false;
        PCBcounter=0;
        BITMAP * fakeDis=create_bitmap(600,500);
        BITMAP * image=load_bitmap("Images/MainScreenToWork.bmp",NULL);
        clear_to_color(fakeDis, makecol(170,231,216));

        for(int j=0;j<8;j++)
            {
                if(myMemory[PCBcounter]!=proID){
                PCBcounter = ((j+1)*pageSize);
                }
                else{
                if(freePCB[(PCBcounter+1)/pageSize]==1 && myMemory[PCBcounter+99]==0)
                {
                    find=true;
                    break;
                }
                }
            }
            if(find){
                int length=(int)myMemory[PCBcounter+70];
                char * nameOfFile= new char[length];
                for(int i=0;i<length;i++)
                {
                    nameOfFile[i]=myMemory[PCBcounter+70+(i+1)];
                }
                nameOfFile[length]='\0';

                textprintf_ex(fakeDis,font,0,0,makecol(255,0,0),-1,"Process Name: ");
                textout_ex(fakeDis,font,nameOfFile,150,0,makecol(255,0,0),-1);
  /*              ofstream myNewFile;
                char * newFileName;
                strcpy(newFileName,nameOfFile);
                cout<<"A"<<newFileName<<endl;
                cout<<"B"<<nameOfFile<<endl;
                strcat(newFileName,"MD.txt");
                cout<<"A"<<newFileName<<endl;
                cout<<"B"<<nameOfFile<<endl;

*/
                //myNewFile.open(newFileName.c_str());
                /*myNewFile<<"Process Name:\n";
                myNewFile<<"Size Of PCB : 128BYTES : 128Bytes \n";
                myNewFile<<"ID Of Process: " << myMemory[PCBcounter]<<endl;
                myNewFile<<"Priority Of Process: "<<myMemory[PCBcounter+1]<<endl;
*/


                textprintf_ex(fakeDis,font,0,20,makecol(0,0,0),-1,"Size Of PCB: 128BYTES ");
                textprintf_ex(fakeDis,font,0,40,makecol(0,0,0),-1,"ID Of Process: %d ",myMemory[PCBcounter++]);
                textprintf_ex(fakeDis,font,0,60,makecol(0,0,0),-1,"Priority Of Process: %d ",myMemory[PCBcounter]);

                PCBcounter += 35;

                int CodeB=StringToIntConverter2(loading2Bytes(PCBcounter));
                PCBcounter +=2;
                int CodeL=StringToIntConverter2(loading2Bytes(PCBcounter));
                PCBcounter +=2;
                PCBcounter +=2;

                int StackB=StringToIntConverter2(loading2Bytes(PCBcounter));
                PCBcounter +=2;
                int StackL=StringToIntConverter2(loading2Bytes(PCBcounter));
                PCBcounter +=2;
                int StackC=StringToIntConverter2(loading2Bytes(PCBcounter));
                PCBcounter +=2;
                PCBcounter +=2;
                int dataL=StringToIntConverter2(loading2Bytes(PCBcounter));


                cout<<dataL<<endl;
                cout<<CodeL<<endl;

                if(StackC!=0){
                textprintf_ex(fakeDis,font,0,80,makecol(0,0,0),-1,"# of Stack Elements : %d ",StackB-StackC);
                //myNewFile<<"# of Stack Elements : "<<StackB-StackC<<endl;
                }else{
                textprintf_ex(fakeDis,font,0,80,makecol(0,0,0),-1,"# of Stack Elements : 0 ");
                //myNewFile<<"# of Stack Elements : 0"<<endl;

                }
                /*myNewFile<<"# of code frames : "<<((CodeL/pageSize)+1)<<endl;
                myNewFile<<"# of data frames : "<<((dataL/pageSize)+1)<<endl;
                myNewFile<<"Size Of Process : "<<((dataL+CodeL)+64)<<endl;*/

                textprintf_ex(fakeDis,font,0,100,makecol(0,0,0),-1,"# of code frames : %d ",(CodeL/pageSize)+1);
                textprintf_ex(fakeDis,font,0,120,makecol(0,0,0),-1,"# of data frames : %d ",(dataL/pageSize)+1);
                textprintf_ex(fakeDis,font,0,140,makecol(0,0,0),-1,"Size Of Process : %d ",(dataL+CodeL)+64);

                blit(fakeDis,image,0,0,200,50,600,500);
                blit(image,screen,0,0,0,0,800,600);

                readkey();

            }
            return find;
    }
    bool Block(short int proID)
    {
            BITMAP * error=load_bitmap("Images/Error.bmp",NULL);
       // int j=0;
/*        for(;j<8;j++)
        {

            if(myMemory[j*pageSize]==proID)
            break;
        }*/


        bool find=false;
        int valE=0;
        BITMAP * fakeDis=create_bitmap(600,500);
        BITMAP * image=load_bitmap("Images/MainScreenToWork.bmp",NULL);
        clear_to_color(fakeDis, makecol(170,231,216));

        for(int j=0;j<8;j++)
            {
                if(myMemory[valE]!=proID){
                valE = ((j+1)*pageSize);
                }
                else{
                if(freePCB[(valE+1)/pageSize]==1)
                {
                    find=true;
                    break;
                }
                }
            }
        if(find){

                valE += 99;
                myMemory[valE]=1;
                textout_ex(fakeDis, font,"Process has been blocked.", 0, 0, makecol(0,0,0),-1);

                readkey();


        }
        blit(fakeDis,image,0,0,200,50,600,500);
                blit(image,screen,0,0,0,0,800,600);

        return find;



    }

    bool unblock(short int proID)
    {
            BITMAP * error=load_bitmap("Images/Error.bmp",NULL);
       // int j=0;
/*        for(;j<8;j++)
        {

            if(myMemory[j*pageSize]==proID)
            break;
        }*/


        bool find=false;
        int valE=0;
        BITMAP * fakeDis=create_bitmap(600,500);
        BITMAP * image=load_bitmap("Images/MainScreenToWork.bmp",NULL);
        clear_to_color(fakeDis, makecol(170,231,216));

        for(int j=0;j<8;j++)
            {
                if(myMemory[valE]!=proID){
                valE = ((j+1)*pageSize);
                }
                else{
                if(freePCB[(valE+1)/pageSize]==1 && myMemory[valE+99]==1)
                {
                    find=true;
                    break;
                }
                }
            }
        if(find){

                valE += 99;
                myMemory[valE]=0;
                textout_ex(fakeDis, font,"Process has been unblocked.", 0, 0, makecol(0,0,0),-1);
                readkey();



        }
        blit(fakeDis,image,0,0,200,50,600,500);
                blit(image,screen,0,0,0,0,800,600);

        return find;



    }


   /* bool clone(int proID)
    {
        int myInt=0;
        int i=0
        for(;i<8;i++)
        {
            if(freePCB[i]==0)
            break;
        }
        int j=0;
        for(;j<8;j++)
        {

            if(myMemory[j*pageSize]==proID)
            break;
        }
        int myInt2=j*pageSize;
        myInt=i*pageSize;
        for(int k=0;k<128;k++)
        {
            myMemory[myInt++]=myMemory[myInt2++];
        }
    }*/

    bool clone(int proID)
    {
        BITMAP * error=load_bitmap("Images/Error.bmp",NULL);
       // int j=0;
/*        for(;j<8;j++)
        {

            if(myMemory[j*pageSize]==proID)
            break;
        }*/


        bool find=false;
        int valE=0;
        BITMAP * fakeDis=create_bitmap(600,500);
        BITMAP * image=load_bitmap("Images/MainScreenToWork.bmp",NULL);
        clear_to_color(fakeDis, makecol(170,231,216));

        for(int j=0;j<8;j++)
            {
                if(myMemory[valE]!=proID){
                valE = ((j+1)*pageSize);
                }
                else{
                if(freePCB[(valE+1)/pageSize]==1 && myMemory[valE+99]==0)
                {
                    find=true;
                    break;
                }
                }
            }



        if(find){
            int myInt2=(valE)+70;
            int nameSize=(int)myMemory[myInt2];
            char * nameOfFile =new char[nameSize];
            for(int i=0;i<nameSize;i++)
            {
                nameOfFile[i]=myMemory[(++myInt2)];
            }
            nameOfFile[nameSize]='\0';
            myFile.open(nameOfFile,ios::binary | ios::in);


            int m=0;
            for(;m<8;m++)
            {
                if(freePCB[m]==0)
                break;
            }
            PCBcounter=m*pageSize;
            freePCB[m]=1;



            if(myFile.good())                                     //Reading through the file
           {
              int changer=PCBcounter;
                priority=myFile.get();
                cout<<"Prior:"<<priority<<endl;
                PID=myFile.get();
                bool myPID=false;
                while(!myPID){
                PID++;
                //if(PID==16){PID=14;}
                for(int q=0;q<8;q++)
                {
                     if(processIDs[q]==PID)break;
                     if(q==7 && processIDs[q]!=PID)myPID=true;
                                               //Memory[0]=PID;
                }
                }
                myMemory[PCBcounter++]=PID;
                processIDs[m]=PID;
                if(priority==31 )
                myMemory[PCBcounter++]=--priority;
                else if(priority==15 )
                myMemory[PCBcounter++]=--priority;
                else
                myMemory[PCBcounter++]=++priority;

                int myCostInt;
                int j=0;
                for(int k=0;k<2;k++)
                {

                    switch (myFile.get())
                        {
                    case 1:
                        splRegs.dataLimit=calcDataSize();             //Fetch the Data Size and convert it to integer

                        noOfDataFrames=(splRegs.dataLimit/128)+1;     //Finding the Frames required for Code
                        fillDFrameTable(noOfDataFrames,m,userCounter);//Filling the Code Frames;Parameters passed are Number of Data Frames, number of Process and User counter;
                        j=0;
                        while(j<(splRegs.dataLimit))
                        {
                            myMemory[userCounter++]=myFile.get();     //While j is less then Size of Data fetch and insert to Memory and increment user counter
                            j++;
                        }

                        userCounter = (((userCounter+pageSize)/pageSize)*pageSize);//Move the user Counter to the next frame of memory
                        break;
                    case 2:
                        splRegs.codeLimit=calcDataSize();
                        noOfCodeFrames=(splRegs.codeLimit/128)+1;         //Finding the Frames required for Code segment
                        fillCFrameTable(noOfCodeFrames,m,userCounter);    //Filling the Code Frames;Parameters passed are Number of Data Frames, number of Process and User counter;
                        j=0;
                        while(j<(splRegs.codeLimit))
                        {
                        myMemory[userCounter++]=myFile.get();
                        j++;
                        }
                        break;
                    default:
                        textout_ex(buffer,font, "No Data Size Specified", 400,30, makecol(0,0,0),-1);
                        break;

                        }
                }

                    if(m%2==0)
                    splRegs.stackBase=(((22+m)*pageSize)-1);          //Maintaining Stack Base
                    else
                    splRegs.stackBase=(((22+(m-1))*pageSize)-1)-64;
                    splRegs.stackLimit=(pageSize/2);                  //Maintaining Stack Size whic is 64
                    splRegs.stackCounter=0;

                    myStr=int_to_hex((splRegs.dataLimit)+(splRegs.codeLimit));
                    fitValInMem(myStr);                               //Fit Data sizes into Memory calculated above
                    loadGeneralRegInMemory();                         //Loading General Registers
                    loadSpecialRegInMemory();
                    //For execution time and waiting time
                    PCBcounter+=4;
                    //freePCB[(PCBcounter/pageSize)]=1;
                    myMemory[PCBcounter++]=nameSize;
                    for(int k=0;k<nameSize;k++)
                    {
                        myMemory[PCBcounter++]=nameOfFile[k];
                    }
                    userCounter = (((userCounter+pageSize)/pageSize)*pageSize);
                    if(priority>=0 && priority<=15)
                    {
                        Pinsert(myMemory[(m*128)+1]);                  //Sending Priority of Required Process
                    }
                    else if(priority >=16 && priority <= 31)
                    {
                    enqueue(myMemory[m*128]);                        //Sending to Round Robin
                    }
                    PCBcounter=(m*pageSize)+4;
                    valE += 4;

                    for(int i=4;i<68;i++)
                    {
                        myMemory[PCBcounter++]=myMemory[valE++];

                    }
                    PCBcounter = (((PCBcounter+(pageSize))/pageSize)*pageSize);

                }
                else                                                  //File could not found
                {

                 /*   clear_bitmap(buffer);


                    textout_ex(buffer, font,"Error in file: ", 400, 50, makecol(0,0,0),-1);

                    blit(buffer,screen,0,0,0,0,800,600);

                    readkey();*/

                clear_bitmap(buffer);
                blit(error, buffer, 0,0,0,0,800,600);
                textout_ex(buffer, font,"Couldn't find the program file specified.", 400, 30, makecol(0,0,0),-1);
                textout_ex(buffer, font,"Error in file: ", 400, 50, makecol(0,0,0),-1);
                textout_ex(buffer, font,nameOfFile, 520, 50, makecol(0,0,0),-1);
                blit(buffer,screen,0,0,0,0,800,600);
                readkey();
                string * myStrQ=StartMenu(&noOfProcess);

                return setMemory(myStrQ,noOfProcess);

               /* cout<<"Couldn't find the program file specified."<<endl;
                cout<<"Error in file:"<<nameOfProcess[i]<<endl;*/

                }
                myFile.close();



        }
        bubbleSort(myMemory,Pelements);
        return find;


    }









    bool loadProc(string nameOfProcess)
    {
        BITMAP * error=load_bitmap("Images/Error.bmp",NULL);

        bool find=false;
        int valE=0;
        BITMAP * fakeDis=create_bitmap(600,500);
        BITMAP * image=load_bitmap("Images/MainScreenToWork.bmp",NULL);
        clear_to_color(fakeDis, makecol(170,231,216));

        int m=0;
        for(;m<8;m++)
        {
                if(freePCB[m]==0)
                break;
        }

        //ifstream myFile;
        myFile.open(nameOfProcess.c_str(),ios::binary | ios::in);


        PCBcounter=m*pageSize;
        cout<<"PCB"<<PCBcounter<<endl;




            if(myFile.good())                                     //Reading through the file
           {
              int changer=PCBcounter;
                priority=myFile.get();
                PID=myFile.get();
                myMemory[PCBcounter++]=PID;
                processIDs[m]=PID;
                myMemory[PCBcounter++]=priority;                  //Memory[1]=Priority
                int myCostInt;
                int j=0;
                for(int k=0;k<2;k++)
                {

                    switch (myFile.get())
                        {
                    case 1:
                        splRegs.dataLimit=calcDataSize();             //Fetch the Data Size and convert it to integer
                        noOfDataFrames=(splRegs.dataLimit/128)+1;     //Finding the Frames required for Code
                        fillDFrameTable(noOfDataFrames,m,userCounter);//Filling the Code Frames;Parameters passed are Number of Data Frames, number of Process and User counter;
                        j=0;
                        while(j<(splRegs.dataLimit))
                        {
                            myMemory[userCounter++]=myFile.get();     //While j is less then Size of Data fetch and insert to Memory and increment user counter
                            j++;
                        }

                        userCounter = (((userCounter+pageSize)/pageSize)*pageSize);//Move the user Counter to the next frame of memory
                        break;
                    case 2:
                        splRegs.codeLimit=calcDataSize();
                        noOfCodeFrames=(splRegs.codeLimit/128)+1;         //Finding the Frames required for Code segment
                        fillCFrameTable(noOfCodeFrames,m,userCounter);    //Filling the Code Frames;Parameters passed are Number of Data Frames, number of Process and User counter;
                        j=0;
                        while(j<(splRegs.codeLimit))
                        {
                        myMemory[userCounter++]=myFile.get();
                        j++;
                        }
                        break;
                    default:
                        textout_ex(buffer,font, "No Data Size Specified", 400,30, makecol(0,0,0),-1);
                        break;

                        }
                }

                    if(m%2==0)
                    splRegs.stackBase=(((22+m)*pageSize)-1);          //Maintaining Stack Base
                    else
                    splRegs.stackBase=(((22+(m-1))*pageSize)-1)-64;
                    splRegs.stackLimit=(pageSize/2);                  //Maintaining Stack Size whic is 64
                    splRegs.stackCounter=0;

                    myStr=int_to_hex((splRegs.dataLimit)+(splRegs.codeLimit));
                    fitValInMem(myStr);                               //Fit Data sizes into Memory calculated above
                    loadGeneralRegInMemory();                         //Loading General Registers
                    loadSpecialRegInMemory();
                    //For execution time and waiting time
                    PCBcounter+=4;
                    freePCB[(PCBcounter/pageSize)]=1;
                    myMemory[PCBcounter++]=nameOfProcess.length();
                    for(int k=0;k<nameOfProcess.length();k++)
                    {
                        myMemory[PCBcounter++]=nameOfProcess[k];
                    }
                    userCounter = (((userCounter+pageSize)/pageSize)*pageSize);
                    PCBcounter = (((PCBcounter+(pageSize))/pageSize)*pageSize);
                    if(priority>=0 && priority<=15)
                    {
                        Pinsert(myMemory[(m*128)+1]);                  //Sending Priority of Required Process
                    }
                    else
                    {
                    enqueue(myMemory[m*128]);                        //Sending to Round Robin
                    }


                }
                else                                                  //File could not found
                {

                 /*   clear_bitmap(buffer);


                    textout_ex(buffer, font,"Error in file: ", 400, 50, makecol(0,0,0),-1);

                    blit(buffer,screen,0,0,0,0,800,600);

                    readkey();*/

                clear_bitmap(buffer);
                blit(error, buffer, 0,0,0,0,800,600);
                textout_ex(buffer, font,"Couldn't find the program file specified.", 400, 30, makecol(0,0,0),-1);
                textout_ex(buffer, font,"Error in file: ", 400, 50, makecol(0,0,0),-1);
                textout_ex(buffer, font,nameOfProcess.c_str(), 520, 50, makecol(0,0,0),-1);
                blit(buffer,screen,0,0,0,0,800,600);
                readkey();
                string * myStrQ=StartMenu(&noOfProcess);

                return setMemory(myStrQ,noOfProcess);

               /* cout<<"Couldn't find the program file specified."<<endl;
                cout<<"Error in file:"<<nameOfProcess[i]<<endl;*/

                }
                myFile.close();




        bubbleSort(myMemory,Pelements);
        return find;




    }






















    bool kill(int proID)
    {
        PCBcounter=0;
        bool find=false;
                                    // Representing Priority of Process in a PCB and 0 represent ID
            for(int j=0;j<8;j++)
            {
                if(myMemory[PCBcounter]!=proID){
                PCBcounter = ((j+1)*pageSize);
                }
                else{
                if(freePCB[(PCBcounter+1)/pageSize]==1 && myMemory[PCBcounter+99]==0)
                {
                    find=true;
                    break;
                }
                }
            }

        if(find==true){
        BITMAP * fakeDis=create_bitmap(600,500);
        clear_to_color(fakeDis, makecol(170,231,216));
        deallocation((PCBcounter/pageSize));
        for(int i=0,myV=1024+((PCBcounter/pageSize)*64);i<64;i++)
        {
            myMemory[myV++]=0;
        }

       /* bool okItsHere=false;
        int myCounter=1;
        while(okItsHere==false)
        {
            priority=Premove();
            myCounter=1;
            for(int j=0;j<8;j++)
            {
                if(myMemory[PCBcounter]!=priority)
                PCBcounter = ((j+1)*pageSize)+1;
                else
                break;
            }
            if(myMemory[myCounter-1]==myMemory[PCBcounter])
            {

            okItsHere=true;

            }
            else{
            Pinsert(myMemory[myCounter]);
            }
        }/*
        if(okItsHere==false)
        {
            while(okItsHere==false)
            {
            PID=dequeue();
            myCounter=0;
            for(int j=0;j<8;j++)
            {
                if(myMemory[myCounter]!=PID)
                myCounter = ((j+1)*pageSize);
                else
                break;

            }
            if(myMemory[myCounter]==myMemory[PCBcounter])
            {

            okItsHere=true;

            }
            else{
            enqueue(myMemory[myCounter]);
            }
            }
        }*/

        textout_ex(fakeDis,font,"The Process Of Your Given ID has been killed.",0,0,makecol(0,0,0),-1);
        blit(fakeDis,screen,0,0,200,50,800,600);
        myMemory[PCBcounter+1]=0;


        }
        return find;

    }
    void myCall()
    {
        pageSize=128;                                                // Page Size 128KB
        PQhead=2048;
        PQtail=2048;
        Pfull=false;
        Pelements=0;
        PCBcounter=0;                                               //PCB counter starting from index 0 of memoryCounter starts at 3200
        userCounter=3200;                                           //User Counter starts at 3200= 19 frames of Kernel Memory * 128 =3200
        frameTablePointer=2176;                                     //Free Frame Table starts at 2176
        maxSize=8;                                                  //Max Size is 8 process
        Relements=0;
        rear=-1;
      //  ExtraFunctions eF;
        front=-1;
        checkStack=false;
        execution_time=0;
        waiting_time=0;
        out.open("Output.txt",ios::app);
        buffer=create_bitmap(800,600);


        for(int i=0;i<65536;i++)
        {
            myMemory[i]='\0';
        }
        for(int i=2176;i<2688;i++)                                  //Initializing 512 Frames of Memory
        {
            myMemory[i]=0;
        }

    }

    ~memoryClass()
    {
        out.close();
    }
/*******************************************Round Robin is Empty****************************************/
    bool RisEmpty()
    {
        return (Relements==0);
    }
/********************************************Round Robin is Full**************************************/
    bool RisFull()
    {
        return (Relements==maxSize);
    }



/*****************************************Round Robin Enqueue**************************************/
    void enqueue(int num)
    {
        if(!RisFull())
        {
            myMemory[((front+1)%maxSize)+2150]=num;                   //Round Robin Start from Memory Index 1312
            front=(front+1)%maxSize;
            Relements++;

        }
        else{
            cout<<"Robin Queue is full.";
            out<<"Robin Queue is full.";

        }
    }
/*****************************************Round Robin Dequeue**************************************/

    int dequeue()
    {
        int value;
        if(!RisEmpty())
        {
            value=myMemory[((rear+1)%maxSize)+2150];
            rear=(rear+1)%maxSize;
            Relements--;
            return value;
        }
        else{
            cout<<"Queue is Empty";
            out<<"Queue is Empty";

        }
    }

/*************************************Priority is Empty Check****************************************/
    bool PisEmpty(){
        return ((PQhead  == PQtail));
    }
/*************************************Insert in Priority********************************************/
    void Pinsert(int i){

        if(Pelements<8)                                               //Size of Priority Queue = 8
            {

            myMemory[PQtail] = i;
            Pelements++;
            PQtail ++;

            }
        if(Pelements==8)
        {
            cout<<"The Queue is Full Can't Insert Anymore.."<<endl;
            out<<"The Queue is Full Can't Insert Anymore.."<<endl;
        }
    }
/*************************************Priority is Remove****************************************/
    int Premove(){
        if(!PisEmpty())
        {
            int temp=myMemory[PQhead];                              //Reading from head and move the integer by one
            PQhead++;
            return temp;
        }
        else{
            cout<<"The Queue is empty.";
            exit(1);
        }


    }


    void DisplayRegs()
    {


    }


        void PrintPCB2(int i)
    {
        int lengthOfName=myMemory[(70)+(pageSize*i)];
        int valueOfPointer=(71+(pageSize*i));
        cout<<"Printing PCB : "<<endl;
        cout<<"Name Of Process: \t";
        out<<"Printing PCB : "<<endl;
        out<<"Name Of Process: \t";

        for(int k=(valueOfPointer);k<(lengthOfName+valueOfPointer);k++)
        {
            cout<<myMemory[k];
            out<<myMemory[k];

        }
        cout<<endl;
        out<<endl;
        valueOfPointer=(pageSize*i);
        cout<<"Process ID: \t"<<(int)myMemory[valueOfPointer++]<<endl;
        out<<"Process ID: \t"<<(int)myMemory[valueOfPointer]<<endl;
        cout<<"Priortiy Of Process: \t"<<(int)myMemory[valueOfPointer++]<<endl;
        out<<"Priortiy Of Process: \t"<<(int)myMemory[valueOfPointer]<<endl;
        cout<<"Size Of Process: \t"<<loading2Bytes(valueOfPointer)<<endl;
        out<<"Size Of Process: \t"<<loading2Bytes(valueOfPointer)<<endl;
        valueOfPointer += 2;
        cout<<"General Purpose Registers :"<<endl;
        out<<"General Purpose Registers :"<<endl;
        for(int k=valueOfPointer,l=0;k<valueOfPointer+32;k+=2,l++)
        {
            cout<<"Register"<<l<<": \t"<<loading2Bytes(k)<<endl;
            out<<"Register"<<l<<": \t"<<loading2Bytes(k)<<endl;
        }
        valueOfPointer += 32;
        cout<<"Special Purpose Registers: "<<endl;
        out<<"Special Purpose Registers: "<<endl;
        cout<<"CodeBase: \t"<<loading2Bytes(valueOfPointer)<<endl;
        out<<"CodeBase: \t"<<loading2Bytes(valueOfPointer)<<endl;
        valueOfPointer += 2;
        cout<<"CodeLimit: \t"<<loading2Bytes(valueOfPointer)<<endl;
        out<<"CodeLimit: \t"<<loading2Bytes(valueOfPointer)<<endl;
        valueOfPointer += 2;
        cout<<"CodeCounter: \t"<<loading2Bytes(valueOfPointer)<<endl;
        out<<"CodeCounter: \t"<<loading2Bytes(valueOfPointer)<<endl;
        valueOfPointer += 2;
        cout<<"StackBase: \t"<<loading2Bytes(valueOfPointer)<<endl;
        out<<"StackBase: \t"<<loading2Bytes(valueOfPointer)<<endl;
        valueOfPointer += 2;
        cout<<"StackLimit: \t"<<loading2Bytes(valueOfPointer)<<endl;
        out<<"StackLimit: \t"<<loading2Bytes(valueOfPointer)<<endl;
        valueOfPointer += 2;
        cout<<"StackCounter: \t"<<loading2Bytes(valueOfPointer)<<endl;
        out<<"StackCounter: \t"<<loading2Bytes(valueOfPointer)<<endl;
        valueOfPointer += 2;
        cout<<"DataBase: \t"<<loading2Bytes(valueOfPointer)<<endl;
        out<<"DataBase: \t"<<loading2Bytes(valueOfPointer)<<endl;
        valueOfPointer += 2;
        cout<<"DataLimit: \t"<<loading2Bytes(valueOfPointer)<<endl;
        out<<"DataLimit: \t"<<loading2Bytes(valueOfPointer)<<endl;
        valueOfPointer += 2;
        cout<<"Flag: \t"<<loading2Bytes(valueOfPointer)<<endl;
        out<<"Flag: \t"<<loading2Bytes(valueOfPointer)<<endl;
        valueOfPointer += 2;
}
/********************************************************************************************************/
/*************************Printing Process Control Block***********************************************************/

    void PrintPCB(int i)
    {
        int lengthOfName=myMemory[(70)+(pageSize*i)];
        int valueOfPointer=(71+(pageSize*i));
        cout<<"Printing PCB : "<<endl;
        cout<<"Name Of Process: \t";
        out<<"Printing PCB : "<<endl;
        out<<"Name Of Process: \t";

        for(int k=(valueOfPointer);k<(lengthOfName+valueOfPointer);k++)
        {
            cout<<myMemory[k];
            out<<myMemory[k];

        }
        cout<<endl;
        out<<endl;
        valueOfPointer=(pageSize*i);
        cout<<"Process ID: \t"<<(int)myMemory[valueOfPointer++]<<endl;
        out<<"Process ID: \t"<<(int)myMemory[valueOfPointer]<<endl;
        cout<<"Priortiy Of Process: \t"<<(int)myMemory[valueOfPointer++]<<endl;
        out<<"Priortiy Of Process: \t"<<(int)myMemory[valueOfPointer]<<endl;
        cout<<"Size Of Process: \t"<<loading2Bytes(valueOfPointer)<<endl;
        out<<"Size Of Process: \t"<<loading2Bytes(valueOfPointer)<<endl;
        valueOfPointer += 2;
        cout<<"General Purpose Registers :"<<endl;
        out<<"General Purpose Registers :"<<endl;
        for(int k=valueOfPointer,l=0;k<valueOfPointer+32;k+=2,l++)
        {
            cout<<"Register"<<l<<": \t"<<loading2Bytes(k)<<endl;
            out<<"Register"<<l<<": \t"<<loading2Bytes(k)<<endl;
        }
        valueOfPointer += 32;
        cout<<"Special Purpose Registers: "<<endl;
        out<<"Special Purpose Registers: "<<endl;
        cout<<"CodeBase: \t"<<loading2Bytes(valueOfPointer)<<endl;
        out<<"CodeBase: \t"<<loading2Bytes(valueOfPointer)<<endl;
        valueOfPointer += 2;
        cout<<"CodeLimit: \t"<<loading2Bytes(valueOfPointer)<<endl;
        out<<"CodeLimit: \t"<<loading2Bytes(valueOfPointer)<<endl;
        valueOfPointer += 2;
        cout<<"CodeCounter: \t"<<loading2Bytes(valueOfPointer)<<endl;
        out<<"CodeCounter: \t"<<loading2Bytes(valueOfPointer)<<endl;
        valueOfPointer += 2;
        cout<<"StackBase: \t"<<loading2Bytes(valueOfPointer)<<endl;
        out<<"StackBase: \t"<<loading2Bytes(valueOfPointer)<<endl;
        valueOfPointer += 2;
        cout<<"StackLimit: \t"<<loading2Bytes(valueOfPointer)<<endl;
        out<<"StackLimit: \t"<<loading2Bytes(valueOfPointer)<<endl;
        valueOfPointer += 2;
        cout<<"StackCounter: \t"<<loading2Bytes(valueOfPointer)<<endl;
        out<<"StackCounter: \t"<<loading2Bytes(valueOfPointer)<<endl;
        valueOfPointer += 2;
        cout<<"DataBase: \t"<<loading2Bytes(valueOfPointer)<<endl;
        out<<"DataBase: \t"<<loading2Bytes(valueOfPointer)<<endl;
        valueOfPointer += 2;
        cout<<"DataLimit: \t"<<loading2Bytes(valueOfPointer)<<endl;
        out<<"DataLimit: \t"<<loading2Bytes(valueOfPointer)<<endl;
        valueOfPointer += 2;
        cout<<"Flag: \t"<<loading2Bytes(valueOfPointer)<<endl;
        out<<"Flag: \t"<<loading2Bytes(valueOfPointer)<<endl;
        valueOfPointer += 2;
}
/********************************************************************************************************/
/*************************************Funtion to Print All Registers****************************/
    void printAllRegs()
    {
        regs.printRegs();
        splRegs.printFlag();
    }

    void printAllRegsAllegro()
    {
        BITMAP * fakeDisplay=create_bitmap(600,500);
        BITMAP * fakeDisplay2=create_bitmap(600,500);
        BITMAP * fakeDisplay3=create_bitmap(600,500);


        regs.printRegsAllegro(fakeDisplay);
        splRegs.printFlagAllegro(fakeDisplay2);
        splRegs.PrintAllRegsAllegro(fakeDisplay3);

    }

    int debugOnce(int proID)
    {
        PCBcounter=0;
            bool found=false;                                          // Representing Priority of Process in a PCB and 0 represent ID
            for(int j=0;j<8;j++)
            {
                if(myMemory[PCBcounter]!=proID){
                PCBcounter = ((j+1)*pageSize);
                }
                else{
                if(freePCB[(PCBcounter+1)/pageSize]==1 && myMemory[PCBcounter+99]==0)
                {
                    found=true;
                    break;
                }
                }
            }
        BITMAP * fakeDis=create_bitmap(600,500);
        clear_to_color(fakeDis, makecol(255,0,255));
        if(found==true){
            textprintf_ex(fakeDis,font,0,0,makecol(0,0,0),-1,"Starting Process Of ID : %d",proID);
            //cout<<"Starting Process of ID: \t"<<proID<<endl;
            //out<<"Starting Process of ID: \t"<<proID<<endl;
            loadIt(PCBcounter);
/*******************************Linear Adress Translation***************************/
            int tempValue=PCBcounter/128;
            int frameNum=(1088+(tempValue*pageSize));
            if(splRegs.codeCounter==0)
            splRegs.codeCounter=myMemory[frameNum]*pageSize;
            while(splRegs.codeCounter<splRegs.codeLimit+splRegs.codeBase){
            int myInt=myMemory[splRegs.codeCounter];
/*************************************************************************************/
            execution_time=execution_time+2;                          //Calculating Execution Time
            waiting_time=waiting_time+2;                              //Calculating Waiting Time
            splRegs.codeCounter++;
            int exception_check=intruction(myInt);                        //Executing instruction specified by the opCODE
/*-----------------------------------Exceptional Checking----------------------------*/

            if(execptionHandling2(exception_check,PCBcounter)!=0)break;
            //blit(fakeDis,screen,0,0,200,50,600,500);

            regs.printRegsAllegro2(fakeDis);
            splRegs.PrintAllRegsAllegro2(fakeDis);
            if((readkey() >> 8 ) == KEY_E){
                PCBcounter += 4;
                loadGeneralRegInMemory();
                loadSpecialRegInMemory();
                return found;
                };
            clear_to_color(fakeDis, makecol(170,231,216));
            }

/*-----------------------------------------------------------------------------------------*/
            //HERE IS IT IS POSSIBLE THAT I WILL CHECK THE CONDITION IF THE MYINT IS EQUALS TO -1 I WILL PRINT THE ERROR OR MAKE THE MEMORY NULL


            deallocation(tempValue);                                //De-Allocation of Memory


            /*-------------------------Printing Waiting and Execution Time-------------------*/
            myStr=int_to_hex(execution_time);
            efficientStore(myStr,(PCBcounter+65));
            myStr=int_to_hex(waiting_time-execution_time);
            efficientStore(myStr,(PCBcounter+67));
            textprintf_ex(fakeDis,font,0,450,makecol(0,0,0),-1,"Execution Time %d",execution_time);
            textprintf_ex(fakeDis,font,0,475,makecol(0,0,0),-1,"Waiting Time %d",waiting_time-execution_time);

            blit(fakeDis,screen,0,0,200,50,600,500);
           // cout<<"This is Waiting Time "<<waiting_time-execution_time<<endl;

            //out<<"This is Execution Time "<<execution_time<<endl;
            //out<<"This is Waiting Time "<<waiting_time-execution_time<<endl;
                                                   //Setting counter to Zero for next counting
            /**********************************************************************************/
        }

        /*******************************Executing Round Robin Queue*************************************/

        return found;

    }





    bool printPCB(int proID,BITMAP * fakeDis)
    {
        int valueOfPointer=0;

        bool found=false;                                          // Representing Priority of Process in a PCB and 0 represent ID
        for(int j=0;j<8;j++)
        {
                if(myMemory[valueOfPointer]!=proID){
                valueOfPointer = ((j+1)*pageSize);
                }
                else{
                if(freePCB[(valueOfPointer+1)/pageSize]==1 && myMemory[valueOfPointer+99]==0)
                {
                    found=true;
                    break;
                }
                }
        }

        if(found)
        {
        //int lengthOfName=myMemory[(70)+PCBcounter];
        //int valueOfPointer=(71+PCBcounter);
        textout_ex(fakeDis,font,"Printing PCB : ",0,0,makecol(0,0,0),-1);
        textout_ex(fakeDis,font,"ID Of Process : ",0,25,makecol(0,0,0),-1);
        textprintf_ex(fakeDis,font,200,25,makecol(0,0,0),-1,"%d",myMemory[valueOfPointer++]);
        textout_ex(fakeDis,font,"Priortiy Of Process : ",0,50,makecol(0,0,0),-1);
        textprintf_ex(fakeDis,font,200,50,makecol(0,0,0),-1,"%d",myMemory[valueOfPointer++]);
        textout_ex(fakeDis,font,"Size Of Process : ",0,75,makecol(0,0,0),-1);
        int sizeOfProcess=StringToIntConverter2(loading2Bytes(valueOfPointer));
        textprintf_ex(fakeDis,font,200,75,makecol(0,0,0),-1,"%d",sizeOfProcess+64);
        valueOfPointer += 2;
        int height=25;
        textout_ex(fakeDis,font,"General Purpose Registers",0,100,makecol(255,255,255),-1);
        for(int k=valueOfPointer,i=0;k<valueOfPointer+32;i++,k+=2){
        textout_ex(fakeDis,font,loading2Bytes(k).c_str(),0,(i*height)+125,makecol(0,0,0),-1);
        k += 2;
        textout_ex(fakeDis,font,loading2Bytes(k).c_str(),200,(i*height)+125,makecol(0,0,0),-1);

        }
        valueOfPointer += 32;
        textout_ex(fakeDis,font,"Special Purpose Registers",0,350,makecol(255,255,255),-1);

        textout_ex(fakeDis,font,"CodeBase : ",0,375,makecol(0,0,0),-1);
        textout_ex(fakeDis,font,loading2Bytes(valueOfPointer).c_str(),200,375,makecol(0,0,0),-1);valueOfPointer += 2;

        textout_ex(fakeDis,font,"CodeLimit : ",0,400,makecol(0,0,0),-1);
        textout_ex(fakeDis,font,loading2Bytes(valueOfPointer).c_str(),200,400,makecol(0,0,0),-1);valueOfPointer += 2;

        textout_ex(fakeDis,font,"CodeCounter : ",0,425,makecol(0,0,0),-1);
        textout_ex(fakeDis,font,loading2Bytes(valueOfPointer).c_str(),200,425,makecol(0,0,0),-1);valueOfPointer += 2;

        textout_ex(fakeDis,font,"StackBase : ",0,450,makecol(0,0,0),-1);
        textout_ex(fakeDis,font,loading2Bytes(valueOfPointer).c_str(),200,450,makecol(0,0,0),-1);valueOfPointer += 2;

        textout_ex(fakeDis,font,"StackLimit : ",0,475,makecol(0,0,0),-1);
        textout_ex(fakeDis,font,loading2Bytes(valueOfPointer).c_str(),200,475,makecol(0,0,0),-1);valueOfPointer += 2;

        textout_ex(fakeDis,font,"StackCounter : ",250,450,makecol(0,0,0),-1);
        textout_ex(fakeDis,font,loading2Bytes(valueOfPointer).c_str(),350,450,makecol(0,0,0),-1);valueOfPointer += 2;

        textout_ex(fakeDis,font,"DataBase : ",250,375,makecol(0,0,0),-1);
        textout_ex(fakeDis,font,loading2Bytes(valueOfPointer).c_str(),350,375,makecol(0,0,0),-1);valueOfPointer += 2;

        textout_ex(fakeDis,font,"DataLimit : ",250,400,makecol(0,0,0),-1);
        textout_ex(fakeDis,font,loading2Bytes(valueOfPointer).c_str(),350,400,makecol(0,0,0),-1);valueOfPointer += 2;

        textout_ex(fakeDis,font,"Flag : ",250,425,makecol(0,0,0),-1);
        textout_ex(fakeDis,font,loading2Bytes(valueOfPointer).c_str(),350,425,makecol(0,0,0),-1);valueOfPointer += 2;



        cout<<valueOfPointer<<endl;
        blit(fakeDis,screen,0,0,200,50,600,500);

        }
        return found;

    }


    bool memDump(int proID)
    {
        bool find=false;
        PCBcounter=0;
        BITMAP * fakeDis=create_bitmap(600,500);
        BITMAP * image=load_bitmap("Images/MainScreenToWork.bmp",NULL);
        clear_to_color(fakeDis, makecol(170,231,216));

        bool found=false;                                          // Representing Priority of Process in a PCB and 0 represent ID
        for(int j=0;j<8;j++)
        {
                if(myMemory[PCBcounter]!=proID){
                PCBcounter = ((j+1)*pageSize);
                }
                else{
                if(freePCB[(PCBcounter+1)/pageSize]==1  && myMemory[PCBcounter+99]==0)
                {
                    found=true;
                    break;
                }
                }
        }

        if(found)
        {

                textprintf_ex(fakeDis,font,0,20,makecol(0,0,0),-1,"Size Of PCB: 128BYTES ");
                textprintf_ex(fakeDis,font,0,40,makecol(0,0,0),-1,"ID Of Process: %d ",myMemory[PCBcounter++]);
                textprintf_ex(fakeDis,font,0,60,makecol(0,0,0),-1,"Priority Of Process: %d ",myMemory[PCBcounter]);
                textprintf_ex(fakeDis,font,0,70,makecol(255,0,0),-1,"Data: ");

                PCBcounter += 35;

                int CodeB=StringToIntConverter2(loading2Bytes(PCBcounter));
                PCBcounter +=2;
                int CodeL=StringToIntConverter2(loading2Bytes(PCBcounter));
                PCBcounter +=2;
                PCBcounter +=2;

                int StackB=StringToIntConverter2(loading2Bytes(PCBcounter));
                PCBcounter +=2;
                int StackL=StringToIntConverter2(loading2Bytes(PCBcounter));
                PCBcounter +=2;
                int StackC=StringToIntConverter2(loading2Bytes(PCBcounter));
                PCBcounter +=2;
                int dataB=StringToIntConverter2(loading2Bytes(PCBcounter));
                PCBcounter +=2;
                int dataL=StringToIntConverter2(loading2Bytes(PCBcounter));

                int ok=dataB;
                int height=8;
                int i=1;
                for(;ok<dataB+dataL;ok++,i++)
                {
                    textprintf_ex(fakeDis,font,0,(i*height)+80,makecol(0,0,0),-1,"Index:%d | Value:%d",ok,myMemory[ok]);
                }
                ok=CodeB;
                textprintf_ex(fakeDis,font,0,(i*height)+80,makecol(255,0,0),-1,"Code: ");
                i++;
                for(;ok<CodeB+CodeL;ok++,i++)
                {
                    textprintf_ex(fakeDis,font,0,(i*height)+80,makecol(0,0,0),-1,"Index:%d | Value:%d",ok,myMemory[ok]);
                }

                /*if(StackC!=0)
                textprintf_ex(fakeDis,font,0,80,makecol(0,0,0),-1,"# of Stack Elements : %d ",StackB-StackC);
                else
                textprintf_ex(fakeDis,font,0,80,makecol(0,0,0),-1,"# of Stack Elements : 0 ");

                textprintf_ex(fakeDis,font,0,100,makecol(0,0,0),-1,"# of code frames : %d ",(CodeL/pageSize)+1);
                textprintf_ex(fakeDis,font,0,120,makecol(0,0,0),-1,"# of data frames : %d ",(dataL/pageSize)+1);
                textprintf_ex(fakeDis,font,0,140,makecol(0,0,0),-1,"Size Of Process : %d ",(dataL+CodeL)+64);
*/
                blit(fakeDis,image,0,0,200,50,600,500);
                blit(image,screen,0,0,0,0,800,600);

                readkey();
        }
        return found;
    }











/*******************************Loading Two Bytes*************************************
Converting the Integer into Hex and then marshell them into String and send them
/*************************************************************************************/
    void bubbleSort(unsigned char *array,int length)                    //Bubble sort function
    {
    int i,j;
    for(i=2048;i<2048+length;i++)                                   //Queue start at memory indec 2048
    {
        for(j=2048;j<i;j++)
        {
            if(array[i]<array[j])
            {
                int temp=array[i];                                  //swap
                array[i]=array[j];
                array[j]=temp;
            }

        }

    }

    }


    template< typename T >
string int_to_hex( T i )
{
  string myStr;
  stringstream stream;
  stream
         << setfill ('0') << setw(4)
         << hex << i;
         myStr=stream.str();
         if(i>65535 ||i<0)
         {

            myStr=myStr.substr(myStr.length()-4);

         }
  return myStr;
}


long int cirR(short int temp)                                       //CirR Function
{
    bitset<8>   bits(temp);
    temp=temp>>1;                                                   //Circular Left Shift
    bits=temp;
    bits.set(7,bits[0]);                                              //Changing 7 position bit with 0th position bit
    return bits.to_ulong();                                         // Returning Result in Long int

}


long int cirL(short int temp)                                       //CirL function
{
    bitset<8>   bits(temp);                                         //Set 8 bits of Temp
    temp=temp<<1;                                                   //Shift right by one
    bits=temp;                                                      //Stored 8 bits of temp in bits
    bits.set(0,bits[7]);                                            //Set 0 position with 7th position
    return bits.to_ulong();                                         // Returning Result in long int

}


void printFrames()
{
    int pointer=2176;
    int height=22;
    int i=1;
    BITMAP * fakeDisplay=create_bitmap(600,500);
    clear_to_color(fakeDisplay, makecol(255,0,255));
    textout_ex(fakeDisplay,font,"Allocated Frame:",0,0,makecol(0,0,0),-1);

    while(myMemory[pointer+25]==1)
    {

        textout_ex(fakeDisplay,font,"Frame Number:",0,(height*i),makecol(0,0,0),-1);
        textprintf_ex(fakeDisplay, font, 110, (height*i), makecol(0,0,0),-1,"%d",(i+25) );
        i++;
        pointer++;
        if(i%20==0)
        {
            blit(fakeDisplay,screen,0,0,200,50,600,500);
            readkey();
            clear_bitmap(fakeDisplay);
        }


    }


    blit(fakeDisplay,screen,0,0,200,50,600,500);
    rest(500);
    clear_bitmap(fakeDisplay);

}



template< typename M >
string int_to_hex2( M i )
{
  string myStr;
  stringstream stream;
  stream
         << setfill ('0') << setw(2)
         << hex << i;
         myStr=stream.str();
         if(i>65535 ||i<0)
         {

            myStr=myStr.substr(myStr.length()-2);

         }
  return myStr;
}


unsigned char myConv(char one,char two)
{
    int sum;

    if(one>=48 && one<=57)
    one=(one-48);
    else if(one>=97 && one <=124)
    one=(one-87);
    sum=(int)one;


    if(two>=48 && two<=57)
    two=(two-48);
    else if(two>=97 && two<=124)
    two=(two-87);
    sum=sum+((int)two*16);
    unsigned char myChar=sum;
    return myChar;

}



short int StringToIntConverter2(string myChar)                      // Function to convert the Hex string to int
{

    int base=16;
    int count=0,num=0,temp=0;
    short int result=0;
    int stringLength=strlen(myChar.c_str());
    stringLength--;
    while(stringLength>=0)
    {

        num=myChar[stringLength];
        if(num<59 && num >47)
        num -=48;
        else if(num>96 && num<103)
        num -=87;
        temp=pow(base,count);
        result +=    (temp*  num);
        count++;

        stringLength--;

    }

return result;

}






short int StringToIntConverter3(string myChar)                      // Function to convert the Hex string to int
{

    int base=10;
    int count=0,num=0,temp=0;
    short int result=0;
    int stringLength=strlen(myChar.c_str());
    stringLength--;
    while(stringLength>=0)
    {

        num=myChar[stringLength];
        if(num<59 && num >47)
        num -=48;
        else if(num>96 && num<103)
        num -=87;
        temp=pow(base,count);
        result +=    (temp*  num);
        count++;

        stringLength--;

    }

return result;

}










    string loading2Bytes(int number)
    {
        int myInt;
        string myStr;
        string myStr2;

        myInt=(int)myMemory[number];
        number++;
        myStr=int_to_hex2(myInt);
        myInt=(int)myMemory[number];
        number++;
        myStr2=int_to_hex2(myInt);
        return myStr+myStr2;

    }
    void loadIt(int  number)
    {
        string myStr;
        number += 4;                                                  // Jump to General Registers from ID

        for(int i=0;i<16;i++)
        {
            myStr=loading2Bytes(number);
            regs.myReg[i]=StringToIntConverter2(myStr);
            number += 2;                                              // Because every Register is of Two bytes
        }

        myStr=loading2Bytes(number);
        splRegs.codeBase=StringToIntConverter2(myStr);number += 2;
        myStr=loading2Bytes(number);
        splRegs.codeLimit=StringToIntConverter2(myStr);number += 2;
        myStr=loading2Bytes(number);
        splRegs.codeCounter=StringToIntConverter2(myStr);number += 2;
        myStr=loading2Bytes(number);
        splRegs.stackBase=StringToIntConverter2(myStr);number += 2;
        myStr=loading2Bytes(number);
        splRegs.stackLimit=StringToIntConverter2(myStr);number += 2;
        myStr=loading2Bytes(number);
        splRegs.stackCounter=StringToIntConverter2(myStr);number += 2;
        myStr=loading2Bytes(number);
        splRegs.dataBase=StringToIntConverter2(myStr);number += 2;
        myStr=loading2Bytes(number);
        splRegs.dataLimit=StringToIntConverter2(myStr);number += 2;
        myStr=loading2Bytes(number);
        splRegs.flags=StringToIntConverter2(myStr);number += 2;

    }
/************Filling the Memory by taking string and converting it to Hex*************************************/

    void fitValInMem(string myStr)
    {
        myMemory[PCBcounter++]=myConv(myStr[1],myStr[0]);
        myMemory[PCBcounter++]=myConv(myStr[3],myStr[2]);
    }
    void efficientStore(string myStr,int myInt)
    {
        myMemory[myInt++]=myConv(myStr[1],myStr[0]);
        myMemory[myInt++]=myConv(myStr[3],myStr[2]);
    }
/**********************************De-Allocation of Memory***************************************/
void deallocation(int tempValue)
    {
        int toRemove=(1024+(tempValue*pageSize));
        while(myMemory[myMemory[toRemove]+2176]==1)                   //Removing Data Entry from Frame table = starts at 1024
        {
            myMemory[myMemory[toRemove++]+2176]=0;
        }
        int noOfDataFrames=(splRegs.dataLimit/128)+1;
        int newFTP=2176;
        int newPK=splRegs.dataBase/128;
        for(int i=0;i<noOfDataFrames;i++)
        {
            myMemory[newFTP+newPK+i]=0;
            cout<<(int)myMemory[newFTP+newPK+i]<<" "<<newFTP+newPK+i<<endl;
        }
        toRemove=(1088+(tempValue*pageSize));                               //Removinf Code Fram Entry From Frame table =starts at 1088
        while(myMemory[myMemory[toRemove]+2176]==1)
        {

            myMemory[myMemory[toRemove++]+2176]=0;
        }
        freePCB[tempValue]=0;
        int noOfCodeFrames=(splRegs.codeLimit/128)+1;         //Finding the Frames required for Code segment
        newFTP=2176;
        newPK=splRegs.codeBase/128;
        for(int i=0;i<noOfCodeFrames;i++)
        {
            myMemory[newFTP+newPK+i]=0;
            cout<<(int)myMemory[newFTP+newPK+i]<<" "<<newFTP+newPK+i<<endl;
        }
        for(int i=0;i<8;i++)
        {
            if(myMemory[tempValue*pageSize]==processIDs[i])
            {
                processIDs[i]=0;
                break;
            }
        }
        int myV=tempValue*pageSize;
        for(int i=0;i<128;i++)
        {
            myMemory[myV+i]=0;

        }
        myMemory[myV+1]='0';
    }




/*********************************Filling the Frame Table****************************************/

    void fillDFrameTable(int size, int j,int userCounter)
    {
        int DtablePointer=(pageSize*8)+(j*pageSize);                        //1024=(1KB) + (0 or pageSize or 64) = Number of Table Pointer
        int DpageSize=0;
        splRegs.dataBase=(userCounter);                               //User counter start act as a Base for Data and stored in Data Base
        for(int i=0;i<size;i++)                                       //Size = Number of frames  which is minimum 1
        {
            myMemory[DtablePointer++]=((userCounter+DpageSize)/128);  //Data Base + Page size / Maximum size of Frame = Data Frame Table Size for one frame
            if(myMemory[25+frameTablePointer]==0)
            myMemory[25+frameTablePointer++]=1;                          //Filling the Free Frame Table to 1 indicating Frame is loaded in this location
            DpageSize += 128;                                         //Increment the Page size by 128 for next fram allocation
        }


    }
    void emptyDFrameTable(int size, int j,int userCounter)
    {
        int DtablePointer=(pageSize*8)+(j*pageSize);                        //1024=(1KB) + (0 or pageSize or 64) = Number of Table Pointer
        int DpageSize=0;
        splRegs.dataBase=(userCounter);                               //User counter start act as a Base for Data and stored in Data Base
        for(int i=0;i<size;i++)                                       //Size = Number of frames  which is minimum 1
        {
            myMemory[DtablePointer++]=0;  //Data Base + Page size / Maximum size of Frame = Data Frame Table Size for one frame
            if(myMemory[25+frameTablePointer]==0)
            myMemory[25+frameTablePointer++]=0;                          //Filling the Free Frame Table to 1 indicating Frame is loaded in this location
            DpageSize += 128;                                         //Increment the Page size by 128 for next fram allocation
        }


    }
    void fillCFrameTable(int size, int j,int tempCodePointer)
    {
        int tablePointer=(1088+(j*pageSize));
        int DpageSize=0;
        splRegs.codeBase=(tempCodePointer);
        for(int i=0;i<size;i++)
        {
                myMemory[tablePointer++]=((tempCodePointer+DpageSize)/128);
                if(myMemory[25+frameTablePointer]==0)
                myMemory[25+frameTablePointer++]=1;
                DpageSize += 128;


        }


    }
/*******************************Calculate Data Size of Data Segment*************************/
    short int calcDataSize(){
                                             //Fetch the first char and assign it to integer
        string myStr;
        myStr=int_to_hex2(myFile.get());                                  //Convert it to string
        string myStr1;

        myStr1=int_to_hex2(myFile.get());
        myStr += myStr1;                                              //Concatenate the two String


        return StringToIntConverter2(myStr);                          //Send the merge string into Funtion which convert into Integer
    }
/****************************************Load Genral Registers***************************/
    void loadGeneralRegInMemory()
    {
        string myStr;
        for(int i=0;i<16;i++)
        {
            myStr=int_to_hex(regs.myReg[i]);
            fitValInMem(myStr);

        }
    }
/****************************************Load Sepcial Registers***************************/

    void loadSpecialRegInMemory()
    {
        string myStr;
        myStr=int_to_hex(splRegs.codeBase);
        fitValInMem(myStr);
        myStr=int_to_hex(splRegs.codeLimit);
        fitValInMem(myStr);
        myStr=int_to_hex(splRegs.codeCounter);
        fitValInMem(myStr);
        myStr=int_to_hex(splRegs.stackBase);
        fitValInMem(myStr);
        myStr=int_to_hex(splRegs.stackLimit);
        fitValInMem(myStr);
        myStr=int_to_hex(splRegs.stackCounter);
        fitValInMem(myStr);
        myStr=int_to_hex(splRegs.dataBase);
        fitValInMem(myStr);
        myStr=int_to_hex(splRegs.dataLimit);
        fitValInMem(myStr);
        myStr=int_to_hex(splRegs.flags);
        fitValInMem(myStr);
        for(int i=0;i<6;i++)
        {
            myStr=int_to_hex(splRegs.myReg[i]);
            fitValInMem(myStr);


        }
    }

/************************************************Print Memory/Stack***********************************************/
    void printMemory(int from)
    {
        for(int i=from;i<(128+from);i++)
        {
            cout<<i<<" : "<<(int)myMemory[i]<<endl;
            out<<i<<" : "<<(int)myMemory[i]<<endl;

        }

    }
/*******************************************************************************************************************/
    void printStack()                                                 //Printing Stack
    {
        cout<<endl<<"Print Stack"<<endl;
        out<<endl<<"Print Stack"<<endl;
        for(int i=splRegs.stackBase;i>(splRegs.stackBase-30) ;i--)
    {

        cout<<i<<": "<<(int)myMemory[i]<<"\t\t\t";
        out<<i<<": "<<(int)myMemory[i]<<"\t\t\t";
        if(i%2==0)
            {
                cout<<endl;
                out<<endl;
        }
    }
        cout<<endl;
        out<<endl;

    }
    void decSCounter(unsigned short int * myNum )
    {
        *myNum -= 1;
    }



    int  intruction(int myInt);//Function to execute the Instructions called by execute function

    //-----Instruction Set Functions
    void move(short int * firstOperand, short int * secondOperand);
    void  add (short int * firstOperand, short int * secondOperand);//Add instruction
    void sub(short int * firstOperand, short int * secondOperand);//Sub Instruction
    void  mul(short int * firstOperand, short int * secondOperand);//Mul Instruction
    int  div(short int * firstOperand, short int * secondOperand);//Div Instruction
    void And(short int * firstOperand, short int * secondOperand);//AnD Instruction
    void Or(short int * firstOperand, short int * secondOperand);//OR Instruction
    void moveI(short int * firstOperand,short int secondOperand);//MOVI Instruction
    void subI(short int * firstOperand,short int secondOperand);//ADDI Instruction
    void addI(short int * firstOperand,short int secondOperand);//ADDI Instruction
    void mulI(short int * firstOperand,short int secondOperand);//MULI Instruction
    int divI(short int * firstOperand,short int secondOperand);//MULI Instruction
    void andI(short int * firstOperand,short int secondOperand);//MULI Instruction
    void OrI(short int * firstOperand,short int secondOperand);//MULI Instruction
    int BZ(short int * firstOperand,short int secondOperand);//JUMP IF ZERO Instruction
    int BNZ(short int * firstOperand,short int secondOperand);////JUMP IF NOT ZERO Instruction
    int BC(short int * firstOperand,short int secondOperand);//JUMP IF CARRY Instruction
    int BS(short int * firstOperand,short int secondOperand);//JUMP IF SIGN Instruction
    int jmp(short int secondOperand);//JUMP Instruction
    int call(short int secondOperand,unsigned char * myM);//JUMP but save the PC to stack
    void loadW(short int *firstOperand,short int myImmediateValue);//Load to memeory
    void storeW(short int *firstOperand,short int myImmediateValue);//Load to memeory
    void shl(short int * firstOperand);//Shifting to left
    void shr(short int * firstOperand);//Shifting to left
    void ror(short int * firstOperand);//Shifting to left
    void rol(short int * firstOperand);//Shifting to left
    void inc (short int *firstOperand);//Incrementing
    void dec (short int *firstOperand);//Incrementing
    void Push(short int *firstOperan);//Push Instructions
    void Pop(short int *firstOperan);//Pop Instructions
    int setMemory(string * nameOfProcess,int noOfProcess);//Set memory
    void executeProg();//Execute Process
    int execptionHandling(int exeception_check, int tempValue);
    bool executeProgOnlyOne(int proID);
    int execptionHandling2(int exeception_check , int tempValue);


    string read_string()
{
        int cur_pos = 0; // position of caret
        int the_key = 0;
        int i;
        char str_to[40];
        int size=40;
        BITMAP *buffer = create_bitmap(800,600);
        BITMAP *fouth=load_bitmap("Images/BlankScreen.bmp",NULL);
        for (i = 0; i < size; i++)
                str_to[i] = '\0'; // 'clean' the string


        while (the_key>>8 != KEY_ENTER)
        {
                the_key = readkey();

                if ((the_key & 0xff) >= ' ') // get only valid chars
                {
                        str_to[cur_pos] = the_key & 0xff;
                        //cout<<str_to[cur_pos];
                        cur_pos++;
                        if (cur_pos > size-2) cur_pos = size-2;

                }

                if (the_key >> 8 == KEY_BACKSPACE)
                {
                        str_to[cur_pos] = '\0'; // chop the string
                        cur_pos --;
                        if (cur_pos < 0) cur_pos = 0;
                }

                // lame redraw (use double buffer, whatever)
                //clear(screen);
                masked_blit(fouth,buffer,0,0,0,0,800,640);


                textout_ex(buffer,font, str_to, 225,430, makecol(0,0,0),-1);
                blit(buffer,screen,0,0,0,0,800,600);
                clear_bitmap(buffer);


        }
        string myStr=str_to;
       // cout<<myStr;
        return myStr;

}




    string read_string2()
{
        int cur_pos = 0; // position of caret
        int the_key = 0;
        int i;
        char str_to[40];
        int size=40;
        BITMAP *buffer = create_bitmap(800,600);
        BITMAP *fouth=create_bitmap(600,500);
        clear_to_color(fouth, makecol(170,231,216));
        //clear_to_color(buffer, makecol(170,231,216));

        for (i = 0; i < size; i++)
                str_to[i] = '\0'; // 'clean' the string


        while (the_key>>8 != KEY_ENTER)
        {
                the_key = readkey();

                if ((the_key & 0xff) >= ' ') // get only valid chars
                {
                        str_to[cur_pos] = the_key & 0xff;
                        //cout<<str_to[cur_pos];
                        cur_pos++;
                        if (cur_pos > size-2) cur_pos = size-2;

                }

                if (the_key >> 8 == KEY_BACKSPACE)
                {
                        str_to[cur_pos] = '\0'; // chop the string
                        cur_pos --;
                        if (cur_pos < 0) cur_pos = 0;
                }

                // lame redraw (use double buffer, whatever)
                //clear(screen);

                masked_blit(fouth,buffer,0,0,200,50,800,640);
                textout_ex(fouth,font, str_to, 225,430, makecol(0,0,0),-1);


                blit(buffer,screen,0,0,0,0,800,600);
                clear_bitmap(buffer);


        }
        string myStr=str_to;
        //cout<<myStr<<endl;
        return myStr;

}


    string* StartMenu(int *noOfProcess)
{
            BITMAP *buffer = create_bitmap(800,600);
            BITMAP *first=load_bitmap("Images/BackGround.bmp",NULL);
            BITMAP *second=load_bitmap("Images/LoadScreen.bmp",NULL);
            BITMAP *third=load_bitmap("Images/NoOfPro.bmp",NULL);
            BITMAP *fouth=load_bitmap("Images/BlankScreen.bmp",NULL);

            masked_blit(first,buffer,0,0,0,0,800,640);
            blit(buffer,screen,0,0,0,0,800,600);
            readkey();

            clear_bitmap(buffer);

            masked_blit(second,buffer,0,0,0,0,800,640);
            blit(buffer,screen,0,0,0,0,800,600);


            readkey();
            clear_bitmap(buffer);

            masked_blit(third,buffer,0,0,0,0,800,640);
            blit(buffer,screen,0,0,0,0,800,600);
            *noOfProcess=((readkey() & 0xff)-48);
            if(*noOfProcess>0 && *noOfProcess<9){
            textprintf_ex(buffer, font, 225, 430, makecol(0,0,0),-1,"%d", *noOfProcess);
            }
            else{
            textout_ex(buffer, font,"Wrong No Input", 225, 430, makecol(0,0,0),-1);
            return StartMenu(noOfProcess);
            }
            blit(buffer,screen,0,0,0,0,800,600);

            readkey();
            clear_bitmap(buffer);

            masked_blit(fouth,buffer,0,0,0,0,800,640);
            blit(buffer,screen,0,0,0,0,800,600);
            string * myProcess=new string[*noOfProcess];
            for(int i=0;i<*noOfProcess;i++)
            {
                myProcess[i]=read_string();
                textout_ex(buffer, font,myProcess[i].c_str(), 225, 430, makecol(0,0,0),-1);
                blit(buffer,screen,0,0,0,0,800,600);
                clear_bitmap(buffer);
                masked_blit(fouth,buffer,0,0,0,0,800,640);
                blit(buffer,screen,0,0,0,0,800,600);

            }
            blit(buffer,screen,0,0,0,0,800,600);
            readkey();


            /*rectfill(buffer,0,0,100,200,makecol(85,90,50));
            blit(buffer,screen,0,0,0,0,800,600);
            readkey();
            clear_bitmap(buffer);*/
            destroy_bitmap(buffer);
            return myProcess;

}



};


#endif // MEMORYCLASS_H
