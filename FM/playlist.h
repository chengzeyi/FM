#ifndef PLAYLIST
#define PLAYLIST

extern int channel;

struct _playlist
{
	char albumtitle[256]; //专辑名
	char song_url[256]; //音乐url
	char file_ext[32]; //后缀名
	char title[256]; //歌曲名
	char picture_url[256]; //图片url
	char artist[256]; //艺术家名
	char sid[32]; //sid
	char file_name[256]; //歌曲文件名
	char pic_name[256]; //歌曲图片名
	int like; //是否喜欢（是：1，否：0）
}; //结构体保存获取到的歌曲信息

extern struct _playlist *playlist; //指向保存歌曲信息的结构体的指针

extern size_t write_playlist(void *buffer, size_t size, size_t nmemb, void *userp); //回调函数，保存获取到的歌曲信息

extern int get_playlist(int channel); //获取歌曲信息，正常返回0，超时及异常返回1

extern int playlist_clean(void); //清理结构体，返回0

extern int playlist_interface(void); //重复获取歌曲信息直到成功，返回0

#endif
