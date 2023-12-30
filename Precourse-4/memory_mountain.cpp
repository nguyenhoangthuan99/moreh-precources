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
#include <thread>
#include <mutex>
#include <fstream>
#include <vector>
#include <cmath>

std::mutex myMutex;
#define MAXRUNS 100 // number of runs for-loop access memory

#define MINBYTES (1 << 11) /* First working set size */ // 2kB
#define MAXBYTES (1 << 25) /* Last working set size */  // 32 Mb
#define MAXSTRIDE 32                                    /* Stride x8 bytes */
#define MAXLEN MAXBYTES / sizeof(long)

#define DRAM_MINBYTES (1 << 26) /* First working set size */ // 64 Mb
#define DRAM_MAXBYTES (1 << 29) /* Last working set size */  // 512 Mb
#define DRAM_MAXSTRIDE 32                                    /* Stride x8 bytes */
#define DRAM_MAXLEN DRAM_MAXBYTES / sizeof(long)
#define FILENAME "file/8192k.txt"

long data[DRAM_MAXLEN];

// Clear cache by create another array and access it
#define CLEAR_CACHE_SIZE (1 << 19) // 2Mb array -> 512k ints elements
#define STRIDE_CLEAR_CACHE 8       // cache block size is 32 bytes = 8*4bytes (int)
static int array_to_clear_cache[CLEAR_CACHE_SIZE];
static int var;

std::string exec(const char *cmd)
{
    std::array<char, 512> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result;
}

