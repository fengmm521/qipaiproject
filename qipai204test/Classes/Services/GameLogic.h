#ifndef GAME_LOGIC_HEAD_FILE
#define GAME_LOGIC_HEAD_FILE

#pragma once

#include "cocos2d.h"
#include "DataType.h"
#include "GloableMacro.h"

USING_NS_CC ;

//计算数组维数
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))

//////////////////////////////////////////////////////////////////////////
//宏定义
#define	DRAW						2									// 和局类型

//数值掩码
#define	LOGIC_MASK_COLOR			0xF0								// 花色掩码
#define	LOGIC_MASK_VALUE			0x0F								// 数值掩码

//扑克类型
#define CT_SINGLE					1									// 单牌类型
#define CT_DOUBLE					2									// 对子类型
#define	CT_SHUN_ZI					3									// 顺子类型
#define CT_JIN_HUA					4									// 金花类型
#define	CT_SHUN_JIN					5									// 顺金类型
#define	CT_BAO_ZI					6									// 豹子类型
#define CT_SPECIAL					7									// 特殊类型

//////////////////////////////////////////////////////////////////////////

//游戏逻辑类
class GameLogic : public CCObject
{
	//变量定义
private:
	static BYTE						m_cbCardListData[52];				//扑克定义

	//函数定义
public:
	//构造函数
	GameLogic();
	//析构函数
	virtual ~GameLogic();

	//类型函数
public:
	//获取类型
	BYTE GetCardType(BYTE cbCardData[], BYTE cbCardCount);
	//获取数值
	BYTE GetCardValue(BYTE cbCardData) { return cbCardData&LOGIC_MASK_VALUE; }
	//获取花色
	BYTE GetCardColor(BYTE cbCardData) { return cbCardData&LOGIC_MASK_COLOR; }

	//控制函数
public:
	/**
	* 	排列扑克
	*	@param cdCardData 	要排列扑克的数组
	*	@param cdCardCount 	排列扑克的数组长度
	*/
	void SortCardList(BYTE cbCardData[], BYTE cbCardCount);
	
	// 混乱扑克，随机抽取cbBufferCount张牌
	// cbCardBuffer 	存放cbBufferCount张牌的数组
	// cbBufferCount	随机抽取牌的数量
	void RandCardList(BYTE cbCardBuffer[], BYTE cbBufferCount);

	//功能函数
public:
	//逻辑数值
	BYTE GetCardLogicValue(BYTE cbCardData);
	//对比扑克
	BYTE CompareCard(BYTE cbFirstData[], BYTE cbNextData[], BYTE cbCardCount);
};

//////////////////////////////////////////////////////////////////////////

#endif