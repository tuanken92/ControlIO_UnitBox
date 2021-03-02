
#include "MWinSystem.h"




MWinSystem::MWinSystem()
{
  clearVariable();
  m_pUnitBoxProcess = new MUnitBoxProcess(0);
  m_pUnitBoxProcess2 = new MUnitBoxProcess2(1);
}


MWinSystem::~MWinSystem()
{
  destroy();
  delete m_pUnitBoxProcess;
  clearVariable();
}

void MWinSystem::clearVariable()
{
  //Data

}


int MWinSystem::Initialize()
{
  return ERR_SYSTEM_SUCCESS;
}

void MWinSystem::startThreads()
{
}


void MWinSystem::destroy()
{

}
void MWinSystem::linkThread()
{
}

void MWinSystem::xxx()
{
}





















