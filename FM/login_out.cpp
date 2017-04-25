#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <curl/curl.h>
#include "login_out.h"
#include "cJSON.h"
#include "gui.h"

char *captcha_id; //验证码ID

int status = 1; //连接状态，0表示正常，1表示异常

struct _post_data *post_data;

size_t write_captcha_id(void *buffer, size_t size, size_t nmemb, void *userp) 
{
	captcha_id = (char *)malloc(size * nmemb-1);
	if (captcha_id == NULL)
	{
#ifdef DEBUG
		printf("memory out of space!\n");
		system("PAUSE");
#endif
		exit(1);
	}
	captcha_id = (char *)memcpy(captcha_id, (char *)buffer + 1, size * nmemb-2);
	captcha_id[size * nmemb - 2] = '\0';
#ifdef DEBUG
	printf("captcha_id: %s\n", captcha_id);
#endif
	return size * nmemb;
}

size_t write_captcha_pic(void *buffer, size_t size, size_t nmemb, void *userp)
{
	FILE *fp = fopen("./tmp/captcha_pic.jpg", "wb");
	if (fp == NULL)
	{
#ifdef DEBUG
		printf("failed to open file!\n");
#endif
		return size * nmemb;
	}
	size_t nWrite = fwrite(buffer, size, nmemb, fp);
	fclose(fp);
	return nWrite;
}

size_t write_request_token(void *buffer, size_t size, size_t nmemb, void *userp)
{
	/*
	调用cJSON解析login_post的response
	for example:
	{"user_info":{"ck":"RqP9","play_record":{"fav_chls_count":1,"liked":17,"banned":7,"played":2602},"is_new_user":0,"uid":"48685375","third_party_info":null,"url":"https:\/\/www.douban.com\/people\/48685375\/","is_dj":false,"id":"48685375","is_pro":false,"name":"潜行者"},"r":0}
	*/
	if(post_data == NULL)
		post_data = (struct _post_data *)malloc(sizeof(struct _post_data));
	if (post_data == NULL)
	{
#ifdef DEBUG
		printf("memory out of space!\n");
		system("PAUSE");
#endif
		exit(1);
	}
	cJSON *root = cJSON_Parse((char *)buffer);
	if (cJSON_GetObjectItem(root, "r")->valueint != 0)
	{
#ifdef DEBUG
		printf("response of login_post has keyword 'r' valued 1!\n");
#endif
		status = 1;
		return size * nmemb;
	}
	cJSON *user_info = cJSON_GetObjectItem(root, "user_info");
	post_data->is_pro = cJSON_GetObjectItem(user_info, "is_pro")->valueint;
	strcpy(post_data->user_name, cJSON_GetObjectItem(user_info, "name")->valuestring);
	cJSON *play_record = cJSON_GetObjectItem(user_info, "play_record");
	post_data->liked = cJSON_GetObjectItem(play_record, "liked")->valueint;
	post_data->banned = cJSON_GetObjectItem(play_record, "banned")->valueint;
	post_data->played = cJSON_GetObjectItem(play_record, "played")->valueint;
#ifdef DEBUG
	printf("parse response of login_post successfully!\nis_pro: %d\tuser_name: %s\nliked: %d\tbanned: %d\nplayed: %d\n", post_data->is_pro, post_data->user_name, post_data->liked, post_data->banned, post_data->played);
#endif
	/*清理工作*/
	cJSON_Delete(root);
	status = 0;
	return size * nmemb;
}

