#include "GloableUtils.h"
#include "cocos2d.h"

USING_NS_CC ;

/**
 * 获取系统时间
 * 参数：
 * 	int* hour： 小时
 *	int* minute: 分钟
 *  int* second: 秒钟
 */
void GloableUtils::getTime(int *hour, int* minute, int* second) {
	struct cc_timeval now;  // 秒，毫秒
	CCTime::gettimeofdayCocos2d(&now, NULL);
	struct tm* tm;

	tm = localtime(&now.tv_sec);
	// int year = tm->tm_year + 1900; // 年
	// int month = tm->tm_mon + 1; // 月
	// int day = tm->tm_mday; // 日
	*hour = tm->tm_hour ;
    *minute = tm->tm_min ;
    *second = tm->tm_sec ;

    return ;
}

/**
 * 获取系统时间，得到字符串 00:00:00
 * 返回值：
 *		char* ：当前系统时间
 */
void GloableUtils::getTime(char* nowTime) {
	int hour, minute, second ;
	// 获取时间
	getTime(&hour, &minute, &second) ;

	sprintf(nowTime, "%02d:%02d:%02d", hour, minute, second) ;
}