#include "MTickTimeAd.h"
//#include "MWinSystem.h"
#include "DefSystem.h"
/*****************/

#define DEBUG   1

char model = ' ';
int iBlackWhite = eStateFirst;                //State of Black-White Chart
void ThreeStateControl(int iState);
//atk
int iMainProcess    = eMain_ORG_All;
int iMainProcess_S9 = eMain_ORG_All_S9//Main Process Of Main
MTickTimeAd m_timeMainProcess;                 //Timer of Main Process
bool bIsRunStep[NUM_STEP] = {false};

//atk
int iInputProcess = WAIT_INPUT_PRESS;           //Main Process Of InputScan
int iCurInputPress = 0;                         //Current Input Pressed
MTickTimeAd m_timeInputProcess;                 //Timer
bool bStatusInput[NUM_INPUT] = {false};         //Status of Input
/*****************/

//////////////////////////////////Function////////////////////////////////////////////////////////////////
void Init();
void SetOutputOn(int iOutPut);
void SetOutputOff(int iOutPut);
bool IsOnInput(int iInPut);

//void LoopButton();
void LoopControl();
void LoopControl_S9();
ESerial m_eSerialStep = SERIAL_DONOTHING;


//MTickTimeAd m_timeprocess, m_timerSerial;


void InitPinMode();

///////////////////////////////////////////Main///////////////////////////////////////////////////////////
//Init
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

#ifdef DEBUG
  Serial.println("Hello SEV");
#endif

  InitPinMode();

  for (int i = 0; i < NUM_INPUT; i++)
    bStatusInput[i] = IsOnInput(i * 2 + IN_BUTTON_START);

  ThreeStateControl(eStateFirst);
}


//Main
void loop() {
  Serial.println(model);
  delay(100);

  // put your main code here, to run repeatedly:
  for (int i = 0; i < NUM_INPUT; i++)
    bStatusInput[i] = IsOnInput(i * 2 + IN_BUTTON_START);

  ScanInput();
  if (model == '9')
  {
   // Serial.println("s9");
    LoopControl_S9();
  }
  else
  {
    LoopControl();
  }
  
}

//Control Black-White Chart
void ThreeStateControl(int iState)
{
  switch (iState)
  {
    //state first
    case eStateFirst:
      {
        //
        if (iBlackWhite == eStateThird)
        {
          SetOutputOn(OUT_BLACK_WHITE_REAR_OUT);
          delay(TIME_CYLINDER);
          SetOutputOff(OUT_BLACK_WHITE_REAR_OUT);
          delay(TIME_CYLINDER);

          SetOutputOn(OUT_BLACK_WHITE_REAR_OUT);
          delay(TIME_CYLINDER);
          SetOutputOff(OUT_BLACK_WHITE_REAR_OUT);
        }
        else if (iBlackWhite == eStateSecond)
        {
          SetOutputOn(OUT_BLACK_WHITE_REAR_OUT);
          delay(TIME_CYLINDER);
          SetOutputOff(OUT_BLACK_WHITE_REAR_OUT);
        }
        else if (iBlackWhite == eStateFirst)
        {}//nop

        iBlackWhite = eStateFirst;
      }
      break;

    //state second
    case eStateSecond:
      {

        if (iBlackWhite == eStateThird)
        {
          SetOutputOn(OUT_BLACK_WHITE_REAR_OUT);
          delay(TIME_CYLINDER);
          SetOutputOff(OUT_BLACK_WHITE_REAR_OUT);

        }
        else if (iBlackWhite == eStateSecond) //nop
        {
        }
        else if (iBlackWhite == eStateFirst)
        {
          SetOutputOn(OUT_BLACK_WHITE_REAR_IN);
          delay(TIME_CYLINDER);
          SetOutputOff(OUT_BLACK_WHITE_REAR_IN);
        }

        iBlackWhite = eStateSecond;
      }
      break;

    //state eStateThird
    case eStateThird:
      {

        if (iBlackWhite == eStateThird)//nop
        {
        }
        else if (iBlackWhite == eStateSecond) //nop
        {
          SetOutputOn(OUT_BLACK_WHITE_REAR_IN);
          delay(TIME_CYLINDER);
          SetOutputOff(OUT_BLACK_WHITE_REAR_IN);
        }
        else if (iBlackWhite == eStateFirst)
        {
          SetOutputOn(OUT_BLACK_WHITE_REAR_IN);
          delay(TIME_CYLINDER);
          SetOutputOff(OUT_BLACK_WHITE_REAR_IN);

          delay(TIME_CYLINDER);

          SetOutputOn(OUT_BLACK_WHITE_REAR_IN);
          delay(TIME_CYLINDER);
          SetOutputOff(OUT_BLACK_WHITE_REAR_IN);

        }

        iBlackWhite = eStateThird;
      }
      break;

    default: break;
  }
}

