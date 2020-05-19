#include "define.h"

//�������
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "conveyor.uir", PANEL)) < 0)
		return -1;

	Interface_Initial(); 
	
	DisplayPanel (panelHandle);
	
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

//���ص�
int CVICALLBACK panel_callback (int panel, int event, void *callbackData,
								int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			SetAsyncTimerAttribute (Time_handle, ASYNC_ATTR_ENABLED, 0);
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK time_display (int reserved,
							  int timerId, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:

			char str_systime[20]= {0};
			GetCurrentDateTime (&systime);
			FormatDateTimeString (systime, "%x\n%X", str_systime, 20);
			SetCtrlVal(panelHandle,PANEL_TextMsg1_time,str_systime);
			break;

	}
	return 0;

}

//�ı����������
int CVICALLBACK record_wipe (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			DeleteTextBoxLines (panelHandle, PANEL_recv, 0, -1);
			
			break;
	}
	return 0;
}

//����ģʽѡ��
int CVICALLBACK mode_select_callback (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{

	//int Numc_array[14]=
	//{
	//	PANEL_Numeric_0p,	 PANEL_Numeric_1p, PANEL_Numeric_2p,
	//	PANEL_Numeric_0i,	 PANEL_Numeric_1i, PANEL_Numeric_2i,
	//	PANEL_Numeric_0d,	 PANEL_Numeric_1d, PANEL_Numeric_2d,
	//	PANEL_Numeric_0s,    PANEL_Numeric_1s, PANEL_Numeric_2s,
	//	PANEL_Numeric_0max,  PANEL_Numeric_1max

	//};
	GetCtrlVal(panelHandle,PANEL_RingSlide,&ringsv);
	switch (event)
	{
		case EVENT_COMMIT:

			switch (ringsv)
			{
				case 0:
					
					for(int i=0; i<14; i++)
					{
						//(1==(i+1)%3)?SetCtrlAttribute(panelHandle,Numc_array[i], 500, 0 ):SetCtrlAttribute(panelHandle,Numc_array[i], 500, 1 ) ;
					}
					
					
					break;

				case 1:
					
					for(int i=0; i<14; i++)
					{
						//(2==(i+1)%3)?SetCtrlAttribute(panelHandle,Numc_array[i], 500, 0 ):SetCtrlAttribute(panelHandle,Numc_array[i], 500, 1 ) ;
						
					}
					
					
					break;

				case 2:
					
					for(int i=0; i<14; i++)
					{
						//(0==(i+1)%3)?SetCtrlAttribute(panelHandle,Numc_array[i], 500, 0 ):SetCtrlAttribute(panelHandle,Numc_array[i], 500, 1 ) ;
					}
					
					
					break;

			}
			
			break;
	}
	return 0;
}

//FPGA����д��
int CVICALLBACK sendat_to_fpga (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	short int sint_buff[5]= {0};
	unsigned int  locationS=0;
	switch (event)
	{
		case EVENT_COMMIT:

			SetCtrlVal(panelHandle,PANEL_Led_wrt,1);

			GetCtrlVal (panelHandle, PANEL_COM, &com) ;
			GetCtrlVal (panelHandle, PANEL_BOD, &bod) ;
			GetCtrlVal(panelHandle,PANEL_RingSlide,&ringsv);
			
			   
			switch (ringsv)
			{
				case 0://����
					GetCtrlVal(panelHandle,PANEL_Numeric_0p,	&sint_buff[0]);
					GetCtrlVal(panelHandle,PANEL_Numeric_0i,	&sint_buff[1]);
					GetCtrlVal(panelHandle,PANEL_Numeric_0d,	&sint_buff[2]);
					GetCtrlVal(panelHandle,PANEL_Numeric_0max,	&sint_buff[3]);
					GetCtrlVal(panelHandle,PANEL_Numeric_0s,	&sint_buff[4]);
					send_dat[0]=0xfb;
					send_dat[1]=0x8a; 
					
					//sint_buff[3]=(sint_buff[3]>0)?(sint_buff[3]&0x03ff):(sint_buff[3]&0x07ff);
					//sint_buff[4]=(sint_buff[4]>0)?(sint_buff[4]&0x03ff):(sint_buff[4]&0x07ff);
					//send_dat[8] = (char) (sint_buff[3]&0x00ff);
					//send_dat[9] = (char) ((sint_buff[3]&0xff00)>>8);
					//send_dat[10]= (char) (sint_buff[4]&0x00ff);
					//send_dat[11]= (char) ((sint_buff[4]&0xff00)>>8);
					send_dat[8]  = (char)(sint_buff[3] & 0x00ff);
					send_dat[9]  = (char)((sint_buff[3] & 0x0700) >> 8);
					send_dat[10] = (char)(sint_buff[4] & 0x00ff);
					send_dat[11] = (char)((sint_buff[4] & 0x0700) >> 8);

					break;
				case 1://�ٶ�
					GetCtrlVal(panelHandle,PANEL_Numeric_1p,	&sint_buff[0]);
					GetCtrlVal(panelHandle,PANEL_Numeric_1i,	&sint_buff[1]);
					GetCtrlVal(panelHandle,PANEL_Numeric_1d,	&sint_buff[2]);
					GetCtrlVal(panelHandle,PANEL_Numeric_1max,	&sint_buff[3]);
					GetCtrlVal(panelHandle,PANEL_Numeric_1s,	&sint_buff[4]);
					send_dat[0]=0xfb;
					send_dat[1]=0xaa; 
					
					//sint_buff[3]=(sint_buff[3]>0)?(sint_buff[3]&0x7fff):(sint_buff[3]&0xffff);
					//sint_buff[4]=(sint_buff[4]>0)?(sint_buff[4]&0x7fff):(sint_buff[4]&0xffff);
					
					send_dat[8] = (char)(sint_buff[3]&0x00ff);
					send_dat[9] = (char)((sint_buff[3]&0xff00)>>8);
					send_dat[10]= (char)(sint_buff[4]&0x00ff);
					send_dat[11]= (char)((sint_buff[4]&0xff00)>>8);
					
					break;
				case 2: //λ��
					
					GetCtrlVal(panelHandle,PANEL_Numeric_2p,	&sint_buff[0]);
					GetCtrlVal(panelHandle,PANEL_Numeric_2i,	&sint_buff[1]);
					GetCtrlVal(panelHandle,PANEL_Numeric_2d,	&sint_buff[2]);
					GetCtrlVal(panelHandle,PANEL_Numeric_2s,	&locationS);
					
					send_dat[0]=0xfb;
					send_dat[1]=0xca; 
					locationS&=0x0007ffff;
					
					send_dat[8] = (char)((locationS&0x000007f8)>>3);
					send_dat[9] = (char)((locationS&0x0007f800)>>11);
					send_dat[10]= (char)((locationS&0x00000007));
					send_dat[11]= (char)((locationS&0x00000000));
					
					break;
			}
			
			//PID��������		 send_dat[2]-send_dat[7]
			for(int i=0; i<3; i++)
			{
				//sint_buff[i]	=(sint_buff[i]>0)?sint_buff[i]&0x7fff:sint_buff[i]&0xffff;
				send_dat[2*i+2] = (char)(sint_buff[i]&0x00ff);
				send_dat[2*i+3] = (char)((sint_buff[i]&0xff00)>>8);
			}
			
			OpenComConfig (com,"" , bod, 0, 8, 1, 512, 512);
			SetComTime (com, 0.5);//��ʱʱ��
			
			if(ComWrt(com,send_dat,12)==12)
			{
				char TxMsg[200]= {0};
				char TimeA[10]= {0};
				char DataS[100]= {0};
				char DataS1[10] = { 0 };
				FormatDateTimeString (systime, "%X", TimeA, 10);
				for (int i = 0; i < 12; i++)
				{
					sprintf(DataS1, "0x%02hhx  ", send_dat[i]);
					strcat(DataS, DataS1);
					if (0 == (i + 1) % 4)
					{
						strcat(DataS, "\n");
					}
				}
				sprintf(TxMsg,"��%s�ѷ���12���ֽ�(��������ָ��)\n��ֵ(16����)Ϊ\n%s" ,TimeA, DataS );
				
				SetCtrlVal(panelHandle,PANEL_TextMsg2_inform,TxMsg); 
				
				SetCtrlVal(panelHandle,PANEL_numcc2,GetOutQLen(com));


			}
		
			
			CloseCom(com);
			Delay(0.1);
			SetCtrlVal(panelHandle,PANEL_Led_wrt,0);
			break;
	}
	return 0;
}

//���ݰ���������
int CVICALLBACK data_apply_switch (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	int das_st=0;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panelHandle,PANEL_TogBut1,&das_st);
			if(1==das_st)
			{
				GetCtrlVal (panelHandle, PANEL_COM, &com) ;
				GetCtrlVal (panelHandle, PANEL_BOD, &bod) ;
				GetCtrlVal (panelHandle,PANEL_ring_outp_form,&file_form); 
				SetCtrlVal (panelHandle, PANEL_LED,1);
				
				Folder_Create();
				if(1==file_form)
				{
					File_Create_Txt();
					fp_rec=fopen (abs_path_file_name, "a+");
				}
				else
				{
					File_Create_Bin();
					fp_rec=fopen (abs_path_file_name, "ab+");
				}
				
				
				
				OpenComConfig (com,"" , bod, 0, 8, 1, 512, 512);
				SetComTime (com, 0.5);//��ʱʱ��
				ssss=1;
				CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE, com_open_multhread, 0, &ID_datacept);
				
			}
			else
			{
				//SetAsyncTimerAttribute (DatApply_handle, ASYNC_ATTR_ENABLED, 0);     			 //ʧ�ܶ�ʱ�����������ݰ����첽��ʱ��
				 ssss=0;
				//251=0xFB��ʾ�������źţ� 15=0x0f(0000????��ʾֹͣ��PC����) ,���ͨѶЭ��
				send_dat[0]=0xfb;
				send_dat[1]=0x0f;
				for(int i=2; i<12; i++)
				{
					send_dat[i]=0xff;
				}
				
				
				if(12==ComWrt(com,send_dat,12))
				{
					char TxMsg[200]= {0};
					char TimeA[10]= {0};
					char DataS[100]={0};
					char DataS1[10] = { 0 };
					FormatDateTimeString (systime, "%X", TimeA, 10);
					for (int i = 0; i < 12; i++)
					{

						sprintf(DataS1, "0x%02hhx  ", send_dat[i]);
						strcat(DataS, DataS1);
						if (0 == (i + 1) % 4)
						{
							strcat(DataS, "\n");
						}
					}
					sprintf(TxMsg,"��%s�ѷ���12���ֽ�(�ر�ָ��)\n��ֵ(16����)Ϊ\n%s" ,TimeA, DataS );	  
					SetCtrlVal(panelHandle,PANEL_TextMsg2_inform,TxMsg);
					SetCtrlVal(panelHandle,PANEL_numcc1, GetInQLen(com));  
					//SetCtrlVal(panelHandle,PANEL_numcc2,GetOutQLen(com));
				}
				
				
				if(GetInQLen(com)>0)
				{
					FlushInQ(com);
				}
				CmtWaitForThreadPoolFunctionCompletion (DEFAULT_THREAD_POOL_HANDLE, ID_datacept, OPT_TP_PROCESS_EVENTS_WHILE_WAITING);
				fclose(fp_rec);
				CmtReleaseThreadPoolFunctionID(DEFAULT_THREAD_POOL_HANDLE, ID_datacept);
				SetCtrlVal(panelHandle, PANEL_LED,0); 
				CloseCom(com);
				
			}

			break;
	}
	return 0;
}

