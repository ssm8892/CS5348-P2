/* The following code has been added by Jesus Tapia - JIT210000
** Struct definition of pstat
*/
#ifndef _PSTAT_H_
#define _PSTAT_H_
#include "param.h"

struct pstat 
{
	// Whether this slot of the process table is in use (1 or 0)
	int inuse[NPROC];

	// The number of tickets this process has
	int tickets[NPROC];

	// The PID of each process
	int pid[NPROC];

	// The number of ticks each process has accumulated
	int ticks[NPROC];
};
/* End of code added */

#endif // _PSTAT_H_
