/********************************************************************************
	File: GamePlayerCenter.cpp
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-27
	
	该类封装的是玩家信息，包括，头像，等级，拥有金币，下注等信息
	同时负责显示在界面上显示这些信息，靠右显示的玩家

********************************************************************************/

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/
#include "GamePlayerCenter.h"


/********************************************************************************
	GamePlayerRight类实现
********************************************************************************/
GamePlayerCenter::GamePlayerCenter(const char* headPortrait, const char* nikeName, int grade, DWORD godenCoin) 
			: GamePlayer(headPortrait, nikeName, grade, godenCoin)
{
	this->initial() ;
} 


GamePlayerCenter::~GamePlayerCenter() 
{}

/**
* 	初始化方法
*/
void GamePlayerCenter::initial() 
{
	GamePlayer::initial() ;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize() ;

	const float head_frame_border = 4.0f ; 		// 头像边框宽度
	const float head_frame_width = 193.0f ; 	// 头像框宽度
	const float head_frame_height = 101.0f ; 	// 头像框高度

	const float width = winSize.width/3 ;
	const float height = head_frame_height ;
	const float item_height = 20.0f ;
	
	
	CCSize size = CCSizeMake(width, height) ;
	this->setContentSize(size) ;	

	// ************ 头像框 *******************************************************************************
	CCNode* headNode = CCNode::create() ;
	headNode->setContentSize(CCSizeMake(head_frame_width, head_frame_height)) ;
	headNode->setAnchorPoint(ccp(0, 0)) ;
	headNode->setPosition(ccp(0, 0)) ;
	this->addChild(headNode, 0) ;

	// 头像背景框
	this->_headFrameSprite = CCSprite::create("user/head_frame_l.png") ;
	this->_headFrameSprite->setAnchorPoint( ccp(0, 0) ) ;
	this->_headFrameSprite->setPosition( ccp(0, 0) ) ;
	headNode->addChild(this->_headFrameSprite, 0) ;

	// 遮罩层
	
	CCSprite* headMask = CCSprite::create("user/head_frame_l_mask.png") ;
	headMask->setContentSize(CCSizeMake(185, 73)) ;
	headMask->setAnchorPoint(ccp(0, 0.5)) ;
	headMask->setPosition(ccp(2, head_frame_height/2)) ;
	headNode->addChild(headMask, 2) ;	
	

	// 默认头像
	this->_headSprite = CCSprite::create(this->_headPortrait.c_str()) ;
	this->_headSprite->setAnchorPoint( ccp(1, 0.5) ) ;
	this->_headSprite->setPosition( ccp(head_frame_width, head_frame_height/2-2) ) ;
	headNode->addChild(this->_headSprite, 1) ;	
	

	// ************************* 左侧布局 *************************************************************
	const float left_node_width = 100.0f ;
	const float left_node_height = item_height*3 ;
	const float margin_left = 20.0f ;

	CCNode* leftNode = CCNode::create() ;
	leftNode->setContentSize(CCSizeMake(left_node_width, left_node_height)) ;
	leftNode->setAnchorPoint(ccp(0, 0.5)) ;
	leftNode->setPosition(ccp(0, head_frame_height/2)) ;
	this->addChild(leftNode, 1) ;

	//************* 昵称 *******************************************************************************
	this->_nikeNameLabel = CCLabelTTF::create(this->_nikeName.c_str(),"font01.ttf", 16.0f,CCSizeMake(left_node_width-margin_left, item_height),
									kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter) ;
	this->_nikeNameLabel->setAnchorPoint(ccp(0, 0.5)) ;
	this->_nikeNameLabel->setPosition(ccp(margin_left, left_node_height/2+item_height)) ;
	leftNode->addChild(this->_nikeNameLabel) ;


	//************* 等级 *******************************************************************************
	char grade[10]  ;
	sprintf(grade, "LV.%d\0", this->_grade) ;
	this->_gradeLabel = CCLabelTTF::create(grade,"font01.ttf", 16.0f,CCSizeMake(left_node_width-margin_left, item_height),
									kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter) ;
	this->_gradeLabel->setAnchorPoint(ccp(0, 0.5)) ;
	this->_gradeLabel->setPosition(ccp(20, left_node_height/2)) ;
	leftNode->addChild(this->_gradeLabel) ;
	

	//************* 金币 *******************************************************************************
	CCSprite* godenIcon = CCSprite::create("user/icon_gold.png") ;
	godenIcon->setAnchorPoint(ccp(0, 0.5)) ;
	godenIcon->setPosition(ccp(5, left_node_height/2-item_height)) ;
	// 加入到头像Node中
	leftNode->addChild(godenIcon) ;

	char godenCoin[50] ;
	sprintf(godenCoin, "%ld\0", this->_godenCoin) ;
	this->_godenCoinLabel = CCLabelTTF::create(godenCoin,"font01.ttf", 16.0f,CCSizeMake(width, item_height),
									kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter) ;
	this->_godenCoinLabel->setAnchorPoint(ccp(0, 0.5)) ;
	this->_godenCoinLabel->setPosition(ccp(margin_left, left_node_height/2-item_height)) ;
	leftNode->addChild(this->_godenCoinLabel) ;


	//************* 下注 *******************************************************************************

	const float bet_node_width = 114.0f ;
	const float bet_node_height = 46.0f ;
	const float bet_margin_left = 40.0f ;

	CCNode* betNode = CCNode::create() ;
	betNode->setContentSize(CCSizeMake(bet_node_width, bet_node_height)) ;
	betNode->setAnchorPoint(ccp(0, 0)) ;
	betNode->setPosition(ccp(head_frame_width, 0)) ;
	this->addChild(betNode, 0) ;

	// 背景
	CCSprite* betNodeBg = CCSprite::create("user/bet_bg.png") ;
	betNodeBg->setAnchorPoint(ccp(0, 0)) ;
	betNodeBg->setPosition(ccp(0, 0)) ;
	betNode->addChild(betNodeBg, 0) ;

	char betCoin[20] ;
	sprintf(betCoin, "%ld", this->_betCoin) ;
	this->_betCoinLabel = CCLabelTTF::create(betCoin,"font01.ttf", 20.0f,CCSizeMake(bet_node_width-bet_margin_left, bet_node_height),kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter) ;
	this->_betCoinLabel->setAnchorPoint(ccp(0, 0.5)) ;
	this->_betCoinLabel->setPosition(ccp(bet_margin_left, bet_node_height/2)) ;
	this->_betCoinLabel->setVisible(false) ; // 默认隐藏
	betNode->addChild(this->_betCoinLabel, 1) ;

	// 初始化牌
	cards = new CardsLarge() ;
	cards->setAnchorPoint(ccp(0, 0)) ;
	cards->setPosition(ccp(0, height)) ;
	// cards->setScale(0.8) ;
	this->addChild(cards) ;

	// 状态：
	this->_state = kInitial ; // 初始化状态	
}

void GamePlayerCenter::onEnter(void) {
	GamePlayer::onEnter() ;
}

void GamePlayerCenter::onExit(void) 
{
	GamePlayer::onExit() ;
}