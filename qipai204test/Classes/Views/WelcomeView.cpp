/********************************************************************************
	File: WelcomeView.cpp
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-30
	
	WelcomeView 类实现

********************************************************************************/

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/
#include "WelcomeView.h"
#include "LoginView.h"


/********************************************************************************
	WelcomeView 类实现
********************************************************************************/
/**
*	构造函数
*/
WelcomeView::WelcomeView() 
{
	// 接收键盘点击事件
	// this->setKeypadEnabled(true) ;
}

/**
*	析造函数
*/
WelcomeView::~WelcomeView() 
{}

/**
*	创建该界面依赖的场景对象
*/
CCScene* WelcomeView::CreateScene() 
{
	CCScene* scene = CCScene::create() ;

	WelcomeView* layer = WelcomeView::create() ;
	scene->addChild(layer) ;

	return scene ;
}

/**
*	初始化方法，继承CCLayer的方法
*/
bool WelcomeView::init() 
{
	if(!CCLayer::init())
	{
		return false ;
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize() ;

	// 背景
	CCSprite* downBg = CCSprite::create("bg_welcome.png") ;
	downBg->setAnchorPoint(ccp(0.5, 0)) ;
	downBg->setPosition(ccp(winSize.width/2, 0)) ;
	this->addChild(downBg, 0) ;

	
	
	// 加载logo
	CCSprite* logo = CCSprite::create("logo_01.png") ;
	logo->setAnchorPoint(ccp(0.5, 0.5)) ;
	logo->setPosition(ccp(winSize.width/2, winSize.height/2)) ;
	this->addChild(logo, 1) ;

	
	//////////////////////////// LOADING  //////////////////////////////////////////
	CCLabelTTF* loadingLabel = CCLabelTTF::create("LOADING...", "Arial", 26) ;
	loadingLabel->setAnchorPoint(ccp(0.5, 0)) ;
	loadingLabel->setPosition(ccp(winSize.width/2, 65)) ;
	loadingLabel->setHorizontalAlignment(kCCTextAlignmentCenter) ; // 水平对齐方式
	loadingLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ; // 垂直对齐方式
	
	this->addChild(loadingLabel, 1) ;	
	
	///////////////////////////////// 进度条 //////////////////////////////////////////
	const float margin_bottom = 38.0f ;

	// 进度条背景
	CCSprite* progressBarBg = CCSprite::create("bg_loading.png") ;
	progressBarBg->setAnchorPoint(ccp(0.5, 0)) ;
    progressBarBg->setPosition(ccp(winSize.width/2, margin_bottom));
    this->addChild(progressBarBg, 1) ;

	// 进度条
	progressBar = CCProgressTimer::create(CCSprite::create("bg_loading_icon.png"));
	progressBar->setType( kCCProgressTimerTypeBar ); //设置进度条为水平
	//    Setup for a bar starting from the left since the midpoint is 0 for the x
    progressBar->setMidpoint(ccp(0,0));
    //    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
    progressBar->setBarChangeRate(ccp(1, 0)); // 设置进度条的长度和高度开始变化的大小
	progressBar->setAnchorPoint(ccp(0.5, 0)) ;
    progressBar->setPosition(ccp(winSize.width/2, margin_bottom+2));
    this->addChild(progressBar, 1) ; 
	
	return true ;
}

/**
 * 处理返回键事件
 */
void WelcomeView::keyBackClicked() 
{
	// 结束游戏
 	CCDirector::sharedDirector()->end() ;
}

void WelcomeView::onEnter() 
{
	CCLayer::onEnter() ;
	
	CCLog("CCLayer::onEnter") ;
 
	// 分三个阶段进行加载
	CCProgressFromTo* fromTo1 = CCProgressFromTo::create(3, 0, 70) ;
	CCProgressFromTo* fromTo2 = CCProgressFromTo::create(1, 70, 100) ;
	CCAction* thirdCallBack = CCCallFuncN::create(this, callfuncN_selector(WelcomeView::thirdProgressCallBack)) ;
	CCLog("thirdCallBack") ;
	// 开始执行
	progressBar->runAction( CCSequence::create(fromTo1, fromTo2, thirdCallBack, NULL) ) ;
	
	CCLog("runAction") ;
}

/**
*	第一进度回调
*/
void WelcomeView::firstProgressCallBack() 
{

}

/**
*	第二进度回调
*/
void WelcomeView::secondProgressCallBack() 
{

}

/**
*	第三进度回调
*/
void WelcomeView::thirdProgressCallBack() 
{
	// 运行游戏场场景
	CCDirector::sharedDirector()->replaceScene(LoginView::CreateScene()) ;	
}
