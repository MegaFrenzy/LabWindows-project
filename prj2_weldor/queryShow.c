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
int  dBHandle;//数据源句柄
int  fileHandle;
int  dbstatus[14];  
int tabhh[20];  //增加数据时保存增加的表格行号，每次最多只能增加20行，大于20行时，先保存
int tabadd; //记录总共增加了多少行数据
 int panelQuery;
 int panelHjgl; 
extern void dpdata(void);  //在焊接管理中显示初始界面的数据 
static int startflag;  


void Str2DatTim(char *Str,int *Year,int *Month,int *Day,int *Hour,int *Minute,double *Second);  //将某年某月某日某时某分某秒字符串转为从1900年1月1日以来的秒数    
double StrD2Sec(char* Str,int Hour); //将某年某月某日(0点整时)字符串转为从1900年1月1日以来的秒数 
int QCIcheck(int I,int I_max,int I_min); //检查电流值，返回值2为合格，3为不合格  

int main (int argc, char *argv[])
{
	char dirTemp[MAX_PATHNAME_LEN];
	char DBConStr[256];    
	
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelgl = LoadPanel (0, "ui1.uir", PANELGL)) < 0)
		return -1;
	
	GetProjectDir (dirTemp);//获取工程目录路径
	sprintf(DBConStr,"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s\\%s;Persist Security Info=False",dirTemp,"hjdb.mdb");//获取数据源所在路径
	dBHandle = DBConnect (DBConStr);//建立数据源连接
	
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
				Fmt(SQLCommand, "%s","SELECT * FROM hjigl" ); //使用的是SQL语言   
				fileHandle= DBActivateSQL(dBHandle,SQLCommand);//与数据库中的表建立连接
				DBBindColInt (fileHandle, 2, &hjnumber, &dbstatus[2]);   //编号
				DBBindColChar (fileHandle, 3, 32 ,hjname, &dbstatus[3], "");   //名称
				DBBindColChar (fileHandle, 4, 15 ,hjxhc, &dbstatus[4], "");	   //型号
				DBBindColInt (fileHandle, 5, &hjwd, &dbstatus[2]);   //编号 
				DBBindColChar (fileHandle,6, 12,  wdate, &dbstatus[5], "yyyy/mm/dd");    //维修日期
				DBBindColChar (fileHandle,7, 100,  weiwu, &dbstatus[6], "");	  //维修内容
				i = DBNumberOfRecords (fileHandle);//获取当前数据库中的记录 
				DBFetchRandom (fileHandle, i);  //到最后 
	
				for(i=1;i<=tabadd;i++)
				{
					GetTableCellVal (panel, PANELDVC_TABLEDVC, MakePoint(1,tabhh[tabadd]), &hjnumber);
					GetTableCellVal (panel, PANELDVC_TABLEDVC, MakePoint(2,tabhh[tabadd]), hjname);
					GetTableCellVal (panel, PANELDVC_TABLEDVC, MakePoint(3,tabhh[tabadd]), hjxhc);
					GetTableCellVal (panel, PANELDVC_TABLEDVC, MakePoint(4,tabhh[tabadd]), &hjwd);
			
					DBCreateRecord (fileHandle);	//增加一条空记录
				    DBPutRecord (fileHandle);		//更新记录内容
				}
				tabadd = 0;
				DBDeactivateSQL (fileHandle); 
			}
		break;
	}
	return 0;
}
//设备管理返回
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
		    
			//显示所有设备档案数据
			Fmt(SQLCommand, "%s","SELECT * FROM hjigl ORDER BY hjbh ASC" ); //使用的是SQL语言   
			fileHandle= DBActivateSQL(dBHandle,SQLCommand);//与数据库中的表建立连接
			DBBindColInt (fileHandle, 2, &hjnumber, &dbstatus[2]);   //编号
			DBBindColChar (fileHandle, 3, 32 ,hjname, &dbstatus[3], "");   //名称
			DBBindColChar (fileHandle, 4, 15 ,hjxhc, &dbstatus[4], "");	   //型号
			DBBindColInt (fileHandle, 5, &hjwd, &dbstatus[2]);   //网段号 
			DBBindColChar (fileHandle,6, 12,  wdate, &dbstatus[5], "yyyy/mm/dd");    //维修日期
			DBBindColChar (fileHandle,7, 100,  weiwu, &dbstatus[6], "");	  //维修内容
			num = DBNumberOfRecords (fileHandle);//获取当前数据库中的记录 
	
			if(num)
			{
				InsertTableRows (paneldvc, PANELDVC_TABLEDVC, -1, num, VAL_USE_MASTER_CELL_TYPE);  
				for(i=1;i<=num;i++)
				{
					DBFetchRandom (fileHandle, i); //指向第i条记录 
					SetTableCellVal (paneldvc, PANELDVC_TABLEDVC, MakePoint(1,i), hjnumber);	//显示编号
					SetTableCellVal (paneldvc, PANELDVC_TABLEDVC, MakePoint(2,i), hjname);	//显示名称
					SetTableCellVal (paneldvc, PANELDVC_TABLEDVC, MakePoint(3,i), hjxhc);	//显示型号
					SetTableCellVal (paneldvc, PANELDVC_TABLEDVC, MakePoint(4,i), hjnumber);	//显示网段
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
				MessagePopup("提醒","增加数据已经超过20行了，请先保存"); 
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
			Fmt(SQLCommand, "%s%d","SELECT * FROM hjigl WHERE hjbh=",hjnumber); //使用的是SQL语言 
			fileHandle= DBActivateSQL(dBHandle,SQLCommand);//与数据库中的表建立连接
			DBBindColInt (fileHandle, 2, &hjnumber, &dbstatus[2]);   //编号
			DBBindColChar (fileHandle, 3, 32 ,hjname, &dbstatus[3], "");   //名称
			DBBindColChar (fileHandle, 4, 15 ,hjxhc, &dbstatus[4], "");	   //型号
			DBBindColInt (fileHandle, 5, &hjwd, &dbstatus[2]);   //编号 
			DBBindColChar (fileHandle,6, 12,  wdate, &dbstatus[5], "yyyy/mm/dd");    //维修日期
			DBBindColChar (fileHandle,7, 100,  weiwu, &dbstatus[6], "");	  //维修内容
			i = DBNumberOfRecords (fileHandle);//获取当前数据库中的记录 
			DBFetchRandom (fileHandle, i);  //到最后 
			DBDeleteRecord (fileHandle);
			DBDeactivateSQL (fileHandle); 
			DeleteTableRows (panel, PANELDVC_TABLEDVC, focus.y, 1);
			break;
	}
	return 0;
}




