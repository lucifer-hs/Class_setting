#include <conio.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// ��ʾ�ַ��� szPrompt ���ȴ��û�������������ڳ������ʹ�ã� 
#define Pause( szPrompt ) printf( "%s", szPrompt ),getch()

typedef struct carinformation    // ������Ϣ
{
 char szRegistrationMark[64];   // ���ƺ�
 char szArrivalTime[16];    // ����ʱ��
 char szEntranceTime[16];   // ����ͣ����(��ʼ�Ʒ�)ʱ��
 char szDepartureTime[16];   // �뿪ʱ��
} TCARINFORMATION, *LPTCARINFORMATION;

//����һ��վ 
typedef struct carstack
{
 LPTCARINFORMATION lpCarInformation;  // ������Ϣ  
 int nTop;     // ջ��Ԫ���±�
 int nStackSize;     // ջ����
} TCARSTACK, *LPTCARSTACK;


// ��ʼ��ջ lpCarStack, ������������Ϊ nSize 
void InitStack( LPTCARSTACK &lpCarStack, int nSize )
{
 lpCarStack = ( LPTCARSTACK ) malloc( sizeof ( TCARSTACK ) );
 lpCarStack->lpCarInformation = ( LPTCARINFORMATION ) malloc(
  nSize * sizeof ( TCARINFORMATION )
  );
 lpCarStack->nTop = -1;
 lpCarStack->nStackSize = nSize;
}


// ������Ϣ carinfo ��ջ lpCarStack
void Push( LPTCARSTACK &lpCarStack, TCARINFORMATION carinfo )
{
 lpCarStack->nTop++;
 lpCarStack->lpCarInformation[lpCarStack->nTop] = carinfo;
}


// ������Ϣ��ջ lpCarStack �е��������� carinfo
void Pop( LPTCARSTACK &lpCarStack, TCARINFORMATION &carinfo )
{
 carinfo = lpCarStack->lpCarInformation[lpCarStack->nTop];
 lpCarStack->nTop--;
}


// ��ջ lpCarstack ��,���� TRUE;����,���� FALSE
BOOL IsStackEmpty( LPTCARSTACK lpCarStack )
{
 return lpCarStack->nTop == -1;
}


// ��ջ lpStackFull ��,���� TRUE;����,���� FALSE
BOOL IsStackFull( LPTCARSTACK lpCarStack )
{
 return lpCarStack->nTop == ( lpCarStack->nStackSize - 1 );
}


// ����ջ lpCarStack,��ָ�� lpCarStack ��Ϊ NULL
void DestroyStack( LPTCARSTACK &lpCarStack )
{
 free( lpCarStack->lpCarInformation );
 free( lpCarStack );
 lpCarStack = NULL;
}


typedef struct carnode     // ���ӽ����Ϣ
{
 TCARINFORMATION carinfo;   // ������Ϣ
 struct carnode *lpNext;    // ָ����һ��Ԫ�ص�ָ��
} TCARNODE, *LPTCARNODE;


typedef struct carqueue     // ����
{
 LPTCARNODE lpHead;    // ͷ���
 LPTCARNODE lpRear;    // ָ��ǰ��β��ָ��
 int nEffectiveSize;    // ��ǰ����Ԫ�ظ���
} TCARQUEUE, *LPTCARQUEUE;


// ��ʼ������ lpCarQueue
void InitQueue( LPTCARQUEUE &lpCarQueue )
{
 lpCarQueue = ( LPTCARQUEUE ) malloc( sizeof( TCARQUEUE ) );
 lpCarQueue->lpHead = ( LPTCARNODE) malloc( sizeof( TCARNODE ) );
 lpCarQueue->lpHead->lpNext = NULL;
 lpCarQueue->lpRear = lpCarQueue->lpHead;
 lpCarQueue->nEffectiveSize = 0;
}


// ������Ϣ carinfo ��� lpCarQueue
void EnQueue( LPTCARQUEUE &lpCarQueue, TCARINFORMATION carinfo )
{
 LPTCARNODE lpCarNode = ( LPTCARNODE ) malloc( sizeof( carnode ) );
 lpCarNode->carinfo = carinfo;
 lpCarNode->lpNext = NULL;
 lpCarQueue->lpRear->lpNext = lpCarNode;
 lpCarQueue->lpRear = lpCarQueue->lpRear->lpNext;
 lpCarQueue->nEffectiveSize++;
}


// ��ͷԪ�ش����� lpCarQueue �г��Ӳ����� carinfo
void DeQueue( LPTCARQUEUE &lpCarQueue, TCARINFORMATION &carinfo )
{
 LPTCARNODE lpTemp = lpCarQueue->lpHead->lpNext;
 carinfo = lpTemp->carinfo;
 lpCarQueue->lpHead->lpNext = lpTemp->lpNext;
 free( lpTemp );
 lpCarQueue->nEffectiveSize--;
}


