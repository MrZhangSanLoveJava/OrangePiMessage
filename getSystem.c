#include "getSystem.h"

// 去除获取的IP地址的杂质
void filtration(char* buf, char* str){
    int i, j = 0;
    for (i = 0; buf[i]; i++){
        if (buf[i] == 't' && buf[i + 1] == ' '){
            i += 2;
            do{
                str[j++] = buf[i++];
            }while(buf[i] != ' ');
            str[j] = '\0';
            return;
        }
    }
}

// 去除CPU使用率的杂质
void filtrationCPU(char* buf, struct CPU* cpu){
    int i, flag = 0;
    for (i = 0; buf[i]; i++){
        if (buf[i] == ':' && buf[i + 1] == ' ' && flag == 0){
            i += 2;
            cpu->us = (buf[i] == ' '?0:buf[i] - '0') * 10 + (buf[i + 1] - '0') + (buf[i + 3] - '0') * 0.1;
            i += 2;
            flag = 1;
        }
        else if (buf[i] == ',' && buf[i + 1] == ' ' && flag == 1){
            i += 2;
            cpu->sy = (buf[i] == ' '?0:buf[i] - '0') * 10 + (buf[i + 1] - '0') + (buf[i + 3] - '0') * 0.1;
            break;
        }
    }
}

// 获取本机的IP地址
int getIP(char* name, char* buf, int n){
    FILE* fd = NULL;
    char message[128];
    char str[50];
    sprintf(str, "ifconfig %s |grep inet\\ ", name);
    fd = popen(str, "r");
    fgets(message, 128, fd);
    sprintf(str, "        inet");
    if (strncmp(message, str, 8) != 0){
        pclose(fd);
        return -1;
    }
    // memcpy(buf, &message[13], 24);
    filtration(message, buf);
    pclose(fd);
    return 1;
}

// 获取温度
void getTemp(struct GetTemp* gettemp){
    char buf[5];
    float temp;
    int fd = open(SOC_SRC, O_RDONLY);
    read(fd, buf, 5);
    temp = (buf[0] - '0') * 10000 + (buf[1] - '0') * 1000 + (buf[2] - '0') * 100 + (buf[3] - '0') * 10 + (buf[4] - '0');
    gettemp->soc = temp / 1000;
    fd = open(GPU_SRC, O_RDONLY);
    read(fd, buf, 5);
    temp = (buf[0] - '0') * 10000 + (buf[1] - '0') * 1000 + (buf[2] - '0') * 100 + (buf[3] - '0') * 10 + (buf[4] - '0');
    gettemp->gpu = temp / 1000;
    close(fd);
}

// 获取CPU占用情况
void getCPU(struct CPU* cpu){
    FILE* fd = NULL;
    char buf[64];
    fd = popen("top -bn 1 -i -c |grep %Cpu", "r");
    fgets(buf, 64, fd);
    filtrationCPU(buf, cpu);
}
