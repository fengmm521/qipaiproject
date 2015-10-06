/********************************************************************************
	File: GameMenuView.cpp
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-30
	
	GameMenuView 类是游戏选项菜单界面类

********************************************************************************/

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/
// #include "GloableMacro.h"
#include "GameMenuView.h"
#include "GloableUtils.h"
#include "YJGameModeLabel.h"

#include "GameGroundView.h"
#include "MessageView.h"
#include "TaskView.h"
#include "ActivityView.h"
#include "HelpView.h"
#include "ShopView.h"

/********************************************************************************
	宏定义
********************************************************************************/
#define MORE_MENU_NODE_TAG		0x10		// 更多菜单节点
#define MORE_MENU_TAG			0x20		// 更多菜单


/********************************************************************************
	using namespace
********************************************************************************/
USING_NS_CC;

/********************************************************************************
	GameMenuView 类实现
********************************************************************************/
/**
 * 构造函数
 */
GameMenuView::GameMenuView() {	
	// 预加载图片
}


/**
 * 析构函数
 */
GameMenuView::~GameMenuView() {
	// 释放更多菜单, 因为在初始化的时候进行了保持，在initBottomBar()方法中
	this->moreMenuNode->release() ;
}

/**
*	static CCScene* scene()                         				
*	静态方法，创建一个场景，并将自定义的GameMenu布景层加入到该场景中
*	return  返回创建好的场景对象
*/
CCScene* GameMenuView::CreateScene() {

	CCScene* scene = CCScene::create() ;
	
	GameMenuView* gameMenu = new GameMenuView() ; 

	if (gameMenu && gameMenu->init())
	{
		gameMenu->init() ;
	}

	gameMenu->autorelease() ;
	
	scene->addChild(gameMenu) ;

	return scene ;
}

/**
 * 初始化方法
 */	
bool GameMenuView::init() {
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

	// 开始更新时间,1秒更新一次
	this->schedule(schedule_selector(GameMenuView::updateTimeLabel), 1.0f) ;
	this->moreMenuShow = false ;

	return true ;
}

/**
 * 当该layer进入了运行的scene中运行
 */
void GameMenuView::onEnter() {
	CCLayer::onEnter() ;
	CCLog("GameMenu::onEnter") ;

	// CCMessageBox("测试MessageBox", "提示") ;
}
 
/**
 * 当该layer离开了scene时调用
 */
void GameMenuView::onExit() {
	CCLayer::onExit() ;
}
 

/**
 * 处理返回键事件
 */
 void GameMenuView::keyBackClicked() {
 	// 结束游戏
 	CCDirector::sharedDirector()->end() ;
 }

	/**
 * 存值菜单点击事件处理函数
 */
void GameMenuView::menuMoneyTreeClickCallback(CCObject* pSender) {}

/**
 * 礼包菜单点击事件处理函数
 */
void GameMenuView::menuGiftsClickCallback(CCObject* pSender) 
{}


/**
 * 中级场
 */
void GameMenuView::menuMiddleClickCallback(CCObject* pSender) {
	// 运行游戏场场景
	CCDirector::sharedDirector()->replaceScene(GameGroundView::CreateScene()) ;	
}

/**
 * 初级场
 */
void GameMenuView::menuJuniorClickCallback(CCObject* pSender) {
	// 运行游戏场场景
	CCDirector::sharedDirector()->replaceScene(GameGroundView::CreateScene()) ;	
}

/**
 * 高级场
 */
void GameMenuView::menuSeniorClickCallback(CCObject* pSender) {
	// 运行游戏场场景
	CCDirector::sharedDirector()->replaceScene(GameGroundView::CreateScene()) ;	
}

/**
 *	底部信息菜单
 */
void GameMenuView::menuInfoClickCallback(CCObject* pSender) 
{
	CCDirector::sharedDirector()->replaceScene(MessageView::CreateScene()) ;
}

/*
 * 底部任务菜单
 */
