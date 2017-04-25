#ifndef LOGIN_OUT
#define LOGIN_OUT

extern char *captcha_id; //验证码ID

extern int status; //连接状态，0表示正常，1表示异常

struct _post_data
{
	int liked;
	int banned;
	int played;
	int is_pro;
	char user_name[128];
}; //结构体保存当前用户信息（目前没什么用）

extern struct _post_data *post_data; //指向结构体的指针

extern size_t write_captcha_id(void *buffer, size_t size, size_t nmemb, void *userp); //回调函数，保存验证码ID

extern size_t write_captcha_pic(void *buffer, size_t size, size_t nmemb, void *userp); //回调函数，保存验证码图片

extern size_t write_request_token(void *buffer, size_t size, size_t nmemb, void *userp); //回调函数，解析用户信息（目前没什么用）

extern size_t write_status(void *buffer, size_t size, size_t nmemb, void *userp); //回调函数，解析用户登录状态并修改status变量

extern int get_captcha_id(void); //获取验证码ID，正常返回0，超时及异常返回1

extern int get_captcha_pic(void); //获取验证码图片，正常返回0，超时及异常返回1

extern int request_token(char email[], char password[], char captcha_solution[], char captcha_id[]); //提交用户登录信息，获取用户信息，正常返回0，超时及异常返回1

extern int login_out_interface(void); //在命令行下显示登录界面，已经在线时跳过登录，否则请求验证码ID及图片，提示用户输入登录信息，显示验证码图片，重复循环直到登录成功，返回0

int login_out_clean(void); //清空captcha_id及post_data，返回0

int get_status(void); //获取用户当前的登录状态，正常返回0，超时及异常返回1

int logout(void); //登出（实际上就是把本地的cookie文件清空）

#endif