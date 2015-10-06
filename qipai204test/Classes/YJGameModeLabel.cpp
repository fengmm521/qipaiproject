/********************************************************************************
	File: YJGameModeLabel.cpp
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-30
	
	YJGameModeLabel 类是游戏模式上的限制信息，例如：进入限制和底注限制

********************************************************************************/


/********************************************************************************
	引入需要的头文件信息
********************************************************************************/
#include "YJGameModeLabel.h"



/********************************************************************************
	YJGameModeLabel 类实现
********************************************************************************/


/**
*	构造函数
*	@param	enterLimit 	进入限制
*	@param	baseBet		底注
*/
YJGameModeLabel::YJGameModeLabel(int enterLimit, int baseBet) 
{
	this->init(enterLimit, baseBet) ;
}

/**
*	构造函数
*	@param	enterLimit 	进入限制
*	@param	baseBet		底注
*/
YJGameModeLabel::YJGameModeLabel(const char* enterLimit, const char*  baseBet) 
{
	this->init(enterLimit, baseBet) ;
}

/*
*	析构函数
*/
YJGameModeLabel::~YJGameModeLabel() 
{}

/**
*	初始化函数
*	@param	enterLimit 	进入限制
*	@param	baseBet		底注
*/
void YJGameModeLabel::init(int enterLimit, int baseBet) 
{
	const float label_height = 30.0f ;
	//////////////////////////  进入限制 ///////////////////////
	char entryfeeStr[30] ;
	sprintf(entryfeeStr, "进入限制：%d金币\0", enterLimit) ;
	CCLabelTTF* enterLimitLabel = CCLabelTTF::create(entryfeeStr, "font01.ttf", 20.0f) ;
	enterLimitLabel->setColor(ccc3(0, 0, 0)) ;
	enterLimitLabel->setAnchorPoint(ccp(0, 0)) ;
	enterLimitLabel->setPosition(ccp(0, label_height)) ;
	enterLimitLabel->setHorizontalAlignment(kCCTextAlignmentLeft) ; // 水平对齐方式
	enterLimitLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ; // 垂直对齐方式
	

	CCLog("Label width : %f, height: %f", enterLimitLabel->getContentSize().width, enterLimitLabel->getContentSize().height) ;

	////////////////////////// 底注 /////////////////////////
	char awardStr[30] ;
	sprintf(awardStr, "　　底注：%d金币\0", baseBet) ;
	CCLabelTTF* baseBetLabel = CCLabelTTF::create(awardStr, "font01.ttf", 20.0f) ;
	baseBetLabel->setColor(ccc3(0, 0, 0)) ;
	baseBetLabel->setAnchorPoint(ccp(0, 0)) ;
	baseBetLabel->setPosition(ccp(0, 0)) ;
	baseBetLabel->setHorizontalAlignment(kCCTextAlignmentLeft) ; // 水平对齐方式
	baseBetLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ; // 垂直对齐方式
	

	float width = enterLimitLabel->getContentSize().width > baseBetLabel->getContentSize().width?enterLimitLabel->getContentSize().width:baseBetLabel->getContentSize().width ;

	this->setContentSize(CCSizeMake(width, 2*label_height)) ;
	this->addChild(enterLimitLabel) ;
	this->addChild(baseBetLabel) ;
}

/**
*	初始化函数
*	@param	enterLimit 	进入限制
*	@param	baseBet		底注
*/
void YJGameModeLabel::init(const char* enterLimit, const char* baseBet) 
{
		const float label_height = 30.0f ;
	//////////////////////////  进入限制 ///////////////////////
	char entryfeeStr[30] ;
	sprintf(entryfeeStr, "进入限制：%s金币\0", enterLimit) ;
	CCLabelTTF* enterLimitLabel = CCLabelTTF::create(entryfeeStr, "font01.ttf", 20.0f) ;
	enterLimitLabel->setColor(ccc3(0, 0, 0)) ;
	enterLimitLabel->setAnchorPoint(ccp(0, 0)) ;
	enterLimitLabel->setPosition(ccp(0, label_height)) ;
	enterLimitLabel->setHorizontalAlignment(kCCTextAlignmentLeft) ; // 水平对齐方式
	enterLimitLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ; // 垂直对齐方式
	this->addChild(enterLimitLabel) ;



	////////////////////////// 底注 /////////////////////////
	char awardStr[30] ;
	sprintf(awardStr, "　　底注：%s金币\0", baseBet) ;
	CCLabelTTF* baseBetLabel = CCLabelTTF::create(awardStr, "font01.ttf", 20.0f) ;
	baseBetLabel->setColor(ccc3(0, 0, 0)) ;
	baseBetLabel->setAnchorPoint(ccp(0, 0)) ;
	baseBetLabel->setPosition(ccp(0, 0)) ;
	baseBetLabel->setHorizontalAlignment(kCCTextAlignmentLeft) ; // 水平对齐方式
	baseBetLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ; // 垂直对齐方式
	this->addChild(baseBetLabel) ;

	float width = enterLimitLabel->getContentSize().width > baseBetLabel->getContentSize().width?enterLimitLabel->getContentSize().width:baseBetLabel->getContentSize().width ;

	this->setContentSize(CCSizeMake(width, 2*label_height)) ;
}

/********************************************************************************
	End of File: YJGameModeLabel.cpp     
********************************************************************************/
