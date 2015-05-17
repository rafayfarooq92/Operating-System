#include<allegro.h>
#include<iostream>
#include<fstream>
#include <cstdio>
#include <iomanip>
#include <cstdlib>
#include <bitset>
#include<cmath>
#include<ctime>
#include<sstream>


#include <cstring>
/*#include "splRegisters.h"
#include "generalRegisters.h"*/

#include "memoryClass.h"
//Adding Classess Files




using namespace std;
#define SCRHT 600
#define SCRWT 800
int linenumber=0;

int noOfProcess=0;


int defineButton(memoryClass * myRegs)
{
    int curMouse=NULL;
    int preMouse=NULL;
    BITMAP *buffer = create_bitmap(800,600);


    BITMAP *third=load_bitmap("Images/MainScreenToWork.bmp",NULL);
    myRegs->printProcess();
    bool Ender=false;
    while(Ender==false){
    preMouse=curMouse;
    masked_blit(third,buffer,0,0,0,0,800,640);
    show_mouse(buffer);
    if(mouse_b & 1)
    {
        curMouse=1;
    }
    else{
    curMouse=NULL;
    }


    /*****************Mouse Events*******************/
    if((mouse_x>0 && mouse_x<150) && (mouse_y>0 && mouse_y<35  ) && (mouse_b & 1) && preMouse!=curMouse)
    {

        myRegs->executeProg();
        if(readkey()>>8 == KEY_ESC)
        {
            Ender=true;
        }

    }
    else if((mouse_x>0 && mouse_x<150) && (mouse_y>35 && mouse_y<70  ) && (mouse_b & 1) && preMouse!=curMouse)
    {


        BITMAP * fakeDisplay=create_bitmap(800,600);
        BITMAP * error=load_bitmap("Images/Error.bmp",NULL);
        //myRegs->executeProgOnlyOne(5);
        clear_to_color(fakeDisplay, makecol(255,0,255));
        textout_ex(fakeDisplay,font,"Please Enter The Process ID.",0,0,makecol(0,0,0),-1);
        blit(fakeDisplay,screen,0,0,200,50,800,600);

        int cur_pos = 0; // position of caret
        int the_key = 0;
        int i;
        char str_to[40];
        int size=40;

        BITMAP *buffer = create_bitmap(800,600);
        clear_to_color(buffer, makecol(170,231,216));
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

                textout_ex(fakeDisplay,font, str_to, 0,30, makecol(0,0,0),-1);
                //masked_blit(fakeDisplay,buffer,0,0,200,50,800,640);

                blit(fakeDisplay,screen,0,0,200,50,800,600);
                //clear_bitmap(fakeDisplay);


        }
        //blit(fakeDisplay,screen,0,0,200,50,800,600);

        string myStr=str_to;




        //cout<<myVal<<endl;
        short int proID=myRegs->StringToIntConverter3(myStr);



            textprintf_ex(fakeDisplay, font, 0, 30, makecol(0,0,0),-1,"%d", proID);
            blit(fakeDisplay,screen,0,0,200,50,800,600);
            rest(20);
            bool good=myRegs->executeProgOnlyOne(proID);
            if(!good)
            {
                clear_bitmap(fakeDisplay);
                blit(error, fakeDisplay, 0,0,0,0,800,600);
                textout_ex(fakeDisplay, font,"Couldn't find the program specified.", 400, 30, makecol(0,0,0),-1);
                textout_ex(fakeDisplay, font,"Error in finding program of ID: ", 400, 50, makecol(0,0,0),-1);
                textprintf_ex(fakeDisplay, font, 560, 50, makecol(0,0,0),-1,"%d",proID);
                blit(fakeDisplay,screen,0,0,0,0,800,600);
                readkey();
                delete myRegs;
               /* myRegs->myCall();
                string * myStrQ=myRegs->StartMenu(&noOfProcess);*/

               /* myRegs->setMemory(myStrQ,noOfProcess);*/
                defineButton(myRegs);
            }
        int newVal=readkey()>>8;
        if(newVal == KEY_ESC && readkey()!=(proID+48))
        {
            Ender=true;
        }


    }

    else if((mouse_x>0 && mouse_x<150) && (mouse_y>70 && mouse_y<100  ) && (mouse_b & 1) && preMouse!=curMouse)
    {

        BITMAP * fakeDisplay=create_bitmap(800,600);
        BITMAP * error=load_bitmap("Images/Error.bmp",NULL);
        //myRegs->executeProgOnlyOne(5);
        clear_to_color(fakeDisplay, makecol(255,0,255));
        textout_ex(fakeDisplay,font,"Please Enter The Process ID.",0,0,makecol(0,0,0),-1);
        blit(fakeDisplay,screen,0,0,200,50,800,600);

        int cur_pos = 0; // position of caret
        int the_key = 0;
        int i;
        char str_to[40];
        int size=40;

        BITMAP *buffer = create_bitmap(800,600);
        clear_to_color(buffer, makecol(170,231,216));
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

                textout_ex(fakeDisplay,font, str_to, 0,30, makecol(0,0,0),-1);
                //masked_blit(fakeDisplay,buffer,0,0,200,50,800,640);

                blit(fakeDisplay,screen,0,0,200,50,800,600);
                //clear_bitmap(fakeDisplay);


        }
        //blit(fakeDisplay,screen,0,0,200,50,800,600);

        string myStr=str_to;




        //cout<<myVal<<endl;
        short int proID=myRegs->StringToIntConverter3(myStr);
            textprintf_ex(fakeDisplay, font, 0, 30, makecol(0,0,0),-1,"%d", proID);
            blit(fakeDisplay,screen,0,0,200,50,800,600);
            rest(200);
            clear_to_color(fakeDisplay, makecol(170,231,216));
            blit(fakeDisplay,screen,0,0,200,50,800,600);

            bool good=myRegs->Block(proID);
            if(!good)
            {
                clear_bitmap(fakeDisplay);
                blit(error, fakeDisplay, 0,0,0,0,800,600);
                textout_ex(fakeDisplay, font,"Couldn't find the program specified.", 400, 30, makecol(0,0,0),-1);
                textout_ex(fakeDisplay, font,"Error in finding program of ID: ", 400, 50, makecol(0,0,0),-1);
                textprintf_ex(fakeDisplay, font, 560, 50, makecol(0,0,0),-1,"%d",proID);
                blit(fakeDisplay,screen,0,0,0,0,800,600);
                readkey();
                delete myRegs;
             /*   string * myStrQ=myRegs->StartMenu(&noOfProcess);

                myRegs->setMemory(myStrQ,noOfProcess);*/
                defineButton(myRegs);
            }

        int newVal=readkey()>>8;
        if(newVal == KEY_ESC && readkey()!=(proID+48))
        {
            Ender=true;
        }

    }
    else if((mouse_x>0 && mouse_x<150) && (mouse_y>100 && mouse_y<130  ) && (mouse_b & 1) && preMouse!=curMouse)
    {


        BITMAP * fakeDisplay=create_bitmap(800,600);
        BITMAP * error=load_bitmap("Images/Error.bmp",NULL);
        //myRegs->executeProgOnlyOne(5);
        clear_to_color(fakeDisplay, makecol(255,0,255));
        textout_ex(fakeDisplay,font,"Please Enter The Process ID.",0,0,makecol(0,0,0),-1);
        blit(fakeDisplay,screen,0,0,200,50,800,600);

        int cur_pos = 0; // position of caret
        int the_key = 0;
        int i;
        char str_to[40];
        int size=40;

        BITMAP *buffer = create_bitmap(800,600);
        clear_to_color(buffer, makecol(170,231,216));
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

                textout_ex(fakeDisplay,font, str_to, 0,30, makecol(0,0,0),-1);
                //masked_blit(fakeDisplay,buffer,0,0,200,50,800,640);

                blit(fakeDisplay,screen,0,0,200,50,800,600);
                //clear_bitmap(fakeDisplay);


        }
        //blit(fakeDisplay,screen,0,0,200,50,800,600);

        string myStr=str_to;




        //cout<<myVal<<endl;
        short int proID=myRegs->StringToIntConverter3(myStr);
            textprintf_ex(fakeDisplay, font, 0, 30, makecol(0,0,0),-1,"%d", proID);
            blit(fakeDisplay,screen,0,0,200,50,800,600);
            rest(200);
            clear_to_color(fakeDisplay, makecol(170,231,216));
            blit(fakeDisplay,screen,0,0,200,50,800,600);

            bool good=myRegs->debugOnce(proID);
            if(!good)
            {
                clear_bitmap(fakeDisplay);
                blit(error, fakeDisplay, 0,0,0,0,800,600);
                textout_ex(fakeDisplay, font,"Couldn't find the program specified.", 400, 30, makecol(0,0,0),-1);
                textout_ex(fakeDisplay, font,"Error in finding program of ID: ", 400, 50, makecol(0,0,0),-1);
                textprintf_ex(fakeDisplay, font, 560, 50, makecol(0,0,0),-1,"%d",proID);
                blit(fakeDisplay,screen,0,0,0,0,800,600);
                readkey();
                delete myRegs;
             /*   string * myStrQ=myRegs->StartMenu(&noOfProcess);

                myRegs->setMemory(myStrQ,noOfProcess);*/
                defineButton(myRegs);
            }

        int newVal=readkey()>>8;
        if(newVal == KEY_ESC && readkey()!=(proID+48))
        {
            Ender=true;
        }




    }

    else if((mouse_x>0 && mouse_x<150) && (mouse_y>130 && mouse_y<160  ) && (mouse_b & 1) && preMouse!=curMouse)
    {


        myRegs->debugOnceAll();

        int newVal=readkey()>>8;
        if(newVal == KEY_ESC )
        {
            Ender=true;
        }

    }
    else if((mouse_x>0 && mouse_x<150) && (mouse_y>150 && mouse_y<180  ) && (mouse_b & 1) && preMouse!=curMouse)
    {


        BITMAP * fakeDisplay=create_bitmap(800,600);
        BITMAP * error=load_bitmap("Images/Error.bmp",NULL);
        //myRegs->executeProgOnlyOne(5);
        clear_to_color(fakeDisplay, makecol(255,0,255));
        textout_ex(fakeDisplay,font,"Please Enter The Process ID.",0,0,makecol(0,0,0),-1);
        blit(fakeDisplay,screen,0,0,200,50,800,600);

        int cur_pos = 0; // position of caret
        int the_key = 0;
        int i;
        char str_to[40];
        int size=40;

        BITMAP *buffer = create_bitmap(800,600);
        clear_to_color(buffer, makecol(170,231,216));
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

                textout_ex(fakeDisplay,font, str_to, 0,30, makecol(0,0,0),-1);
                //masked_blit(fakeDisplay,buffer,0,0,200,50,800,640);

                blit(fakeDisplay,screen,0,0,200,50,800,600);
                //clear_bitmap(fakeDisplay);


        }
        //blit(fakeDisplay,screen,0,0,200,50,800,600);

        string myStr=str_to;




        //cout<<myVal<<endl;
        short int proID=myRegs->StringToIntConverter3(myStr);
            textprintf_ex(fakeDisplay, font, 0, 30, makecol(0,0,0),-1,"%d", proID);
            blit(fakeDisplay,screen,0,0,200,50,800,600);
            rest(200);
            clear_to_color(fakeDisplay, makecol(170,231,216));
            blit(fakeDisplay,screen,0,0,200,50,800,600);

            bool good=myRegs->kill(proID);
            if(!good)
            {
                clear_bitmap(fakeDisplay);
                blit(error, fakeDisplay, 0,0,0,0,800,600);
                textout_ex(fakeDisplay, font,"Couldn't find the program specified.", 400, 30, makecol(0,0,0),-1);
                textout_ex(fakeDisplay, font,"Error in finding program of ID: ", 400, 50, makecol(0,0,0),-1);
                textprintf_ex(fakeDisplay, font, 560, 50, makecol(0,0,0),-1,"%d",proID);
                blit(fakeDisplay,screen,0,0,0,0,800,600);
                readkey();
                delete myRegs;
                /*string * myStrQ=myRegs->StartMenu(&noOfProcess);

                myRegs->setMemory(myStrQ,noOfProcess);*/
                defineButton(myRegs);
            }

        int newVal=readkey()>>8;
        if(newVal == KEY_ESC && readkey()!=(proID+48))
        {
            Ender=true;
        }


    }

    else if((mouse_x>0 && mouse_x<150) && (mouse_y>180 && mouse_y<210  ) && (mouse_b & 1) && preMouse!=curMouse)
    {

        BITMAP * fakeDisplay=create_bitmap(800,600);
        BITMAP * error=load_bitmap("Images/Error.bmp",NULL);
        //myRegs->executeProgOnlyOne(5);
        clear_to_color(fakeDisplay, makecol(255,0,255));
        textout_ex(fakeDisplay,font,"Please Enter The Process ID.",0,0,makecol(0,0,0),-1);
        blit(fakeDisplay,screen,0,0,200,50,800,600);

        int cur_pos = 0; // position of caret
        int the_key = 0;
        int i;
        char str_to[40];
        int size=40;

        BITMAP *buffer = create_bitmap(800,600);
        clear_to_color(buffer, makecol(170,231,216));
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

                textout_ex(fakeDisplay,font, str_to, 0,30, makecol(0,0,0),-1);
                //masked_blit(fakeDisplay,buffer,0,0,200,50,800,640);

                blit(fakeDisplay,screen,0,0,200,50,800,600);
                //clear_bitmap(fakeDisplay);


        }
        //blit(fakeDisplay,screen,0,0,200,50,800,600);

        string myStr=str_to;




        //cout<<myVal<<endl;
        short int proID=myRegs->StringToIntConverter3(myStr);
            textprintf_ex(fakeDisplay, font, 0, 30, makecol(0,0,0),-1,"%d", proID);
            blit(fakeDisplay,screen,0,0,200,50,800,600);
            rest(200);
            clear_to_color(fakeDisplay, makecol(170,231,216));
            blit(fakeDisplay,screen,0,0,200,50,800,600);

            bool good=myRegs->clone(proID);
            if(!good)
            {
                clear_bitmap(fakeDisplay);
                blit(error, fakeDisplay, 0,0,0,0,800,600);
                textout_ex(fakeDisplay, font,"Couldn't find the program specified.", 400, 30, makecol(0,0,0),-1);
                textout_ex(fakeDisplay, font,"Error in finding program of ID: ", 400, 50, makecol(0,0,0),-1);
                textprintf_ex(fakeDisplay, font, 560, 50, makecol(0,0,0),-1,"%d",proID);
                blit(fakeDisplay,screen,0,0,0,0,800,600);
                readkey();
                delete myRegs;
                /*string * myStrQ=myRegs->StartMenu(&noOfProcess);

                myRegs->setMemory(myStrQ,noOfProcess);*/
                defineButton(myRegs);
            }

        int newVal=readkey()>>8;
        if(newVal == KEY_ESC && readkey()!=(proID+48))
        {
            Ender=true;
        }

    }
    else if((mouse_x>0 && mouse_x<150) && (mouse_y>210 && mouse_y<237  ) && (mouse_b & 1) && preMouse!=curMouse)
    {

        BITMAP * fakeDisplay=create_bitmap(800,600);
        BITMAP * error=load_bitmap("Images/Error.bmp",NULL);
        //myRegs->executeProgOnlyOne(5);
        clear_to_color(fakeDisplay, makecol(255,0,255));
        textout_ex(fakeDisplay,font,"Please Enter The Process ID.",0,0,makecol(0,0,0),-1);
        blit(fakeDisplay,screen,0,0,200,50,800,600);

        int cur_pos = 0; // position of caret
        int the_key = 0;
        int i;
        char str_to[40];
        int size=40;

        BITMAP *buffer = create_bitmap(800,600);
        clear_to_color(buffer, makecol(170,231,216));
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

                textout_ex(fakeDisplay,font, str_to, 0,30, makecol(0,0,0),-1);
                //masked_blit(fakeDisplay,buffer,0,0,200,50,800,640);

                blit(fakeDisplay,screen,0,0,200,50,800,600);
                //clear_bitmap(fakeDisplay);


        }
        //blit(fakeDisplay,screen,0,0,200,50,800,600);

        string myStr=str_to;




        //cout<<myVal<<endl;
        short int proID=myRegs->StringToIntConverter3(myStr);
            textprintf_ex(fakeDisplay, font, 0, 30, makecol(0,0,0),-1,"%d", proID);
            blit(fakeDisplay,screen,0,0,200,50,800,600);
            rest(200);
            clear_to_color(fakeDisplay, makecol(170,231,216));
            blit(fakeDisplay,screen,0,0,200,50,800,600);

            bool good=myRegs->unblock(proID);
            if(!good)
            {
                clear_bitmap(fakeDisplay);
                blit(error, fakeDisplay, 0,0,0,0,800,600);
                textout_ex(fakeDisplay, font,"Couldn't find the program specified.", 400, 30, makecol(0,0,0),-1);
                textout_ex(fakeDisplay, font,"Error in finding program of ID: ", 400, 50, makecol(0,0,0),-1);
                textprintf_ex(fakeDisplay, font, 560, 50, makecol(0,0,0),-1,"%d",proID);
                blit(fakeDisplay,screen,0,0,0,0,800,600);
                readkey();
                delete myRegs;
             /*   string * myStrQ=myRegs->StartMenu(&noOfProcess);

                myRegs->setMemory(myStrQ,noOfProcess);*/
                defineButton(myRegs);
            }

        int newVal=readkey()>>8;
        if(newVal == KEY_ESC && readkey()!=(proID+48))
        {
            Ender=true;
        }


    }
    else if((mouse_x>0 && mouse_x<150) && (mouse_y>237 && mouse_y<280  ) && (mouse_b & 1) && preMouse!=curMouse)
    {
        BITMAP * myBitmap=create_bitmap(600,500);
        clear_to_color(myBitmap, makecol(170,231,216));
        textout_ex(myBitmap,font,"Start Typing Without pressing anyother key.",0,0,makecol(255,0,0),-1);
        blit(myBitmap,screen,0,0,200,50,800,600);
        string myStr=myRegs->read_string();
        myRegs->loadProc(myStr);
        if(readkey()>>8 == KEY_ESC)
        {
            Ender=true;
        }

    }

    else if((mouse_x>0 && mouse_x<150) && (mouse_y>280 && mouse_y<315  ) && (mouse_b & 1) && preMouse!=curMouse)
    {



        BITMAP * fakeDisplay=create_bitmap(800,600);
        BITMAP * buffering=create_bitmap(800,600);

        BITMAP * error=load_bitmap("Images/Error.bmp",NULL);
        //myRegs->executeProgOnlyOne(5);
        clear_to_color(fakeDisplay, makecol(255,0,255));
        textout_ex(fakeDisplay,font,"Please Enter The Process ID.",0,0,makecol(0,0,0),-1);
        blit(fakeDisplay,screen,0,0,200,50,800,600);

        //string myVal=myRegs->read_string2();


        int cur_pos = 0; // position of caret
        int the_key = 0;
        int i;
        char str_to[40];
        int size=40;

        BITMAP *buffer = create_bitmap(800,600);
        clear_to_color(buffer, makecol(170,231,216));
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

                textout_ex(fakeDisplay,font, str_to, 0,30, makecol(0,0,0),-1);
                //masked_blit(fakeDisplay,buffer,0,0,200,50,800,640);

                blit(fakeDisplay,screen,0,0,200,50,800,600);
                //clear_bitmap(fakeDisplay);


        }
        //blit(fakeDisplay,screen,0,0,200,50,800,600);

        string myStr=str_to;




        //cout<<myVal<<endl;
        short int proID=myRegs->StringToIntConverter3(myStr);

            textprintf_ex(fakeDisplay, font, 0, 30, makecol(0,0,0),-1,"%d", proID);
            blit(fakeDisplay,screen,0,0,200,50,800,600);
            rest(200);
            clear_to_color(fakeDisplay, makecol(170,231,216));
            blit(fakeDisplay,screen,0,0,200,50,800,600);

            bool good=myRegs->printPCB(proID,fakeDisplay);
            if(!good)
            {
                clear_bitmap(fakeDisplay);
                blit(error, fakeDisplay, 0,0,0,0,800,600);
                textout_ex(fakeDisplay, font,"Couldn't find the program specified.", 400, 30, makecol(0,0,0),-1);
                textout_ex(fakeDisplay, font,"Error in finding program of ID: ", 400, 50, makecol(0,0,0),-1);
                textprintf_ex(fakeDisplay, font, 400, 80, makecol(0,0,0),-1,"%d",proID);
                blit(fakeDisplay,screen,0,0,0,0,800,600);
                readkey();
                delete myRegs;
               /* string * myStrQ=myRegs->StartMenu(&noOfProcess);

                myRegs->setMemory(myStrQ,noOfProcess);*/
                defineButton(myRegs);
            }
        int newVal=readkey()>>8;
        if(newVal == KEY_ESC && readkey()!=(proID+48))
        {
            Ender=true;
        }



    }
    else if((mouse_x>0 && mouse_x<150) && (mouse_y>315 && mouse_y<342  ) && (mouse_b & 1) && preMouse!=curMouse)
    {

        myRegs->printProcess();
        if(readkey()>>8 == KEY_ESC)
        {
            Ender=true;
        }

    }

    else if((mouse_x>0 && mouse_x<150) && (mouse_y>342 && mouse_y<370  ) && (mouse_b & 1) && preMouse!=curMouse)
    {

        BITMAP * fakeDisplay=create_bitmap(800,600);
        BITMAP * buffering=create_bitmap(800,600);

        BITMAP * error=load_bitmap("Images/Error.bmp",NULL);
        //myRegs->executeProgOnlyOne(5);
        clear_to_color(fakeDisplay, makecol(255,0,255));
        textout_ex(fakeDisplay,font,"Please Enter The Process ID.",0,0,makecol(0,0,0),-1);
        blit(fakeDisplay,screen,0,0,200,50,800,600);

        //string myVal=myRegs->read_string2();


        int cur_pos = 0; // position of caret
        int the_key = 0;
        int i;
        char str_to[40];
        int size=40;

        BITMAP *buffer = create_bitmap(800,600);
        clear_to_color(buffer, makecol(170,231,216));
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

                textout_ex(fakeDisplay,font, str_to, 0,30, makecol(0,0,0),-1);
                //masked_blit(fakeDisplay,buffer,0,0,200,50,800,640);

                blit(fakeDisplay,screen,0,0,200,50,800,600);
                //clear_bitmap(fakeDisplay);


        }
        //blit(fakeDisplay,screen,0,0,200,50,800,600);

        string myStr=str_to;




        //cout<<myVal<<endl;
        short int proID=myRegs->StringToIntConverter3(myStr);

            textprintf_ex(fakeDisplay, font, 0, 30, makecol(0,0,0),-1,"%d", proID);
            blit(fakeDisplay,screen,0,0,200,50,800,600);
            rest(200);
            clear_to_color(fakeDisplay, makecol(170,231,216));
            blit(fakeDisplay,screen,0,0,200,50,800,600);

            bool good=myRegs->printPageTable(proID);
            if(!good)
            {
                clear_bitmap(fakeDisplay);
                blit(error, fakeDisplay, 0,0,0,0,800,600);
                textout_ex(fakeDisplay, font,"Couldn't find the program specified.", 400, 30, makecol(0,0,0),-1);
                textout_ex(fakeDisplay, font,"Error in finding program of ID: ", 400, 50, makecol(0,0,0),-1);
                textprintf_ex(fakeDisplay, font, 400, 80, makecol(0,0,0),-1,"%d",proID);
                blit(fakeDisplay,screen,0,0,0,0,800,600);
                readkey();
                delete myRegs;
               /* string * myStrQ=myRegs->StartMenu(&noOfProcess);

                myRegs->setMemory(myStrQ,noOfProcess);*/
                defineButton(myRegs);
            }
        int newVal=readkey()>>8;
        if(newVal == KEY_ESC && readkey()!=(proID+48))
        {
            Ender=true;
        }

    }
    else if((mouse_x>0 && mouse_x<150) && (mouse_y>370 && mouse_y<398  ) && (mouse_b & 1) && preMouse!=curMouse)
    {

        BITMAP * fakeDisplay=create_bitmap(800,600);
        BITMAP * buffering=create_bitmap(800,600);

        BITMAP * error=load_bitmap("Images/Error.bmp",NULL);
        //myRegs->executeProgOnlyOne(5);
        clear_to_color(fakeDisplay, makecol(255,0,255));
        textout_ex(fakeDisplay,font,"Please Enter The Process ID.",0,0,makecol(0,0,0),-1);
        blit(fakeDisplay,screen,0,0,200,50,800,600);

        //string myVal=myRegs->read_string2();


        int cur_pos = 0; // position of caret
        int the_key = 0;
        int i;
        char str_to[40];
        int size=40;

        BITMAP *buffer = create_bitmap(800,600);
        clear_to_color(buffer, makecol(170,231,216));
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

                textout_ex(fakeDisplay,font, str_to, 0,30, makecol(0,0,0),-1);
                //masked_blit(fakeDisplay,buffer,0,0,200,50,800,640);

                blit(fakeDisplay,screen,0,0,200,50,800,600);
                //clear_bitmap(fakeDisplay);


        }
        //blit(fakeDisplay,screen,0,0,200,50,800,600);

        string myStr=str_to;




        //cout<<myVal<<endl;
        short int proID=myRegs->StringToIntConverter3(myStr);

            textprintf_ex(fakeDisplay, font, 0, 30, makecol(0,0,0),-1,"%d", proID);
            blit(fakeDisplay,screen,0,0,200,50,800,600);
            rest(200);
            clear_to_color(fakeDisplay, makecol(170,231,216));
            blit(fakeDisplay,screen,0,0,200,50,800,600);

            bool good=myRegs->memDump(proID);
            if(!good)
            {
                clear_bitmap(fakeDisplay);
                blit(error, fakeDisplay, 0,0,0,0,800,600);
                textout_ex(fakeDisplay, font,"Couldn't find the program specified.", 400, 30, makecol(0,0,0),-1);
                textout_ex(fakeDisplay, font,"Error in finding program of ID: ", 400, 50, makecol(0,0,0),-1);
                textprintf_ex(fakeDisplay, font, 400, 80, makecol(0,0,0),-1,"%d",proID);
                blit(fakeDisplay,screen,0,0,0,0,800,600);
                readkey();
                delete myRegs;
               /* string * myStrQ=myRegs->StartMenu(&noOfProcess);

                myRegs->setMemory(myStrQ,noOfProcess);*/
                defineButton(myRegs);
            }
        int newVal=readkey()>>8;
        if(newVal == KEY_ESC && readkey()!=(proID+48))
        {
            Ender=true;
        }

    }

    else if((mouse_x>0 && mouse_x<150) && (mouse_y>398 && mouse_y<425  ) && (mouse_b & 1) && preMouse!=curMouse)
    {

        myRegs->dumpFreeFrame();
        if(readkey()>>8 == KEY_ESC)
        {
            Ender=true;
        }

    }
    else if((mouse_x>0 && mouse_x<150) && (mouse_y>425 && mouse_y<458  ) && (mouse_b & 1) && preMouse!=curMouse)
    {

        BITMAP * fakeDisplay=create_bitmap(800,600);
        BITMAP * buffering=create_bitmap(800,600);

        BITMAP * error=load_bitmap("Images/Error.bmp",NULL);
        //myRegs->executeProgOnlyOne(5);
        clear_to_color(fakeDisplay, makecol(255,0,255));
        textout_ex(fakeDisplay,font,"Please Enter The Process ID.",0,0,makecol(0,0,0),-1);
        blit(fakeDisplay,screen,0,0,200,50,800,600);

        //string myVal=myRegs->read_string2();


        int cur_pos = 0; // position of caret
        int the_key = 0;
        int i;
        char str_to[40];
        int size=40;

        BITMAP *buffer = create_bitmap(800,600);
        clear_to_color(buffer, makecol(170,231,216));
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

                textout_ex(fakeDisplay,font, str_to, 0,30, makecol(0,0,0),-1);
                //masked_blit(fakeDisplay,buffer,0,0,200,50,800,640);

                blit(fakeDisplay,screen,0,0,200,50,800,600);
                //clear_bitmap(fakeDisplay);


        }
        //blit(fakeDisplay,screen,0,0,200,50,800,600);

        string myStr=str_to;




        //cout<<myVal<<endl;
        short int proID=myRegs->StringToIntConverter3(myStr);

            textprintf_ex(fakeDisplay, font, 0, 30, makecol(0,0,0),-1,"%d", proID);
            blit(fakeDisplay,screen,0,0,200,50,800,600);
            rest(200);
            clear_to_color(fakeDisplay, makecol(170,231,216));
            blit(fakeDisplay,screen,0,0,200,50,800,600);

            bool good=myRegs->memoryDetails(proID);
            if(!good)
            {
                clear_bitmap(fakeDisplay);
                blit(error, fakeDisplay, 0,0,0,0,800,600);
                textout_ex(fakeDisplay, font,"Couldn't find the program specified.", 400, 30, makecol(0,0,0),-1);
                textout_ex(fakeDisplay, font,"Error in finding program of ID: ", 400, 50, makecol(0,0,0),-1);
                textprintf_ex(fakeDisplay, font, 400, 80, makecol(0,0,0),-1,"%d",proID);
                blit(fakeDisplay,screen,0,0,0,0,800,600);
                readkey();
                delete myRegs;
               /* string * myStrQ=myRegs->StartMenu(&noOfProcess);

                myRegs->setMemory(myStrQ,noOfProcess);*/
                defineButton(myRegs);
            }
        int newVal=readkey()>>8;
        if(newVal == KEY_ESC && readkey()!=(proID+48))
        {
            Ender=true;
        }

    }
    else if((mouse_x>0 && mouse_x<150) && (mouse_y>458 && mouse_y<485  ) && (mouse_b & 1) && preMouse!=curMouse)
    {



        myRegs->printFrames();

        if(readkey()>>8 == KEY_ESC)
        {
            Ender=true;
        }

    }
    else if((mouse_x>0 && mouse_x<150) && (mouse_y>490 && mouse_y<525  ) && (mouse_b & 1) && preMouse!=curMouse)
    {

        myRegs->printAllRegsAllegro();
        if(readkey()>>8 == KEY_ESC)
        {
            Ender=true;
        }

    }
    else if((mouse_x>0 && mouse_x<150) && (mouse_y>525 && mouse_y<560  ) && (mouse_b & 1) && preMouse!=curMouse)
    {


            Ender=true;


    }
    /************Mouse Events Ends********************/

    blit(buffer,screen,0,0,0,0,800,600);
    clear_bitmap(buffer);
    }
    if(Ender==true){allegro_exit();exit(1);}
    destroy_bitmap(buffer);

}


int main()
{
    allegro_init();


   // set_color_depth(32);
    install_keyboard();
    install_mouse();
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0);
    set_window_title("Virtual Operating System");


    memoryClass myRegs;
    bool Ender=false;
    string * myStr=myRegs.StartMenu(&noOfProcess);
    cout<<noOfProcess<<endl;
    cout<<myStr[0]<<endl;

    myRegs.setMemory(myStr,noOfProcess);
    cout<<"Start"<<endl;

    //myRegs.printMemory(128);
    //myRegs.PrintPCB(0);
    defineButton(&myRegs);
/*
    string myStr;
    myStr=read_string();
    cout<<myStr;

*/
    readkey();




    allegro_exit();


    return 0;
}
END_OF_MAIN()
