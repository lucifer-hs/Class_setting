#include <stdio.h>
#include <malloc.h>
#define N 2					/*ͣ����������ͣ����*/
#define Price 2				/*ÿ��λͣ������*/
typedef struct 
{
	int CarNo[N];			/*���ƺ�*/
	int CarTime[N];			/*����ʱ��*/
	int top;				/*ջָ��*/
} SqStack;					/*����˳��ջ����*/

	/*������������*/
typedef struct qnode
{
	int CarNo;			/*���ƺ�*/
	int CarTime;		/*����ʱ��*/    
	struct qnode *next;
} QNode;
typedef struct
{
	QNode *front;          /*���׺Ͷ�βָ��*/
	QNode *rear;
} LiQueue;


/*˳��ջ�Ļ��������㷨*/
void InitStack(SqStack *&s)
{
	s=(SqStack *)malloc(sizeof(SqStack));
	s->top=-1;
}


int StackEmpty(SqStack *s)//�ж�ջ�Ƿ�Ϊ�� 
{
	return(s->top==-1);
}


int StackFull(SqStack *s)//�ж�ջ�Ƿ�������ͣ�����Ƿ������� 
{
	return(s->top==N-1);
}

/*S�еĲ�����Ԫ��*/
int Push(SqStack *&s,int e1,int e2) //��ջ 
{
	if (s->top==N-1)
		return 0;
	s->top++;
	s->CarNo[s->top]=e1;//���ƺ���ջ 
	s->CarTime[s->top]=e2;//ʱ����ջ 
	return 1;
}

/*ɾ��S��ջ��Ԫ�أ�����e1,e2������ֵ*/
int Pop(SqStack *&s,int &e1,int &e2)
{
	if (s->top==-1)
		return 0;
	e1=s->CarNo[s->top]; 
	e2=s->CarTime[s->top];
	s->top--;
	return 1;
}
/*���ͣ����ʹ��״��*/ 
void DispStack(SqStack *s)
{
	int i;
	for (i=0;i<=s->top;i++)
	{
	printf("  %d\t  %d\t\t\t %d\t",i+1,s->CarNo[i],s->CarTime[i]);
	printf("\n");
	}
	
}

/*����Ϊ�����еĻ��������㷨*/
void InitQueue(LiQueue *&q)
{
	q=(LiQueue *)malloc(sizeof(LiQueue));
	q->front=q->rear=NULL;
}

