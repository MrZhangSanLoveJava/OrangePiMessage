# OrangePiMessage
OrangePi配合OLED将一些系统内容显示到屏幕上，可以显示
- 本机的IP地址
- soc的温度
- gpu的温度
- cpu用户使用率
- cpu系统使用率

现在还没想好再添加什么功能，因为是第一个版本的，所有有很多的Bug，大佬们可以自行修改。

# 版本

V1.0.0 基本功能实现了

# 使用方法

将下载好的包使用下面的命令进行解压：

```shell
unzip test.zip
```

然后进入目录后使用

```shell
make
```

进行编译，makefile文件是写好了的。

然后使用下面的命令即可运行

```shell
sudo ./main
```


