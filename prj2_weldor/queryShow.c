#include "hjglm.h"
#include "cvi_db.h"
#include <utility.h>
#include <ansi_c.h>
#include <formatio.h>
#include <cvirte.h>		
#include <userint.h>
#include "ui1.h"
#include "PANEL_query.h"

 int panelgl;
 int paneldvc;
int fileHandle1,fileHandle2;
int  dBHandle;//����Դ���
int  fileHandle;
int  dbstatus[14];  
int tabhh[20];  //��������ʱ�������ӵı���кţ�ÿ�����ֻ������20�У�����20��ʱ���ȱ���
int tabadd; //��¼�ܹ������˶���������
 int panelQuery;
 int panelHjgl; 
extern void dpdata(void);  //�ں��ӹ�������ʾ��ʼ��������� 
static int startflag;  


void Str2DatTim(char *Str,int *Year,int *Month,int *Day,int *Hour,int *Minute,double *Second);  //��ĳ��ĳ��ĳ��ĳʱĳ��ĳ���ַ���תΪ��1900��1��1������������    
double StrD2Sec(char* Str,int Hour); //��ĳ��ĳ��ĳ��(0����ʱ)�ַ���תΪ��1900��1��1������������ 
int QCIcheck(int I,int I_max,int I_min); //������ֵ������ֵ2Ϊ�ϸ�3Ϊ���ϸ�  

int main (int argc, char *argv[])
{
	char dirTemp[MAX_PATHNAME_LEN];
	char DBConStr[256];    
	
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelgl = LoadPanel (0, "ui1.uir", PANELGL)) < 0)
		return -1;
	
	GetProjectDir (dirTemp);//��ȡ����Ŀ¼·��
	sprintf(DBConStr,"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s\\%s;Persist Security Info=False",dirTemp,"hjdb.mdb");//��ȡ����Դ����·��
	dBHandle = DBConnect (DBConStr);//��������Դ����
	
	DisplayPanel (panelgl);
	RunUserInterface ();
	
	DBDisconnect (dBHandle); 
	DiscardPanel (panelgl);
	return 0;
}

int CVICALLBACK CPSave (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	char SQLCommand[256];
	char hjname[32],hjxhc[15],wdate[12],weiwu[100];
	int  hjwd;
	int  i;
	int  hjnumber;

	switch (event)
	{
		case EVENT_COMMIT:
			if(tabadd)
			{
				Fmt(SQLCommand, "%s","SELECT * FROM hjigl" ); //ʹ�õ���SQL����   
				fileHandle= DBActivateSQL(dBHandle,SQLCommand);//�����ݿ��еı�������
				DBBindColInt (fileHandle, 2, &hjnumber, &dbstatus[2]);   //���
				DBBindColChar (fileHandle, 3, 32 ,hjname, &dbstatus[3], "");   //����
				DBBindColChar (fileHandle, 4, 15 ,hjxhc, &dbstatus[4], "");	   //�ͺ�
				DBBindColInt (fileHandle, 5, &hjwd, &dbstatus[2]);   //��� 
				DBBindColChar (fileHandle,6, 12,  wdate, &dbstatus[5], "yyyy/mm/dd");    //ά������
				DBBindColChar (fileHandle,7, 100,  weiwu, &dbstatus[6], "");	  //ά������
				i = DBNumberOfRecords (fileHandle);//��ȡ��ǰ���ݿ��еļ�¼ 
				DBFetchRandom (fileHandle, i);  //����� 
	
				for(i=1;i<=tabadd;i++)
				{
					GetTableCellVal (panel, PANELDVC_TABLEDVC, MakePoint(1,tabhh[tabadd]), &hjnumber);
					GetTableCellVal (panel, PANELDVC_TABLEDVC, MakePoint(2,tabhh[tabadd]), hjname);
					GetTableCellVal (panel, PANELDVC_TABLEDVC, MakePoint(3,tabhh[tabadd]), hjxhc);
					GetTableCellVal (panel, PANELDVC_TABLEDVC, MakePoint(4,tabhh[tabadd]), &hjwd);
			
					DBCreateRecord (fileHandle);	//����һ���ռ�¼
				    DBPutRecord (fileHandle);		//���¼�¼����
				}
				tabadd = 0;
				DBDeactivateSQL (fileHandle); 
			}
		break;
	}
	return 0;
}
//�豸������
int CVICALLBACK CPDReturn (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DiscardPanel (paneldvc);
			
			break;
	}
	return 0;
}

