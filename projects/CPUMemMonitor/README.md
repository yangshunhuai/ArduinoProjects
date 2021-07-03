# CPUMemMonitor 系统资源监视器

## 设计功能
* 在一块LCD1602显示屏上以进度条和数字形式显示CPU和内存使用百分率。
* 支持通过串口实时刷新

## 电路图
见Sketch文件夹，有PDF格式的文档和Proteus源文件。

## 使用方法
1. 按照电路图连接电路。
2. 编译源代码（用Arduino IDE）并刷写到Arduino板子或者MCU上。
3. 将板子连接到电脑。
4. 如果电脑是Windows，在设备管理器里找到`端口（COM和LPT）`，找到Arduino XXX这个设备（XXX取决于用的是什么板子）或者你的ISP下载器，点开，记下COMx这个串口号码。
   
   如果是Unix和类Unix，在`/dev`文件夹下找到Arduino设备即可。
   
   一般情况下，macOS是`/dev/cu.usbmodemXXX`，Linux是`/dev/ttyUSBX`。
5. 在电脑上打开`MonitorServer/MonitorServer.py`，把port变量设为刚才的串口设备名。
6. 电脑上装好Python并且确保pyserial包已经装好。没有装好的话用`pip install pyserial`安装。
7. 用Python打开这个MonitorServer.py。
8. LCD屏幕会先闪烁一下，这是打开串口后Arduino自动复位的标志。然后即可正常运行。

## 疑难解答
唯一可能出现的故障是服务器程序一闪而过，这有四种可能：

* Python没有安装。
* pyserial库没有安装。
* 串口设置不对。
* 设备没有正确连接。

1. 先检查Python是否安装，可以在开始菜单中寻找Python或者在终端中输入Python验证。
2. 打开Python REPL，输入`import serial`检查pyserial是否安装。
3. 再次检查串口设备名称是否正确。
4. 重新编译刷写程序到板子检查。
5. 更换一条数据线（有的厂家为了节约成本把数据线中的TX和RX信号线砍了）。
