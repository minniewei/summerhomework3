#include <iostream>
#include <cstdio>
using namespace std;

long long int mod(long long int n, long long int a, long long int maxN){
  if( n == 0 ) return 1;
  if( n == 1 ) return a;

  long long int modValue = mod(n/2, a, maxN);
  if( n % 2 == 0 ){
    return (modValue * modValue) % maxN;
  }
  else {
    return ((modValue * modValue) % maxN) * a % maxN;
  }
}

bool checkCarmichael(int n, int a){
  if( mod( (long long int)n, (long long int)a, (long long int)n ) == a ){
    return true;
  }
  else {
    return false;
  }
}

int main(){
  bool composite[65005] = {true, true, false};
  for( int i = 2 ; i <= 65000 ; ++i ){
    if( !composite[i] ){
      for( int j = i+i ; j <= 65000 ; j += i ){
        composite[j] = true;
      }
    }
  }

  int n;
  while( scanf("%d", &n) != EOF && n != 0 ){
    bool isCarmichael = true;
    if( !composite[n] ) {
      isCarmichael = false;
    }

    for( int i = 2 ; i < n && isCarmichael ; ++i ){
      isCarmichael = isCarmichael && checkCarmichael(n, i);  
    }

    if( isCarmichael ){ 
      printf("The number %d is a Carmichael number.\n", n);
    }
    else{
      printf("%d is normal.\n", n);
    }
  }
  return 0;
}