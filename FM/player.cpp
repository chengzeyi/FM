#include <windows.h>
#include <mmsystem.h>
#include <process.h>  
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "playlist.h"
#include "download.h"
#include "gui.h"
#include "player.h"

int volume = 1000;

struct _message *message;

struct _play_song *on_play;

struct _play_song *next_play;

int player_initialize(void)
{
	on_play = (struct _play_song *)malloc(sizeof(struct _play_song));
	next_play = (struct _play_song *)malloc(sizeof(struct _play_song));
	message = (struct _message *)malloc(sizeof(struct _message));
	if (on_play == NULL || next_play == NULL || message == NULL)
	{
#ifdef DEBUG
		printf("memory out of space!\n");
		system("PAUSE");
#endif
		exit(1);
	}
	on_play->empty = 1;
	next_play->empty = 1;
	message->next = 0;
	message->pause_resume = 0;
	message->switch_channel = 0;
	message->volume_down = 0;
	message->volume_up = 0;

	return 0;
}

int play_start(void)
{
	if (on_play->empty)
		return 1;
	TCHAR route[256] = "./tmp/";
	strcat(route, on_play->file_name);
	TCHAR cmd[MAX_PATH + 10];
	wsprintf(cmd, "open %s alias song", route);
	mciSendString(cmd, NULL, 0, NULL);
	mciSendString("play song", NULL, 0, NULL);
	wsprintf(cmd, "setaudio song volume to %d", volume);
	mciSendString(cmd, NULL, 0, NULL);
	return 0;
}

int play_pause(void)
{
	mciSendString("pause song", NULL, 0, NULL);
	return 0;
}

int play_resume(void)
{
	mciSendString("resume song", NULL, 0, NULL);
	return 0;
}

int play_pause_resume(void)
{
	char buff[8];
	mciSendString("status song mode", buff, 8, NULL);
	if (strcmp(buff, "paused") == 0)
		play_resume();
	else if(strcmp(buff, "playing") == 0)
		play_pause();
	return 0;
}

int play_volume_up(void)
{
	TCHAR cmd[256];
	if (volume == 1000)
		return 0;
	volume += 100;
	wsprintf(cmd, "setaudio song volume to %d", volume);
	mciSendString(cmd, NULL, 0, NULL);
	return 0;
}

int play_volume_down(void)
{
	TCHAR cmd[256];
	if (volume == 0)
		return 0;
	volume -= 100;
	wsprintf(cmd, "setaudio song volume to %d", volume);
	mciSendString(cmd, NULL, 0, NULL);
	return 0;
}

int play_break(void)
{
	mciSendString("stop song", NULL, 0, NULL);
	mciSendString("close song", NULL, 0, NULL);
	return 0;
}

int play_next(void)
{
	struct _play_song *tmp;

	play_break();
	on_play->empty = 1;
	if (next_play->empty == 1)
	{
#ifdef DEBUG
		printf("downloading hasn't been finished!\n");
#endif
		return 1;
	}
	/*将next_play导入on_play并将next_play->empty设为1*/
	tmp = on_play;
	on_play = next_play;
	next_play = tmp;
	play_start();
	return 0;
}

int player_clean(void)
{
	free(on_play);
	free(next_play);
	free(message);
	return 0;
}

int player_interface(void)
{
	channel = 0;
	player_initialize();
	gui_initialize();
	gui_refresh();
	gui_mouse_msg();
	player_clean();
	gui_clean();

	return 0;
}