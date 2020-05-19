#include <Windows.h>
#include <shellapi.h>


_declspec(dllexport) void go_folder(char* folder_route)

{
	ShellExecuteA(0, "open", folder_route, 0, 0, 0);

}