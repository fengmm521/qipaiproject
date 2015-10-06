/********************************************************************************
	File: HelpView.cpp
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-25
	
	HelpView 类是一个帮助信息界面类，用来显示帮助信息内容
	HelpView 实现

********************************************************************************/

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/
#include "HelpView.h"

#include "GameMenuView.h"
#include "MessageView.h"
#include "TaskView.h"
#include "ActivityView.h"
#include "ShopView.h"
#include "YJTabTitle.h"


/********************************************************************************
	宏定义
********************************************************************************/
#define MORE_MENU_NODE_TAG		0x10		// 更多菜单节点
#define MORE_MENU_TAG			0x20		// 更多菜单

/********************************************************************************
	局部变量声明
********************************************************************************/

CCLabelTTF* textContentLabel ;

/********************************************************************************
	HelpView 类实现
********************************************************************************/
/**
 * 构造函数
 */
HelpView::HelpView() {	
	
}


/**
 * 析构函数
 */
HelpView::~HelpView() {
	if(tabs)
	{
		tabs->removeAllObjects() ;
		tabs->release() ;
	}

	if (textContentLabel)
	{
		textContentLabel->release() ;
	}
}

/**
* 静态方法，创建一个场景，并将自定义的HelpView布景层加入到该场景中
* return  返回创建好的场景对象
*/
CCScene* HelpView::CreateScene() {

	CCScene* scene = CCScene::create() ;
	
	HelpView* msgView = new HelpView() ; // HelpView::create() ;

	if (msgView && msgView->init())
	{
		msgView->init() ;
	}

	msgView->autorelease() ;
	
	scene->addChild(msgView) ;

	return scene ;
}

/**
 * 初始化方法
 */	
bool HelpView::init() {
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

	// 初始化底部条信息
	this->initTopBar(winSize) ;	

	// 初始化中部条
	this->initCenterBar(winSize) ;

	// 初始化底部条
	this->initBottomBar(winSize) ;	
		
	// 接收键盘点击事件
	this->setKeypadEnabled(true) ;

	this->moreMenuShow = false ;

	// 开始更新时间,1秒更新一次
	// this->schedule(schedule_selector(HelpView::updateTimeLabel), 1.0f) ;

	return true ;
}

/**
 * 当该layer进入了运行的scene中运行
 */
void HelpView::onEnter() {
	CCLayer::onEnter() ;
	CCLog("HelpView::onEnter") ;
}
 
/**
 * 当该layer离开了scene时调用
 */
void HelpView::onExit() {


	CCLayer::onExit() ;
}
 

/**
 * 处理返回键事件
 */
 void HelpView::keyBackClicked() {
 	// CCScene* scene = CCTransitionFlipX::create(0.8f, GameMenuView::CreateScene(), kOrientationRightOver) ;
  //   CCDirector::sharedDirector()->replaceScene(scene) ;
 	CCDirector::sharedDirector()->replaceScene(GameMenuView::CreateScene()) ;
 }


/**
 * 存值菜单点击事件处理函数
 */
void HelpView::menuStoreClickCallback(CCObject* pSender) {}

/**
 * 礼包菜单点击事件处理函数
 */
void HelpView::menuGiftsClickCallback(CCObject* pSender) 
{}

/**
 * 返回菜单点击事件处理函数
 */
void HelpView::menuBackClickCallback(CCObject* pSender) 
{
	// CCScene* scene = CCTransitionFlipX::create(0.8f, GameMenuView::CreateScene(), kOrientationRightOver) ;
	// CCDirector::sharedDirector()->replaceScene(scene) ;
	CCDirector::sharedDirector()->replaceScene(GameMenuView::CreateScene()) ;
}


/**
 * 设置菜单点击事件处理函数
 */
void HelpView::menuSettingClickCallback(CCObject* pSender) {}

/**
 *	底部信息菜单
 */
void HelpView::menuInfoClickCallback(CCObject* pSender) 
{
	CCDirector::sharedDirector()->replaceScene(MessageView::CreateScene()) ;
}


/*
 * 底部任务菜单
 */
