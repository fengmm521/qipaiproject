/********************************************************************************
	File: YJGoodsImageButton.h
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-30
	
	YJGoodsImageButton 类是ShopView商品界面中商品列表中显示的商品图信息


********************************************************************************/

#ifndef __GOLDENFRAUD__YJGoodsImageButton__
#define __GOLDENFRAUD__YJGoodsImageButton__

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/
#include "cocos2d.h"


/********************************************************************************
	using namespace
********************************************************************************/
USING_NS_CC ;

/********************************************************************************
	YJGoodsImageButton 类定义
********************************************************************************/
class YJGoodsImageButton : public CCNode, public CCTargetedTouchDelegate
{
public:
	/**
	* 	构造函数
	*/
	YJGoodsImageButton() ;

	/**
	*	析构函数
	*/
	~YJGoodsImageButton() ;

	/**
    *   创建一个TabTitle对象
    *   @param nornalImageName      普通状态下的图片名称
    *   @param selectedImageName    选中状态下的图片名称
    *   @param title          		按钮上显示的标题文字信息
    *   @param money             	钱
    *   @param target             	
    *	@param selector				
    *   
    *   @return YJGoodsImageButton
    */ 
    static YJGoodsImageButton* create(const char* normalImageName, const char* selectedImageName, const char* title, 
                                			float money, CCObject* target, SEL_MenuHandler selector) ;

    /**
    *   创建一个TabTitle对象
    *   @param normalImageName      普通状态下的图片名称
    *   @param selectedImageName    选中状态下的图片名称
    *   @param title          		按钮上显示的标题文字信息
    *   @param money             	钱
    *   @param target             	
    *	@param selector		
    *  
    *   @return YJGoodsImageButton
    */ 
    static YJGoodsImageButton* create(const char* nOrSImageName, const char* title, 
                                			float money, CCObject* target, SEL_MenuHandler selector) ;

    /**
    *   初始化操作
    *   @param nornalImageName      普通状态下的图片名称
    *   @param selectedImageName    选中状态下的图片名称
    *   @param title          		按钮上显示的标题文字信息
    *   @param money             	钱
    *   @param target             	
    *	@param selector				
    *   
    *   @return true：初始化成功；false：失败
    */ 
    bool initWithString(const char* normalImageName, const char* selectedImageName, const char* title, float money, CCObject* target, SEL_MenuHandler selector) ;

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
    *	触摸结束
    */
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event) ;

    /**
    *   设置触摸是否可用
    */
    void setTouchEnabled(bool touchEnabled) ;

    inline void setTarget(cocos2d::CCObject* pTarget, SEL_MenuHandler pSelector)
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
    inline SEL_MenuHandler getSelector()
    {
        return _pSelector;
    }


private:
	 // 目标对象
    cocos2d::CCObject*  _pTarget ;
    
    // 方法指针
    SEL_MenuHandler      _pSelector ;

	/**
	*	普通背景
	*/
	CCSprite* _bgSprite ;

	// 普通状态下图片名称
    std::string _normalImageName ;

    // 选中状态下图片名称
    std::string _selectedImageName ;

    // 标题
    std::string _title ;

    // 钱
    float _money ;

	// 开始触摸时候的位置
	CCPoint _beginPos ;

    // 是否可以触摸
    bool _touchEnabled ;

} ;



#endif