void GameMenuView::menuTaskClickCallback(CCObject* pSender) 
{
	CCDirector::sharedDirector()->replaceScene(TaskView::CreateScene()) ;
}

/**
 * 底部商城菜单
 */
void GameMenuView::menuShopClickCallback(CCObject* pSender) 
{
	CCDirector::sharedDirector()->replaceScene(ShopView::CreateScene()) ;
}

/**
* 底部活动菜单项
*/
void GameMenuView::menuActivityClickCallback(CCObject* pSender) 
{
	CCDirector::sharedDirector()->replaceScene(ActivityView::CreateScene()) ;
}

/**
 * 帮助菜单点击事件处理函数
 */
void GameMenuView::menuHelpClickCallback(CCObject* pSender) 
{
	CCDirector::sharedDirector()->replaceScene(HelpView::CreateScene()) ;
}

/**
 * 设置菜单点击事件处理函数
 */
void GameMenuView::menuSettingClickCallback(CCObject* pSender) 
{
	//CCDirector::sharedDirector()->replaceScene(SettingView::CreateScene()) ;
}

/**
* 底部菜单菜单项
*/
void GameMenuView::menuMoreClickCallback(CCObject* pSender) 
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
void GameMenuView::menuRankingClickCallback(CCObject* pSender) 
{}

/**
 * 好友菜单点击事件处理函数
 */
void GameMenuView::menuFriendClickCallback(CCObject* pSender) 
{}

/**
 * 客服菜单点击事件处理函数
 */
void GameMenuView::menuCustomServiceClickCallback(CCObject* pSender) 
{}

/**
 * 更新时间标签里面显示的时间，schedule
 */
void GameMenuView::updateTimeLabel() 
{
	char nowTime[9] ;
	GloableUtils::getTime(nowTime) ;
	this->timeLabel->setString(nowTime) ;
}

