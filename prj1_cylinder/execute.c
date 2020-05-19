#include "define.h"
#include "execute.h"
#include "task.h"
#include "file.h"     



int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "qigang.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK PANEL_callback (int panel, int event, void *callbackData,
								int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK Quit_Callback (int panel, int control, int event,
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

//计时器回调函数（记录数据/绘图）
int CVICALLBACK Asyn_Callback (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2)
{

	int Qua_SPC  = AIParam.nSampsPerChan ;				//每次执行读取操作的函数时每通道的采样点数
	double G2[2] = {0}, G3[2]= {0};
	double ActualVal_0[MAX_NUMS_TO_READ_PER_CH]= {0};	//0通道：温度	实际值
	double ActualVal_1[MAX_NUMS_TO_READ_PER_CH]= {0};   //1、2通道：压力实际值
	double ActualVal_2[MAX_NUMS_TO_READ_PER_CH]= {0};   //1、2通道：压力实际值
	double ActualVal_3[MAX_NUMS_TO_READ_PER_CH]= {0};   //3、4通道：扭矩实际值
	double ActualVal_4[MAX_NUMS_TO_READ_PER_CH]= {0};   //3、4通道：扭矩实际值
	double ActualVal_5[MAX_NUMS_TO_READ_PER_CH]= {0};   //5通道：加速度 实际值
	
	switch (event)
	{
		case EVENT_TIMER_TICK:
			GetCtrlVal(panelHandle,PANEL_BinSwitch,&token);
			if(token)
			{

				if(!USB3202_AI_ReadAnalog(hDevice, Collect_Buff, Qua_SPC, 			//每通道读入点数
										  &SampsPerChanRead, 						//每通道实际读入点数
										  &AvailSampPerCH, 							//每通道可读未读点数
										  Timeout))

				{
					auto char ErrContent[150] = {0};
					sprintf(ErrContent,"采集开关即将关闭 ",SampsPerChanRead);		//调试显示(Timeout nSampsPerChanRead=%d\n)
					MessagePopup("Error",ErrContent);

					SetCtrlVal (panelHandle, PANEL_LED,0);								//关闭采集
					SetCtrlVal (panelHandle, PANEL_BinSwitch,0);
					SetAsyncTimerAttribute (Async_handle, ASYNC_ATTR_ENABLED, 0);
					Task_Stop();
				}
				//整理数据：分离出每个通道的值存放至对应数组
				for(int pos=0; pos<(Qua_SPC-1); pos++)
				{
					ActualVal_0[pos] =  Data_Convert(Collect_Buff[0+pos*SAMPLE_CH_COUNT],0);
					ActualVal_1[pos] =  Data_Convert(Collect_Buff[1+pos*SAMPLE_CH_COUNT],1);
					ActualVal_2[pos] =  Data_Convert(Collect_Buff[2+pos*SAMPLE_CH_COUNT],2);
					ActualVal_3[pos] =  Data_Convert(Collect_Buff[3+pos*SAMPLE_CH_COUNT],3);
					ActualVal_4[pos] =  Data_Convert(Collect_Buff[4+pos*SAMPLE_CH_COUNT],4);
					ActualVal_5[pos] =  Data_Convert(Collect_Buff[5+pos*SAMPLE_CH_COUNT],5);
				}

				//绘图
				for(int graph_point=0; graph_point<Qua_SPC-1; graph_point+=delta_interval)
				{
					PlotStripChart (panelHandle, PANEL_Stripchart1, &ActualVal_0[graph_point], 	//温度
									1, 0, 0, VAL_DOUBLE);

					G2[0] = ActualVal_1[graph_point];
					G2[1] = ActualVal_2[graph_point];
					PlotStripChart (panelHandle, PANEL_Stripchart2, G2, 						//压力
									2, 0, 0, VAL_DOUBLE);

					G3[0] = ActualVal_3[graph_point];
					G3[1] = ActualVal_4[graph_point];
					PlotStripChart (panelHandle, PANEL_Stripchart3, G3, 						//扭矩
									2, 0, 0, VAL_DOUBLE);


					PlotStripChart (panelHandle, PANEL_Stripchart4, &ActualVal_5[graph_point],	//加速度
									1, 0, 0, VAL_DOUBLE);

				}

				//文件写入
				FILE *fp_rec;

				if(file_form)  
				{
					//文本文件形式
					fp_rec=fopen (abs_path_file_name, "a+");
					for(int fp=0; fp<Qua_SPC-1; fp++)
					{
						fprintf(fp_rec,"%10.6f        %10.6f        %10.6f        %10.6f        %10.6f        %10.6f\n",
								ActualVal_0[fp],ActualVal_1[fp],ActualVal_2[fp],ActualVal_3[fp],
								ActualVal_4[fp],ActualVal_5[fp]);
					
					}
					//printf( "%d",AvailSampPerCH); //调试用：输出可读未读点数 
				}
				else
				{
					//二进制形式
						fp_rec=fopen (abs_path_file_name, "ab+");
				
						fwrite(Collect_Buff, sizeof(double), 6 * Qua_SPC,fp_rec);
				
				}

				fclose(fp_rec);
	  
			}
			break;
	}
	return 0;
}

int CVICALLBACK Switch_Callback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int offon;
	int status;
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panelHandle,PANEL_BinSwitch,&offon);
			//根据开关状态启/停采集
			if(offon)
			{
				//打开采集开关后执行以下操作
				SetCtrlVal (panelHandle, PANEL_LED,1);
				GetCtrlVal (panelHandle,PANEL_Speedpspc,&rate_per_ch);
				GetCtrlVal (panelHandle,PANEL_Ring_out_form,&file_form);
				Folder_Create();
				(1==file_form)?File_Create_Txt():File_Create_Bin();
			
				status=Task_Initialize();
				//创建异步定时器开始采集(回调函数为Asyn_Callback)
				Async_handle = NewAsyncTimer (0.048, -1, 0, Asyn_Callback, 0);
				SetAsyncTimerAttribute (Async_handle, ASYNC_ATTR_ENABLED, 1);
			}
			else
			{
				//关闭采集开关后执行以下操作
				SetCtrlVal (panelHandle, PANEL_LED,0);
				SetAsyncTimerAttribute (Async_handle, ASYNC_ATTR_ENABLED, 0);
				Task_Stop();
			}
			break;
	}
	return 0;
}



int CVICALLBACK Explore_directory (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			char file_dir[2*MAX_PATHNAME_LEN]= {0};		     //软件路径下Report文件夹的路径
			GetProjectDir(project_route);
			sprintf(file_dir,"%s%s",project_route,"\\Report");
		    //	printf("%s",project_route);

			//加载DLL动态链接库
			HMODULE hmod = LoadLibrary("gofolder.dll");
			
			//定义函数指针指向打开文件夹的函数
			void ( *func_pt)(char* ) = (void(*)(char*))GetProcAddress(hmod,"go_folder");
			
			//执行该函数
			func_pt(file_dir);
			
			/*	
			HMODULE hmod2 = LoadLibrary("closeconsole.dll");
			void ( *func_pt2)() = (void(*)())GetProcAddress(hmod2,"closeconsole");
			func_pt2();
			 */
			
			//释放动态链接库
			FreeLibrary(hmod);
			//	FreeLibrary(hmod2);
			

			break;
	}
	return 0;
}
 


