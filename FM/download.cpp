#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <curl/curl.h>
#include "playlist.h"
//#pragma comment(lib, "Winmm.lib")

int progress_data;

#ifdef DEBUG
int my_progress_func(int *progress_data, double t, double d, double ultotal, double ulnow)
{
	if (d * 100.0 / t >= *progress_data)
	{
#ifdef DEBUG
		printf("%d percent\n", *progress_data);
#endif
		*progress_data += 10;
	}
	return 0;
}
#endif

size_t write_download_file(void *buffer, size_t size, size_t nmemb, void *userp)
{
	char route[256] = "./tmp/";
	strcat(route, playlist->file_name);
	FILE *fp = fopen(route, "ab+");
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

size_t write_download_pic(void *buffer, size_t size, size_t nmemb, void *userp)
{
	char route[256] = "./tmp/";
	strcat(route, playlist->pic_name);
	FILE *fp = fopen(route, "ab+");
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

int download_file(void)
{
	char url[256];
	strcpy(url, playlist->song_url);
	char route[256] = "./tmp/";
	strcat(route, playlist->file_name);
	if(!_access(route, 0)) //如果已经下载过了就不再下载
	{
#ifdef DEBUG
		printf("file already exists!\n");
#endif
		return 0;
	}
#ifdef DEBUG
	printf("start to download file!\n");
#endif
	CURL *curl;
	CURLcode res;
	struct curl_slist *headers = NULL;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "./tmp/cookie.txt");//提交保存的cookie
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "./tmp/cookie.txt"); //把服务器发过来的cookie保存到cookie_open.txt
		headers = curl_slist_append(headers, "User-Agent:Mozilla/5.0 (Windows NT 6.1; WOW64; rv:25.0) Gecko/20100101 Firefox/25.0");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); //设置请求头
		/*设置回调函数*/
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_download_file);
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
		/*设置显示进度*/
#ifdef DEBUG
		progress_data = 10;
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, FALSE);
		curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, my_progress_func);
		curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, &progress_data);
#endif
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5);//连接超时设置
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

int download_pic(void)
{
	char url[256];
	strcpy(url, playlist->picture_url);
	char route[256] = "./tmp/";
	strcat(route, playlist->pic_name);
	if (!_access(route, 0)) //如果已经下载过了就不再下载
	{
#ifdef DEBUG
		printf("file already exists!\n");
#endif
		return 0;
	}
#ifdef DEBUG
	printf("start to download file!\n");
#endif
	CURL *curl;
	CURLcode res;
	struct curl_slist *headers = NULL;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "./tmp/cookie.txt");//提交保存的cookie
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "./tmp/cookie.txt"); //把服务器发过来的cookie保存到cookie_open.txt
		headers = curl_slist_append(headers, "User-Agent:Mozilla/5.0 (Windows NT 6.1; WOW64; rv:25.0) Gecko/20100101 Firefox/25.0");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); //设置请求头
															 /*设置回调函数*/
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_download_pic);
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
		/*设置显示进度*/
#ifdef DEBUG
		progress_data = 10;
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, FALSE);
		curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, my_progress_func);
		curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, &progress_data);
#endif
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);
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

int download_interface(void)
{
	while(download_file() != 0)
		continue;
	while (download_pic() != 0)
		continue;
	return 0;
}