// 初始化顶部bar
void GameMenuView::initTopBar(CCSize winSize) 
{
	////////////////////////////////////////////// 顶部条信息 //////////////////////////////////////////////
	// topBarNode背景
	CCSprite* topBarBg = CCSprite::create("bg_nav_top.png") ;
	topBarBg->setAnchorPoint(ccp(0.5, 0)) ;
	topBarBg->setPosition(ccp(winSize.width/2, 0)) ;
	
	// 顶部条高度
	const float topBar_height = topBarBg->getContentSize().height ; 


	this->topBarNode = CCNode::create() ;
	this->topBarNode->setContentSize(CCSizeMake(winSize.width, topBar_height)) ;
	this->topBarNode->setPosition(ccp(0, winSize.height - topBar_height)) ;
	this->addChild(this->topBarNode, 0, 1) ;

	// 将背景加入到topBarNode中
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

	// 分割线
	CCSprite* spliteLineLeft = CCSprite::create("icon_top_nav_splite.png") ;
	spliteLineLeft->setAnchorPoint(ccp(0, 1)) ;
	spliteLineLeft->setPosition(ccp(winSize.width/3+10, topBar_height)) ;
	this->topBarNode->addChild(spliteLineLeft, 1) ;

	// 显示时间
	char timeString[9] ;
	GloableUtils::getTime(timeString) ;
	this->timeLabel = CCLabelTTF::create(timeString, "AppleGothic", 30.0f) ;
	this->timeLabel->setAnchorPoint(ccp(0.5, 0.5)) ;
	this->timeLabel->setPosition(ccp(winSize.width/2, topBar_height/2+5)) ;
	this->timeLabel->setColor(ccc3(255, 0, 0) );	
	this->timeLabel->setHorizontalAlignment(kCCTextAlignmentCenter) ; 			// 水平对齐方式
	this->timeLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ; 	// 垂直对齐方式
	this->topBarNode->addChild(this->timeLabel) ;

	// 分割线
	CCSprite* spliteLineRight = CCSprite::create("icon_top_nav_splite.png") ;
	spliteLineRight->setAnchorPoint(ccp(0, 1)) ;
	spliteLineRight->setPosition(ccp(winSize.width*2/3-20, topBar_height)) ;
	this->topBarNode->addChild(spliteLineRight, 1) ;

	////////////////////////////////////////// 菜单选项 ///////////////////////////////////////////////
	const float menu_node_item_width = 50.0f ;
	const float menu_node_item_height = 55.0f ;
	
	const float menu_node_item_padding = 15.0f ;
	const float menuNode_width = 4*menu_node_item_width+3*menu_node_item_padding ;

	// 顶部菜单
	CCMenu* topMenu = CCMenu::create() ;
	topMenu->setContentSize(CCSizeMake(menuNode_width, topBar_height)) ;
	topMenu->setAnchorPoint(ccp(0, 0)) ;
	topMenu->setPosition(ccp(winSize.width-3*menu_node_item_padding/2-menuNode_width, 3)) ;
	topMenu->alignItemsHorizontallyWithPadding(10) ; // 水平排列，间距10像素
	this->topBarNode->addChild(topMenu, 1) ;	

	// 摇钱树按钮
	CCMenuItemImage* moneyTreeMenuItem = CCMenuItemImage::create("menu_moneytree_n.png", "menu_moneytree_s.png", 
															this, menu_selector(GameMenuView::menuMoneyTreeClickCallback)) ;
	moneyTreeMenuItem->setAnchorPoint(ccp(0, 0.5)) ;
	moneyTreeMenuItem->setPosition(ccp(0, topBar_height/2)) ;
	topMenu->addChild(moneyTreeMenuItem) ;


	// 礼包按钮
	CCMenuItemImage* giftsMenuItem = CCMenuItemImage::create("menu_gifts_n.png", "menu_gifts_s.png", 
															this, menu_selector(GameMenuView::menuGiftsClickCallback)) ;
	giftsMenuItem->setAnchorPoint(ccp(0, 0.5)) ;
	giftsMenuItem->setPosition(ccp(menu_node_item_width+menu_node_item_padding + 5, topBar_height/2)) ;
	topMenu->addChild(giftsMenuItem) ;
	

	// 帮助按钮
	CCMenuItemImage* helpMenuItem = CCMenuItemImage::create("menu_help_n.png", "menu_help_s.png", 
															this, menu_selector(GameMenuView::menuHelpClickCallback)) ;
	helpMenuItem->setAnchorPoint(ccp(0, 0.5)) ;
	helpMenuItem->setPosition(ccp((menu_node_item_width+menu_node_item_padding)*2, topBar_height/2)) ;
	topMenu->addChild(helpMenuItem) ;

	// 设置按钮
	CCMenuItemImage* settingMenuItem = CCMenuItemImage::create("menu_setting_n.png", "menu_setting_s.png", 
															this, menu_selector(GameMenuView::menuSettingClickCallback)) ;
	settingMenuItem->setAnchorPoint(ccp(0, 0.5)) ;
	settingMenuItem->setPosition(ccp((menu_node_item_width+menu_node_item_padding)*3 - 5, topBar_height/2)) ;
	topMenu->addChild(settingMenuItem) ;
	

}

