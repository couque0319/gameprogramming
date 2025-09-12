#include <stdio.h>
#include <stdarg.h>

double sum(int count, ...);

int main(void)
{
    double a1 = 10.5, a2 = 20.23;
    double b1 = 10.3, b2 = 245.67, b3 = 0.51, b4 = 198345.764, b5 = 1.0;

    printf("합계 = %lf\n", sum(2, a1, a2));
    printf("합계 = %lf\n", sum(5, b1, b2, b3, b4, b5)); // 인자 5개 유지

    return 0;
}

double sum(int count, ...)
{
    double total = 0, number;
    int i = 0;
    va_list ap;
    va_start(ap, count);

    while (i < count)
    {
        number = va_arg(ap, double); // 인수의 데이터 형은 double
        total += number;
        i++;
    }

    va_end(ap);
    return total;
}