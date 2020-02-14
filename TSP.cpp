/*
 * @Author: quanbin 
 * @Date: 2020-01-07 12:13:54 
 * @Last Modified by: quanbin
 * @Last Modified time: 2020-01-07 12:14:14
 */
//vscode
#include <iostream>
using namespace std;

const int maxn = 100;
int n;             //节点数
int G[maxn][maxn]; //图矩阵
int path[maxn];    //存放结果
int bestRes;        //临时最优结果
int currentRes;     //临时结果
int bestPath[maxn];   //存放最优结果

//交换函数
void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

//回溯
void backTrackTsp(int t)
{
    cout << "当前解为: ";
    for(int i = 1; i <= n; i++){
        cout << path[i];     
    }
    cout << endl;
    //到达叶子节点
    if(t == n){
        if(G[path[t-1]][path[t]] != 0 && G[path[t]][1] != 0){                     //剪枝条件1:有回路 
            if(currentRes + G[path[t-1]][path[t]] + G[path[n]][1] < bestRes){     //剪枝条件2:比最优解更优
                bestRes = currentRes + G[path[t-1]][path[t]] + G[path[t]][1];
                
                //输出
                for(int i = 1; i <= n; i++){
                    bestPath[i] = path[i];
                }
                
            }
        }
    }
    
    else{
        
        for(int i = t; i <= n; i++){
            if(G[path[t-1]][path[t]] != 0 && currentRes + G[path[t-1]][path[t]] < bestRes ){
                swap(path[i], path[t]);
                currentRes += G[path[t-1]][path[t]];
                backTrackTsp(t + 1);
                currentRes -= G[path[t-1]][path[t]];  
                swap(path[i], path[t]);
            }
        }
    }

}

int main()
{
    //输入
    cout << "请输入节点个数" << endl;
    cin >> n;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin >> G[i][j];
        }
    }

    //初始化
    currentRes = 0;
    bestRes = 100000;
    for(int i = 1; i <= n; i++){
        path[i] = i;
    }

    backTrackTsp(2);

    cout << "最佳路径为" << endl;
    for(int i = 1; i <= n; i++){
        if(i != n)
            cout << bestPath[i] << " --> ";
        else{
            cout << bestPath[i] << " --> 1" << endl;;
        }
    }
    cout << "最短路径长度为" << bestRes << endl;
    return 0;
}