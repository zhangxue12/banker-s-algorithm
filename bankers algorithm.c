
#include<stdio.h>
int p,s;                               //  s：资源的种类数  p:进程的个数
int MAX[50][50];
int Allocation[50][50];
int Need[50][50];
int Avaliable[50];
int Work[50];
int Finish[50];  
int Request[50];
int Sum[50];
int count;
int temp[50];
int num;                              // num 请求分配资源的进程号
int e;
								

void input()     //输入相关数
{   
int i,j;
printf("请输入资源的种类数: ");
scanf("%d",&s);
printf("请输入进程总数: ");                                
scanf("%d",&p);
printf("请输入各类资源总数: ");//每一类资源所需总数
for(i=0;i<s;i++)
    scanf("%d",&Sum[i]);

printf("请输入各进程的MAX: \n");//输入max

for(i=0;i<p;i++)    //  进程的个数
{	
	printf("第 %d 个进程：",i);
    for(j=0;j<s;j++)     //资源的种类数
{   
	scanf("%d",&MAX[i][j]);
}
}

printf("请输入各进程的ALL: \n");  //ALL数
for(i=0;i<p;i++)
{		
	printf("第 %d 个进程：",i);
	for(j=0;j<s;j++)
	{	
		scanf("%d",&Allocation[i][j]);
	}	
	
}
//output(Allocation,m,n);
for(i=0;i<p;i++)		
  for(j=0;j<s;j++)
   Need[i][j]=MAX[i][j]-Allocation[i][j];
//output(Need,m,n);
for(j=0;j<s;j++)
 for(i=0;i<p;i++)
{
	Sum[j]=Sum[j]-Allocation[i][j];  //各类资源总数
	Avaliable[j]=Sum[j];
    Work[j]=Avaliable[j];  //初始化work
}
//show( Avaliable,n);
}


void output()                        //输出各个矩阵
{   
//
	int i,j;
	for(i=0;i<p;i++)
	temp[i]=-1;
	printf("\n--------------------------------------------\n");
	printf("顺序为：  MAX--------ALL-------NEED-----AVA\n\n");
	for(i=0;i<p;i++)     //对MAX矩阵输出      p为行，s为列
	{   
		printf("P%d ",i);
		for(j=0;j<s;j++)
		   printf("%d ",MAX[i][j]);		
		printf("\t");
	 
			//	printf("ALL :\n");
		for(j=0;j<s;j++)	
		printf("%d ",Allocation[i][j]);
		printf("\t");
       
		//	printf("NEED :\n");
		for(j=0;j<s;j++)
			printf("%d ",Need[i][j]);
		printf("\t");
		if(i==0)   
		{
			//printf("AVA :");
			for(j=0;j<s;j++)
				printf("%d ",Avaliable[j]);
		}
		printf("\n");
	}
	
}


void recover(int i)   //分配了request后的各个矩阵恢复到原来的样子
{ 
	int f;
	for(f=0;f<s;f++)
	{
		Avaliable[f] = Avaliable[f] +Request[f];
		Allocation[i][f] = Allocation[i][f] - Request[f];
		Need[i][f] = Need[i][f] + Request[f];
		Work[f]=Avaliable[f];
	}
	printf("\n-----------------------------------------------\n");
	printf("已恢复初始状态!\n");
	output();
}


int safety()    //安全性检测
{
	int i,j,k ,v=0,y=0;
	int count;
	int n=5;
	
	for(i=0;i<p;i++)
	{
		Finish[i]=0;
	 }
    k=1;
	while(k)
{
		for(i=0,j=0;i<p;i++)
		{
			k=0;
			
			if(Finish[i]==1)   //如果finish[i]=true,那么跳到下一个进程
				continue;
			else
			{
				count=0;
				for(j=0;j<s;j++)
				{   printf("+++%d---\n",i);
					if(Need[i][j]<=Work[j])
						count++;        //确保每一类资源都通过比较
				}
				if(count==s)     
				{   
					printf("++++++%d",i);
					for(j=0;j<s;j++)
					{
						Work[j]=Work[j]+Allocation[i][j];
					}
                   for(j=0;j<s;j++)
					 //  printf("%d",Work[j]);
					Finish[i]=1;
				   k=1;
				    temp[y]=i;
					printf("--%d\n",y);
						y++;/////////////////////
				     //y++;
					//k++;     ////////////////////
				}
				else continue;
			}
		
		}
		v++;
		for(e=0;e<p;e++)
		printf(" finishi[%d]=%d ",e,Finish[e]);
		printf("\n");
	        count=p;
			for(j=0;j<p;j++)    //计数，看有多少个进程的finish还没有置为1
			{
				if(Finish[j]==1)
					count--;
			}
			if(count==0)
			{
				for(e=0;e<p;e++)
	            printf("%d",temp[e]);
			   printf("k=%d",k);
            }
			else 
			{  if(v<p)
			    k=1;
			   else break;
			}
			if(k==0)
			break;
		//	printf("123400");
	}//while 循环结束
	for(j=0;j<p;j++)       //如果有一个进程的finish没有置为1，那么返回值为1
	{
		if(!Finish[j])
			return 1;     
	}
	return 0;
}




void bank(int num)
{
	int i,f,m;
	printf("输入的是 P%d 进程: \n",num);
	printf("该进程Need： ");
	for(i=0;i<s;i++)
	printf("%d ",Need[num][i]);
	printf("\n");
	printf("请输入Request: ");
	for(i=0;i<s;i++)
	scanf("%d",&Request[i]);
	for(i=0;i<s;i++)
	{
	        
		 if (Request[i]>Need[num][i] ) 
			{
			    int r;
				printf("超出进程需求量!\n");
			
				//recover(num);
				
				printf("请重新输入请求分配资源的进程号: ");
	            scanf("%d",&r);
                bank(r);
			//	break;
			}
			else if (Request[i]>Avaliable[i]) 
			{   
				int r;
				printf("系统没有足够的可用资源量满足进程需要!\n\n");
			//	recover(num);
				printf("请重新输入请求分配资源的进程号: ");
	            scanf("%d",&r);
                bank(r);
			//	break;
				
			}
	}
	printf(" 请求成功！\n");
	//printf("输入成功，输入的是：");
	//for(f=0;f<s;f++)
	//	printf("%d ",Request[f]);
	printf("\n");
    printf("--------------------------------------\n");
	printf("进行试分配!\n");
	
	
	for( f=0;f<s;f++)
	{
		Avaliable[f] = Avaliable[f] - Request[f];
		Allocation[num][f] = Allocation[num][f] + Request[f];
		Need[num][f] = Need[num][f]-Request[f];
		Work[f]=Avaliable[f];
	}
	output();
	printf("试分配完成!\n"); 
    m=safety();
if(!m)            //0表示全部进程的finish都置为1，即有安全序列
{
	printf("安全序列为：");
	for(i=0;i<p-1;i++)          //////////////////////
	{
		printf("P%d -> ",temp[i]);
	}
    printf("P%d\n",temp[p-1]);  	
}
else 
  printf("不存在安全序列!\n");
}


int main()
{
	int x;
	int m=1;
	//	count(Allocation,Avaliable,sum,M,N);
    input();
	output();
    x=safety();
    while(m)
	{
		if(x==1)
	{
		printf("系统不安全!\n");
		m=0;
	}
	else 
	{
		printf("此时系统是安全的！\n");
		 printf("请输入请求分配资源的进程号: ");
	scanf("%d",&num);
    bank(num);
	output();
	safety();
    x=safety();
	m=1;
	}
	}
	return 0;
}





   