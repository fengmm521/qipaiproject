/********************************************************************************
	File: Jeton.h
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-29
	
	筹码信息类

********************************************************************************/
#ifndef __GOLDENFRAUD_Jeton__
#define __GOLDENFRAUD_Jeton__

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/

#include "cocos2d.h"
#include "DataType.h"
#include "GloableMacro.h"

/********************************************************************************
	using namepace
********************************************************************************/

USING_NS_CC ;

/********************************************************************************
	宏定义
********************************************************************************/

/********************************************************************************
	Jeton类定义
********************************************************************************/
class Jeton : public CCObject
{
public:

	/**
	*	获取筹码显示组件
	*	@param playerIndex 玩家索引
	*	@param val 筹码的面值
	*/
	static CCSprite* getJeton(int playerIndex, DWORD val) ;

	
} ;


#endif