//�����߳�
int CVICALLBACK com_open_multhread (void *functionData)
{
	double data_application_interval=0.5;
	GetCtrlVal(panelHandle,PANEL_interval_apply,&data_application_interval);
	
	
	GetCtrlVal(panelHandle,PANEL_Point_Interval,&point_interval);
	
	//InstallComCallback(com, LWRS_RECEIVE, EPACK_SIZE, 0, com_callback, 0);


	//ʹ�ܶ�ʱ�����������ݰ����첽��ʱ��
	//DatApply_handle = NewAsyncTimer (data_application_interval, -1, 0, data_apply_asynt, 0);
	//SetAsyncTimerAttribute (DatApply_handle, ASYNC_ATTR_ENABLED, 1);
	
	int frequenc =0;
	GetCtrlVal(panelHandle,PANEL_frequenc_set_ring,&frequenc);
	//251=0xFBΪ�������ź�
	//send_dat[1=frequenc+16= 0001 0xxx ��ʾ��������  Ŀǰ������001-101��5���ֱ�Ϊ1K,2K,5K,10K,20K
	send_dat[0]= (char)(0xfb);
	send_dat[1]= (char)(frequenc+16);
	for(int i=2; i<12; i++)
	{
		send_dat[i]=0xff;
	}
	
	
	
	if(12==ComWrt(com,send_dat,12))
	{

		char TxMsg[200]= {0};
		char TimeA[10]= {0};
		char DataS[100]= {0};
		char DataS1[10] = { 0 };
		FormatDateTimeString (systime, "%X", TimeA, 10);
		for (int i = 0; i < 12; i++)
		{
			sprintf(DataS1, "0x%02hhx  ", send_dat[i]);
			strcat(DataS, DataS1);
			if (0 == (i + 1) % 4)
			{
				strcat(DataS, "\n");
			}
		}
		sprintf(TxMsg,"��%s�ѷ���12���ֽ�(��������ָ��)\n��ֵ(16����)Ϊ\n%s" ,TimeA, DataS );
		SetCtrlVal(panelHandle,PANEL_TextMsg2_inform,TxMsg);
		SetCtrlVal(panelHandle,PANEL_numcc1, GetInQLen(com)); 
	
	int 		Loc=0;											  //λ��19λ����������
	short int 	array_stemp[4]= {0};							  //ia,ib,iq,status
	char 		outword[80]= {0};
	char 		outwords[100]= {0};
	char 		buf[EPACK_SIZE]= {0};
	
	
	while(ssss){
				memset(outwords,0,100);
	
	SetCtrlVal(panelHandle,PANEL_numcc1,GetInQLen(com));


	//if(251==ComRdByte(portNumber))																		  //251=0xFB
	//{
		ComRd(com,buf,EPACK_SIZE);
		for(int i=0; i<EPACK_SIZE; i=i+EPACK_SIZE)
		{
			
			if(4==(buf[i+1] & 0x04))
			{
				array_stemp[0]	= (short int)(((buf[i] & 0xff) | ((buf[i+1] & 0x03) << 8)) | 0xfc00 );		//ia
			}
			else
			{
				array_stemp[0] 	= (short int)(((buf[i] & 0xff) | ((buf[i+1] & 0x03) << 8)) );
			}
			
			if(4==(buf[i+1] & 0x04))
			{
				array_stemp[1]	= (short int)(((buf[i+2] & 0xff) | ((buf[i+3] & 0x03) << 8)) | 0xfc00 );	//ib
			}
			else
			{
				array_stemp[1] 	= (short int)(((buf[i+2] & 0xff) | ((buf[i+3] & 0x03) << 8)) );  
			}

			Loc 			= (int)((buf[i+6]&0x07) | (((buf[i+4]&0xff)|((buf[i+5]&0xff)<<8))<<3));		

			array_stemp[2] 	= (short int)( ((buf[i+6]&0xe0)>>5) | ((buf[i+7]&0xff)<<3) );					//iq
			
			array_stemp[3]  = (short int)((buf[i+8]&0x01) );												//status
																											 
		
			
			sprintf(outword,"A�������%5hd  B�������%5hd  λ�ã�%5d iq:%5hd ״̬:%5hd\n",
									array_stemp[0],array_stemp[1],Loc,array_stemp[2],array_stemp[3]);
			strcat(outwords,outword);

		}
		
		//��ͼ�������
	
		if( 0==((icount++)%point_interval) )
		{
		PlotStripChart (panelHandle, PANEL_StripChart1, array_stemp, 2, 0, 0, VAL_SHORT_INTEGER); 		   //A��B�����
		PlotStripChart (panelHandle, PANEL_StripChart2, &Loc, 1, 0, 0, VAL_INTEGER);		  			   //λ��
		PlotStripChart (panelHandle, PANEL_StripChart3, &array_stemp[2], 1, 0, 0, VAL_SHORT_INTEGER);
		}
		
		InsertTextBoxLine (panelHandle, PANEL_recv, -1, outwords);

		
		if(file_form)
		{
			//�ı��ļ���ʽ
					 	 //" A��    B��    λ��  Iq   ״̬\n");
			fprintf(fp_rec,"%5hd  %5hd  %5d  %5hd  %5hd\n",
					array_stemp[0],array_stemp[1],Loc,array_stemp[2],array_stemp[3]);
			
			//printf( "%d",AvailSampPerCH); 														//�����ã�����ɶ�δ������
		}
		else
		{
			//��������ʽ
			fwrite(array_stemp ,2 ,4 ,fp_rec);		 									  //sizeof(short int)=2 ,ÿ��д4����:ia,ib,iq,status
			fwrite(&Loc		   ,4 ,1 ,fp_rec);											  //Loc��int���ͣ�����д��
			
			
		}



		

	//}



}	
		
		
		
		
		
		
		
		
		//SetCtrlVal(panelHandle,PANEL_numcc2,GetOutQLen(com));
	}


	return 0;
}

