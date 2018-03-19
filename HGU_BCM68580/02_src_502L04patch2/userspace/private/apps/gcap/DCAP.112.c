#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <getopt.h>

#include <mocalib.h>
#include <mocaint.h>
#include "GCAP_Common.h"

static char *chipId = NULL;    // -i option

GCAP_GEN static void showUsage()
{
    printf("Usage: DCAP.112 [-h] \n\
Report the POLICING of the node \n\
\n\
Options:\n\
  -h     Display this help and exit\n");
}

GCAP_GEN int DCAP_112_main(int argc, char **argv)
{
    int nRet = MOCA_API_SUCCESS;
    void *ctx;
    uint32_t  polen;
   
    chipId = NULL;

    // ----------- Parse parameters
#if defined(STANDALONE)
   int i;
   for (i=1; i < argc; i++)
   {
       if (strcmp(argv[i], "-i") == 0)
       {
           i++;
           chipId = argv[i];
       }
       else if (strcmp(argv[i], "?") == 0)
       {
          printf( "Error!  Invalid option - %s\n", argv[i]);
          return(-1);
       }
       else if (strcmp(argv[i], "-h") == 0)
       {
          showUsage();
          return(0); 
       }
    } 
#else
    opterr = 0;

    while((nRet = getopt(argc, argv, "hi:")) != -1) 
    {
        switch(nRet) 
        {
        case 'i':
            chipId = optarg;
            break;
        case '?':
            fprintf(stderr, "Error!  Invalid option - %c\n", optopt);
            return(-1);
            break;
        case 'h':            
        default:
            showUsage();
            return(0); 
        }
     }
#endif
   ctx = moca_open(chipId);

    if (!ctx)
    {
        fprintf(stderr, "Error!  Unable to connect to moca instance\n");
        return(-3);
    }


   nRet = moca_get_policing_en(ctx, &polen);
   if (nRet != MOCA_API_SUCCESS)
   {
       moca_close(ctx);
       fprintf(stderr, "Error!  Internal\n");
       return(-4);
    }
    printf("POLICING is %s \n",( polen == 1? "enabled":"disabled"));


   moca_close(ctx);
   return(0);
}
