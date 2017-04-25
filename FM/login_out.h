#ifndef LOGIN_OUT
#define LOGIN_OUT

extern char *captcha_id; //��֤��ID

extern int status; //����״̬��0��ʾ������1��ʾ�쳣

struct _post_data
{
	int liked;
	int banned;
	int played;
	int is_pro;
	char user_name[128];
}; //�ṹ�屣�浱ǰ�û���Ϣ��Ŀǰûʲô�ã�

extern struct _post_data *post_data; //ָ��ṹ���ָ��

extern size_t write_captcha_id(void *buffer, size_t size, size_t nmemb, void *userp); //�ص�������������֤��ID

extern size_t write_captcha_pic(void *buffer, size_t size, size_t nmemb, void *userp); //�ص�������������֤��ͼƬ

extern size_t write_request_token(void *buffer, size_t size, size_t nmemb, void *userp); //�ص������������û���Ϣ��Ŀǰûʲô�ã�

extern size_t write_status(void *buffer, size_t size, size_t nmemb, void *userp); //�ص������������û���¼״̬���޸�status����

extern int get_captcha_id(void); //��ȡ��֤��ID����������0����ʱ���쳣����1

extern int get_captcha_pic(void); //��ȡ��֤��ͼƬ����������0����ʱ���쳣����1

extern int request_token(char email[], char password[], char captcha_solution[], char captcha_id[]); //�ύ�û���¼��Ϣ����ȡ�û���Ϣ����������0����ʱ���쳣����1

extern int login_out_interface(void); //������������ʾ��¼���棬�Ѿ�����ʱ������¼������������֤��ID��ͼƬ����ʾ�û������¼��Ϣ����ʾ��֤��ͼƬ���ظ�ѭ��ֱ����¼�ɹ�������0

int login_out_clean(void); //���captcha_id��post_data������0

int get_status(void); //��ȡ�û���ǰ�ĵ�¼״̬����������0����ʱ���쳣����1

int logout(void); //�ǳ���ʵ���Ͼ��ǰѱ��ص�cookie�ļ���գ�

#endif