///////////////////////In Out///////////////////////////////////////////////////
void InitPinMode()
{

  //Input
  pinMode(IN_BUTTON_START, INPUT_PULLUP);
  pinMode(IN_BUTTON_NEXT, INPUT_PULLUP);
  pinMode(IN_BUTTON_BACK, INPUT_PULLUP);
  pinMode(IN_BUTTON_RESET, INPUT_PULLUP);


  //Output
  pinMode(OUT_LED_1, OUTPUT);
  pinMode(OUT_LED_2, OUTPUT);
  pinMode(OUT_LED_3, OUTPUT);
  pinMode(OUT_LED_4, OUTPUT);
  pinMode(OUT_CHART_VISION_REAR, OUTPUT);
  pinMode(OUT_CHART_WHITE_FRONT, OUTPUT);
  pinMode(OUT_BLACK_WHITE_REAR_IN, OUTPUT);
  pinMode(OUT_BLACK_WHITE_REAR_OUT, OUTPUT);
  pinMode(OUT_USB_L, OUTPUT);
  pinMode(OUT_USB_R, OUTPUT);
  pinMode(OUT_CHART_BLACK_FRONT_L, OUTPUT);
  pinMode(OUT_CHART_BLACK_FRONT_R, OUTPUT);

}

void SetOutputOn(int iOutPut)
{
  digitalWrite(iOutPut, HIGH);
}

void SetOutputOff(int iOutPut)
{
  digitalWrite(iOutPut, LOW);
}
bool IsOnInput(int iInPut)
{
  return !digitalRead(iInPut);
}

////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////


