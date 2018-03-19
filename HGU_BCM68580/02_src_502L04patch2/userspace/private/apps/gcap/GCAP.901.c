#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <getopt.h>

#include <mocalib.h>

static char *chipId = NULL;    // -i option
static int persistent = 0;     // -M option
static int reset = 0;          // -r option
static char *onoff = NULL;

GCAP_GEN static void showUsage()
{
    printf("Usage: GCAP.901 <ON/[OFF]> [-M] [-r] [-h]\n\
Set Golden Node to operate in PSM (internal power-save) mode.\n\
Default values will be used if parameters are not supplied.\n\
Note that resetting SoC is required for configuration to take effect.\n\
\n\
Options:\n\
 ON/OFF Turn ON or OFF PSM mode (default OFF)\n\
  -M    Make configuration changes permanent\n\
  -r    Reset SoC to make configuration changes effective\n\
  -h    Display this help and exit\n");
}

GCAP_GEN int GCAP_901_main(int argc, char **argv)
{
    int ret;
    void *ctx;

    chipId = NULL;
    onoff = NULL;
    persistent = 0;
    reset = 0;

    // ----------- Parse parameters

   if ((argc < 2) || (argv[1] == NULL) || (argv[1][0] == '-'))
    {
        onoff = "OFF";
    }
    else
    {
        onoff = argv[1];
    }
    if ((strcmp(onoff, "ON") != 0) && (strcmp(onoff, "OFF") != 0))
    {
        printf("Error!  Invalid parameter - %s\n",onoff);
        return(-3);
    }

#if defined(STANDALONE) 
    
   int i;
   for (i=1; i < argc; i++)
   {
      if (strcmp(argv[i], "-i") == 0)
      {
         i++;
         chipId = argv[i];
      }
      else if (strcmp(argv[i], "-M") == 0)
      {
         persistent = 1;
      }
      else if (strcmp(argv[i], "-r") == 0)
      {
         reset = 1;
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

    while((ret = getopt(argc, argv, "Mrhi:")) != -1) 
    {
        switch(ret) 
        {
        case 'i':
            chipId = optarg;
            break;
        case 'M':
            persistent = 1;
            break;
        case 'r':
            reset = 1;
            break;
        case '?':
            printf( "Error!  Invalid option - %c\n", optopt);
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
        printf( "Error!  Unable to connect to moca instance\n");
        return(-2);
    }

    if (strcmp(onoff, "OFF") == 0)
    {
        ret = moca_set_power_save_mechanism_dis(ctx, 1);
    }
    else
    {
        ret = moca_set_power_save_mechanism_dis(ctx, 0);
    }
        
    if (ret != MOCA_API_SUCCESS)
    {
         moca_close(ctx);
         printf( "Error!  Internal error 1\n");
         return(-3);
    }    
 
    // ----------- Finish
 

    if (reset)
    {
        ret = moca_set_restart(ctx);
    }
    
    if (ret != MOCA_API_SUCCESS)
    {
        moca_close(ctx);
        printf( "Error!  Internal 2\n");
        return(-4);
    }

    if (persistent)
    {
       ret = moca_set_persistent(ctx);
       if (ret != MOCA_API_SUCCESS)
       {
          moca_close(ctx);
          printf( "Error!  Unable to save persistent parameters\n");
          return(-5);
       }
    }
    moca_close(ctx);

    return(0);
}