//����ͬ���ص�����:�������ݣ���ͼ��¼
void CVICALLBACK com_callback (int portNumber, int eventMask, void *callbackData)
{

	//char buf[EPACK_SIZE*NUM_APP_PACKS]= {0};
	//char outwords[EPACK_SIZE*NUM_APP_PACKS*10]= {0};
	//short int  ia,ib,statusn,nop,locate_iq;
	//short int array_stemp[NUM_APP_PACKS*4]= {0};
	int 		Loc=0;											  //λ��19λ����������
	short int 	array_stemp[4]= {0};							  //ia,ib,iq,status
	char 		outword[80]= {0};
	char 		outwords[100]= {0};
	char 		buf[EPACK_SIZE]= {0};
	

	
	SetCtrlVal(panelHandle,PANEL_numcc1,GetInQLen(portNumber));


	//if(251==ComRdByte(portNumber))																		  //251=0xFB
	//{
		ComRd(portNumber,buf,EPACK_SIZE);
		for(int i=0; i<EPACK_SIZE; i=i+EPACK_SIZE)
		{
			
			if(4==(buf[i+1] & 0x04))
			{
				array_stemp[0]	= (short int)(((buf[i] & 0xff) | ((buf[i+1] & 0x03) << 8)) | 0xfc00 );		//ia
			}
			else
			{
				array_stemp[0] 	= (short int)(((buf[i] & 0xff) | ((buf[i+1] & 0x03) << 8)) );
			}
			
			if(4==(buf[i+1] & 0x04))
			{
				array_stemp[1]	= (short int)(((buf[i+2] & 0xff) | ((buf[i+3] & 0x03) << 8)) | 0xfc00 );	//ib
			}
			else
			{
				array_stemp[1] 	= (short int)(((buf[i+2] & 0xff) | ((buf[i+3] & 0x03) << 8)) );  
			}

			Loc 			= (int)((buf[i+6]&0x07) | (((buf[i+4]&0xff)|((buf[i+5]&0xff)<<8))<<3));		

			array_stemp[2] 	= (short int)( ((buf[i+6]&0xe0)>>5) | ((buf[i+7]&0xff)<<3) );					//iq
			
			array_stemp[3]  = (short int)((buf[i+8]&0x01) );												//status
																											 
		
			
			sprintf(outword,"A�������%5hd  B�������%5hd  λ�ã�%5d iq:%5hd ״̬:%5hd\n",
									array_stemp[0],array_stemp[1],Loc,array_stemp[2],array_stemp[3]);
			strcat(outwords,outword);

		}
		
		//��ͼ�������
	
		if( 0==((icount++)%point_interval) )
		{
		PlotStripChart (panelHandle, PANEL_StripChart1, array_stemp, 2, 0, 0, VAL_SHORT_INTEGER); 		   //A��B�����
		PlotStripChart (panelHandle, PANEL_StripChart2, &Loc, 1, 0, 0, VAL_INTEGER);		  			   //λ��
		PlotStripChart (panelHandle, PANEL_StripChart3, &array_stemp[2], 1, 0, 0, VAL_SHORT_INTEGER);
		}
		InsertTextBoxLine (panelHandle, PANEL_recv, -1, outwords);

		
		if(file_form)
		{
			//�ı��ļ���ʽ
					 	 //" A��    B��    λ��  Iq   ״̬\n");
			fprintf(fp_rec,"%5hd  %5hd  %5d  %5hd  %5hd\n",
					array_stemp[0],array_stemp[1],Loc,array_stemp[2],array_stemp[3]);
			
			//printf( "%d",AvailSampPerCH); 														//�����ã�����ɶ�δ������
		}
		else
		{
			//��������ʽ
			fwrite(array_stemp ,2 ,4 ,fp_rec);		 									  //sizeof(short int)=2 ,ÿ��д4����:ia,ib,iq,status
			fwrite(&Loc		   ,4 ,1 ,fp_rec);											  //Loc��int���ͣ�����д��
			
			
		}



		

	//}



}

