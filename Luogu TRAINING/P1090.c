#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//https://www.luogu.com.cn/problem/P1090

int * MergeSort(int *a, int n)  //归并排序 时间复杂度 O(NlogN)
{
    if (n>1)
    {
        int * result = (int *)malloc(n*sizeof(int)); //用于return数组的临时变量
        //分割数组
        int *i = a; //0 -> n/2-1 有n/2个
        int *j = a+n/2; //n/2 -> n-1 有n-n/2个

        i = MergeSort(i, n/2);
        j = MergeSort(j, n-n/2);
        
        //归并数组
        int index1=0; int index2=0;
        for (int loop=0;loop<n;loop++)  //循环归并
        {
            if (index1<(n/2)&&index2<(n-n/2))        //判断数列为空
            {
                if (*(i+index1)>=*(j+index2))
                {
                    *(result+loop) = *(j+index2);
                    index2++;
                }else if(*(i+index1)<*(j+index2))
                {
                    *(result+loop) = *(i+index1);
                    index1++;
                }
            }else if(index1==n/2)             //r1数列为空
            {
                for (int loop2=loop;loop2<n;loop2++)
                {
                    *(result+loop2) = *(j+index2);
                    index2++;
                }
                loop = n;//退出循环
            }else if(index2==(n-n/2))             //r2数列为空
            {
                for (int loop2=loop;loop2<n;loop2++)
                {
                    *(result+loop2) = *(i+index1);
                    index1++;
                }
                loop = n;//退出循环
            }
        }
        //返回并释放
        memcpy(a, result, n*sizeof(unsigned int));
        free(result);
        return a;
    }else
    {
        //memcpy(result, a, n*sizeof(int));
        return a;
    }
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    int * list = (int *)malloc(n*sizeof(int));
    for (int i=0;i<n;i++)
    {
        scanf("%d", list+i);
    }

    long long sum = 0;

    MergeSort(list, n);

    for (int i=0;i<n-2;i++)
    {
        *(list+i+1) = *(list+i) + *(list+i+1);
        sum += *(list+i+1);
        if (*(list+i+1)>*(list+i+2))
        {
            MergeSort(list+i+1, n-i-1);
        }
    }
    sum += *(list+n-2)+*(list+n-1);
    
    printf("%llu", sum);
}