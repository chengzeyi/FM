#include <windows.h>
#include <string.h>
#include "load.h"
#include "playlist.h"
#include "download.h"
#include "player.h"

int load_next_play(void)
{
	strcpy(next_play->title, playlist->title);
	strcpy(next_play->file_name, playlist->file_name);
	strcpy(next_play->pic_name, playlist->pic_name);
	strcpy(next_play->artist, playlist->artist);
	strcpy(next_play->sid, playlist->sid);
	next_play->like = playlist->like;
	next_play->empty = 0;
	return 0;
}

int load_interface(void)
{
	while (1)
	{
		if (next_play == NULL)
			continue;
		if (next_play->empty == 1)
		{
			playlist_interface();
			download_interface();
			load_next_play();
		}
		Sleep(1000);
	}
}