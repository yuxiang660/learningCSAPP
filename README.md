# 第一章 计算机系统漫游
## hello world程序
* 编译系统 [code](./code/chapter1/Makefile)
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
  * 例子: [code](./code/chapter2/size/main.cpp)
* 整数表示
  * 无符号数，最高位权重是1
  * 有符号数，最高位权重是-1
  * 有符号数和无符号数运算，C语言默认将两个数都视作非负的无符号数。例子：[code](./code/chapter2/main.cpp)
* 小数表示
  * 定点表示法：二进制小数
  * 浮点表示法：符号，尾数，阶码
  ![float](./pictures/float.png)

# 第三章 程序的机器级表示
## 程序编码
* 机器级代码，例子：[code](./code/chapter3/Makefile)
  * 汇编与目标代码
    * `objdump -d mstore.o`可以获得汇编代码与机器代码的对应关系
    * `gdb mstore.o` and `x/14xb multstore`，同样可获得汇编代码`multstore`对应的机器代码
  * 反汇编可执行文件
    * `objdump -d main`可以反汇编出可执行文件的汇编代码，与目标文件的反汇编代码的不同之处在于：
      * 左边列出的地址不同
      * `callq`指令填上了调用函数`mult2`需要的地址
  * 汇编文件`mstore.s`
    * 以`.`开头的语句都是伪指令，可忽略
## 汇编语法
* 16个64位主寄存器<br>
![16_registers](./pictures/16_registers.png)
* 操作数(汇编代码的数据源)指示符
  * 立即数(immediate)，表示常数，如：`$0x1F`
  * 寄存器(register)，表示某个寄存器的内容，`R[r]`
  * 内存引用，`M[Addr]`
  ![operands](./pictures/operands.png)
* 数据传送指令<br>
![move](./pictures/move.png)
  * 不支持内存到内存移动，这个要两条指令实现
  * examples
  ![mov_example](./pictures/mov_example.png)
* 压入和弹出栈数据<br>
![push_pop](./pictures/push_pop.png)
  * example for `pushq %rax` and `popq %rdx`
  ![push_pop_example](./pictures/push_pop_example.png)
* 算术和逻辑操作<br>
四组操作：
  * 加载有效地址: 从内存读数据到寄存器(movq的变形)
  * 一元操作
  * 二元操作
  * 移位
  ![arithmetic](./pictures/arithmetic.png)
* 条件码<br>
![condition](./pictures/condition.png)

## 函数的调用过程
* 运行时栈
  * 如果函数参数个数比较少，可以直接用寄存器存储，不需要入栈
  ![stack](./pictures/stack.png)

# 第四章 处理器体系结构
## Y86-64指令集体系结构
* 程序员可见的状态<br>
![state](./pictures/state.png)

## 逻辑设计和硬件控制语言HCL
* 组合电路的限制<br>
  * 每个逻辑门的输入必须连接到：1)一个系统输入（主输入），2)某个存储单元的输出，3)某个逻辑门的输出。
  * 两个或多个逻辑门的输出不能连接在一起。
  * 这个网必须是无环的。
* 组合电路和HCL布尔表达式
* 字级的组合电路和HCL整数表达式
  * 通过复杂的逻辑门可以组成更大的网。通常，我们会设计能对数据字（word）进行操作的电路。
* 存储器和时钟
  * D触发器
## Y86-64的顺序实现SEQ
* 将处理组织成阶段
  * 取指(fetch)，从内存中(程序计数器PC的值)取出指令字节
  * 译码(decode)，从寄存器读入操作数
  * 执行(execute)
  * 访存(memory)，数据(内存)的读入或写出
  * 写回(write back)，写回寄存器
  * 更新PC
* SEQ硬件结构<br>
![SEQ](./pictures/SEQ.png)
![SEQ2](./pictures/SEQ2.png)
  * 白色方框表示时钟寄存器
  * 蓝色方框表示硬件单元
  * 灰色圆角矩形表示控制逻辑块
  * 白色圆圈表示线路的名称
* SEQ时序
  * SEQ实现包括
    * 组合逻辑
    * 两种存储设备
      * 时钟寄存器（程序计数器和条件码寄存器）
      * 随机访问存储器（寄存器文件，指令内存，数据内存）
  * 原则：从不回读<br>
  处理器从来不需要为了完成一条指令的执行而去读由该指令更新了的状态