//�������
int CVICALLBACK emotor_switch (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	int emotor_sv=0;
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlVal(panelHandle,PANEL_Led_wrt,1);        
			GetCtrlVal(panelHandle,PANEL_emotor_button,&emotor_sv); 
			
			GetCtrlVal (panelHandle, PANEL_COM, &com) ;
			GetCtrlVal (panelHandle, PANEL_BOD, &bod) ;
			
			
			send_dat[0]=0xfb;
			send_dat[1]=0xea;  //��ʾ���Ƶ������ָ��
			for(int i=3;i<12;i++){send_dat[i]=0xff;}
			if(emotor_sv)
			{
				send_dat[2]=0x01;	
			}
			else
			{
				send_dat[2]=0x00;
			}
			
			OpenComConfig (com,"" , bod, 0, 8, 1, 512, 512);
			SetComTime (com, 0.5);//��ʱʱ��

			if(ComWrt(com,send_dat,12)==12)
			{
				char TxMsg[200]= {0};
				char TimeA[10]= {0};
				char DataS[100]= {0};
				char DataS1[10] = { 0 };
				FormatDateTimeString (systime, "%X", TimeA, 10);
				for (int i = 0; i < 12; i++)
				{
					sprintf(DataS1, "0x%02hhx  ", send_dat[i]);
					strcat(DataS, DataS1);
					if (0 == (i + 1) % 4)
					{
						strcat(DataS, "\n");
					}
				}
				sprintf(TxMsg,"��%s�ѷ���12���ֽ�(�����ָͣ��)\n��ֵ(16����)Ϊ\n%s" ,TimeA, DataS );
				SetCtrlVal(panelHandle,PANEL_TextMsg2_inform,TxMsg); 
				
				SetCtrlVal(panelHandle,PANEL_numcc2,GetOutQLen(com));  
				
			}
			CloseCom(com);
			Delay(0.1);
			SetCtrlVal(panelHandle,PANEL_Led_wrt,0); 
			break;
	}
	return 0;
}

