/********************************************************************************
	File: YJTabTitle.h
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-06-05
	
	标签Title类，可以换状态图片

********************************************************************************/
#ifndef __GOLDENFRAUD_YJTabTitle__
#define __GOLDENFRAUD_YJTabTitle__


/********************************************************************************
	引入需要的头文件信息
********************************************************************************/
#include "cocos2d.h"

/********************************************************************************
	using namespace
********************************************************************************/
USING_NS_CC ;

/********************************************************************************
    声明类型
********************************************************************************/
typedef enum
{   
    kStateNormal = 0,           // 普通状态
    kStateSelected              // 选中状态

} YJTabTitleState ;

/********************************************************************************
	YJTabTitle 类定义
********************************************************************************/

class YJTabTitle : public CCNode, public CCTargetedTouchDelegate
{
public:
	/**
	*	构造函数
	*/
	YJTabTitle() ;

	/**
	*	析构函数
	*/
	~YJTabTitle() ;

    /**
    *   创建一个TabTitle对象
    *   @param nornalImageName      普通状态下的图片名称
    *   @param selectedImageName    选中状态下的图片名称
    *   @param displayText          标签上显示的文字信息
    *   @param fontName             字体名称
    *   @param fontSize             字体大小
    *   
    *   @return TabTitle对象
    */ 
    static YJTabTitle* create(const char* normalImageName, const char* selectedImageName, YJTabTitleState state, const char* displayText, 
                                const char *fontName, float fontSize, CCObject* target, SEL_CallFuncN selector) ;

    /**
    *   创建一个TabTitle对象
    *   @param normalImageName      普通状态下的图片名称
    *   @param selectedImageName    选中状态下的图片名称
    *   @param displayText          标签上显示的文字信息
    *   
    *   @return TabTitle对象
    */ 
    static YJTabTitle* create(const char* normalImageName, const char* selectedImageName, const char* displayText, CCObject* target, SEL_CallFuncN selector) ;

    /**
    *   初始化操作
    *   @param normalImageName      普通状态下的图片名称
    *   @param selectedImageName    选中状态下的图片名称
    *   @param displayText          标签上显示的文字信息
    *   @param fontName             字体名称
    *   @param fontSize             字体大小
    *   
    *   @return true：初始化成功；false：失败
    */ 
    bool initWithString(const char* normalImageName, const char* selectedImageName, YJTabTitleState state, const char* displayText, const char *fontName, float fontSize, CCObject* target, SEL_CallFuncN selector) ;

    /**
    *   获取矩形区域
    */
    CCRect getRect() ;

    virtual void onEnter() ;

    virtual void onExit() ;

    /**
    *	是否包含
    */
    bool containsTouchLocation(CCTouch* touch) ;

    /**
    *	开始触摸
    */
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event) ;

    /**
    *	触摸移动
    */
    //virtual void ccTouchMoved(CCTouch* touch, CCEvent* event) ;

    /**
    *	触摸结束
    */
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event) ;

    /**
    *   设置TabTitle状态
    */

    // 设置TabTitle状态
    inline void setState(YJTabTitleState state) 
    {
        if (this->state != state)
        {
            this->state = state ;

            switch(this->state)
            {
                case kStateNormal:
                    this->bgSprite->setTexture(CCTextureCache::sharedTextureCache()->addImage(this->normalImageName.c_str())) ;
                    break ;

                case kStateSelected:
                    this->bgSprite->setTexture(CCTextureCache::sharedTextureCache()->addImage(this->selectedImageName.c_str())) ;
                    break ;
            }
        }
    }

    // 获取状态
    inline YJTabTitleState getState() { return this->state ; }

    inline void setTarget(cocos2d::CCObject* pTarget, SEL_CallFuncN pSelector)
    {
        _pTarget = pTarget;
        _pSelector = pSelector;
        
        if (_pTarget)
        {
            _pTarget->retain();
        }
    } 

    /** Get the target of callback selector funtion, mainly used by CCHttpClient */
    inline CCObject* getTarget()
    {
        return _pTarget;
    }
    /** Get the selector function pointer, mainly used by CCHttpClient */
    inline SEL_CallFuncN getSelector()
    {
        return _pSelector;
    }

protected:
    // 目标对象
    cocos2d::CCObject*  _pTarget ;
    
    // 方法指针
    SEL_CallFuncN      _pSelector ;

    // 图片显示背景
    CCSprite* bgSprite ;

    // 显示文字的Label
    CCLabelTTF* label ;

    // 状态
    YJTabTitleState state ;

    // 普通状态下图片名称
    std::string normalImageName ;

    // 选中状态下图片名称
    std::string selectedImageName ;

    // 显示的字符串
    std::string displayText ;

    // 字体名称
    std::string fontName ;

    // 字体大小
    float fontSize ;
} ;


#endif