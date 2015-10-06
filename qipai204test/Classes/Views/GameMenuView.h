/********************************************************************************
	File: GameMenuView.h
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-30
	
	GameMenuView 类是游戏选项菜单界面类

********************************************************************************/

#ifndef __GOLDENFRAUD__GameMenuView__
#define __GOLDENFRAUD__GameMenuView__

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/

#include "cocos2d.h"


/********************************************************************************
	using namespace
********************************************************************************/
using namespace cocos2d ;


/********************************************************************************
	GameMenuView 类定义
********************************************************************************/
/**
 * 定义游戏菜单类
 */
class GameMenuView : public cocos2d::CCLayer {
public:
	/**
	 * 构造函数
	 */
	GameMenuView() ;

	/**
	 * 析构函数
	 */
	~GameMenuView() ;

	/******************************************************************************/
	/* CCScene* scene()                                                      	  */
	/* 创建一个场景，并将布景层加入到该场景中									  */
	/* return  返回创建好的场景对象                                               */
	/******************************************************************************/
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




// 菜单项点击事件
	/**
	 * 存值菜单点击事件处理函数
	 */
	void menuMoneyTreeClickCallback(CCObject* pSender) ;

	
	/**
	 * 礼包菜单点击事件处理函数
	 */
	void menuGiftsClickCallback(CCObject* pSender) ;

	/**
	 * 帮助菜单点击事件处理函数
	 */
	void menuHelpClickCallback(CCObject* pSender) ;

	/**
	 * 设置菜单点击事件处理函数
	 */
	void menuSettingClickCallback(CCObject* pSender) ;

	/**
	 * 中级场
	 */
	void menuMiddleClickCallback(CCObject* pSender) ;

	/**
	 * 初级场
	 */
	void menuJuniorClickCallback(CCObject* pSender) ;

	/**
	 * 高级场
	 */
	void menuSeniorClickCallback(CCObject* pSender) ;

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
	* 底部菜单菜单项
	*/
	void menuMoreClickCallback(CCObject* pSender) ;

	
	/**
	* 更多 排行榜菜单项
	*/
	void menuRankingClickCallback(CCObject* pSender) ;

	/**
	 * 好友菜单点击事件处理函数
	 */
	void menuFriendClickCallback(CCObject* pSender) ;

	/**
	 * 客服菜单点击事件处理函数
	 */
	void menuCustomServiceClickCallback(CCObject* pSender) ;

	/**
	 * 更新时间标签里面显示的时间，schedule
	 */
	void updateTimeLabel() ;

private:

	// 初始化顶部bar
	void initTopBar(CCSize winSize) ;

	// 初始化中间部分bar
	void initCenterBar(CCSize winSize) ;

	// 初始化底部Bar
	void initBottomBar(CCSize winSize) ;

	CREATE_FUNC(GameMenuView);

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
	 * 摇钱树、在线人数和联系客服
	 */
	CCNode* onLineNode ;

	/**
	 * 底部条
	 */
	CCNode* footerBarNode ;

	/**
	 * 时间显示标签
	 */
	CCLabelTTF* timeLabel ;

	/**
	* 	更多菜单
	*/
	CCNode* moreMenuNode ;

	/**
	*	是否显示更多菜单，默认为false
	*/
	bool moreMenuShow  ;
}; 

#endif