/********************************************************************************
	File: GamePlayer.cpp
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-22
	
	该类封装的是玩家信息，包括，头像，等级，拥有金币，下注等信息
	同时负责显示在界面上显示这些信息

********************************************************************************/

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/

#include "GamePlayer.h"

/********************************************************************************
	GamePlayer类定义
********************************************************************************/
GamePlayer::GamePlayer(void) 
{

}

GamePlayer::GamePlayer(const char* headPortrait, const char* nikeName, int grade, DWORD godenCoin) : _headPortrait(headPortrait), _nikeName(nikeName), _grade(grade), _godenCoin(godenCoin) , _betCoin(0)
{
	this->initial() ;
} 

/*
* 	析构方法
*/
GamePlayer::~GamePlayer(void) 
{ }

void GamePlayer::initial()
{
	// CCLog("GamePlayer::%d", sizeof(m_cbHandCardData)/sizeof(m_cbHandCardData[0][0])) ;
}

void GamePlayer::provideCard(int i) 
{
	if(this->cards)
	{
		this->cards->provide(i) ;
	}
}

/*
*	
*/
void GamePlayer::onEnter(void) 
{
	CCNode::onEnter() ;

	return ;
}

void GamePlayer::onExit(void) 
{
	CCNode::onExit() ;
}

/**
*	和玩家比较牌的大小
*	@param 
*		GamePlayer* other 比较的另一个玩家
*	@return 0牌相同；1我大；-1他大		
*/
BYTE GamePlayer::compareCard(GamePlayer* other) 
{
	return 0 ;
}

/**
*	玩家下注
*/
void GamePlayer::betOn(DWORD bet) 
{
	this->setGodenCoin(this->_godenCoin - bet) ;
	this->setBetCoin(this->getBetCoin() + bet) ;

	if(!this->_betCoinLabel->isVisible())
	{
		this->_betCoinLabel->setVisible(true) ;
	}
}

// 叫庄
void GamePlayer::focus(CCAction* action) 
{
	// 头像闪烁
	this->_headSprite->runAction(action) ;
}

/**
*	赢了
*	@param	totalBet 当前游戏中总下注金额
*/
void GamePlayer::win(DWORD totalBet) 
{
	this->setGodenCoin(this->_godenCoin + totalBet) ;
}

/**
*	隐藏所有牌
*/
void GamePlayer::hideAllCard() 
{
	this->cards->hideAllCard() ;
}

/**
*	隐藏下注金币
*/
void GamePlayer::hideBetCoin() 
{
	this->_betCoin = 0 ;
	this->_betCoinLabel->setVisible(false) ;
}

