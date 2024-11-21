#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	long long i,j;
	long long n,mi,ma;
	printf("请输入数据个数：");
	scanf("%lld",&n);
	printf("请输入最小值：");
	scanf("%lld",&mi);
	printf("请输入最大值：");
	scanf("%lld",&ma);
	srand(time(NULL));
	
    long long r[4],p[4],mod=ma-mi,ans;
    p[0]=1;
    p[1]=p[0]*32768;
    p[2]=p[1]*32768;
    p[3]=p[2]*32768;
	freopen("input.txt","w",stdout);
	printf("%d\n",n);
	while(n--)
	{
        r[0]=rand();
        r[1]=rand();
        r[2]=rand();
        r[3]=rand();
        ans=r[0]*p[0]%mod+r[1]*p[1]%mod+r[2]*p[2]%mod+r[3]*p[3]%mod;
        printf("%lld ",ans%mod+mi);
	}
    printf("\n");
    return 0;
}
