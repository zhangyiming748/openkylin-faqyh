# FAQYH

## 简介

FAQYH（FAQ your hardware） 是一个非常简单的命令行工具，用于帮助用户快速获取计算机硬件信息，并输出为适合提交issue和发送的格式，用户可以在本机一键运行并将生成的文件发送给FAQ SIG群负责人，方便FAQ SIG成员记录和排查问题。本项目不依赖任何第三方库，纯C++实现，使用CMake构建。

注意：本工具功能非常简单，仅用于获取一些基本信息，更多详细信息推荐使用专业工具，如`hardinfo`等。

## 项目结构

项目结构如下：

```
├── CMakeLists.txt
├── READMD.md
├── LICENSE.md
├── debian
│   ├── changelog
│   ├── compat
│   ├── control
│   └── rules
├── include  // 头文件
│   ├── formatter.hpp
│   ├── hwinfo.hpp
│   ├── logger.hpp
│   └── main.hpp
└── src  // 源文件
    ├── formatter.cpp  // 格式化输出内容
    ├── hwinfo.cpp  // 获取硬件信息
    ├── logger.cpp  // 终端输出
    └── main.cpp  // 主程序

```

分别从以下文件获取信息：

OS：
- /etc/os-release

CPU：
- /proc/cpuinfo

GPU：
- /sys/class/drm/card0/device/vendor
- /sys/class/drm/card0/device/device


内存：
- /proc/meminfo

硬盘：
- /sys/block/<disk>/size


整机
- /sys/class/dmi/id/product_name 

网卡
- /sys/class/net/<interface>/device/
厂商根据：/usr/share/hwdata/pci.ids 获取



## 构建debian包

```bash
dpkg-buildpackage -S -nc --no-sign
dpkg-buildpackage -us -uc -b
dh clean
```

构建完成后，会在源码上一级目录生成一个.deb文件，可以直接安装。

## 使用方法

打开终端，输入以下命令：

```bash
faqyh
```

按照提示输入即可。

## 输出格式

普通输出格式如下：

```
系统: openKylin 2.0 SP1
CPU: 
整机: Dell G15 5515
网卡: Realtek Semiconductor Co., Ltd. RTL8111/8168/8411 PCI Express Gigabit Ethernet Controller
内存: 16GB
硬盘: 512GB
```

## TODO

- [x] 获取CPU信息
- [x] 获取OS信息
- [x] 获取网卡信息
- [x] 获取整机信息
- [ ] 获取主板信息
- [ ] 获取显卡信息
- [x] 获取内存信息
- [x] 获取硬盘信息
- [ ] 输出为适合提交issue的格式
- [ ] 输出为适合发送的格式
- [ ] 输出为FAQ数据库JSON格式