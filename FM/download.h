#ifndef DOWNLOAD
#define DOWNLOAD

extern char *progress_data; //����̨����ʾ���ؽ���ʱ�Ľ������ݣ���ʱû�ã�

extern size_t write_download_file(void *buffer, size_t size, size_t nmemb, void *userp); //�ص��������������

extern size_t write_download_pic(void *buffer, size_t size, size_t nmemb, void *userp); //�ص������������������ͼƬ

extern int download_file(void); //����playlist�еĸ��������سɹ�����0����ʱ���쳣����1

extern int download_pic(void); //����playlist�еĸ�������ͼƬ�����سɹ�����0����ʱ���쳣����1

extern int download_interface(void); //������ģ��ķ�װ��ѭ������ֱ���ɹ�������0

#endif