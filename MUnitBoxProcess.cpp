
#include "MUnitBoxProcess.h"
#include <Arduino.h>
#include "MWinSystem.h"

extern  MWinSystem m_plnkSystem;



MUnitBoxProcess::MUnitBoxProcess(int iLine)
{
  m_iLine = iLine;
  clearVariable();
  Initialize();
  //AssignComponents(SUnitBoxRefCompList0 listRefComponents);
  // Critical Section �ʱ�ȭ
}


MUnitBoxProcess::~MUnitBoxProcess()
{
  clearVariable();

}

void MUnitBoxProcess::clearVariable()
{

}
bool MUnitBoxProcess::Initialize()
{


  m_eOPMode = STOP_MODE;
  m_eOPStatus = STEP_STOP;

  m_bAutoRun = false;
  m_bThreadLife = false;



  return 1;
}

void MUnitBoxProcess::ThreadRun()
{

  ThreadFunction();
}

void MUnitBoxProcess::ThreadFunction()
{
  // Thread Loop
  ThreadJob();
}

void MUnitBoxProcess::ThreadJob()
{
  switch (m_eOPMode)
  {
    case STOP_MODE:

      m_bAutoRun = false;
      break;
    case READY_MODE:

      m_bAutoRun = false;
      break;
    case AUTORUN_MODE:

      switch (m_eOPStatus)
      {
        case ERROR_STOP:
        case STEP_STOP:
        case INIT_STATUS:
          m_bAutoRun = false;

          break;

        case START_RUN:

          m_bAutoRun = true;
          m_eOPStatus = RUN;
          break;
        case RUN:
          doRunStep();
          break;
        case RUN_SAFTY:
          m_bAutoRun = false;
          break;
      }
      break;
  }
}

void MUnitBoxProcess::ThreadStop()
{

}

void MUnitBoxProcess::doRunStep()
{
  switch (m_estepCurrent)
  {
    case STEP_UNIT_BOX_NONE:
      break;
  }
}

int MUnitBoxProcess::Start()
{
  SetOPMode(AUTORUN_MODE);
  SetOPStatus(RUN);
  SetStep(STEP_UNIT_INIT);
  return 1;
}

int MUnitBoxProcess::Stop()
{
  if (isRunning())
  {
    m_bAutoRun = false;
  }
  return 1;
}

bool MUnitBoxProcess::isRunning()
{
  return m_bAutoRun;
}

void MUnitBoxProcess::SetStep(EStepUnitBoxProcess eStep)
{
  m_estepPrev = m_estepCurrent;
  m_estepCurrent = eStep;
}

void MUnitBoxProcess::SetOPMode(EOpMode eOPMode)
{
  m_eOPMode = eOPMode;
}
void MUnitBoxProcess::SetOPStatus(EOPStatus eOPStatus )
{
  m_eOPStatus = eOPStatus;
}

bool MUnitBoxProcess::IsSafty()
{
  return 1;
}

bool MUnitBoxProcess::IsError()
{
  return 0;
}

void MUnitBoxProcess::SetOutputOn(int iOutPut)
{
  digitalWrite(iOutPut, HIGH);
}

void MUnitBoxProcess::SetOutputOff(int iOutPut)
{
  digitalWrite(iOutPut, LOW);
}
bool MUnitBoxProcess::IsOnInput(int iInPut)
{
  return !digitalRead(iInPut);
}

void MUnitBoxProcess::RequestVision()
{
  Serial.println('L');
}

bool MUnitBoxProcess::IsFinishVision()
{
  return true;
}



