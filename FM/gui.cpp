#include <stdio.h>
#include <easyx.h>
#include <conio.h>
#include <process.h>
#include "gui.h"
#include "player.h"
#include "playlist.h"
#include "file_manage.h"
#include "personal_post.h"
#include "login_out.h"

struct _channel_list *channel_list;

MOUSEMSG m;

Position channel_list_append(Position last, int channel, char channel_name[])
{
	Position tmp;
	tmp = (Position)malloc(sizeof(struct _channel_list));
	if (tmp == NULL)
		exit(1);
	last->next = tmp;
	tmp->channel = channel;
	strcpy(tmp->channel_name, channel_name);
	tmp->next = NULL;
	return tmp;
}

int gui_captcha_pic(void)
{
	char route[256] = "./tmp/captcha_pic.jpg";
	IMAGE img(250, 40);

	initgraph(250, 40, SHOWCONSOLE);
	SetWorkingImage(&img);
	loadimage(&img, _T(route), 250, 40);
	SetWorkingImage();
	putimage(0, 0, &img);

	return 0;
}

int gui_captcha_pic_close(void)
{
	closegraph();

	return 0;
}

int channel_list_clean(Position channel_list)
{
	if (channel_list->next != NULL)
		channel_list_clean(channel_list->next);
	free(channel_list);
	return 0;
}

int gui_initialize(void)
{
	Position tmp;

	/*�Ա���ɫ�����Ļ*/
	initgraph(700, 250);
	setbkmode(TRANSPARENT);
	setbkcolor(BGCOLOR);
	cleardevice();

	/*��ʼ��Ƶ���б�*/
	channel_list = (struct _channel_list *)malloc(sizeof(struct _channel_list));
	if (channel_list == NULL)
		exit(1);
	/*��һ��cell�ǿյ�*/
	tmp = channel_list_append(channel_list, -3, "My Favorite");
	tmp = channel_list_append(tmp, 0, "My Private");
	tmp = channel_list_append(tmp, -2, "Daily Private");
	tmp = channel_list_append(tmp, -10, "Douban Selected");
	tmp = channel_list_append(tmp, 153, "Working");
	tmp = channel_list_append(tmp, 151, "Outdoor");
	tmp = channel_list_append(tmp, 152, "Relaxing");
	tmp = channel_list_append(tmp, 154, "Exciting");
	tmp = channel_list_append(tmp, 155, "Peaceful");
	tmp = channel_list_append(tmp, 77, "Easy");
	tmp = channel_list_append(tmp, 10, "OST");
	tmp = channel_list_append(tmp, 27, "Classical");

	return 0;
}

int gui_play_song_info(char title[], char artist[])
{
	HRGN rgn = CreateRectRgn(30, 60, 450, 150); // ����һ����������
	setcliprgn(rgn); // ���þ�����������Ϊ�ü���
	DeleteObject(rgn); // ����ʹ�� rgn������ rgn ռ�õ�ϵͳ��Դ

	settextstyle(22, 18, "����");
	settextcolor(BLACK);
	outtextxy(35, 70, (LPCTSTR)title);
	settextstyle(14, 12, "����");
	outtextxy(35, 100, (LPCTSTR)artist);

	setcliprgn(NULL);

	return 0;
}

int gui_channel_info(int channel)
{
	char text[256];
	Position tmp = channel_list->next;
	HRGN rgn = CreateRectRgn(10, 10, 200, 50); // ����һ����������
	setcliprgn(rgn); // ���þ�����������Ϊ�ü���
	DeleteObject(rgn); // ����ʹ�� rgn������ rgn ռ�õ�ϵͳ��Դ

	while (1)
	{
		if (channel == tmp->channel)
		{
			strcpy(text, tmp->channel_name);
			break;
		}
		if (tmp->next == NULL)
		{
			strcpy(text, "Unknown Channel");
			break;
		}
		tmp = tmp->next;
	}

	settextstyle(15, 12, "����");
	settextcolor(GREEN);
	outtextxy(15, 15, text);

	setcliprgn(NULL);

	IMAGE btn_switch_channel(25, 25);
	SetWorkingImage(&btn_switch_channel);
	setbkcolor(BGCOLOR);
	setfillcolor(GREEN);
	setlinestyle(PS_NULL);
	cleardevice();
	POINT pts1[] = { { 0, 11 },{ 12, 0 },{ 25, 11 } };
	fillpolygon(pts1, 3); //������
	POINT pts2[] = { { 1, 15},{12, 25},{24, 15} };
	fillpolygon(pts2, 3); //������
	SetWorkingImage();
	putimage(200, 10, &btn_switch_channel);

	return 0;
}