//�����趨
int CVICALLBACK Param_Set (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	
	Point act_xy;
	char revise_label[20]={0}; 
	unsigned short int amend_v;    

	
	switch (event)
	{
		case EVENT_COMMIT:
			
			SetCtrlVal(panelHandle,PANEL_Led_wrt,1);
			
			GetCtrlVal( panelHandle,PANEL_Param_SN,&amend_v);  
			
			GetCtrlVal( panelHandle,PANEL_Param_SA,revise_label); 
			if(0==strcmp(revise_label,"����"))
			{
				MessagePopup("ע��","��ѡ�����в�������������Ҽ����ٽ����޸�");
				break;			
			}
		
			if(0==ringsv){MessagePopup("ע��","����ѡ������еĲ������ٽ����޸�");break;}
			GetTableCellVal (panelHandle, PANEL_Param_ST,MakePoint (1, ringsv) , revise_label); 
		
			
			
			 
			//char *v0=&amend_v;
			//char pv1=v0[0];
			//char pv2=v0[1];
			char v1 = amend_v&0x00ff;
			char v2 = (amend_v&0xff00)>>8;
			//���͸�����
		   
			GetCtrlVal (panelHandle, PANEL_COM, &com) ;
			GetCtrlVal (panelHandle, PANEL_BOD, &bod) ;


			send_dat[0]=0xfb;
			send_dat[1]=0xfa; 	 			//��ʾ������ַ����
			send_dat[2]=(char)(ringsv-1); 	 	//λ��
			send_dat[3]=v2; 				//�趨ֵ��8λ
			send_dat[4]=v1;					//�趨ֵ��8λ
			for(int i=5; i<12; i++)
			{
				send_dat[i]=0xff;
			}
		
			OpenComConfig (com,"" , bod, 0, 8, 1, 512, 512);
			SetComTime (com, 0.1);//��ʱʱ��

			if(ComWrt(com,send_dat,12)==12)
			{
				char TxMsg[200]= {0};
				char TimeA[10]= {0};
				char DataS[100]= {0};
				char DataS1[10] = { 0 };
				FormatDateTimeString (systime, "%X", TimeA, 10);
				for (int i = 0; i < 12; i++)
				{
					sprintf(DataS1, "0x%02hhx  ", send_dat[i]);
					strcat(DataS, DataS1);
					if (0 == (i + 1) % 4)
					{
						strcat(DataS, "\n");
					}
				}
				sprintf(TxMsg,"��%s�ѷ���12���ֽ�(����������)\n��ֵ(16����)Ϊ\n%s" ,TimeA, DataS );
				SetCtrlVal(panelHandle,PANEL_TextMsg2_inform,TxMsg);


				SetCtrlVal(panelHandle,PANEL_numcc2,GetOutQLen(com));

			}


			CloseCom(com);
			Delay(0.1);
			
			
			//��ʾ
			act_xy.y=ringsv;
			act_xy.x=2;
			SetTableCellVal (panelHandle, PANEL_Param_ST,act_xy , amend_v);  
			
			{
				char TxMsg[100]= {0};
				
				  
				sprintf(TxMsg,"�ѽ�%s��ֵ�޸�Ϊ%#x" ,revise_label,amend_v);
				InsertTextBoxLine (panelHandle, PANEL_recv, -1, TxMsg);      
				//SetCtrlVal(panelHandle,PANEL_TextMsg2_inform,"");  
			
			}
			
			SetCtrlVal( panelHandle,PANEL_Param_SN,0); 
			SetCtrlVal( panelHandle,PANEL_Param_SA,"����");    
			SetCtrlVal(panelHandle,PANEL_Led_wrt,0);          
			break;
	}
	return 0;
}

