#include "myoled.h"

// 发送数据
char send_data(int fd, unsigned char data){
    int ret = 0;
    ret=wiringPiI2CWriteReg8(fd, DATA, data);     // 发送控制帧
    return ret;
}

// 发送命令
char send_cmd(int fd, unsigned char cmd){
    int ret;
    ret = wiringPiI2CWriteReg8(fd, CMD, cmd);
    return ret;
}

// 设置OLED的光标
void OLED_setcursor(int fd, unsigned char x, unsigned char y){
    send_cmd(fd, 0xB0 | y);         // 设置y的位置
    send_cmd(fd, 0x10 | ((x & 0xF0) >> 4));    // 设置x的高位置
    send_cmd(fd, 0x00 | (x & 0x0F));
}

// OLED清屏
void OLED_clear(int fd){
    unsigned char i, j;
    for (i = 0; i < 8; i++){
        OLED_setcursor(fd, 0, i);
        for (j = 0; j < 128; j++){
            send_data(fd, 0x00);
        }
    }
}

// OLED显示一个字符
void OLED_showchar(int fd, unsigned char x, unsigned char y, unsigned char Char){
    unsigned char i;
    OLED_setcursor(fd, (x - 1) * 8, (y - 1) * 2);
    for (i = 0; i < 8; i++){
        send_data(fd, OLED_F8x16[Char - ' '][i]);
    }
    OLED_setcursor(fd, (x - 1) * 8, (y - 1) * 2 + 1);
    for (i = 0; i < 8; i++){
        send_data(fd, OLED_F8x16[Char - ' '][i + 8]);
    }
}

// OLED显示字符串
void OLED_ShowString(int fd, int x, int y, const char* str){
    int i;
    for (i = 0; str[i] != '\0'; i++){
        OLED_showchar(fd, x, y, str[i]);
        if (x++ == 16){
            x = 1;
            y++;
        }
    }
}

// 初始化显示屏
void OLED_Init(int fd){
    send_cmd(fd, 0xAE);	//关闭显示
    printf("关闭显示\n");
	
	send_cmd(fd, 0xD5);	//设置显示时钟分频比/振荡器频率
	send_cmd(fd, 0xf0);
    printf("设置显示时钟分频比/振荡器频率\n");
	
	send_cmd(fd, 0xA8);	//设置多路复用率
	send_cmd(fd, 0x3F);
    printf("设置多路复用率\n");
	
	send_cmd(fd, 0xD3);	//设置显示偏移
	send_cmd(fd, 0x00);
    printf("设置显示偏移\n");
	
	send_cmd(fd, 0x40);	//设置显示开始行
    printf("设置显示开始行\n");
	
	send_cmd(fd, 0xA1);	//设置左右方向，0xA1正常 0xA0左右反置
    printf("设置左右方向，0xA1正常 0xA0左右反置\n");
	
	send_cmd(fd, 0xC8);	//设置上下方向，0xC8正常 0xC0上下反置
    printf("设置上下方向，0xC8正常 0xC0上下反置\n");

	send_cmd(fd, 0xDA);	//设置COM引脚硬件配置
	send_cmd(fd, 0x12);
    printf("设置COM引脚硬件配置\n");
	
	send_cmd(fd, 0x81);	//设置对比度控制
	send_cmd(fd, 0xFF);
    printf("设置对比度控制\n");

	send_cmd(fd, 0xD9);	//设置预充电周期
	send_cmd(fd, 0x22);
    printf("设置预充电周期\n");

	send_cmd(fd, 0xDB);	//设置VCOMH取消选择级别
	send_cmd(fd, 0x20);
    printf("设置VCOMH取消选择级别\n");

	send_cmd(fd, 0xA4);	//设置整个显示打开/关闭
    printf("设置整个显示打开/关闭\n");

	send_cmd(fd, 0xA6);	//设置正常/倒转显示
    printf("设置正常/倒转显示\n");

	send_cmd(fd, 0x8D);	//设置充电泵
	send_cmd(fd, 0x14);
    printf("设置充电泵\n");

	send_cmd(fd, 0xAF);	//开启显示
    printf("开启显示\n");
		
	OLED_clear(fd);				//OLED清屏
}