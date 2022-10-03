/*
 * @Author: Peng Xuanyao 793063685@qq.com
 * @Date: 2022-09-30 17:11:28
 * @LastEditors: Peng Xuanyao 793063685@qq.com
 * @LastEditTime: 2022-10-03 11:48:45
 * @FilePath: /src/ReadFileVec.h
 * @Description: 
 */
#include <iostream>
#include <fstream>
using std::cerr;
using std::cout;
using std::setw;
using std::setfill;
using std::ifstream;

template <int N, typename Tm, typename Tv>
void ReadFileVec (char *fp, Tm OutBuf[N])
{
    int i;
    int j;
    Tv val;
    
    ifstream fp_strmi (fp);
    if (!fp_strmi.is_open())
    {
        cerr << "Error!\nThe file is not able to open!\n";
    }
    else
    {
        for (i = 0; i < N; i++)
        {
            fp_strmi >> val;
            OutBuf[i] = Tm (val);
        }
    }
    fp_strmi.close();
    cout << setw(60) << setfill('-') << '-' << '\n';
    cout << "Read file successfully!\n";
    cout << setw(60) << setfill('-') << '-' << '\n';
}