//管理界面查询功能回调函数
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
  
//焊机查询界面-返回回调函数
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
//焊机查询界面-查询功能回调函数
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
			char wdate[12];  //工作日期，5
			GetCtrlVal(panelQuery,PAN_query_Text2Find_int,&FDatenum);
			char SQLCommand[256];
			int i=1;
			int judge1=0;
			Fmt(SQLCommand, "%s%d","SELECT DISTINCT hjbh,workdate FROM hjdata WHERE hjbh=",FDatenum);
			fileHandle2= DBActivateSQL(dBHandle,SQLCommand);//与数据库中的表建立连接
			DBBindColInt (fileHandle2, 1, &hjnumber, &dbstatus[2]);
			DBBindColChar (fileHandle2,2, 12 ,wdate, &dbstatus[5], "yyyy/mm/dd");
			num = DBNumberOfRecords (fileHandle2);//获取当前数据库中的记录
			//DeleteTableRows(panelQuery,PAN_query_TABLE1,1,-1);   //删除控制面板中的所有行
			//从tree中获取数据又多少列，若大于1则清空tree中列表的内容
			GetNumListItems (panelQuery, PAN_query_TREE, &judge1);
			if(judge1>1)
				DeleteListItem (panelQuery, PAN_query_TREE,1, -1);
			//设置tree标题为X号焊机   
			sprintf(hjnumbertitle,"%d号焊机",FDatenum);
			SetTreeItemAttribute (panelQuery, PAN_query_TREE, 0, ATTR_LABEL_TEXT, hjnumbertitle);
			if(num>0)
			{
				//InsertTableRows (panelQuery, PAN_query_TABLE1, -1,num , VAL_USE_MASTER_CELL_TYPE);
				//利用数据指针将数据逐行写入面板表格控件中    
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
				MessagePopup("查询","您所要查询的数据没查到！");
			}
			DBDeactivateSQL (fileHandle2);
			break;
	}
	return 0;
}

