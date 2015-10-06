/********************************************************************************
	File: SettingView.cpp
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-25
	
	SettingView 类是一个软件设置界面类，用来设置系统的一些参数
	SettingView 类实现

********************************************************************************/

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/
#include "SettingView.h"
#include "GloableUtils.h"
#include "YJOptionMenuItemImage.h"
#include "GameMenuView.h"


/********************************************************************************
	SettingView 类实现
********************************************************************************/
/**
 * 构造函数
 */
SettingView::SettingView() {	
	
}


/**
 * 析构函数
 */
SettingView::~SettingView() {
}

/**
* 静态方法，创建一个场景，并将自定义的MessageView布景层加入到该场景中
* return  返回创建好的场景对象
*/
CCScene* SettingView::CreateScene() {

	CCScene* scene = CCScene::create() ;
	
	SettingView* settingView = new SettingView() ; // SettingView::create() ;

	if (settingView && settingView->init())
	{
		settingView->init() ;
	}

	settingView->autorelease() ;
	
	scene->addChild(settingView) ;

	return scene ;
}

/**
 * 初始化方法
 */	
bool SettingView::init() {
	if(!CCLayer::init()) {
		return false ;
	}

	// 获取设备屏幕分辨率
	CCSize winSize = CCDirector::sharedDirector()->getWinSize() ;

	
	CCSprite* bg = CCSprite::create("bg_land.png") ; 
	// bg->setPosition(ccp(winSize.width/2, winSize.height/2) );
	bg->setAnchorPoint(ccp(0.5, 0));
	bg->setPosition(ccp(winSize.width/2, 0) );
	this->addChild(bg, 0, 0) ;

		
	// 接收键盘点击事件
	this->setKeypadEnabled(true) ;

	// 开始更新时间,1秒更新一次
	// this->schedule(schedule_selector(SettingView::updateTimeLabel), 1.0f) ;

	return true ;
}

/**
 * 当该layer进入了运行的scene中运行
 */
void SettingView::onEnter() {
	CCLayer::onEnter() ;
	CCLog("SettingView::onEnter") ;
}
 
/**
 * 当该layer离开了scene时调用
 */
void SettingView::onExit() {
	CCLayer::onExit() ;
}
 

/**
 * 处理返回键事件
 */
 void SettingView::keyBackClicked() {
 	// 结束游戏
 	CCDirector::sharedDirector()->replaceScene(GameMenuView::CreateScene()) ;
 }

	/**
 * 存值菜单点击事件处理函数
 */
void SettingView::menuStoreClickCallback(CCObject* pSender) {}

/**
 * 礼包菜单点击事件处理函数
 */
void SettingView::menuGiftsClickCallback(CCObject* pSender) 
{}

/**
 * 返回菜单点击事件处理函数
 */
void SettingView::menuBackClickCallback(CCObject* pSender) 
{
	CCDirector::sharedDirector()->replaceScene(GameMenuView::CreateScene()) ;
}


/**
 * 设置菜单点击事件处理函数
 */
void SettingView::menuSettingClickCallback(CCObject* pSender) {}

/**
 *	底部信息菜单
 */
void SettingView::menuInfoClickCallback(CCObject* pSender) {}


/*
 * 底部任务菜单
 */
void SettingView::menuTaskClickCallback(CCObject* pSender) {}

/**
 * 底部商城菜单
 */
void SettingView::menuShopClickCallback(CCObject* pSender) {}

/**
* 底部活动菜单项
*/
void SettingView::menuActivityClickCallback(CCObject* pSender) {}


/**
 * 更新时间标签里面显示的时间，schedule
 
void SettingView::updateTimeLabel() {
	char nowTime[9] ;
	GloableUtils::getTime(nowTime) ;
	this->timeLabel->setString(nowTime) ;
}
*/

/********************************************************************************
	End of File: SettingView.cpp 
********************************************************************************/