## 流水线的通用原理
重要特性：提高系统的吞吐量(throughput)，也就是单位时间内完成任务的总数，不过也会轻微增加延时(latency)，也就是完成一个任务所需要的时间。
* 流水线的局限性
  * 不一致的划分
  ![pipeline](./pictures/pipeline.png)
  * 流水线过深，收益反而下降
## Y86-64的流水线实现SEQ+
和顺序实现相比，需要使得更新PC阶段在下一个时钟周期开始时执行，而不是结束时才执行。

# 第五章 优化程序性能
## 常见优化方式
* 调整编译器优化等级
* 消除循环中的低效性，例如：不在循环判断条件中调用函数
* 消除不必要的内存引用，例如：用局部变量存储数据
## 现代微处理器
![processor](./pictures/processor.png)
* 指令控制单元(ICU, Instruction Control Unit)
  * 从内存中读取指令序列
* 执行单元(EU, Execution Unit)
  * 执行操作

# 第六章 存储器层次结构
提高程序局部性，可以提升程序性能。因为不同层次的存储器，访问时间差别是巨大的：
* CPU寄存器：0周期
* 高速缓存：4~75个周期
* 主存：上百个周期
* 磁盘：几千万个周期
## 存储技术
* 随机访问存储器(RAM)
  * 静态(SRAM)
    * 用于高速缓存存储器，既可以在CPU上，也可以在片下
  * 动态(DRAM)
    * 对干扰非常敏感，需要刷新
    * 使用纠错码纠错
    * 64位内存模块
    ![DRAM](./pictures/DRAM.png)
* 非易失性存储器(nonvolatile memory)
断电后不丢失信息(不同于RAM)。存储在ROM设备中的程序通常被称为固件(firmware)。
  * PROM: 只能编程一次
  * EEPROM：可擦写可编程
  * flash memory
* 磁盘存储
* 固态硬盘 SSD
## 局部性
* 重复引用相同变量，有好的时间局部性
* 步长越小，空间局部性越好，例如，二维数组遍历先行后列

第七章 链接
# 编译驱动程序
* [demo](./code/chapter7/link)
* 相似的代码可参考第一章的代码[例子](./code/chapter1)
# 静态链接
为了构造可执行文件，链接器必须完成：
* 符号解析(symbol resolution)，将每个符号引用和定义关联
* 重定位(relocation)，将符号定义和内存位置关联起来
# 目标文件
目标文件有三种形式：
* 可重定位目标文件<br>
二进制代码和数据(.o 文件，.a文件)，与其他可重定位目标文件合并创建一个可执行目标文件，可由编译器和汇编器生成
* 可执行目标文件<br>
可直接复制到内存并执行(.out 文件)
* 共享目标文件<br>
一种特殊的可重定位目标文件(.so文件)，可以在加载或者运行时被动态地加载进内存并链接(链接库)，可由编译器和汇编器生成

目标文件的格式：
* Windows：Portable Executable, PE
* Mac: Mach-O
* Linux: Executable and Linkable Format, ELF

# 可重定位目标文件
![ELF](./pictures/ELF.png)
* ELF header
  * 描述系统信息，字的大小和字节顺序
  * 帮助链接器语法分析的信息：ELF头的大小，目标文件的类型(三种)
* .text
  * 已编译程序的机器代码
* .rodata
  * 只读数据，比如printf语句中的格式串和开关语句的跳转表
* .data
  * 已初始化的全局和静态C变量。局部C变量在运行时被保存在栈中，既不出现在.data节中，也不出现在.bss节中。
* .bss
  * 未初始化的全局和静态C变量，以及所有被初始化为0的全局或静态变量。在目标文件中这个节不占据实际的空间，它仅仅是一个占位符。目标文件格式区分已经初始化和未初始化变量是为了空间效率。在目标文件中，未初始化变量不需要占据任何实际的磁盘空间。运行时，在内存中分配这些变量，初始值为0。
