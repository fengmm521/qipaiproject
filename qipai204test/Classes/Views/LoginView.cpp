/********************************************************************************
	File: LoginView.cpp
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-30
	
	LoginView 类实现

********************************************************************************/

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/
#include "LoginView.h"
#include "GameMenuView.h"


/********************************************************************************
    局部方法声明
********************************************************************************/

static CCRect getRect(CCNode * pNode)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize() ;

    CCRect rc;
    rc.origin = pNode->getPosition();
    rc.size = pNode->getContentSize();
    rc.origin.x -= winSize.width / 2;
    rc.origin.y -= winSize.height / 2;
    return rc;
}

/********************************************************************************
	LoginView 类实现
********************************************************************************/
/**
*	构造函数
*/
LoginView::LoginView() 
{
	
}

/**
*	析造函数
*/
LoginView::~LoginView() 
{}

/**
*	创建该界面依赖的场景对象
*/
CCScene* LoginView::CreateScene() 
{
	CCScene* scene = CCScene::create() ;

	LoginView* layer = LoginView::create() ;
	scene->addChild(layer) ;

	return scene ;
}

/**
*	初始化方法，继承CCLayer的方法
*/
bool LoginView::init() 
{
	if(!CCLayer::init())
	{
		return false ;
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize() ;

	// 背景
	CCSprite* downBg = CCSprite::create("bg_welcome.png") ;
	downBg->setAnchorPoint(ccp(0.5, 0)) ;
	downBg->setPosition(ccp(winSize.width/2, 0)) ;
	this->addChild(downBg, 0) ;

	// 加载logo
	CCSprite* logo = CCSprite::create("logo_01.png") ;
	logo->setAnchorPoint(ccp(0.5, 0.5)) ;
	logo->setPosition(ccp(winSize.width/2, winSize.height/2+35)) ;
	this->addChild(logo, 1) ;

	///////////////////////////////// 输入框 ////////////////////////////////////////
	
	const float input_width = 213.0f ;
	const float input_height = 39.0f ;  
    const float labelNode_padding = 8.0f ;
    const float labelNode_width = winSize.width/3 ;
	const float labelNode_height = 2*input_height+labelNode_padding ;	
	
	CCNode* labelNode = CCNode::create() ;
	labelNode->setContentSize(CCSizeMake(labelNode_width, labelNode_height)) ;
	labelNode->setAnchorPoint(ccp(0.5, 0)) ;
	labelNode->setPosition(ccp(winSize.width/2-5, 85)) ;
	this->addChild(labelNode, 2) ;

	CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create("bg_textfield.png") ;

    // 用户名
    CCSprite* txtUsernameBg = CCSprite::createWithTexture(batchNode->getTexture()) ;
    txtUsernameBg->setAnchorPoint(ccp(0, 0)) ;
    txtUsernameBg->setPosition(ccp(0, input_height+labelNode_padding)) ;
    labelNode->addChild(txtUsernameBg, 0) ;

    this->txtUsername = CCTextFieldTTF::textFieldWithPlaceHolder("Username", CCSizeMake(input_width, input_height),
                                                                kCCTextAlignmentLeft, "font01.ttf", 26.0f) ;
    this->txtUsername->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ;
    this->txtUsername->setAnchorPoint(ccp(0, 0.5)) ;
    this->txtUsername->setPosition(ccp((winSize.width-labelNode_width)/2+5, 85+labelNode_height*3/4)) ;
    this->addChild(this->txtUsername, 3) ;

	// 密码
    CCSprite* txtPasswordBg = CCSprite::createWithTexture(batchNode->getTexture()) ;
    txtPasswordBg->setAnchorPoint(ccp(0, 0)) ;
    txtPasswordBg->setPosition(ccp(0, 0)) ;
    labelNode->addChild(txtPasswordBg, 0) ;

    this->txtPassword = CCTextFieldTTF::textFieldWithPlaceHolder("Password", CCSizeMake(input_width, input_height),
                                                                kCCTextAlignmentLeft, "font01.ttf", 26.0f) ;
    this->txtPassword->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ;
    this->txtPassword->setAnchorPoint(ccp(0, 0.5)) ;
    this->txtPassword->setPosition(ccp((winSize.width-labelNode_width)/2+5, 85+labelNode_height/4-2)) ;
    this->addChild(this->txtPassword,3) ;

    // 登录按钮
    CCMenuItemImage* loginMenuItem = CCMenuItemImage::create("menu_login_n.png", "menu_login_s.png", this, menu_selector(LoginView::menuLoginCallback)) ;
    loginMenuItem->setAnchorPoint(ccp(0, 0)) ;
    loginMenuItem->setPosition(ccp(0, input_height+labelNode_padding)) ;

    // 注册按钮
    CCMenuItemImage* registeMenuItem = CCMenuItemImage::create("menu_registe_n.png", "menu_registe_s.png", this, menu_selector(LoginView::menuRegisteCallback)) ;
    registeMenuItem->setAnchorPoint(ccp(0, 0)) ;
    registeMenuItem->setPosition(ccp(0, 0)) ;

    CCMenu* loginMenu = CCMenu::create(loginMenuItem, registeMenuItem, NULL) ;
    loginMenu->setAnchorPoint(ccp(0, 0)) ;
    loginMenu->setPosition(ccp(input_width+10, -5)) ;
    labelNode->addChild(loginMenu) ;


    // //////////////////////////////////////////////////////////////////////////////////////////////
    const float loginNode_padding = 11.0f ;
	const float loginNode_margin_bottom = 32.0f ;
    const float menu_item_width = 101.0f ;
	
    CCNode* optionNode = CCNode::create() ;
    optionNode->setContentSize(CCSizeMake(winSize.width/3, 50)) ;
    optionNode->setAnchorPoint(ccp(0.5, 0)) ;
    optionNode->setPosition(ccp(winSize.width/2-5, loginNode_margin_bottom)) ;
    this->addChild(optionNode, 1) ;

    // 游客登录
    CCMenuItemImage* guestLoginItem = CCMenuItemImage::create("menu_guest_login_n.png", "menu_guest_login_s.png", this, menu_selector(LoginView::menuGuestLoginCallback)) ;
    guestLoginItem->setAnchorPoint(ccp(0, 0)) ;
    guestLoginItem->setPosition(ccp(0, 0)) ;

    // 忘记密码
    CCMenuItemImage* forgetPwdItem = CCMenuItemImage::create("menu_forget_pwd_n.png", "menu_forget_pwd_s.png", this, menu_selector(LoginView::menuForgetPwdCallback)) ;
    forgetPwdItem->setAnchorPoint(ccp(0, 0)) ;
    forgetPwdItem->setPosition(ccp(menu_item_width+loginNode_padding, 0)) ;

	
    // go
    CCMenuItemImage* goMenuItem = CCMenuItemImage::create("menu_go_n.png", "menu_go_s.png", this, menu_selector(LoginView::menuGoCallback)) ;
    goMenuItem->setAnchorPoint(ccp(0, 0)) ;
    goMenuItem->setPosition(ccp(2*(menu_item_width+loginNode_padding), 0)) ;

    CCMenu* goMenu = CCMenu::create(guestLoginItem, forgetPwdItem, goMenuItem, NULL) ;
    goMenu->setAnchorPoint(ccp(0, 0)) ;
    goMenu->setPosition(ccp(0, 0)) ;
    optionNode->addChild(goMenu) ;
/*
    /////////////////////////////////////////////////////////////////////////////////////////////
    CCLabelTTF* tipLabel = CCLabelTTF::create("小提示：在游戏中达到规定时间，可以获取神秘大奖哦！", CCSizeMake(winSize.width, 45), 
                                                    kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter, "font01.ttf", 22.0f) ;
    tipLabel->setAnchorPoint(ccp(0.5, 0)) ;
    tipLabel->setPosition(ccp(winSize.width/2, 20)) ;
    this->addChild(tipLabel, 2) ;
*/

    // 接收键盘点击事件
    this->setKeypadEnabled(true) ;

    // 触摸可使用
    this->setTouchEnabled(true);

	return true ;
}

void LoginView::onEnter() 
{
    CCLayer::onEnter() ;

    this->mTrackNodeArray = CCArray::createWithCapacity(2) ;
    this->mTrackNodeArray->retain() ;
    this->mTrackNodeArray->addObject(this->txtUsername) ;
    this->mTrackNodeArray->addObject(this->txtPassword) ;
}

void LoginView::onExit() 
{
    CCLayer::onExit() ;
    this->mTrackNodeArray->removeAllObjects() ;
    this->mTrackNodeArray->release() ;

    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
}


/**
 * 处理返回键事件
 */
void LoginView::keyBackClicked() 
{
	// 结束游戏
 	CCDirector::sharedDirector()->end() ;
}

/**
*	第一进度回调
*/
void LoginView::firstProgressCallBack() 
{

}

/**
*	第二进度回调
*/
void LoginView::secondProgressCallBack() 
{

}

/**
*	第三进度回调
*/
void LoginView::thirdProgressCallBack() 
{

}

/**
*   登录菜单项的点击事件
*/
void LoginView::menuLoginCallback(CCObject* pSender) 
{
    CCLog("LoginView login menu item Clicked!") ;
    // 跳转到游戏大厅
    CCDirector::sharedDirector()->replaceScene(GameMenuView::CreateScene()) ;
}

/**
*   注册菜单项的点击事件
*/
void LoginView::menuRegisteCallback(CCObject* pSender)
{}

/**
*   游客登录菜单项的点击事件
*/
void LoginView::menuGuestLoginCallback(CCObject* pSender)
{   
    // 跳转到游戏大厅
    CCDirector::sharedDirector()->replaceScene(GameMenuView::CreateScene()) ;
}

/**
* 忘记密码菜单项点击事件
*/
void LoginView::menuForgetPwdCallback(CCObject* pSender) 
{

}

/**
*   Go菜单项的点击事件
*/
void LoginView::menuGoCallback(CCObject* pSender) 
{
    CCLog("LoginView go menu item Clicked!") ;
}

/**
*   注册触摸事件分发器
*/
void LoginView::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}


