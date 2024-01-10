#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

void printPath(vector<vector<vector<int>>> &paths, int t, int i, int j){
  if(t == 0){
    printf("%d %d", i + 1, j + 1);
    return;
  }

  printPath(paths, t-1, i, paths[t][i][j]);
  printf(" %d", j + 1);
}

int main(){
  int n;
  while(scanf("%d", &n) != EOF){
    vector<vector<double>> conversionTable(n, vector<double>(n, 0));
    for(int i = 0 ; i < n ; ++i){
      for(int j = 0 ; j < n ; ++j){
        if(i == j){
          conversionTable[i][j] = 1;
          continue;
        }
        scanf("%lf", &conversionTable[i][j]);
      }
    }

    vector<vector<vector<double>>> values(n, vector<vector<double>>(n, vector<double>(n)));
    vector<vector<vector<int>>> paths(n, vector<vector<int>>(n, vector<int>(n, -1)));    
    values[0] = conversionTable;

    int item = -1, itemT = -1;
    for(int t = 1 ; t < n && item == -1 ; ++t){
      for(int i = 0 ; i < n && item == -1 ; ++i){
        for(int j = 0 ; j < n && item == -1 ; ++j){
          values[t][i][j] = -1.0;
          for(int k = 0 ; k < n ; ++k ){
            double newRate = values[t-1][i][k] * conversionTable[k][j];
            if(newRate > values[t][i][j]){
              values[t][i][j] = newRate;
              paths[t][i][j] = k;
            }
          }
        }

        if(values[t][i][i] > 1.01){
          item = i;
          itemT = t;
          break;
        }
      }
    }

    if(item == -1){
      printf("no arbitrage sequence exists\n");
      continue;
    }

    printPath(paths, itemT, item, item);
    printf("\n");
  }
  return 0;
}