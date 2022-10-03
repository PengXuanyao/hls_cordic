#include <ap_fixed.h>
#include <ap_int.h>

#define WA 17   // 输入数据位宽
#define FA 14   // 输入数据小数位宽
#define WS 16   // 输出数据位宽
#define FS 14   // 输出数据小数位宽

typedef ap_fixed<WA, WA-FA> di_t;
typedef ap_fixed<WS, WS-FS> do_t;
typedef ap_uint<2> flag_t;

const di_t PI = 3.1415926;
const do_t Kn = 0.607252935;    // 这个是cordic迭代系数

void cordic(di_t alpha, do_t &mysin, do_t &mycos);