int gui_buttons(int button)
{
	IMAGE btn_pause_resume(25, 25);
	IMAGE btn_next(25, 25);
	IMAGE btn_volume_up(25, 25);
	IMAGE btn_volume_down(25, 25);
	IMAGE btn_liked_disliked(25, 25);
	IMAGE btn_hate(25, 25);

	if (button == PAUSE)
	{
		SetWorkingImage(&btn_pause_resume);
		setbkcolor(BGCOLOR);
		setfillcolor(BLACK);
		setlinestyle(PS_NULL);
		cleardevice();
		fillrectangle(0, 0, 8, 25); //����
		fillrectangle(17, 0, 25, 25); //����
		SetWorkingImage();
		putimage(350, 180, &btn_pause_resume);
	}

	else if (button == RESUME)
	{
		SetWorkingImage(&btn_pause_resume);
		setbkcolor(BGCOLOR);
		setfillcolor(BLACK);
		setlinestyle(PS_NULL);
		cleardevice();
		POINT pts[] = { { 0, 0 },{ 25, 13 },{ 0, 25 } };
		fillpolygon(pts, 3); //����
		SetWorkingImage();
		putimage(350, 180, &btn_pause_resume);
	}

	else if (button == NEXT)
	{
		SetWorkingImage(&btn_next);
		setbkcolor(BGCOLOR);
		setfillcolor(BLACK);
		setlinestyle(PS_NULL);
		cleardevice();
		POINT pts[] = { { 0, 0 },{ 22, 13 },{ 0, 25 } };
		fillpolygon(pts, 3); //����
		fillrectangle(21, 0, 25, 25); //����
		SetWorkingImage();
		putimage(400, 180, &btn_next);
	}

	else if (button == VOLUME_UP)
	{
		SetWorkingImage(&btn_volume_up);
		setbkcolor(BGCOLOR);
		setfillcolor(BLACK);
		setlinestyle(PS_NULL);
		cleardevice();
		fillrectangle(0, 10, 25, 15); //����
		fillrectangle(10, 0, 15, 25); //����
		SetWorkingImage();
		putimage(300, 180, &btn_volume_up);
	}

	else if (button == VOLUME_DOWN)
	{
		SetWorkingImage(&btn_volume_down);
		setbkcolor(BGCOLOR);
		setfillcolor(BLACK);
		setlinestyle(PS_NULL);
		cleardevice();
		fillrectangle(0, 10, 25, 15); //����
		SetWorkingImage();
		putimage(250, 180, &btn_volume_down);
	}

	else if (button == LIKE_RED)
	{
		SetWorkingImage(&btn_liked_disliked);
		setbkcolor(BGCOLOR);
		setfillcolor(LIGHTRED);
		setlinestyle(PS_NULL);
		cleardevice();
		/*����*/
		POINT pts[] = { {12, 3}, {18, 0},{25, 6}, {25, 12}, {12, 25}, {0, 12}, {0, 6}, {6, 0} };
		fillpolygon(pts, 8);
		SetWorkingImage();
		putimage(30, 180, &btn_liked_disliked);
	}

	else if (button == LIKE_GRAY)
	{
		SetWorkingImage(&btn_liked_disliked);
		setbkcolor(BGCOLOR);
		setfillcolor(DARKGRAY);
		setlinestyle(PS_NULL);
		cleardevice();
		/*����*/
		POINT pts[] = { { 12, 3 },{ 18, 0 },{ 25, 6 },{ 25, 12 },{ 12, 25 },{ 0, 12 },{ 0, 6 },{ 6, 0 } };
		fillpolygon(pts, 8);
		SetWorkingImage();
		putimage(30, 180, &btn_liked_disliked);
	}
	else if (button == HATE)
	{
		SetWorkingImage(&btn_hate);
		setbkcolor(BGCOLOR);
		setfillcolor(DARKGRAY);
		setlinestyle(PS_NULL);
		cleardevice();
		/*����Ͱ*/
		fillrectangle(8, 0, 17, 3);
		fillrectangle(0, 3, 25, 6);
		fillrectangle(2, 8, 23, 11);
		fillrectangle(2, 11, 5, 22);
		fillrectangle(8, 11, 11, 22);
		fillrectangle(14, 11, 17, 22);
		fillrectangle(20, 11, 23, 22);
		fillrectangle(2, 22, 23, 25);
		SetWorkingImage();
		putimage(80, 180, &btn_hate);
	}
	return 0;
}

int gui_btn_file(void)
{
	IMAGE btn_file(25, 25);

	SetWorkingImage(&btn_file);
	setbkcolor(BGCOLOR);
	setfillcolor(LIGHTGRAY);
	setlinestyle(PS_NULL);
	cleardevice();
	fillrectangle(0, 0, 15, 4); //�̺���
	fillrectangle(0, 4, 25, 7); //������
	fillrectangle(0, 9, 25, 25); //����
	SetWorkingImage();
	putimage(615, 10, &btn_file);

	return 0;
}

