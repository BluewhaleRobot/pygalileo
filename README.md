# pygalileo [![Build Status](https://travis-ci.org/BluewhaleRobot/pygalileo.svg)](https://travis-ci.org/BluewhaleRobot/pygalileo)

Galileo navigation systemm python SDK

## 编译安装

### Windows

首先要保证系统已经安装完 Visual Studio 2017, Python且Python的安装路径为`C:\Python27`

如果没有安装Python可以通过下面的指令安装。以管理员身份打开Powershell,输入以下指令

```powershell
choco install python2 -y
```

下载GalileoSDK C++项目

```powershell
git clone https://github.com/bluewhalerobot/GalileoSDK --depth=1
```

下载本项目

```powershell
git clone https://github.com/bluewhalerobot/pygalileo --depth=1
```

开始编译

```powershell
cd pygalileo
MSBuild.exe pyGalileo.sln //p:configuration=release //p:platform=x64
```

编译完成后会在`x64\Release`文件夹中生成 `GalileoSDK.dll`和`pygalileo.pyd`文件。此文件即为伽利略Python SDK库文件。

### Linux

对于 Ubuntu 16.04 系统的用户需要先安装更新版本的Boost。Ubuntu 18.04的用户不需要安装

安装boost

```bash
wget -O boost.tar.gz https://dl.bintray.com/boostorg/release/1.69.0/source/boost_1_69_0.tar.gz
tar xzf boost.tar.gz
cd boost_1_69_0
sudo apt-get install build-essential g++ python-dev autotools-dev libicu-dev build-essential libbz2-dev libboost-all-dev
./bootstrap.sh --prefix=/usr/
./b2 -j8
sudo ./b2 install
```

安装伽利略C++ SDK, 安装方法可以参考[这里](https://github.com/bluewhalerobot/GalileoSDK)

下载编译项目源码

```bash
git clone https://github.com/bluewhalerobot/pygalileo --depth=1
cd pygalileo/pyGalileo
mkdir build
cd  build
cmake ..
make -j
```

注意：本项目可以支持Python3 和 Python2.7。只需要在编译时指定Python参数即可。默认使用Python2.7, 如果想要使用Python 3可以输入下面指令

```bash
cmake -DUSE_PYTHON2=OFF ..
make -j
```

编译完成会在编译文件夹内生成 `pygalileo.so`文件。此文件即为伽利略Python SDK库文件。

## 使用

把生成的库文件复制到自己的项目路径里面就可以向一般的python库一样使用了。
下面的例子向机器人发布测试消息。程序运行后可以在机器人上创建`/pub_test`话题
更多的例子可以参考`pyGalileo\python\galileo_test.py`文件

```python
import pygalileo
import time

sdk = pygalileo.SDK()
while True:
    servers = sdk.GetServersOnline()
    if len(servers) == 0:
        print("No Server Found")
    for server in servers:
        print(server.id)
        sdk.Connect("", True, 10000, None, None)
    sdk.PublishTest()
    time.sleep(1)
```