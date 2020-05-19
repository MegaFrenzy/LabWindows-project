#include "file.h"

char project_route[2*MAX_PATHNAME_LEN]= {0}; 	//软件路径   
char abs_path_file_name[500]= {0};				//包含需创建的文件名的绝对路径

void Folder_Create(void)
{
	int judgef_exist=0;						   	   	 //判断路径存在值
	char file_dir[2*MAX_PATHNAME_LEN]= {0};		     //软件路径下Report文件夹的路径
	//FilePathName_Initialize
	GetProjectDir(project_route);
	sprintf(file_dir,"%s%s",project_route,"\\Report");
	judgef_exist=FileExists(file_dir,0);
	(0==judgef_exist)?(MakeDir (file_dir)):0;
	SetDir(file_dir);
}

void File_Create_Txt(void)
{
	double current_time;							 //时间参数          
	char file_name[MAX_FILENAME_LEN]= {0}; 			 //txt格式文件名    
	GetCurrentDateTime(&current_time);
	{
		char CURTIME[20]= {0};
		FormatDateTimeString (current_time, "%Y%m%d-%H%M",CURTIME, 20);
		sprintf(file_name,"%s%s",CURTIME,".txt");
	}
	sprintf(abs_path_file_name,"%s%s%s",project_route,"\\Report\\",file_name);
	FILE *fp_txt;
	fp_txt=fopen (abs_path_file_name, "a+");
	fprintf(fp_txt,"  温度(℃)           压力1(Mpa)       压力2(Mpa)      扭矩1(Nm)       扭矩2(Nm)        加速度(g)\n");
	fclose(fp_txt);
	fp_txt=NULL;

}

void File_Create_Bin(void)
{
	double current_time;							 //时间参数          
	char file_name[MAX_FILENAME_LEN]= {0}; 			 //txt格式文件名    
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