int gui_check(char warning[])
{
	IMAGE btn_yes(100, 40);
	IMAGE btn_no(100, 40);

	setbkcolor(BGCOLOR);
	SetWorkingImage();
	cleardevice();

	/*Yesѡ��*/
	SetWorkingImage(&btn_yes);
	setbkcolor(BGCOLOR);
	cleardevice();
	setfillcolor(DARKGRAY);
	setlinecolor(LIGHTGRAY);
	fillrectangle(5, 5, 95, 35);
	settextstyle(14, 12, "����");
	settextcolor(WHITE);
	setbkcolor(DARKGRAY);
	outtextxy(25, 12, "Yes");

	/*Noѡ��*/
	SetWorkingImage(&btn_no);
	setbkcolor(BGCOLOR);
	cleardevice();
	setfillcolor(DARKGRAY);
	setlinecolor(LIGHTGRAY);
	fillrectangle(5, 5, 95, 35);
	settextstyle(14, 12, "����");
	settextcolor(WHITE);
	setbkcolor(DARKGRAY);
	outtextxy(30, 12, "No");

	SetWorkingImage();
	putimage(150, 180, &btn_yes);
	putimage(450, 180, &btn_no);

	settextstyle(18, 15, "����");
	settextcolor(BLACK);
	outtextxy(200, 60, warning);

	return 0;
}

int gui_cleaning(void)
{
	SetWorkingImage();
	setbkcolor(BGCOLOR);
	cleardevice();
	settextstyle(22, 18, "����");
	settextcolor(BLACK);
	outtextxy(180, 100, "Cleaning...");

	return 0;
}

int gui_btn_logout(void)
{
	IMAGE btn_logout(25, 25);

	SetWorkingImage(&btn_logout);
	setbkcolor(BGCOLOR);
	setfillcolor(LIGHTGRAY);
	setlinestyle(PS_NULL);
	cleardevice();
	/*������*/
	fillrectangle(1, 1, 24, 24);
	clearrectangle(6, 6, 18, 18);
	SetWorkingImage();
	putimage(665, 10, &btn_logout);

	return 0;
}

int gui_song_pic(char pic_name[])
{
	char route[256] = "./tmp/";
	IMAGE img(200, 200);
	strcat(route, pic_name);
	SetWorkingImage(&img);
	loadimage(&img, _T(route), 200, 200);
	SetWorkingImage();
	putimage(490, 40, &img);
	return 0;
}

int gui_channel_list(void)
{
	int i;
	Position tmp = channel_list->next;

	SetWorkingImage();
	setbkcolor(BGCOLOR);
	cleardevice();
	settextstyle(14, 12, "����");
	settextcolor(WHITE);
	setfillcolor(DARKGRAY);
	setlinecolor(LIGHTGRAY);
	/*��4*3�������ʽ��ʾƵ���б�*/
	for (i = 0; i != 12; i++)
	{
		fillrectangle((i % 3) * 200 + 45, (i / 3) * 50 + 40, (i % 3) * 200 + 235, (i / 3) * 50 + 70);
		outtextxy((i % 3) * 200 + 50, (i / 3) * 50 + 45, tmp->channel_name);
		if (tmp->next != NULL)
			tmp = tmp->next;
		else
			break;
	}

	return 0;
}

int gui_clean(void)
{
	closegraph();
	channel_list_clean(channel_list);
	return 0;
}

int gui_refresh(void)
{
	char buff[16];
	SetWorkingImage();
	cleardevice(); //�ñ���ɫ���
	gui_channel_info(channel); //��ʾƵ����Ϣ
	
	/*�����ǰ���Ÿ�����װ�����*/
	if (on_play->empty == 1)
	{
		gui_play_song_info("Loading...", "");
		gui_buttons(LIKE_GRAY);
	}
	/*�����ǰ���Ÿ���δװ�����*/
	else
	{
		gui_play_song_info(on_play->title, on_play->artist);
		gui_song_pic(on_play->pic_name);
		if (on_play->like == 0)
			gui_buttons(LIKE_GRAY);
		else
			gui_buttons(LIKE_RED);
	}

	/*���ݲ���״̬�ж���ʾʲô��ť*/
	mciSendString("status song mode", buff, 16, 0);
	if (strcmp(buff, "playing") == 0)
		gui_buttons(PAUSE);
	else
		gui_buttons(RESUME);

	/*��ʾһЩ��ť*/
	gui_buttons(NEXT);
	gui_buttons(VOLUME_UP);
	gui_buttons(VOLUME_DOWN);
	gui_buttons(HATE);
	gui_btn_file();
	gui_btn_logout();

	return 0;
}