* .symtab
  * 一个符号表，它存放在程序中定义和引用的函数和全局变量的信息。一些程序员错误地认为必须通过-g选项来编译一个程序，才能得到符号表信息。实际上，每个可重定位目标文件在.symtab中都有一张符号表(除非程序员特意用STRIP命令去掉它)。然而，和编译器中的符号表不同，.symtab符号表不包含局部变量的条目。
  * `-g` enables use of extra debugging information, e.g. line number.
    * [sum.c](./code/chapter7/link/sum.c)无`-g`的symbol table如下：
    ```
    sum2.o:     file format elf64-x86-64

    SYMBOL TABLE:
    0000000000000000 l    df *ABS*  0000000000000000 sum.i
    0000000000000000 l    d  .text  0000000000000000 .text
    0000000000000000 l    d  .data  0000000000000000 .data
    0000000000000000 l    d  .bss   0000000000000000 .bss
    0000000000000000 l    d  .note.GNU-stack        0000000000000000 .note.GNU-stack
    0000000000000000 l    d  .eh_frame      0000000000000000 .eh_frame
    0000000000000000 l    d  .comment       0000000000000000 .comment
    0000000000000000 g     F .text  0000000000000045 sum
    ```
    * [sum.c](./code/chapter7/link/sum.c)有`-g`的symbol table如下：
    ```
    sum.o:     file format elf64-x86-64

    SYMBOL TABLE:
    0000000000000000 l    df *ABS*  0000000000000000 sum.i
    0000000000000000 l    d  .text  0000000000000000 .text
    0000000000000000 l    d  .data  0000000000000000 .data
    0000000000000000 l    d  .bss   0000000000000000 .bss
    0000000000000000 l    d  .debug_info    0000000000000000 .debug_info
    0000000000000000 l    d  .debug_abbrev  0000000000000000 .debug_abbrev
    0000000000000000 l    d  .debug_aranges 0000000000000000 .debug_aranges
    0000000000000000 l    d  .debug_line    0000000000000000 .debug_line
    0000000000000000 l    d  .debug_str     0000000000000000 .debug_str
    0000000000000000 l    d  .note.GNU-stack        0000000000000000 .note.GNU-stack
    0000000000000000 l    d  .eh_frame      0000000000000000 .eh_frame
    0000000000000000 l    d  .comment       0000000000000000 .comment
    0000000000000000 g     F .text  0000000000000045 sum
    ```
  * 上述符号表各列的意义
  ```
  COLUMN ONE: the symbol's value
  COLUMN TWO: a set of characters and spaces indicating the flag bits that are set on the symbol. There are seven groupings which are listed below:
    group one: (l,g,,!) local, global, neither, both.
    group two: (w,) weak or strong symbol.
    group three: (C,) symbol denotes a constructor or an ordinary symbol.
    group four: (W,) symbol is warning or normal symbol.
    group five: (I,) indirect reference to another symbol or normal symbol.
    group six: (d,D,) debugging symbol, dynamic symbol or normal symbol.
    group seven: (F,f,O,) symbol is the name of function, file, object or normal symbol.
  COLUMN THREE: the section in which the symbol lives, ABS means not associated with a certain section
  COLUMN FOUR: the symbol's size or alignment.
  COLUMN FIVE: the symbol's name.
  ```
* .rel.text
  * 一个.text节中位置的列表，当链接器把这个目标文件和其他文件组合时，需要修改这些位置。一般而言，任何调用外部函数或者引用全局变量的指令都需要修改。另一方面，调用本地函数的指令则不需要修改。注意，可执行目标文件中并不需要重定位信息，因此通常省略。
* rel.data
  * 被模块引用或定义的所有全局变量的重定位信息。一般而言，任何已初始化的全局变量，如果它的初始值是一个全局变量地址或者外部定义函数的地址，都需要被修改。
* .debug
  * 一个调式符号表，其条目是程序中定义的局部变量和类型定义，程序中定义和引用的全局变量。
* .strtab
  * 一个字符串表，其内容包括.symtab和.debug节中的符号表，以及节头部中的节名字。字符串表就是以null结尾的字符串的序列。

# 符号和符号表
三种不同的符号：
* 由此模块定义并能被其他模块引用的全局符号，如：非静态的C函数和全局变量
* 由其他模块定义并被此模块引用的全局符号(外部符号)
* 只被此模块定义和引用的局部符号，对应于带`static`属性的C函数和全局变量。

**注意**：.symtab中的符号表不包含对应于本地非静态程序变量的任何符号，这些符号在运行时在栈中被管理，链接器对此类符号不感兴趣。

## static属性
```c
int f()
{
  static int x = 0;
  return x;
}

int g()
{
  static int x = 1;
  return x;
}
```
编译器在.data或.bss中为每个定义分配空间，并在符号表中创建一个唯一的名字。如上面的例子中，编译器会向汇编器输出两个不同名字的局部链接器符号，可以用`x.1`表示函数f中的定义，而用`x.2`表示函数g中的定义。

