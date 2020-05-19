#include "file.h"

char project_route[2*MAX_PATHNAME_LEN]= {0}; 	//���·��   
char abs_path_file_name[500]= {0};				//�����贴�����ļ����ľ���·��

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
	fprintf(fp_txt,"  �¶�(��)           ѹ��1(Mpa)       ѹ��2(Mpa)      Ť��1(Nm)       Ť��2(Nm)        ���ٶ�(g)\n");
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