/**
*   键盘将要出现的时候
*/
void LoginView::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
{
    CCLog("LoginView:keyboardWillShowAt(origin:%f,%f, size:%f,%f)",
        info.end.origin.x, info.end.origin.y, info.end.size.width, info.end.size.height);

    if (! this->mTrackNodeArray)
    {
        return;
    }

    CCNode* trackNode = NULL ;
    CCRect rectTracked ;
    for(int i=0; i<this->mTrackNodeArray->count(); i++) 
    {
        trackNode = (CCNode*) this->mTrackNodeArray->objectAtIndex(i) ;

        rectTracked = getRect(trackNode);
        CCLog("LoginView:trackingNodeAt(origin:%f,%f, size:%f,%f)",
            rectTracked.origin.x, rectTracked.origin.y, rectTracked.size.width, rectTracked.size.height);

        // if the keyboard area doesn't intersect with the tracking node area, nothing need to do.
        if (! CCRect::CCRectIntersectsRect(rectTracked, info.end))
        {
            continue ;
        }

        // assume keyboard at the bottom of screen, calculate the vertical adjustment.
        float adjustVert = info.end.getMaxY() - rectTracked.getMinY();
        CCLog("LoginView:needAdjustVerticalPosition(%f)", adjustVert);

        // move all the children node of KeyboardNotificationLayer
        CCArray* children = getChildren();
        CCNode* node = 0;
        int count = children->count();
        CCPoint pos;
        for (int i = 0; i < count; ++i)
        {
            node = (CCNode*)children->objectAtIndex(i);
            pos = node->getPosition();
            pos.y += adjustVert;
            node->setPosition(pos);
        }
    }

    
}

