/********************************************************************************
	File: GamePlayerRight.cpp
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-27
	
	该类封装的是玩家信息，包括，头像，等级，拥有金币，下注等信息
	同时负责显示在界面上显示这些信息，靠右显示的玩家

********************************************************************************/

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/
#include "GamePlayerRight.h"


/********************************************************************************
	GamePlayerRight类实现
********************************************************************************/
GamePlayerRight::GamePlayerRight(const char* headPortrait, const char* nikeName, int grade, DWORD godenCoin) 
			: GamePlayer(headPortrait, nikeName, grade, godenCoin)
{
	this->initial() ;
} 


GamePlayerRight::~GamePlayerRight() 
{}

/**
* 	初始化方法
*/
void GamePlayerRight::initial() 
{
	GamePlayer::initial() ;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize() ;

	const float head_frame_border = 4.0f ; 		// 头像边框宽度
	const float head_frame_width = 86.0f ; 		// 头像框宽度
	const float head_frame_height = 115.0f ; 	// 头像框高度

	const float bet_node_width = 89.0f ;
	const float bet_node_height = 41.0f ;


	const float item_height = 20.0f ;

	const float width = head_frame_width*2+35 ;
	const float height = head_frame_height + bet_node_height;
	

	CCSize size = CCSizeMake(width, height) ;
	this->setContentSize(size) ;	

	CCNode* headNode = CCNode::create() ;
	headNode->setContentSize(CCSizeMake(head_frame_width, head_frame_height)) ;
	headNode->setAnchorPoint(ccp(1, 1)) ;
	headNode->setPosition(ccp(width, height)) ;
	this->addChild(headNode) ;

	/************* 头像框 *******************************************************************************/
	// 头像背景框	
	this->_headFrameSprite = CCSprite::create("user/head_frame_p.png") ;
	this->_headFrameSprite->setAnchorPoint( ccp(1, 1) ) ;
	this->_headFrameSprite->setPosition( ccp(head_frame_width, head_frame_height) ) ;
	// 加入到头像Node中
	headNode->addChild(this->_headFrameSprite, 0) ; 

	CCLog("_headFrameSprite width:%f, height: %f", _headFrameSprite->getContentSize().width,  _headFrameSprite->getContentSize().height) ;

	// 默认头像
	this->_headSprite = CCSprite::create(this->_headPortrait.c_str()) ;
	this->_headSprite->setAnchorPoint( ccp(1, 1) ) ;
	this->_headSprite->setPosition( ccp(head_frame_width-head_frame_border, head_frame_height-item_height) ) ;
	// 加入到头像Node中
	headNode->addChild(this->_headSprite, 1) ;
	
	/************* 昵称 *******************************************************************************/
	this->_nikeNameLabel = CCLabelTTF::create(this->_nikeName.c_str(), "font01.ttf", 14.0f) ;
	this->_nikeNameLabel->setAnchorPoint(ccp(0.5, 1)) ;
	this->_nikeNameLabel->setPosition(ccp(head_frame_width/2, head_frame_height-2)) ;
	this->_nikeNameLabel->setHorizontalAlignment(kCCTextAlignmentCenter) ; 		// 水平对齐方式
	this->_nikeNameLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ; 	// 垂直对齐方式
	// 加入到头像Node中
	headNode->addChild(this->_nikeNameLabel, 2) ;


	/************* 等级 *******************************************************************************/
	char grade[10]  ;
	sprintf(grade, "LV.%d\0", this->_grade) ;
	this->_gradeLabel = CCLabelTTF::create(grade, "font01.ttf", 14.0f) ;
	this->_gradeLabel->setAnchorPoint(ccp(0.5, 1)) ;
	this->_gradeLabel->setPosition(ccp(head_frame_width/2, head_frame_height-item_height)) ;
	this->_gradeLabel->setHorizontalAlignment(kCCTextAlignmentCenter) ; 		// 水平对齐方式
	this->_gradeLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ; 	// 垂直对齐方式
	// 加入到头像Node中
	headNode->addChild(this->_gradeLabel, 2) ;
	

	/************* 金币 *******************************************************************************/
	CCSprite* godenIcon = CCSprite::create("user/icon_gold.png") ;
	godenIcon->setAnchorPoint(ccp(0, 0)) ;
	godenIcon->setPosition(ccp(5, 5)) ;
	// 加入到头像Node中
	headNode->addChild(godenIcon, 2) ;

	char godenCoin[50] ;
	sprintf(godenCoin, "%ld\0", this->_godenCoin) ;
	this->_godenCoinLabel = CCLabelTTF::create(godenCoin, "font01.ttf", 14.0f) ;
	this->_godenCoinLabel->setContentSize(CCSizeMake(width, item_height)) ;
	this->_godenCoinLabel->setAnchorPoint(ccp(0.5, 0)) ;
	this->_godenCoinLabel->setPosition(ccp(head_frame_width/2, 0)) ;
	this->_godenCoinLabel->setHorizontalAlignment(kCCTextAlignmentCenter) ; 		// 水平对齐方式
	this->_godenCoinLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ; 	// 垂直对齐方式
	// 加入到头像Node中
	headNode->addChild(this->_godenCoinLabel) ;


	///////////////////////////////////// 下注 ////////////////////////////////////////
	
	CCNode* betNode = CCNode::create() ;
	betNode->setContentSize(CCSizeMake(bet_node_width, bet_node_height)) ;
	betNode->setAnchorPoint(ccp(1, 1)) ;
	betNode->setPosition(ccp(width, height-head_frame_height)) ;
	this->addChild(betNode, 0) ;

	// 背景
	CCSprite* betNodeBg = CCSprite::create("user/bet_bg.png") ;
	betNodeBg->setAnchorPoint(ccp(0, 0)) ;
	betNodeBg->setPosition(ccp(0, 0)) ;
	betNode->addChild(betNodeBg, 0) ;

	char betCoin[20] ;
	sprintf(betCoin, "%ld\0", this->_betCoin) ;
	this->_betCoinLabel = CCLabelTTF::create(betCoin, "font01.ttf", 20.0f) ;
	this->_betCoinLabel->setContentSize(CCSizeMake(bet_node_width, bet_node_height)) ;
	this->_betCoinLabel->setAnchorPoint(ccp(0, 0.5)) ;
	this->_betCoinLabel->setPosition(ccp(40, bet_node_height/2)) ;
	this->_betCoinLabel->setHorizontalAlignment(kCCTextAlignmentLeft) ; 			// 水平对齐方式
	this->_betCoinLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ; 	// 垂直对齐方式
	this->_betCoinLabel->setVisible(false) ; // 默认隐藏
	betNode->addChild(this->_betCoinLabel, 1) ;


	// 牌
	this->cards = new CardsLarge() ;
	this->cards->setAnchorPoint(ccp(1, 0)) ;
	this->cards->setPosition(ccp(0, bet_node_height)) ;
	// this->cards->setScale(0.8) ;

	this->addChild(cards, 0) ;


	// 状态：
	this->_state = kInitial ; // 初始化状态	
}

void GamePlayerRight::onEnter(void) {
	GamePlayer::onEnter() ;
}

void GamePlayerRight::onExit(void) 
{
	GamePlayer::onExit() ;
}