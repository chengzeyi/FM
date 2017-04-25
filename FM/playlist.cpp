#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "cJSON.h"
#include "playlist.h"

int channel = 0;

struct _playlist *playlist;

size_t write_playlist(void *buffer, size_t size, size_t nmemb, void *userp)
{
	/*
	调用cJSON解析get_playlist的response
	for example:
	{
	"warning":"user_is_ananymous",
	"r":0,
	"version_max":100,
	"is_show_quick_start":0,
	"song":
	[{
	"albumtitle":"你当我什么",
	"url":"http:\/\/mr1.doubanio.com\/fe2b6cef41cd9a4acc6fff1acc06e29b\/0\/fm\/song\/p82943_128k.mp4",
	"file_ext":"mp4",
	"album":"\/subject\/2340769\/",
	"ssid":"56e3",
	"title":"大小姐",
	"sid":"82943",
	"sha256":"6e9e76e87b7ad6d01a142cc8439d3bdc87d26d33a85dad7d67cd0ca7168e4b5b",
	"status":0,
	"picture":"https://img3.doubanio.com\/lpic\/s2799400.jpg",
	"update_time":1470125637,
	"alert_msg":"",
	"public_time":"2007",
	"singers":
	[{
	"style":[],
	"name":"关楚耀",
	"region":["香港"],
	"name_usual":"关楚耀",
	"genre":["Pop"],
	"avatar":"https://img1.doubanio.com\/img\/fmadmin\/large\/32118.jpg",
	"related_site_id":0,
	"is_site_artist":false,"id":"15954"
	}],
	"like":0,
	"artist":"关楚耀",
	"is_royal":false,
	"subtype":"",
	"length":179,
	"release":
	{
	"link":"https:\/\/douban.fm\/album\/2340769g1246","id":"2340769",
	"ssid":"1246"
	},
	"aid":"2340769",
	"kbps":"128",
	"available_formats":
	{
	"64":1424,
	"192":4204,
	"128":2800
	}
	}]
	}
	*/
	if (playlist == NULL)
		playlist = (struct _playlist *)malloc(sizeof(struct _playlist));
	if (playlist == NULL)
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
		printf("response of get_playlist has keyword 'r' valued 1!\n");
#endif
		return size * nmemb;
	}
	/*这里出现了一个数组*/
	cJSON *song = cJSON_GetObjectItem(root, "song");
	song = song->child;
	strcpy(playlist->albumtitle, cJSON_GetObjectItem(song, "albumtitle")->valuestring);
	strcpy(playlist->song_url, cJSON_GetObjectItem(song, "url")->valuestring); 
	strcpy(playlist->file_ext, cJSON_GetObjectItem(song, "file_ext")->valuestring);
	strcpy(playlist->title, cJSON_GetObjectItem(song, "title")->valuestring);
	strcpy(playlist->picture_url, cJSON_GetObjectItem(song, "picture")->valuestring);
	strcpy(playlist->artist, cJSON_GetObjectItem(song, "artist")->valuestring);
	strcpy(playlist->sid, cJSON_GetObjectItem(song, "sid")->valuestring);
	strcpy(playlist->file_name, playlist->sid);
	strcat(playlist->file_name, ".mp3");
	strcpy(playlist->pic_name, playlist->sid);
	strcat(playlist->pic_name, ".jpg");
	playlist->like = cJSON_GetObjectItem(song, "like")->valueint;
#ifdef DEBUG
	printf("parse response of get_playlist successfully!\nalbumtitle: %s\nsong_url: %s\nfile_ext: %s\ntitle: %s\npicture_url: %s\nartist: %s\nsid: %s\nfile_name: %s\n", playlist->albumtitle, playlist->song_url, playlist->file_ext, playlist->title, playlist->picture_url, playlist->artist, playlist->sid, playlist->file_name);
#endif
	/*清理工作*/
	cJSON_Delete(root);
	return size * nmemb;
}

int get_playlist(int channel)
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
#ifdef DEBUG
			printf("memory out of space!\n");
			system("PAUSE");
#endif
			exit(1);
		}
		sprintf(url, "https://douban.fm/j/v2/playlist?channel=%d&kbps=128&client=s:mainsite|y:3.0&app_name=radio_website&version=100&type=n", channel);
#ifdef DEBUG
		printf("get_playlist_url: %s\n", url);
#endif
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "./tmp/cookie.txt");//提交保存的cookie
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "./tmp/cookie.txt"); //把服务器发过来的cookie保存到cookie_open.txt
		headers = curl_slist_append(headers, "User-Agent:Mozilla/5.0 (Windows NT 6.1; WOW64; rv:25.0) Gecko/20100101 Firefox/25.0");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); //设置请求头
		/*设置回调函数*/
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_playlist);
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

int playlist_interface(void)
{
	while(get_playlist(channel) != 0)
		continue;
	return 0;
}