////atk
//int iInputProcess = WAIT_INPUT_PRESS;           //Main Process Of InputScan
//int iCurInputPress = 0;                         //Current Input Pressed
//MTickTimeAd m_timeInputProcess;                 //Timer
//bool bStatusInput[NUM_INPUT] = {false};         //Status of Input
/*********************Scan Input*********************/
void ScanInput()
{
  switch (iInputProcess)
  {
    //Wait input press
    case WAIT_INPUT_PRESS:
      {

#ifdef DEBUG
        Serial.print('^');
#endif
        for (int i = 0; i < NUM_INPUT; i++)
        {
          //bool b = IsOnInput(i);
          if (bStatusInput[i])
          {
            iCurInputPress = i;
            m_timeInputProcess.StartTimer();
            iInputProcess = WAIT_INPUT_DEBOUNCE;
            //Serial.print('@');
            break;
          }
        }
      }
      break;

    //Wait debounce
    case WAIT_INPUT_DEBOUNCE:
      {
#ifdef DEBUG
        Serial.print('#');
#endif

        if (m_timeInputProcess.LessThan(TIME_DEBOUNCE))
          break;
        if (bStatusInput[iCurInputPress])
        {
          iInputProcess = WAIT_INPUT_RELEASE;
          break;
        }
        else
        {
          iInputProcess = WAIT_INPUT_PRESS;
          break;
        }

      }
      break;

    //Wait Release
    case WAIT_INPUT_RELEASE:
      {
#ifdef DEBUG
        Serial.print('$');
#endif

        if (bStatusInput[iCurInputPress])
        {
          break;
        }
        else  //wait until release
        {
          switch (iCurInputPress) //Send to PC
          {
            case IN_START:  Serial.print('R');
              break;

            case IN_NEXT:

#ifdef DEBUG
              Serial.print('N');
#endif
              inc_process();
              break;

            case IN_BACK:

#ifdef DEBUG
              Serial.print('B');
#endif
              dec_process();
              break;

            case IN_RESET:
#ifdef DEBUG
              Serial.print('S');
#endif

              if (bIsRunStep[eMain_ORG_All])
                bIsRunStep[eMain_ORG_All] = false;
              iMainProcess = eMain_ORG_All;
              
              if (bIsRunStep[eMain_ORG_All_S9])
                bIsRunStep[eMain_ORG_All_S9] = false;
              iMainProcess_S9 = eMain_ORG_All_S9;

              break;

            default:
              break;
          }
          m_timeInputProcess.StartTimer();
          iInputProcess = WAIT_INPUT_FINISH;
          break;
        }
      }
      break;


    //Wait finish
    case WAIT_INPUT_FINISH:
      {
#ifdef DEBUG
        Serial.print('%');
#endif

        if (m_timeInputProcess.LessThan(TIME_DEBOUNCE))
          break;
        iInputProcess = WAIT_INPUT_PRESS;
      }
      break;

  }

}



////atk
//int iMainProcess    = eMain_ORG_All;           //Main Process Of Main
//MTickTimeAd m_timeMainProcess;                 //Timer
//bool bIsRunStep[NUM_STEP] = {false};

void inc_process()
{
  if (iMainProcess <  eMain_Do_nothing ||  iMainProcess >= eMain_Front_Vision)
    return;

#ifdef DEBUG
  Serial.print('>');
  Serial.print(iMainProcess);
#endif

  if (bIsRunStep[iMainProcess + 1])
    bIsRunStep[iMainProcess + 1] = false;
  iMainProcess ++;

#ifdef DEBUG
  Serial.print(iMainProcess);
  Serial.print('<');
#endif

}
void inc_process_S9()
{
  if (iMainProcess_S9 <  eMain_Do_nothing ||  iMainProcess_S9 >= eMain_Front_Vision_S9)
    return;

#ifdef DEBUG
  Serial.print('>');
  Serial.print(iMainProcess_S9);
#endif

  if (bIsRunStep[iMainProcess_S9 + 1])
    bIsRunStep[iMainProcess_S9 + 1] = false;
  iMainProcess_S9 ++;

#ifdef DEBUG
  Serial.print(iMainProcess_S9);
  Serial.print('<');
#endif

}


void dec_process()
{
  if (iMainProcess <= eMain_Do_nothing ||  iMainProcess > eMain_Front_Vision)
    return;
#ifdef DEBUG
  Serial.print('[');
  Serial.print(iMainProcess);
#endif

  if (bIsRunStep[iMainProcess - 1])
    bIsRunStep[iMainProcess - 1] = false;
  iMainProcess --;

#ifdef DEBUG
  Serial.print(iMainProcess);
  Serial.print(']');
#endif
}
void dec_process_S9()
{
  if (iMainProcess_S9 <= eMain_Do_nothing ||  iMainProcess_S9 > eMain_Front_Vision_S9)
    return;
#ifdef DEBUG
  Serial.print('[');
  Serial.print(iMainProcess_S9);
#endif

  if (bIsRunStep[iMainProcess_S9 - 1])
    bIsRunStep[iMainProcess_S9 - 1] = false;
  iMainProcess_S9 --;

#ifdef DEBUG
  Serial.print(iMainProcess_S9);
  Serial.print(']');
#endif
}




