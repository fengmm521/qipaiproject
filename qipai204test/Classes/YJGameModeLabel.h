/********************************************************************************
	File: YJGameModeLabel.h
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-30
	
	YJGameModeLabel 类是游戏模式上的限制信息，例如：进入限制和底注限制

********************************************************************************/

#ifndef __GOLDENFRAUD__YJGameModeLabel__
#define __GOLDENFRAUD__YJGameModeLabel__

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/
#include "cocos2d.h"


/********************************************************************************
	using namespace
********************************************************************************/
USING_NS_CC ;


/********************************************************************************
	WelcomeView 类定义
********************************************************************************/

class YJGameModeLabel : public CCNode 
{
public:
	/**
	*	构造函数
	*	@param	enterLimit 	进入限制
	*	@param	baseBet		底注
	*/
	YJGameModeLabel(int enterLimit, int baseBet) ;

	/**
	*	构造函数
	*	@param	enterLimit 	进入限制
	*	@param	baseBet		底注
	*/
	YJGameModeLabel(const char* enterLimit, const char*  baseBet) ;

	/*
	*	析构函数
	*/
	~YJGameModeLabel() ;

	/**
	*	初始化函数
	*	@param	enterLimit 	进入限制
	*	@param	baseBet		底注
	*/
	void init(int enterLimit, int baseBet) ;

	/**
	*	初始化函数
	*	@param	enterLimit 	进入限制
	*	@param	baseBet		底注
	*/
	void init(const char* enterLimit, const char* baseBet) ;

};


#endif

/********************************************************************************
	End of File: YJGameModeLabel.h  
********************************************************************************/