## 符号的意义
每个符号都被分配到目标文件的某个节，由`section`字段表示(如：.text等)。有三个特殊的伪节*(pseudosection)，它们在节头部表中没有条目：
* ABS: 代表不该被重定位的符号
* UNDEF：代表未定义的符号，也就是在本目标模块中引用，但是却在其他地方定义的符号
* COMMON：表示还未被分配位置的未初始化的数据目标。对于COMMON符号，value字段给出对齐要求，而size给出最小的大小
  * COMMON和.bss的区别
    * COMMON: 未初始化的全局变量
    * .bss: 未初始化的静态变量，以及初始化为0的全局或静态变量
### `readelf` 例子
`readelf -a main.o`命令可得到下面三行：
```
13: 0000000000000000     8 OBJECT  GLOBAL DEFAULT    3 array
14: 0000000000000000    35 FUNC    GLOBAL DEFAULT    1 main
16: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND sum
```
`objdump -t main.o`命令可得到如下三行：
```
0000000000000000 g     O .data  0000000000000008 array
0000000000000000 g     F .text  0000000000000023 main
0000000000000000         *UND*  0000000000000000 sum
```
* main条目<br>
它是一个位于`.text`节中偏移量为0(即value值)处的35字节函数。
* array条目<br>
它是一个位于`.data`节中偏移量为0处的8字节目标。
* sum条目<br>
它是一个对外部符号`sum`的引用。READELF用一个整数索引来标识每个节。 Ndx=1表示.text节，而Ndx=3表示.data节。

## 符号解析
链接器解析符号引用的方法是将每个引用与它输入的可重定位目标文件的符号表中的一个确定的符号定义关联起来。
* 全局符号的引用解析<br>
当编译器遇到一个不是在当前模块中定义的符号(变量或函数名)时，会假设该符号是在其他某个模块中定义的，生成一个链接器符号表条目，并把它交给链接器处理。如果链接器在它的任何输入模块中都找不到这个被引用符号的定义，就输出一条错误信息并终止。

### 链接器如何解析多重定义的全局符号
在编译时，编译器向汇编器输出每个全局符号，或者是强(strong)或者是弱(weak)，而汇编器把这个信息隐含地编码在可重定位目标文件的符号表里。
* 函数和已初始化的全局变量是强符号
* 未初始化的全局变量是弱符号

Linux链接器使用下面的规则来处理多重定义的符号名，可参考[例子](./code/chapter7/symbol_conflict)：
* 规则1：不允许有多个同名的强符号
* 规则2：如果有一个强符号和多个弱符号同名，那么选择强符号
* 规则3：如果有多个弱符号同名，那么从这些弱符号中任意选择一个

### 与静态库链接
![static_lib](./pictures/static_lib.png)

上图显示了[例子](./code/chapter7/static_lib)的编译过程。链接器只会从静态库中提取需要链接的目标文件(`addvec.o`)，不会把所有的目标文件都链接进可执行文件。

### 链接器如何使用静态库来解析引用
从左到有解析，一般把静态库放到后面。有时候会出现需要写两遍静态库的情况, 如, `libx.a`和`liby.a`相互调用的情况：
`gcc foo.c libx.a liby.a libx.a`

## 重定位
重定位的目的是：为每个符号分配运行时地址。由两步组成：
* 重定位节和符号定义
  * 将所有输入模块的相同类型的节合并为同一类型的新的聚合节
  * 将运行时内存地址赋给每个节以及每个符号
* 重定位节中的符号引用
  * 修改代码节和数据节中对每个符号的引用，使得它们指向正确的运行时地址

### 重定位条目
由于汇编器无法确定外部引用最终在内存中的位置，所以它就会生成一个重定位条目，告诉链接器在将目标文件合并成可执行文件时如何修改这个引用。重定位条目会告诉链接器需要修改的引用的信息。
* .rel.text: 存放代码的重定位条目
* .rel.data：存放已初始化数据的重定位条目

