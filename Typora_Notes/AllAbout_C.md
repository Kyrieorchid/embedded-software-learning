###### 重写printf()

​	printf()底层调用write()，重写write()定向到串口输出。

***

##### `__attribute__`

​	`__attribute__` 是GNU编译器 (GCC) 提供的一个扩展，用来设置函数、变量、类型的特殊属性。这些属性可以用来优化代码、控制代码生成、增强代码检查等。

​	语法：`__attribute__((attribute-list))`

​	`__attribute__((packed))`:取消结构体内存对齐，使其紧凑排列。

​	`__attribute__((weak))`:声明弱符号属性，用于全局变量和函数，若存在 *<u>同名强符号</u>* 变量或函数则可以覆盖。

***

###### GDB&GCC&GNU

​	GNU（GNU's Not Unix）项目的目标是开发一个与Unix兼容的操作系统，提供完全自由的软件工具和应用程序。（开发了许多工具和软件，但它缺少一个重要的部分：操作系统内核。GNU工具与Linux内核结合，形成了一个完整的操作系统，通常被称为GNU/Linux。

​	GCC（GNU Compiler Collection）是一个编译器集合，支持多种编程语言，包括C、C++、Objective-C、Fortran、Ada等。**Tips**：预处理（生成**.i**文件）-> 编译（生成**.s**汇编文件）-> 汇编（生成**.o**二进制目标文件）-> 链接（生成**.exe**可执行文件）。[GCC命令](https://blog.csdn.net/qq_39872252/article/details/133309120)

​	GDB（GNU Debugger）：调试器，单步执行、断点和检查变量值等功能。

​	GNU Make：需要`Makefile`文件来描述编译和链接规则，`make`命令会按`Makefile`的内容编译与链接。

***

###### Shallow Copy & Deep Copy

​	<u>浅拷贝</u>：浅拷贝创建一个新的对象，但并不复制对象内部的子对象，而是将引用拷贝过来。因此，浅拷贝后的对象与原对象共享相同的子对象。

​	<u>深拷贝</u>：深拷贝创建一个新的对象，并递归地复制所有子对象。因此，深拷贝后的对象与原对象完全独立，修改一个对象不会影响另一个对象。

​	![image-20240716184341475](C:\Users\admin\AppData\Roaming\Typora\typora-user-images\image-20240716184341475.png)

​	切片操作（即`[:]`）相当于浅拷贝，而不是深拷贝。全切片操作复制的是引用，而不是实际的子对象，因此，修改原对象中的可变子对象会影响到新对象中的对应子对象。

​	<u>当对一个简单的一维数组（如 `[1, 2, 3, 4]`）进行浅拷贝时,因为一维数组的元素是不可变类型（如整数），在浅拷贝过程中，复制的是这些元素的引用，但由于它们是不可变的，直接修改会创建一个新的对象，而不会影响原对象。</u>

***

###### const假只读

const只是修饰变量，不能通过变量名直接操作对应内存，可通过指针修改const定义的变量。

`const uint8 a = 10; *(uint8*)(&a) = 11;`

***

###### 数组指针

定义了一个数组 `uint8 a[8] = {0}; uint8 *b = a;`，此时，`&a` 和 `&b` 有区别：

1. `&a` 表示的是整个数组 `a` 的地址。数组名 `a` 在表达式中通常会退化为指向其第一个元素的指针（`*b = a`就是），<u>但在取地址操作符 `&` 前面，`a` 表示整个数组</u>，`&a` 得到的是数组 `a` 的地址，类型是 `uint8 (*)[8]`。
2. `&b` 表示的是指针 `b` 的地址。指针 `b` 是一个指针变量，存储了数组 `a` 的地址（`*b = a`中a就表示首元素地址），`&b` 得到的是指针 `b` 自身的地址，类型是 `uint8 **`。

关键在于a在`uint8 *b = a`中就表示首元素地址，b就是二级指针；在`&a`中a就表示整个数组，&a就是数组的一级指针。

***

###### BIT0清0

将register的bit0清零时，`reg &= 0`会将reg全清零，`reg &= ~1`。

***

###### void*指针

又叫通用指针，没有具体的指向数据类型，不能直接解引用。可以被强制转换为需要的具体类型的指针再解引用。

动态内存分配函数（如`malloc`）返回`void`指针，可以分配任意类型的数据。

![image-20240808115727682](C:\Users\admin\AppData\Roaming\Typora\typora-user-images\image-20240808115727682.png)

可以使用`void`指针作为函数参数，实现对不同类型数据的操作。

![image-20240808115819249](C:\Users\admin\AppData\Roaming\Typora\typora-user-images\image-20240808115819249.png)

***

###### 内存对齐

内存对齐是指将数据放置在特定的地址边界上，使得CPU可以高效地访问数据。对于大小为N字节的数据类型，对齐要求其地址是N的倍数。

结构体对齐：



***

###### 链接脚本

`.ld`链接脚本文件使用的是一种特定于GNU链接器（GNU linker，简称`ld`）的脚本语言，用于控制链接器在生成<u>可执行文件或其他可链接目标文件（如库文件）</u>时的行为和布局。使用LLVM工具链，仍然可以使用GNU `ld`脚本，但需要注意LLD的某些特性和限制。

***

##### Defination & Declaration

* A definition of a variable allocates memory for it. For example: int X; is a definition.
* A declaration merely tells the compiler that the variable exists somewhere, but doesn't allocate memory. For example: extern int X; is a declaration.
* When you include a.h in both main.c and a.c, the contents of a.h are copied into both source files during preprocessing.
* If a.h contains a definition like int X;, then X is defined in both main.c and a.c. This results in two separate definitions of X when these object files are linked together, causing the linker to generate an error: `duplicate symbol`.
* So, <b>defination</b> in one source file and <b>declaration</b> in corresponding heard file.