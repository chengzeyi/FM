#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <windows.h> 
#include <curl/curl.h>
#include <conio.h>
#include "cJSON.h"
#include "login_out.h"
#include "playlist.h"
#include "download.h"
#include "player.h"
#include "load.h"
#include "gui.h"

int main(void)
{
	system("chcp 65001");
	system("cls");
	login_out_interface();
	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)load_interface, NULL, 0, NULL);
	player_interface();

	return 0;
}