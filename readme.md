# Readme

本项目对赛灵思的HLS入门课程（[24课：案例分析\_哔哩哔哩\_bilibili](https://www.bilibili.com/video/BV1bt41187RW?p=24&vd_source=293ffecc5040ce31ebf8b10de8372434)）的项目进行了整理和实现，整理相关的HLS代码，并编写了tb测试数据生成脚本。

目前2022，xilinx已经不再更新vivado_hls工具，而是主要推进新版的vitis_hls工具链。此项目在Ubuntu22.04、vitis 2020.2环境进行了部署。

相关的源码在src中（包括设计和仿真文件），vitis_hls工程文件在cordic文件夹中（直接使用vitis_hls->File->Open Project打开整个coedic文件夹即可）。

一些学习和调试记录以供参考：

## B站课程学习

> [24课：案例分析\_哔哩哔哩\_bilibili](https://www.bilibili.com/video/BV1bt41187RW?p=24&vd_source=293ffecc5040ce31ebf8b10de8372434)

一共25节课程，比较精简。主要讲HLS基本使用中关于变量类型、数组和函数等基础，同时重点讲了各种Directive的使用（有利于实现不同的设计指标等）。

目前已经看到24课，前面笔记记录在笔记本上，第24课讲了一个具体的HLS工程实例，此次笔记主要记录一下实现过程。

<!-- more -->

## Cordic算法实现

### 算法原理

cordic算法是一种通过简单运算（加、减、移位、查找表）进行迭代（旋转）实现复杂函数计算（三角函数、乘除法、双曲函数等）的算法，适用于没有浮点运算的系统（微控制器、FPGA等）。

> [CORDIC - Wikipedia](https://en.wikipedia.org/wiki/CORDIC)
> 
> CORDIC (for COordinate Rotation DIgital Computer), also known as Volder's algorithm, or: Digit-by-digit method Circular CORDIC (Jack E. Volder), Linear CORDIC, Hyperbolic CORDIC (John Stephen Walther), and Generalized Hyperbolic CORDIC (GH CORDIC) (Yuanyong Luo et al.), is a simple and efficient algorithm to calculate trigonometric functions, hyperbolic functions, square roots, multiplications, divisions, and exponentials and logarithms with arbitrary base, typically converging with one digit (or bit) per iteration. CORDIC is therefore also an example of digit-by-digit algorithms. CORDIC and closely related methods known as pseudo-multiplication and pseudo-division or factor combining are commonly used when no hardware multiplier is available (e.g. in simple microcontrollers and FPGAs), as the only operations it requires are additions, subtractions, bitshift and lookup tables. As such, they all belong to the class of shift-and-add algorithms. In computer science, CORDIC is often used to implement floating-point arithmetic when the target platform lacks hardware multiply for cost or space reasons.

对于三角函数来说，CORDIC算法原理就是首先找到一个初始的旋转起点$(x_0, y_0)$，然后由旋转公式:

$$ \begin{bmatrix} x \\ y \end{bmatrix} = \begin{bmatrix} cos{\theta} & -sin{\theta} \\ sin{\theta} & cos{\theta} \end{bmatrix} \begin{bmatrix} x_0 \\ y_0 \end{bmatrix} $$

得到目标的$(x, y)$，其中的旋转可以看成是一系列小角度进行迭代旋转。

具体的推导公式可以参考：[CORDIC算法原理详解 - 知乎](https://zhuanlan.zhihu.com/p/384524393)

其他参考资料：[FPGA的算法解析4：CORDIC 算法解析 - 知乎](https://zhuanlan.zhihu.com/p/471677202)

### HLS代码编写

#### 遇到的一些问题

1. interval和lantency的区别，interval会考虑overhead？
   
   > Latency：第一个输入，到第一个输出，之间的延迟；表征的是处理时间;
   > Interval：第一个输入，到第二个输入，之间的间隔；表征的是吞吐能力。
   
2. 遇见一种奇怪的用法，应该是用于const数组的初始化操作：

    ```cpp
        const di_t myarctan[16] = {
        #include "myarctan.h"// 添加文件
        };
    ```

   目前暂时没有弄清楚myarctan.h长什么样子，先直接用数据替代了一下。

3. 目前主要问题是在tb中，没有ReadFileVec的定义。后续两种解决方案：一种是不用ReadFileVec直接安排好数据即可，第二个是找一下视频资料，隐约记得C++部分讲过这个。
   
   这个问题已经解决了，在前面的课程中，讲过了利用template读取数据的方法，也给出了源码。[10课：描述高效的C测试平台-测试激励\_哔哩哔哩\_bilibili](https://www.bilibili.com/video/BV1bt41187RW?p=10&vd_source=293ffecc5040ce31ebf8b10de8372434)

4. 下一个问题是输出数据无法对齐，未改动之前的程序是这样的：

   ```cpp
    cout << setfill(' ') << setw(18) << right << alpha[i];
    cout << setfill(' ') << setw(18) << right << sinres[i];
    cout << setfill(' ') << setw(18) << right << sinRef[i];
    cout << setfill(' ') << setw(18) << right << cosres[i];
    cout << setfill(' ') << setw(18) << right << cosRef[i];
   ```
   
   输出的结果是这样的：

   ![wrong_format](https://raw.githubusercontent.com/PengXuanyao/img-bed/main/wrong_format.png)

   目前暂时不知道具体的根源是什么，解决办法是将数据强制装换成float可以解决问题。（原本的数据是ap_fixed自定义的格式）

   ```cpp
    cout << setfill(' ') << setw(18) << right << (float)alpha[i];
    cout << setfill(' ') << setw(18) << right << (float)sinres[i];
    cout << setfill(' ') << setw(18) << right << (float)sinRef[i];
    cout << setfill(' ') << setw(18) << right << (float)cosres[i];
    cout << setfill(' ') << setw(18) << right << (float)cosRef[i];
   ```
   
   问题解决：

   ![right_format](https://raw.githubusercontent.com/PengXuanyao/img-bed/main/right_format.png)

5. 最后是结果不正确的问题，这个经过排查，发现是flag每次都被设置为了0，导致没有正确处理2、3情况，也就是对cos取反的情况被忽略。

   最后找到问题是根源是函数`void cordic_calculate (di_t alpha, flag_t flag, do_t &mysin, do_t &mycos, flag_t flag_delay)`头的定义有问题，最后一个flag_delay应该使用c++的引用语法`flag_t &flag_delay`，更正即可。

### HLS综合与性能对比

> 进行联合仿真后打不开波形文件图？
>
> 注意要选择dump trace : all。
>
> ![dump trace](https://raw.githubusercontent.com/PengXuanyao/img-bed/main/dump_trac.png)

联仿之后发现波形结果中有很多延迟，肉眼可见能够通过流水线进行lantency的优化。

![wave_form](https://raw.githubusercontent.com/PengXuanyao/img-bed/main/20221003154939.png)

通过加入pipeline能够对设计进行优化和改善，改善之后的效果还是很明显的，如下是性能的对比：

![performance](https://raw.githubusercontent.com/PengXuanyao/img-bed/main/20221003160538.png)

资源消耗的对比：

![utilization](https://raw.githubusercontent.com/PengXuanyao/img-bed/main/20221003160740.png)

## 项目总结

1. HLS能够帮助快捷的实现复杂功能的硬件电路，但是需要程序员不仅要对C++代码较为了解，并且要对硬件具体实现的方式方法非常清楚，才能够正确地结合directive实现合适的硬件电路。
2. 本次项目能够熟悉了整个HLS开发的流程，是一个helloworld性质的proj，后续需要自己设计并实现一定功能的复杂电路，才能够具体掌握hls。
