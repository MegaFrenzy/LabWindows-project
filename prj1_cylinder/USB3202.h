#ifndef _USB3202_DEVICE_
#define _USB3202_DEVICE_

#include "windows.h"

// #################### ���Ի����������Ͷ��� #####################
// Humanized data types definition
typedef char				I8;		// 8λ�з�����������
typedef unsigned char		U8;		// 8λ�޷�����������
typedef short				I16;	// 16λ�з�����������
typedef unsigned short		U16;	// 16λ�޷�����������
typedef long				I32;	// 32λ�з�����������
typedef unsigned long		U32;	// 32λ�޷�����������
typedef __int64				I64;	// 64λ�з�����������
typedef unsigned __int64	U64;	// 64λ�޷�����������
typedef float				F32;	// 32λ��������(�����ȣ�ͬΪlabVIEW�е�SGL)
typedef double				F64;	// 64λ��������(˫���ȣ�ͬΪlabVIEW�е�DBL)

// ########################## �豸����ָ�� ########################
#define USB3202_AI_MAX_CHANNELS	8 // �������֧��ģ������������ͨ��
#define USB3202_DI_MAX_CHANNELS	4 // �������֧����������������ͨ��
#define USB3202_DO_MAX_CHANNELS	4 // �������֧���������������ͨ��

// ############# AI���������ṹ��USB3202_AI_PARAM���� #############
typedef struct _USB3202_AI_CH_PARAM // AIͨ�������ṹ��
{
	U32 nChannel;			// ͨ����[0, 7]���ֱ��ʾ����ͨ����AI0��AI7
	U32 nSampleGain;		// �������棬����Ŵ�����ο����泣������
	U32 nRefGround;			// �زο���ʽ

	U32 nReserved0;			// ����(δ��)
	U32 nReserved1;			// ����(δ��)
	U32 nReserved2;			// ����(δ��)
} USB3202_AI_CH_PARAM, *PUSB3202_AI_CH_PARAM;

// AIӲ��ͨ������USB3202_AI_CH_PARAM�е�nSampleGain��������Ŵ�����ʹ�õ�ѡ��
#define USB3202_AI_SAMPGAIN_1MULT		0 // 1������
#define USB3202_AI_SAMPGAIN_2MULT		1 // 2������
#define USB3202_AI_SAMPGAIN_4MULT		2 // 4������
#define USB3202_AI_SAMPGAIN_8MULT		3 // 8������

// AIӲ��ͨ�������ṹ��USB3202_AI_CH_PARAM�е�nRefGround������ʹ�õĵزο�ѡ��
#define USB3202_AI_REFGND_RSE			0 // �ӵزο�����(Referenced Single Endpoint)
#define USB3202_AI_REFGND_NRSE			1 // �ǲο�����(Non Referenced Single Endpoint)
#define USB3202_AI_REFGND_DIFF			2 // ���(Differential)

