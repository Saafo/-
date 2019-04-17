#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

#define pi 3.1415926535897
#define epsilon 8.85e-12
#define rad 10 //圆和球的半径
#define dis 20 //圆心和球心到点电荷的距离
#define Q 10 //圆和球的总电荷
#define q 5 //点电荷的电荷
#define init_step 10 //整数步长，真实步长精度为其倒数


int main()
{

    clock_t start_time, finish_time; //计时器
    double cos_sigma,cos_beta; //sigma为立体平面内三角形夹角，beta是力与轴的夹角
    double distance, duration_time; //distance为圆或球上的点到点电荷的距离
    double error; //误差
    for(int int_step = 1 ; int_step > 0 ; int_step -= 1)
    {
        float float_step = int_step * 1.0 /init_step; //float_step处于0～1,是真实step
        start_time = clock();
        double sphere_sum_force = 0.0;
        double circle_sum_force = 0.0;
        double dQv = Q / (180 * 90.0 ) * float_step * float_step / 4;
        double dQs = Q / 180.0 * float_step / 2;

        //先算球对点的总电场力
        //用球坐标确定每个点，再算出距离，电场力
        # pragma omp parallel for reduction(+:sphere_sum_force)   //4核并行运算
        for(int i = 0 ; i < 90 * init_step ; i += int_step) //0~90平面角部分
        {
            float rho = i * 1.0 / init_step;
            for(float theta = 0.0 ; theta < 90 ; theta += float_step)
            {
                cos_sigma = cos(rho) * cos(theta);
                distance = sqrt(rad * rad + dis * dis - 2 * rad * dis * cos_sigma);
                cos_beta = (distance * distance + dis * dis - rad * rad) / (2 * distance * dis);
                sphere_sum_force += dQv * q / ( 4 * pi * epsilon * distance * distance) * cos_beta;
                printf("Rho = %f, Theta = %f, sum = %lf, id = %d\n", rho, theta, sphere_sum_force, omp_get_thread_num());
            }
        }
        # pragma omp parallel for reduction(+:sphere_sum_force)   //4核并行运算
        for(int i = 90 * init_step ; i < 180 * init_step ; i += int_step) //90~180平面角部分
        {
            float rho = i * 1.0 / init_step;
            for(float theta = 0.0 ; theta < 90 ; theta += float_step)
            {
                cos_sigma = 0 - cos(rho - 90) * cos(theta);
                distance = sqrt(rad * rad + dis * dis - 2 * rad * dis * cos_sigma);
                cos_beta = (distance * distance + dis * dis - rad * rad) / (2 * distance * dis);
                sphere_sum_force += dQv * q / ( 4 * pi * epsilon * distance * distance) * cos_beta;
                printf("Rho = %f, Theta = %f, sum = %lf, id = %d\n", rho, theta, sphere_sum_force, omp_get_thread_num());
            }
        }

        //再算环对点的总电场力
        for(float alpha = 0 ; alpha < 180 ; alpha += float_step)
        {
            distance = sqrt(rad * rad + dis * dis - 2 * rad * dis * cos(alpha));
            cos_beta = (distance * distance + dis * dis - rad * rad) / (2 * distance * dis);
            circle_sum_force += dQs * q / ( 4 * pi * epsilon * distance * distance) * cos_beta;
            printf("Alpha = %f, sum = %lf, id = %d\n", alpha, circle_sum_force, omp_get_thread_num());
        }

        // 数据尾处理
        sphere_sum_force *= 4;
        circle_sum_force *= 2;
        error = circle_sum_force / sphere_sum_force * 100;

        //时间处理部分
        finish_time = clock();
        duration_time = (double)(finish_time - start_time) / CLOCKS_PER_SEC;


        //文件写入部分
        FILE* fp = fopen("new_data.txt", "a+");
        fseek(fp, 0, SEEK_END);     //定位到文件末尾
        fprintf(fp, "%lf\t%lf\t%lf\t%lf\n", duration_time, sphere_sum_force, circle_sum_force, error);
        fclose(fp);

        //打印结果
        printf("%lf\t%lf\t%lf\t%lf\n", duration_time, sphere_sum_force, circle_sum_force, error);
    }
    system("pause");
    return 0;
}