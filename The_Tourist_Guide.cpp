#include <iostream>
#include <cstdio>
using namespace std;

int main(){
  int scenario = 0;
  int N, R;
  while( scanf("%d%d", &N, &R) != EOF &&
       N != 0 && R != 0 ){
    int capacity[105][105] = {0};
    for( int i = 0 ; i < R ; ++i ){
      int C1, C2, P;
      scanf("%d%d%d", &C1, &C2, &P);
      capacity[C1][C2] = capacity[C2][C1] = P;
    }

    for( int k = 1 ; k <= N ; ++k ){
      for( int i = 1 ; i <= N ; ++i ){
        for( int j = 1 ; j <= N ; ++j ){
          capacity[i][j] = max(capacity[i][j], min(capacity[i][k], capacity[k][j]));
        }
      }
    }

    int S, D, T;
    scanf("%d%d%d", &S, &D, &T);
    printf("Scenario #%d\n", ++scenario);
    printf("Minimum Number of Trips = %d\n\n", T / (capacity[S][D]-1) + ((T % (capacity[S][D]-1) > 0)? 1 : 0) );
  }

  return 0;
}