typedef struct _USB3202_AI_PARAM // ������AI�йص�Ӳ����������(���AI��������)
{
	// ͨ������
	U32 nSampChanCount;     // ����ͨ������[1, 8](�˲����ڵ��������Ч��δ��ע���Ĳ������ڵ������ģʽ����Ч)
	USB3202_AI_CH_PARAM CHParam[8]; // ͨ����������(�˲����ڵ��������Ч��δ��ע���Ĳ������ڵ������ģʽ����Ч)
	U32 nSampleSignal;		// �����ź�(Sample Signal), ������泣������
	U32 nSampleRange;		// ������Χ(Sample Range)��λѡ��, ��������泣��������(�˲����ڵ��������Ч��δ��ע���Ĳ������ڵ������ģʽ����Ч)
	U32 nReserved0;

	// ʱ�Ӳ���
	U32 nSampleMode;		// ����ģʽ, 0=�����ʱ�������(����)�� 1��Ӳ����ʱ�������(�ݲ�֧��)��2=���޵������ 3=��������
	U32 nSampsPerChan;		// ÿ��ͨ����������(Ҳ��ÿͨ������ȡ����),ȡֵ��ΧΪ�������ģʽʱӦ����1�����޵����������ʱΪ[2, 1024*1024]
	F64 fSampleRate;		// ��������(Sample Rate), ��λΪsps��ȡֵ��ΧΪ[1sps, 250000sps],����ÿ������ͨ���Ĳ�������, ����nChannelCount�ĳ˻����ܴ���250000sps
	U32 nClockSource;		// ʱ��Դѡ��, =0:��ʱ��OSCCLK; =1:��ʱ��CLKIN,��������CN2�ϵ�DIO2/CLKIN�������룬��˳�ʼ��ʱ�ὫDIO2�ķ���ǿ����Ϊ����
	U32 bClockOutput;		// ����ʱ���������, =0:��ʾ��ֹ; =1:��ʾ����,��������CN2��DIO3/CLKOUT�����������˳�ʼ��ʱ�ὫDIO3�ķ���ǿ����Ϊ���
	U32 nReserved1;
	U32 nReserved2;

	// ��ʼ��������
	U32 bDTriggerEn;		// ���ִ���DTR����(Digital Trigger Enable), =FALSE:��ʾ��ֹ; =TRUE:��ʾ����,�����ź���������CN2�ϵ�DIO1�������룬��˳�ʼ��ʱ�ὫDIO1�ķ���ǿ����Ϊ����
	U32 nDTriggerDir;	    // ���ִ�������(Digital Trigger Direction)
	U32 bATriggerEn;		// ģ�����ִ���ATR����(Analog Trigger Enable), =TRUE:��ʾ����, =FALSE:��ʾ��ֹ
	U32 nATriggerDir;		// ģ�ⴥ������(Analog Trigger Direction)
	U32 nATrigChannel;		// ����ͨ��(Analog Trigger Channel)
	F32 fTriggerLevel;		// ������ƽ(Trigger Level)
	U32 nTriggerSens;		// ����������(Trigger Sensitive for Digital and Analog trigger),��λ��΢��(uS)��ȡֵ��Χ[0, 1638]
	U32 nDelaySamps;		// �����ӳٵ���(0:Post Trigger, >0:Delay Trigger)

	// ��������
	U32 nReserved3;			// �����ֶ�(��δ����)
	U32 nReserved4;			// �����ֶ�(��δ����)
	U32 nReserved5;			// �����ֶ�(��δ����)
	U32 nReserved6;			// �����ֶ�(��δ����)
} USB3202_AI_PARAM, *PUSB3202_AI_PARAM;

// AIӲ�������ṹ��USB3202_AI_PARAM�е�nSampleSignal�����ź���ʹ�õ�ѡ��
#define USB3202_AI_SAMPSIGNAL_AI			0 // AIͨ�������ź�
#define USB3202_AI_SAMPSIGNAL_0V			1 // 0V(AGND)
#define USB3202_AI_SAMPSIGNAL_2D5V			2 // 2.5V(DC)

// AIӲ�������ṹ��USB3202_AI_PARAM�е�nSampleRange������ʹ�õĲ�����Χ��λѡ��
#define USB3202_AI_SAMPRANGE_N10_P10V		0 // ��10V
#define USB3202_AI_SAMPRANGE_N5_P5V			1 // ��5V
#define USB3202_AI_SAMPRANGE_0_P10V			2 // 0-10V
#define USB3202_AI_SAMPRANGE_0_P5V			3 // 0-5V

// AIӲ�������ṹ��USB3202_AI_PARAM�е�nSampleMode����ģʽ��ʹ�õ�ѡ��
#define USB3202_AI_SAMPMODE_ONE_DEMAND		0 // �������(����)
#define USB3202_AI_SAMPMODE_FINITE			2 // ���޵����
#define USB3202_AI_SAMPMODE_CONTINUOUS		3 // ��������

// AIӲ�������ṹ��USB3202_AI_PARAM�е�nClockSourceʱ��Դ��ʹ�õ�ѡ��
#define USB3202_AI_CLKSRC_LOCAL			0 // ����ʱ��(ͨ��Ϊ���ؾ���ʱ��OSCCLK),Ҳ���ڲ�ʱ��
#define USB3202_AI_CLKSRC_CLKIN			1 // �ⲿʱ��(��������CN2�ϵ�DIO2/CLKIN��������)

// AIӲ�������ṹ��USB3202_AI_PARAM�е�nDTriggerDir/nATriggerDir����������ʹ�õ�ѡ��
#define USB3202_AI_TRIGDIR_FALLING			0 // �½���/�͵�ƽ
#define USB3202_AI_TRIGDIR_RISING			1 // ������/�ߵ�ƽ
#define USB3202_AI_TRIGDIR_CHANGE			2 // �仯(�����±���/�ߵ͵�ƽ����Ч)

