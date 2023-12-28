#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>
#include <string.h>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <array>

#define MAXRUNS 100 // number of runs for-loop access memory

#define MINBYTES (1 << 11) /* First working set size */ // 2kB
#define MAXBYTES (1 << 27) /* Last working set size */  // 128 Mb
#define MAXSTRIDE 20                                   /* Stride x8 bytes */
#define MAXLEN MAXBYTES / sizeof(long)

long data[MAXLEN];

// Clear cache by create another array and access it
#define CLEAR_CACHE_SIZE (1 << 19) // 2Mb array -> 512k ints elements
#define STRIDE_CLEAR_CACHE 8       // cache block size is 32 bytes = 8*4bytes (int)
static int array_to_clear_cache[CLEAR_CACHE_SIZE];
static int var;

std::string exec(const char* cmd) {
    std::array<char, 512> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void printf_cache_info(){
    std::string result_L1d = exec("lscpu | grep \"L1d cache:\"");
    std::string result_L2 = exec("lscpu | grep \"L2 cache:\"");
    std::string result_L3 = exec("lscpu | grep \"L3 cache:\"");
    std::cout<<std::endl;
    std::cout<<result_L1d<<std::endl;
    std::cout<<result_L2<<std::endl;
    std::cout<<result_L3<<std::endl;

}

static void clear_cache()
{
    int x = var;
    for (int i = 0; i < CLEAR_CACHE_SIZE; i += STRIDE_CLEAR_CACHE)
    {
        x += array_to_clear_cache[i];
    }
    var = x;
}

double read_clock_cpuinfo()
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
    return core_mhz;
}
void init_data(long *data, int n)
{
    for (int i = 0; i < n; i++)
    {
        data[i] = i;
    }
}

void test_access_memory(int num_elements, int stride, int runs)
{
    long result;
    for (int j = 0; j < runs; j++)
    {
        result = 0;
        for (int i = 0; i < num_elements; i += stride)
        {
            result += data[i];
        }
        volatile long temp; // volatile tell compiler not to optimize the loop
        temp = result;
    }
}

long double run_bandwidth(int size, int stride)
{
    int num_elements = size / sizeof(long);
    auto start = std::chrono::high_resolution_clock::now();
    test_access_memory(num_elements, stride, MAXRUNS);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    long double result = (long double)(size / stride);
    result *= MAXRUNS;
    result /= ((long double)microseconds);
    return result;
}

long double run_latency_ns(int size, int stride)
{
    int num_elements = size / sizeof(long);
    auto start = std::chrono::high_resolution_clock::now();
    test_access_memory(num_elements, stride, MAXRUNS);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    
    long double result = ((long double)microseconds)*1000.0 / (MAXRUNS*num_elements/stride);
    return result;
}

int main()
{
    int size, stride;
    double core_mhz;
    clear_cache();
    init_data(data, MAXLEN);
    test_access_memory(MAXLEN,1,5); //warm up cache

    core_mhz = read_clock_cpuinfo();
    printf("Clock frequency read from cpuinfo is: %.1f MHz\n",core_mhz);
    printf_cache_info();
    printf("\n");
    // Test bandwidth
    printf("Throughput/Bandwidth with different buffer size and stride (MB/sec)\n");

    printf("\t");
    for (stride = 1; stride<= MAXSTRIDE; stride ++){
        printf("s%d\t",stride);
    }
    printf("\n");

    for (size = MAXBYTES; size >= MINBYTES; size >>=1){
        if (size >=(1<<20)){ //Mb
            printf("%dm\t",size/(1<<20));
        }
        else{
            printf("%dk\t",size/1024);
        }
        for (stride = 1; stride<=MAXSTRIDE; stride++){
            printf("%.0Lf\t",run_bandwidth(size,stride));
        }
        printf("\n");
        
    }

    sleep(3);
    printf("\n---------------------------------------------------------\n");


    // Test latency
    printf("Latency with different buffer size and stride (nano seconds)\n");

    printf("\t");
    for (stride = 1; stride<= MAXSTRIDE; stride ++){
        printf("s%d\t",stride);
    }
    printf("\n");

    for (size = MAXBYTES; size >= MINBYTES; size >>=1){
        if (size >=(1<<20)){ //Mb
            printf("%dm\t",size/(1<<20));
        }
        else{
            printf("%dk\t",size/1024);
        }
        for (stride = 1; stride<=MAXSTRIDE; stride++){
            printf("%.4Lf\t",run_latency_ns(size,stride));
        }
        printf("\n");
        
    }

    return 0;
}

