#include <io.h>
#include <string.h>
#include "file_manage.h"

int file_clean_all(void)
{
	int i = 0;
	char route[256];
	struct _finddata_t file;
	/*删除mp3文件*/
	while(_findfirst("./tmp/*.mp3", &file) != -1)
	{
		strcpy(route, "./tmp/");
		strcat(route, file.name);
		remove(route);
		i++;
		if (i == MAX_FILE_AMOUNT)
			break;
	}
	/*删除jpg文件*/
	while (_findfirst("./tmp/*.jpg", &file) != -1)
	{
		strcpy(route, "./tmp/");
		strcat(route, file.name);
		remove(route);
		i++;
		if (i == MAX_FILE_AMOUNT)
			break;
	}
	return 0;
}