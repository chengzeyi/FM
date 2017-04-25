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
}; //�򵥶�̬��������Ƶ����Ϣ

extern int gui_captcha_pic(void); //���û���¼ʱ��ʾ��֤��ͼƬ������0

extern int gui_captcha_pic_close(void); //�ر���֤��ͼƬ���ڣ�����0

extern struct _channel_list *channel_list; //����ͷ���գ�

extern Position channel_list_append(Position last, int channel, char channel_name[]); //������ĩ�˲����µ�cell������һ��ָ������ĩ��cell��ָ��

extern int channel_list_clean(Position channel_list); //�����������0

extern int gui_initialize(void); //��ʼ�������������棬����0

extern int gui_play_song_info(char title[], char artist[]); //��ʾ���ڲ��ŵĸ�������Ϣ������0

extern int gui_channel_info(int channel); //��ʾ��ǰƵ����Ϣ������0

extern int gui_buttons(int button); //��ʾ������Ϣ�·��ļ�����ť������0

extern int gui_song_pic(char pic_name[]); //��ʾ����ͼƬ������0

extern int gui_channel_list(void); //��ʾ��ѡ��Ƶ���б�����0

extern int gui_btn_file(void); //��ʾ�����ļ���ť������0

extern int gui_btn_logout(void); //��ʾ�ǳ���ť������0

extern int gui_check(char warning[]); //����char warning[]��ʾһ��ȷ�Ͽ򣬷���0

extern int gui_cleaning(void); //�������ļ���������ʾ"cleanning"����������0

extern int gui_clean(void); //�رղ����������沢�����������0

extern int gui_refresh(void); //ˢ��һ�β����������棬����0

extern int gui_mouse_msg(void); //׷���û�����������ʱˢ�²����������沢��ʾ���ʵ����ݣ��Զ���ʼ��һ�׸����Ĳ��ţ����û��ǳ����˳�������������0

#endif