int CVICALLBACK CPDvice (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	char SQLCommand[256];
	char hjname[32],hjxhc[15],wdate[12],weiwu[100];
	int  hjwd;
	int  i;
	int  num;
	int  hjnumber;

	switch (event)
	{
		case EVENT_COMMIT:
			if ((paneldvc = LoadPanel (panelgl, "ui1.uir", PANELDVC)) < 0)
		        return -1;
	        DisplayPanel (paneldvc);
		    
			//��ʾ�����豸��������
			Fmt(SQLCommand, "%s","SELECT * FROM hjigl ORDER BY hjbh ASC" ); //ʹ�õ���SQL����   
			fileHandle= DBActivateSQL(dBHandle,SQLCommand);//�����ݿ��еı�������
			DBBindColInt (fileHandle, 2, &hjnumber, &dbstatus[2]);   //���
			DBBindColChar (fileHandle, 3, 32 ,hjname, &dbstatus[3], "");   //����
			DBBindColChar (fileHandle, 4, 15 ,hjxhc, &dbstatus[4], "");	   //�ͺ�
			DBBindColInt (fileHandle, 5, &hjwd, &dbstatus[2]);   //���κ� 
			DBBindColChar (fileHandle,6, 12,  wdate, &dbstatus[5], "yyyy/mm/dd");    //ά������
			DBBindColChar (fileHandle,7, 100,  weiwu, &dbstatus[6], "");	  //ά������
			num = DBNumberOfRecords (fileHandle);//��ȡ��ǰ���ݿ��еļ�¼ 
	
			if(num)
			{
				InsertTableRows (paneldvc, PANELDVC_TABLEDVC, -1, num, VAL_USE_MASTER_CELL_TYPE);  
				for(i=1;i<=num;i++)
				{
					DBFetchRandom (fileHandle, i); //ָ���i����¼ 
					SetTableCellVal (paneldvc, PANELDVC_TABLEDVC, MakePoint(1,i), hjnumber);	//��ʾ���
					SetTableCellVal (paneldvc, PANELDVC_TABLEDVC, MakePoint(2,i), hjname);	//��ʾ����
					SetTableCellVal (paneldvc, PANELDVC_TABLEDVC, MakePoint(3,i), hjxhc);	//��ʾ�ͺ�
					SetTableCellVal (paneldvc, PANELDVC_TABLEDVC, MakePoint(4,i), hjnumber);	//��ʾ����
				}
			}
			DBDeactivateSQL (fileHandle); 

			break;
	}
	return 0;
}

int CVICALLBACK CPWeld (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				if ((panelHjgl = LoadPanel (0, "hjglm.uir", PANEL_hjgl)) < 0)
		        return -1;
			DisplayPanel (panelHjgl);
			SetCtrlAttribute (panelHjgl, PANEL_hjgl_STRIPCHART, ATTR_VISIBLE, 0);   
			dpdata();
			break;
	}
	return 0;
}

int CVICALLBACK CPQuit (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK CPDAdd (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			InsertTableRows (paneldvc, PANELDVC_TABLEDVC, -1, 1, VAL_USE_MASTER_CELL_TYPE); 
			if(++tabadd == 20)
			{
				tabadd--;
				MessagePopup("����","���������Ѿ�����20���ˣ����ȱ���"); 
			}
			else
			{
				GetNumTableRows (paneldvc, PANELDVC_TABLEDVC, &tabhh[tabadd]);
			}
			break;
	}
	return 0;
}