int gui_mouse_msg(void)
{
	MOUSEMSG m; // ���������Ϣ
	char buff[16]; //mci��Ϣ

	while (1)
	{
	begin:
		Sleep(10);
		if (MouseHit())
		{
			m = GetMouseMsg();
			if (m.mkLButton)
			{
				/*����������ͣ/���ţ���һ�װ�ť�ж�*/
				if (m.x >= 250 && m.y >= 180 && m.x < 275 && m.y < 205)
					play_volume_down();
				else if (m.x >= 300 && m.y >= 180 && m.x < 325 && m.y < 205)
					play_volume_up();
				else if (m.x >= 350 && m.y >= 180 && m.x < 375 && m.y < 205)
				{
					play_pause_resume();
					gui_refresh();
				}
				else if (m.x >= 400 && m.y >= 180 && m.x < 425 && m.y < 205)
				{
					play_next();
					gui_refresh();
				}
				/*�ж�ϲ����ť*/
				else if (m.x >= 30 && m.y >= 180 && m.x < 55 && m.y < 205)
				{
					if (on_play->empty == 1)
						continue;
					_beginthreadex(NULL, 0, (_beginthreadex_proc_type)post_like_unlike, NULL, 0, NULL);
					on_play->like = !on_play->like;
					gui_refresh();
					continue;
				}
				/*�ж�hate��ť*/
				else if (m.x >= 80 && m.y >= 180 && m.x < 105 && m.y < 205)
				{
					_beginthreadex(NULL, 0, (_beginthreadex_proc_type)post_hate_wrapper, NULL, 0, NULL);
					play_next();
					gui_refresh();
					continue;
				}
				/*�ж�switch_channel��ť*/
				else if (m.x >= 200 && m.y >= 10 && m.x < 225 && m.y < 35)
				{
					gui_channel_list();
					/*�жϲ����б�ѡ��*/
					while (1)
					{
						Sleep(10);
						if(MouseHit())
						{
							m = GetMouseMsg();
							if (m.mkRButton)//����Ҽ��˳�Ƶ���б����
							{
								gui_refresh();
								goto begin;
							}
							else if (m.mkLButton) //ѡ��Ƶ���б�
							{
								int i;
								Position tmp = channel_list->next;

								for (i = 0; i != 12; i++)
								{
									if (m.x >= (i % 3) * 200 + 45 && m.y >= (i / 3) * 50 + 40 && m.x < (i % 3) * 200 + 235 && m.y < (i / 3) * 50 + 70)
									{
										/*�ı�Ƶ�����жϵ�ǰ����*/
										channel = tmp->channel; 
										on_play->empty = 1;
										next_play->empty = 1;
										play_break();
										gui_refresh();
										goto begin;
									}
									if (tmp->next != NULL)
										tmp = tmp->next;
									else
										break;
								}
							}
						}
					}
				}
				/*�ж�file��ť*/
				else if (m.x >= 615 && m.y >= 10 && m.x < 640 && m.y < 35)
				{
					gui_check("Clean all temp files?");
					while (1)
					{
						Sleep(10);
						if (MouseHit())
						{
							m = GetMouseMsg();
							if (m.mkLButton)
							{
								/*Yse*/
								if (m.x >= 200 && m.y >= 180 && m.x < 300 && m.y < 220)
								{
									gui_cleaning();
									/*ֹͣ�Զ�װ��*/
									on_play->empty = 0;
									next_play->empty = 0;
									/*�жϲ���*/
									play_break();
									/*��ʼ����*/
									file_clean_all();
									/*�ָ��Զ�װ��*/
									on_play->empty = 1;
									next_play->empty = 1;
									/*��ʾ������*/
									gui_refresh();
									goto begin;
								}
								/*No*/
								else if (m.x >= 500 && m.y >= 180 && m.x < 600 && m.y < 220)
								{
									gui_refresh();
									goto begin;
								}
							}
						}
					}
				}
				/*�ж�logout��ť*/
				else if (m.x >= 665 && m.y >= 10 && m.x < 690 && m.y < 35)
				{
					gui_check("Log out?");
					while (1)
					{
						Sleep(10);
						if (MouseHit())
						{
							m = GetMouseMsg();
							if (m.mkLButton)
							{
								/*Yes*/
								if (m.x >= 200 && m.y >= 180 && m.x < 300 && m.y < 220)
								{
									logout();
									return 0;
								}
								/*No*/
								else if (m.x >= 500 && m.y >= 180 && m.x < 600 && m.y < 220)
								{
									gui_refresh();
									goto begin;
								}
							}
						}
					}
				}
			}
		}
		/*�Զ�������һ��*/
		mciSendString("status song mode", buff, 16, 0);
		if (strcmp(buff, "") == 0 || strcmp(buff, "stopped") == 0)
		{
			if (play_next() == 0)
				gui_refresh();
		}
	}
	return 0;
}