void LoopControl()
{
  switch (iMainProcess)
  {
    //Do eMain_ORG_Rear
    case eMain_ORG_Rear:
      {

#ifdef DEBUG
        Serial.println("100");
#endif

      }
      break;


    //Do eMain_ORG_Front
    case eMain_ORG_Front:
      {
#ifdef DEBUG
        Serial.println("101");
#endif
      }
      break;

    //Do eMain_ORG_All
    case eMain_ORG_All:
      {
        if (!bIsRunStep[iMainProcess])
        {
          SetOutputOff(OUT_CHART_WHITE_FRONT);
          ThreeStateControl(eStateFirst);
          SetOutputOff(OUT_CHART_BLACK_FRONT_L);
          SetOutputOff(OUT_CHART_BLACK_FRONT_R);

          SetOutputOff(OUT_LED_1);
          SetOutputOff(OUT_LED_2);
          SetOutputOff(OUT_LED_3);
          bIsRunStep[iMainProcess] = true;
         // bIsRunStep[iMainProcess_S9] = true;
        }
#ifdef DEBUG
        Serial.println("102");
#endif
      }
      break;


    //Do nothing => Scan
    case eMain_Do_nothing:
      {
#ifdef DEBUG
        Serial.print('*');
#endif
      }
      break;


    //Do eMain_USB_In
    case eMain_USB_In:
      {
        if (!bIsRunStep[iMainProcess])
        {
#ifdef DEBUG
          Serial.print('1');
#endif
          SetOutputOn(OUT_USB_L);
          SetOutputOn(OUT_USB_R);

          bIsRunStep[iMainProcess] = true;
        }
      }
      break;


    //Do eMain_USB_Out
    case eMain_USB_Out:
      {
        if (!bIsRunStep[iMainProcess])
        {
#ifdef DEBUG
          Serial.print('2');
#endif
          SetOutputOff(OUT_USB_L);
          SetOutputOff(OUT_USB_R);
          SetOutputOff(OUT_LED_3);
          bIsRunStep[iMainProcess] = true;
          //bIsRunStep[iMainProcess_S9] = true;
        }
      }
      break;



    //Do eMain_Rear_Light
    case eMain_Rear_Light:
      {
        if (!bIsRunStep[iMainProcess])
        {
#ifdef DEBUG
          Serial.print('3');
#endif
          SetOutputOn(OUT_LED_3);
          bIsRunStep[iMainProcess] = true;
        }
      }
      break;


    //Do eMain_Rear_Preview
    case eMain_Rear_Preview:
      {
        if (!bIsRunStep[iMainProcess])
        {
#ifdef DEBUG
          Serial.print('4');
#endif                                            //atk
          SetOutputOff(OUT_LED_3);
          SetOutputOn(OUT_BLACK_WHITE_REAR_OUT);
          delay(TIME_CYLINDER);
          SetOutputOff(OUT_BLACK_WHITE_REAR_OUT);
          bIsRunStep[iMainProcess] = true;
        }
      }
      break;


    //Do eMain_Rear_Black_Chart
    case eMain_Rear_Black_Chart:
      {
        if (!bIsRunStep[iMainProcess])
        {
#ifdef DEBUG
          Serial.print('5');
#endif

          ThreeStateControl(eStateSecond);

          bIsRunStep[iMainProcess] = true;
        }
      }
      break;


    //Do eMain_Rear_White_Chart
    case eMain_Rear_White_Chart:
      {
        if (!bIsRunStep[iMainProcess])
        {

#ifdef DEBUG
          Serial.print('6');
#endif

          ThreeStateControl(eStateThird);

          SetOutputOn(OUT_LED_2);                         //BackLight On

          bIsRunStep[iMainProcess] = true;

        }

      }
      break;


    //Do eMain_Rear_Vision
    case eMain_Rear_Vision:
      {
        if (!bIsRunStep[iMainProcess])
        {

#ifdef DEBUG
          Serial.print('7');
#endif

          ThreeStateControl(eStateFirst);

          SetOutputOff(OUT_LED_2);                         //BackLight Off
          SetOutputOff(OUT_LED_1);

          bIsRunStep[iMainProcess] = true;
        }

      }
      break;


    //Do eMain_Front_Light
    case eMain_Front_Light:
      {
        if (!bIsRunStep[iMainProcess])
        {
#ifdef DEBUG
          Serial.print('8');
#endif

          SetOutputOn(OUT_LED_1);                         //BackLight Off

          bIsRunStep[iMainProcess] = true;
        }
      }
      break;


    //Do eMain_Front_Preview
    case eMain_Front_Preview:
      {
        if (!bIsRunStep[iMainProcess])
        {
#ifdef DEBUG
          Serial.print('9');
#endif

          SetOutputOff(OUT_LED_1);                         //BackLight Off

          bIsRunStep[iMainProcess] = true;
        }
      }
      break;


    //Do eMain_Front_White_Chart
    case eMain_Front_White_Chart:
      {
        if (!bIsRunStep[iMainProcess])
        {
#ifdef DEBUG
          Serial.println("10");
#endif

          SetOutputOn(OUT_CHART_WHITE_FRONT);
          SetOutputOff(OUT_CHART_BLACK_FRONT_L);
          SetOutputOff(OUT_CHART_BLACK_FRONT_R);

          bIsRunStep[iMainProcess] = true;
        }
      }
      break;


    //Do eMain_Front_Black_Chart
    case eMain_Front_Black_Chart:
      {
        if (!bIsRunStep[iMainProcess])
        {
#ifdef DEBUG
          Serial.println("11");
#endif

          SetOutputOff(OUT_CHART_WHITE_FRONT);
          SetOutputOn(OUT_CHART_BLACK_FRONT_L);
          SetOutputOn(OUT_CHART_BLACK_FRONT_R);
          bIsRunStep[iMainProcess] = true;
        }
      }
      break;


    //Do eMain_Front_Vision
    case eMain_Front_Vision:
      {
        if (!bIsRunStep[iMainProcess])
        {
#ifdef DEBUG
          Serial.println("12");
#endif
          SetOutputOff(OUT_CHART_BLACK_FRONT_L);
          SetOutputOff(OUT_CHART_BLACK_FRONT_R);
          bIsRunStep[iMainProcess] = true;
        }
      }
      break;
    default:
      break;
  }

}
void LoopControl_S9()
{
   switch (iMainProcess_S9)
  {
    //Do eMain_ORG_Rear
    case eMain_ORG_Rear_S9:
      {

#ifdef DEBUG
        Serial.println("100");
#endif

      }
      break;


    //Do eMain_ORG_Front
    case eMain_ORG_Front_S9:
      {
#ifdef DEBUG
        Serial.println("101");
#endif
      }
      break;

    //Do eMain_ORG_All
    case eMain_ORG_All_S9:
      {
        if (!bIsRunStep[iMainProcess_S9])
        {
          SetOutputOff(OUT_CHART_WHITE_FRONT);
          ThreeStateControl(eStateFirst);
          SetOutputOff(OUT_CHART_BLACK_FRONT_L);
          SetOutputOff(OUT_CHART_BLACK_FRONT_R);

          SetOutputOff(OUT_LED_1);
          SetOutputOff(OUT_LED_2);
          SetOutputOff(OUT_LED_3);
          bIsRunStep[iMainProcess_S9] = true;
        }
#ifdef DEBUG
        Serial.println("102");
#endif
      }
      break;


    //Do nothing => Scan
    case eMain_Do_nothing_S9:
      {
#ifdef DEBUG
        Serial.print('*');
#endif
      }
      break;


    //Do eMain_USB_In
    case eMain_USB_In_S9:
      {
        if (!bIsRunStep[iMainProcess_S9])
        {
#ifdef DEBUG
          Serial.print('1');
#endif
          SetOutputOn(OUT_USB_L);
          SetOutputOn(OUT_USB_R);

          bIsRunStep[iMainProcess_S9] = true;
        }
      }
      break;


    //Do eMain_USB_Out
    case eMain_USB_Out_S9:
      {
        if (!bIsRunStep[iMainProcess_S9])
        {
#ifdef DEBUG
          Serial.print('2');
#endif
          SetOutputOff(OUT_USB_L);
          SetOutputOff(OUT_USB_R);
          SetOutputOff(OUT_LED_3);
          bIsRunStep[iMainProcess_S9] = true;
        }
      }
      break;



    //Do eMain_Rear_Light
    case eMain_Rear_Light_S9:
      {
        if (!bIsRunStep[iMainProcess_S9])
        {
#ifdef DEBUG
          Serial.print('3');
#endif
         // if model == '9':
           // SetOutputOn(OUT_CHART_VISION_REAR);
          SetOutputOn(OUT_LED_3);
          bIsRunStep[iMainProcess_S9] = true;
        }
      }
      break;


    //Do eMain_Rear_Preview
    case eMain_Rear_Preview_S9:
      {
        if (!bIsRunStep[iMainProcess_S9])
        {
#ifdef DEBUG
          Serial.print('4');
#endif                                            //atk
         // if model == '9':
           // SetOutputOn(OUT_CHART_VISION_REAR);
          SetOutputOff(OUT_LED_3);
          SetOutputOn(OUT_BLACK_WHITE_REAR_OUT);
          delay(TIME_CYLINDER);
          SetOutputOff(OUT_BLACK_WHITE_REAR_OUT);
          bIsRunStep[iMainProcess_S9] = true;
        }
      }
      break;


    //Do eMain_Rear_Black_Chart
    case eMain_Rear_Black_Chart_S9:
      {
        if (!bIsRunStep[iMainProcess_S9])
        {
#ifdef DEBUG
          Serial.print('5');
#endif

          ThreeStateControl(eStateSecond);

          bIsRunStep[iMainProcess_S9] = true;
        }
      }
      break;


    //Do eMain_Rear_White_Chart
    case eMain_Rear_White_Chart_S9:
      {
        if (!bIsRunStep[iMainProcess_S9])
        {

#ifdef DEBUG
          Serial.print('6');
#endif

          ThreeStateControl(eStateThird);

          SetOutputOn(OUT_LED_2);                         //BackLight On

          bIsRunStep[iMainProcess_S9] = true;

        }

      }
      break;


    //Do eMain_Rear_Vision
    case eMain_Rear_Vision_S9:
      {
        if (!bIsRunStep[iMainProcess_S9])
        {

#ifdef DEBUG
          Serial.print('7');
#endif

          ThreeStateControl(eStateFirst);

          SetOutputOff(OUT_LED_2);                         //BackLight Off
          SetOutputOff(OUT_LED_1);

          bIsRunStep[iMainProcess_S9] = true;
        }

      }
      break;
    
  case eMain_Rear2_Light_S9:
  {
    if (!bIsRunStep[iMainProcess_S9])
    {
#ifdef DEBUG
          Serial.print('8');
#endif
      SetOutputOff(OUT_CHART_VISION_REAR);
      SetOutputOn(OUT_LED_4)
      bIsRunStep[iMainProcess_S9] = true;
    }
  } break;
  
  case eMain_Rear2_Preview_S9:
  {
    if (!bIsRunStep[iMainProcess_S9])
    {
#ifdef DEBUG
          Serial.print('9');
#endif
      SetOutputOff(OUT_LED_4);
          SetOutputOn(OUT_BLACK_WHITE_REAR_OUT);
          delay(TIME_CYLINDER);
          SetOutputOff(OUT_BLACK_WHITE_REAR_OUT);
      bIsRunStep[iMainProcess_S9] = true;
    }
  } break;
  
    case eMain_Rear2_Black_Chart_S9:
  {
    if (!bIsRunStep[iMainProcess_S9])
    {
#ifdef DEBUG
          Serial.print('10');
#endif
      ThreeStateControl(eStateSecond);
      bIsRunStep[iMainProcess_S9] = true;
    }
  } break;
  
  case eMain_Rear2_White_Chart_S9:
  {
    if (!bIsRunStep[iMainProcess_S9])
    {
#ifdef DEBUG
          Serial.print('11');
#endif
      ThreeStateControl(eStateThird);
          SetOutputOn(OUT_LED_2);   
      bIsRunStep[iMainProcess_S9] = true;
    }
  } break;
  
  case eMain_Rear2_Vision_S9:
  {
    if (!bIsRunStep[iMainProcess_S9])
    {
#ifdef DEBUG
          Serial.print('12');
#endif
      ThreeStateControl(eStateFirst);
          SetOutputOff(OUT_LED_2);                         //BackLight Off
          SetOutputOff(OUT_LED_1);
      bIsRunStep[iMainProcess_S9] = true;
    }
  } break;

  case eMain_Dual_1_S9:
  {
    if (!bIsRunStep[iMainProcess_S9])
    {
#ifdef DEBUG
          Serial.print('13');
#endif
      
      bIsRunStep[iMainProcess_S9] = true;
    }
  } break;
  
  case eMain_Dual_2_S9:
  {
    if (!bIsRunStep[iMainProcess_S9])
    {
#ifdef DEBUG
          Serial.print('14');
#endif
      bIsRunStep[iMainProcess_S9] = true;
    }
  } break;
  
    //Do eMain_Front_Light
    case eMain_Front_Light_S9:
      {
        if (!bIsRunStep[iMainProcess_S9])
        {
#ifdef DEBUG
          Serial.print('15');
#endif

          SetOutputOn(OUT_LED_1);                         //BackLight Off

          bIsRunStep[iMainProcess_S9] = true;
        }
      }
      break;


    //Do eMain_Front_Preview
    case eMain_Front_Preview_S9:
      {
        if (!bIsRunStep[iMainProcess_S9])
        {
#ifdef DEBUG
          Serial.print('16');
#endif

          SetOutputOff(OUT_LED_1);                         //BackLight Off

          bIsRunStep[iMainProcess_S9] = true;
        }
      }
      break;


    //Do eMain_Front_White_Chart
    case eMain_Front_White_Chart_S9:
      {
        if (!bIsRunStep[iMainProcess_S9])
        {
#ifdef DEBUG
          Serial.println("17");
#endif

          SetOutputOn(OUT_CHART_WHITE_FRONT);
          SetOutputOff(OUT_CHART_BLACK_FRONT_L);
          SetOutputOff(OUT_CHART_BLACK_FRONT_R);

          bIsRunStep[iMainProcess_S9] = true;
        }
      }
      break;


    //Do eMain_Front_Black_Chart
    case eMain_Front_Black_Chart_S9:
      {
        if (!bIsRunStep[iMainProcess_S9])
        {
#ifdef DEBUG
          Serial.println("18");
#endif

          SetOutputOff(OUT_CHART_WHITE_FRONT);
          SetOutputOn(OUT_CHART_BLACK_FRONT_L);
          SetOutputOn(OUT_CHART_BLACK_FRONT_R);
          bIsRunStep[iMainProcess_S9] = true;
        }
      }
      break;


    //Do eMain_Front_Vision
    case eMain_Front_Vision_S9:
      {
        if (!bIsRunStep[iMainProcess_S9])
        {
#ifdef DEBUG
          Serial.println("19");
#endif
          SetOutputOff(OUT_CHART_BLACK_FRONT_L);
          SetOutputOff(OUT_CHART_BLACK_FRONT_R);
          bIsRunStep[iMainProcess_S9] = true;
        }
      }
      break;
    default:
      break;
  }

}

