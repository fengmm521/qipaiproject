/********************************************************************************
	File: Cards.cpp
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-29
	
	Cards类实现

********************************************************************************/

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/

#include "Cards.h"

/********************************************************************************
	Cards类实现
********************************************************************************/
// 构造函数
Cards::Cards() 
{

}

// 析构函数
Cards::~Cards() 
{

}

// 移动扑克牌，这个是在发牌的时候进行调用
void Cards::provide(int i) 
{
	if(i>=0 && i<=3)
	{
		this->cardIcons[i]->setVisible(true) ;
	}
}

// 隐藏所有的牌
void Cards::hideAllCard(void) 
{
	for(int i=0; i<MAX_COUNT; i++)
	{
		if(cardIcons[i])
		{
			cardIcons[i]->setVisible(false) ;
		}
	}
}

// 比牌结束后，显示牌面内容
void Cards::showCard() 
{

}

// 看牌，在显示牌的位置显示看的图标
void Cards::lookCard() 
{
	if(this->lookIcon)
	{
		this->lookIcon->setVisible(true) ;
	}
}

void Cards::init() 
{
	
}