// 初始化中间部分bar
void GameMenuView::initCenterBar(CCSize winSize) 
{
	//////////////////////////////// 喇叭信息以及系统信息显示框  ///////////////////////////////////
	const float info_tip_width = 526.0f ;
	const float info_tip_height = 40.0f ;
	this->infoTipNode = CCNode::create() ;
	this->infoTipNode->setContentSize(CCSizeMake(info_tip_width, info_tip_height)) ;
	this->infoTipNode->setAnchorPoint(ccp(0.5, 1)) ;
	this->infoTipNode->setPosition(ccp(winSize.width/2, winSize.height-70)) ;
	this->addChild(this->infoTipNode, 0, 2) ;

	// 背景图片
	CCSprite* infoTipBg = CCSprite::create("bg_broadcast.png") ;
	infoTipBg->setAnchorPoint(ccp(0, 0)) ;
	infoTipBg->setPosition(ccp(0, 0)) ;
	this->infoTipNode->addChild(infoTipBg) ;

	// 喇叭图标
	CCSprite* bugleIconSprite = CCSprite::create("icon_bugle.png") ;
	bugleIconSprite->setAnchorPoint(ccp(0, 0)) ;
	bugleIconSprite->setPosition(ccp(-10, -10)) ;
	this->infoTipNode->addChild(bugleIconSprite) ;

	// 通知信息
	CCLabelTTF* tipInfoLabel = CCLabelTTF::create("王佑：呵呵，这局我赢定了！","font01.ttf", 22.0f, CCSizeMake(info_tip_width, info_tip_height),
												kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter) ;
	tipInfoLabel->setAnchorPoint(ccp(0, 0)) ;
	tipInfoLabel->setPosition(ccp(60, 0)) ;
	this->infoTipNode->addChild(tipInfoLabel) ;


	////////////////////////////////// 游戏模式选择框  ////////////////////////////////////
	const float mode_menu_height = 300.0f ;
	const float mode_menu_width = 280.0f ;
	this->modeSelectNode = CCNode::create() ;
	this->modeSelectNode->setContentSize(CCSizeMake(winSize.width, mode_menu_height)) ;
	this->modeSelectNode->setAnchorPoint(ccp(0, 0.5)) ;
	this->modeSelectNode->setPosition(ccp(0, winSize.height/2-20)) ;
	this->addChild(this->modeSelectNode) ; // 加入到Layer

	// 模式选择菜单
	CCMenu *modeSelectMenu = CCMenu::create() ;
	modeSelectMenu->setContentSize(CCSizeMake(winSize.width, mode_menu_height)) ;
	modeSelectMenu->setAnchorPoint(ccp(0, 0)) ;
	modeSelectMenu->setPosition(ccp(0, 0)) ;
	this->modeSelectNode->addChild(modeSelectMenu) ;

	// 中级

	CCMenuItemImage* middleMenuItem = CCMenuItemImage::create("menu_gamemode_middle_n.png", "menu_gamemode_middle_s.png", 
																		this, menu_selector(GameMenuView::menuMiddleClickCallback)) ;
	middleMenuItem->setAnchorPoint(ccp(0.5, 0)) ;
	middleMenuItem->setPosition(ccp(mode_menu_width/2, 0)) ;

	modeSelectMenu->addChild(middleMenuItem) ;

	YJGameModeLabel* middleLabel = new YJGameModeLabel(3000, 100) ;
	middleLabel->setAnchorPoint(ccp(0.5, 0.5)) ;
	middleLabel->setPosition(ccp(mode_menu_width/2, mode_menu_height/2 -30)) ;
	this->modeSelectNode->addChild(middleLabel, 1) ;
	middleLabel->release() ;

	// 初级
	CCMenuItemImage* juniorMenuItem = CCMenuItemImage::create("menu_gamemode_junior_n.png", "menu_gamemode_junior_s.png", 
																		this, menu_selector(GameMenuView::menuJuniorClickCallback) ) ;
	juniorMenuItem->setAnchorPoint(ccp(0.5, 0)) ;
	juniorMenuItem->setPosition(ccp(winSize.width/2, 0)) ;
	modeSelectMenu->addChild(juniorMenuItem) ;

	YJGameModeLabel* juniorLabel = new YJGameModeLabel(3000, 100) ;
	juniorLabel->setAnchorPoint(ccp(0.5, 0.5)) ;
	juniorLabel->setPosition(ccp(winSize.width/2, mode_menu_height/2 -10)) ;
	this->modeSelectNode->addChild(juniorLabel, 1) ;
	juniorLabel->release() ;

	// 高级
	CCMenuItemImage* seniorMenuItem = CCMenuItemImage::create("menu_gamemode_senior_n.png", "menu_gamemode_senior_s.png", 
																		this, menu_selector(GameMenuView::menuSeniorClickCallback) ) ;
	seniorMenuItem->setAnchorPoint(ccp(0.5, 0)) ;
	seniorMenuItem->setPosition(ccp(winSize.width-mode_menu_width/2, 0)) ;
	modeSelectMenu->addChild(seniorMenuItem) ;

	YJGameModeLabel* seniorLabel = new YJGameModeLabel("3000", "100") ;
	seniorLabel->setAnchorPoint(ccp(0.5, 0.5)) ;
	seniorLabel->setPosition(ccp(winSize.width-mode_menu_width/2, mode_menu_height/2 -30)) ;
	this->modeSelectNode->addChild(seniorLabel, 1) ;
	seniorLabel->release() ;
	

	//////////////////////////////////////// 在线人数  ////////////////////////////////////////////
	const float onLineNode_margin_bottom = 78.0f ;
	this->onLineNode = CCNode::create() ;
	
	this->onLineNode->setAnchorPoint(ccp(0.5, 0)) ;
	this->onLineNode->setPosition(ccp(winSize.width/2, onLineNode_margin_bottom)) ;

	this->addChild(this->onLineNode, 0, 4) ;

	
	// 在线人数背景
	CCSprite* onlineBg = CCSprite::create("bg_online_players.png") ;
	onlineBg->setPosition(ccp(0, 0)) ;
	onlineBg->setAnchorPoint(ccp(0, 0)) ;
	this->onLineNode->addChild(onlineBg) ;
	this->onLineNode->setContentSize(onlineBg->getContentSize()) ;
	
	// 在线人数文字
	CCLabelTTF* onlineCountLabel = CCLabelTTF::create("在线人数：1000000", "font01.ttf", 26.0f) ;
	onlineCountLabel->setAnchorPoint(ccp(0.5, 0.5)) ;
	onlineCountLabel->setPosition(ccp(winSize.width/2, onlineBg->getContentSize().height/2)) ;
	onlineCountLabel->setHorizontalAlignment(kCCTextAlignmentLeft) ; // 水平对齐方式
	onlineCountLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ; // 垂直对齐方式
	this->onLineNode->addChild(onlineCountLabel) ;
	
}