// #################### AI����״̬�ṹ��USB3202_AI_STATUS���� #####################
typedef struct _USB3202_AI_STATUS
{
	U32 bTaskDone;				// �ɼ����������־, =TRUE:��ʾ�ɼ������ѽ���, =FALSE:��ʾ�ɼ�����δ����(�����������ڽ�����)
	U32 bTriggered;				// ������־, =TRUE:��ʾ�ѱ�����, =FALSE:��ʾδ������(�����ȴ�����)

	U32 nTaskState;				// �ɼ�����״̬, =1:����, ����ֵ��ʾ���쳣���
	U32 nAvailSampsPerChan;		// �ɶ�������ֻ�������ڵ�ǰָ����������ʱ���ܵ���AI_ReadAnalog()������ȡָ�����ȵĲ�������
	U32 nMaxAvailSampsPerChan;	// ��AI_StartTask()����ֹ������ɶ�������״ֵ̬��Χ[0, nBufSampsPerChan],����Ϊ���ɼ�������ܶ��ṩ�������ֵԽ������1�����ʾ��ζ������Խ�ߣ�Խ���׳����������Ŀ���
	U32 nBufSampsPerChan;		// ÿͨ����������С(��������)��
	I64 nSampsPerChanAcquired;	// �Ѳ�������(������AI_StartTask()֮���������ĵ���)�����ֻ�Ǹ��û���ͳ������

	U32 nHardOverflowCnt;		// Ӳ���������(�ڲ��������º����0)
	U32 nSoftOverflowCnt;		// ����������(�ڲ��������º����0)
	U32 nInitTaskCnt;			// ��ʼ���ɼ�����Ĵ���(������AI_InitTask()�Ĵ���)
	U32 nReleaseTaskCnt;		// �ͷŲɼ�����Ĵ���(������AI_ReleaseTask()�Ĵ���)
	U32 nStartTaskCnt;			// ��AI_InitTask()֮�������ɼ�����Ĵ���(������AI_StartTask()�Ĵ���)
	U32 nStopTaskCnt;			// ��AI_InitTask()֮��ֹͣ�ɼ�����Ĵ���(������AI_StopTask()�Ĵ���)
	U32 nTransRate;				// ��������, ��ÿ�봫�����(sps)����ΪUSB��Ӧ������������ܵļ����Ϣ

	U32 nReserved0;				// �����ֶ�(��δ����)
	U32 nReserved1;				// �����ֶ�(��δ����)
	U32 nReserved2;				// �����ֶ�(��δ����)
	U32 nReserved3;				// �����ֶ�(��δ����)
	U32 nReserved4;				// �����ֶ�(��δ����)
} USB3202_AI_STATUS, *PUSB3202_AI_STATUS;

// #################### AI��Ҫ��Ϣ�ṹ��(USB3202_AI_MAIN_INFO) #######################
typedef struct _USB3202_AI_MAIN_INFO
{
	U32 nChannelCount;		// AIͨ������
	U32 nSampRangeCount;	// AI������Χ��λ����
	U32 nSampGainCount;		// AI�������浲λ����
	U32 nCouplingCount;		// AI��ϵ�λ����
	U32 nImpedanceCount;	// AI�迹�ĵ�λ����
	U32 nDepthOfMemory;		// AI���ش洢�����(����)
	U32 nSampResolution;	// AI�����ֱ���(��=8��ʾ8Bit; =12��ʾ12Bit; =14��ʾ14Bit; =16��ʾ16Bit)
	U32 nSampCodeCount;		// AI������������(��256, 4096, 16384, 65536)
	U32 nTrigLvlResolution;	// ������ƽ�ֱ���(��=8��ʾ8Bit; =12��ʾ12Bit; =16��ʾ16Bit)
	U32 nTrigLvlCodeCount;	// ������ƽ��������(��256, 4096)

	U32 nReserved0;			// �����ֶ�(��δ����)
	U32 nReserved1;			// �����ֶ�(��δ����)
	U32 nReserved2;			// �����ֶ�(��δ����)
	U32 nReserved3;			// �����ֶ�(��δ����)
} USB3202_AI_MAIN_INFO, *PUSB3202_AI_MAIN_INFO;

