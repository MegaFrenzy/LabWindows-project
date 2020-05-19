#pragma once
#include "USB3202.h" 
#include "cvidef.h"
#include "toolbox.h"
#include "asynctmr.h"
#include <cvirte.h>
#include <userint.h>
#include "qigang.h"
		

#define SAMPLE_CH_COUNT 6 								//����ͨ����6��
#define MAX_NUMS_TO_READ_PER_CH 1000					//ÿͨ��ÿ�����ȡֵ��
		
		

extern HANDLE hDevice;  								//�ɼ������
extern int Async_handle;								//�첽��ʱ�����
extern int panelHandle;									//�����
extern USB3202_AI_PARAM AIParam;						//ģ������ṹ�����

extern int token;										//�ɼ�����״̬
extern int file_form; 									//�ļ������ʽ 0��������  1���ı�
extern int rate_per_ch;									//�������ܵ�ÿͨ����������
extern int delta_interval;								//��ͼ��϶

//U32 ReadSampsPerChan = NUMS_TO_READ_PER_CH;			//ÿͨ������������
extern U32 SampsPerChanRead , AvailSampPerCH ;

extern double Collect_Buff[18000];  					//������ѹֵ������
extern double Timeout;									//��ʱʱ��    

