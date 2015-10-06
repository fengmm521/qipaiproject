/********************************************************************************
	File: CardsLarge.cpp
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-29
	
	CardsLarge类实现

********************************************************************************/

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/

#include "Cards.h"

/********************************************************************************
	CardsLarge类实现
********************************************************************************/
// 构造函数
CardsLarge::CardsLarge() 
{
	this->init() ;
}

// 析构函数
CardsLarge::~CardsLarge() 
{

}

// 比牌结束后，显示牌面内容
void CardsLarge::showCard(void) 
{

}




// 初始化方法
void CardsLarge::init() 
{

	/************************* 初始化牌 *************************************************************/
	for(int i=0; i<3; i++)
	{
		this->cardIcons[i] = CCSprite::create(LARGE_CARD_BACK) ;
		this->cardIcons[i]->setAnchorPoint(ccp(0, 0)) ;
		this->cardIcons[i]->setPosition(ccp(i*30, 10)) ;
		this->cardIcons[i]->setVisible(false) ;

		this->addChild(cardIcons[i], i) ;
	}

	/************************* 初始化看图标************************************************************/
	this->lookIcon = CCSprite::create("card/icon_kan.png") ;
	this->lookIcon->setAnchorPoint(ccp(0, 0)) ;
	this->lookIcon->setPosition(ccp(0,0)) ;
	this->lookIcon->setVisible(false) ;
	this->addChild(lookIcon, 3) ;
}