#ifndef MUnitBoxProcess22_H
#define MUnitBoxProcess22_H
#include "DefSystem.h"
#include "MTickTimeAd.h"
class MUnitBoxProcess2
{
  public:
    MUnitBoxProcess2(int iLine);
    ~MUnitBoxProcess2();

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
    void OutPutOn(int iOutPut);
    void OutPutOff(int iOutPut);
    bool IsOnInPut(int iInPut);

    MTickTimeAd m_timeProcess;
};

#endif //MUnitBoxProcess22_H
