#include <windows.h> 

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR lpCmdLine, int)
{
	int i = 0;

	for (i = 0; i < strlen(lpCmdLine); i++)
	{
		if (!isdigit(lpCmdLine[i]))
		{
			MessageBox(NULL, "Parameter is not an integer!", "Error", MB_ABORTRETRYIGNORE);
			return 0;
		}
	}

	MessageBox(NULL, lpCmdLine, "Caption", MB_OK);
	
	return 0;
}