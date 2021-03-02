
#include "MUnitBoxProcess2.h"
#include <Arduino.h>
#include "MWinSystem.h"
extern  MWinSystem m_plnkSystem;



MUnitBoxProcess2::MUnitBoxProcess2(int iLine)
{
  m_iLine = iLine;
  clearVariable();
  Initialize();
  //AssignComponents(SUnitBoxRefCompList0 listRefComponents);
  // Critical Section �ʱ�ȭ
}


MUnitBoxProcess2::~MUnitBoxProcess2()
{
  clearVariable();

}

void MUnitBoxProcess2::clearVariable()
{

}
bool MUnitBoxProcess2::Initialize()
{

  m_eOPMode = STOP_MODE;
  m_eOPStatus = STEP_STOP;

  m_bAutoRun = false;
  m_bThreadLife = false;

  return 1;
}

void MUnitBoxProcess2::ThreadRun()
{

  ThreadFunction();
}

void MUnitBoxProcess2::ThreadFunction()
{
  // Thread Loop
  ThreadJob();
}

void MUnitBoxProcess2::ThreadJob()
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

void MUnitBoxProcess2::ThreadStop()
{

}

void MUnitBoxProcess2::doRunStep()
{
  switch (m_estepCurrent)
  {
    case STEP_UNIT_BOX_NONE:
      break;
  }
}

int MUnitBoxProcess2::Start()
{
  SetOPMode(AUTORUN_MODE);
  SetOPStatus(RUN);
  SetStep(STEP_UNIT_INIT);
  return 1;
}

int MUnitBoxProcess2::Stop()
{
  if (isRunning())
  {
    m_bAutoRun = false;
  }
  return 1;
}

bool MUnitBoxProcess2::isRunning()
{
  return m_bAutoRun;
}

void MUnitBoxProcess2::SetStep(EStepUnitBoxProcess eStep)
{
  m_estepPrev = m_estepCurrent;
  m_estepCurrent = eStep;
}

void MUnitBoxProcess2::SetOPMode(EOpMode eOPMode)
{
  m_eOPMode = eOPMode;
}
void MUnitBoxProcess2::SetOPStatus(EOPStatus eOPStatus )
{
  m_eOPStatus = eOPStatus;
}

bool MUnitBoxProcess2::IsSafty()
{
  return 1;
}

bool MUnitBoxProcess2::IsError()
{
  return 0;
}


void MUnitBoxProcess2::OutPutOn(int iOutPut)
{
  digitalWrite(iOutPut, HIGH);
}

void MUnitBoxProcess2::OutPutOff(int iOutPut)
{
  digitalWrite(iOutPut, LOW);
}
bool MUnitBoxProcess2::IsOnInPut(int iInPut)
{
  return !digitalRead(iInPut);
}



