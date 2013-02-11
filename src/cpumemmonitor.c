
#include <iostream>
#include <sys/sysinfo.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include "stdio.h"

#include <glibtop.h>
#include <glibtop/cpu.h>
#include <glibtop/mem.h>
using namespace std;
/* last total cpu time */
    guint64 cpu_total_time_last_;
    guint64 cpu_used_time_last_;

    /* last io bytes */
    long read_bytes_last_;
    long write_bytes_last_;

    /* nubmer of cpu */
    guint64 ncpu_;

unsigned long getMEM()
{

glibtop_init();
glibtop_mem memory;
glibtop_get_mem(&memory);



return (unsigned long)(memory.cached + memory.buffer + memory.free) * 100/memory.total;
}


float getCPU()
{

 /* initial glibtop_cpu data */
    glibtop_cpu cpu;
    glibtop_get_cpu (&cpu);

    if (!cpu_total_time_last_){
        cpu_total_time_last_ = cpu.total;
        cpu_used_time_last_  = cpu.user + cpu.nice + cpu.sys;
        return 0.0;
    }

    /* get system load */
    float load;
    float total, used;

    total = cpu.total - cpu_total_time_last_;
    used  = cpu.user + cpu.nice + cpu.sys - cpu_used_time_last_;
    cpu_total_time_last_ = cpu.total;
    cpu_used_time_last_  = cpu.user + cpu.nice + cpu.sys;

    load  = 100 * used / max(total, 1.0f);
    load  = min (load, 100.0f);

    return load;



}
int main(int argc, char**argv)
{
   int sockfd,n;
   struct sockaddr_in servaddr,cliaddr;
   socklen_t len;
   char mesg[1000];
   char tosend[1000];
   sockfd=socket(AF_INET,SOCK_DGRAM,0);
   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   servaddr.sin_port=htons(8905);
   bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
   for (;;)
   {
      len = sizeof(cliaddr);
      n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);
      sprintf(tosend,"%f,%Ld",getCPU(),getMEM());
      sendto(sockfd,tosend,strlen(tosend),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
      mesg[n] = 0;
   }
}