int QueueLength(LiQueue *q)
{
	int n=0;
	QNode *p=q->front;
	while (p!=NULL)
	{
		n++;
		p=p->next;
	}
	return(n);
}
//�ж϶����Ƿ�Ϊ�� 
int QueueEmpty(LiQueue *q)
{
	if (q->rear==NULL)
		return 1;
	else
		return 0;
}
void enQueue(LiQueue *&q, int e,int w) 
{
	QNode *s;
    s=(QNode *)malloc(sizeof(QNode));
	s->CarNo=e;
	s->CarTime=w;
	s->next=NULL;
    if (q->rear==NULL)		/*������Ϊ��,���½���Ƕ��׽�����Ƕ�β���*/
		q->front=q->rear=s;
	else
	{
		q->rear->next=s;  /*��*s���������β,rearָ����*/
		q->rear=s;
	}
}
int deQueue(LiQueue *&q,int &e,int &w)
{
	QNode *t;
	if (q->rear==NULL)		/*����Ϊ��*/
		return 0;
	if (q->front==q->rear)  /*������ֻ��һ�����ʱ*/
	{
		t=q->front;
		q->front=q->rear=NULL;
	}
	else					/*�������ж�����ʱ*/
	{
		t=q->front;
		q->front=q->front->next;
	}
	e=t->CarNo;
	w=t->CarTime; 
    free(t);
	return 1;
}
/*������ʹ�����*/
void DisplayQueue(LiQueue *q)
{
	int i=1;
	QNode *p=q->front;
	while (p!=NULL)
	{
		printf("  %d\t  %d\t\t\t %d\t",i,p->CarNo,p->CarTime);
		printf("\n"); 
		p=p->next ;
		i++;
	}
}
int main()
{
    char choose;                /*����ѡ������*/
	int no,e1,time,e2,kind;     /*���ڴ�ų��ƺš���ǰͣ��ʱ��*/
	int i,j;
	SqStack *St,*St1;           /*��ʱջSt1,��ͣ�����м�ĳ�Ҫ�Ƴ�ȥʱ�����ڵ���*/
	LiQueue *Qu;
	InitStack(St);
	InitStack(St1);
	InitQueue(Qu);
	puts("\n                            ��ӭʹ��ͣ��������ϵͳ                          ");
	puts("\n                                                                            ");
	puts("\n��������ʾ��:����״̬��A��D��E ��ʾ�����У�A:��ʾ�������� D:��ʾ������ȥ,  	");
    puts("\n  C:��ʾ��ʾͣ����������E:��ʾ���������ÿ�����������������ɣ���:��	");
	puts("\n  ����״̬,���ƺ�,��ǰʱ�̣�������֮���Զ��ŷֿ��� ��������ʾ��:A,1,5  		");
	puts("\n���ڶ�ȡ������Ϣ...\n");
	
do
	{
	    printf("\n*****************************************************************");
    	printf("\n��ֱ���������״̬��A/D/C/E�������ƺź͵�ǰʱ�̣�����֮���Զ��ŷֿ���:\n");
	    scanf(" %c,%d,%d",&choose,&no,&time); 

	switch(choose)
	{

   /*************************** �������� ******************************/		
		case 'A':
		case 'a':

			if (!StackFull(St))			/*ͣ��������*/
			{
				Push(St,no,time);
				printf("�ó���ͣ�����е�λ����:%d\n",St->top+1);
				printf( "���ƺ�:\t\t%d\n", no );
    			printf( "����ʱ��:\t%d\n",time );
    			puts( "�Ƿ��շ�:\t��" );
			}
			else						/*ͣ������*/
			{   enQueue(Qu,no,time);
				printf("\nͣ�����������ó����������ڱ���е�λ����:%d\n",QueueLength(Qu));
				printf( "���ƺ�:\t\t%d\n", no );
    			printf( "����ʱ��:\t%d\n",time );
    			puts( "�Ƿ��շ�:\t��" );	
			}
		
		break;
  /************************* �����뿪 ********************************/
		case 'D':
		case 'd':

			printf("\n�����복����𡾳������1.����С���� 2.����ͳ� 3.��������:\n");
	        scanf("%d",&kind); 
		
			for (i=0;i<=St->top && St->CarNo[i]!=no;i++);
			if (i>St->top)       /*Ҫ�뿪�������ڱ����*/
			{          /*��������ֱ�Ӵӱ���Ͽ��ߣ���ʱ������ǰ�������Ҫ�ȿ�����·��Ȼ���������ŵ���β*/
				while (Qu->front->CarNo!=no )
				{
					enQueue(Qu,Qu->front->CarNo,Qu->front->CarTime );
				//	deQueue(Qu,Qu->front->CarNo );
				    Qu->front =	Qu->front->next ;
				}
				deQueue(Qu,no,time);
                printf("\n����ϳ��ƺ�Ϊ%d���������뿪!\n",no);
				puts( "[���ʹ�����]\n" );
   				puts( "[��λ]\t[���ƺ�]\t[����(��ʼ�Ʒ�)ʱ��]\n");
				DisplayQueue(Qu);
				printf("\n");
			
			}
			else                             /*Ҫ�뿪��������ͣ������*/
			{
				for (j=i;j<=St->top;j++)
				{
					Pop(St,e1,e2);           /*e1,e2�������ر�ɾԪ�صĳ��ƺź�ͣ��ʱ��*/
					Push(St1,e1,e2);		/*��������ʱջSt1�У���e1,e2���뵽��ʱջ��*/
				}
				Pop(St,e1,e2);				/*�������뿪*/
				printf("\n���ƺ�Ϊ%d������ͣ��ʱ��Ϊ��%d��ͣ������Ϊ:%d\n",no,time-e2,(time-e2)*Price*kind); 
				/*��С�������ԣ���ǰʱ�� ��ȥ �ó���ʱͣ����ʱ�̣��ٳ��Լ۸���Ƿ���,�����ڿͳ��Ϳ������ԣ���Ҫ����kind��С�����ļ۸�*/
				while (!StackEmpty(St1))	/*����ʱջSt1���»ص�St��*/
				{
					Pop(St1,e1,e2);
					Push(St,e1,e2);
				}
				if (!QueueEmpty(Qu))		/*�Ӳ���ʱ,����ͷ��ջSt*/
				{
					deQueue(Qu,e1,time);
					Push(St,e1,time);		/*�Ե�ǰʱ�俪ʼ�Ʒ�*/
				}

				printf("\n��ǰͣ�����еĳ����ĳ��ƺŷֱ���:");
				puts( "[ͣ����ʹ�����]\n" );
   				puts( "[��λ]\t[���ƺ�]\t[����(��ʼ�Ʒ�)ʱ��]\n");	//���ͣ�����еĳ���
				DispStack(St);
			}			
		
		break;
/************************   �鿴ͣ����  *********************************/
		case 'C':
		case 'c':
		if (!StackEmpty(St))  	                            //��ʾͣ�������
			{
				puts( "[ͣ����ʹ�����]\n" );
   				puts( "[��λ]\t[���ƺ�]\t[����(��ʼ�Ʒ�)ʱ��]\n");	//���ͣ�����еĳ���
				DispStack(St);
				printf("\n");
			}
			else  printf("\n��ǰͣ�������޳���\n\n");
			if (!QueueEmpty(Qu)) 
			{
				puts( "[���ʹ�����]\n" );
				puts( "[��λ]\t[���ƺ�]\t[����(��ʼ�Ʒ�)ʱ��]\n");
   				DisplayQueue(Qu);	
			}
			 else  printf("\n��ǰ�㳵�����޳���\n\n");
		break;		
/************************   ����  *********************************/
        case 'E':
		case 'e':
		
			printf("\n�����˳�ϵͳ...\n");				
	        
		
	   break;
/************************   ����  *********************************/
	   default:	/*�������*/
			printf("������������!\n");
			break;
	}
	} while(choose!='E'&&choose!='e');
    
}