void serialEvent()
{
  String str;
  while (Serial.available())
  {

    char data = (char)Serial.read();

#ifdef DEBUG
    Serial.print(data);

    switch(data)
    {
      case 'A':  SetOutputOn(OUT_LED_1); break;     //Led1
      case 'a':  SetOutputOff(OUT_LED_1); break;    //Led1

      case 'B':  SetOutputOn(OUT_LED_2); break;     //Led2
      case 'b':  SetOutputOff(OUT_LED_2); break;    //Led2

      case 'C':  SetOutputOn(OUT_LED_3); break;     //Led3
      case 'c':  SetOutputOff(OUT_LED_3); break;    //Led3

      case 'D':  SetOutputOn(OUT_LED_4); break;     //Led4
      case 'd':  SetOutputOff(OUT_LED_4); break;    //Led4      

      case 'E':  SetOutputOn(OUT_CHART_VISION_REAR); break;     //Chart Vision Rear
      case 'e':  SetOutputOff(OUT_CHART_VISION_REAR); break;    //Chart Vision Rear 

      case 'F':  SetOutputOn(OUT_CHART_WHITE_FRONT); break;     //Chart White Front
      case 'f':  SetOutputOff(OUT_CHART_WHITE_FRONT); break;    //Chart White Front

      case 'G':  SetOutputOn(OUT_USB_L); break;     //USB Left
      case 'g':  SetOutputOff(OUT_USB_L); break;    //USB Left 

      case 'H':  SetOutputOn(OUT_USB_R); break;     //USB Right
      case 'h':  SetOutputOff(OUT_USB_R); break;    //USB Right      

      case 'I':  SetOutputOn(OUT_CHART_BLACK_FRONT_L); break;     //Black Front Left
      case 'i':  SetOutputOff(OUT_CHART_BLACK_FRONT_L); break;    //Black Front Left

      case 'K':  SetOutputOn(OUT_CHART_BLACK_FRONT_R); break;     //Black Front Right
      case 'k':  SetOutputOff(OUT_CHART_BLACK_FRONT_R); break;    //Black Front Right 
       
      case 'L':  ThreeStateControl(eStateFirst); break;    //Black_White State 1 //in
      case 'M':  ThreeStateControl(eStateSecond); break;     //Black_White State 2 //black
      case 'N':  ThreeStateControl(eStateThird); break;    //Black_White State 3 //white     

      case 'O':  SetOutputOn(OUT_BLACK_WHITE_REAR_IN); break;     //OUT_BLACK_WHITE_REAR_IN
      case 'o':  SetOutputOff(OUT_BLACK_WHITE_REAR_IN); break;    //OUT_BLACK_WHITE_REAR_IN

      case 'P':  SetOutputOn(OUT_BLACK_WHITE_REAR_OUT); break;     //OUT_BLACK_WHITE_REAR_OUT
      case 'p':  SetOutputOff(OUT_BLACK_WHITE_REAR_OUT); break;    //OUT_BLACK_WHITE_REAR_OUT   

      default: break;                          
    }
#endif

/*USB In*///------------------------change model
switch(data)
    {
      case '9': model = '9';break;
      case '!':  SetOutputOn(OUT_USB_L);  SetOutputOn(OUT_USB_R);   break;      //USB In
      case '@':  SetOutputOff(OUT_USB_L); SetOutputOff(OUT_USB_R);  break;      //USB Out    

      case '#':  SetOutputOn(OUT_CHART_BLACK_FRONT_L);  SetOutputOn(OUT_CHART_BLACK_FRONT_R);   break;      //Black Front Left
      case '$':  SetOutputOff(OUT_CHART_BLACK_FRONT_L); SetOutputOff(OUT_CHART_BLACK_FRONT_R);  break;      //Black Front Left

     
      case 'E':
       if (model=='9') inc_process_S9();
       else inc_process();
       break;    //Next
      case 'F':  
       if (model=='9') dec_process_S9();
       else dec_process();
       break;//Back
      case 'G':  if (bIsRunStep[eMain_ORG_All])
                    bIsRunStep[eMain_ORG_All] = false;
                  iMainProcess = eMain_ORG_All; break;   //Reset

      default: break;                          
    }
  }
}