size_t write_status(void *buffer, size_t size, size_t nmemb, void *userp)
{
	/*
	调用cJSON解析response
	for example:
	{"song":[{"status":0,"picture":"https://img3.doubanio.com\/f\/fm\/ee35f1c5b60b81047cf82cd7289b2f668a03f9fc\/pics\/fm\/landingpage\/qr@2x.png","artist":"豆瓣FM https:\/\/douban.fm","ver":0,"alert_msg":"","sha256":"61832d23a8ed139b21e03ff1c73396ebe990e4e30f0c70dc88c8cfd1aca385a1","albumtitle":"豆瓣FM","promo":{},"title":"API已升级, 请下载豆瓣FM App继续收听。感谢理解。","ssid":"5bf5","length":309,"url":"http:\/\/mr7.doubanio.com\/9b0f67501f975dfbcec7c815c81b0c22\/0\/fm\/song\/p1831618_128k.mp4","subtype":"S","singers":[],"aid":"131100","file_ext":"mp4","album":"https:\/\/douban.fm\/","kbps":"128","sid":"1831618","like":0}],"is_show_quick_start":0,"r":0,"version_max":102,"logout":1,"warning":"user_is_ananymous"}
	*/
	cJSON *root = cJSON_Parse((char *)buffer);
	if (cJSON_GetObjectItem(root, "r")->valueint == 1)
	{
#ifdef DEBUG
		printf("response of get_status has keyword 'r' valued 1!\n");
#endif
		status = 1;
		return size * nmemb;
	}
	else
	{
#ifdef DEBUG
		printf("response of get_status has keyword 'r' valued 0!\n");
#endif
		status = 0;
		return size * nmemb;
	}
}

int get_captcha_id(void)
{
	CURL *curl;
	CURLcode res;
	struct curl_slist *headers = NULL;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "https://douban.fm/j/new_captcha");
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "./tmp/cookie.txt"); //把服务器发过来的cookie保存到cookie.txt
		headers = curl_slist_append(headers, "User-Agent:Mozilla/5.0 (Windows NT 6.1; WOW64; rv:25.0) Gecko/20100101 Firefox/25.0");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); //设置请求头
		/*设置回调函数*/
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_captcha_id);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, 0);
		/*设置是否打印数据*/
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
		/*设置是否进行SSL验证*/
#ifdef SKIP_PEER_VERIFICATION  
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif  
#ifdef SKIP_HOSTNAME_VERFICATION  
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10); 
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);//连接超时设置
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
#ifdef DEBUG
			printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
#endif
			return 1;
		}
		/*清理工作*/
		curl_easy_cleanup(curl);
		curl_slist_free_all(headers);
	}
	return 0;
}

int get_captcha_pic(void)
{
	char *url;
	CURL *curl;
	CURLcode res;
	struct curl_slist *headers = NULL;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (curl)
	{
		/*格式化url*/
		url = (char *)malloc(sizeof("https://www.douban.com/misc/captcha?id=CUpLQmKt9dGsJC9q4XoY76HN:en&size=s"));
		if (url == NULL)
		{
#ifdef DEBUG
			printf("memory out of space!\n");
			system("PAUSE");
#endif
			exit(1);
		}
		sprintf(url, "https://www.douban.com/misc/captcha?id=%s&size=s", captcha_id);
#ifdef DEBUG
		printf("captcha_pic_url: %s\n", url);
#endif

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "./tmp/cookie.txt");//提交第一步保存的cookie
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "./tmp/cookie.txt"); //把服务器发过来的cookie保存到cookie_open.txt
		headers = curl_slist_append(headers, "User-Agent:Mozilla/5.0 (Windows NT 6.1; WOW64; rv:25.0) Gecko/20100101 Firefox/25.0");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); //设置请求头
		/*设置回调函数*/
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_captcha_pic);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, 0);
		/*设置是否打印数据*/
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
		/*设置是否进行SSL验证*/
#ifdef SKIP_PEER_VERIFICATION  
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif  
#ifdef SKIP_HOSTNAME_VERFICATION  
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);//连接超时设置
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
#ifdef DEBUG
			printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
#endif
			return 1;
		}
		/*清理工作*/
		curl_easy_cleanup(curl);
		curl_slist_free_all(headers);
		free(url);
	}
	return 0;
}

