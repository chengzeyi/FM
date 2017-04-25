#include <curl/curl.h>
#include "personal_post.h"
#include "player.h"

int post_hate(char sid[])
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
		url = (char *)malloc(256);
		if (url == NULL)
		{
			exit(1);
		}
		sprintf(url, "https://douban.fm/j/v2/playlist?channel=0&sid=%s&kbps=128&client=s:mainsite|y:3.0&app_name=radio_website&version=100&type=b", sid);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "./tmp/cookie.txt");//提交保存的cookie
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "./tmp/cookie.txt"); //把服务器发过来的cookie保存到cookie_open.txt
		headers = curl_slist_append(headers, "User-Agent:Mozilla/5.0 (Windows NT 6.1; WOW64; rv:25.0) Gecko/20100101 Firefox/25.0");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); //设置请求头
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
			return 1;
		}
		/*清理工作*/
		curl_easy_cleanup(curl);
		curl_slist_free_all(headers);
		free(url);
	}
	return 0;
}

int post_hate_wrapper(void)
{
	int count;

	for (count = 0; count != 5; count++)
	{
		if (post_hate(on_play->sid) == 0)
			break;
	}
	return 0;
}

int post_like(char sid[])
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
		url = (char *)malloc(256);
		if (url == NULL)
		{
			exit(1);
		}
		sprintf(url, "https://douban.fm/j/v2/playlist?channel=0&sid=%s&kbps=128&client=s:mainsite|y:3.0&app_name=radio_website&version=100&type=r", sid);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "./tmp/cookie.txt");//提交保存的cookie
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "./tmp/cookie.txt"); //把服务器发过来的cookie保存到cookie_open.txt
		headers = curl_slist_append(headers, "User-Agent:Mozilla/5.0 (Windows NT 6.1; WOW64; rv:25.0) Gecko/20100101 Firefox/25.0");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); //设置请求头
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
			return 1;
		}
		/*清理工作*/
		curl_easy_cleanup(curl);
		curl_slist_free_all(headers);
		free(url);
	}
	return 0;
}

int post_unlike(char sid[])
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
		url = (char *)malloc(256);
		if (url == NULL)
		{
			exit(1);
		}
		sprintf(url, "https://douban.fm/j/v2/playlist?channel=0&sid=%s&kbps=128&client=s:mainsite|y:3.0&app_name=radio_website&version=100&type=u", sid);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "./tmp/cookie.txt");//提交保存的cookie
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "./tmp/cookie.txt"); //把服务器发过来的cookie保存到cookie_open.txt
		headers = curl_slist_append(headers, "User-Agent:Mozilla/5.0 (Windows NT 6.1; WOW64; rv:25.0) Gecko/20100101 Firefox/25.0");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); //设置请求头
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
			return 1;
		}
		/*清理工作*/
		curl_easy_cleanup(curl);
		curl_slist_free_all(headers);
		free(url);
	}
	return 0;
}

int post_like_unlike(void)
{
	int count;

	if (on_play->like == 0)
	{
		for (count = 0; count != 5; count++)
		{
			if (post_like(on_play->sid) == 0)
				break;
		}
	}
	else
	{
		for (count = 0; count != 5; count++)
		{
			if (post_unlike(on_play->sid) == 0)
				break;
		}
	}
	return 0;
}