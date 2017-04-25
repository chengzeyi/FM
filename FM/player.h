#ifndef PLAYER
#define PLAYER
#define SHOW_GUI

extern int volume; //��������(ranging from 0 to 1000, default: 1000, step: 100)

struct _message
{
	int pause_resume;
	int volume_up;
	int volume_down;
	int next;
	int switch_channel;
}; //�ṹ�������ڿ���̨�±����û�������Ϣ���ѷ�����

extern struct _message *message; //ָ���û�������Ϣ��ָ�루�ѷ�����

struct _play_song
{
	char title[256];
	char artist[256];
	char file_name[256];
	char pic_name[256];
	char sid[32];
	int like;
	int empty;
}; //�ṹ�����ڱ��沥�����еĸ�����Ϣ

extern struct _play_song *on_play; //ָ�����ڲ��ŵĸ�����Ϣ��ָ��

extern struct _play_song *next_play; //ָ����һ��Ҫ���ŵĸ�����Ϣ��ָ��

extern int player_initialize(void); //��ʼ��������������0

extern int play_start(void); //��ʼ���ţ�����0

extern int play_pause(void); //��ͣ���ţ�����0

extern int play_resume(void); //�ָ����ţ�����0

extern int play_pause_resume(void); //���ݵ�ǰ���ŵ�״̬�ж���Ҫ��ͣ���ǻָ����ţ�����0

extern int play_volume_up(void); //��������������0

extern int play_volume_down(void); //��С����������0

extern int play_next(void); //������һ�ף��ɹ�����0������һ�׸�����δװ�غ÷���1

extern int play_break(void); //�жϲ��ţ�����0

extern int player_clean(void); //��սṹ�壬����0

extern int player_interface(void); //������������������Ϣѭ��������GUI������Ϣѭ���˳������GUI�Ͳ�����������0

#endif