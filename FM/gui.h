#ifndef GUI
#define GUI
#define BGCOLOR 0xFAFAFA
#define VOLUME_UP 1
#define VOLUME_DOWN 2
#define PAUSE 3
#define RESUME 4
#define NEXT 5
#define LIKE_RED 6
#define LIKE_GRAY 7
#define HATE 8

typedef struct _channel_list *PtrToList;

typedef PtrToList Position;

struct _channel_list
{
	int channel;
	char channel_name[256];
	Position next;
}; //简单动态链表，保存频道信息

extern int gui_captcha_pic(void); //在用户登录时显示验证码图片，返回0

extern int gui_captcha_pic_close(void); //关闭验证码图片窗口，返回0

extern struct _channel_list *channel_list; //链表头（空）

extern Position channel_list_append(Position last, int channel, char channel_name[]); //在链表末端插入新的cell，返回一个指向链表末端cell的指针

extern int channel_list_clean(Position channel_list); //清空链表，返回0

extern int gui_initialize(void); //初始化播放器主界面，返回0

extern int gui_play_song_info(char title[], char artist[]); //显示正在播放的歌曲的信息，返回0

extern int gui_channel_info(int channel); //显示当前频道信息，返回0

extern int gui_buttons(int button); //显示歌曲信息下方的几个按钮，返回0

extern int gui_song_pic(char pic_name[]); //显示封面图片，返回0

extern int gui_channel_list(void); //显示可选的频道列表，返回0

extern int gui_btn_file(void); //显示清理文件按钮，返回0

extern int gui_btn_logout(void); //显示登出按钮，返回0

extern int gui_check(char warning[]); //根据char warning[]显示一个确认框，返回0

extern int gui_cleaning(void); //在清理文件过程中显示"cleanning"字样，返回0

extern int gui_clean(void); //关闭播放器主界面并清空链表，返回0

extern int gui_refresh(void); //刷新一次播放器主界面，返回0

extern int gui_mouse_msg(void); //追踪用户鼠标操作，适时刷新播放器主界面并显示合适的内容，自动开始下一首歌曲的播放，在用户登出后退出播放器，返回0

#endif