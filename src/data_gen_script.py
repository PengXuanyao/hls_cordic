'''
Author: Peng Xuanyao 793063685@qq.com
Date: 2022-10-03 10:52:03
LastEditors: Peng Xuanyao 793063685@qq.com
LastEditTime: 2022-10-03 11:20:06
FilePath: /src/data_gen_script.py
Description: 生成tb所需的测试数据
'''
from math import cos, sin
import random

N = 629 # 总共的数据个数
myalpha = [] # 角度
mysin = [] # sin值
mycos = [] # cos值

# 计算
for i in range(N):
    myalpha.append((2 * random.random() - 1) * 3.1415926) # 将[0,1)之间的随机数，偏移、放大至(-3.1415926, +3.1415926);
    mysin.append(sin(myalpha[i]))
    mycos.append(cos(myalpha[i]))

# 存文件
with open("myalpha.dat", 'w') as file:
    for i in range(N):
        file.write(f'{myalpha[i]}\n')

with open('mysin.dat', 'w') as file:
    for i in range(N):
        file.write(f'{mysin[i]}\n')

with open('mycos.dat', 'w') as file:
    for i in range(N):
        file.write(f'{mycos[i]}\n')     