/* The following code is added by Sai Motukuri - SSM190012
** This file contains the code that outputs the tick data into the console.
** The structure of this code has been inspired from the random.c test case code. 
*/
#include "pstat.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

//Function Declaration
void spin();

int main(){

  int numtickets[]={20,10,30};
  int pids[3];

  //Setting the tickets for the parents process (20 tickets)
  pids[0]=getpid();
  settickets(numtickets[0]);

  //Fork twice to create the other two processes
  int i;
  for(i=1;i<3;i++){
    pids[i]=fork();
    if(pids[i]==0){
      for (;;){
        //Spin the child processes
	spin();
      }
    }
    else{
      //Set the tickets for the other two processes
      settickets(numtickets[i]);
    }
  }
    
  struct pstat proc;
  int time=0;
  int ticks[3]={0,0,0};

  //Print the pIds and the ticket count for all 3 processes.
  printf(1, "pIDs:\t\t%d,\t %d, \t%d\n", pids[0],pids[1],pids[2]);
  printf(1, "TICKETS:\t%d, \t%d, \t%d\n",numtickets[2], numtickets[0], numtickets[2]);
  printf(1, "    TIME (s)\t     TICKS DATA:\n ");

  //Loop for 30 intervals and print tick data for each process at every interval
  while(time<30){
      if(getpinfo(&proc)!=0){
      printf(1, "check failed: getpinfo\n");
      goto Clear;
    }
    
    int j;
    int pid;
    for(i=0;i<3;i++){
      pid=pids[i];
      for(j=0;j<NPROC;j++){
	if(proc.pid[j]==pid){
      	  ticks[i]=proc.ticks[j];
	}
      }
    }
    printf(1, "\t%d,\t", (time+1));
    for(i = 0; i < 3; i++){
      printf(1, "%d,\t", ticks[i]);
    } 
    printf(1, "\n", 1);
    
    spin();
    time++;
  }
  
  //Kill all the processes
  Clear:
    for(i = 0; pids[i]>0; i++){
      kill(pids[i]);
    }
    while(wait()>-1);

  exit();
}

//Set up a spin function that will keep the processes running for the time period
void spin()
{
  int i = 0;
  int j = 0;
  int k = 0;
  for(i = 0; i < 50; ++i)
    {
      for(j = 0; j < 400000; ++j)
        {
	  k = j % 10;
	  k = k + 1;
	}
    }
}
/* End of code added */
