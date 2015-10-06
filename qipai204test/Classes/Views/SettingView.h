/********************************************************************************
	File: SettingView.h
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-25
	
	SettingView 类是一个软件设置界面类，用来设置系统的一些参数

********************************************************************************/
#ifndef __GOLDENFRAUD__SettingView__
#define __GOLDENFRAUD__SettingView__

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/

#include "cocos2d.h"

/********************************************************************************
	using namespace
********************************************************************************/
using namespace cocos2d ;


/********************************************************************************
	SettingView 类定义
********************************************************************************/
class SettingView : public cocos2d::CCLayer {
public:
	/**
	 * 构造函数
	 */
	SettingView() ;

	/**
	 * 析构函数
	 */
	~SettingView() ;

	/**
	* 创建一个场景，并将布景层加入到该场景中
	* return  返回创建好的场景对象
	*/
	static CCScene* CreateScene() ;

	/**
	 * 初始化方法
	 */	
	virtual bool init() ;


	/**
	 * 当该layer进入了运行的scene中运行
	 */
	virtual void onEnter() ;

	/**
	 * 当该layer离开了scene时调用
	 */
	virtual void onExit() ;

	/**
	 * 处理返回键事件
	 */
	virtual void keyBackClicked() ;


// 属性定义

	/**
	 * 顶部条
	 */
	CCNode* topBarNode ;

	 /**
	  *	喇叭信息以及系统信息显示框
	  */
	CCNode* infoTipNode ;

	/**
	 * 游戏模式选择框
	 */
	CCNode* modeSelectNode ;


	/**
	 * 底部条
	 */
	CCNode* footerBarNode ;

	/**
	 * 时间显示标签
	 
	CCLabelTTF* timeLabel ;
	*/

// 菜单项点击事件
	/**
	 * 存值菜单点击事件处理函数
	 */
	void menuStoreClickCallback(CCObject* pSender) ;

	
	/**
	 * 礼包菜单点击事件处理函数
	 */
	void menuGiftsClickCallback(CCObject* pSender) ;

	/**
	 * 返回菜单点击事件处理函数
	 */
	void menuBackClickCallback(CCObject* pSender) ;


	/**
	 * 设置菜单点击事件处理函数
	 */
	void menuSettingClickCallback(CCObject* pSender) ;

	/**
	 *	底部信息菜单
	 */
	void menuInfoClickCallback(CCObject* pSender) ;

	/*
	 * 底部任务菜单
	 */
	void menuTaskClickCallback(CCObject* pSender) ;

	/**
	 * 底部商城菜单
	 */
	void menuShopClickCallback(CCObject* pSender) ;

	/**
	* 底部活动菜单项
	*/
	void menuActivityClickCallback(CCObject* pSender) ;

	/**
	 * 更新时间标签里面显示的时间，schedule
	
	void updateTimeLabel() ;
	 */

	CREATE_FUNC(SettingView);
}; 

#endif
/********************************************************************************
	End of File: SettingView.h
********************************************************************************/