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

#define 	  EPACK_SIZE 		10								//���ݰ���С���ֽڣ�
#define		  NUM_APP_PACKS		1						 	 	//ÿ�η������ݰ��ĸ���

static int	  panelHandle;

unsigned int  point_interval;									//������
unsigned int  icount=0;
int 	  	  com,bod;											//���ڣ�������  
int 		  ringsv;  											//ring�ؼ�status value,���ؼ��е�y����
int 		  file_form; 										//�ļ������ʽ 0��������  1���ı�  
int 		  ID_datacept,Time_handle,DatApply_handle;			//ID�����
int 		  ssss;

char 		  project_route[2*MAX_PATHNAME_LEN]= {0};			//���·��
char 	   	  abs_path_file_name[500]= {0};						//�����ļ����ľ���·�� 
char 		  send_dat[12];										//��ARM���͵�������
double 		  systime;  										//ϵͳʱ��   

FILE 		  *fp_rec;											//�ļ�ָ��

int 	CVICALLBACK com_open_multhread (void *functionData) ;																	  //���߳�
int		CVICALLBACK time_display (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);	  //ʱ��
int		CVICALLBACK data_apply_asynt(int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);   //�첽��ʱ��

void 	CVICALLBACK com_callback (int portNumber, int eventMask, void *callbackData);											  //���ڻص�
void 	CVICALLBACK Param_Revise (int panelHandle, int controlID, int MenuItemID, void *callbackData); 							  //�������޸�

void  	Interface_Initial();    
void 	Folder_Create(void); 					//�����ļ���
void 	File_Create_Txt(void); 					//�����ı��ļ�
void 	File_Create_Bin(void); 					//�����������ļ� 
