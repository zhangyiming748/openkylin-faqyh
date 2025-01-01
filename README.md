# FAQYH

## 简介

FAQYH（FAQ your hardware） 是一个非常简单的命令行工具，快速获取计算机硬件信息，并输出为适合提交issue和发送的格式，用户可以在本机一键运行并将生成的文件发送给FAQ SIG群负责人，方便FAQ SIG成员记录和排查问题。

注意：本工具功能非常简单，仅用于获取一些基本信息，更多详细信息推荐使用专业工具，如`hardinfo`等。

## 使用方法

打开终端，输入以下命令：

```bash
faqyh
```

即可获取计算机硬件信息输出到终端，并自动复制到剪贴板。

输出示例：

```
设备：Dell Inc. Dell G15 5515 笔记本电脑
操作系统：openKylin 2.0 SP1
内核版本：6.6.10 
CPU设备：AMD Ryzen 7 5800H with Radeon Graphics 8 核心 16 线程
GPU设备： 
GPU1: NVIDIA Corporation GeForce RTX 3060 Mobile / Max-Q
GPU2: Advanced Micro Devices, Inc. [AMD/ATI]  Vega Series / Radeon Vega Mobile Series
内存设备：32 GB
磁盘设备：
磁盘1: nvme0n1 476 GB
网卡设备：
网卡1: Intel Corporation Wi-Fi 6 AX200
网卡2: Realtek Semiconductor Co., Ltd. RTL8125 2.5GbE Controller
```

如果发现有信息缺失，或者信息不准确，请提交[issue](https://gitee.com/openkylin/faqyh/issues)，非常感谢您的反馈！

## 安装方法

### 使用openKylin软件源安装

```bash
sudo apt install faqyh
```

### 通过源码构建并安装

```bash
git clone https://gitee.com/openkylin/faqyh
cd faqyh
mkdir build
cd build
cmake ..
make
sudo make install
```

### 安装运行依赖

- xsel
- wl-clipboard

安装依赖：
```bash
sudo apt install xsel wl-clipboard
```

### 构建debian包，并安装

```bash
dpkg-buildpackage -S -nc --no-sign
dpkg-buildpackage -us -uc -b
dh clean
sudo dpkg -i ../faqyh_xxx_amd64.deb
```

构建完成后，会在源码上一级目录生成一个.deb文件，可以直接安装。

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
- /proc/version

CPU：
- /proc/cpuinfo

GPU：
- /sys/class/drm/card0/device/vendor
- /sys/class/drm/card0/device/device


内存：
- /proc/meminfo

硬盘：
- /sys/block/disk/size


整机
- /sys/class/dmi/id/product_name 

网卡
- /sys/class/net/<interface>/device/


厂商根据：/usr/share/hwdata/pci.ids 获取


## 开源协议

本项目遵守MIT许可证，请参考[LICENSE](LICENSE.md)文件。