### 重定位符号引用
* [main.c](./code/chapter7/link/main.c)的重定位前的汇编代码(`objdump -d main.o`)
```
0000000000000000 <main>:
   0:   55                      push   %rbp
   1:   48 89 e5                mov    %rsp,%rbp
   4:   48 83 ec 10             sub    $0x10,%rsp
   8:   be 02 00 00 00          mov    $0x2,%esi
   d:   48 8d 3d 00 00 00 00    lea    0x0(%rip),%rdi        # 14 <main+0x14>
                        10: R_X86_64_PC32       array-0x4
  14:   e8 00 00 00 00          callq  19 <main+0x19>
                        15: R_X86_64_PLT32      sum-0x4
  19:   89 45 fc                mov    %eax,-0x4(%rbp)
  1c:   b8 00 00 00 00          mov    $0x0,%eax
  21:   c9                      leaveq 
  22:   c3                      retq 
```
* [main.c](./code/chapter7/link/main.c)的重定位后的汇编代码(`objdump -D main`)
```
0000000000401000 <main>:
  401000:       55                      push   %rbp
  401001:       48 89 e5                mov    %rsp,%rbp
  401004:       48 83 ec 10             sub    $0x10,%rsp
  401008:       be 02 00 00 00          mov    $0x2,%esi
  40100d:       48 8d 3d ec 2f 00 00    lea    0x2fec(%rip),%rdi        # 404000 <array>
  401014:       e8 0a 00 00 00          callq  401023 <sum>
  401019:       89 45 fc                mov    %eax,-0x4(%rbp)
  40101c:       b8 00 00 00 00          mov    $0x0,%eax
  401021:       c9                      leaveq 
  401022:       c3                      retq
0000000000401023 <sum>:
  401023:       55                      push   %rbp
  ...
0000000000404000 <array>:
  404000:       01 00                   add    %eax,(%rax)
  ...
```

## 可执行目标文件
![ELF_Format](./pictures/ELF_Format.png)
* 可执行目标文件 ELF header (`readelf -h main`)
```
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x401000
  Start of program headers:          64 (bytes into file)
  Start of section headers:          13872 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         5
  Size of section headers:           64 (bytes)
  Number of section headers:         13
  Section header string table index: 12
```
* 可重定位目标文件 ELF header (`readelf -h main.o`)
```
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              REL (Relocatable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x0
  Start of program headers:          0 (bytes into file)
  Start of section headers:          1744 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           0 (bytes)
  Number of program headers:         0
  Size of section headers:           64 (bytes)
  Number of section headers:         20
  Section header string table index: 19
```
* 可执行目标文件相对于可重定位目标文件的不同之处
  * .init节，定义了一个小函数，叫做_init，程序的初始化代码会调用它。
  * 因为可执行文件是完全链接的(已被重定位)，所以它不再需要.rel节。

## 加载可执行目标文件
![prog_mem](./pictures/prog_mem.png)
如上图所示，每个Linux程序都有一个运行时内存映像，程序运行过程如下：
* 加载器运行，创建如上图所示的内存映像
* 加载器复制可执行文件的内容到代码段和数据段
* 加载器跳转到程序的入口点：`_start`函数地址
* `_start`函数调用系统启动函数`__libc_start_main`，该函数定义在libc.so中
* `__libc_start_main`初始化执行环境，并调用用户层的`main`函数

## 动态链接共享库
![dynamic_lib](./pictures/dynamic_lib.png)
不同于静态链接，在创建可执行文件时，链接器(`ld`)只执行部分重定位，然后在程序加载时，由动态链接器(`ld-linux.so`)完成全部重定位过程。

当加载器加载可执行文件时，注意到可执行文件包含`.interp`节，这一节包含动态链接器的路径名。以上图为例，动态链接器执行下面的重定位任务完成链接：
* 重定位`libc.so`的文本和数据到某个内存段
* 重定位`libvector.so`的文本和数据到另一个内存段
* 重定位`prog21`中所有对由`libc.so`和`libvector.so`定义的符号的引用
* 最后，动态链接器将控制传递给应用程序。从这个时刻开始，共享库的位置就固定了，并且在程序执行的过程中都不会改变

## 从应用程序中加载和链接共享库
应用程序除了在编译时指定共享库，也可以在它运行时要求动态链接器加载和链接某个共享库，可参考[例子](./code/chapter7/dynamic_lib/dlmain.c)