//�����޸�
void CVICALLBACK Param_Revise (int panelHandle, int controlID, int MenuItemID, void *callbackData)
{
	char revise_label[20]={0};   
	unsigned short int revise_val;
	
	Point act_xy;  
	GetActiveTableCell(panelHandle, PANEL_Param_ST, &act_xy); 
	
	
	
	
	
	act_xy.x=2;
	GetTableCellVal (panelHandle, PANEL_Param_ST,act_xy , &revise_val);
	SetCtrlVal( panelHandle,PANEL_Param_SN,revise_val);
	
	act_xy.x=1;   
	GetTableCellVal (panelHandle, PANEL_Param_ST,act_xy , revise_label); 
	SetCtrlVal( panelHandle,PANEL_Param_SA,revise_label); 
	 
	 //act_xy.y�������͹�����ringsv
	
	char TxMsg[100]= {0};
	
	sprintf(TxMsg,"ȡ������(%d,%d)%s��ֵ0x%04hx\n������16����ֵ��д��" ,act_xy.x,ringsv=act_xy.y,revise_label,revise_val);
	SetCtrlVal(panelHandle,PANEL_TextMsg2_inform,TxMsg);


}

//�����ʼ��
void Interface_Initial()
{
	Time_handle = NewAsyncTimer (1.0, -1, 0, time_display, 0);
	SetAsyncTimerAttribute (Time_handle, ASYNC_ATTR_ENABLED, 1);
	
	
	HideBuiltInCtrlMenuItem (panelHandle, PANEL_Param_ST,-2 );
	HideBuiltInCtrlMenuItem (panelHandle, PANEL_Param_ST,-3 );   
	HideBuiltInCtrlMenuItem (panelHandle, PANEL_Param_ST,-4 );   
	NewCtrlMenuItem (panelHandle, PANEL_Param_ST, "�޸�", -1, Param_Revise, 0);
	
   	SetCtrlVal( panelHandle,PANEL_Text_Note,"ѡ�����ݺ��Ҽ������޸�����\n(16����)");
}

