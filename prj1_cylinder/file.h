#include "define.h"



extern char project_route[2*MAX_PATHNAME_LEN]; 	//软件路径   
extern char abs_path_file_name[500];				//包含需创建的文件名的绝对路径


void 	Folder_Create(void); 					//创建文件夹
void 	File_Create_Txt(void); 					//创建文本文件
void 	File_Create_Bin(void); 					//创建二进制文件    