## 位置无关代码
问题：多个进程如何共享程序的一个副本，以节约内存资源？<br>
通过一种编译方式共享代码段，使得可以把他们加载到内存的任何位置而无需链接器修改。使用这种方式，无限多个进程可以共享一个共享模块的代码段的单一副本。当然，每个进程仍然会有它自己的读写数据块。
### PIC数据引用
无论我们在内存中的何处加载一个目标模块，数据段与代码段的距离总是保持不变。因此，代码段中任何指令和数据段中的任何变量之间的距离都是一个运行时常量，与代码段和数据段的绝对位置是无关的。<br>
如何生成全局变量PIC引用？
* Global Offset Table (GOT)<br>
以`libvector.so`中的全局变量[addcnt](./code/chapter7/dynamic_lib/addvec.c)函数为例，看`addvec`函数是如何引用全局变量`addcnt`的。
![GOT](./pictures/GOT.png)
`addvec`例程通过`GOT[3]`间接地加载全局变量`addcnt`的地址，然后把`addcnt`在内存中加1。这里的关键思想是对`GOT[3]`的PC相对引用中的偏移量是一个运行时常量。
### PIC函数调用
如何实现不需要链接器修改调用模块的代码段，实现动态库的PIC函数调用？答案是通过以下两个机制，实现延时绑定(lazy binding)：
* GOT
* 过程链接表(Procedure Linkage Table, PLT)

如果一个目标模块调用定义在共享库中的任何函数，那么它就由自己的GOT和PLT。GOT是数据段的一部分，而PLT是代码段的一部分。那么，GOT和PLT是如何协同工作的呢？
![GOT_PLT.png](./pictures/GOT_PLT.png)
以[main.c](./code/chapter7/dynamic_lib/main.c)调用`libvector.so`中的[addvec](./code/chapter7/dynamic_lib/addvec.c)函数为例：
* 过程链接表(PLT)<br>
每个被可执行程序调用的库函数都有自己的PLT条目。PLT是一个16字节条目的数组。上图中：
  * PLT[0]是一个特殊条目，跳转到动态链接器中
  * PLT[1]调用系统启动函数`__libc_start_main`
  * PLT[2]开始的条目是用户代码调用的函数，其中PLT[2]调用`addvec`
  * PLT[3]调用`printf`
* 全局偏移量表(GOT)<br>
GOT是8字节条目的数组。上图中：
  * GOT[0]和GOT[1]包含动态链接器在解析函数地址时会使用的信息。
  * GOT[2]是动态链接器在`ld-linux.so`模块中的入口点。
  * 其余的每个条目对应于一个被调用的函数，**其地址需要在运行时被解析**。每个条目都有一个相匹配的PLT条目。例如，GOT[4]和PLT[2]对应于`addvec`
下面解释，GOT和PLT是如何工作的？
* `addvec`被第一次调用时，目的是利用动态链接器将`addvec`的运行是地址加载到GOT[4]中(GOT[4]对应与`addvec`函数的GOT条目)，详细过程如下：
  * 程序进入PLT[2]，这是`addvec`的PLT条目
  * 第一条PLT指令通过GOT[4]进行间接跳转。但是因为是第一次调用，GOT[4]条目是指向它对应的PLT条目的第二条指令的(默认GOT内容)，即上图中的`4005c6: pushq $0x1`行
  * 把`addvec`的ID(0x1)压入栈中后，继续往下执行: 跳转到`4005a0`，即PLT[0]
  * PLT[0]通过GOT[1]间接地把动态链接器的一个参数压入栈中，然后通过GOT[2]间接跳转进动态链接器中。动态链接器使用两个栈条目来确定`addvec`的运行时位置，用这个地址重写GOT[4]，再把控制传递给`addvec`
* 后续调用`addvec`的过程
  * 和前面一样，控制传递到PLT[2]
  * 与第一次不同，GOT[4]存了`addvec`运行时的地址，就不用再通过动态链接器查找地址了，直接把控制传递给`addvec`

## 库打桩机制 library interpositioning
Linux允许你截获对共享库函数的调用，取而代之执行自己的代码。打桩可以发生在不同的时机，参考[例子](./code/chapter7/interpose)
* 编译时打桩
  * 相当于在可执行文件中直接复写调用库的函数，需要修改原代码
* 链接时打桩
  * 在编译时添加`-Wl,,--wrap,xxxFunc`编译选项，修改打桩函数的symbol，加上`__wrap`和`__real`前缀
* 运行时打桩
  * 利用`LD_PRELOAD`环境变量(以空格或分号分隔)影响动态链接库的运行。动态链接器(LD-LINUX.SO)会先搜索LD_PRELOAD库，然后才搜索任何其他的库。

## 处理目标文件的工具
常用命令
* 获取动态库中某个函数的symbol
  * `readelf --dyn-syms -W xx.so | grep xxxFunc`


