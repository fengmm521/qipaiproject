/********************************************************************************
	File: Cards.h
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-29
	
	该类封装的是扑克牌信息，定义Cards类，和大牌类CardsLarge和小牌类CardsSmall

********************************************************************************/
#ifndef __GOLDENFRAUD_Cards__
#define __GOLDENFRAUD_Gards__

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
// 大牌
#define LARGE_CARD_BACK "card/card_back.png"
#define LARGE_CARD_WIDTH 67
#define LARGE_CARD_HEIGHT 87


/********************************************************************************
	Cards类定义
********************************************************************************/

class Cards : public CCNode 
{
public:
	// 构造函数
	Cards() ;

	// 析构函数
	virtual ~Cards() ;	

	// 比牌结束后，显示牌面内容
	virtual void showCard(void) ;

	// 看牌，在显示牌的位置显示看的图标
	void lookCard(void) ;

	// 移动扑克牌，这个是在发牌的时候进行调用
	void provide(int i) ;

	// 隐藏所有的牌
	void hideAllCard(void) ;

protected:
	/**
	*	要在界面上显示的扑克牌， 默认是背面
	*/
	CCSprite* cardIcons[3] ;

	/**
	* 	看牌图标
	*/
	CCSprite* lookIcon ;

	// 初始化方法
	virtual void init() ;
} ;

/********************************************************************************
	CardsLarge大牌类定义
********************************************************************************/
class CardsLarge : public Cards
{
public:
	// 构造函数
	CardsLarge() ;

	// 析构函数
	virtual ~CardsLarge() ;

	// 比牌结束后，显示牌面内容
	virtual void showCard(void) ;
protected:
	// 初始化方法
	virtual void init() ;

};

/********************************************************************************
	CardsSmall小牌类定义
********************************************************************************/
/*
class CardsSmall : public Cards
{
	public:
	// 构造函数
	CardsSmall() ;

	// 析构函数
	virtual ~CardsSmall() ;

	// 移动扑克牌，这个是在发牌的时候进行调用
	virtual void provide(int i) ;

	// 比牌结束后，显示牌面内容
	virtual void showCard(void) ;

protected:
	// 初始化方法
	virtual void init() ;
};
*/

#endif