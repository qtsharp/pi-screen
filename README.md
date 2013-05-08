pi-screen
=========

本程序用于树莓派通过GPIO连接1602的效果演示，使用wiringPi库和其附带的LCD库进行GPIO和1602的操作。

自行编译需要安装wiringPi库：
    git clone git://git.drogon.net/wiringPi 
    cd wiringPi 
    git pull origin 
    cd wiringPi 
    ./build 

编译：
    gcc 1602.c -o 1602 -L lib -l wiringPi

运行：
    sudo ./1602 hello
    
![线路连接图](https://github.com/qtsharp/pi-screen/blob/master/lcd8_bb.png)

[使用示例](https://github.com/qtsharp/pi-screen/blob/master/1602.c)