void HelpView::menuTaskClickCallback(CCObject* pSender) 
{
	CCDirector::sharedDirector()->replaceScene(TaskView::CreateScene()) ;
}

/**
 * 底部商城菜单
 */
void HelpView::menuShopClickCallback(CCObject* pSender) 
{
	CCDirector::sharedDirector()->replaceScene(ShopView::CreateScene()) ;
}

/**
* 底部活动菜单项
*/
void HelpView::menuActivityClickCallback(CCObject* pSender) 
{
	CCDirector::sharedDirector()->replaceScene(ActivityView::CreateScene()) ;
}


/**
* 底部活动菜单项
*/
void HelpView::menuMoreClickCallback(CCObject* pSender) 
{
	// 设置更多菜单显示标志
	this->moreMenuShow = !this->moreMenuShow ;

	if(this->moreMenuShow) 
	{
		this->addChild(moreMenuNode, 5, MORE_MENU_NODE_TAG) ;
	} 
	else
	{
		this->removeChildByTag(MORE_MENU_NODE_TAG, false) ;
	}	
}


/**
* 更多 排行榜菜单项
*/
void HelpView::menuRankingClickCallback(CCObject* pSender) 
{}

/**
 * 好友菜单点击事件处理函数
 */
void HelpView::menuFriendClickCallback(CCObject* pSender) 
{}

/**
 * 客服菜单点击事件处理函数
 */
void HelpView::menuCustomServiceClickCallback(CCObject* pSender) 
{}


/**
*	常见问题标签点击事件回调函数
*/
void HelpView::commonQuestionTabCallback(CCNode* node) 
{
	CCLog("HelpView::commonQuestionTabCallback Clicked ------- ") ;
	textContentLabel->setString( "支付宝帮助中心是支付宝用户的网上帮助平台，提供常见问题查询，自助服务受理，智能机器人在线回复等服务，同时提供人工在线服务（9:00-24:00）及24小时服务热线，服务热线：95188。支付宝客服，支付宝电话，支付宝客服电话，支付宝客服中心，支付宝客服电话号码，淘宝支付宝客服，支付宝客服是多少，支付宝服务，支付宝服务电话，支付宝服务热线，支付宝人工服务，支付宝客户服务，支付宝服务电话，支付宝服务热线，支付宝帮助，支付宝小二帮助中心，支付宝帮助中心， 支付宝客户满意中心，支付宝客户中心，支付宝客户满意。") ;
	YJTabTitle* item ;
	for(int i=0; i<tabs->count(); i++)
	{	
		YJTabTitle* item = (YJTabTitle*) tabs->objectAtIndex(i) ;
		if(item != node) 
		{
			item->setState(kStateNormal) ;
		}
	}
}

/**
*	游戏规则tab点击事件回调函数
*/
void HelpView::gameRuleTabCallback(CCNode* node) 
{
	CCLog("HelpView::gameRuleTabCallback Clicked ------- ") ;

	textContentLabel->setString("     游戏规则帮助.......................................") ;

	YJTabTitle* item ;
	for(int i=0; i<tabs->count(); i++)
	{	
		YJTabTitle* item = (YJTabTitle*) tabs->objectAtIndex(i) ;
		if(item != node) 
		{
			item->setState(kStateNormal) ;
		}
	}
}


/**
* 	推荐好友
*/
void HelpView::recommendFriendsTabCallback(CCNode* node) 
{
	CCLog("HelpView::recommendFriendsTabCallback Clicked ------- ") ;

	textContentLabel->setString("     推荐好友帮助.......................................") ;

	YJTabTitle* item ;
	for(int i=0; i<tabs->count(); i++)
	{	
		YJTabTitle* item = (YJTabTitle*) tabs->objectAtIndex(i) ;
		if(item != node) 
		{
			item->setState(kStateNormal) ;
		}
	}
}

/**
* 	联系我们
*/
void HelpView::contactUsTabCallback(CCNode* node) 
{
	CCLog("HelpView::contactUsTabCallback Clicked ------- ") ;

	textContentLabel->setString("     联系我们帮助.......................................") ;

	YJTabTitle* item ;
	for(int i=0; i<tabs->count(); i++)
	{	
		YJTabTitle* item = (YJTabTitle*) tabs->objectAtIndex(i) ;
		if(item != node) 
		{
			item->setState(kStateNormal) ;
		}
	}
}


