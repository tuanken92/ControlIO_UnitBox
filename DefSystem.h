#ifndef DEFSYSTEM_H
#define DEFSYSTEM_H

/*atk*/
#define NUM_INPUT 4
#define NUM_STEP  19

#define IN_START  0
#define IN_NEXT   1
#define IN_BACK   2
#define IN_RESET  3

#define TIME_DEBOUNCE 100
#define TIME_FINISH   1000
#define TIME_CYLINDER 450


#define WAIT_INPUT_PRESS        0
#define WAIT_INPUT_DEBOUNCE     1
#define WAIT_INPUT_RELEASE      2
#define WAIT_INPUT_FINISH       3


#define BTN_STATE_NEXT  1
#define BTN_STATE_BACK  2
#define BTN_STATE_RESET 3


enum EThreeState
{
  eStateFirst,
  eStateSecond,
  eStateThird
};

enum EMainProcess
{
  eMain_Btn_Next,
  eMain_Btn_Back,
  eMain_Btn_Reset,


  eMain_ORG_Rear,
  eMain_ORG_Front,
  eMain_ORG_All,
  
  eMain_USB_In,
  eMain_USB_Out,
  
  eMain_Do_nothing,           //ORG State
  
  eMain_Rear_Light,            //Led On
  eMain_Rear_Preview,          //Led Off
  eMain_Rear_Black_Chart,      //Black Chart In                             ***Vacum 3 state
  eMain_Rear_White_Chart,      //White Chart In && BackLight On             ***Vacum 3 state
  eMain_Rear_Vision,           //Return ORG Rear (Black-White Chart + BackLight Off)
  
  eMain_Front_Light,            //Led On
  eMain_Front_Preview,          //Led Off
  eMain_Front_White_Chart,      //White Chart In
  eMain_Front_Black_Chart,      //Black Chart In
  eMain_Front_Vision           //Return ORG Front 
      
};

enum EMainProcess_S9
{
  eMain_Btn_Next_S9,
  eMain_Btn_Back_S9,
  eMain_Btn_Reset_S9,


  eMain_ORG_Rear_S9,
  eMain_ORG_Front_S9,
  eMain_ORG_All_S9,
  
  eMain_USB_In_S9,
  eMain_USB_Out_S9,
  
  eMain_Do_nothing_S9,           //ORG State
  
  eMain_Rear_Light_S9,            //Led On
  eMain_Rear_Preview_S9,          //Led Off
  eMain_Rear_Black_Chart_S9,      //Black Chart In                             ***Vacum 3 state
  eMain_Rear_White_Chart_S9,      //White Chart In && BackLight On             ***Vacum 3 state
  eMain_Rear_Vision_S9,           //Return ORG Rear (Black-White Chart + BackLight Off)
//
  eMain_Rear2_Light_S9,            //Led On
  eMain_Rear2_Preview_S9,          //Led Off
  eMain_Rear2_Black_Chart_S9,      //Black Chart In                             ***Vacum 3 state
  eMain_Rear2_White_Chart_S9,      //White Chart In && BackLight On             ***Vacum 3 state
  eMain_Rear2_Vision_S9,           //Return ORG Rear (Black-White Chart + BackLight Off)

  eMain_Dual_1_S9,
  eMain_Dual_2_S9,
  
  eMain_Front_Light_S9,            //Led On
  eMain_Front_Preview_S9,          //Led Off
  eMain_Front_White_Chart_S9,      //White Chart In
  eMain_Front_Black_Chart_S9,      //Black Chart In
  eMain_Front_Vision_S9           //Return ORG Front 
      
};


/*atk*/


///////////////////////////////////////////////////////////////////////////                    
// Àû¿ë ¼³ºñ :  I/O Define                    
//__________________________________________________________________________                    
// INPUT DEFINE                     

//////////////////////////////////////////////////////////////////////////
//__________________________________________________________________________
// X0 ~ X15
//const int IN_BUTTON_START   = 30;
//const int IN_BUTTON_NEXT    = 24;
//const int IN_BUTTON_BACK    = 26;
//const int IN_BUTTON_RESET   = 28;
const int IN_BUTTON_START   = 22;
const int IN_BUTTON_NEXT    = 24;
const int IN_BUTTON_BACK    = 26;
const int IN_BUTTON_RESET   = 28;      
//const int IN_SENSOR_SPARE24 = 22;   
//const int IN_SENSOR_SPARE26 = 26;   
//const int IN_SENSOR_SPARE28 = 28;   
//const int IN_SENSOR_SPARE30 = 30;   
//const int IN_SENSOR_SPARE32 = 32;   


//__________________________________________________________________________                    
// OUTPUT DEFINE  
//__________________________________________________________________________
// Y0 ~ Y7
// const int  OUT_START_LAMP = 2000;
const int OUT_LED_1 = 23;
const int OUT_LED_2 = 25;
const int OUT_LED_3 = 27;
const int OUT_LED_4 = 29;

const int OUT_CHART_VISION_REAR       = 31;
const int OUT_CHART_WHITE_FRONT       = 33;
const int OUT_BLACK_WHITE_REAR_IN     = 35;
const int OUT_BLACK_WHITE_REAR_OUT    = 37;
const int OUT_USB_L                   = 39;
const int OUT_USB_R                   = 41;
const int OUT_CHART_BLACK_FRONT_L     = 43;
const int OUT_CHART_BLACK_FRONT_R     = 45; 



