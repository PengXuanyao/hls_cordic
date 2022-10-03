/*
 * @Author: pengxuanyao 
 * @Date: 2022-09-30 16:23:00 
 * @Last Modified by:   pengxuanyao 
 * @Last Modified time: 2022-09-30 16:23:00 
 */
#include "cordic.h"

/**
 * @description: 
 * 预处理函数，将输入角度限定在+-PI/2之间
 * @param {di_t} full_alpha
 * @param {di_t} &alpha
 * @param {flag_t} &flag
 * @return {*}
 */
void pre_cordic (di_t full_alpha, di_t &alpha, flag_t &flag)
{
    if (full_alpha > PI / 2)
    {
        alpha = PI - full_alpha;
        flag = 2;
    }
    else if (full_alpha < -PI / 2)
    {
        alpha = -PI - full_alpha;
        flag = 3;
    }
    else
    {
        alpha = full_alpha;
        flag = 0;
    }
}

/**
 * @description: 
 * CODIC算法主体部分，迭代N次，计算出结果
 * @param {di_t} alpha
 * @param {flag_t} flag
 * @param {do_t} &mysin
 * @param {do_t} &mycos
 * @param {flag_t} flag_delay
 * @return {*}
 */
void cordic_calculate (di_t alpha, flag_t flag, do_t &mysin, do_t &mycos, flag_t &flag_delay)
{
    const int N = 16;
    do_t xi[N];
    do_t yi[N];
    di_t zi[N];
    flag_t flag_delay_a[N];

    xi[0] = Kn;
    yi[0] = 0;
    zi[0] = alpha;
    flag_delay_a[0] = flag;

    const di_t myarctan[16] = 
    {0.7853981, 0.4636476, 0.2449787, 0.1243549, 0.0624188,
    0.0312398, 0.0156237, 0.0078123, 0.0039062, 0.0019531,
    0.0009765, 0.0004883, 0.0002441, 0.0001221, 0.0000610};

    int m = 0;
    loop:
    for (m = 0; m < N; m++)
    {
        if (zi[m] >= 0)
        {
            xi[m+1] = xi[m] - (yi[m] >> m);
            yi[m+1] = yi[m] + (xi[m] >> m);
            zi[m+1] = zi[m] - myarctan[m];
        }
        else
        {   
            xi[m+1] = xi[m] + (yi[m] >> m);
            yi[m+1] = yi[m] - (xi[m] >> m);
            zi[m+1] = zi[m] + myarctan[m];
        }
        flag_delay_a[m+1] = flag_delay_a[m];
    }
    mysin = yi[N-1];
    mycos = xi[N-1];
    flag_delay = flag_delay_a[N-1];
}

/**
 * @description: 
 * 后处理得到的sin cos值
 * @param {do_t} mysin
 * @param {do_t} mycos
 * @param {flag_t} flag_delay
 * @param {do_t} &sin_out
 * @param {do_t} &cos_out
 * @return {*}
 */
void post_cordic(do_t mysin, do_t mycos, flag_t flag_delay, do_t &sin_out, do_t &cos_out)
{
    switch (int(flag_delay))
    {
    case 2:
        sin_out = mysin;
        cos_out = -mycos;
        break;
    case 3:
        sin_out = mysin;
        cos_out = -mycos;
        break;
    default:
        sin_out = mysin;
        cos_out = mycos;
        break;
    }
}

/**
 * @description: 
 * codic算法的顶层函数
 * @param {di_t} full_alpha
 * @param {do_t} &sin_out
 * @param {do_t} &cos_out
 * @return {*}
 */
void cordic (di_t full_alpha, do_t &sin_out, do_t &cos_out)
{
    di_t alpha;
    flag_t flag;
    do_t mysin;
    do_t mycos;
    flag_t flag_delay;

    pre_cordic(full_alpha, alpha, flag);
    cordic_calculate(alpha, flag, mysin, mycos, flag_delay);
    post_cordic(mysin, mycos, flag_delay, sin_out, cos_out);
}
