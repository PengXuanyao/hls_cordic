/*
 * @Author: Peng Xuanyao 793063685@qq.com
 * @Date: 2022-09-30 10:55:37
 * @LastEditors: Peng Xuanyao 793063685@qq.com
 * @LastEditTime: 2022-10-01 11:51:57
 * @FilePath: /src/cordic_tb.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <iomanip>
#include <cmath>
#include <math.h>
#include "cordic.h"
#include "ReadFileVec.h"

using namespace std;

int main()
{
    const int N = 629;
    char *fd_alpha = "myalpha.dat";
    char *fd_sin = "mysin.dat";
    char *fd_cos = "mycos.dat";
    di_t alpha[N] = {0};
    do_t sinRef[N] = {0};
    do_t cosRef[N] = {0};
    do_t sinres[N] = {0};
    do_t cosres[N] = {0};
    int ErrCntSin = 0;
    int ErrCntCos = 0;
    float precision = pow(2, -10);
    int i;

    ReadFileVec <N, di_t, float> (fd_alpha, alpha);
    ReadFileVec <N, do_t, float> (fd_sin, sinRef);
    ReadFileVec <N, do_t, float> (fd_cos, cosRef);

    for (i = 0; i < N; i++)
    {
        cordic(alpha[i], sinres[i], cosres[i]);
    }

    // 打印表头
    cout << setfill('-') << setw(90) << '-' << '\n';
    cout << setfill(' ') << setw(18) << right << "Alpha";
    cout << setfill(' ') << setw(18) << right << "sin";
    cout << setfill(' ') << setw(18) << right << "sinRef";
    cout << setfill(' ') << setw(18) << right << "cos";
    cout << setfill(' ') << setw(18) << right << "cosRef" << '\n';
    cout << setfill('-') << setw(90) << '-' << '\n';

    // 数据打印
    for (i = 0; i < N ; i++)
    {
        cout << setfill(' ') << setw(18) << right << (float)alpha[i];
        cout << setfill(' ') << setw(18) << right << (float)sinres[i];
        cout << setfill(' ') << setw(18) << right << (float)sinRef[i];
        cout << setfill(' ') << setw(18) << right << (float)cosres[i];
        cout << setfill(' ') << setw(18) << right << (float)cosRef[i];
        if ( abs(float(sinres[i] - sinRef[i])) > precision)
        {
            ErrCntSin++;
            cout << setfill(' ') << setw(18) << right << "(sin failed)";
        }
        if ( abs(float(cosres[i] - cosRef[i])) > precision)
        {
            ErrCntCos++;
            cout << setfill(' ') << setw(18) << right << "(cos failed)";
        }
        cout << '\n';
    }
    cout << setfill('-') << setw(90) << '-' << '\n';

    // 打印表尾，是否有错误数据出现
    if (ErrCntCos + ErrCntSin > 0)
    {
        if (ErrCntSin > 0)
        {
            cout << "There are " << ErrCntSin << " sin results failed" << '\n';
        }
        if (ErrCntCos > 0)
        {
            cout << "There are " << ErrCntCos << " cos results failed" << '\n';
        }
        cout << "Test failed for percision: " << precision << '\n';
        cout << setfill('-') << setw(90) << '-' << '\n';
        return 1;
    }
    else
    {
        cout << "Test passed for percision: " << precision << '\n';
        cout << setfill('-') << setw(90) << '-' << '\n';
        return 0;
    }

}
