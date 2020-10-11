# 第一章 计算机系统漫游
## hello world程序
* 编译系统 [code](./code/hello)
  * 预处理器
  * 编译器
  * 汇编器
  * 链接器
![compile](pictures/compileSystem.png)

* 计算机系统中的抽象
  * 文件是对IO设备的抽象
  * 虚拟内存是对主存和磁盘IO设备的抽象
  * 进程是对处理器，主存和IO设备的抽象，是对正在运行的程序的抽象
![abstract](./pictures/abstract.png)


# 第二章 信息的表示和处理
## 信息存储
* 字节(byte)、字(word)和字长(word size)
  * 字节，8位的块，最小的可寻址的内存单位
  * 虚拟地址以字来编码，所以字长决定了虚拟地址空间的最大大小。每台计算机都有一个字长，指明指针的长度。 对于一个字长为w位的机器，虚拟地址范围为(0 ~ 2^w - 1)
  * 例子: [code](./code/size/main.cpp)