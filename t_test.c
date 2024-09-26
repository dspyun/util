
#include <math.h>
#include <zephyr/kernel.h>
#include <stdio.h>
#include <string.h>
#include "slm_util.h"
#include "slm_at_host.h"
#include "slm_at_factory.h"



double mean(double arr[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

double variance(double arr[], int n) {
    double avg = mean(arr, n);
    double var_sum = 0.0;
    for (int i = 0; i < n; i++) {
        var_sum += (arr[i] - avg) * (arr[i] - avg);
    }
    return var_sum / (n - 1); // Sample variance
}

double t_test(double group1[], int n1, double group2[], int n2) {
    double mean1 = mean(group1, n1);
    double mean2 = mean(group2, n2);
    double var1 = variance(group1, n1);
    double var2 = variance(group2, n2);
    
    double pooled_variance = ((var1 / n1) + (var2 / n2));
    double t_value = (mean1 - mean2) / sqrt(pooled_variance);
    
    return t_value;
}


int t_test_example(void) {
    double group1[] = {5.1, 4.9, 5.2, 5.0, 4.8}; // 첫 번째 집단
	double group2[] = {5.3, 4.7, 5.1, 4.8, 5.0}; // 두 번째 집단
    //double group2[] = {6.1, 6.3, 6.2, 5.9, 6.4}; // 두 번째 집단
    int n1 = sizeof(group1) / sizeof(group1[0]);
    int n2 = sizeof(group2) / sizeof(group2[0]);

    double t_value = t_test(group1, n1, group2, n2);
    printk("t-test : t-value: %f\n", t_value);

    return t_value;
}
