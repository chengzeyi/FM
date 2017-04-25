#ifndef DOWNLOAD
#define DOWNLOAD

extern char *progress_data; //控制台下显示下载进度时的进度数据（暂时没用）

extern size_t write_download_file(void *buffer, size_t size, size_t nmemb, void *userp); //回调函数，保存歌曲

extern size_t write_download_pic(void *buffer, size_t size, size_t nmemb, void *userp); //回调函数，保存歌曲封面图片

extern int download_file(void); //下载playlist中的歌曲，下载成功返回0，超时及异常返回1

extern int download_pic(void); //下载playlist中的歌曲封面图片，下载成功返回0，超时及异常返回1

extern int download_interface(void); //对下载模块的封装，循环请求直到成功，返回0

#endif