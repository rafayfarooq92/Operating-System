

#include "memoryClass.h"



/************************************Set Memory*************************************************/

int memoryClass::setMemory(string * nameOfProcess,int noOfProcess)
{
    int j=0;
    BITMAP * error=load_bitmap("Images/Error.bmp",NULL);
    install_keyboard();
    for(int i=0;i<noOfProcess;i++)
    {
          myFile.open(nameOfProcess[i].c_str(),ios::binary | ios::in);
          if(myFile.good())                                     //Reading through the file
          {
                priority=myFile.get();
                cout<<"Priorr:"<<priority<<endl;
                PID=myFile.get();
                myMemory[PCBcounter++]=PID;                       //Memory[0]=PID;
                processIDs[i]=PID;
                myMemory[PCBcounter++]=priority;                  //Memory[1]=Priority
                int myCostInt;
                for(int k=0;k<2;k++)
                {

                    switch (myFile.get())
                        {
                    case 1:
                        splRegs.dataLimit=calcDataSize();             //Fetch the Data Size and convert it to integer
                        noOfDataFrames=(splRegs.dataLimit/128)+1;     //Finding the Frames required for Code
                        fillDFrameTable(noOfDataFrames,i,userCounter);//Filling the Code Frames;Parameters passed are Number of Data Frames, number of Process and User counter;
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
                        fillCFrameTable(noOfCodeFrames,i,userCounter);    //Filling the Code Frames;Parameters passed are Number of Data Frames, number of Process and User counter;
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

                    if(i%2==0)
                    splRegs.stackBase=(((22+i)*pageSize)-1);          //Maintaining Stack Base
                    else
                    splRegs.stackBase=(((22+(i-1))*pageSize)-1)-64;
                    splRegs.stackLimit=(pageSize/2);                  //Maintaining Stack Size whic is 64
                    splRegs.stackCounter=0;

                    myStr=int_to_hex((splRegs.dataLimit)+(splRegs.codeLimit));
                    fitValInMem(myStr);                               //Fit Data sizes into Memory calculated above
                    loadGeneralRegInMemory();                         //Loading General Registers
                    loadSpecialRegInMemory();
                    //For execution time and waiting time
                    PCBcounter+=4;
                    freePCB[(PCBcounter/pageSize)]=1;
                    myMemory[PCBcounter++]=nameOfProcess[i].length();
                    for(int k=0;k<nameOfProcess[i].length();k++)
                    {
                        myMemory[PCBcounter++]=nameOfProcess[i][k];
                    }
                    userCounter = (((userCounter+pageSize)/pageSize)*pageSize);
                    PCBcounter = (((PCBcounter+(pageSize))/pageSize)*pageSize);
                    cout<<"PRO:"<<priority<<endl;
                    if(priority>=16 && priority<=31)
                    {
                    enqueue(myMemory[i*128]);                        //Sending to Round Robin
                    }
                    else if(priority>=0 && priority<=15)
                    {
                        Pinsert(myMemory[(i*128)+1]);                  //Sending Priority of Required Process
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
                textout_ex(buffer, font,nameOfProcess[i].c_str(), 520, 50, makecol(0,0,0),-1);
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

    }


/*  void memoryClass::setMemory()
    {

        cout<<"How Many Processes You Want to run?:";
        cin>>noOfProcess;
        int j=0;
        if(noOfProcess>=1 && noOfProcess<=8)
        {
            for(int i=0;i<noOfProcess;i++)
            {
                cout<<"Input the program file name:";
                cin>>nameOfProcess;
                myFile.open(nameOfProcess.c_str(),ios::binary | ios::in);
                if(myFile.good())                                     //Reading through the file
                {
                    priority=myFile.get();
                    PID=myFile.get();
                    myMemory[PCBcounter++]=PID;                       //Memory[0]=PID;
                    myMemory[PCBcounter++]=priority;                  //Memory[1]=Priority
                    int myCostInt;
                 for(int k=0;k<2;k++)
                 {

                    switch (myFile.get())
                        {
                    case 1:
                        splRegs.dataLimit=calcDataSize();             //Fetch the Data Size and convert it to integer
                        noOfDataFrames=(splRegs.dataLimit/128)+1;     //Finding the Frames required for Code
                        fillDFrameTable(noOfDataFrames,i,userCounter);//Filling the Code Frames;Parameters passed are Number of Data Frames, number of Process and User counter;
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
                        fillCFrameTable(noOfCodeFrames,i,userCounter);    //Filling the Code Frames;Parameters passed are Number of Data Frames, number of Process and User counter;
                        j=0;
                        while(j<(splRegs.codeLimit))
                        {
                        myMemory[userCounter++]=myFile.get();
                        j++;
                        }
                        break;
                    default:
                        cout<<"No Data or Code Segment Specified"<<endl;
                        break;

                        }
                }

                    if(i%2==0)
                    splRegs.stackBase=(((22+i)*pageSize)-1);          //Maintaining Stack Base
                    else
                    splRegs.stackBase=(((22+(i-1))*pageSize)-1)-64;
                    splRegs.stackLimit=(pageSize/2);                  //Maintaining Stack Size whic is 64
                    splRegs.stackCounter=0;

                    myStr=int_to_hex((splRegs.dataLimit)+(splRegs.codeLimit));
                    fitValInMem(myStr);                               //Fit Data sizes into Memory calculated above
                    loadGeneralRegInMemory();                         //Loading General Registers
                    loadSpecialRegInMemory();
                    //For execution time and waiting time
                    PCBcounter+=4;

                    myMemory[PCBcounter++]=nameOfProcess.length();
                    for(int k=0;k<nameOfProcess.length();k++)
                    {
                        myMemory[PCBcounter++]=nameOfProcess[k];
                    }
                    userCounter = (((userCounter+pageSize)/pageSize)*pageSize);
                    PCBcounter = (((PCBcounter+(pageSize))/pageSize)*pageSize);
                    if(priority>=0 && priority<=15)
                    {
                        Pinsert(myMemory[(i*128)+1]);                  //Sending Priority of Required Process
                    }
                    else
                    {
                    enqueue(myMemory[i*128]);                        //Sending to Round Robin
                    }

                }
                else                                                  //File could not found
                {
                cout<<"Couldn't find the program file specified."<<endl;
                cout<<"Error in file:"<<nameOfProcess<<endl;
                out<<"Couldn't find the program file specified."<<endl;
                out<<"Error in file:"<<nameOfProcess<<endl;

                }
                myFile.close();
            }


        }
        else
        {
            cout<<"No Or Many Processes Loaded. Mini No is 1 and Max is 8."<<endl;
            out<<"No Or Many Processes Loaded. Mini No is 1 and Max is 8."<<endl;

        }
         bubbleSort(myMemory,Pelements);                              //Sorting the Prioirty Queue

    }/*

/**************************************Executiing Process***********************************************/
    void memoryClass::executeProg()
    {
         /*******************************Executing Priorirty Queue*************************************/

        while(!PisEmpty())
        {
            priority=Premove();
            PCBcounter=1;                                             // Representing Priority of Process in a PCB and 0 represent ID
            for(int j=0;j<8;j++)
            {
                if(myMemory[PCBcounter]!=priority)
                PCBcounter = ((j+1)*pageSize)+1;
                else
                break;
            }
            bool found=false;
            if(freePCB[(PCBcounter+1)/pageSize]==1 && myMemory[PCBcounter+98]==0)
                {
                    found=true;

                }
            if(found){
            cout<<"Starting Process of Priority: \t"<<priority<<endl;
            out<<"Starting Process of Priority: \t"<<priority<<endl;
            loadIt(PCBcounter-1);
/*******************************Linear Adress Translation***************************/
            int tempValue=PCBcounter/128;
            int frameNum=(1088+(tempValue*pageSize));
            splRegs.codeCounter=myMemory[frameNum]*pageSize;
            while(splRegs.codeCounter<splRegs.codeLimit+splRegs.codeBase){
            int myInt=myMemory[splRegs.codeCounter];
/*************************************************************************************/
            execution_time=execution_time+2;                          //Calculating Execution Time
            waiting_time=waiting_time+2;                              //Calculating Waiting Time
            splRegs.codeCounter++;
            int exception_check=intruction(myInt);                        //Executing instruction specified by the opCODE
/*-----------------------------------Exceptional Checking----------------------------*/

            if(execptionHandling(exception_check,tempValue)!=0)break;


/*-----------------------------------------------------------------------------------------*/


            //HERE IS IT IS POSSIBLE THAT I WILL CHECK THE CONDITION IF THE MYINT IS EQUALS TO -1 I WILL PRINT THE ERROR OR MAKE THE MEMORY NULL
            }
            unsigned short int myVar=splRegs.codeCounter;
            myVar -=1;                                                //Talking codeCounter to previous instrction
            if(myMemory[myVar]!=243)                                  //Checking if the last instruction was not END
            {
                out<<"The Program Could not successfully terminate."<<endl;
                cout<<"The Program Could not Successfully Terminate."<<endl;
                //return 1;
            }
            deallocation(tempValue);                                //De-Allocation of Memory
            cout<<endl;
            /*-------------------------Printing Waiting and Execution Time-------------------*/
            myStr=int_to_hex(execution_time);
            efficientStore(myStr,(PCBcounter+65));
            myStr=int_to_hex(waiting_time-execution_time);
            efficientStore(myStr,(PCBcounter+67));
            cout<<"This is Execution Time "<<execution_time<<endl;
            cout<<"This is Waiting Time "<<waiting_time-execution_time<<endl;

            out<<"This is Execution Time "<<execution_time<<endl;
            out<<"This is Waiting Time "<<waiting_time-execution_time<<endl;


            }
            cout<<"The Process is not allocated to any frame."<<endl;
            execution_time=0;                                       //Setting counter to Zero for next counting
            /**********************************************************************************/
        }
        int counter=0;
        /*******************************Executing Round Robin Queue*************************************/

        execution_time=0;
        while(!RisEmpty())
        {

            PID=dequeue();
            PCBcounter=0;
            for(int j=0;j<8;j++)
            {
                if(myMemory[PCBcounter]!=PID)
                PCBcounter = ((j+1)*pageSize);
                else
                break;
                cout<<"PCB: \t"<<PCBcounter<<endl;
                out<<"PCB: \t"<<PCBcounter<<endl;

            }
            bool found=false;
            if(freePCB[(PCBcounter+1)/pageSize]==1 && myMemory[PCBcounter+99]==0)
                {
                    found=true;

                }
            if(found){


            cout<<"Starting Process of ID : \t"<<PID<<endl;
            out<<"Starting Process of ID : \t"<<PID<<endl;
            loadIt(PCBcounter);
  /*******************************Linear Adress Translation***************************/

            int tempValue=PCBcounter/128;                             // Temp Value indicate the Process
            int frameNum=(1088+(tempValue*pageSize));
            if(splRegs.codeCounter==0)
            splRegs.codeCounter=myMemory[frameNum]*pageSize;

            while(splRegs.codeCounter<splRegs.codeLimit+splRegs.codeBase && counter!=8){
            int myInt=myMemory[splRegs.codeCounter];
  /*************************************************************************************/

            splRegs.codeCounter++;
            execution_time=execution_time+2;                          //Calculating Execution Time
            waiting_time=waiting_time+2;                              //Calculating Waiting Time
            int exception_check=intruction(myInt);                        //Executing instruction specified by the opCODE
            /*-----------------------------------Exceptional Checking----------------------------*/
            if(execptionHandling(exception_check,tempValue)!=0)break;
            /*-----------------------------------------------------------------------------------------*/
            counter += 2;
            }

            //*****************Saving Execution and Running Time*****************///
            myStr=loading2Bytes((PCBcounter+66));
            int prev=StringToIntConverter2(myStr);
            prev += execution_time;
            myStr=int_to_hex(prev);
            efficientStore(myStr,(PCBcounter+66));
            myStr=int_to_hex(waiting_time-execution_time);
            efficientStore(myStr,(PCBcounter+68));                  //68 is the location of  Waiting Time
            cout<<"Execution Time: "<<prev<<endl;
            cout<<"Waiting Time: "<<waiting_time-prev<<endl;


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

            }
            else
            cout<<"Can't run this process no frame is allocated."<<endl;

        }
                                                             //Successful Excution
}











































bool memoryClass::executeProgOnlyOne(int proID)
    {
         /*******************************Executing Priorirty Queue*************************************/


            //priority=Premove();
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
        if(found==true){
            cout<<"Starting Process of ID: \t"<<proID<<endl;
            out<<"Starting Process of ID: \t"<<proID<<endl;
            loadIt(PCBcounter);
/*******************************Linear Adress Translation***************************/
            int tempValue=PCBcounter/128;
            cout<<"Temp Val"<<tempValue<<endl;

            int frameNum=(1088+(tempValue*pageSize));
            cout<<"Frame Num"<<frameNum<<endl;

            splRegs.codeCounter=myMemory[frameNum]*pageSize;
            cout<<splRegs.codeLimit<<endl;
            cout<<splRegs.codeBase<<endl;
            cout<<splRegs.codeCounter<<endl;


            while(splRegs.codeCounter<splRegs.codeLimit+splRegs.codeBase){
            cout<<"PC counter"<<splRegs.codeCounter<<endl;
            int myInt=myMemory[splRegs.codeCounter];
/*************************************************************************************/
            execution_time=execution_time+2;                          //Calculating Execution Time
            waiting_time=waiting_time+2;                              //Calculating Waiting Time
            splRegs.codeCounter++;
            int exception_check=intruction(myInt);                        //Executing instruction specified by the opCODE
/*-----------------------------------Exceptional Checking----------------------------*/

            if(execptionHandling(exception_check,tempValue)!=0)break;


/*-----------------------------------------------------------------------------------------*/


            //HERE IS IT IS POSSIBLE THAT I WILL CHECK THE CONDITION IF THE MYINT IS EQUALS TO -1 I WILL PRINT THE ERROR OR MAKE THE MEMORY NULL
            }
            unsigned short int myVar=splRegs.codeCounter;
            myVar -=1;                                                //Talking codeCounter to previous instrction
            if(myMemory[myVar]!=243)                                  //Checking if the last instruction was not END
            {
                out<<"The Program Could not successfully terminate."<<endl;
                cout<<"The Program Could not Successfully Terminate."<<endl;
                //return 1;
            }
            deallocation(tempValue);                                //De-Allocation of Memory
            cout<<endl;
           /* tempValue = (tempValue*pageSize) +4;
            loadGeneralRegInMemory();
            loadSpecialRegInMemory();
*/
            /*-------------------------Printing Waiting and Execution Time-------------------*/
            myStr=int_to_hex(execution_time);
            efficientStore(myStr,(PCBcounter+65));
            myStr=int_to_hex(waiting_time-execution_time);
            efficientStore(myStr,(PCBcounter+67));
            cout<<"This is Execution Time "<<execution_time<<endl;
            cout<<"This is Waiting Time "<<waiting_time-execution_time<<endl;

            out<<"This is Execution Time "<<execution_time<<endl;
            out<<"This is Waiting Time "<<waiting_time-execution_time<<endl;



            execution_time=0;                                       //Setting counter to Zero for next counting
            /**********************************************************************************/
        }

        /*******************************Executing Round Robin Queue*************************************/

        return found;
                                                             //Successful Excution
}






























/*******************************************************************************************************************/
/********************************************Instruction Funtion***************************************************/

int memoryClass::intruction(int myInt)                               //Function to execute instrunction defined by the opCode
{

    short int* secondOperand,*firstOperand;
    short int myImmediateValue;
    char * immOpStr;
    string myStr;
    string operationCode;
    operationCode=int_to_hex2(myInt);
    if(operationCode[0]=='1')                                         //Checking for approperiate instruction type
    {
            myInt=myMemory[splRegs.codeCounter];                      //Reading Register Code
            splRegs.codeCounter++;                                    //incrementing counter
            firstOperand=regs.selectRegisters(myInt);                 //Selecting Register on the basis of code
            myInt=myMemory[splRegs.codeCounter];                      //Reading Register Code
            splRegs.codeCounter++;                                    //incrementing counter
            secondOperand=regs.selectRegisters(myInt);                //Selecting Register on the basis of code

        switch(operationCode[1])                                      //Checking for approperiate instruction to execute
        {

            case '6':
            cout<<"Move Instructon"<<endl;
            out<<"Move Instructon"<<endl;
            move(firstOperand,secondOperand);                         //Performing mov Operation
            break;
            case '7':
            cout<<"Add Instructon"<<endl;
            out<<"Add Instructon"<<endl;
            add(firstOperand,secondOperand);                            //Performing add Operation
            break;
            case '8':
            cout<<"Sub Instructon"<<endl;
            out<<"Sub Instructon"<<endl;
            sub(firstOperand,secondOperand);                            //Performing sub Operation
            break;

            case '9':
            cout<<"Mul Instructon"<<endl;
            out<<"Mul Instructon"<<endl;
            mul(firstOperand,secondOperand);                            //Performing mul Operation
            break;
            case 'a':
            cout<<"Div Instructon"<<endl;
            out<<"Div Instructon"<<endl;
            return div(firstOperand,secondOperand);                            //Performing div Operation
            break;
            case 'b':
            cout<<"AND Instructon"<<endl;
            out<<"AND Instructon"<<endl;
            And(firstOperand,secondOperand);                            //Performing and Operation
            break;
            case 'c':
            cout<<"OR Instructon"<<endl;
            out<<"OR Instructon"<<endl;
            Or(firstOperand,secondOperand);                             //Performing or Operation
            break;
            default:
            cout<<"No Instruction For This Code."<<endl;
            out<<"No Instruction For This Code."<<endl;
            return 1;
            break;

        }

    }

    else if(operationCode[0]=='3')                                      //Checking for approperiate instruction type
    {
            cout<<"Register Imm Instruction"<<endl;
            out<<"Register Imm Instruction"<<endl;
            myInt=myMemory[splRegs.codeCounter];                        //Reading Register Code
            splRegs.codeCounter++;                                      //incrementing counter
            firstOperand=regs.selectRegisters(myInt);                   //Selecting Register on the basis of code
            myStr=loading2Bytes(splRegs.codeCounter);
            myImmediateValue=StringToIntConverter2(myStr);splRegs.codeCounter += 2;

        switch(operationCode[1])                                        //Checking for approperiate instruction to execute
        {
            case '0':
            cout<<"MOVI Instruction."<<endl;
            out<<"MOVI Instruction."<<endl;
            moveI(firstOperand,myImmediateValue);                       //Moving immediate value
            break;
            case '1':
            cout<<"ADDl Instruction."<<endl;
            out<<"ADDl Instruction."<<endl;
            addI(firstOperand,myImmediateValue);                        //Performing add imm Operation
            break;
            case '2':
            cout<<"Subl Instruction."<<endl;
            out<<"Subl Instruction."<<endl;
            subI(firstOperand,myImmediateValue);                        //Performing sub imm Operation
            break;
            case '3':
            cout<<"MulI Instruction."<<endl;
            out<<"MulI Instruction."<<endl;
            mulI(firstOperand,myImmediateValue);                        //Performing mul imm Operation
            break;
            case '4':
            cout<<"DivI Instruction."<<endl;
            out<<"DivI Instruction."<<endl;
            return divI(firstOperand,myImmediateValue);                     //Performing div imm Operation
            break;
            case '5':
            cout<<"AndI Instruction."<<endl;
            out<<"AndI Instruction."<<endl;
            andI(firstOperand,myImmediateValue);                        //Performing and imm Operation
            break;
            case '6':
            cout<<"Orl Instruction."<<endl;
            out<<"Orl Instruction."<<endl;
            OrI(firstOperand,myImmediateValue);                         //Performing or imm Operation
            break;
            case '7':
            cout<<"BZ Instruction."<<endl;
            out<<"BZ Instruction."<<endl;
            return BZ(firstOperand,myImmediateValue);                         //Performing branch zero Operation
            break;
            case '8':
            cout<<"BNZ Instruction."<<endl;
            out<<"BNZ Instruction."<<endl;
            return BNZ(firstOperand,myImmediateValue);                         //Performing branch if not zero Operation
            break;
            case '9':
            cout<<"BC Instruction."<<endl;
            out<<"BC Instruction."<<endl;
            return BC(firstOperand,myImmediateValue);                          //Performing branch if carry Operation
            break;
            case 'a':
            cout<<"BS Instruction."<<endl;
            out<<"BS Instruction."<<endl;
            return BS(firstOperand,myImmediateValue);                          //Performing B IF SIGN Operation
            break;
            case 'b':
            cout<<"JMP Instruction."<<endl;
            out<<"JMP Instruction."<<endl;
            return jmp(myImmediateValue);                                      //Performing JMP Operation
            break;
            case 'c':
            cout<<"CALL Instruction."<<endl;
            out<<"CALL Instruction."<<endl;

            return call(myImmediateValue,myMemory);                            //Performing CALL Operation
            break;


        }


    }
    else if(operationCode[0]=='5')                                      //Checking for approperiate instruction type
    {
        cout<<"Register Memory Instruction"<<endl;
        out<<"Register Memory Instruction"<<endl;
        myInt=myMemory[splRegs.codeCounter];                            //Reading Register Code
        splRegs.codeCounter++;                                          //incrementing counter
        cout<<"Register To Modify: "<<myInt<<endl;
        out<<"Register To Modify: "<<myInt<<endl;
        firstOperand=regs.selectRegisters(myInt);                       //Selecting Register on the basis of code
        myStr=loading2Bytes(splRegs.codeCounter);splRegs.codeCounter += 2;
        myImmediateValue=StringToIntConverter2(myStr);

        if(myImmediateValue<0 || myImmediateValue>=splRegs.dataLimit)//Checking if it is under the limit
        {
        out<<"Trying to access outside adress space."<<endl;            //Handling exception
        return 2;
        }
        switch(operationCode[1])                                        //Checking for approperiate instruction to execute
        {

            case '1':

            cout<<"Load Word Into Register."<<endl;
            out<<"Load Word Into Register."<<endl;
            loadW(firstOperand,(myImmediateValue+splRegs.dataBase));    //Performing Operation
            cout<<"Content Has been loaded to the register."<<endl;
            out<<"Content Has been loaded to the register."<<endl;
            break;

            case '2':

            cout<<"Read Word From Register To Memory."<<endl;
            out<<"Read Word From Register To Memory."<<endl;
            storeW(firstOperand,(myImmediateValue+splRegs.dataBase));   //Performing Operation
            cout<<"Content Has been writen to the memory."<<endl;
            out<<"Content Has been writen to the memory."<<endl;
            break;
        }



    }
    else if(operationCode[0]=='7')                                      //Checking for approperiate instruction type
    {
            cout<<"Single Operand Instruction"<<endl;

            out<<"Single Operand Instruction"<<endl;
            myInt=myMemory[splRegs.codeCounter];                    //Reading Register Code
            splRegs.codeCounter++;                                  //incrementing counter
            firstOperand=regs.selectRegisters(myInt);               //Selecting Register on the basis of code
            if(splRegs.stackCounter==0)
            {
                splRegs.stackCounter=splRegs.stackBase;
            }




        switch(operationCode[1])                                    //Checking for approperiate instruction to execute
        {
            case '1':
            cout<<"SHL instruction."<<endl<<endl;
            out<<"SHL instruction."<<endl<<endl;
            shl(firstOperand);                                      //Performing SHL Operation
            break;
            case '2':
            cout<<"SHR instruction."<<endl<<endl;
            out<<"SHR instruction."<<endl<<endl;
            shr(firstOperand);                                      //Performing SHR Operation
            break;

            case '3':
            cout<<"ROL instruction."<<endl<<endl;
            out<<"ROL instruction."<<endl<<endl;
            rol(firstOperand);                                       //Performing ROL Operation
            break;
            case '4':
            cout<<"ROR instruction."<<endl<<endl;
            out<<"ROR instruction."<<endl<<endl;
            ror(firstOperand);                                      //Performing ROR Operation
            break;
            case '5':
            cout<<"Increament instruction"<<endl<<endl;
            out<<"Increament instruction"<<endl<<endl;
            inc(firstOperand);                                      //Performing inc Operation
            break;
            case '6':
            cout<<"Decreament instruction"<<endl<<endl;
            out<<"Decreament instruction"<<endl<<endl;
            dec(firstOperand);                                      //Performing dec Operation
            break;
            case '7':
            cout<<"Push instruction"<<endl<<endl;
            out<<"Push instruction"<<endl<<endl;

            if((splRegs.stackBase-splRegs.stackCounter)<splRegs.stackLimit)//Performing Operation
            Push(firstOperand);

            else
            {
            out<<"The Stack is Full"<<endl;
            return 3;
            }
            printStack();                                           //Printing content of stack
            break;
            case '8':
            cout<<"Pop instruction"<<endl<<endl;
            out<<"Pop instruction"<<endl<<endl;
            if((splRegs.stackBase-splRegs.stackCounter)!=0)
            Pop(firstOperand);                                      //Performing Operation
            else{
            out<<"Stack is already Empty."<<endl;                   //The stack was empty
            return 4;
                }
            printStack();
            break;
        }
    }
    else if(operationCode[0]=='f')                                  //Checking for approperiate instruction type
    {
        cout<<"No operand Instruction"<<endl;
        out<<"No operand Instruction"<<endl;
        static int error;
        switch(operationCode[1])                                    //Checking for approperiate instruction to execute
        {
            case '1':
            cout<<"RET instruction."<<endl<<endl;
            out<<"RET instruction."<<endl<<endl;
            if(splRegs.stackCounter!=splRegs.stackBase || splRegs.stackCounter!=0)
            splRegs.codeCounter=myMemory[splRegs.stackCounter++];
            else{
            out<<"Stack is already Empty."<<endl;return 5;
            }
            break;

            case '2':                                               //Performing Operation
            cout<<"NOOP Instruction."<<endl<<endl;                  //Do nothing just incrementing coounter
            out<<"NOOP Instruction."<<endl<<endl;                  //Do nothing just incrementing coounter
            error++;
            out<<error<<endl;
            out<<splRegs.codeCounter<<endl;
            break;
            case '3':                                               //Performing Operation
            cout<<"END Instruction."<<endl<<endl;                   //Following and instruction
            cout<<"Program Successfully Terminated."<<endl;
            out<<"END Instruction."<<endl<<endl;                   //Following and instruction
            out<<"Program Successfully Terminated."<<endl;
            cout<<"Terminating Process"<<endl;
            out<<"Terminating Process"<<endl;
            return 9;

            break;

            default:
            out<<"No Instruction Found For This Code."<<endl;
            out<<operationCode<<endl;
            out<<splRegs.codeLimit<<endl;
        }
    }
    else
    {
        out<<"No Valid Instruction"<<endl;
        cout<<"No Valid instruction "<<endl;

    }
    return 0;




}


/*******************************************Instruction Set*******************************************/

            void memoryClass::Push(short int *firstOperand)
            {
            goodVal=int_to_hex(*firstOperand);
            splRegs.stackCounter--;
            splRegs.stackCounter--;
            efficientStore(goodVal,splRegs.stackCounter);
            }
            void memoryClass::Pop(short int *firstOperand)
            {
            goodVal=loading2Bytes(splRegs.stackCounter);
            splRegs.stackCounter += 2;
            *firstOperand =StringToIntConverter2(goodVal);
            cout<<"Copied Val: "<<*firstOperand<<endl;
            out<<"Copied Val: "<<*firstOperand<<endl;
            }

            void memoryClass::move(short int * firstOperand, short int * secondOperand)//Move instruction
             {
                  *firstOperand=*secondOperand;
                  splRegs.setS(*secondOperand);
                  splRegs.setOF(*secondOperand);
            }
             void  memoryClass::add (short int * firstOperand, short int * secondOperand)//Add instruction
             {
                  *firstOperand +=*secondOperand;
                  /*cout<<splRegs.codeCounter<<endl;
                  out<<splRegs.codeCounter<<endl;*/
                  splRegs.setS(*firstOperand);
                  splRegs.setOF(*firstOperand);


            }

             void  memoryClass::sub(short int * firstOperand, short int * secondOperand)//Sub Instruction
             {
                  *firstOperand -=*secondOperand;
                  splRegs.setS(*firstOperand);
                  splRegs.setOF(*firstOperand);


            }

             void  memoryClass::mul(short int * firstOperand, short int * secondOperand)//Mul Instruction
             {
                  *firstOperand *=*secondOperand;
                  splRegs.setS(*firstOperand);
                  splRegs.setOF(*firstOperand);


            }

             int memoryClass::div(short int * firstOperand, short int * secondOperand)//Div Instruction
             {
                 if(*secondOperand==0)
                 {
                    out<<"Divide By Zero";
                    return 6;
                 }
                 else
                 {
                     *firstOperand /=*secondOperand;
                     splRegs.setS(*firstOperand);
                     splRegs.setOF(*firstOperand);
                     return 0;
                 }


            }

             void memoryClass::And(short int * firstOperand, short int * secondOperand)//AnD Instruction
             {
                  *firstOperand =*firstOperand&*secondOperand;
                  splRegs.setS(*firstOperand);
                  splRegs.setOF(*firstOperand);


            }

             void memoryClass::Or(short int * firstOperand, short int * secondOperand)//OR Instruction
             {
                  *firstOperand =*firstOperand|*secondOperand;
                  splRegs.setS(*firstOperand);
                  splRegs.setOF(*firstOperand);
            }

            void memoryClass::moveI(short int * firstOperand,short int secondOperand)//MOVI Instruction
            {

                 *firstOperand=secondOperand;
                 splRegs.setS(secondOperand);
                 splRegs.setOF(secondOperand);
            }
            void memoryClass::addI(short int * firstOperand,short int secondOperand)//ADDI Instruction
            {

                 *firstOperand +=secondOperand;
                 splRegs.setS(*firstOperand);
                 splRegs.setOF(*firstOperand);

            }
            void memoryClass::subI(short int * firstOperand,short int secondOperand)//SubI Instruction
            {

                 *firstOperand -=secondOperand;
                 splRegs.setS(*firstOperand);
                 splRegs.setOF(*firstOperand);

            }
            void memoryClass::mulI(short int * firstOperand,short int secondOperand)//MULI Instruction
            {

                 *firstOperand *=secondOperand;
                 splRegs.setS(*firstOperand);
                 splRegs.setOF(*firstOperand);

            }

            int memoryClass::divI(short int * firstOperand,short int secondOperand)//DIVI Instruction
            {
                 if(secondOperand==0)
                 {
                     out<<"Divide By Zero";
                     return 6;
                 }
                 else
                 {
                     *firstOperand /=secondOperand;
                     splRegs.setS(*firstOperand);
                     splRegs.setOF(*firstOperand);
                     return 0;
                 }
            }

            void memoryClass::andI(short int * firstOperand,short int secondOperand)//ANDI Instruction
            {

                 *firstOperand &=secondOperand;
                 splRegs.setS(*firstOperand);
                 splRegs.setOF(*firstOperand);

            }

            void memoryClass::OrI(short int * firstOperand,short int secondOperand)//ORI Instruction
            {

                 *firstOperand |=secondOperand;
                 splRegs.setS(*firstOperand);
                 splRegs.setOF(*firstOperand);

            }
            int memoryClass::BZ(short int * firstOperand,short int secondOperand)//JUMP IF ZERO Instruction
            {
                 if(splRegs.getZeroFlag()==1)
                 {
                    if((secondOperand+splRegs.codeBase)<=(splRegs.codeLimit + splRegs.codeBase) && (secondOperand+splRegs.codeBase)>=( splRegs.codeBase))
                    {
                    splRegs.codeCounter=secondOperand+splRegs.codeBase;
                    return 0;
                    }
                    else
                    {
                        out<<"Trying to jump out of memory limit."<<endl;
                        return 1;
                    }
                 }

            }
            int memoryClass::BNZ(short int * firstOperand,short int secondOperand)////JUMP IF NOT ZERO Instruction
            {
            if(splRegs.getZeroFlag()!=1)
                 {
                    if((secondOperand+splRegs.codeBase)<=(splRegs.codeLimit + splRegs.codeBase) && (secondOperand+splRegs.codeBase)>=( splRegs.codeBase))
                    {
                    splRegs.codeCounter=secondOperand+splRegs.codeBase;
                    return 0;
                    }

                    else
                    {
                        out<<"Trying to jump out of memory limit."<<endl;
                        return 1;
                    }
                 }
            }

            int memoryClass::BC(short int * firstOperand,short int secondOperand)//JUMP IF CARRY Instruction
            {

                 if(splRegs.getCarryFlag())
                 {
                    if((secondOperand+splRegs.codeBase)<=(splRegs.codeLimit + splRegs.codeBase) && (secondOperand+splRegs.codeBase)>=( splRegs.codeBase))
                    {
                    splRegs.codeCounter=secondOperand+splRegs.codeBase;
                    return 0;
                    }
                    else
                    {
                        out<<"Trying to jump out of memory limit."<<endl;
                        return 1;
                    }
                 }

            }
            int memoryClass::BS(short int * firstOperand,short int secondOperand)//JUMP IF SIGN Instruction
            {
                 if(splRegs.getSignFlag())
                 {
                    if((secondOperand+splRegs.codeBase)<=(splRegs.codeLimit + splRegs.codeBase) && (secondOperand+splRegs.codeBase)>=( splRegs.codeBase))
                    {
                    splRegs.codeCounter=secondOperand+splRegs.codeBase;
                    return 0;
                    }
                    else
                    {
                        out<<"Trying to jump out of memory limit."<<endl;
                        return 1;
                    }
                 }


            }
            int memoryClass::jmp(short int secondOperand)//JUMP Instruction
            {
                    if(secondOperand>0 && secondOperand<=splRegs.codeLimit)
                    {
                    splRegs.codeCounter=secondOperand+splRegs.codeBase;
                    return 0;
                    }
                    else
                    {
                        out<<"Trying to jump out of memory limit."<<endl;
                        splRegs.codeCounter=splRegs.codeLimit+splRegs.codeBase;
                        return 1;
                    }
            }
            int memoryClass::call(short int secondOperand,unsigned char * myM)//JUMP but save the PC to stack
            {
                    if((secondOperand+splRegs.codeBase)<=(splRegs.codeLimit + splRegs.codeBase) && (secondOperand+splRegs.codeBase)>=( splRegs.codeBase))
                    {
                        if(splRegs.stackCounter<(splRegs.stackBase+64)){
                        myM[splRegs.stackCounter--]=splRegs.codeCounter;
                        return 0;}
                        else{
                        return 3;
                        }

                        splRegs.codeCounter=secondOperand+splRegs.codeBase;

                    }
                    else
                    {
                        out<<"Trying to jump out of memory limit."<<endl;
                        return 1;
                    }
            }

            void memoryClass::loadW(short int *firstOperand,short int myImmediateValue)//Load to memeory
            {
                  string myStr=loading2Bytes(myImmediateValue);
                 *firstOperand =StringToIntConverter2(myStr);

            }
            void memoryClass::storeW(short int *firstOperand,short int myImmediateValue)//Read from memory
            {
                 string myStr=int_to_hex(*firstOperand);
                 efficientStore(myStr,myImmediateValue);


            }
            void memoryClass::shl(short int * firstOperand)//Shifting to left
            {
                *firstOperand = (*firstOperand << 1);
                splRegs.setS(*firstOperand);
                splRegs.setOF(*firstOperand);

            }
            void memoryClass::shr(short int * firstOperand)//Shifting to right
            {
                *firstOperand = (*firstOperand >> 1);
                splRegs.setS(*firstOperand);
                splRegs.setOF(*firstOperand);
            }
            void memoryClass::ror(short int * firstOperand)//Rotating Left
            {

                *firstOperand=cirR(*firstOperand);
                splRegs.setS(*firstOperand);
                splRegs.setOF(*firstOperand);
            }

            void memoryClass::rol(short int * firstOperand)//Rotating Right
            {
                *firstOperand=cirL(*firstOperand);
                splRegs.setS(*firstOperand);
                splRegs.setOF(*firstOperand);

            }
            void memoryClass::inc (short int *firstOperand)//Incrementing
            {
                *firstOperand += 1;
                splRegs.setS(*firstOperand);
            }
            void memoryClass::dec (short int *firstOperand)//Decrementing
            {
                *firstOperand -= 1;
                splRegs.setS(*firstOperand);
            }



            int memoryClass::execptionHandling(int exeception_check , int tempValue){
            if(exeception_check==1)
            {
            cout<<"Trying Jump Out of memory of memory."<<endl;
            PrintPCB(tempValue);
            return 1;
            }
            else if(exeception_check==2){
            cout<<"Trying to access Outside its Adress Space of DATA"<<endl;
            PrintPCB(tempValue);
            return 2;}
            else if(exeception_check==3){
            cout<<"The Stack is Full"<<endl;
            PrintPCB(tempValue);
            return 3;}
            else if(exeception_check==4){
            cout<<"Stack is Empty "<<endl;
            PrintPCB(tempValue);
            return 4;}
            else if(exeception_check==5){
            cout<<"Divide by zero exception"<<endl;
            PrintPCB(tempValue);
            return 5;}
            else if(exeception_check==0){
            printAllRegs();
            return 0;
            }
    }


             int memoryClass::execptionHandling2(int exeception_check , int tempValue){
            BITMAP * fakeDis=create_bitmap(600,500);
            clear_to_color(fakeDis, makecol(170,231,216));
            cout<<"Temp V"<<tempValue<<endl;
            if(exeception_check==1)
            {
            textout_ex(fakeDis,font,"Trying Jump Out of memory of memory.",0,0,makecol(255,0,0),-1);
            blit(fakeDis,screen,0,0,200,50,600,500);
            readkey();
            clear_to_color(fakeDis, makecol(170,231,216));
            printPCB(myMemory[tempValue],fakeDis);
            //blit(fakeDis,screen,0,0,200,50,600,500);
            return 1;
            }
            else if(exeception_check==2){
            textout_ex(fakeDis,font,"Trying to access Outside its Adress Space of DATA.",0,0,makecol(255,0,0),-1);
            blit(fakeDis,screen,0,0,200,50,600,500);
            readkey();
            clear_to_color(fakeDis, makecol(170,231,216));
            printPCB(myMemory[tempValue],fakeDis);
            //blit(fakeDis,screen,0,0,200,50,600,500);
            return 2;}
            else if(exeception_check==3){
            textout_ex(fakeDis,font,"The Stack is Full.",0,0,makecol(255,0,0),-1);
            blit(fakeDis,screen,0,0,200,50,600,500);
            readkey();
            clear_to_color(fakeDis, makecol(170,231,216));
            printPCB(myMemory[tempValue],fakeDis);
            return 3;}
            else if(exeception_check==4){
            textout_ex(fakeDis,font,"Stack is Empty.",0,0,makecol(255,0,0),-1);
            blit(fakeDis,screen,0,0,200,50,600,500);
            readkey();
            clear_to_color(fakeDis, makecol(170,231,216));
            printPCB(myMemory[tempValue],fakeDis);
            return 4;}
            else if(exeception_check==5){
            textout_ex(fakeDis,font,"Divide by zero exception.",0,0,makecol(255,0,0),-1);
            blit(fakeDis,screen,0,0,200,50,600,500);
            readkey();
            clear_to_color(fakeDis, makecol(170,231,216));
            printPCB(myMemory[tempValue],fakeDis);
            return 5;}
            else if(exeception_check==9){
            textout_ex(fakeDis,font,"END-Instruction.",0,0,makecol(255,0,0),-1);
            blit(fakeDis,screen,0,0,200,50,600,500);
            readkey();
            clear_to_color(fakeDis, makecol(170,231,216));
            printPCB(myMemory[tempValue],fakeDis);
            return 9;
            }
            else if(exeception_check==0){
            printAllRegs();
            return 0;
            }
    }

