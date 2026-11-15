#include "config.h"

#include "apm.h"

/* apm_video.c was built inside apm_funcs.c, which needs XAA */
#define PSZ	8
#define A(s)	Apm##s
#define MAXLOOP	1000000

static __inline__ void
A(WaitForFifo)(ApmPtr pApm, int slots)
{
  if (!pApm->UsePCIRetry) {
    volatile int i;

    for(i = 0; i < MAXLOOP; i++) {
      if ((STATUS() & STATUS_FIFO) >= slots)
	break;
    }
    if (i == MAXLOOP) {
      unsigned int status = STATUS();

      WRXB(0x1FF, 0);
      if (!xf86ServerIsExiting())
	  FatalError("Hung in WaitForFifo() (Status = 0x%08X)\n", status);
    }
  }
}

#include "apm_video.c"
