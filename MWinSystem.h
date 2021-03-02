
#include "MUnitBoxProcess.h"
#include "MUnitBoxProcess2.h"
#ifndef WINSYSTEM_H
#define WINSYSTEM_H


/** Error Code Define */
const int	ERR_SYSTEM_SUCCESS						= 0;

const int	ERR_SYSTEM_FAIL							= -1;
const int	ERR_SYSTEM_COMPONENT_CREATE_FAIL		= 1;
const int	ERR_SYSTEM_TEACHING_INFO_FILE_OPEN_FAIL = 2;
const int	ERR_SYSTEM_TEACHING_INFO_FILE_CLOSE_FAIL = 3;
const int	ERR_SYSTEM_MODEL_CREATE_FAIL			= 4;
const int	ERR_SYSTEM_MODEL_DELETE_FAIL			= 5;
const int	ERR_SYSTEM_MAX_COUNT_EXCEED_LIMIT		= 6;


class MWinSystem
{
  public:
    MWinSystem();
    virtual ~MWinSystem();

  private:

    void						clearVariable();
    void						destroy();


  public:
    int							Initialize();
    void						startThreads();
    void						linkThread();
    void           xxx();

    MUnitBoxProcess*   m_pUnitBoxProcess;
    MUnitBoxProcess2*   m_pUnitBoxProcess2;
};
#endif //WINSYSTEM_H