void Folder_Create(void)
{
	int judgef_exist=0;						   	   	 //�ж�·������ֵ
	char file_dir[2*MAX_PATHNAME_LEN]= {0};		     //���·����Report�ļ��е�·��
	//FilePathName_Initialize
	GetProjectDir(project_route);
	sprintf(file_dir,"%s%s",project_route,"\\Report");
	judgef_exist=FileExists(file_dir,0);
	(0==judgef_exist)?(MakeDir (file_dir)):0;
	SetDir(file_dir);
}

void File_Create_Txt(void)
{
	double current_time;							 //ʱ�����          
	char file_name[MAX_FILENAME_LEN]= {0}; 			 //txt��ʽ�ļ���    
	GetCurrentDateTime(&current_time);
	{
		char CURTIME[20]= {0};
		FormatDateTimeString (current_time, "%Y%m%d-%H%M",CURTIME, 20);
		sprintf(file_name,"%s%s",CURTIME,".txt");
	}
	sprintf(abs_path_file_name,"%s%s%s",project_route,"\\Report\\",file_name);
	FILE *fp_txt;
	fp_txt=fopen (abs_path_file_name, "a+");
	//fprintf(fp_txt," A��    B��    λ��   ״̬\n");
	fclose(fp_txt);
	fp_txt=NULL;

}

