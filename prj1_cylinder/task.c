#include "task.h"


int Task_Initialize(void)
{
	hDevice=USB3202_DEV_Create(0,0);
	if(INVALID_HANDLE_VALUE==hDevice||-1==hDevice)
	{
		MessagePopup("Error","初始化任务句柄失败，请检查设备是否连接");
		return -1;
	}
	//DevCount=USB3202_DEV_GetCount(); 					//设备数量
	//USB3202_DEV_GetSpeed(hDevice,&UsbSpeed); 			//USB速度
	
	AIParam_Initialize(); 								//初始化模拟输入参数  
	
	if(!USB3202_AI_VerifyParam(hDevice, &AIParam))  	//合法性检查
	{
		MessagePopup("Error","模拟输入参数不合法\n注意查看日志文件USB3202.log");
		return -1;
	}

	if(!USB3202_AI_InitTask(hDevice, &AIParam, NULL))   //AI采样初始化
	{
		MessagePopup("Error","AI采样初始化任务失败\n");
		return -1; 
	}
	
	if(!USB3202_AI_StartTask(hDevice))	   				//启动AI采样任务
	{
		MessagePopup("Error","模拟采样任务启动失败");
		return -1;
	}

	return 0;
}

void AIParam_Initialize(void)
{
	memset(&AIParam, 0, sizeof(USB3202_AI_PARAM));
	// 通道参数
	AIParam.nSampChanCount	= SAMPLE_CH_COUNT;
	for(auto int nChannel=0; nChannel<USB3202_AI_MAX_CHANNELS; nChannel++)
	{
		AIParam.CHParam[nChannel].nChannel		= nChannel;
		AIParam.CHParam[nChannel].nSampleGain	= USB3202_AI_SAMPGAIN_1MULT;
		AIParam.CHParam[nChannel].nRefGround	= USB3202_AI_REFGND_RSE;
		AIParam.CHParam[nChannel].nReserved0	= 0;
		AIParam.CHParam[nChannel].nReserved1	= 0;
		AIParam.CHParam[nChannel].nReserved2	= 0;
	}
	AIParam.nSampleSignal			= USB3202_AI_SAMPSIGNAL_AI;
	AIParam.nSampleRange			= USB3202_AI_SAMPRANGE_0_P5V;
	AIParam.nReserved0				= 0;

	// 时钟参数
	AIParam.nSampleMode				= USB3202_AI_SAMPMODE_CONTINUOUS;
	AIParam.nSampsPerChan			= (int)(rate_per_ch / 20); 		//由采样速率计算而来,相当于50ms触发一次采样事件 //原始值1000/10=100，即100ms一次
	AIParam.fSampleRate				= (double)rate_per_ch; 		//每通道每秒样点sps由控件获得					//原始值为1000
	AIParam.nClockSource			= USB3202_AI_CLKSRC_LOCAL;
	AIParam.bClockOutput			= FALSE;
	AIParam.nReserved1				= 0;
	AIParam.nReserved2				= 0;

	// 触发参数
	AIParam.bDTriggerEn				= TRUE;
	AIParam.nDTriggerDir			= USB3202_AI_TRIGDIR_FALLING;
	AIParam.bATriggerEn				= TRUE;
	AIParam.nATriggerDir			= USB3202_AI_TRIGDIR_FALLING;
	////////////////////////
	AIParam.nATrigChannel           = 0;		//0通道触发模拟采集任务的开始
	AIParam.fTriggerLevel			= 0.0;
	AIParam.nTriggerSens			= 10;
	AIParam.nDelaySamps				= 0;

	// 其他参数
	AIParam.nReserved3				= 0;
	AIParam.nReserved4				= 0;
	AIParam.nReserved5				= 0;
	AIParam.nReserved6				= 0;
	
	//设定画图间隙 
	delta_interval 					= (rate_per_ch<=1000) ? (rate_per_ch/100) : (rate_per_ch/10) ;		
	//设定超时时间3.0秒
	Timeout							= 3.0;
}

int Task_Stop(void)
{

	if(!USB3202_AI_StopTask(hDevice))					//停止AI采样       
	{
		//MessagePopup("Error","AI_StopTask Error");
		return -1;
	}

	if(!USB3202_AI_ReleaseTask(hDevice))			   	//释放AI采集任务      
	{
		//MessagePopup("Error","AI_ReleaseTask Error");
		return -1;
	}

	if(USB3202_DEV_Release(hDevice)<0)				   	//释放设备对象    
	{
		//MessagePopup("Error","DEV_Release Error");
		return -1;
	}
	return 0;
}

double Data_Convert(double volt,int flg)
{
	//将0-5V转换为对应单位的测量值
	double ret=0.0;
	switch(flg)
	{	 
		case 0:						//转为0-300℃
			ret = (volt-1.0)*75;
			break;
		case 1:						//转为0-10MPa
			ret = (volt-1.0)*2;
			break;
		case 2:						//转为0-10MPa
			ret = (volt-1.0)*2;
			break;
		case 3:						//转为0-100Nm
			ret = (volt-1.0)*20;
			break;
		case 4:						//转为0-100Nm
			ret = (volt-1.0)*20;
			break;
		case 5:						//转为 负50g-50g
			ret = volt*10;
			return ret; 
			
		 
		/*	
		case 0:						//转为--
			return 163+Random(0.0,4.0); break;
		case 1:						//转为--
			return 1.5+Random(0.0,0.5);  break;
		case 2:						//转为--
			return 6.5+Random(0.0,0.3);  break;
		case 3:						//转为--
			return 13+Random(0.0,1.6);   break;
		case 4:						//转为--
			return 76+Random(0.0,3.2);   break;
		case 5:						//转为--
			return 22.5+Random(0.0,3.0); break;
		*/
	}
	ret=(ret<0.0)?0.0:ret;    
	return ret;
}