// 初始化顶部bar
void HelpView::initTopBar(CCSize winSize) 
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// topBarNode 背景
	CCSprite* topBarBg = CCSprite::create("bg_nav_top.png") ;
	topBarBg->setAnchorPoint(ccp(0.5, 0)) ;
	topBarBg->setPosition(ccp(winSize.width/2, 0)) ;

	const float topBar_height = topBarBg->getContentSize().height ; 

	

	// 顶部条信息 //////////////////////////////////////////////////////////////////////////////////////
	this->topBarNode = CCNode::create() ;
	this->topBarNode->setContentSize(CCSizeMake(winSize.width, topBar_height)) ;
	this->topBarNode->setAnchorPoint(ccp(0, 0)) ;
	this->topBarNode->setPosition(ccp(0, winSize.height - topBar_height)) ;
	this->addChild(this->topBarNode, 0, 1) ;

	// 将topBarNode背景加入到topBarNode
	this->topBarNode->addChild(topBarBg, 0 ) ;


	///////////////////////////// 左侧布局 //////////////////////////
	CCNode* leftNode = CCNode::create() ;
	leftNode->setContentSize(CCSizeMake(300, topBar_height)) ;
	leftNode->setAnchorPoint(ccp(0, 0.5)) ;
	leftNode->setPosition(ccp(30, topBar_height/2)) ;
	this->topBarNode->addChild(leftNode, 1) ;

	// 头像
	CCSprite* headPortraitSprite = CCSprite::create("user/head_default_f2.png") ;
	headPortraitSprite->setAnchorPoint(ccp(0, 0)) ;
	headPortraitSprite->setPosition(ccp(0, 10)) ;
	headPortraitSprite->setScale(0.8) ;
	leftNode->addChild(headPortraitSprite) ;

	// 昵称
	CCLabelTTF* nikeNameLabel = CCLabelTTF::create("昵称：我是主角", "font01.ttf", 22.0f) ;
	// nikeNameLabel->setColor(ccc3(191, 173, 111)) ;
	nikeNameLabel->setAnchorPoint(ccp(0, 0)) ;
	nikeNameLabel->setPosition(ccp(70, topBar_height/2+2)) ;
	nikeNameLabel->setHorizontalAlignment(kCCTextAlignmentLeft) ; 			// 水平对齐方式
	nikeNameLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ; 	// 垂直对齐方式
	leftNode->addChild(nikeNameLabel) ;

	// 金币
	CCLabelTTF* goldCoinLabel = CCLabelTTF::create("金币：10000", "font01.ttf", 22.0f) ;
	goldCoinLabel->setAnchorPoint(ccp(0, 1)) ;
	goldCoinLabel->setPosition(ccp(70, topBar_height/2)) ;
	goldCoinLabel->setHorizontalAlignment(kCCTextAlignmentLeft) ; 			// 水平对齐方式
	goldCoinLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ; 	// 垂直对齐方式
	leftNode->addChild(goldCoinLabel) ;


	// 信息
	CCSprite* titleMsg = CCSprite::create("icon_title_help.png") ;
	titleMsg->setAnchorPoint(ccp(0.5, 0.5)) ;
	titleMsg->setPosition(ccp(winSize.width/2, topBar_height/2)) ;
	this->topBarNode->addChild(titleMsg, 1) ;

	// 分割线
	CCSprite* spliteLineLeft = CCSprite::create("icon_top_nav_splite.png") ;
	spliteLineLeft->setAnchorPoint(ccp(0, 1)) ;
	spliteLineLeft->setPosition(ccp(winSize.width/3+10, topBar_height)) ;
	this->topBarNode->addChild(spliteLineLeft, 1) ;


	// 分割线
	CCSprite* spliteLineRight = CCSprite::create("icon_top_nav_splite.png") ;
	spliteLineRight->setAnchorPoint(ccp(0, 1)) ;
	spliteLineRight->setPosition(ccp(winSize.width*2/3-20, topBar_height)) ;
	this->topBarNode->addChild(spliteLineRight, 1) ;


	/////////////////////////////////////////////////////////////////////////////////////////////////
	/****************************** 菜单选项 ********************************************************/
	// 右侧menu
	const float right_width = 200 ;
	const float item_width = 55 ;

	
	// 礼物
	CCMenuItemImage* menuGifts = CCMenuItemImage::create("menu_gifts_n.png", "menu_gifts_s.png", this,
															menu_selector(HelpView::menuGiftsClickCallback)) ;
	// menuBack->setContentSize(CCSizeMake(67, 68)) ;
	menuGifts->setAnchorPoint(ccp(0, 0.5)) ;
	menuGifts->setPosition(ccp(0, topBar_height/2)) ;
	//menuGifts->setPosition(ccp(right_width-2*item_width, topBar_height/2)) ;
	//rightMenu->addChild(menuGifts) ;

	// 返回大厅
	CCMenuItemImage* menuBack = CCMenuItemImage::create("menu_back_n.png", "menu_back_s.png", this,
															menu_selector(MessageView::menuBackClickCallback)) ;
	menuBack->setAnchorPoint(ccp(0, 0.5)) ;
	menuBack->setPosition(ccp(2*(item_width+10), topBar_height/2)) ;
	//menuBack->setPosition(ccp(right_width, topBar_height/2)) ;
	//rightMenu->addChild(menuBack) ;

	// 设置
	CCMenuItemImage* menuSetting = CCMenuItemImage::create("menu_setting_n.png", "menu_setting_s.png", this,
															menu_selector(MessageView::menuSettingClickCallback)) ;
	// menuBack->setContentSize(CCSizeMake(67, 68)) ;
	
	menuSetting->setAnchorPoint(ccp(0, 0.5)) ;
	menuSetting->setPosition(ccp(item_width+10, topBar_height/2)) ;
	//menuSetting->setPosition(ccp(right_width-item_width, topBar_height/2)) ;


	//rightMenu->addChild(menuSetting) ;
	CCMenu* rightMenu = CCMenu::create(menuGifts, menuBack, menuSetting, NULL) ;
	rightMenu->setContentSize(CCSizeMake(winSize.width/4, topBar_height)) ;
	rightMenu->setAnchorPoint(ccp(0, 0)) ;
	rightMenu->setPosition(ccp(winSize.width*3/4-10, 0)) ;	
	this->topBarNode->addChild(rightMenu, 1) ;
}

