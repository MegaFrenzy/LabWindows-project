
//定义主函数执行时的相关参数

HANDLE hDevice;  								//采集卡句柄
int Async_handle;								//异步定时器句柄
int panelHandle;									//面板句柄
USB3202_AI_PARAM AIParam;						//模拟输入结构体参数

int token;										//采集开关状态
int file_form; 									//文件输出方式 0：二进制  1：文本
int rate_per_ch;									//从面板接受的每通道采样速率
int delta_interval;								//画图间隙

U32 SampsPerChanRead , AvailSampPerCH ;			//每通道读入点数，可读未读的点数

double Collect_Buff[18000];  					//采样电压值缓冲区
double Timeout;									//超时时间      
