#include <graphics.h>
#include<time.h>
#include <stdio.h>
#include <windows.h> 
int q_x;
int state[1][2]={1,4};
struct brick
{
	int left;//������
	int top;//������
	int right;//������
	int bottom;//������
	int exist;//�Ƿ����
};
struct brick b[3][5];
void initb()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<5;j++)
		{
			b[i][j].left=j*130;
			b[i][j].top=i*40;
			b[i][j].right=(j+1)*130;
			b[i][j].bottom=(i+1)*40;
			b[i][j].exist=1;
		}
	}
}
void printb()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(b[i][j].exist==1)
			{
				setfillcolor(RED);
				fillrectangle(b[i][j].left,b[i][j].top,b[i][j].right,b[i][j].bottom);
			}
		}
	}
}
void crash(int x,int y,int s[1][2])//�������
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(b[i][j].exist==1)
			{
				if(b[i][j].left<=x&&b[i][j].right>=x)
				{
					if(s[0][0]==2)//��������
					{
						if(y==b[i][j].bottom)
						{
							b[i][j].exist=0;//ש����ʧ
							state[0][0]=1;//�ı�״̬
						}
					}
				}
				if(b[i][j].left<=x&&b[i][j].right>=x)
				{
					if(s[0][0]==1)//�����½�
					{
						if(y+12==b[i][j].top)
						{
							b[i][j].exist=0;
							state[0][0]=2;
						}
					}
				}
				if(b[i][j].bottom>=y&&b[i][j].top<=y)
				{
					if(s[0][1]==3)//��������
					{
						if(x==b[i][j].right)
						{
							b[i][j].exist=0;
							state[0][1]=4;
						}
					}
				}
				if(b[i][j].bottom>=y&&b[i][j].top<=y)
				{
					if(s[0][1]==4)
					{
						if(x+12==b[i][j].left)
						{
							b[i][j].exist=0;
							state[0][1]=3;
						}
					}
				}
			}
		}
	}
}
//���̺߳���   
DWORD WINAPI ThreadFun(LPVOID pM)  
{
	MOUSEMSG m;
	while(1)
	{
		m=GetMouseMsg();
			if(m.x>590) m.x=590;
			setfillcolor(BLUE);
			fillrectangle(m.x,390,m.x+60,400);
			clearrectangle(0,390,m.x,400);
			clearrectangle(m.x+60,390,650,400);
			q_x=m.x;
	}
    return 0;  
}    
DWORD WINAPI ThreadFun2(LPVOID pM)  
{
	int h=130,p=0;
	srand((unsigned)time(0));
	p=rand()%650;//����һ��״̬����1�������䣬2����������3������4������
	int h1=0,p1=0;
	initb();
	while(1)
	{
		Sleep(5);
		clearrectangle(0,0,650,390);
		fillcircle(p+6,h+6,6);
		setfillcolor(GREEN);
		floodfill(p+6,h+6,getlinecolor());
		crash(p,h,state);
		if(h+12==390) 
		{
			state[0][0]=2;
			if(!(p>=q_x&&p<=q_x+60)) break;
		}
		if(h==0) state[0][0]=1;
		if(p+12==650) state[0][1]=3;
		if(p==0) state[0][1]=4;
		if(state[0][0]==1) h++;
		if(state[0][0]==2) h--;
		if(state[0][1]==3) p--;
		if(state[0][1]==4) p++;
		printb();
	}
    return 0;  
} 
//����������ν��������ʵ�������߳�ִ�еĺ�����   
int main()  
{  
	initgraph(650,400);
    printf("     ��򵥵Ĵ������߳�ʵ��\n");  
    printf("--by MoreWindows( http://blog.csdn.net/MoreWindows)--\n\n");  
  
    HANDLE handle = CreateThread(NULL, 0, ThreadFun, NULL, 0,NULL);  
    HANDLE handle1 = CreateThread(NULL, 0, ThreadFun2, &q_x, 0,NULL);
    WaitForSingleObject(handle1, INFINITE);  
    WaitForSingleObject(handle, INFINITE);  
    return 0;  
}  

