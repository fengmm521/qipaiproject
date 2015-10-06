
#ifndef __GLOABLEUTILS__GameMenu__

#define __GLOABLEUTILS__GameMenu__

class GloableUtils {

public:
	/**
	 * 获取系统时间
	 * 参数：
	 * 	int* hour： 小时
	 *	int* minute: 分钟
	 *  int* second: 秒钟
	 */
	static void getTime(int *hour, int* minute, int* second) ;

	/**
	 * 获取系统时间，得到字符串 00:00:00
	 * 返回值：
	 *		char* ：当前系统时间
	 */
	static void getTime(char* nowTime) ;
} ;

#endif