// #################### AI������Χ��Ϣ�ṹ��(USB3202_AI_VOLT_RANGE_INFO) #######################
typedef struct _USB3202_AI_VOLT_RANGE_INFO
{
	U32 nSampleRange;		// ��ǰ������Χ��λ��
	U32 nReserved0;			// �����ֶ�(��δ����)
	F64 fMaxVolt;			// ������Χ������ѹֵ,��λ:��(V)
	F64 fMinVolt;			// ������Χ����С��ѹֵ,��λ:��(V)
	F64 fAmplitude;			// ������Χ����,��λ:��(V)
	F64 fHalfOfAmp;			// ������Χ���ȵĶ���֮һ,��λ:��(V)
	F64 fCodeWidth;			// ������,��λ:��(V), ��ÿ����λ��ֵ������ĵ�ѹֵ
	F64 fOffsetVolt;		// ƫ�Ƶ�ѹ,��λ:��(V),һ��������ƫУ׼
	F64 fOffsetCode;		// ƫ����ֵ,һ��������ƫУ׼,������ĵ�ѹֵ�ȼ���fOffsetVolt
	char strDesc[16];		// ������Χ�ַ�����,��"��10V", "0-10V"��

	U32 nPolarity;			// ������Χ�ļ���(0=˫����BiPolar, 1=������UniPolar)
	U32 nCodeCount;			// ԭ������
	I32 nMaxCode;			// ԭ�����ֵ
	I32 nMinCode;	        // ԭ����Сֵ

	U32 nReserved1;			// �����ֶ�(��δ����)
	U32 nReserved2;			// �����ֶ�(��δ����)
	U32 nReserved3;			// �����ֶ�(��δ����)
	U32 nReserved4;			// �����ֶ�(��δ����)
} USB3202_AI_VOLT_RANGE_INFO, *PUSB3202_AI_VOLT_RANGE_INFO;

// �ṹ��AI_VOLT_RANGE_INFO�����ݳ�ԱPolarity���õĲ�����Χ����ѡ��
#define USB3202_AI_POLAR_BIPOLAR	0 // ˫����
#define USB3202_AI_POLAR_UNIPOLAR	1 // ������

// #################### AI������Ϣ�ṹ��(USB3202_AI_SAMP_GAIN_INFO) #######################
typedef struct _USB3202_AI_VOLT_GAIN_INFO
{
	U32 nSampleGain;		// ��ǰ�������浲λ��
	U32 nReserved0;			// �����ֶ�(��δ����)
	F64 fAmpFactor;			// �Ŵ���(Amplification Factor)
	char strDesc[16];		// ���������ַ�����,��"10��", "100��"��

	U32 nReserved1;			// �����ֶ�(��δ����)
	U32 nReserved2;			// �����ֶ�(��δ����)
	U32 nReserved3;			// �����ֶ�(��δ����)
	U32 nReserved4;			// �����ֶ�(��δ����)
} USB3202_AI_VOLT_GAIN_INFO, *PUSB3202_AI_VOLT_GAIN_INFO;

// #################### AI������Ϣ�ṹ��(USB3202_AI_SAMP_RATE_INFO) #######################
typedef struct _USB3202_AI_SAMP_RATE_INFO
{
	F64 fMaxRate;		// ��ͨ������������(sps)����ͨ��ʱ��ͨ��ƽ����������
	F64 fMinRate;		// ��ͨ����С��������(sps)����ͨ��ʱ��ͨ��ƽ����С������
	F64 fTimerBase;		// ʱ�ӻ�׼�������ؾ���Ƶ�ʣ���λ��Hz
	U32 nDivideMode;	// ��Ƶģʽ��0=������Ƶ(INTDIV), 1=DDS��Ƶ(DDSDIV)

	U32 nRateType;		// ��������,ָfMaxRate��fMinRate������, =0:��ʾΪ���в���ͨ����������, =1:��ʾΪÿ������ͨ��������
	U32 nReserved0;		// �����ֶ�(��δ����)
	U32 nReserved1;		// �����ֶ�(��δ����)
} USB3202_AI_SAMP_RATE_INFO, *PUSB3202_AI_SAMP_RATE_INFO;

