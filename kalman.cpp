 
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/arch/cpu.h>
#include <zephyr/sys/printk.h>

using namespace std;

class KalmanFilter
{
    double Q = 0.00001;
    double R = 0.001;
    double X = 0, P = 1, K;
public:
	KalmanFilter(double initValue);
	virtual ~KalmanFilter() {}
	virtual void measurementUpdate(void);
	virtual double update(double measurement);  
};

KalmanFilter::KalmanFilter(double initValue)
{
    X = initValue;
}

//예전값들을 공식으로 계산한다
void KalmanFilter::measurementUpdate()
{
    K = (P + Q) / (P + Q + R);
    P = R * (P + Q) / (R + P + Q);
}

//현재값을 받아 계산된 공식을 적용하고 반환한다
double KalmanFilter::update(double measurement)
{
    measurementUpdate();
    X = X + (measurement - X) * K;

    return X;
}


void kalman_example(void)
{
    KalmanFilter mKalmanAccX(0.0f);
    KalmanFilter mKalmanAccY(0.0f);
    KalmanFilter mKalmanAccZ(0.0f);

    float x=0, y=0, z=0;
    float filteredX=0, filteredY=0,filteredZ=0;

    for(;;) 
    {
        //read_accelerometer(&x, &y, &z);
        filteredX = (float) mKalmanAccX.update(x);
        filteredY = (float) mKalmanAccY.update(y);
        filteredZ = (float) mKalmanAccY.update(z);
        printk("kalman (x,y) = (%f, %f)", filteredX, filteredY);
    }
 
}