#pragma once
#include <Windows.h>
#include "asynctmr.h"
#include <utility.h>
#include "toolbox.h"
#include <ansi_c.h>
#include <rs232.h>
#include <cvirte.h>
#include <userint.h>
#include "conveyor.h"

#define 	  EPACK_SIZE 		10								//数据包大小（字节）
#define		  NUM_APP_PACKS		1						 	 	//每次发送数据包的个数

static int	  panelHandle;

unsigned int  point_interval;									//画点间隔
unsigned int  icount=0;
int 	  	  com,bod;											//串口，波特率  
int 		  ringsv;  											//ring控件status value,表格控件中的y坐标
int 		  file_form; 										//文件输出方式 0：二进制  1：文本  
int 		  ID_datacept,Time_handle,DatApply_handle;			//ID及句柄
int 		  ssss;

char 		  project_route[2*MAX_PATHNAME_LEN]= {0};			//软件路径
char 	   	  abs_path_file_name[500]= {0};						//包含文件名的绝对路径 
char 		  send_dat[12];										//向ARM发送的数据组
double 		  systime;  										//系统时间   

FILE 		  *fp_rec;											//文件指针

int 	CVICALLBACK com_open_multhread (void *functionData) ;																	  //多线程
int		CVICALLBACK time_display (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);	  //时间
int		CVICALLBACK data_apply_asynt(int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);   //异步定时器

void 	CVICALLBACK com_callback (int portNumber, int eventMask, void *callbackData);											  //串口回调
void 	CVICALLBACK Param_Revise (int panelHandle, int controlID, int MenuItemID, void *callbackData); 							  //单参数修改

void  	Interface_Initial();    
void 	Folder_Create(void); 					//创建文件夹
void 	File_Create_Txt(void); 					//创建文本文件
void 	File_Create_Bin(void); 					//创建二进制文件 
