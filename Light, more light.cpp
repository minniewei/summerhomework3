#include<iostream>
#include<cstdio>
#include<cmath>
#define ERROR 1e-8
using namespace std;

int main(){
    double n;
    while( scanf( "%lf", &n ) != EOF && n != 0.0 ){
        unsigned int sqrt_num = (int)(sqrt(n)+ERROR);
        if( (double)(sqrt_num * sqrt_num) == n )
            printf( "yes\n" );
        else
            printf( "no\n" );
    }
    return 0;
}