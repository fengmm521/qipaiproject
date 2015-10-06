/********************************************************************************
	File: YJOptionMenuItemImage.cpp
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-30
	
	该类是继承至CCMenuItemImage，实现指定其他图片和文字

********************************************************************************/


/********************************************************************************
	引入需要的头文件信息
********************************************************************************/
#include "YJOptionMenuItemImage.h"

/********************************************************************************
	YJOptionMenuItemImage 类方法实现
********************************************************************************/

bool YJOptionMenuItemImage::init()
{
	if(!CCMenuItemImage::init())
	{
		return false ;
	}

	return true ;
}

YJOptionMenuItemImage* YJOptionMenuItemImage::create(const char *normalImage, const char *selectedImage, CCObject* target, SEL_MenuHandler selector, 
										int limit, int baseCoin) 
{
	YJOptionMenuItemImage *pRet = new YJOptionMenuItemImage();
    if (pRet && pRet->initWithNormalImage(normalImage, selectedImage, NULL, target, selector))
    {
    	CCSize size = pRet->getContentSize() ;
		const float font_height = 30.0f ;
		const float font_width = size.width ;


		////////////////////////////////////////////////////////////////////////////////
		/*
		const float labelNode_height = 2 * font_height ;
		const float margin_left = size.width/4+5 ;
		CCNode* labelNode = CCNode::create() ;
		labelNode->setAnchorPoint(ccp(0, 1)) ;
		labelNode->setContentSize(CCSizeMake(font_width, labelNode_height)) ;		
		labelNode->setPosition(ccp(45, 240) ) ;
		pRet->addChild(labelNode) ;
		*/

		//////////////////////////  进入限制 ///////////////////////
		char entryfeeStr[30] ;
		sprintf(entryfeeStr, "进入限制：%d金币\0", limit) ;
		CCLabelTTF* entryfeeLabel = CCLabelTTF::create(entryfeeStr, "font01.ttf", 20.0f) ;
		entryfeeLabel->setColor(ccc3(0, 0, 0)) ;
		entryfeeLabel->setAnchorPoint(ccp(0, 1)) ;
		entryfeeLabel->setPosition(ccp(0, 0)) ;
		entryfeeLabel->setHorizontalAlignment(kCCTextAlignmentLeft) ; // 水平对齐方式
		entryfeeLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ; // 垂直对齐方式
		pRet->addChild(entryfeeLabel) ;

/*
		////////////////////////// 底注 /////////////////////////
		char awardStr[30] ;
		sprintf(awardStr, "　　底注：%d金币\0", baseCoin) ;
		CCLabelTTF* awardLabel = CCLabelTTF::create(awardStr, "font01.ttf", 20.0f) ;
		awardLabel->setColor(ccc3(0, 0, 0)) ;
		awardLabel->setAnchorPoint(ccp(0, 1)) ;
		awardLabel->setPosition(ccp(0, labelNode_height-font_height)) ;
		awardLabel->setHorizontalAlignment(kCCTextAlignmentLeft) ; // 水平对齐方式
		awardLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ; // 垂直对齐方式
		labelNode->addChild(awardLabel) ;
*/
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);

    return NULL;
}