// ������ lpCarQueue Ϊ��,���� TRUE;����,���� FALSE
BOOL IsQueueEmpty( LPTCARQUEUE lpCarQueue )
{
 return lpCarQueue->nEffectiveSize == 0;
}


// �������� lpCarQueue
void DestroyQueue( LPTCARQUEUE &lpCarQueue )
{
 LPTCARNODE lpNextCarNode = NULL;
 for ( LPTCARNODE lpCarNode = lpCarQueue->lpHead; lpCarNode != NULL; lpCarNode = lpNextCarNode )
 {
  lpNextCarNode = lpCarNode->lpNext;
  free( lpCarNode );
 }
 free( lpCarQueue );
 lpCarQueue = NULL;
}


// ���ַ���ʱ���ʽת��Ϊ����(����)��ʽ,���� 12:36 ����ת��Ϊ 756 ( 12 * 60 + 36 )
int ConvertTimeFormat( char *lpTime )
{
 int nHour = 0;
 int nMinute = 0;

 sscanf( lpTime, "%d:%d", &nHour, &nMinute );

 return nHour * 60 + nMinute;
}


// ������ͣ�����ڵ�ͣ��ʱ�� nContinuanceMinutes (����)�������
double CalculateExpense( int nContinuanceMinutes )
{
 return nContinuanceMinutes * ( 5.0 / 60 );
}


