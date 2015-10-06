/********************************************************************************
	File: YJOptionMenuItemImage.h
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-30
	
	该类是继承至CCMenuItemImage，实现指定其他图片和文字，在菜单界面使用

********************************************************************************/
#ifndef __GOLDENFRAUD_YJOptionMenuItemImage_
#define __GOLDENFRAUD_YJOptionMenuItemImage_

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/
#include "cocos2d.h"


USING_NS_CC ;


/********************************************************************************
	YJMenuItemImage 类定义
********************************************************************************/
class YJOptionMenuItemImage : public CCMenuItemImage
{
public:

	static YJOptionMenuItemImage* create(const char *normalImage, const char *selectedImage, CCObject* target, SEL_MenuHandler selector, 
										int limit, int baseCoin) ;


	virtual bool init(void) ;
} ;
 



#endif