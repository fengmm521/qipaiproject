/********************************************************************************
	File: GamePlayerCenter.h
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-22
	
	该类封装的是玩家信息，包括，头像，等级，拥有金币，下注等信息
	同时负责显示在界面上显示这些信息，靠中间布局

********************************************************************************/
#ifndef __GOLDENFRAUD_GamePlayerCenter__
#define __GOLDENFRAUD_GamePlayerCenter__

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/
#include "GamePlayer.h"


class GamePlayerCenter : public GamePlayer
{
public:

	GamePlayerCenter() {} 
	/**
	*	靠右侧布局的玩家
	*/
	GamePlayerCenter(const char* headPortrait, const char* nikeName, int grade, DWORD godenCoin) ;	

	virtual ~GamePlayerCenter() ;

	/**
	* 初始化方法，从GamePlayer类中继承
	*/
	virtual void initial(void);

	virtual void onEnter(void) ;

	virtual void onExit(void) ;

} ;



#endif