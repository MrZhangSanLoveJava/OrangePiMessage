#include <stdio.h>
#include "myoled.h"
#include "getSystem.h"
#include <signal.h>

int menu = 0, flag = 0;

void time_handle(int signum){
    // 定时器处理函数
    menu++;
    flag = 1;
    if (menu == 2){
        menu = 0;
    }
    alarm(10);
}

int main(){
    int fd, i;
    char name[][6] = {"wlan0", "eth0"};
    char message[24] = "127.0.0.1";
    char Ipmessage[28], Tempmessage[30], cpumessage[20];
    struct GetTemp temp;
    struct CPU cpu;
    wiringPiSetup();
    fd = wiringPiI2CSetupInterface("/dev/i2c-2", I2CADDRESS);
    if (fd < 0){
        printf("wiringPiI2CSetup error\n");
        return -1;
    }
    // 获取IP地址
    for (i = 0; i < 2; i++){
        if (getIP(name[i], message, 24) == 1){
            printf("%s\n", message);
            break;
        }
    }
    sprintf(Ipmessage, "IP:%s", message);
    // 获取温度
    OLED_Init(fd);
    signal(SIGALRM, time_handle);
    alarm(10);
    while(1){
        if (menu == 0){
            if (flag){
                OLED_clear(fd);
                flag = 0;
            }
            getTemp(&temp);
            delayMicroseconds(50000);
            OLED_ShowString(fd, 1, 1, "PI Message:");
            OLED_ShowString(fd, 1, 2, Ipmessage);
            sprintf(Tempmessage, "soc:%.2f C", temp.soc);
            OLED_ShowString(fd, 1, 3, Tempmessage);
            sprintf(Tempmessage, "gpu:%.2f C", temp.gpu);
            OLED_ShowString(fd, 1, 4, Tempmessage);
        }
        else if (menu){
            if (flag){
                OLED_clear(fd);
                flag = 0;
            }
            getCPU(&cpu);
            delayMicroseconds(50000);
            OLED_ShowString(fd, 1, 1, "PI CPU:");
            sprintf(cpumessage, "user:%-3.2f%%", cpu.us);
            OLED_ShowString(fd, 1, 2, cpumessage);
            sprintf(cpumessage, "sys :%.2f%%", cpu.sy);
            OLED_ShowString(fd, 1, 3, cpumessage);
        }
        
    }
    return 0;
}
