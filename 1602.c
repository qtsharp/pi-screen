#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <wiringPi.h>
#include <lcd.h>

/***********************************
本程序用于树莓派通过GPIO连接1602的效
果演示，使用wiringPi库和其附带的LCD
库进行GPIO和1602的操作。

                 created by @qtsharp
************************************
示例1：
    $sudo ./l602
    屏幕显示：
        ------------------
        |  Raspberry Pi! |
        |51.9C 215/477MB |
        ------------------
        
示例2：
    $sudo ./1602 QtSharp
    屏幕显示：
        ------------------
        |QtSharp         |
        |51.9C 215/477MB |
        ------------------

示例3：
    $sudo ./1602 \ \ Hello\ World
    屏幕显示：
        ------------------
        |  hello world   |
        |51.9C 215/477MB |
        ------------------

************************************/




int main (int args, char *argv[])
{
    if (wiringPiSetup () == -1)
        exit (1) ;
    int fd = lcdInit (2, 16, 8,  11,10 , 0,1,2,3,4,5,6,7) ;
    if (fd == -1)
    {
        printf ("lcdInit 1 failed\n") ;
        return 1 ;
    }
    sleep (1) ; //显示屏初始化
    
    lcdPosition (fd, 0, 0); lcdPuts (fd, "  Raspberry Pi!"); //启动信息
    sleep(1);
    
    if(argv[1])
    {
        lcdPosition (fd, 0, 0) ;
        lcdPuts (fd, "                ") ; //清空第一行
        lcdPosition (fd, 0, 0) ; lcdPuts (fd, argv[1]) ; //命令行参数显示至第一行
    } 

    FILE *fp;
    char temp_char[15]; //树莓派温度
    char Total[20]; //总内存量
    char Free[20]; //空闲内存量
    
    while(1)
    {
        fp=fopen("/sys/class/thermal/thermal_zone0/temp","r"); //读取树莓派温度
        fgets(temp_char,9,fp);
        float Temp;
        Temp=atof(temp_char)/1000;
        lcdPosition (fd, 0, 1);lcdPrintf (fd, "%3.1fC", Temp) ; 
        fclose(fp);

        fp=fopen("/proc/meminfo","r"); //读取内存信息
        fgets(Total,19,fp);
        fgets(Total,4,fp);
        fgets(Free,9,fp);
        fgets(Free,19,fp);
        fgets(Free,4,fp);
        lcdPosition (fd, 6, 1);
        lcdPrintf (fd, "%3d/%3dMB", atoi(Free),atoi(Total)) ;
        fclose(fp);
        
        sleep(1);
    }

    return 0;
    
}
