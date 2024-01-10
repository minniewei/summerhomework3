#include <iostream>
using namespace std;
 
int t, n, a[30][30], mx;
string s;
 
int main(){
    cin >> t;
    while (t--){
        cin >> s;
        n = s.length();
        for (int j = 1; j <= n; j++){
            a[1][j] = s[j-1]-'0';
            a[1][j] += a[1][j-1];
        }
        for (int i = 2; i <= n; i++){
            cin >> s;
            for (int j = 1; j <= n; j++){
                a[i][j] = s[j-1]-'0';
                a[i][j] += a[i][j-1];
            }
        }
        mx = 0;
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
                a[i][j] += a[i-1][j];
                for (int k = 0; k < i; k++){
                    for (int l = 0; l < j; l++){
                        int tmp = a[i][j];
                        tmp -= a[i][l];
                        tmp -= a[k][j];
                        tmp += a[k][l];
                        if (tmp == (i-k)*(j-l)) mx = max(mx, tmp);
                    }
                }
            }
        }
        cout << mx << "\n";
        if (t != 0) cout << "\n";
    }
}