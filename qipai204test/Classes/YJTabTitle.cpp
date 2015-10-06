/********************************************************************************
	File: YJTabTitle.cpp
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-06-05
	
	标签Title类，可以换状态图片

********************************************************************************/


/********************************************************************************
	引入需要的头文件信息
********************************************************************************/
#include "YJTabTitle.h"

/********************************************************************************
	using namespace
********************************************************************************/
USING_NS_CC ;

/********************************************************************************
    局部变量声明
********************************************************************************/
// 开始触摸时候的位置
CCPoint beginPos ;



/********************************************************************************
	YJTabTitle 类实现
********************************************************************************/
/**
*	构造函数
*/
YJTabTitle::YJTabTitle() 
{}

/**
*	析构函数
*/
YJTabTitle::~YJTabTitle() 
{
	if (_pTarget)
    {
        _pTarget->release();
    }
}

/**
*   创建一个TabTitle对象
*   @param normalImageName      普通状态下的图片名称
*   @param selectedImageName    选中状态下的图片名称
*   @param displayText          标签上显示的文字信息
*   @param fontName             字体名称
*   @param fontSize             字体大小
*   
*   @return TabTitle对象
*/ 
YJTabTitle* YJTabTitle::create(const char* normalImageName, const char* selectedImageName, YJTabTitleState state, const char* displayText, 
                                const char *fontName, float fontSize, CCObject* target, SEL_CallFuncN selector) 
{

	YJTabTitle *pRet = new YJTabTitle();
    if(pRet && pRet->initWithString(normalImageName, selectedImageName, state, displayText, fontName, fontSize, target, selector))
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
*   @param displayText          标签上显示的文字信息
*   
*   @return TabTitle对象
*/ 
YJTabTitle* YJTabTitle::create(const char* normalImageName, const char* selectedImageName, const char* displayText, CCObject* target, SEL_CallFuncN selector) 
{
	return YJTabTitle::create(normalImageName, selectedImageName, kStateNormal, displayText, "黑体", 28.0f, target, selector) ;
}


/**
*   初始化操作
*/
bool YJTabTitle::initWithString(const char* normalImageName, const char* selectedImageName, YJTabTitleState state, 
						const char* displayText, const char *fontName, float fontSize, CCObject* target, SEL_CallFuncN selector) 
{
	if(!normalImageName)
	{
		return false ;
	}

	if(!selectedImageName)
	{
		return false ;
	}

	if(kStateNormal!=state && kStateSelected!=state)
	{
		return false ;
	}

	if(!displayText)
	{
		return false ;
	}

	if(!fontName)
	{
		return false ;
	}

	this->normalImageName = normalImageName ;
	this->selectedImageName = selectedImageName ;
	this->displayText = displayText ;
	this->fontName = fontName ;
	this->fontSize = fontSize ;

	this->state = state ;	// 设置状态
	this->setTarget(target, selector) ; // 设置回到函数

	CCTextureCache* textureCache = CCTextureCache::sharedTextureCache() ;
	std::string initImageName ;
	if( kStateNormal == state)
	{
		initImageName = normalImageName ;
	}
	else if(kStateSelected == state)
	{
		initImageName = selectedImageName ;
	}

	this->bgSprite = CCSprite::createWithTexture(textureCache->addImage(initImageName.c_str())) ;

	this->bgSprite->setAnchorPoint(ccp(0, 0)) ;
	this->bgSprite->setPosition(ccp(0, 0)) ;
	this->setContentSize(this->bgSprite->getContentSize()) ;
	this->addChild(this->bgSprite, 0) ;

	this->label = CCLabelTTF::create(this->displayText.c_str(), this->fontName.c_str(), this->fontSize) ;
	this->label->setAnchorPoint(ccp(0.5, 0.5)) ;
	this->label->setPosition(ccp(this->getContentSize().width/2, this->getContentSize().height/2)) ;
	this->addChild(this->label, 1) ;

	return true ;
}

/**
*   获取矩形区域
*/
CCRect YJTabTitle::getRect() 
{
	CCSize s =  this->getContentSize() ;
    return CCRectMake(0, 0, s.width, s.height);
}

void YJTabTitle::onEnter()
{
	CCNode::onEnter() ;

	CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void YJTabTitle::onExit()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);

    CCNode::onExit() ;
}


/**
*	是否包含
*/
bool YJTabTitle::containsTouchLocation(CCTouch* touch)
{
	// return CCRect::CCRectContainsPoint(getRect(), convertTouchToNodeSpaceAR(touch));
	return CCRect::CCRectContainsPoint(getRect(), convertTouchToNodeSpace(touch));
}

/**
*	开始触摸
*/
bool YJTabTitle::ccTouchBegan(CCTouch* pTouch, CCEvent* event)
{
	CCLog("YJTabTitle++++++++++++++++++++++++++++++++++++++++++++") ;

	CCPoint point = convertTouchToNodeSpace(pTouch);
    CCLog("YJTabTitle:clickedAt(%f, %f)", point.x, point.y);

	if(! containsTouchLocation(pTouch)) {
        return false; 
    } 

    beginPos = pTouch->locationInView();  
    CCLog("beginPos locationInView: x: %f, y: %f", beginPos.x, beginPos.y) ;  
    beginPos = CCDirector::sharedDirector()->convertToGL(beginPos);
    CCLog("beginPos convertToGL: x: %f, y: %f", beginPos.x, beginPos.y) ;  
    return true;
}

/**
*	触摸结束
*/
void YJTabTitle::ccTouchEnded(CCTouch* pTouch, CCEvent* event)
{
	CCLog("YJTabTitle::ccTouchEnded +++++++++++++++++++++++++++++++++");

    
    CCPoint endPos = pTouch->locationInView();    // 触摸结束的时候，手指所在坐标
    CCLog("endPos locationInView: x: %f, y: %f", endPos.x, endPos.y) ;  
    endPos = CCDirector::sharedDirector()->convertToGL(endPos);
    CCLog("endPos convertToGL: x: %f, y: %f", endPos.x, endPos.y) ; 


    // CCPoint point = convertTouchToNodeSpaceAR(pTouch);
    CCPoint point = convertTouchToNodeSpace(pTouch);
    CCLog("YJTabTitle:clickedAt(%f, %f)", point.x, point.y);

    CCLog("YJTabTitle:rect(%f, %f)", getRect().origin.x, getRect().origin.y);

    float delta = 5.0f;
    if (::abs(endPos.x - beginPos.x) > delta
        || ::abs(endPos.y - beginPos.y) > delta)
    {
        // not click
        beginPos.x = beginPos.y = -1;
        return;
    }

    // 处理被点击（decide the trackNode is clicked.）
    // CCTextFieldTTF* trackNode = NULL ;
    // CCRect rect;


    // 如果当前是普通状态
    if (kStateNormal == this->state)
    {
    	this->setState(kStateSelected) ;
    	// 调用回调函数
	    if (_pTarget && _pSelector) 
	    {
	        (_pTarget->*_pSelector)((CCNode *)this);
	    }	    
     }
    

    CCLog("Clicked----------------------------------");
}