int CVICALLBACK CPDDlet (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	Point focus;
	char SQLCommand[256];
	char hjname[32],hjxhc[15],wdate[12],weiwu[100];
	int  hjwd;
	int  i;
	int  hjnumber;
	switch (event)
	{
		case EVENT_COMMIT:
			GetActiveTableCell(panel, PANELDVC_TABLEDVC, &focus);
			GetTableCellVal (panel, PANELDVC_TABLEDVC, MakePoint(1,focus.y), &hjnumber); 
			Fmt(SQLCommand, "%s%d","SELECT * FROM hjigl WHERE hjbh=",hjnumber); //ʹ�õ���SQL���� 
			fileHandle= DBActivateSQL(dBHandle,SQLCommand);//�����ݿ��еı�������
			DBBindColInt (fileHandle, 2, &hjnumber, &dbstatus[2]);   //���
			DBBindColChar (fileHandle, 3, 32 ,hjname, &dbstatus[3], "");   //����
			DBBindColChar (fileHandle, 4, 15 ,hjxhc, &dbstatus[4], "");	   //�ͺ�
			DBBindColInt (fileHandle, 5, &hjwd, &dbstatus[2]);   //��� 
			DBBindColChar (fileHandle,6, 12,  wdate, &dbstatus[5], "yyyy/mm/dd");    //ά������
			DBBindColChar (fileHandle,7, 100,  weiwu, &dbstatus[6], "");	  //ά������
			i = DBNumberOfRecords (fileHandle);//��ȡ��ǰ���ݿ��еļ�¼ 
			DBFetchRandom (fileHandle, i);  //����� 
			DBDeleteRecord (fileHandle);
			DBDeactivateSQL (fileHandle); 
			DeleteTableRows (panel, PANELDVC_TABLEDVC, focus.y, 1);
			break;
	}
	return 0;
}




//��������ѯ���ܻص�����
int CVICALLBACK FSelete (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if ((panelQuery = LoadPanel (panelHjgl, "PANEL_query.uir", PAN_query))<0)
				return -1;
			DisplayPanel (panelQuery);       
			break;
	}
	return 0;
}
  
//������ѯ����-���ػص�����
int CVICALLBACK querycb (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel(panelQuery);
			break;
	}
	return 0;
}
//������ѯ����-��ѯ���ܻص�����
int CVICALLBACK SearchDate (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			int FDatenum=0;
			int hjnumber=0;
			char hjnumbertitle[10]= {0};
			int num;
			char wdate[12];  //�������ڣ�5
			GetCtrlVal(panelQuery,PAN_query_Text2Find_int,&FDatenum);
			char SQLCommand[256];
			int i=1;
			int judge1=0;
			Fmt(SQLCommand, "%s%d","SELECT DISTINCT hjbh,workdate FROM hjdata WHERE hjbh=",FDatenum);
			fileHandle2= DBActivateSQL(dBHandle,SQLCommand);//�����ݿ��еı�������
			DBBindColInt (fileHandle2, 1, &hjnumber, &dbstatus[2]);
			DBBindColChar (fileHandle2,2, 12 ,wdate, &dbstatus[5], "yyyy/mm/dd");
			num = DBNumberOfRecords (fileHandle2);//��ȡ��ǰ���ݿ��еļ�¼
			//DeleteTableRows(panelQuery,PAN_query_TABLE1,1,-1);   //ɾ����������е�������
			//��tree�л�ȡ�����ֶ����У�������1�����tree���б������
			GetNumListItems (panelQuery, PAN_query_TREE, &judge1);
			if(judge1>1)
				DeleteListItem (panelQuery, PAN_query_TREE,1, -1);
			//����tree����ΪX�ź���   
			sprintf(hjnumbertitle,"%d�ź���",FDatenum);
			SetTreeItemAttribute (panelQuery, PAN_query_TREE, 0, ATTR_LABEL_TEXT, hjnumbertitle);
			if(num>0)
			{
				//InsertTableRows (panelQuery, PAN_query_TABLE1, -1,num , VAL_USE_MASTER_CELL_TYPE);
				//��������ָ�뽫��������д�������ؼ���    
				while(DBFetchNext(fileHandle2)!=DB_EOF)
				{
					InsertTreeItem (panelQuery, PAN_query_TREE, VAL_CHILD,0, VAL_LAST, wdate, NULL, NULL, -1);
					//SetTableCellVal( panelQuery,PAN_query_TABLE1,MakePoint(1,i),hjnumber);
					//SetTableCellVal( panelQuery,PAN_query_TABLE1,MakePoint(2,i),wdate);
					//i++;
				}
			}
			else
			{
				MessagePopup("��ѯ","����Ҫ��ѯ������û�鵽��");
			}
			DBDeactivateSQL (fileHandle2);
			break;
	}
	return 0;
}

////��ĳ��ĳ��ĳ��ĳʱĳ��ĳ���ַ���תΪ��1900��1��1������������ 
void Str2DatTim(char Str[20],int *Year,int *Month,int *Day,int *Hour,int *Minute,double *Second)