// CCLayer function
bool LoginView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLog("++++++++++++++++++++++++++++++++++++++++++++") ;

    mBeginPos = pTouch->locationInView();    
    mBeginPos = CCDirector::sharedDirector()->convertToGL(mBeginPos);
    return true;
}

void LoginView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

    CCLog("LoginView::ccTouchEnded +++++++++++++++++++++++++++++++++");

    if (! mTrackNodeArray)
    {
        CCLog("track node is null +++++++++++");
        return;
    }
    
    CCPoint endPos = pTouch->locationInView();    // 触摸结束的时候，手指所在坐标
    endPos = CCDirector::sharedDirector()->convertToGL(endPos);

    float delta = 5.0f;
    if (::abs(endPos.x - this->mBeginPos.x) > delta
        || ::abs(endPos.y - this->mBeginPos.y) > delta)
    {
        // not click
        mBeginPos.x = this->mBeginPos.y = -1;
        return;
    }

    // 处理被点击（decide the trackNode is clicked.）
    CCTextFieldTTF* trackNode = NULL ;
    CCRect rect;
    CCPoint point = convertTouchToNodeSpaceAR(pTouch);
    CCLog("LoginView:clickedAt(%f, %f)", point.x, point.y);

    for(int i=0; i<this->mTrackNodeArray->count(); i++)
    {
        CCLog("track index is: %d", i) ;
        trackNode = (CCTextFieldTTF*) this->mTrackNodeArray->objectAtIndex(i) ;

        rect = getRect(trackNode); // 得到节点的矩形框
        CCLog("LoginView:TrackNode at(origin:%f,%f, size:%f,%f)",
            rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);

        // 处理跟踪节点
        this->onClickTrackNode(trackNode, CCRect::CCRectContainsPoint(rect, point));
        
    }

    CCLog("----------------------------------");

    
}

void LoginView::onClickTrackNode(CCTextFieldTTF* txt, bool bClicked)
{
    // CCTextFieldTTF * pTextField = (CCTextFieldTTF*)mTrackNode;
    if (bClicked)
    {
        // TextFieldTTFTest be clicked
        CCLog("LoginView:CCTextFieldTTF attachWithIME");
        txt->attachWithIME();
    }
    else
    {
        // TextFieldTTFTest not be clicked
        CCLog("LoginView:CCTextFieldTTF detachWithIME");
        txt->detachWithIME();
    }
}