void printf_system_info()
{
    std::string result_cpuMHz = exec("cat /proc/cpuinfo | grep \"cpu MHz\" | head -n1");
    std::string result_L1d = exec("lscpu | grep \"L1d cache:\"");
    std::string result_L2 = exec("lscpu | grep \"L2 cache:\"");
    std::string result_L3 = exec("lscpu | grep \"L3 cache:\"");
    std::string result_mem = exec("cat /proc/meminfo | grep MemTotal");
    std::string result_disk = exec("df -h .");
    std::string result_num_cpu = exec("lscpu | grep \"CPU(s):\"");
    std::cout << std::endl;
    std::cout << result_num_cpu;
    std::cout << result_cpuMHz << std::endl;
    std::cout << result_L1d;
    std::cout << result_L2;
    std::cout << result_L3;
    std::cout << result_mem;
    std::cout << "Disk usage info:" << std::endl;
    std::cout << result_disk << std::endl;
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

void init_data(long *data, int n)
{
    for (int i = 0; i < n; i++)
    {
        data[i] = i;
    }
}
// #pragma GCC push_options
// #pragma GCC optimize("O0")
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
// #pragma GCC pop_options

// #pragma GCC push_options
// #pragma GCC optimize("O0")
// void test_access_memory_dram(int num_elements, int stride, int runs)
// {
//     long result;

//     for (int j = 0; j < runs; j++)
//     {
//         result = 0;
//         for (int i = 0; i < num_elements; i += stride)
//         {
//             result += data[i];
//         }
//         volatile long temp; // volatile tell compiler not to optimize the loop
//         temp = result;
//     }
// }
// #pragma GCC pop_options

// #pragma GCC push_options
// #pragma GCC optimize("O0")
void test_read_file(const char *filename, int runs)
{

    for (int i = 0; i < runs; i++)
    {

        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<char> buffer(size);
        file.read(buffer.data(), size);
        if (file.read(buffer.data(), size))
        {
            /* worked! */
            buffer.clear();
        }
    }
}
// #pragma GCC pop_options
std::streamsize sizeoffile(const char *filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

long double run_bandwidth(int size, int stride)
{
    long num_elements = (long)size / sizeof(long);
    auto start = std::chrono::high_resolution_clock::now();
    test_access_memory(num_elements, stride, MAXRUNS * 1<<(log2(MAXBYTES) - log2(size)));
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    long double result = (long double)(size / stride);
    result *= MAXRUNS * 1<<(log2(MAXBYTES) - log2(size));
    result /= ((long double)microseconds);
    return result;
}

long double run_multithread_bandwidth(int size, int stride)
{
    long num_elements = (long)size / sizeof(long);
    auto start = std::chrono::high_resolution_clock::now();
    std::thread th1(test_access_memory, num_elements, stride, (int)MAXRUNS / 2);
    std::thread th2(test_access_memory, num_elements, stride, (int)MAXRUNS / 2);
    th1.join();
    th2.join();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    long double result = (long double)(size / stride);
    result *= MAXRUNS;
    result /= ((long double)microseconds);
    return result;
}

long double run_read_file_bandwidth(const char *filename)
{
    long long size = (long)sizeoffile(filename);
    // std::cout << "filesize " << size << std::endl;
    test_read_file(filename, 5); // warm up
    auto start = std::chrono::high_resolution_clock::now();
    test_read_file(filename, MAXRUNS*1<<(log2(MAXBYTES) - log2(size)));
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    long double result = (long double)size * MAXRUNS* 1<<(log2(MAXBYTES) - log2(size)) / (long double)microseconds;
    return result;
}
long double run_read_file_latency(const char *filename)
{
    // long long size = (long)sizeoffile(filename);
    // std::cout << "filesize " << size << std::endl;
    test_read_file(filename, 5); // warm up
    auto start = std::chrono::high_resolution_clock::now();
    test_read_file(filename, MAXRUNS* 1<<(log2(MAXBYTES) - log2(size)));
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    // std::cout<<microseconds<<std::endl;
    long double result = (long double)microseconds / (MAXRUNS* 1<<(log2(MAXBYTES) - log2(size)) * 1000);
    return result;
}
long double run_multithread_latency(int size, int stride)
{
    long num_elements = (long)size / sizeof(long);
    auto start = std::chrono::high_resolution_clock::now();
    std::thread th1(test_access_memory, num_elements, stride, (long)MAXRUNS / 2);
    std::thread th2(test_access_memory, num_elements, stride, (long)MAXRUNS / 2);
    th1.join();
    th2.join();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    // std::cout<<microseconds<< " " <<(long double) microseconds<<std::endl;
    long double result = (((long double)microseconds) / (MAXRUNS * num_elements / (long)stride)) * 1000.;
    return result;
}

long double run_latency_ns(int size, int stride)
{
    long num_elements = (long)size / sizeof(long);
    auto start = std::chrono::high_resolution_clock::now();
    test_access_memory(num_elements, stride, MAXRUNS * 1<<(log2(MAXBYTES) - log2(size)));
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    long double result = ((long double)microseconds * 1000) / (MAXRUNS * num_elements * * 1<<(log2(MAXBYTES) - log2(size)) / (long)stride);
    return result;
}

void multi_thread_dram_benchmark()
{
    std::cout << "\n---------------------------------------------------------------------------------------------------------\n";
    int size, stride;
    printf("Throughput/Bandwidth of DRAM with different buffer size and stride (MB/sec)\n");

    printf("\t");
    for (stride = 1; stride <= DRAM_MAXSTRIDE; stride += 2)
    {
        printf("s%d\t", stride);
    }
    printf("\n");
    for (size = DRAM_MAXBYTES; size >= DRAM_MINBYTES; size >>= 1)
    {
        if (size >= (1 << 20))
        { // Mb
            printf("%dm\t", size / (1 << 20));
        }
        else
        {
            printf("%dk\t", size / 1024);
        }
        for (stride = 1; stride <= DRAM_MAXSTRIDE; stride += 2)
        {
            printf("%.0Lf\t", run_multithread_bandwidth(size, stride));
        }
        printf("\n");
    }

    std::cout << "\n---------------------------------------------------------------------------------------------------------\n";

    printf("Latency of DRAM with different buffer size and stride (nano seconds)\n");

    printf("\t");
    for (stride = 1; stride <= DRAM_MAXSTRIDE; stride += 2)
    {
        printf("s%d\t", stride);
    }
    printf("\n");
    for (size = DRAM_MAXBYTES; size >= DRAM_MINBYTES; size >>= 1)
    {
        if (size >= (1 << 20))
        { // Mb
            printf("%dm\t", size / (1 << 20));
        }
        else
        {
            printf("%dk\t", size / 1024);
        }
        for (stride = 1; stride <= DRAM_MAXSTRIDE; stride += 2)
        {
            printf("%.3Lf\t", run_multithread_latency(size, stride));
        }
        printf("\n");
    }
}

void disk_benchmark()
{
    std::cout << "\n---------------------------------------------------------------------------------------------------------\n";
    int size;
    printf("Throughput and latency read of Disk with different file size  \n");

    printf("\t");
    // for (stride = 0; stride <= DRAM_MAXSTRIDE; stride++)
    // {
    printf("bwidth(MB/s)\tlatency(ms)");
    // }
    printf("\n");
    for (size = MAXBYTES; size >= MINBYTES; size >>= 1)
    {
        if (size >= (1 << 20))
        { // Mb
            printf("%dm\t", size / (1 << 20));
        }
        else
        {
            printf("%dk\t", size / 1024);
        }
        // for (stride = 0; stride <= DRAM_MAXSTRIDE; stride++)
        // {
        std::string formatted_str = std::to_string((int)size / 1024);
        std::string extension = "k.txt";
        std::string folder = "file/";
        std::string fname_str = folder + formatted_str + extension;
        const char *fname = fname_str.c_str();
        printf("%.0Lf\t\t", run_read_file_bandwidth(fname));
        printf("%.3Lf\t", run_read_file_latency(fname));
        // }
        printf("\n");
    }
}

void cache_benchmark()
{
    int size, stride;
    printf("Throughput/Bandwidth with different buffer size and stride (MB/sec)\n");

    printf("\t");
    for (stride = 1; stride <= MAXSTRIDE; stride += 2)
    {
        printf("s%d\t", stride);
    }
    printf("\n");

    for (size = MAXBYTES; size >= MINBYTES; size >>= 1)
    {
        if (size >= (1 << 20))
        { // Mb
            printf("%dm\t", size / (1 << 20));
        }
        else
        {
            printf("%dk\t", size / 1024);
        }
        for (stride = 1; stride <= MAXSTRIDE; stride += 2)
        {
            printf("%.0Lf\t", run_bandwidth(size, stride));
        }
        printf("\n");
    }

    sleep(3);
    printf("\n---------------------------------------------------------------------------------------------------------\n");

    // Test latency
    printf("Latency with different buffer size and stride (nano seconds)\n");

    printf("\t");
    for (stride = 1; stride <= MAXSTRIDE; stride += 2)
    {
        printf("s%d\t", stride);
    }
    printf("\n");

    for (size = MAXBYTES; size >= MINBYTES; size >>= 1)
    {
        if (size >= (1 << 20))
        { // Mb
            printf("%dm\t", size / (1 << 20));
        }
        else
        {
            printf("%dk\t", size / 1024);
        }
        for (stride = 1; stride <= MAXSTRIDE; stride += 2)
        {
            printf("%.4Lf\t", run_latency_ns(size, stride));
        }
        printf("\n");
    }
}

int main()
{

    // double core_mhz;
    clear_cache();
    init_data(data, DRAM_MAXLEN);
    test_access_memory(DRAM_MAXLEN, 1, 5); // warm up cache

    // core_mhz = read_clock_cpuinfo();
    // printf("Clock frequency read from cpuinfo is: %.1f MHz\n", core_mhz);
    printf_system_info();
    printf("\n");
    // Test bandwidth
    cache_benchmark();
    multi_thread_dram_benchmark();
    disk_benchmark();

    return 0;
}