////将某年某月某日某时某分某秒字符串转为从1900年1月1日以来的秒数 
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
//将某年某月某日(0点整时)字符串转为从1900年1月1日以来的秒数  
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
	MakeDateTime(Hour,0,0,Month,Day,Year,&SecondOut);//Hour点整的规则秒数
	return SecondOut;
}
//判断电流电压
int QCIcheck(int I,int I_max,int I_min) //检查电流值，返回值2为合格，3为不合格     
{
   int val=1;   //1不计入，2合格，3不合格，以便计算合格时间
   if(I>20)
   {
   		val=(I>I_max||I<I_min)?3:2;		
   }
   return val;
}
//根据日期显示图像的树控件回调函数
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
	double hjtimet,QC_passed,QC_failed; //统计焊机工作时间，合格时间，不合格时间
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
		//	sprintf(TempMesBox,"即将显示%d号焊机在日期%s的工作记录" ,FDatenum,Dat);
		//	MessagePopup("消息提示", TempMesBox);
			HidePanel(panelQuery);
			SetCtrlVal (panelHjgl, PANEL_hjgl_PBianhao, FDatenum); 
			SetCtrlVal (panelHjgl, PANEL_hjgl_PDate, Dat); 
			//查表hjigl和hjset显参数
			sprintf(SQLCommand,"SELECT * FROM hjigl WHERE hjbh=%d",FDatenum);
			fileHandle1= DBActivateSQL(dBHandle,SQLCommand);//与数据库中的表建立连接
			DBBindColChar (fileHandle1, 3, 32 ,M3, &dbstatus[3], "");
			DBBindColChar (fileHandle1, 4, 32 ,M4, &dbstatus[4], "");
			RecNum=DBNumberOfRecords (fileHandle1); 
			if(0==RecNum)
			{
				MessagePopup("提示！","没有符合要求的焊接记录！");
				return 0;
			} 
			DBFetchRandom (fileHandle1, RecNum);
			SetCtrlVal (panelHjgl, PANEL_hjgl_PMingcheng, M3); 
			SetCtrlVal (panelHjgl, PANEL_hjgl_PXinghao, M4);
			SetCtrlVal (panelHjgl, PANEL_hjgl_PBianhao, FDatenum); 
			DBDeactivateSQL (fileHandle1); 
			
			sprintf(SQLCommand,"SELECT * FROM hjset WHERE hjbh=%d",FDatenum);
			fileHandle1= DBActivateSQL(dBHandle,SQLCommand);//与数据库中的表建立连接
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
				DBFetchRandom (fileHandle1, RecNum); //指向最后一条记录
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
					SetTreeCellAttribute (panelHjgl, PANEL_hjgl_TREE, hjtree[hjnumber].treehh, 1, ATTR_LABEL_TEXT, "开");		//开
					SetTreeCellAttribute (panelHjgl, PANEL_hjgl_TREE, hjtree[hjnumber].treehh, 1, ATTR_LABEL_COLOR, VAL_GREEN);

				}
				else
				{
					SetTreeCellAttribute (panelHjgl, PANEL_hjgl_TREE, hjtree[hjnumber].treehh, 1, ATTR_LABEL_TEXT, "关");   //关
					SetTreeCellAttribute (panelHjgl, PANEL_hjgl_TREE, hjtree[hjnumber].treehh, 1, ATTR_LABEL_COLOR, VAL_RED);
				}
				hjtree[hjnumber]. hjsjonoff  = conoff; //开关状态
				*/
			}
  		DBDeactivateSQL (fileHandle1); 
			
			//查表hjdata画曲线
			sprintf(SQLCommand,"SELECT * FROM sheetdat WHERE hjbh=%d AND workdate =#%s#",FDatenum,Dat);
			  //sprintf(SQLCommand,"SELECT * FROM hjdata WHERE hjbh=%d AND workdate =#%s#",FDatenum,Dat);   
			fileHandle= DBActivateSQL(dBHandle,SQLCommand);//与数据库中的表建立连接
			DBBindColChar(fileHandle,4, 20 ,starttime, &dbstatus[5], "yyyy/mm/dd hh:mm:ss");
			DBBindColInt (fileHandle, 5, &gcurrent, &dbstatus[5]);//电流
			DBBindColInt (fileHandle, 6, &gvoltage, &dbstatus[6]);//电压
			DBBindColChar(fileHandle,7, 20 ,stoptime, &dbstatus[6], "yyyy/mm/dd hh:mm:ss");
			RecNum = DBNumberOfRecords (fileHandle);
			if(0==RecNum)
			{
				MessagePopup("提示！","没有符合要求的焊接记录！");
				return 0;
			}
			hjtimet=0,QC_passed=0,QC_failed=0; 
			//将GRAPH控件的横坐标设置为时间格式（xxxx/xx/xx xx:xx:xx)
			SetCtrlAttribute (panelHjgl, PANEL_hjgl_GRAPH, ATTR_XFORMAT, VAL_ABSOLUTE_TIME_FORMAT);
			SetAxisTimeFormat (panelHjgl, PANEL_hjgl_GRAPH, VAL_BOTTOM_XAXIS, VAL_ABSOLUTE_TIME_FORMAT, "%X\n%x");
			MTimeOut1=StrD2Sec(Dat,8);  //返回从1900年1月1日开始直到查找日期 8点整的秒数值 
			MTimeOut2=StrD2Sec(Dat,18); //返回从1900年1月1日开始直到查找日期18点整的秒数值 
			//将GRAPH控件左右边界范围调整为所查找日期的8点-18点
			SetAxisScalingMode (panelHjgl, PANEL_hjgl_GRAPH, VAL_BOTTOM_XAXIS, VAL_MANUAL, MTimeOut1, MTimeOut2);
			plot_dt_current[0]=0,plot_dt_voltage[0]=0;
			for(int pv=1; pv<=RecNum; pv++)
			{
				DBFetchRandom (fileHandle, pv);
				Str2DatTim(starttime,&Myear,&Mmonth,&Mday,&Mhour,&Mminute,&Msecond);
				MakeDateTime(Mhour,Mminute,Msecond,Mmonth,Mday,Myear,&MTimeOut1);
				Str2DatTim(stoptime,&Myear,&Mmonth,&Mday,&Mhour,&Mminute,&Msecond);
				MakeDateTime(Mhour,Mminute,Msecond,Mmonth,Mday,Myear,&MTimeOut2);
				Msecond=MTimeOut2-MTimeOut1;	  //该条数据的持续时间
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
