/********************************************************************************
	File: WelcomeView.h
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-30
	
	WelcomeView 类是一个欢迎界面类，用来过度

********************************************************************************/
#ifndef __GOLDENFRAUD_WelcomeView_
#define __GOLDENFRAUD_WelcomeView_

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/
#include "cocos2d.h"

/********************************************************************************
	宏定义
********************************************************************************/
#define TAG_LABELNODE			2 	// label
#define TAG_LOADING_PERCENTAGE 	5	// 加载进度

/********************************************************************************
	using namespace
********************************************************************************/
USING_NS_CC ;


/********************************************************************************
	WelcomeView 类定义
********************************************************************************/

class WelcomeView : public CCLayer 
{
public:
	/**
	*	构造函数
	*/
	WelcomeView() ;

	/**
	*	析造函数
	*/
	~WelcomeView() ;

	/**
	*	创建该界面依赖的场景对象
	*/
	static CCScene* CreateScene() ;

	/**
	*	初始化方法，继承CCLayer的方法
	*/
	virtual bool init() ;
	
	virtual void onEnter() ;

	/**
	 * 处理返回键事件
	 */
	virtual void keyBackClicked() ;

//////// 回调函数 //////////////////////////////////////////////////////////
public:
	/**
	*	第一进度回调
	*/
	void firstProgressCallBack() ;

	/**
	*	第二进度回调
	*/
	void secondProgressCallBack() ;

	/**
	*	第三进度回调
	*/
	void thirdProgressCallBack() ;


	CREATE_FUNC(WelcomeView);
	
private:
	CCProgressTimer* progressBar ;
} ;

#endif