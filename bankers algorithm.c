
#include<stdio.h>
int p,s;                               //  s����Դ��������  p:���̵ĸ���
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
int num;                              // num ���������Դ�Ľ��̺�
int e;
								

void input()     //���������
{   
int i,j;
printf("��������Դ��������: ");
scanf("%d",&s);
printf("�������������: ");                                
scanf("%d",&p);
printf("�����������Դ����: ");//ÿһ����Դ��������
for(i=0;i<s;i++)
    scanf("%d",&Sum[i]);

printf("����������̵�MAX: \n");//����max

for(i=0;i<p;i++)    //  ���̵ĸ���
{	
	printf("�� %d �����̣�",i);
    for(j=0;j<s;j++)     //��Դ��������
{   
	scanf("%d",&MAX[i][j]);
}
}

printf("����������̵�ALL: \n");  //ALL��
for(i=0;i<p;i++)
{		
	printf("�� %d �����̣�",i);
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
	Sum[j]=Sum[j]-Allocation[i][j];  //������Դ����
	Avaliable[j]=Sum[j];
    Work[j]=Avaliable[j];  //��ʼ��work
}
//show( Avaliable,n);
}


void output()                        //�����������
{   
//
	int i,j;
	for(i=0;i<p;i++)
	temp[i]=-1;
	printf("\n--------------------------------------------\n");
	printf("˳��Ϊ��  MAX--------ALL-------NEED-----AVA\n\n");
	for(i=0;i<p;i++)     //��MAX�������      pΪ�У�sΪ��
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


void recover(int i)   //������request��ĸ�������ָ���ԭ��������
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
	printf("�ѻָ���ʼ״̬!\n");
	output();
}


int safety()    //��ȫ�Լ��
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
			
			if(Finish[i]==1)   //���finish[i]=true,��ô������һ������
				continue;
			else
			{
				count=0;
				for(j=0;j<s;j++)
				{   printf("+++%d---\n",i);
					if(Need[i][j]<=Work[j])
						count++;        //ȷ��ÿһ����Դ��ͨ���Ƚ�
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
			for(j=0;j<p;j++)    //���������ж��ٸ����̵�finish��û����Ϊ1
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
	}//while ѭ������
	for(j=0;j<p;j++)       //�����һ�����̵�finishû����Ϊ1����ô����ֵΪ1
	{
		if(!Finish[j])
			return 1;     
	}
	return 0;
}




void bank(int num)
{
	int i,f,m;
	printf("������� P%d ����: \n",num);
	printf("�ý���Need�� ");
	for(i=0;i<s;i++)
	printf("%d ",Need[num][i]);
	printf("\n");
	printf("������Request: ");
	for(i=0;i<s;i++)
	scanf("%d",&Request[i]);
	for(i=0;i<s;i++)
	{
	        
		 if (Request[i]>Need[num][i] ) 
			{
			    int r;
				printf("��������������!\n");
			
				//recover(num);
				
				printf("�������������������Դ�Ľ��̺�: ");
	            scanf("%d",&r);
                bank(r);
			//	break;
			}
			else if (Request[i]>Avaliable[i]) 
			{   
				int r;
				printf("ϵͳû���㹻�Ŀ�����Դ�����������Ҫ!\n\n");
			//	recover(num);
				printf("�������������������Դ�Ľ��̺�: ");
	            scanf("%d",&r);
                bank(r);
			//	break;
				
			}
	}
	printf(" ����ɹ���\n");
	//printf("����ɹ���������ǣ�");
	//for(f=0;f<s;f++)
	//	printf("%d ",Request[f]);
	printf("\n");
    printf("--------------------------------------\n");
	printf("�����Է���!\n");
	
	
	for( f=0;f<s;f++)
	{
		Avaliable[f] = Avaliable[f] - Request[f];
		Allocation[num][f] = Allocation[num][f] + Request[f];
		Need[num][f] = Need[num][f]-Request[f];
		Work[f]=Avaliable[f];
	}
	output();
	printf("�Է������!\n"); 
    m=safety();
if(!m)            //0��ʾȫ�����̵�finish����Ϊ1�����а�ȫ����
{
	printf("��ȫ����Ϊ��");
	for(i=0;i<p-1;i++)          //////////////////////
	{
		printf("P%d -> ",temp[i]);
	}
    printf("P%d\n",temp[p-1]);  	
}
else 
  printf("�����ڰ�ȫ����!\n");
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
		printf("ϵͳ����ȫ!\n");
		m=0;
	}
	else 
	{
		printf("��ʱϵͳ�ǰ�ȫ�ģ�\n");
		 printf("���������������Դ�Ľ��̺�: ");
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





   