int request_token(char email[], char password[], char captcha_solution[], char captcha_id[])
{
	char *data;
	CURL *curl;
	CURLcode res;
	struct curl_slist *headers = NULL;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (curl)
	{
		/*构造post参数*/
		char *data = (char *)malloc(256);
		if (data == NULL)
		{
#ifdef DEBUG
			printf("memory out of space!\n");
			system("PAUSE");
#endif
			exit(1);
		}
		sprintf(data, "source=radio&alias=%s&form_password=%s&captcha_solution=%s&captcha_id=%s&task=sync_channel_list", email, password, captcha_solution, captcha_id);
#ifdef  DEBUG
		printf("login_post: %s\n", data);
#endif
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data); //启用post
		curl_easy_setopt(curl, CURLOPT_URL, "https://douban.fm/j/login");
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "./tmp/cookie.txt");//提交第一步保存的cookie
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "./tmp/cookie.txt"); //把服务器发过来的cookie保存到cookie.txt
		headers = curl_slist_append(headers, "User-Agent:Mozilla/5.0 (Windows NT 6.1; WOW64; rv:25.0) Gecko/20100101 Firefox/25.0");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); //设置请求头
		/*设置回调函数*/
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_request_token);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, 0);
		/*设置是否打印数据*/
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
		/*设置是否进行SSL验证*/
#ifdef SKIP_PEER_VERIFICATION  
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif  
#ifdef SKIP_HOSTNAME_VERFICATION  
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);//连接超时设置
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
#ifdef DEBUG
			printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
#endif
			return 1;
		}
		/*清理工作*/
		curl_easy_cleanup(curl);
		curl_slist_free_all(headers);
		free(data);
	}
	return 0;
}

int login_out_clean(void)
{
	free(captcha_id);
	free(post_data);
	captcha_id = NULL;
	post_data = NULL;

	return 0;
}

int get_status(void)
{
	CURL *curl;
	CURLcode res;
	struct curl_slist *headers = NULL;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "https://douban.fm/j/check_loggedin?san=1");
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "./tmp/cookie.txt");//提交保存的cookie
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "./tmp/cookie.txt"); //把服务器发过来的cookie保存到cookie.txt
		headers = curl_slist_append(headers, "User-Agent:Mozilla/5.0 (Windows NT 6.1; WOW64; rv:25.0) Gecko/20100101 Firefox/25.0");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); //设置请求头
		/*设置回调函数*/
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_status);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, 0);
		/*设置是否打印数据*/
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
		/*设置是否进行SSL验证*/
#ifdef SKIP_PEER_VERIFICATION  
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif  
#ifdef SKIP_HOSTNAME_VERFICATION  
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);//连接超时设置
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
#ifdef DEBUG
			printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
#endif
			return 1;
		}
		/*清理工作*/
		curl_easy_cleanup(curl);
		curl_slist_free_all(headers);
	}
	return 0;
}

int logout(void)
{
	FILE *fp;

	if ((fp = fopen("./tmp/cookie.txt", "w+")) == NULL)
		return 1;
	else
	{
		fclose(fp);
		return 0;
	}
}

int login_out_interface(void)
{
	char email[32], password[32], captcha_solution[16];

	/*判断tmp文件夹是否存在，若不存在则创建*/
	if (_access("./tmp", 0) == -1)
	{
		system("mkdir tmp");
	}
	printf("FM application based on douban FM API\nprogrammed by Cheng Zeyi ( chengzeyi.github.io )\nconnecting...\n");
	while(get_status() != 0)
		continue;
	if (status == 0)
	{
		printf("already logged in!\n");
		return 0;
	}
	while (1)
	{
		printf("user currently not online!\n");
		while (get_captcha_id() != 0)
			continue;
		while(get_captcha_pic() != 0)
			continue;
		printf("enter email: ");
		scanf_s("%s", email, 32);
		printf("enter password: ");
		scanf_s("%s", password, 32);
		gui_captcha_pic();
		printf("enter captcha_solution: ");
		scanf_s("%s", captcha_solution, 16);
		gui_captcha_pic_close();
		printf("logging...\n");
		while(request_token(email, password, captcha_solution, captcha_id) != 0)
			continue;
		if (status == 0)
			break;
		printf("failed to login!\n");
		login_out_clean();
	}

	return 0;
}