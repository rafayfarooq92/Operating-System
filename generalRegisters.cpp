#include "generalRegisters.h"

void generalRegisters::printRegs()                                                    // Register Printing Function after each Instruction
    {
        cout<<"General Purpose Registers"<<endl;
        out<<"General Purpose Registers"<<endl;
        for(int i=0,j=8;i<8&&j<16;j++,i++){
        cout<<"R"<<i<<" "<<myReg[i]<<"\t\t\t"<<"R"<<j<<" "<<myReg[j]<<endl;
        out<<"R"<<i<<" "<<myReg[i]<<"\t\t\t"<<"R"<<j<<" "<<myReg[j]<<endl;
        }
    }

    void generalRegisters::printRegsAllegro(BITMAP * fakeDisplay)                                                    // Register Printing Function after each Instruction
    {
        clear_to_color(fakeDisplay, makecol(255,0,255));
        int height=22;
        textout_ex(fakeDisplay,font,"General Purpose Registers",0,0,makecol(0,0,0),-1);
        for(int i=0,j=8;i<8&&j<16;j++,i++){
        textprintf_ex(fakeDisplay, font, 110, (height*i)+25, makecol(0,0,0),-1,"R%d : %d \t\t  R%d : %d ",i,myReg[i],j,myReg[j] );
        }
        blit(fakeDisplay,screen,0,0,200,100,600,500);

    }
    void generalRegisters::printRegsAllegro2(BITMAP * fakeDisplay)                                                    // Register Printing Function after each Instruction
    {
      //  clear_to_color(fakeDisplay, makecol(255,0,255));
        int height=22;
        textout_ex(fakeDisplay,font,"General Purpose Registers",0,50,makecol(0,0,0),-1);
        for(int i=0,j=8;i<8&&j<16;j++,i++){
        textprintf_ex(fakeDisplay, font, 110, (height*i)+65, makecol(0,0,0),-1,"R%d : %d \t\t  R%d : %d ",i,myReg[i],j,myReg[j] );
        }

        blit(fakeDisplay,screen,0,0,200,50,600,500);

    }