// ###################### CTR���������ṹ��(USB3202_CTR_PARAM) #######################
typedef struct _USB3202_CTR_PARAM // ������CTR�йص�Ӳ����������(���CTR��������)
{
	U32 nPulseDir;		// ���巽��(0=�½���,1=������, 2=˫����)
	U32 bInitReset;		// �Ƿ��ڳ�ʼ��ʱ��λ��������0��=TRUE:��ʼ��ʱ���������, =FALSE:��ʼ���ǲ���
	U32 bFullReset;		// �Ƿ������ʱ�Զ���λ��������0��=TRUE:���ʱ�Զ���λ��0, =FALSE:�����ʱ��ס��ǰ��������

	U32 nReserved0;		// �����ֶ�(��δ����)
	U32 nReserved1;		// �����ֶ�(��δ����)
	U32 nReserved2;		// �����ֶ�(��δ����)
} USB3202_CTR_PARAM, *PUSB3202_CTR_PARAM;

// CTRӲ�������ṹ��USB3202_CTR_PARAM�е�nPulseDir���巽����ʹ�õ�ѡ��
#define USB3202_CTR_PULSEDIR_FALLING	0 // �±���
#define USB3202_CTR_PULSEDIR_RISING		1 // �ϱ���
#define USB3202_CTR_PULSEDIR_CHANGE		2 // �仯(���±��ؾ���Ч)

// #################### DIO��Ҫ��Ϣ�ṹ��(USB3202_DIO_PARAM) #######################
typedef struct _USB3202_DIO_PARAM // ������DIO�йص�Ӳ����������(���DIO��������)
{
	U8 bOutputEn[4];	// �����������(Output Enable),bOutputEn[n]=0:�����ֹ(��Ϊ����)��=1:�������(��������Ч)��(Ĭ�Ϸ���Ϊ����)
						// �����临�õ�CTRSRC,DTR,CLKIN,CLKOUT��Чʱ����������Ӧ��DIO��������Զ�ʧЧ
	
	U32 nReserved0;		// �����ֶ�(��δ����)
	U32 nReserved1;		// �����ֶ�(��δ����)
	U32 nReserved2;		// �����ֶ�(��δ����)
} USB3202_DIO_PARAM, *PUSB3202_DIO_PARAM;

// ################################ ����������Ϣ ################################
#define ERROR_NO_AVAILABLE_SAMPS	(0xE0000000+1)	// ����Ч����
#define ERROR_TASK_FAIL				(0xE0000000+2)	// ����ʧ��
#define ERROR_RATE_OVER_RANGE		(0xE0000000+3)	// �������ʳ���

// ################################ �豸�����ӿ����� ################################
#ifndef _USB3202_DRIVER_
#define DEVLIB __declspec(dllimport)
#else
#define DEVLIB __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	// ################################ DEV�豸��������� ################################
	HANDLE DEVLIB WINAPI USB3202_DEV_Create(					// �����豸������(hDevice), �ɹ�����ʵ�ʾ��,ʧ���򷵻�INVALID_HANDLE_VALUE(-1),�ɵ���GetLastError()��������ԭ��
										U32 nDeviceIdx,			// �豸���(�߼���Ż��������, ����ʹ����������ɲ���bUsePhysIdx����)
										BOOL bUsePhysIdx);		// �Ƿ�ʹ���������, =TRUE:ʹ���������, =FALSE:ʹ���߼����										

	U32 DEVLIB WINAPI USB3202_DEV_GetCount(void);				// ȡ�ø��豸��̨��,�ɹ�����ֵ>0, ʧ�ܷ���0(�ɵ���GetLastError()��������ԭ��)

	BOOL DEVLIB WINAPI USB3202_DEV_GetCurrentIdx(				// ���ָ���豸�е��߼���ź��������
										HANDLE hDevice,			// �豸������,����DEV_Create()��������
										U32* pLgcIdx,			// ���ص��߼����
										U32* pPhysIdx);			// ���ص��������

	BOOL DEVLIB WINAPI USB3202_DEV_GetSpeed(					// ��ȡ�豸���ӵ�USB�˿��ٶ�, 
										HANDLE hDevice,			// �豸������,����DEV_Create()��������
										U32* pSpeed);			// USB�ӿ��ٶȣ�=1:USB1.0, =2:USB2.0, =3:USB3.0

	BOOL DEVLIB WINAPI USB3202_DEV_Release(HANDLE hDevice);		// �ͷ��豸����(�ؼ�����)

	// ################################ AIģ��������ʵ�ֺ��� ################################
	BOOL DEVLIB WINAPI USB3202_AI_InitTask(					// ��ʼ���ɼ�����(Initialize Task)
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									PUSB3202_AI_PARAM pAIParam, // AI��������, �����ڴ˺����о���Ӳ����ʼ״̬�͸�����ģʽ,����������AI_VerifyParam()���в���У��
									HANDLE* pSampEvent);	// ���ز����¼�������,���豸�г��ֿɶ����ݶ�ʱ�ᴥ�����¼�������=NULL,��ʾ����Ҫ���¼����

    BOOL DEVLIB WINAPI USB3202_AI_StartTask(				// ��ʼ�ɼ�����
									HANDLE hDevice);		// �豸������,����DEV_Create()��������

    BOOL DEVLIB WINAPI USB3202_AI_SendSoftTrig(				// ������������¼�(Send Software Trigger),�������Ҳ��ǿ�ƴ���
									HANDLE hDevice);		// �豸������,����DEV_Create()��������

	BOOL DEVLIB WINAPI USB3202_AI_GetStatus(				// ȡ��AI�Ĳɼ�����״̬
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									PUSB3202_AI_STATUS pAIStatus);// ȡ��AI����״̬

	BOOL DEVLIB WINAPI USB3202_AI_WaitUntilTaskDone(		// �ɼ��������ǰ�ȴ�,����TRUE��ʾ�ɼ��������
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									F64 fTimeout);			// ���ڵȴ���ʱ�䣬��λ����(S)

	BOOL DEVLIB WINAPI USB3202_AI_ReadAnalog(				// �Ӳɼ������ж�ȡ��������(��ѹ��������)(Read analog data from the task)
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									F64 fAnlgArray[],		// ģ����������(��ѹ����),���ڷ��ز����ĵ�ѹ���ݣ�ȡֵ�����ɸ�ͨ������ʱ�Ĳ�����Χ����(��λ:V)
									U32 nReadSampsPerChan,	// ÿͨ�������ȡ�ĵ���(��λ����)
									U32* pSampsPerChanRead,	// ����ÿͨ��ʵ�ʶ�ȡ�ĵ���(��λ����), =NULL,��ʾ���뷵��
									U32* pAvailSampsPerChan,// �����л����ڵĿɶ�����, =NULL,��ʾ���뷵��
									F64 fTimeout);			// ��ʱʱ�䣬��λ����(S)

	BOOL DEVLIB WINAPI USB3202_AI_ReadBinary(				// �Ӳɼ������ж�ȡ��������(ԭ����������)(Read binary data from the task)
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									U16 nBinArray[],		// �������������飨ԭ�����飩,���ڷ��ز�����ԭ�����ݣ�ȡֵ����Ϊ[0, 65535]
									U32 nReadSampsPerChan,	// ÿͨ�������ȡ�ĵ���(��λ����)
									U32* pSampsPerChanRead,	// ����ÿͨ��ʵ�ʶ�ȡ�ĵ���(��λ����), =NULL,��ʾ���뷵��
									U32* pAvailSampsPerChan,// �����л����ڵĿɶ�����, =NULL,��ʾ���뷵��
									F64 fTimeout);			// ��ʱʱ�䣬��λ����(S)

	BOOL DEVLIB WINAPI USB3202_AI_StopTask(HANDLE hDevice);	// ֹͣ�ɼ�����

	BOOL DEVLIB WINAPI USB3202_AI_ReleaseTask(HANDLE hDevice); // �ͷŲɼ�����

	// ========================= AI������������ =========================
	BOOL DEVLIB WINAPI USB3202_AI_GetMainInfo(				// ���AI����Ҫ��Ϣ
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									PUSB3202_AI_MAIN_INFO pMainInfo); // ���AI��Ҫ��Ϣ

	BOOL DEVLIB WINAPI USB3202_AI_GetVoltRangeInfo(				// ��ò�����Χ�ĸ�����Ϣ(���ȡ��ֱ��ʡ�����)
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									U32 nChannel,			// AI����ͨ����(���ڱ��豸����ͨ������һ��������Χѡ��,�ʺ����0)
									U32 nSampleRange,		// ������Χѡ��[0, 4]
									PUSB3202_AI_VOLT_RANGE_INFO pRangeInfo); // ������Χ��Ϣ

	BOOL DEVLIB WINAPI USB3202_AI_GetGainInfo(				// �������ĸ�����Ϣ(���ȡ��ֱ��ʡ�����)
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									U32 nChannel,			// AI����ͨ����[0, 15]
									U32 nSampleGain,		// ����ѡ��[0, 3]
									PUSB3202_AI_VOLT_GAIN_INFO pGainInfo); // ������Ϣ

	BOOL DEVLIB WINAPI USB3202_AI_GetRateInfo(				// ��ò���������Ϣ
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									PUSB3202_AI_SAMP_RATE_INFO pRateInfo); // ����������Ϣ

 	BOOL DEVLIB WINAPI USB3202_AI_ScaleBinToVolt(			// ����ָ��������Χ������ԭ�����������ɵ�ѹ����,����ʵ�������ĵ���
									PUSB3202_AI_VOLT_RANGE_INFO pRangeInfo, // ��ǰת��������Ҫ�Ĳ�����Χ��Ϣ
									PUSB3202_AI_VOLT_GAIN_INFO pGainInfo,		// ��ǰת��������Ҫ�Ĳ���������Ϣ(����=NULL����ʾ��ʹ������)
									F64 fVoltArray[],		// ��ѹ��������,���ڷ���������ĵ�ѹ����,��λV
									U16 nBinArray[],		// ������ԭ������,���ڴ�������ǰ��ԭ�����ݣ�ȡֵ����Ϊ[0, 65535], (��ָĳ��ͨ������������)
									U32 nScaleSamps,		// ���������Ĳ�������
									U32* pSampsScaled);		// ����ʵ�������Ĳ�������, =NULL,��ʾ���뷵��

	BOOL DEVLIB WINAPI USB3202_AI_ScaleVoltToBin(			// ����ָ��������Χ����ѹ���������ɶ�����ԭ������,����ʵ�������ĵ���
									PUSB3202_AI_VOLT_RANGE_INFO pRangeInfo, // ��ǰת��������Ҫ�Ĳ�����Χ��Ϣ
									PUSB3202_AI_VOLT_GAIN_INFO pGainInfo,		// ��ǰת��������Ҫ�Ĳ���������Ϣ(����=NULL����ʾ��ʹ������)
									U16 nBinArray[],		// ԭ�뻺����,���ڷ����������ԭ�����ݣ�ȡֵ����Ϊ[0, 65535], (��ָĳ��ͨ������������)
									F64 fVoltArray[],		// ��ѹ������,���ڴ�������ǰ�ĵ�ѹ����,��λV
									U32 nScaleSamps,		// ���������Ĳ�������
									U32* pSampsScaled);		// ����ʵ�������Ĳ�������, =NULL,��ʾ���뷵��
	BOOL DEVLIB WINAPI USB3202_AI_VerifyParam(				// У��AI��������(Verify Parameter),�����ڳ�ʼ���ɼ�����ǰ���ô˺���У��������Ϸ���
									HANDLE hDevice,			// �豸������,����DEV_Create()��������
									PUSB3202_AI_PARAM pAIParam);// ��У���AI��������

	BOOL DEVLIB WINAPI USB3202_AI_LoadParam(HANDLE hDevice, PUSB3202_AI_PARAM pAIParam); // ��USB3202.ini�м���AI����
	BOOL DEVLIB WINAPI USB3202_AI_SaveParam(HANDLE hDevice, PUSB3202_AI_PARAM pAIParam); // ����AI������USB3202.ini
	BOOL DEVLIB WINAPI USB3202_AI_ResetParam(HANDLE hDevice, PUSB3202_AI_PARAM pAIParam); // ����ǰAI������λ������ֵ

	// ############################ CTR���������� ############################
	BOOL DEVLIB WINAPI USB3202_CTR_InitTask(			// ��ʼ�������ɼ�����
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nChannel,		// ͨ����(���豸����1��ͨ��,�����0)
									PUSB3202_CTR_PARAM pCTRParam); // ��������

	BOOL DEVLIB WINAPI USB3202_CTR_StartTask(			// ��ʼ�ɼ�����
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nChannel);		// ͨ����(���豸����1��ͨ��,�����0)

    BOOL DEVLIB WINAPI USB3202_CTR_ReadCounter(			// ��ȡ�������ĵ�ǰ����ֵ
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nChannel,		// ͨ����(���豸����1��ͨ��,�����0)
									U32* pCountVal);	// ����ֵ

	BOOL DEVLIB WINAPI USB3202_CTR_StopTask(			// ֹͣ(����ͣ)�ɼ�����
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nChannel);		// ͨ����(���豸����1��ͨ��,�����0)

	BOOL DEVLIB WINAPI USB3202_CTR_ReleaseTask(			// �ͷŲɼ�����
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nChannel);		// ͨ����(���豸����1��ͨ��,�����0)

	// ############################ DI��DO�������������ʵ�ֺ��� ############################
	BOOL DEVLIB WINAPI USB3202_DIO_InitTask(			// ��ʼ��DIO����
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nPort,			// �˿ں�(���豸����1���˿�,�����0)
									PUSB3202_DIO_PARAM pDIOParam); // ��������

	BOOL DEVLIB WINAPI USB3202_DIO_GetParam(			// ��ȡDIOӲ������
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nPort,			// �˿ں�(���豸����1���˿�,�����0)									
									PUSB3202_DIO_PARAM pDIOParam);	// ���������������ֵ

	BOOL DEVLIB WINAPI USB3202_DIO_ReadPort(			// ���������˿�ֵ(Read Digital Port Value)
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nPort,			// �˿ں�(���豸����1���˿�,�����0)
									U32* pPortData);	// ���صĶ˿�����, ��ЧλBit[7:0]

    BOOL DEVLIB WINAPI USB3202_DIO_WritePort(			// д�������˿�ֵ(Write Digital Port Value)
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nPort,			// �˿ں�(���豸����1���˿�,�����0)
									U32 nPortData);		// �˿�����, ��ЧλBit[7:0]

	BOOL DEVLIB WINAPI USB3202_DIO_ReadLines(			// ���������˿�ֵ(Read Digital Port Value)
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nPort,			// �˿ں�(���豸����1���˿�,�����0)
									U32 bLineDataArray[4]);// �����ݻ�����, ͬʱ���ض˿��и��ߵ�״ֵ̬bLineDataArray[n]=0:��ʾ��(���)״̬, =1��ʾ��(���)״̬

    BOOL DEVLIB WINAPI USB3202_DIO_WriteLines(			// д�������˿�ֵ(Write Digital Port Value)
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nPort,			// �˿ں�(���豸����1���˿�,�����0)
									U32 bLineDataArray[4]); // �����ݻ�����, �˿��и��ߵ�״ֵ̬bLineDataArray[n]=0:��ʾ��(���)״̬, =1��ʾ��(���)״̬

    BOOL DEVLIB WINAPI USB3202_DIO_ReadLine(			// ����ֵ
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nPort,			// �˿ں�(���豸����1���˿�,�����0)
									U32 nLine,			// �ߺ�[0, 3]
									U32* pLineData);		// ������, ȡֵ0��1 

    BOOL DEVLIB WINAPI USB3202_DIO_WriteLine(			// д��ֵ
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nPort,			// �˿ں�(���豸����1���˿�,�����0)
									U32 nLine,			// �ߺ�[0, 3]
									U32 bLineData);		// ��ֵ,ȡֵ0��1

	BOOL DEVLIB WINAPI USB3202_DIO_ReleaseTask(			// �ͷ�DIO����
									HANDLE hDevice,		// �豸������,����DEV_Create()��������
									U32 nPort);			// �˿ں�(���豸����1���˿�,�����0)
									
#ifdef __cplusplus
}
#endif

#ifndef _CVIDEF_H
	// �Զ������������������
	#ifndef _USB3202_DRIVER_
		#ifndef LOAD_USB3202_LIB // ���û�м���LIB��
			#define LOAD_USB3202_LIB
			#pragma comment(lib, "USB3202.lib")
			#pragma message("Welcome to use ART products!")
			#pragma message("Linked with USB3202.lib successfully!")
			#pragma message("Linked with USB3202.dll successfully!")
		#endif // LOAD_USB3202_LIB
	#endif // _USB3202_DRIVER_
#endif // _CVIDEF_H

#endif // _USB3202_DEVICE_