//const int OUT_CYLINDER_USB_IN_OUT_L = 25;   
//const int OUT_CYLINDER_USB_IN_OUT_R = 23;    
//const int OUT_CYLINDER_TEST_BLACK_L = 29;    
//const int OUT_CYLINDER_TEST_BLACK_R = 27;   
//const int OUT_BUTTON_NEXT = 31;
//const int OUT_BUTTON_BACK = 33;
//const int OUT_BUTTON_RESET = 35;
//const int OUT_BUTTON_BUZZ = 37;
//const int OUT_LAMP_RED = 39;
//const int OUT_LAMP_GREEN = 43;
//const int OUT_LAMP_YELLOW = 41;

enum  EBlackWhiteOp
{
  State_In,
  State_Black,
  State_White
};

/************************************************************************/
/*  Operation Mode							                            */
/************************************************************************/
enum EOpMode
{
  READY_MODE,
  AUTORUN_MODE,
  STOP_MODE,
};
/************************************************************************/
/*  Operation Status						                            */
/************************************************************************/
enum EOPStatus
{
  INIT_STATUS,
  ERROR_STOP,
  STEP_STOP,
  CYCLE_STOP,
  START_RUN,
  RUN,
  RUN_SAFTY,
};


//Unitbox//
enum EStepUnitBoxProcess
{
  STEP_UNIT_BOX_NONE = -1,
  STEP_UNIT_INIT = 0,
  STEP_UNIT_WAIT_SS_CV_PREV,
  STEP_UNIT_WAIT_SS_CV_PREV2,
  STEP_UNIT_WAIT_STOP_CV_PRE,
  STEP_UNIT_WAIT_DETECT,
  STEP_UNIT_WAIT_DETECT2,
  STEP_UNIT_ALIGHT_OK,
  STEP_UNIT_WAIT_STOP_CV,
  STEP_UNIT_REQUEST_VISON,
  STEP_UNIT_REQUEST_VISON2,

  STEP_UNIT_WAIT_FINISH_VISION,

  STEP_UNIT_RUN_VISON_0,
  STEP_UNIT_RUN_VISON_1,
  STEP_UNIT_RUN_VISON_2,
  STEP_UNIT_RUN_VISON_3,
  STEP_UNIT_RUN_VISON_4,

  STEP_UNIT_WAIT_RESULT_VISON_0,
  STEP_UNIT_WAIT_RESULT_VISON_1,
  STEP_UNIT_WAIT_RESULT_VISON_2,
  STEP_UNIT_WAIT_RESULT_VISON_3,
  STEP_UNIT_WAIT_RESULT_VISON_4,
  STEP_UNIT_WAIT_RESULT_SHOW,
  STEP_UNIT_UP_CL,
  STEP_UNIT_WAIT_UP,
  STEP_UNIT_WAIT_CYLINDOR_RETURN,
  STEP_UNIT_WAIT_CYLINDOR_RETURN2,
  STEP_UNIT_WAIT_UNIT_OUT,
  STEP_UNIT_FINISH,
  STEP_UNIT_BYPASS_INIT,
  STEP_UNIT_BYPASS_WAIT_DETECT_UNIT,
  STEP_UNIT_BYPASS_WAIT_DETECT_UNIT2,
  STEP_UNIT_BYPASS_WAIT_DETECT_IN_CV,
  STEP_UNIT_BYPASS_WAIT_UNITBOX_IS_PASS,
  STEP_UNIT_NG,
  STEP_UNIT_WAIT_RESET,
  STEP_UNIT_WAIT_RESET2,
  STEP_UNIT_INIT_TEACH,
  STEP_UNIT_WAIT_DETECT_TEACH,
  STEP_UNIT_WAIT_DETECT2_TEACH,
  STEP_UNIT_WAIT_STOP_CV_TEACH,
  STEP_UNIT_WAIT_FOCUS_TEACH,
  STEP_UNIT_WAIT_FINISH_TEACH,

  STEP_UNIT_TESTVISION_INIT,
  STEP_UNIT_TESTVISION_REQUEST_VISION

};


enum EButton
{
  EBUTTON_WAIT_START_ON,
  EBUTTON_WAIT_START_DELAY,
  EBUTTON_WAIT_START_OFF,
  EBUTTON_WAIT_FINISH,
  EBUTTON_NEXT
};


enum EInput
{
  E_INPUT_WAIT_PRESS,
  E_INPUT_WAIT_DEBOUNCE,
  E_INPUT_WAIT_RELEASE,
  E_INPUT_WAIT_FINISH,
};


enum ESerial
{
   SERIAL_DONOTHING,
   
   SERIAL_NEXT_ON,
   SERIAL_NEXT_WAIT,
   SERIAL_NEXT_OFF,

   SERIAL_BACK_ON,
   SERIAL_BACK_WAIT,
   SERIAL_BACK_OFF,

   SERIAL_RESET_NG_ON,
   SERIAL_RESET_NG_WAIT,
   SERIAL_RESET_NG_OFF
   
};


#endif // DEFSYSTEM_H

