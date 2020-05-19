#include "task.h"


int Task_Initialize(void)
{
	hDevice=USB3202_DEV_Create(0,0);
	if(INVALID_HANDLE_VALUE==hDevice||-1==hDevice)
	{
		MessagePopup("Error","��ʼ��������ʧ�ܣ������豸�Ƿ�����");
		return -1;
	}
	//DevCount=USB3202_DEV_GetCount(); 					//�豸����
	//USB3202_DEV_GetSpeed(hDevice,&UsbSpeed); 			//USB�ٶ�
	
	AIParam_Initialize(); 								//��ʼ��ģ���������  
	
	if(!USB3202_AI_VerifyParam(hDevice, &AIParam))  	//�Ϸ��Լ��
	{
		MessagePopup("Error","ģ������������Ϸ�\nע��鿴��־�ļ�USB3202.log");
		return -1;
	}

	if(!USB3202_AI_InitTask(hDevice, &AIParam, NULL))   //AI������ʼ��
	{
		MessagePopup("Error","AI������ʼ������ʧ��\n");
		return -1; 
	}
	
	if(!USB3202_AI_StartTask(hDevice))	   				//����AI��������
	{
		MessagePopup("Error","ģ�������������ʧ��");
		return -1;
	}

	return 0;
}

void AIParam_Initialize(void)
{
	memset(&AIParam, 0, sizeof(USB3202_AI_PARAM));
	// ͨ������
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

	// ʱ�Ӳ���
	AIParam.nSampleMode				= USB3202_AI_SAMPMODE_CONTINUOUS;
	AIParam.nSampsPerChan			= (int)(rate_per_ch / 20); 		//�ɲ������ʼ������,�൱��50ms����һ�β����¼� //ԭʼֵ1000/10=100����100msһ��
	AIParam.fSampleRate				= (double)rate_per_ch; 		//ÿͨ��ÿ������sps�ɿؼ����					//ԭʼֵΪ1000
	AIParam.nClockSource			= USB3202_AI_CLKSRC_LOCAL;
	AIParam.bClockOutput			= FALSE;
	AIParam.nReserved1				= 0;
	AIParam.nReserved2				= 0;

	// ��������
	AIParam.bDTriggerEn				= TRUE;
	AIParam.nDTriggerDir			= USB3202_AI_TRIGDIR_FALLING;
	AIParam.bATriggerEn				= TRUE;
	AIParam.nATriggerDir			= USB3202_AI_TRIGDIR_FALLING;
	////////////////////////
	AIParam.nATrigChannel           = 0;		//0ͨ������ģ��ɼ�����Ŀ�ʼ
	AIParam.fTriggerLevel			= 0.0;
	AIParam.nTriggerSens			= 10;
	AIParam.nDelaySamps				= 0;

	// ��������
	AIParam.nReserved3				= 0;
	AIParam.nReserved4				= 0;
	AIParam.nReserved5				= 0;
	AIParam.nReserved6				= 0;
	
	//�趨��ͼ��϶ 
	delta_interval 					= (rate_per_ch<=1000) ? (rate_per_ch/100) : (rate_per_ch/10) ;		
	//�趨��ʱʱ��3.0��
	Timeout							= 3.0;
}

int Task_Stop(void)
{

	if(!USB3202_AI_StopTask(hDevice))					//ֹͣAI����       
	{
		//MessagePopup("Error","AI_StopTask Error");
		return -1;
	}

	if(!USB3202_AI_ReleaseTask(hDevice))			   	//�ͷ�AI�ɼ�����      
	{
		//MessagePopup("Error","AI_ReleaseTask Error");
		return -1;
	}

	if(USB3202_DEV_Release(hDevice)<0)				   	//�ͷ��豸����    
	{
		//MessagePopup("Error","DEV_Release Error");
		return -1;
	}
	return 0;
}

double Data_Convert(double volt,int flg)
{
	//��0-5Vת��Ϊ��Ӧ��λ�Ĳ���ֵ
	double ret=0.0;
	switch(flg)
	{	 
		case 0:						//תΪ0-300��
			ret = (volt-1.0)*75;
			break;
		case 1:						//תΪ0-10MPa
			ret = (volt-1.0)*2;
			break;
		case 2:						//תΪ0-10MPa
			ret = (volt-1.0)*2;
			break;
		case 3:						//תΪ0-100Nm
			ret = (volt-1.0)*20;
			break;
		case 4:						//תΪ0-100Nm
			ret = (volt-1.0)*20;
			break;
		case 5:						//תΪ ��50g-50g
			ret = volt*10;
			return ret; 
			
		 
		/*	
		case 0:						//תΪ--
			return 163+Random(0.0,4.0); break;
		case 1:						//תΪ--
			return 1.5+Random(0.0,0.5);  break;
		case 2:						//תΪ--
			return 6.5+Random(0.0,0.3);  break;
		case 3:						//תΪ--
			return 13+Random(0.0,1.6);   break;
		case 4:						//תΪ--
			return 76+Random(0.0,3.2);   break;
		case 5:						//תΪ--
			return 22.5+Random(0.0,3.0); break;
		*/
	}
	ret=(ret<0.0)?0.0:ret;    
	return ret;
}
