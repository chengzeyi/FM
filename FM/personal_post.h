#ifndef PERSONAL_POST
#define PERSONAL_POST
#define LIKE 1
#define UNLIKE 2

extern int post_hate(char sid[]); //�ύ��ban������������0����ʱ���쳣����1

extern int post_hate_wrapper(void); //�ύ��ban����������5�γ��ԣ�������0

extern int post_like(char sid[]); //�ύ��ϲ��������������0����ʱ���쳣����1

extern int post_unlike(char sid[]); //�ύ��ȡ��ϲ��������������0����ʱ���쳣����1

extern int post_like_unlike(); //����on_play->like��ֵ�ж�Ҫ���к����ύ�������ύ��������5�γ��ԣ�������0

#endif