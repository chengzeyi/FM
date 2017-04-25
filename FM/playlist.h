#ifndef PLAYLIST
#define PLAYLIST

extern int channel;

struct _playlist
{
	char albumtitle[256]; //ר����
	char song_url[256]; //����url
	char file_ext[32]; //��׺��
	char title[256]; //������
	char picture_url[256]; //ͼƬurl
	char artist[256]; //��������
	char sid[32]; //sid
	char file_name[256]; //�����ļ���
	char pic_name[256]; //����ͼƬ��
	int like; //�Ƿ�ϲ�����ǣ�1����0��
}; //�ṹ�屣���ȡ���ĸ�����Ϣ

extern struct _playlist *playlist; //ָ�򱣴������Ϣ�Ľṹ���ָ��

extern size_t write_playlist(void *buffer, size_t size, size_t nmemb, void *userp); //�ص������������ȡ���ĸ�����Ϣ

extern int get_playlist(int channel); //��ȡ������Ϣ����������0����ʱ���쳣����1

extern int playlist_clean(void); //����ṹ�壬����0

extern int playlist_interface(void); //�ظ���ȡ������Ϣֱ���ɹ�������0

#endif
