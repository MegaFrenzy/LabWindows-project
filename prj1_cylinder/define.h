#pragma once
#include "USB3202.h" 
#include "cvidef.h"
#include "toolbox.h"
#include "asynctmr.h"
#include <cvirte.h>
#include <userint.h>
#include "qigang.h"
		

#define SAMPLE_CH_COUNT 6 								//采样通道共6个
#define MAX_NUMS_TO_READ_PER_CH 1000					//每通道每次最大取值数
		
		

extern HANDLE hDevice;  								//采集卡句柄
extern int Async_handle;								//异步定时器句柄
extern int panelHandle;									//面板句柄
extern USB3202_AI_PARAM AIParam;						//模拟输入结构体参数

extern int token;										//采集开关状态
extern int file_form; 									//文件输出方式 0：二进制  1：文本
extern int rate_per_ch;									//从面板接受的每通道采样速率
extern int delta_interval;								//画图间隙

//U32 ReadSampsPerChan = NUMS_TO_READ_PER_CH;			//每通道请求读入点数
extern U32 SampsPerChanRead , AvailSampPerCH ;

extern double Collect_Buff[18000];  					//采样电压值缓冲区
extern double Timeout;									//超时时间    

