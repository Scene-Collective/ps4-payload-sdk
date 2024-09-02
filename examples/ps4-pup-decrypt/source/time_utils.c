#include "time_utils.h"

extern time_t prevtime;

uint8_t GetElapsed(uint64_t ResetInterval) {
  time_t currenttime = time(0);
  uint64_t elapsed = currenttime - prevtime;

  if ((ResetInterval == 0) || (elapsed >= ResetInterval)) {
    prevtime = currenttime;
    return 1;
  }

  return 0;
}