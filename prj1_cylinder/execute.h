
//����������ִ��ʱ����ز���

HANDLE hDevice;  								//�ɼ������
int Async_handle;								//�첽��ʱ�����
int panelHandle;									//�����
USB3202_AI_PARAM AIParam;						//ģ������ṹ�����

int token;										//�ɼ�����״̬
int file_form; 									//�ļ������ʽ 0��������  1���ı�
int rate_per_ch;									//�������ܵ�ÿͨ����������
int delta_interval;								//��ͼ��϶

U32 SampsPerChanRead , AvailSampPerCH ;			//ÿͨ������������ɶ�δ���ĵ���

double Collect_Buff[18000];  					//������ѹֵ������
double Timeout;									//��ʱʱ��      