void File_Create_Bin(void)
{
	double current_time;							 //ʱ�����          
	char file_name[MAX_FILENAME_LEN]= {0}; 			 //txt��ʽ�ļ���    
	GetCurrentDateTime(&current_time);
	{
		char CURTIME[20]= {0};
		FormatDateTimeString (current_time, "%Y%m%d-%H%M",CURTIME, 20);
		sprintf(file_name,"%s%s",CURTIME,".bin");
	}
	
	sprintf(abs_path_file_name,"%s%s%s",project_route,"\\Report\\",file_name);
	FILE *fp_bin;
	fp_bin=fopen (abs_path_file_name, "ab+");
	fclose(fp_bin);
	fp_bin=NULL;
}

int CVICALLBACK explore_directory (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			char file_dir[2*MAX_PATHNAME_LEN]= {0};		     //���·����Report�ļ��е�·��
			GetProjectDir(project_route);
			sprintf(file_dir,"%s%s",project_route,"\\Report");
		    
			//����DLL��̬���ӿ�
			HMODULE hmod = LoadLibrary("gofolder.dll");
			
			//���庯��ָ��ָ����ļ��еĺ���
			void ( *func_pt)(char* ) = (void(*)(char*))GetProcAddress(hmod,"go_folder");
			
			//ִ�иú���
			func_pt(file_dir);
			
			//�ͷŶ�̬���ӿ�
			FreeLibrary(hmod);
		
			break;
	}
	return 0;
}

int CVICALLBACK ghmghmg (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			
			break;
	}
	return 0;
}

//���ڿ���  --��ʱ����
int CVICALLBACK com_open_coback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int bval=0;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_COM, &com) ;
			GetCtrlVal (panelHandle, PANEL_BOD, &bod) ;
			GetCtrlVal (panelHandle, PANEL_BinSwitch1, &bval) ;

			if(1==bval)
			{
				SetCtrlVal(panelHandle, PANEL_LED,1);
				OpenComConfig (com,"" , bod, 0, 8, 1, 512, 512);
				SetComTime (com, 600);//��ʱʱ��
			}
			else
			{
				CloseCom(com);
				SetCtrlVal(panelHandle, PANEL_LED,0);
			}
			break;
	}
	return 0;
}

//�첽��ʱ������ʱ������������ָ��    --��ʱ����
int CVICALLBACK  data_apply_asynt(int reserved,
								  int timerId, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			
			//ÿ��data_application_interval�뷢��һ�ֽ���������ָ����͵�ֵΪ��Ҫ�������ݰ�������
			if(1==ComWrtByte(com,NUM_APP_PACKS))
			{
				char TxMsg[80]= {0};
				char TimeA[10]= {0};
				FormatDateTimeString (systime, "%X", TimeA, 10);
				sprintf(TxMsg,"%s�ѷ���1���ֽ�,\n��ֵΪ%#04hhx  " ,TimeA, NUM_APP_PACKS );
				SetCtrlVal(panelHandle,PANEL_TextMsg2_inform,TxMsg);
				SetCtrlVal(panelHandle,PANEL_numcc1, GetInQLen(com));
				//SetCtrlVal(panelHandle,PANEL_numcc2,GetOutQLen(com));

			}
			
			
			
			break;
	}
	return 0;

}
