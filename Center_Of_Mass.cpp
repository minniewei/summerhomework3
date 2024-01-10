#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
/////////////////////////////////////
struct point{
	double x, y;
	point(double a, double b){
		x = a;
		y = b;
	}
	double Distance(point t){
		return sqrt((x-t.x)*(x-t.x) + (y-t.y)*(y-t.y));
	}
};
vector<point> p;
vector<int> CH; //存放凸包頂點序號   模擬棧
int testCase, top, cc=0, nodeNum;
/////////////////////////////////////
void Input(){
	p.clear();
	CH.clear();
	CH.resize(nodeNum+5);
	double xx, yy;
	for(int i=0; i<nodeNum; i++){
		cin >> xx >> yy;
		p.push_back(point(xx, yy));
	}
}

bool cmp(point a, point b){
	if(a.y == b.y)  return a.x < b.x;
	return a.y < b.y;
}

bool turnRight(point px1, point px2, point pp){
    const double eps = 1e-20;
	if((px2.x - px1.x)*(pp.y - px2.y) - (pp.x - px2.x)*(px2.y - px1.y) <= eps) return true;
	return false;
}
void ComputeCH(){
	sort(p.begin(), p.end(), cmp);
	CH[0] = 0;
	CH[1] = 1;

	top = 1;
	//從起點0到到排序最後點作凸包右鏈  過程1
	for(int i=2; i<nodeNum; i++){
		while( top && turnRight(p[CH[top-1]], p[CH[top]], p[i]) )
		{
		   top--;
		}
		CH[++top] = i;
	}

	int len = top;
	//從排序最高點到到起點0fab反向作凸包右鏈  過程2
	CH[++top] = nodeNum-2;
	for(int i=nodeNum-3; i>=0; i--){
		//top!=len, 不考慮已在過程1生成凸包上的點
		while( top!=len && turnRight(p[CH[top-1]], p[CH[top]], p[i]) )
		{
		   top--;
		}
		CH[++top] = i;
	}
}

/*計算凸多邊形重心模板  該模板另外在求解的過程中，不
  需要考慮點的輸入順序是順時針還是逆時針，相除後就抵消了。
*/
double Area(point p0, point p1, point p2){
    double area = 0;
    area =  p0.x * p1.y + p1.x * p2.y + p2.x * p0.y - p1.x * p0.y - p2.x * p1.y - p0.x * p2.y;
    return area / 2 ;
}
void ComputeGC(){
	int sPos = 0;
    double sum_x , sum_y , sum_area , area;
	sum_x = sum_y = sum_area = area = 0;
	//一定得按照序進行套用，我從最左下點開始,逆時針掃整個凸包
    for(int i=2; i<top ; i++){
       area = Area(p[CH[sPos]],p[CH[sPos+1]],p[CH[i]]) ;
       sum_area += area ;
       sum_x += (p[CH[sPos]].x + p[CH[sPos+1]].x + p[CH[i]].x) * area ;
       sum_y += (p[CH[sPos]].y + p[CH[sPos+1]].y + p[CH[i]].y) * area ;
       p[CH[sPos+1]] = p[CH[i]] ;
    }
	printf ("%.3lf %.3lf\n", sum_x/sum_area/3, sum_y/sum_area/3);
}

///////////////////////////////////////////////////////
int main(){
	while(cin >> nodeNum && nodeNum >= 3)
	{
		Input();
		ComputeCH(); //計算凸包
		ComputeGC();  //計算凸多邊形重心並輸出
	}
	return 0;
}