// 初始化中间部分bar
void HelpView::initCenterBar(CCSize winSize) 
{
		
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// 遮罩效果
	CCSprite* contentBgSprite = CCSprite::create("bg_center_content.png") ;
	contentBgSprite->setAnchorPoint(ccp(0, 0)) ;
	contentBgSprite->setPosition(ccp(0, 0)) ;

	// 内容背景
	CCSprite* bgCenter = CCSprite::create("bg_center.png") ;
	bgCenter->setAnchorPoint(ccp(0.5, 0)) ;
	bgCenter->setPosition(ccp(winSize.width/2, 77)) ;
	this->addChild(bgCenter, 1) ;


	this->modeSelectNode = CCNode::create() ;
	this->modeSelectNode->setContentSize(contentBgSprite->getContentSize()) ;
	this->modeSelectNode->setAnchorPoint(ccp(0.5, 0.5)) ;
	this->modeSelectNode->setPosition(ccp(winSize.width*0.5, winSize.height*0.5+5)) ;
	this->addChild(this->modeSelectNode, 2) ;

	// 内容背景 加入到 modeSelectNode
	this->modeSelectNode->addChild(contentBgSprite) ;

	const float padding = 10.0f ;		// 内距
	const float margin_left = 40.0f ; 	// 左边距
	const float margin_top = 10.0f ;	// 上边距
	const float margin_bottom = 15.0f ;	// 下边距	

	// 文字内容背景
	CCSprite* textBg = CCSprite::create("bg_center_text.png") ;
	textBg->setAnchorPoint(ccp(0, 0)) ;
	textBg->setPosition(ccp(15, margin_bottom)) ;
	this->modeSelectNode->addChild(textBg, 2) ;

	tabs = CCArray::createWithCapacity(4) ;
	tabs->retain() ;

	// 常见问题Tab
	YJTabTitle* commonQuestionTab = YJTabTitle::create("icon_tab_n.png", "icon_tab_s.png", kStateSelected, "常见问题", "font01.ttf", 25, 
														this, callfuncN_selector(HelpView::commonQuestionTabCallback)) ;
	commonQuestionTab->setAnchorPoint(ccp(0, 0)) ;
	commonQuestionTab->setPosition(ccp(margin_left, textBg->getContentSize().height+margin_bottom-3.5)) ;
	this->modeSelectNode->addChild(commonQuestionTab, 3) ;
	tabs->addObject(commonQuestionTab) ;

	// 游戏规则Tab
	YJTabTitle* gameRuleTab = YJTabTitle::create("icon_tab_n.png", "icon_tab_s.png", kStateNormal, "游戏规则", "font01.ttf", 25, 
												this, callfuncN_selector(HelpView::gameRuleTabCallback)) ;
	gameRuleTab->setAnchorPoint(ccp(0, 0)) ;
	gameRuleTab->setPosition(ccp(margin_left+padding+gameRuleTab->getContentSize().width, textBg->getContentSize().height+margin_bottom-3.5)) ;
	this->modeSelectNode->addChild(gameRuleTab, 3) ;
	tabs->addObject(gameRuleTab) ;

	// 推荐好友Tab
	YJTabTitle*  recommendFriendsTab = YJTabTitle::create("icon_tab_n.png", "icon_tab_s.png", kStateNormal, "推荐好友", "font01.ttf", 25, 
												this, callfuncN_selector(HelpView::recommendFriendsTabCallback)) ;
	recommendFriendsTab->setAnchorPoint(ccp(0, 0)) ;
	recommendFriendsTab->setPosition(ccp(margin_left+2*(padding+recommendFriendsTab->getContentSize().width), textBg->getContentSize().height+margin_bottom-3.5)) ;
	this->modeSelectNode->addChild(recommendFriendsTab, 3) ;
	tabs->addObject(recommendFriendsTab) ;

	// 联系我们Tab
	YJTabTitle*  contactUsTab = YJTabTitle::create("icon_tab_n.png", "icon_tab_s.png", kStateNormal, "联系我们", "font01.ttf", 25, 
												this, callfuncN_selector(HelpView::contactUsTabCallback)) ;
	contactUsTab->setAnchorPoint(ccp(0, 0)) ;
	contactUsTab->setPosition(ccp(margin_left+3*(padding+contactUsTab->getContentSize().width), textBg->getContentSize().height+margin_bottom-3.5)) ;
	this->modeSelectNode->addChild(contactUsTab, 3) ;
	tabs->addObject(contactUsTab) ;

	textContentLabel = CCLabelTTF::create("支付宝帮助中心是支付宝用户的网上帮助平台，提供常见问题查询，自助服务受理，智能机器人在线回复等服务，同时提供人工在线服务（9:00-24:00）及24小时服务热线，服务热线：95188。支付宝客服，支付宝电话，支付宝客服电话，支付宝客服中心，支付宝客服电话号码，淘宝支付宝客服，支付宝客服是多少，支付宝服务，支付宝服务电话，支付宝服务热线，支付宝人工服务，支付宝客户服务，支付宝服务电话，支付宝服务热线，支付宝帮助，支付宝小二帮助中心，支付宝帮助中心， 支付宝客户满意中心，支付宝客户中心，支付宝客户满意。"
														, "font01.ttf",22.0f,CCSizeMake(740, 232),
													kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter) ;
	textContentLabel->setAnchorPoint(ccp(0, 0)) ;
	textContentLabel->setPosition(ccp(25, margin_bottom+5)) ;
	textContentLabel->setColor(ccc3(234, 192, 142)) ;
	this->modeSelectNode->addChild(textContentLabel, 3) ;

	textContentLabel->retain() ;
}


