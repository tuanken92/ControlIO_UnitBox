#ifndef MUNITBOXPROCESS_H
#define MUNITBOXPROCESS_H
#include "DefSystem.h"
#include "MTickTimeAd.h"
class MUnitBoxProcess
{
  public:
    MUnitBoxProcess(int iLine);
    ~MUnitBoxProcess();

    int m_iLine;
  private:
  public:
    void				 clearVariable();
    bool				 Initialize();

    void				 ThreadRun();
    void				 ThreadStop();
    void         ThreadFunction();

    void				 ThreadJob();

  public:
    bool				 m_bThreadLife;
    bool				 m_bThreadTerminate;
    /** Thread Handle */

    EOpMode				 m_eOPMode;
    EOPStatus			 m_eOPStatus;
    EStepUnitBoxProcess  m_estepCurrent;
    EStepUnitBoxProcess  m_estepPrev;
    void				 doRunStep();


    int Start();

    int Stop();

    bool isRunning();

    int GetRunMode();

    void SetOPMode(EOpMode eOPMode);
    void SetOPStatus(EOPStatus eOPStatus );
    void SetStep(EStepUnitBoxProcess eStep);

    bool IsSafty();

    bool IsError();

    void GotoTeaching();

    void StopTeaching();

    bool				 m_bAutoRun;
  public:
    void SetOutputOn(int iOutPut);
    void SetOutputOff(int iOutPut);
    bool IsOnInput(int iInPut);

    void RequestVision();
    bool IsFinishVision();

    MTickTimeAd m_timeProcess;
};

#endif //MUNITBOXPROCESS_H