{
	char C1[5]= {0},C2[3]= {0},C3[3]= {0};
	char C4[3]= {0},C5[3]= {0},C6[3]= {0};
	for(int p=0; p<20; p++)
	{
		0<=p&&p<4?C1[p]=Str[p]:0;
		4<p&&p<7?C2[p-5]=Str[p]:0;
		7<p&&p<10?C3[p-8]=Str[p]:0;
		10<p&&p<13?C4[p-11]=Str[p]:0;
		13<p&&p<16?C5[p-14]=Str[p]:0;
		16<p&&p<=18?C6[p-17]=Str[p]:0;
	}
	*Year=atoi(C1);
	*Month=atoi(C2);
	*Day=atoi(C3);
	*Hour=atoi(C4);
	*Minute=atoi(C5);
	*Second=(double)(atoi(C6));
}
//��ĳ��ĳ��ĳ��(0����ʱ)�ַ���תΪ��1900��1��1������������  
double StrD2Sec(char* Str,int Hour)  
{   int Year,Month,Day;
	double SecondOut;
	char C1[5]= {0},C2[3]= {0},C3[3]= {0};
	for(int p=0; p<10; p++)
	{
		0<=p&&p<4?C1[p]=Str[p]:0;
		4<p&&p<7?C2[p-5]=Str[p]:0;
		7<p&&p<10?C3[p-8]=Str[p]:0;
	}
	Year=atoi(C1);
	Month=atoi(C2);
	Day=atoi(C3);
	MakeDateTime(Hour,0,0,Month,Day,Year,&SecondOut);//Hour�����Ĺ�������
	return SecondOut;
}
//�жϵ�����ѹ
int QCIcheck(int I,int I_max,int I_min) //������ֵ������ֵ2Ϊ�ϸ�3Ϊ���ϸ�     
{
   int val=1;   //1�����룬2�ϸ�3���ϸ��Ա����ϸ�ʱ��
   if(I>20)
   {
   		val=(I>I_max||I<I_min)?3:2;		
   }
   return val;
}
//����������ʾͼ������ؼ��ص�����
int CVICALLBACK TreeCallB (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{

	int FDatenum;
	int RecNum=0 , Index_ActiveTreeItem=0;
	char Dat[11]= {0};
	char SQLCommand[256];
	//char TempMesBox[80]= {0}; 
	char starttime[20],stoptime[20];
	char M3[32]={0},M4[32]={0};  
	int gcurrent=0,gvoltage=0,M1,conoff,M7,M8,M9,M10,M11,M12;   
	int Myear,Mmonth,Mday,Mhour,Mminute;
	double Msecond,MTimeOut1,MTimeOut2;
	double hjtimet,QC_passed,QC_failed; //ͳ�ƺ�������ʱ�䣬�ϸ�ʱ�䣬���ϸ�ʱ��
	double plot_dt_time[2];
	int plot_dt_current[2],plot_dt_voltage[2];
	int ColorP[7]={VAL_WHITE,VAL_GREEN,VAL_DK_YELLOW,0xb3FFFFL,0x00CCCCL,VAL_RED,VAL_DK_YELLOW};  
	int QC_val;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panelQuery,PAN_query_Text2Find_int,&FDatenum);
			GetActiveTreeItem (panelQuery, PAN_query_TREE, &Index_ActiveTreeItem);
			if(0==Index_ActiveTreeItem ) 
				return 0; 	
			GetTreeCellAttribute (panelQuery, PAN_query_TREE, Index_ActiveTreeItem, 0, ATTR_LABEL_TEXT, Dat);
		//	sprintf(TempMesBox,"������ʾ%d�ź���������%s�Ĺ�����¼" ,FDatenum,Dat);
		//	MessagePopup("��Ϣ��ʾ", TempMesBox);
			HidePanel(panelQuery);
			SetCtrlVal (panelHjgl, PANEL_hjgl_PBianhao, FDatenum); 
			SetCtrlVal (panelHjgl, PANEL_hjgl_PDate, Dat); 
			//���hjigl��hjset�Բ���
			sprintf(SQLCommand,"SELECT * FROM hjigl WHERE hjbh=%d",FDatenum);
			fileHandle1= DBActivateSQL(dBHandle,SQLCommand);//�����ݿ��еı�������
			DBBindColChar (fileHandle1, 3, 32 ,M3, &dbstatus[3], "");
			DBBindColChar (fileHandle1, 4, 32 ,M4, &dbstatus[4], "");
			RecNum=DBNumberOfRecords (fileHandle1); 
			if(0==RecNum)
			{
				MessagePopup("��ʾ��","û�з���Ҫ��ĺ��Ӽ�¼��");
				return 0;
			} 
			DBFetchRandom (fileHandle1, RecNum);
			SetCtrlVal (panelHjgl, PANEL_hjgl_PMingcheng, M3); 
			SetCtrlVal (panelHjgl, PANEL_hjgl_PXinghao, M4);
			SetCtrlVal (panelHjgl, PANEL_hjgl_PBianhao, FDatenum); 
			DBDeactivateSQL (fileHandle1); 
			
			sprintf(SQLCommand,"SELECT * FROM hjset WHERE hjbh=%d",FDatenum);
			fileHandle1= DBActivateSQL(dBHandle,SQLCommand);//�����ݿ��еı�������
			DBBindColInt (fileHandle1, 3, &M1, &dbstatus[3]); 
			DBBindColChar(fileHandle1, 4, 32 ,M4, &dbstatus[4], "");
		//	DBBindColInt (fileHandle1, 5, &conoff, &dbstatus[5]);  
			DBBindColInt (fileHandle1, 7, &M7, &dbstatus[ 6]);  
			DBBindColInt (fileHandle1, 8, &M8, &dbstatus[ 7]);  
			DBBindColInt (fileHandle1, 9, &M9, &dbstatus[ 8]);  
			DBBindColInt (fileHandle1,10,&M10, &dbstatus[ 9]);  
			DBBindColInt (fileHandle1,11,&M11, &dbstatus[10]);  
			DBBindColInt (fileHandle1,12,&M12, &dbstatus[11]);  
			RecNum=DBNumberOfRecords (fileHandle1); 

			if(RecNum)
			{
				DBFetchRandom (fileHandle1, RecNum); //ָ�����һ����¼
				SetCtrlVal (panelHjgl, PANEL_hjgl_PWorker, M1);
				SetCtrlVal (panelHjgl, PANEL_hjgl_PGongjian, M4);
				SetCtrlVal (panelHjgl, PANEL_hjgl_PDianliu, M7);
				SetCtrlVal (panelHjgl, PANEL_hjgl_PDianliuMax, M8);
				SetCtrlVal (panelHjgl, PANEL_hjgl_PDianliuMin, M9);
				SetCtrlVal (panelHjgl, PANEL_hjgl_PDianya, M10);
				SetCtrlVal (panelHjgl, PANEL_hjgl_PDianyauMax, M11);
				SetCtrlVal (panelHjgl, PANEL_hjgl_PDianyaMin, M12);
				/*
				if( conoff)
				{
					SetTreeCellAttribute (panelHjgl, PANEL_hjgl_TREE, hjtree[hjnumber].treehh, 1, ATTR_LABEL_TEXT, "��");		//��
					SetTreeCellAttribute (panelHjgl, PANEL_hjgl_TREE, hjtree[hjnumber].treehh, 1, ATTR_LABEL_COLOR, VAL_GREEN);

				}
				else
				{
					SetTreeCellAttribute (panelHjgl, PANEL_hjgl_TREE, hjtree[hjnumber].treehh, 1, ATTR_LABEL_TEXT, "��");   //��
					SetTreeCellAttribute (panelHjgl, PANEL_hjgl_TREE, hjtree[hjnumber].treehh, 1, ATTR_LABEL_COLOR, VAL_RED);
				}
				hjtree[hjnumber]. hjsjonoff  = conoff; //����״̬
				*/
			}
  		DBDeactivateSQL (fileHandle1); 
			
			//���hjdata������
			sprintf(SQLCommand,"SELECT * FROM sheetdat WHERE hjbh=%d AND workdate =#%s#",FDatenum,Dat);
			  //sprintf(SQLCommand,"SELECT * FROM hjdata WHERE hjbh=%d AND workdate =#%s#",FDatenum,Dat);   
			fileHandle= DBActivateSQL(dBHandle,SQLCommand);//�����ݿ��еı�������
			DBBindColChar(fileHandle,4, 20 ,starttime, &dbstatus[5], "yyyy/mm/dd hh:mm:ss");
			DBBindColInt (fileHandle, 5, &gcurrent, &dbstatus[5]);//����
			DBBindColInt (fileHandle, 6, &gvoltage, &dbstatus[6]);//��ѹ
			DBBindColChar(fileHandle,7, 20 ,stoptime, &dbstatus[6], "yyyy/mm/dd hh:mm:ss");
			RecNum = DBNumberOfRecords (fileHandle);
			if(0==RecNum)
			{
				MessagePopup("��ʾ��","û�з���Ҫ��ĺ��Ӽ�¼��");
				return 0;
			}
			hjtimet=0,QC_passed=0,QC_failed=0; 
			//��GRAPH�ؼ��ĺ���������Ϊʱ���ʽ��xxxx/xx/xx xx:xx:xx)
			SetCtrlAttribute (panelHjgl, PANEL_hjgl_GRAPH, ATTR_XFORMAT, VAL_ABSOLUTE_TIME_FORMAT);
			SetAxisTimeFormat (panelHjgl, PANEL_hjgl_GRAPH, VAL_BOTTOM_XAXIS, VAL_ABSOLUTE_TIME_FORMAT, "%X\n%x");
			MTimeOut1=StrD2Sec(Dat,8);  //���ش�1900��1��1�տ�ʼֱ���������� 8����������ֵ 
			MTimeOut2=StrD2Sec(Dat,18); //���ش�1900��1��1�տ�ʼֱ����������18����������ֵ 
			//��GRAPH�ؼ����ұ߽緶Χ����Ϊ���������ڵ�8��-18��
			SetAxisScalingMode (panelHjgl, PANEL_hjgl_GRAPH, VAL_BOTTOM_XAXIS, VAL_MANUAL, MTimeOut1, MTimeOut2);
			plot_dt_current[0]=0,plot_dt_voltage[0]=0;
			for(int pv=1; pv<=RecNum; pv++)
			{
				DBFetchRandom (fileHandle, pv);
				Str2DatTim(starttime,&Myear,&Mmonth,&Mday,&Mhour,&Mminute,&Msecond);
				MakeDateTime(Mhour,Mminute,Msecond,Mmonth,Mday,Myear,&MTimeOut1);
				Str2DatTim(stoptime,&Myear,&Mmonth,&Mday,&Mhour,&Mminute,&Msecond);
				MakeDateTime(Mhour,Mminute,Msecond,Mmonth,Mday,Myear,&MTimeOut2);
				Msecond=MTimeOut2-MTimeOut1;	  //�������ݵĳ���ʱ��
				hjtimet+=Msecond;
				plot_dt_time[0]=MTimeOut1,plot_dt_time[1]=MTimeOut2;  
				plot_dt_current[1]=gcurrent;
				plot_dt_voltage[1]=gvoltage;
				QC_val=QCIcheck(gcurrent,M8,M9);
				QC_passed=(2==QC_val)?(QC_passed+Msecond):QC_passed;
				QC_failed=(3==QC_val)?(QC_failed+Msecond):QC_failed; 
				PlotXY (panelHjgl, PANEL_hjgl_GRAPH, plot_dt_time, plot_dt_current, 2, VAL_DOUBLE, VAL_INTEGER, VAL_FAT_LINE, VAL_SOLID_SQUARE, VAL_SOLID, 1, ColorP[2*QC_val-1]);
				PlotXY (panelHjgl, PANEL_hjgl_GRAPH, plot_dt_time, plot_dt_voltage, 2, VAL_DOUBLE, VAL_INTEGER, VAL_FAT_LINE, VAL_SOLID_SQUARE, VAL_SOLID, 1, ColorP[2*QC_val]);
				plot_dt_current[0]=plot_dt_current[1];
				plot_dt_voltage[0]=plot_dt_voltage[1]; 

			}
			SetCtrlVal (panelHjgl, PANEL_hjgl_PHJWorkTime, hjtimet/3600);     
			SetCtrlVal (panelHjgl, PANEL_hjgl_PhjDianliu, QC_passed/3600);
			SetCtrlVal (panelHjgl, PANEL_hjgl_PNDianliu, QC_failed/3600); 
			DBDeactivateSQL (fileHandle);      
			break;

		   }
	return 0;
}