// 初始化底部Bar
void GameMenuView::initBottomBar(CCSize winSize) 
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
																this, menu_selector(GameMenuView::menuActivityClickCallback)) ;
	activityMenuItem->setAnchorPoint(ccp(1, 1)) ;
	activityMenuItem->setPosition(ccp(winSize.width/2-menuItem_margin, footerBarNode_height-3)) ;
	footerMenu->addChild(activityMenuItem) ;

	// 获取menuItem宽度
	const float menuItem_width = activityMenuItem->getContentSize().width ;


	// 信息菜单	
	CCMenuItemImage* infoMenuItem = CCMenuItemImage::create("menu_message_n.png", "menu_message_s.png", 
															this, menu_selector(GameMenuView::menuInfoClickCallback)) ;
	infoMenuItem->setAnchorPoint(ccp(1, 1)) ;
	infoMenuItem->setPosition(ccp(winSize.width/2-menuItem_margin-menuItem_width-menuItem_padding, footerBarNode_height-3)) ;
	footerMenu->addChild(infoMenuItem) ;

	// 商城菜单
	CCMenuItemImage* shopMenuItem = CCMenuItemImage::create("menu_shop_n.png", "menu_shop_s.png", 
															this, menu_selector(GameMenuView::menuShopClickCallback)) ;
	shopMenuItem->setAnchorPoint(ccp(0, 1)) ;
	shopMenuItem->setPosition(ccp(winSize.width/2+menuItem_margin, footerBarNode_height-3)) ;
	footerMenu->addChild(shopMenuItem) ;

	// 菜单菜单
	CCMenuItemImage* moreMenuItem = CCMenuItemImage::create("menu_more_n.png", "menu_more_s.png" , 
															this, menu_selector(GameMenuView::menuMoreClickCallback)) ;
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
	End of File: GameMenuView.cpp     
********************************************************************************/