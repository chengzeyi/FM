#ifndef PERSONAL_POST
#define PERSONAL_POST
#define LIKE 1
#define UNLIKE 2

extern int post_hate(char sid[]); //提交“ban”，正常返回0，超时及异常返回1

extern int post_hate_wrapper(void); //提交“ban”（最多进行5次尝试），返回0

extern int post_like(char sid[]); //提交“喜欢”，正常返回0，超时及异常返回1

extern int post_unlike(char sid[]); //提交“取消喜欢”，正常返回0，超时及异常返回1

extern int post_like_unlike(); //根据on_play->like的值判断要进行何种提交，进行提交（最多进行5次尝试），返回0

#endif