#ifndef LOAD
#define LOAD

extern int load_next_play(void); //装载下一个要播放的歌曲（把playlist装载到next_play中），返回0

extern int load_interface(void); //当next_playy->empty == 1时自动开始请求新的歌曲并下载、装载，返回0

#endif