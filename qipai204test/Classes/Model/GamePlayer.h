/********************************************************************************
	File: GamePlayer.h
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-22
	
	该类封装的是玩家信息，包括，头像，等级，拥有金币，下注等信息
	同时负责显示在界面上显示这些信息

********************************************************************************/
#ifndef __GOLDENFRAUD_GamePlayer__
#define __GOLDENFRAUD_GamePlayer__

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/

#include "cocos2d.h"
#include "DataType.h"
#include "Cards.h"

/********************************************************************************
	宏定义
********************************************************************************/

USING_NS_CC ;

typedef enum 
{
	kInitial = 0,		// 初始状态	
	kPrepareReady, 		// 准备状态
	kWaitBet, 			// 等待下注
	kBetDone, 			// 下注完毕
	kCompareCard,		// 比牌
	kGiveUpCard			// 弃牌
} GamePlayerState ;


/********************************************************************************
	GamePlayer类定义
********************************************************************************/
class GamePlayer : public CCNode 
{
public:
	/*
	*	构造方法
	*/
	GamePlayer() ;
	
	GamePlayer(const char* headPortrait, const char* nikeName, int grade, DWORD godenCoin) ;		

	/*
	* 	析构方法
	*/
	virtual ~GamePlayer() ;

	/*
	*	
	*/
	virtual void onEnter(void) ;

	virtual void onExit(void) ;

	virtual void initial(void)  ;

	void provideCard(int i) ;

	// 叫庄
	void focus(CCAction* action) ;

	/**
	*	和玩家比较牌的大小
	*	@param 
	*		GamePlayer* other 比较的另一个玩家
	*	@return 0牌相同；1我大；-1他大		
	*/
	BYTE compareCard(GamePlayer* other) ;

	/**
	*	玩家下注
	*/
	void betOn(DWORD bet) ;

	/**
	*	赢了
	*	@param	totalBet 当前游戏中总下注金额
	*/
	void win(DWORD totalBet) ;

	/**
	*	隐藏所有牌
	*/
	void hideAllCard() ;

	/**
	*	隐藏下注金币
	*/
	void hideBetCoin() ;

public:
	inline void setHeadPortrait(const char* headPortrait) 
	{ 
		_headPortrait = headPortrait ; 
		CCSpriteBatchNode* ui = CCSpriteBatchNode::create(_headPortrait.c_str());
		_headSprite->setTexture(ui->getTexture()) ;
	}
	inline const char* getHeadPortrait() { return _headPortrait.c_str() ; }

	inline void setNikeName(const char* nikeName)
	{ 
		_nikeName = nikeName ; 
		_nikeNameLabel->setString(_nikeName.c_str()) ;
	}
	inline const char* getNikeName() { return _nikeName.c_str() ; }

	inline void setGrade(int grade) 
	{ 
		_grade = grade ; 
		char gradeStr[10] ;
		sprintf(gradeStr, "LV.%d\0", _grade) ;
		_gradeLabel->setString(gradeStr) ;
	}
	inline int getGrade() { return _grade ; } 

	inline void setGodenCoin(DWORD godenCoin) 
	{ 
		_godenCoin = godenCoin ; 
		char godenCoinStr[50] ;
		sprintf(godenCoinStr, "%ld\0", _godenCoin) ;
		_godenCoinLabel->setString(godenCoinStr) ;
	}
	inline DWORD getGodenCoin() { return _godenCoin ; }

	inline void setBetCoin(DWORD betCoin) 
	{ 
		_betCoin = betCoin ; 
		char betCoinStr[20] ;
		sprintf(betCoinStr, "%ld\0", _betCoin) ;
		_betCoinLabel->setString(betCoinStr) ;
	}
	inline DWORD getBetCoin() { return _betCoin ; }

	inline void setCard(const BYTE* card) 
	{ 
		memcpy(_card, card, 3) ; 
		CCLog("card is : %x %x %x", card[0], card[1], card[2]) ;
	}
	// inline void getCard(BYTE* card) { memcpy(card, _card, 3) ; }
	inline BYTE* getCard() { return _card ; }

	inline void setState(GamePlayerState state) 
	{
	 	_state = state ; 
	 	switch(_state)
	 	{
	 		case kPrepareReady: // 准备状态

	 			break ;
	 		case kWaitBet: // 等待下注，说明已经下了底
	 			_betCoinLabel->setVisible(true) ;
	 			break ;
	 		case kGiveUpCard: // 放弃牌
	 			// this->cards->setVisible(false) ;
	 			hideAllCard() ;
	 			_betCoin = 0 ;
	 			_betCoinLabel->setVisible(false) ;
	 			break ;
	 		default:
	 			break ;
	 	}
	}

	inline GamePlayerState getState() { return _state ; }

protected:
	// 头像图片名称
	std::string _headPortrait ;
	// 头像显示组件框
	CCSprite* _headFrameSprite ;
	// 头像显示组件
	CCSprite* _headSprite ;


	// 昵称
	std::string _nikeName ;
	// 昵称显示组件
	CCLabelTTF* _nikeNameLabel ;


	// 等级
	int _grade ;
	// 等级显示组件
	CCLabelTTF* _gradeLabel ;


	// 拥有金币数
	DWORD _godenCoin ; // DWORD 就是 unsigned long
	// 拥有金币显示组件
	CCLabelTTF* _godenCoinLabel ;


	// 下注金币数
	DWORD _betCoin ;
	// 下注金币显示组件
	CCLabelTTF* _betCoinLabel ;


	// 持有的牌
	BYTE _card[3] ;

	// 牌
	Cards* cards ;

	// 玩家状态
	GamePlayerState _state ;

} ;


#endif