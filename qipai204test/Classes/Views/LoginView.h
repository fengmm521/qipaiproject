/********************************************************************************
	File: LoginView.h
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-30
	
	LoginView 类是一个用户登录界面类，用户可以输入用户名和密码进行登录

********************************************************************************/
#ifndef __GOLDENFRAUD_LoginView_
#define __GOLDENFRAUD_LoginView_

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/
#include "cocos2d.h"


/********************************************************************************
	using namespace
********************************************************************************/
USING_NS_CC ;

/********************************************************************************
	LoginView 类定义
********************************************************************************/

class LoginView : public CCLayer,  public CCIMEDelegate
{
public:
	/**
	*	构造函数
	*/
	LoginView() ;

	/**
	*	析造函数
	*/
	~LoginView() ;

	/**
	*	创建该界面依赖的场景对象
	*/
	static CCScene* CreateScene() ;

	/**
	*	初始化方法，继承CCLayer的方法
	*/
	virtual bool init() ;

	/**
	 * 处理返回键事件
	 */
	virtual void keyBackClicked() ;

	virtual void onEnter() ;

	virtual void onExit() ;

	/**
	* 	如果触摸事件是开启的，那么这个方法会在onEnter中调用（If isTouchEnabled, this method is called onEnter.）
	*	Override it to change the way CCLayer receives touch events. 
	*	( Default: CCTouchDispatcher::sharedDispatcher()->addStandardDelegate(this,0); ) 
	*	Example: void CCLayer::registerWithTouchDispatcher() { CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,INT_MIN+1,true); }
	*/
	virtual void registerWithTouchDispatcher();
	/*
	*	CCIMEDelegate代理中的一个方法，在键盘即将出现的时候调用
	*/
    virtual void keyboardWillShow(CCIMEKeyboardNotificationInfo& info);

    // CCLayer ，触摸开始
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) ;
    // 触摸结束
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) ;

    /**
    *	被处理的Node是否被点击了
    *	@param bClicked true表示被点击了；否者没有被点击
    */
    void onClickTrackNode(CCTextFieldTTF* txt, bool bClicked);

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

	/**
	*	登录菜单项的点击事件
	*/
	void menuLoginCallback(CCObject* pSender) ;

	/**
	*   注册菜单项的点击事件
	*/
	void menuRegisteCallback(CCObject* pSender) ;

	/**
	*   游客登录菜单项的点击事件
	*/
	void menuGuestLoginCallback(CCObject* pSender) ;

	/**
	* 忘记密码菜单项点击事件
	*/
	void menuForgetPwdCallback(CCObject* pSender) ;

	/**
	*	Go菜单项的点击事件
	*/
	void menuGoCallback(CCObject* pSender) ;

	CREATE_FUNC(LoginView);

private:
	CCTextFieldTTF*    txtUsername ;
	CCTextFieldTTF*    txtPassword ;

	CCArray * mTrackNodeArray ; 	// 处理的节点
    CCPoint  mBeginPos ;	//	开始坐标
} ;

#endif