#ifndef __GETSYSTEM_H
#define __GETSYSTEM_H

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define SOC_SRC "/sys/class/thermal/thermal_zone0/temp"
#define GPU_SRC "/sys/class/thermal/thermal_zone1/temp"

struct GetTemp{
    float soc;
    float gpu;
};

struct CPU{
    float us;    // 用户使用
    float sy;    // 系统使用
};

int getIP(char* name, char* buf, int n);
void getTemp(struct GetTemp* gettemp);
void getCPU(struct CPU* cpu);

#endif