// 初始化底部Bar
void HelpView::initBottomBar(CCSize winSize) 
{
	/////////////////////////////////////////// 底部条 ////////////////////////////////////////
	
	this->footerBarNode = CCNode::create() ;
	this->footerBarNode->setAnchorPoint(ccp(0, 0)) ;
	this->footerBarNode->setPosition(ccp(0, -5)) ;	
	this->addChild(this->footerBarNode) ;

	/////////////////////////////////////// 定义背景 /////////////////////////////////////////
	// 背景
	CCSprite* bottomBarBg = CCSprite::create("bg_bottom_bar.png") ;
	bottomBarBg->setAnchorPoint(ccp(0.5, 0)) ;
	bottomBarBg->setPosition(ccp(winSize.width/2, 0)) ;
	this->footerBarNode->addChild(bottomBarBg, 1) ;

	// 定义底部条高度
	const float footerBarNode_height = bottomBarBg->getContentSize().height ;
	// 设置底部条的高和宽
	this->footerBarNode->setContentSize(CCSizeMake(winSize.width, footerBarNode_height)) ;

	// 背景遮罩层
	CCSprite* bottomBg = CCSprite::create("bg_bottom.png") ;
	bottomBg->setAnchorPoint(ccp(0, 1)) ;
	bottomBg->setPosition(ccp(0, footerBarNode_height)) ;
	this->footerBarNode->addChild(bottomBg, 0) ;


	CCSpriteBatchNode* bottomIcon = CCSpriteBatchNode::create("bg_bottom_icon.png") ;

	// 左边的icon
	CCSprite* leftIcon = CCSprite::createWithTexture(bottomIcon->getTexture()) ;
	leftIcon->setAnchorPoint(ccp(0, 0)) ;
	leftIcon->setPosition(ccp(0, 0)) ;
	this->footerBarNode->addChild(leftIcon, 1) ;

	// 右边的icon
	CCSprite* rightIcon = CCSprite::createWithTexture(bottomIcon->getTexture()) ;
	rightIcon->setAnchorPoint(ccp(1, 0)) ;
	rightIcon->setPosition(ccp(winSize.width, 0)) ;
	rightIcon->setFlipX(true) ; // 水平翻转
	this->footerBarNode->addChild(rightIcon, 1) ;

	const float menuItem_margin = 50.0f ;		// 距离中间位置的距离
	const float menuItem_padding = 100.0f ;		// menuItem之间的间隔

	// 底部菜单
	CCMenu* footerMenu = CCMenu::create() ;
	footerMenu->setContentSize(CCSizeMake(winSize.width, footerBarNode_height) ) ;
	footerMenu->setAnchorPoint(ccp(0, 0)) ;
	footerMenu->setPosition(ccp(0, 0)) ;
	this->footerBarNode->addChild(footerMenu, 2) ;

	// 活动菜单
	CCMenuItemImage* activityMenuItem = CCMenuItemImage::create("menu_activity_n.png", "menu_activity_s.png", 
																this, menu_selector(HelpView::menuActivityClickCallback)) ;
	activityMenuItem->setAnchorPoint(ccp(1, 1)) ;
	activityMenuItem->setPosition(ccp(winSize.width/2-menuItem_margin, footerBarNode_height-3)) ;
	footerMenu->addChild(activityMenuItem) ;

	// 获取menuItem宽度
	const float menuItem_width = activityMenuItem->getContentSize().width ;


	// 信息菜单	
	CCMenuItemImage* infoMenuItem = CCMenuItemImage::create("menu_message_n.png", "menu_message_s.png", 
															this, menu_selector(HelpView::menuInfoClickCallback)) ;
	infoMenuItem->setAnchorPoint(ccp(1, 1)) ;
	infoMenuItem->setPosition(ccp(winSize.width/2-menuItem_margin-menuItem_width-menuItem_padding, footerBarNode_height-3)) ;
	footerMenu->addChild(infoMenuItem) ;

	// 商城菜单
	CCMenuItemImage* shopMenuItem = CCMenuItemImage::create("menu_shop_n.png", "menu_shop_s.png", 
															this, menu_selector(HelpView::menuShopClickCallback)) ;
	shopMenuItem->setAnchorPoint(ccp(0, 1)) ;
	shopMenuItem->setPosition(ccp(winSize.width/2+menuItem_margin, footerBarNode_height-3)) ;
	footerMenu->addChild(shopMenuItem) ;

	// 菜单菜单
	CCMenuItemImage* moreMenuItem = CCMenuItemImage::create("menu_more_n.png", "menu_more_s.png" , 
															this, menu_selector(HelpView::menuMoreClickCallback)) ;
	moreMenuItem->setAnchorPoint(ccp(0, 1)) ;
	moreMenuItem->setPosition(ccp(winSize.width/2+menuItem_margin+menuItem_width+menuItem_padding, footerBarNode_height-3)) ;
	footerMenu->addChild(moreMenuItem) ;
	
	// 更多菜单背景
	CCSprite* moreMenuBg = CCSprite::create("bg_more_menu.png") ;
	moreMenuBg->setAnchorPoint(ccp(0,0)) ;
	moreMenuBg->setPosition(ccp(0, 0)) ;

	const float moreMenu_width = moreMenuBg->getContentSize().width ;
	const float moreMenu_height = moreMenuBg->getContentSize().height ;

	// 更多菜单节点
	moreMenuNode = CCNode::create() ;
	moreMenuNode->setContentSize(moreMenuBg->getContentSize()) ;		// 设置moreMenuNode的尺寸
	moreMenuNode->setAnchorPoint(ccp(1, 0)) ;
	moreMenuNode->setPosition(ccp(winSize.width-80, 80)) ;
	moreMenuNode->retain() ;
	// this->addChild(moreMenuNode, 5, MORE_MENU_NODE_TAG) ;

	moreMenuNode->addChild(moreMenuBg, 0) ;	// 将背景加入到更多菜单中		

	// 更多菜单
	CCMenu* moreMenu = CCMenu::create() ;
	moreMenu->setAnchorPoint(ccp(0, 0)) ;
	moreMenu->setPosition(ccp(0, 0)) ;
	moreMenuNode->addChild(moreMenu, 1, MORE_MENU_TAG) ;


	// 排行榜菜单项
	CCMenuItemImage* rankingMenuItem = CCMenuItemImage::create("menu_ranking_n.png", "menu_ranking_s.png" , 
															this, menu_selector(GameMenuView::menuRankingClickCallback)) ;
	rankingMenuItem->setAnchorPoint(ccp(0, 1)) ;
	rankingMenuItem->setPosition(ccp(10, moreMenu_height-10)) ;
	moreMenu->addChild(rankingMenuItem) ;

	// 任务菜单
	CCMenuItemImage* taskMenuItem = CCMenuItemImage::create("menu_task_n.png", "menu_task_s.png" , 
															this, menu_selector(GameMenuView::menuTaskClickCallback)) ;
	taskMenuItem->setAnchorPoint(ccp(1, 1)) ;
	taskMenuItem->setPosition(ccp(moreMenu_width-10, moreMenu_height-10)) ;
	moreMenu->addChild(taskMenuItem) ;

	// 好友菜单
	CCMenuItemImage* friendMenuItem = CCMenuItemImage::create("menu_friend_n.png", "menu_friend_s.png", 
															this, menu_selector(GameMenuView::menuFriendClickCallback)) ;	
	friendMenuItem->setAnchorPoint(ccp(0, 0)) ;
	friendMenuItem->setPosition(ccp(10, 5)) ;
	moreMenu->addChild(friendMenuItem) ;

	// 客服菜单
	CCMenuItemImage* customserviceMenuItem = CCMenuItemImage::create("menu_cs_n.png", "menu_cs_s.png", 
																this, menu_selector(GameMenuView::menuSettingClickCallback)) ;
	customserviceMenuItem->setAnchorPoint(ccp(1, 0)) ;
	customserviceMenuItem->setPosition(ccp(moreMenu_width-10, 5)) ;
	moreMenu->addChild(customserviceMenuItem) ;
	
}

/********************************************************************************
	End of File: HelpView.cpp 
********************************************************************************/