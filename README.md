# 数据结构大作业——小组汇报

## 说明

大作业来自《数据结构题集( C 语言版)》一书，共分成 4 组，选择其中一组完成即可。
3 人一组完成大作业，并制作 PPT 进行课堂展示，老师和学生打分，取平均分为最终成绩。

1. 实习 1.6 池塘夜降彩色雨，实习 5.6 最小生成树问题
2. 实习 2.4 马踏棋盘，实习 6.4 平衡二叉树操作的演示
3. 实习 2.8 电梯模拟，实习 4.1 稀疏矩阵运算器
4. 实习 5.8 全国交通咨询模拟，实习 6.7 多关键字排序

## 要点

### 作业的完成程度

功能完备，性能卓越（例如：算法的先进性，GUI 的友好性）

### 讲者的演讲能力

- 讲解的条理性、表达的清晰性
- 时间的控制
- 声音洪亮

### PPT 的制作

- 内容
  - 问题描述
  - 数据结构概要，算法特色(包括各种改进)
  - 时空性能分析
  - 程序运行效果：录制视频，不要当场演示！

- PPT 制作
  - 字体大小：太小看不清
  - 颜色反差：反差应该大，不要用黑底白字
  - 适当动画

## 选题：马踏棋盘和平衡二叉树

### 马踏棋盘

#### 问题描述

>将马随机放在国际象棋的 8x8 棋盘 `Board[8][8]` 的某个方格中,马按走棋规则进行移动。
>要求每个方格只进入一次，走遍棋盘上全部 64 个方格。
>编制非递归程序，求出马的行走路线，并按求出的行走路线，
>将数字 1,2,...,64 依次填人一个 8x8 的方阵，输出之。

- 算法，代码，图形化（一步一步打印）
- 时空性能分析

### 平衡二叉树

>利用平衡二叉树实现一个动态查找表。
>实现动态查找表的三种基本功能：查找、插入和删除。

- 算法，代码
- 画图演示
- 时空性能分析

## 使用方法

1. 进入对应项目文件夹 `cd AVLTree` 或 `cd Knight\'s\ Tour\ Problem`
2. 编译： `make`
3. 运行： `./AVLT` 或 `./KTP`
4. 清理： `make clean`
