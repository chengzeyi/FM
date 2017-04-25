#ifndef PLAYER
#define PLAYER
#define SHOW_GUI

extern int volume; //保存音量(ranging from 0 to 1000, default: 1000, step: 100)

struct _message
{
	int pause_resume;
	int volume_up;
	int volume_down;
	int next;
	int switch_channel;
}; //结构体用于在控制台下保存用户控制信息（已废弃）

extern struct _message *message; //指向用户控制信息的指针（已废弃）

struct _play_song
{
	char title[256];
	char artist[256];
	char file_name[256];
	char pic_name[256];
	char sid[32];
	int like;
	int empty;
}; //结构体用于保存播放器中的歌曲信息

extern struct _play_song *on_play; //指向正在播放的歌曲信息的指针

extern struct _play_song *next_play; //指向下一个要播放的歌曲信息的指针

extern int player_initialize(void); //初始化播放器，返回0

extern int play_start(void); //开始播放，返回0

extern int play_pause(void); //暂停播放，返回0

extern int play_resume(void); //恢复播放，返回0

extern int play_pause_resume(void); //根据当前播放的状态判断是要暂停还是恢复播放，返回0

extern int play_volume_up(void); //增大音量，返回0

extern int play_volume_down(void); //减小音量，返回0

extern int play_next(void); //播放下一首，成功返回0，若下一首歌曲还未装载好返回1

extern int play_break(void); //中断播放，返回0

extern int player_clean(void); //清空结构体，返回0

extern int player_interface(void); //启动播放器，启动消息循环，启动GUI，在消息循环退出后清空GUI和播放器，返回0

#endif