#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>
#include <string.h>

#define MAXRUNS 1000

#define MINBYTES (1 << 11) /* First working set size */ // 2kB
#define MAXBYTES (1 << 27) /* Last working set size */  // 256 Mb
#define MAXSTRIDE 15                                    /* Stride x8 bytes */
#define MAXLEN MAXBYTES / sizeof(long)

long data[MAXLEN];
double read_clock_cpuinfo(int verbose)
{
    double core_mhz;
    static char buf[512];
    FILE *fp = fopen("/proc/cpuinfo", "r");
    core_mhz = 0.0;

    if (!fp)
    {
        fprintf(stderr, "Open /proc/cpuinfo error\n");
        core_mhz = 1.0;
        return core_mhz;
    }
    while (fgets(buf, 512, fp))
    {
        if (strstr(buf, "cpu MHz"))
        {
            double cpu_mhz = 0.0;
            sscanf(buf, "cpu MHz\t: %lf", &cpu_mhz);
            core_mhz = cpu_mhz;
            break;
        }
    }
    fclose(fp);
    if (core_mhz == 0.0)
    {
        fprintf(stderr, "Open /proc/cpuinfo error\n");
        core_mhz = 1000.0;
        return core_mhz;
    }
}
void init_data(long *data, int n)
{
    for (int i = 0; i < n; i++)
    {
        data[i] = i;
    }
}

int main()
{

    return 0;
}