int main( void )
{
 int nParkCapability = 0;   // ͣ��������

 putchar( '\n' );
 printf( "������ͣ��������:" );
 scanf( "%d", &nParkCapability );
 
 LPTCARSTACK lpCarStack = NULL;   // ͣ����,��ջģ��
 InitStack( lpCarStack, nParkCapability );

 LPTCARQUEUE lpCarQueue = NULL;   // ���,������ģ��
 InitQueue( lpCarQueue );

 char cCommandType = NULL;   // ��������
 char szUserInput[128] = { NULL };  // �û�����
 do 
 {
  putchar( '\n' );
  printf( "--------------------" );
  puts( "[��������]" );
  puts( "1 - ��������" );
  puts( "2 - �����뿪" );
  puts( "3 - ֹͣ����" );
  puts( "4 - ��ʾ��ǰͣ�����ͱ��ʹ�����" );
  putchar( '\n' );
  puts( "��:" );
  puts( "1,��A1234,14:26" );
  puts( "2,��A1234,16:51" );
  puts( "3" );
  puts( "4" );
  putchar( '\n' );
  printf( "����������:" );
  scanf( "%s", szUserInput );
  puts( "--------------------" );

  char szCarInformation[128] = { NULL };
  sscanf( szUserInput,   // �����������복����Ϣ�ֿ����
   "%c,%s",
   &cCommandType,   // �û������ǰ�벿��,����������
   szCarInformation  // �û�����ĺ�벿��,��������Ϣ
   );

  char *lpCommaLocation = NULL;  // ������Ϣ�ַ����еĶ���λ��

  for ( lpCommaLocation = szCarInformation; *lpCommaLocation != '\0'; lpCommaLocation++ )
  {
   if ( *lpCommaLocation == ',' )
   {
    break;
   }
  }
  *lpCommaLocation = '\0';
  
  TCARINFORMATION carinfo = { NULL }; // �洢�����û�����ĳ�����Ϣ
  
  strcpy( carinfo.szRegistrationMark, szCarInformation );

  if ( cCommandType == '1' )
  {
   strcpy( carinfo.szArrivalTime, lpCommaLocation + 1 );

   if ( FALSE == IsStackFull( lpCarStack ) )
   {
    strcpy( carinfo.szEntranceTime, carinfo.szArrivalTime );
    Push( lpCarStack, carinfo );
    printf( "�ѽ���ͣ������ %d ����λ\n",
     lpCarStack->nTop + 1
     );
    printf( "���ƺ�:\t\t%s\n", carinfo.szRegistrationMark );
    printf( "����ʱ��:\t%s\n", carinfo.szEntranceTime );
    puts( "�Ƿ��շ�:\t��" );
   }
   else
   {
    EnQueue( lpCarQueue, carinfo );
    printf( "ͣ��������,��ͣ���ڱ���ĵ� %d ����λ\n",
     lpCarQueue->nEffectiveSize
     );
    printf( "���ƺ�:\t\t%s\n", carinfo.szRegistrationMark );
    printf( "ͣ��ʱ��:\t%s\n", carinfo.szArrivalTime );
    puts( "�Ƿ��շ�:\t��" );
   }
  }
  else if ( cCommandType == '2' )
  {
   strcpy( carinfo.szDepartureTime, lpCommaLocation + 1 );

   LPTCARSTACK lpTempCarStack = NULL;
   InitStack( lpTempCarStack, nParkCapability );
   
   TCARINFORMATION carinfoOut = { NULL };

   BOOL bIsCarFound = FALSE;
   while ( FALSE == IsStackEmpty( lpCarStack ) )
   {
    Pop( lpCarStack, carinfoOut );
    if ( 0 != strcmp( carinfoOut.szRegistrationMark, carinfo.szRegistrationMark ) )
    {
     Push( lpTempCarStack, carinfoOut );
    }
    else
    {
     bIsCarFound = TRUE;
     break;
    }
   }

   while ( FALSE == IsStackEmpty( lpTempCarStack ) )
   {
    TCARINFORMATION tempcarinfo = { NULL };
    Pop( lpTempCarStack, tempcarinfo );
    Push( lpCarStack, tempcarinfo );
   }

   if ( FALSE == bIsCarFound )
   {
    printf( "���ƺ�Ϊ %s �ĳ�δ����ͣ����.\n", carinfo.szRegistrationMark );
    Pause( "--------------------\n�������������һ����Ϣ...\n" );
    continue;
   }

   strcpy( carinfoOut.szDepartureTime, carinfo.szDepartureTime );
   int nEntranceTime = ConvertTimeFormat( carinfoOut.szEntranceTime );
   int nDepartureTime = ConvertTimeFormat( carinfoOut.szDepartureTime );
   int nContinuanceMinutes = nDepartureTime - nEntranceTime;
   printf( "�Ʒ�ʱ��:\t%s - %s (�� %d ����)\n",
    carinfoOut.szEntranceTime,
    carinfoOut.szDepartureTime,
    nContinuanceMinutes
    );
   double rExpense = CalculateExpense( nContinuanceMinutes );
   printf( "Ӧ���ɵķ���:\t%.1lf Ԫ\n", rExpense );

   if ( FALSE == IsQueueEmpty( lpCarQueue ) )
   {
    TCARINFORMATION tempcarinfo = { NULL };
    DeQueue( lpCarQueue, tempcarinfo );
    strcpy( tempcarinfo.szEntranceTime, carinfoOut.szDepartureTime );
    Push( lpCarStack, tempcarinfo );
    puts( "--------------------" );
    printf( "ͣ���ڱ���ĵ� 1 ����λ,���ƺ�Ϊ %s �ĳ��ѽ���ͣ����\n",
     tempcarinfo.szRegistrationMark
    );
   }
  }
  else if ( cCommandType == '3' )
  {
   puts( "********************" );
   puts( "��лʹ�ô�ϵͳ" );
   puts( "********************" );
   break;
  }
  else if ( cCommandType == '4' )
  {
   putchar( '\n' );
   puts( "[ͣ����ʹ�����]\n" );
   puts( "[��λ]\t[���ƺ�]\t[����ʱ��]\t[����(��ʼ�Ʒ�)ʱ��]\n");
   for ( int i = 0; i <= lpCarStack->nTop; i++ )
   {
    printf( "%d\t%s\t\t%s\t\t%s\n",
     i + 1,
     lpCarStack->lpCarInformation[i].szRegistrationMark,
     lpCarStack->lpCarInformation[i].szArrivalTime,
     lpCarStack->lpCarInformation[i].szEntranceTime
     );
   }
   putchar( '\n' );
   putchar( '\n' );
   putchar( '\n' );
   puts( "[���ʹ�����]\n" );
   puts( "[��λ]\t[���ƺ�]\t[����ʱ��]\t[����(��ʼ�Ʒ�)ʱ��]\n");
   int nNum = 0;
   for ( LPTCARNODE lpCarNode = lpCarQueue->lpHead->lpNext;
    lpCarNode != NULL; lpCarNode = lpCarNode->lpNext )
   {
    nNum++;
    printf( "%d\t%s\t\t%s\t\t%s\n",
     nNum,
     lpCarNode->carinfo.szRegistrationMark,
     lpCarNode->carinfo.szArrivalTime,
     lpCarNode->carinfo.szEntranceTime
    );
   }
   putchar( '\n' );
  }
  else
  {
   puts( "������Ϣ����.��һ���ַ�ֻ��Ϊ '1' �� '2' �� '3' �� '4'" );
  }
  Pause( "--------------------\n�������������һ����Ϣ.\n" );
 } while ( TRUE );

 DestroyStack( lpCarStack );//����ջ 
 DestroyQueue( lpCarQueue );//���ٶ��� 

 Pause( "\n��������˳�����...\n" );

 return 0;
}
