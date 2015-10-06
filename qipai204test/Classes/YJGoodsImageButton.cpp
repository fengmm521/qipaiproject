/********************************************************************************
	File: YJGoodsImageButton.cpp
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-30
	
	YJGoodsImageButton 类是ShopView商品界面中商品列表中显示的商品图信息
	类实现

********************************************************************************/

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/
#include "YJGoodsImageButton.h"


/********************************************************************************
	宏定义
********************************************************************************/
#define LABEL_TITLE_TAG				0x10			// 标题label
#define LABEL_MONEY_TAG				0x11			// 钱label


/********************************************************************************
	YJGoodsImageButton 类实现
********************************************************************************/
/**
* 	构造函数
*/
YJGoodsImageButton::YJGoodsImageButton() 
{
}

/**
*	析构函数
*/
YJGoodsImageButton::~YJGoodsImageButton() 
{
	if (_pTarget)
    {
        _pTarget->release();
    }
}


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
YJGoodsImageButton* YJGoodsImageButton::create(const char* normalImageName, const char* selectedImageName, const char* title, 
                            			float money, CCObject* target, SEL_MenuHandler selector) 
{
	YJGoodsImageButton *pRet = new YJGoodsImageButton();
    if(pRet && pRet->initWithString(normalImageName, selectedImageName, title, money, target, selector))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

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
YJGoodsImageButton* YJGoodsImageButton::create(const char* nOrSImageName, const char* title, 
                            			float money, CCObject* target, SEL_MenuHandler selector) 
{
	return YJGoodsImageButton::create(nOrSImageName, nOrSImageName, title, money, target, selector) ;
}

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
bool YJGoodsImageButton::initWithString(const char* normalImageName, const char* selectedImageName, const char* title, float money, 
	CCObject* target, SEL_MenuHandler selector) 
{
	if(!normalImageName)
	{
		return false ;
	}

	if(!selectedImageName)
	{
		return false ;
	}

	if(!title)
	{
		return false ;
	}

	this->_normalImageName = normalImageName ;
	this->_selectedImageName = selectedImageName ;
	this->_title = title ;
	this->_money = money ;

	this->setTarget(target, selector) ; // 设置回到函数

	CCTextureCache* textureCache = CCTextureCache::sharedTextureCache() ;

	this->_bgSprite = CCSprite::createWithTexture(textureCache->addImage(this->_normalImageName.c_str())) ;

	this->_bgSprite->setAnchorPoint(ccp(0, 0)) ;
	this->_bgSprite->setPosition(ccp(0, 0)) ;
	this->setContentSize(this->_bgSprite->getContentSize()) ;
	this->addChild(this->_bgSprite, 0) ;

	// 标题Label
	CCLabelTTF* titleLabel = CCLabelTTF::create(this->_title.c_str(), "font01.ttf", 22) ;
	titleLabel->setColor(ccc3(243, 226, 036)) ;
	titleLabel->setAnchorPoint(ccp(0.5, 1)) ;
	titleLabel->setPosition(ccp(this->getContentSize().width/2, this->getContentSize().height-20)) ;
	this->addChild(titleLabel, 1, LABEL_TITLE_TAG) ;

	// 钱label
	char moneyStr[15] ;
	sprintf(moneyStr, "￥:%.2f\0", this->_money) ;
	CCLabelTTF* moneyLabel = CCLabelTTF::create(moneyStr, "font01.ttf", 20) ;
	moneyLabel->setAnchorPoint(ccp(0.5, 0)) ;
	moneyLabel->setPosition(ccp(this->getContentSize().width/2, 15)) ;
	this->addChild(moneyLabel, 1, LABEL_MONEY_TAG) ;

	return true ;
}



/**
*   获取矩形区域
*/
CCRect YJGoodsImageButton::getRect() 
{
	CCSize s =  this->getContentSize() ;
    return CCRectMake(0, 0, s.width, s.height);
}

void YJGoodsImageButton::onEnter() 
{
	CCNode::onEnter() ;
	CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

    // 触摸是否可用
    this->_touchEnabled = true ;
}

void YJGoodsImageButton::onExit() 
{
	CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);

	// 触摸是否可用
    this->_touchEnabled = false ;

	CCNode::onExit() ;
}


/**
*   设置触摸是否可用
*/
void YJGoodsImageButton::setTouchEnabled(bool touchEnabled) 
{
	if(touchEnabled)
	{
		CCDirector* pDirector = CCDirector::sharedDirector();
   	 	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
		this->_touchEnabled = true ;

		CCLog("YJGoodsImageButton::setTouchEnabled --> true") ;
	}
	else
	{
		CCDirector* pDirector = CCDirector::sharedDirector();
    	pDirector->getTouchDispatcher()->removeDelegate(this);
    	this->_touchEnabled = false ;

    	CCLog("YJGoodsImageButton::setTouchEnabled --> false") ;
	}
}

/**
*	是否包含
*/
bool YJGoodsImageButton::containsTouchLocation(CCTouch* touch) 
{
	return CCRect::CCRectContainsPoint(getRect(), convertTouchToNodeSpace(touch));
}

/**
*	开始触摸
*/
bool YJGoodsImageButton::ccTouchBegan(CCTouch* touch, CCEvent* event) 
{
	CCLog("YJGoodsImageButton  ++++++++++++++++++++++++++++++++++++++++++++") ;

	CCPoint point = convertTouchToNodeSpace(touch);
    CCLog("YJGoodsImageButton:clickedAt(%f, %f)", point.x, point.y);

	if(! containsTouchLocation(touch)) {
        return false; 
    } 

    _beginPos = touch->locationInView();  
    CCLog("_beginPos locationInView: x: %f, y: %f", _beginPos.x, _beginPos.y) ;  
    _beginPos = CCDirector::sharedDirector()->convertToGL(_beginPos);
    CCLog("_beginPos convertToGL: x: %f, y: %f", _beginPos.x, _beginPos.y) ;  
    return true;
}

/**
*	触摸结束
*/
void YJGoodsImageButton::ccTouchEnded(CCTouch* touch, CCEvent* event) 
{
	CCLog("YJGoodsImageButton::ccTouchEnded +++++++++++++++++++++++++++++++++");

    
    CCPoint endPos = touch->locationInView();    // 触摸结束的时候，手指所在坐标
    CCLog("endPos locationInView: x: %f, y: %f", endPos.x, endPos.y) ;  
    endPos = CCDirector::sharedDirector()->convertToGL(endPos);
    CCLog("endPos convertToGL: x: %f, y: %f", endPos.x, endPos.y) ; 


    // CCPoint point = convertTouchToNodeSpaceAR(touch);
    CCPoint point = convertTouchToNodeSpace(touch);
    CCLog("YJGoodsImageButton:clickedAt(%f, %f)", point.x, point.y);

    CCLog("YJGoodsImageButton:rect(%f, %f)", getRect().origin.x, getRect().origin.y);

    float delta = 5.0f;
    if (::abs(endPos.x - _beginPos.x) > delta
        || ::abs(endPos.y - _beginPos.y) > delta)
    {
        // not click
        _beginPos.x = _beginPos.y = -1;
        return;
    }

    // 处理被点击（decide the trackNode is clicked.）
    // CCTextFieldTTF* trackNode = NULL ;
    // CCRect rect;


    // 如果当前是普通状态
   

	// 调用回调函数
    if (_pTarget && _pSelector) 
    {
        (_pTarget->*_pSelector)(this);
    }	    

    CCLog("Clicked----------------------------------");
}