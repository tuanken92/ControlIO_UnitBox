#include <Arduino.h>

#include "MTickTimeAd.h"


MTickTimeAd::MTickTimeAd()
{
  m_ulPreTime = 0;
}


MTickTimeAd::~MTickTimeAd()
{
  m_ulPreTime = 0;
}

void MTickTimeAd::StartTimer()
{
  m_ulPreTime = millis();

}

bool MTickTimeAd::LessThan(unsigned long time)
{
  if ( millis() < m_ulPreTime)
  {
    if (millis() > ((4294967295 - m_ulPreTime) + time))
      return false;
    else
      return true;
  } else
  {
    if ((millis() - m_ulPreTime) > time)
      return false;
    else
      return true;
  }

}

bool MTickTimeAd::MoreThan(unsigned long time)
{
  if ( millis() < m_ulPreTime)
  {
    if (millis() > ((4294967295 - m_ulPreTime) + time))
      return true;
    else
      return false;
  } else
  {
    if ((millis() - m_ulPreTime) > time)
      return true;
    else
      return false;
  }
}
