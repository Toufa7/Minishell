#include <stdio.h>
#include <signal.h>
#include <string.h>   /* for memset */
#include <unistd.h>   /* for sleep and getpid */

int done = 0;

void sighandler(int signo)
{
   if (signo == SIGTERM || signo == SIGINT)
   {
      done = 1;
   }
}

int main(void)
{
   struct sigaction act;

   memset(&act, 0, sizeof(act));
   act.sa_handler = sighandler;

   sigaction(SIGINT,  &act, 0);
   sigaction(SIGTERM, &act, 0);

   printf("Press ctrl-c, or send SIGTERM to process ID %d, to gracefully exit program.\n", getpid());

   while (!done)
   {
      sleep(1);
      printf("I'm still waiting...\n");
   }

   printf("All done!\n");

   return 0;
}