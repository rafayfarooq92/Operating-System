#include "splRegisters.h"

int splRegisters::getOvrFlag()                                                        //Checking Overflow Flag
{
            return bits[3];
}

void splRegisters::printFlagAllegro(BITMAP * fakeDisplay)
{
        clear_to_color(fakeDisplay, makecol(255,0,255));
        int height=22;
        textout_ex(fakeDisplay,font,"Flag Registers",0,0,makecol(0,0,0),-1);
        textprintf_ex(fakeDisplay, font, 10, 22, makecol(0,0,0),-1,"Carry Flag : %d   Zero Flag : %d ",myF[0],myF[1] );
        textprintf_ex(fakeDisplay, font, 10, 44, makecol(0,0,0),-1,"Signed Flag : %d   Overflow Flag : %d ",myF[2],myF[3]);

        blit(fakeDisplay,screen,0,0,200,300,600,500);



}

void splRegisters::PrintAllRegsAllegro(BITMAP * fakeDisplay)
{

    clear_to_color(fakeDisplay, makecol(255,0,255));
        int height=22;
        textout_ex(fakeDisplay,font,"Special Purpose Registers",0,0,makecol(0,0,0),-1);
        textprintf_ex(fakeDisplay, font, 10, 22, makecol(0,0,0),-1,"CodeCounter : %d   CodeLimit : %d ",codeCounter,codeLimit );
        textprintf_ex(fakeDisplay, font, 10, 44, makecol(0,0,0),-1,"CodeBase : %d   StactCounter : %d ",codeBase,stackCounter);
        textprintf_ex(fakeDisplay, font, 10, 66, makecol(0,0,0),-1,"StackBase : %d   StactLimit : %d ",stackBase,stackLimit );
        textprintf_ex(fakeDisplay, font, 10, 88, makecol(0,0,0),-1,"DataBase : %d   DataLimit : %d ",dataBase,dataLimit);

        blit(fakeDisplay,screen,0,0,200,360,600,500);


}

void splRegisters::PrintAllRegsAllegro2(BITMAP * fakeDisplay)
{

   // clear_to_color(fakeDisplay, makecol(255,0,255));
        int height=22;
        textout_ex(fakeDisplay,font,"Special Purpose Registers",0,250,makecol(0,0,0),-1);
        textprintf_ex(fakeDisplay, font, 10, 22+250, makecol(0,0,0),-1,"CodeCounter : %d   CodeLimit : %d ",codeCounter,codeLimit );
        textprintf_ex(fakeDisplay, font, 10, 44+250, makecol(0,0,0),-1,"CodeBase : %d   StactCounter : %d ",codeBase,stackCounter);
        textprintf_ex(fakeDisplay, font, 10, 66+250, makecol(0,0,0),-1,"StackBase : %d   StactLimit : %d ",stackBase,stackLimit );
        textprintf_ex(fakeDisplay, font, 10, 88+250, makecol(0,0,0),-1,"DataBase : %d   DataLimit : %d ",dataBase,dataLimit);

        blit(fakeDisplay,screen,0,0,200,50,600,500);


}

