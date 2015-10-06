/********************************************************************************
	File: GameGroundView.cpp
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-22
	
	类GameGroundView的实现

********************************************************************************/

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/

#include "GameGroundView.h"
#include "GameMenuView.h"
#include "GamePlayerRight.h"
#include "GamePlayerLeft.h"
#include "GamePlayerCenter.h"
// #include "YJMenuItemImage.h"

/********************************************************************************
	宏定义
********************************************************************************/
#define BOTTOM_PLAYER_OPERATION_MENU 			0x110	// 用户操作菜单


/********************************************************************************
	变量定义
********************************************************************************/
// 机器人和玩家集合
CCArray* playerArray ;

// 发牌动作集合
CCArray* actionArray ;

// 运行的action
CCAction* willRunAction ; 

// 玩家操作菜单
CCMenu* playerOperationMenu ;

// 庄家索引
int bankerIndex = 0 ; 

// 上次的赢家
int winPlayerIndex = bankerIndex ;

// 当前玩家索引
int currentPlayerIndex = bankerIndex ;

//当前发牌的人索引
int providerIndex = bankerIndex ;

// 发牌轮数,没人三张牌，就是三轮发牌
int providerTurn = 0 ;

// 单注，默认是100
DWORD singleBet = 100 ;

// 总注，开始为0
DWORD totalBet = 0 ;

// 总轮数
int totalTurns = 20 ;

// 当前轮数
int currentTurn = 1 ;

GameState state = kInitialGame ;

/********************************************************************************
	GameGroundView 类实现
********************************************************************************/
/**
 *	构造函数  	
 */
GameGroundView::GameGroundView()
{
}
/**
 * 析构函数
 */
GameGroundView::~GameGroundView() 
{
	
	if(playerArray) {
		playerArray->release() ;
	}

	if(willRunAction) 
	{
		willRunAction->release() ;
	}

	if(actionArray) {
		actionArray->release() ;
	}

	if(gameLogic)
	{
		gameLogic->release() ;
	}
	
}

/**
 * 	创建展示该Layer的场景对象
 *	@return 返回加入了该Layer的场景对象
 */
CCScene* GameGroundView::CreateScene() 
{
	CCScene* scene = CCScene::create() ;

	GameGroundView* ggLayer = GameGroundView::create() ;

	scene->addChild(ggLayer) ;

	return scene ;
}

/**
 *	初始化函数，这个函数在CCLayer类的create方法中调用
 * 	@return 初始化成功返回true，否者返回false
 */
bool GameGroundView::init() 
{
	if(!CCLayer::init())
	{
		return false ;
	}

	playerArray =  CCArray::createWithCapacity(5) ;
	playerArray->retain() ;

	actionArray = CCArray::createWithCapacity(7) ;
	actionArray->retain() ;

	CCSize size = CCDirector::sharedDirector()->getWinSize() ;

	// 初始化背景
	initBg(size) ;

	// 初始化顶部条
	initTopBar(size) ;

	// 初始化底部条
	initBottomMenu(size) ;

	// 初始化机器人和玩家
	initPlayers(size) ;
	
	// 初始化发牌动作
	initActions(size) ;


	/////////////////////////////////////// 准备菜单 //////////////////////////////////////
	CCMenu* menu = CCMenu::create() ;
	menu->setAnchorPoint(ccp(0, 0)) ;
	menu->setPosition(ccp(0, 0)) ;
	this->addChild(menu, 1) ;


	// 准备菜单项
	CCMenuItemImage* readyMenuItem = CCMenuItemImage::create("menu_ready_n.png", "menu_ready_s.png", this,
															menu_selector(GameGroundView::menuReadyClickCallback)) ;
	readyMenuItem->setAnchorPoint(ccp(0.5, 0.5)) ;
	readyMenuItem->setPosition(ccp(size.width/2, size.height/2)) ;
	// CCLog("readyMenuItem width: %d, readyMenuItem height: %d", readyMenuItem->rect().size.width, readyMenuItem->rect().size.height) ;
	menu->addChild(readyMenuItem) ;


	// 游戏逻辑
	this->gameLogic = new GameLogic() ;



	// 筹码所在区域
	this->jetonAreaNode = CCNode::create() ;
	this->jetonAreaNode->setContentSize(CCSizeMake(JETON_AREA_WIDTH, JETON_AREA_HEIGHT)) ;
	this->jetonAreaNode->setAnchorPoint(ccp(0, 0)) ;
	this->jetonAreaNode->setPosition(ccp(size.width/3, size.height/2)) ;

	// 随机得到庄家
	bankerIndex = rand() % GAME_PLAYER_COUNT ;

	CCLog("bankerIndex is :%d", bankerIndex) ;

	winPlayerIndex = bankerIndex ;

	providerIndex = bankerIndex ;

	currentPlayerIndex = bankerIndex ;

	// 新游戏
	newGame() ;

	this->setKeypadEnabled(true) ;


	return true ;
}


void GameGroundView::onEnter() 
{
	CCLayer::onEnter() ;

	// 获取玩家操作菜单
	playerOperationMenu = (CCMenu*) this->bottomBar->getChildByTag(BOTTOM_PLAYER_OPERATION_MENU) ;
	playerOperationMenu->retain() ;
}

void GameGroundView::onExit() 
{
	// 释放玩家操作菜单
	playerOperationMenu->release() ;

	CCLayer::onExit() ;
}

// 累加总注
void GameGroundView::appendTotalBet(DWORD bet) 
{
	totalBet += bet ;
	char str[15]  ;
	sprintf(str, "总注:%d\0", totalBet) ;
	this->allBetLabel->setString(str) ;
}

// 新游戏，用来初始化和调整参数使用
void GameGroundView::newGame() 
{
	// 游戏状态
	state = kInitialGame ;

	// 设置单注为100
	singleBet = 100 ;
	char str[15]  ;
	sprintf(str, "单注:%d\0", singleBet) ;
	this->singleBetLabel->setString(str) ;

	// 设置总注为0
	totalBet = 0 ;
	sprintf(str, "总注:%d\0", totalBet) ;
	this->allBetLabel->setString(str) ;
}

// 设置单注
void GameGroundView::setSingleBet(DWORD bet) 
{
	singleBet = bet ;
	char str[15]  ;
	sprintf(str, "单注:%d\0", singleBet) ;
	this->singleBetLabel->setString(str) ;
}

// 下一玩家
void GameGroundView::nextPlayer() 
{
	currentPlayerIndex = (++currentPlayerIndex) % GAME_PLAYER_COUNT ;
	CCLog("nextPlayer -> currentPlayerIndex:%d", currentPlayerIndex) ;
}


// 显示玩家操作菜单
void  GameGroundView::showPlayerOperationMenu() 
{
	CCAction* action = CCMoveTo::create(0.5, 
						ccp(0, (this->bottomBar->getContentSize().height-playerOperationMenu->getContentSize().height )/2)) ;
	playerOperationMenu->runAction(action) ;
}

// 隐藏玩家操作菜单
void  GameGroundView::hidePlayerOperationMenu() 
{
	CCAction* action = CCMoveTo::create(0.5, 
						ccp(0, -this->bottomBar->getContentSize().height) ) ;
	playerOperationMenu->runAction(action) ;
}

/**
 * 处理返回键事件
 */
void GameGroundView::keyBackClicked() 
{
	// CCScene* scene = CCTransitionFlipX::create(0.8f, GameMenuView::CreateScene(), kOrientationRightOver) ;
 //    CCDirector::sharedDirector()->replaceScene(scene) ;
	CCDirector::sharedDirector()->replaceScene(GameMenuView::CreateScene()) ;
}

/**
*	返回按钮点击事件处理函数
*/
void GameGroundView::menuBackClickCallback(CCObject* pSender) 
{
	// CCScene* scene = CCTransitionFlipX::create(0.8f, GameMenuView::CreateScene(), kOrientationRightOver) ;
	// CCDirector::sharedDirector()->replaceScene(scene) ;
	CCDirector::sharedDirector()->replaceScene(GameMenuView::CreateScene()) ;
}

/**
*	准备按钮点击事件处理函数
*/
void GameGroundView::menuReadyClickCallback(CCObject* pSender) 
{

	schedule(schedule_selector(GameGroundView::startingGameSchedule)) ;
	// 隐藏 准备 按钮
	((CCNode*)pSender)->setVisible(false) ;
}

/**
*	开始游戏
*/
void GameGroundView::startingGameSchedule() 
{
	CCLog("starting schedule -------> ") ;

	switch(state)
	{
		case kInitialGame:
		{
			CCLog("kInitialGame -------> ") ;
			// 下底注
			state = kBetBasic ;

			GamePlayer* gamePlayer = NULL ;
			CCLog("playerArray count is %d", playerArray->count()) ;
			// 显示投注信息
			for(int i=0; i<playerArray->count(); i++)
			{
				gamePlayer = (GamePlayer*) playerArray->objectAtIndex(i) ;

				gamePlayer->retain() ;
				gamePlayer->setState(kPrepareReady) ; // 准备好状态
				// 1、下注
				gamePlayer->betOn(singleBet) ;				

				// 累计总注
				appendTotalBet(singleBet) ;

				//gamePlayer->setVisible(false) ;
				gamePlayer->release() ;
			}
			CCLog("kInitialGame end -------> ") ;
			break ;
		}
		case kBetBasic: // 下底注
		{
			CCLog("kBetBasic -------> ") ;
			state = kProvideCard ;
			// 2、发牌动作, 发牌结束后会设置游戏状态为kTurn
			provideCard() ;
			break ;
		}

		case kProvideCard: // 发牌
		{	
			CCLog("kProvideCard -------> ") ;	
			break ;
		}
		case kTurn: // 开始游戏
		{
			// 闪烁
			GamePlayer* gamePlayer = (GamePlayer*) playerArray->objectAtIndex(currentPlayerIndex) ;

			if(kGiveUpCard == gamePlayer->getState()) // 玩家已经放弃牌
			{
				nextPlayer() ;
				return ;
			}

			if(kWaitBet != gamePlayer->getState())  // 非等下注状态
			{
				// 判断是否只剩下当前玩家，如果是，那么就表示已经赢了
				int count = 0 ;
				
				// 取得当前没有放弃牌的机器人和玩家的数量
				GamePlayer* player = NULL ;
				for(int i=0; i<playerArray->count(); i++)
				{
					player = (GamePlayer*) playerArray->objectAtIndex(i) ;
					if(kGiveUpCard != player->getState()) 
					{
						count ++ ;
					}
				}

				// 没有放弃牌的玩家和机器人数量为 1
				if(count == 1) { // 当前玩家已经赢了
					gamePlayer->win(totalBet) ;
					gamePlayer->hideBetCoin() ;
					gamePlayer->hideAllCard() ;
					// 赢家
					winPlayerIndex = currentPlayerIndex ;

					// 顺时针轮庄
					if(bankerIndex>0) 
					{
						bankerIndex-- ;
					}
					else 
					{
						bankerIndex = GAME_PLAYER_COUNT-1 ;
					}

					// 赢家的逆时针下一家叫注
					currentPlayerIndex = ++winPlayerIndex % GAME_PLAYER_COUNT ; 

					// 开始发牌的索引
					providerIndex = bankerIndex ;

					// 新游戏
					newGame() ;
					return ;
				}

				// 设置玩家的状态为等待下注状态
				gamePlayer->setState(kWaitBet) ;

				// 如果当前轮到 玩家进行操作，那么现实操作菜单
				if(4 == currentPlayerIndex)  // 等待玩家操作
				{
					// 显示 操作菜单
					showPlayerOperationMenu() ;
				}

				// 标识一下当前 那个用户或者玩家进行下注
				CCAction* action = (CCAction*) actionArray->objectAtIndex(6) ;
				gamePlayer->focus(action) ; // 闪烁头像
			}


			// 操作
			if(kWaitBet == gamePlayer->getState()) // 等待下注状态
			{
				// 执行智能操作

			}
			
			break ;
		}

		default:
			break ;
	}

	CCLog("end schedule -------> ") ;
}

/**
*	设置按钮点击事件处理函数
*/
void GameGroundView::menuSettingClickCallback(CCObject* pSender) 
{	
	
	
}

// 发牌
void GameGroundView::provideCard() 
{
	CCActionManager* actionManager = this->cardAnimate->getActionManager() ;

	CCLog("provideCard bankerIndex is : %d", bankerIndex) ;

	// 动画序列数组
	CCArray* tempActionArray = CCArray::createWithCapacity(5) ;
	for(int i=0; i<3; i++) {
		for(int j=0; j<5; j++)
		{
			tempActionArray->addObject(actionArray->objectAtIndex((bankerIndex+j)%5 )) ;
		}
	}
	tempActionArray->addObject(actionArray->objectAtIndex(5 )) ;

	willRunAction = CCSequence::create(tempActionArray) ;
    willRunAction->retain() ;
    
    actionManager->addAction(willRunAction, this->cardAnimate, false) ;

    // 发牌
    BYTE cardDataList[GAME_PLAYER_COUNT * MAX_COUNT] ;
    // 随机获取15张牌
    this->gameLogic->RandCardList(cardDataList, GAME_PLAYER_COUNT * MAX_COUNT) ;

    BYTE cardThree[MAX_COUNT] ;
    // 庄家
    GamePlayer* gamePlayer ;
    for(int i=0; i<GAME_PLAYER_COUNT; i++) {
	    GamePlayer* gamePlayer = (GamePlayer*) playerArray->objectAtIndex((bankerIndex+i)%GAME_PLAYER_COUNT ) ;
	    memcpy(cardThree, cardDataList+i*MAX_COUNT, MAX_COUNT) ;
	    gamePlayer->setCard(cardThree) ;
	    gameLogic->SortCardList(gamePlayer->getCard(), MAX_COUNT) ;

	    CCLog("after sort card is : %x %x %x", gamePlayer->getCard()[0], gamePlayer->getCard()[1], gamePlayer->getCard()[2]) ;
    }
}

/**
*	发每张牌后调用的函数
*/
void GameGroundView::provideCardCallback() 
{
	GamePlayer* player = (GamePlayer*) playerArray->objectAtIndex(providerIndex) ;
	player->provideCard(providerTurn) ;

	providerIndex = ++providerIndex % 5 ;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize() ;
	cardAnimate->setPosition(ccp(winSize.width/2, winSize.height)) ;

	// 一圈牌已经发完，进行下一圈
	if(providerIndex == bankerIndex) 
	{
		providerTurn = ++providerTurn % 3 ;
	}
}

/**
*	发完牌后调用的函数
*/
void GameGroundView::provideCardFinishedCallback() 
{
	CCActionManager* actionManager = this->cardAnimate->getActionManager() ;
	if(willRunAction) 
	{
		actionManager->removeAllActionsFromTarget(this->cardAnimate) ;
		willRunAction->release() ;
	}

	// 游戏状态为开始游戏
	state = kTurn ;	
}

// 等待下注结束
void GameGroundView::waitBetFinishedCallback() 
{
	GamePlayer* gamePlayer = (GamePlayer*) playerArray->objectAtIndex(currentPlayerIndex) ;
	if(kWaitBet == gamePlayer->getState())
	{
		gamePlayer->setState(kGiveUpCard) ;
		
		// 当前轮到的是玩家
		if(4 == currentPlayerIndex) 
		{
			// 隐藏操作菜单
			hidePlayerOperationMenu() ;

		}

		// 下一个玩家
		nextPlayer() ;

		CCLog("GameGroundView::waitBetFinishedCallback") ;
	}
}

/**
*	礼物按钮点击事件处理函数
*/
void GameGroundView::menuGiftsClickCallback(CCObject* pSender) 
{}


/**
*	跟注菜单点击事件处理函数
*/
void GameGroundView::menuFollowBetClickCallback(CCObject* pSender) 
{}

/**
*	加注菜单点击事件处理函数
*/
void GameGroundView::menuAddBetClickCallback(CCObject* pSender) 
{}

/**
*	看牌菜单点击事件处理函数
*/
void GameGroundView::menuLookCardClickCallback(CCObject* pSender) 
{}

/**
*	比牌菜单点击事件处理函数
*/
void GameGroundView::menuCompareCardClickCallback(CCObject* pSender) 
{}

/**
*	放弃菜单点击事件处理函数
*/
void GameGroundView::menuGiveupClickCallback(CCObject* pSender) 
{}


void GameGroundView::initActions(CCSize winSize)
{
	// 模拟发牌
	cardAnimate = CCSprite::create("card/card_back.png") ;
	cardAnimate->setAnchorPoint(ccp(0.5, 0)) ;
	cardAnimate->setPosition(ccp(winSize.width/2, winSize.height)) ;
	// cardAnimate->setScale(0.8) ;
	this->addChild(cardAnimate, 4) ;


	CCAction* action = NULL ;
	// 机器人1 的发牌动作
	action = CCSequence::create(CCMoveTo::create(PROVIDECARD_DURATION, ccp(winSize.width*3/4, winSize.height/3+20)), 
                        				   CCCallFuncN::create(this, callfuncN_selector(GameGroundView::provideCardCallback))) ;
    actionArray->addObject(action) ;

    // 机器人2 的发牌动作
    action = CCSequence::create(CCMoveTo::create(PROVIDECARD_DURATION, ccp(winSize.width*3/4, winSize.height*2/3)), 
                        				   CCCallFuncN::create(this, callfuncN_selector(GameGroundView::provideCardCallback))) ;
    actionArray->addObject(action) ;

    // 机器人3 的发牌动作
    action = CCSequence::create(CCMoveTo::create(PROVIDECARD_DURATION, ccp(winSize.width/4, winSize.height*2/3)), 
                        				   CCCallFuncN::create(this, callfuncN_selector(GameGroundView::provideCardCallback))) ;
    actionArray->addObject(action) ;

    // 机器人4 的发牌动作
    action = CCSequence::create(CCMoveTo::create(PROVIDECARD_DURATION, ccp(winSize.width/4, winSize.height/3+20)), 
                        				   CCCallFuncN::create(this, callfuncN_selector(GameGroundView::provideCardCallback))) ;
    actionArray->addObject(action) ;

    // 玩家 的发牌动作
    action = CCSequence::create(CCMoveTo::create(PROVIDECARD_DURATION, ccp(winSize.width/2, winSize.height/3)), 
                        				   CCCallFuncN::create(this, callfuncN_selector(GameGroundView::provideCardCallback))) ;
    actionArray->addObject(action) ;
  	
  	// 当发牌完毕后执行的操作
  	action = CCCallFuncN::create(this, callfuncN_selector(GameGroundView::provideCardFinishedCallback)) ;
  	actionArray->addObject(action) ;

  	// 等待玩家操作的Action
  	action = CCSequence::create(CCBlink::create(10, 20), CCCallFuncN::create(this, callfuncN_selector(GameGroundView::waitBetFinishedCallback)) ) ;
  	actionArray->addObject(action) ;
}

// 初始化背景
void GameGroundView::initBg(CCSize size) 
{
	/******* 背景 ******************************************************/
	CCSprite* bg = CCSprite::create("bg_land.png") ;
	bg->setPosition(ccp(size.width/2, size.height/2) ) ;
	this->addChild(bg, 0) ; 		// 作为背景加入到Layer中

	CCSprite* table = CCSprite::create("bg_table.png") ;
	table->setPosition(ccp(size.width/2, size.height/2)) ;
	this->addChild(table, 0) ;
}

// 初始化顶部条
void GameGroundView::initTopBar(CCSize size) 
{
	/////////////////////////////////////// 顶部条 /////////////////////////////////////////

	// 顶部条背景
	CCSprite* topBarBg = CCSprite::create("bg_nav_top.png") ;
	topBarBg->setAnchorPoint(ccp(0.5, 0)) ;
	topBarBg->setPosition(ccp(size.width/2, 0)) ;

	const float topBar_height = topBarBg->getContentSize().height ;	// topBar高
	const float topBar_width = size.width ;							// topBar宽
	const float margin_left_right = 20.0f ;
	const float padding = 10.0f ;									// 间距

	// 初始化TopBarNode
	this->topBar = CCNode::create() ;
	topBar->setContentSize(topBarBg->getContentSize()) ;
	topBar->setAnchorPoint(ccp(0.5, 1) ) ;
	topBar->setPosition(ccp(size.width/2, size.height)) ;
	this->addChild(topBar, 1) ;

	// 将背景加入到topBarNode中
	this->topBar->addChild(topBarBg, 0) ;

	// 单注图标
	CCSprite* singleIcon = CCSprite::create("icon_single_bet.png") ;
	singleIcon->setAnchorPoint(ccp(0, 0.5)) ;
	singleIcon->setPosition(ccp(margin_left_right, topBar_height/2)) ;
	this->topBar->addChild(singleIcon, 1) ; 

	// 单注
	singleBetLabel = CCLabelTTF::create("单注:1800", "font01.ttf", 22.0f) ;
	singleBetLabel->setAnchorPoint(ccp(0, 0)) ;
	singleBetLabel->setPosition(ccp(margin_left_right+5+ singleIcon->getContentSize().width, topBar_height/2)) ;
	singleBetLabel->setHorizontalAlignment(kCCTextAlignmentLeft) ; 			// 水平对齐方式
	singleBetLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ; 	// 垂直对齐方式
	this->topBar->addChild(singleBetLabel, 1) ;

	// 可比轮数
	CCLabelTTF* enableTurnLabel = CCLabelTTF::create("可比轮数:1/3", "font01.ttf", 18.0f) ;
	enableTurnLabel->setAnchorPoint(ccp(0, 1)) ;
	enableTurnLabel->setPosition(ccp(margin_left_right+5+ singleIcon->getContentSize().width, topBar_height/2)) ;
	enableTurnLabel->setHorizontalAlignment(kCCTextAlignmentLeft) ; 			// 水平对齐方式
	enableTurnLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ; 	// 垂直对齐方式
	this->topBar->addChild(enableTurnLabel, 1) ;

	// 总注图标

	CCSprite* totalIcon = CCSprite::create("icon_total_bet.png") ;
	totalIcon->setAnchorPoint(ccp(0, 0.5)) ;
	totalIcon->setPosition(ccp(200, topBar_height/2)) ;
	this->topBar->addChild(totalIcon, 1) ;

	// 总注
	allBetLabel = CCLabelTTF::create("总注:1800", "font01.ttf", 22.0f) ;
	allBetLabel->setAnchorPoint(ccp(0, 0)) ;
	allBetLabel->setPosition(ccp(205+totalIcon->getContentSize().width, topBar_height/2)) ;
	allBetLabel->setHorizontalAlignment(kCCTextAlignmentLeft) ; 			// 水平对齐方式
	allBetLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ; 	// 垂直对齐方式
	this->topBar->addChild(allBetLabel, 1) ;

	// 最大轮数
	CCLabelTTF* maxTurnsLabel = CCLabelTTF::create("最大轮数:1/20", "font01.ttf", 18.0f) ;
	// maxTurnsLabel->setColor(ccc3(0, 0, 0)) ;
	maxTurnsLabel->setAnchorPoint(ccp(0, 1)) ;
	maxTurnsLabel->setPosition(ccp(205+totalIcon->getContentSize().width, topBar_height/2)) ;
	maxTurnsLabel->setHorizontalAlignment(kCCTextAlignmentLeft) ; 			// 水平对齐方式
	maxTurnsLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter) ; 	// 垂直对齐方式
	this->topBar->addChild(maxTurnsLabel, 1) ;



	// 右侧menu
	const float right_width = 200 ;
	const float item_width = 55 ;

	
	// 礼物
	CCMenuItemImage* menuGifts = CCMenuItemImage::create("menu_gifts_n.png", "menu_gifts_s.png", this,
															menu_selector(GameGroundView::menuGiftsClickCallback)) ;
	// menuBack->setContentSize(CCSizeMake(67, 68)) ;
	menuGifts->setAnchorPoint(ccp(0, 0.5)) ;
	menuGifts->setPosition(ccp(0, topBar_height/2)) ;
	//menuGifts->setPosition(ccp(right_width-2*item_width, topBar_height/2)) ;
	//rightMenu->addChild(menuGifts) ;

	

	// 设置
	CCMenuItemImage* menuSetting = CCMenuItemImage::create("menu_setting_n.png", "menu_setting_s.png", this,
															menu_selector(GameGroundView::menuSettingClickCallback)) ;
	// menuBack->setContentSize(CCSizeMake(67, 68)) ;
	menuSetting->setAnchorPoint(ccp(0, 0.5)) ;
	menuSetting->setPosition(ccp(item_width+10, topBar_height/2)) ;
	//menuSetting->setPosition(ccp(right_width-item_width, topBar_height/2)) ;

	// 返回大厅
	CCMenuItemImage* menuBack = CCMenuItemImage::create("menu_back_n.png", "menu_back_s.png", this,
															menu_selector(GameGroundView::menuBackClickCallback)) ;
	
	menuBack->setAnchorPoint(ccp(0, 0.5)) ;
	menuBack->setPosition(ccp(2*(item_width+10), topBar_height/2)) ;
	//menuBack->setPosition(ccp(right_width, topBar_height/2)) ;
	//rightMenu->addChild(menuBack) ;

	
	//rightMenu->addChild(menuSetting) ;
	CCMenu* rightMenu = CCMenu::create(menuGifts, menuBack, menuSetting, NULL) ;
	rightMenu->setContentSize(CCSizeMake(size.width/4, topBar_height)) ;
	rightMenu->setAnchorPoint(ccp(0, 0)) ;
	rightMenu->setPosition(ccp(size.width*3/4-10, 0)) ;	
	this->topBar->addChild(rightMenu, 1) ;
	// rightMenu->alignItemsHorizontallyWithPadding(10) ;
	
}

// 初始化底部操作menu
void GameGroundView::initBottomMenu(CCSize size) 
{
	const float item_width = 145.0f ;
	const float item_height = 57.0f ;
	const float margin = 17.5f ; // 外边距，距边框的距离
	const float padding = 10.0f ; // 内边距，组件之间的间距

	CCSprite* bg = CCSprite::create("bg_bottom.png") ;
	bg->setAnchorPoint(ccp(0.5, 0)) ;
	bg->setPosition(ccp(size.width/2, 0)) ;

	const float bottomBar_height = bg->getContentSize().height ;

	this->bottomBar = CCNode::create() ;
	bottomBar->setContentSize(CCSizeMake(size.width, bottomBar_height)) ;
	bottomBar->setAnchorPoint(ccp(0.5, 0)) ;
	bottomBar->setPosition(ccp(size.width/2, 0)) ;
	// bottomBar->setVisible(false) ;
	// bottomBar->setEnabled(false) ;
	this->addChild(bottomBar, 1) ;

	this->bottomBar->addChild(bg, 0) ;	// 将背景加入到管理

	// 跟注
	CCMenuItemImage* menuFollowBet = CCMenuItemImage::create("menu_follow_bet_n.png", "menu_follow_bet_s.png", 
															this, menu_selector(GameGroundView::menuFollowBetClickCallback) ) ;
	menuFollowBet->setAnchorPoint(ccp(0, 0)) ;
	menuFollowBet->setPosition(ccp(margin, 0)) ;

	// 加注
	CCMenuItemImage* menuAddBet = CCMenuItemImage::create("menu_add_bet_n.png", "menu_add_bet_s.png", 
															this, menu_selector(GameGroundView::menuAddBetClickCallback) ) ;
	menuAddBet->setAnchorPoint(ccp(0, 0)) ;
	menuAddBet->setPosition(ccp(margin+padding+item_width, 0)) ;

	// 看牌
	CCMenuItemImage* menuLookCard = CCMenuItemImage::create("menu_look_card_n.png", "menu_look_card_s.png", 
														this, menu_selector(GameGroundView::menuLookCardClickCallback) ) ;
	menuLookCard->setAnchorPoint(ccp(0.5, 0)) ;
	menuLookCard->setPosition(ccp(size.width/2, 0)) ;


	// 比牌
	CCMenuItemImage* menuCompareCard = CCMenuItemImage::create("menu_compare_card_n.png", "menu_compare_card_s.png", 
															this, menu_selector(GameGroundView::menuCompareCardClickCallback) ) ;
	menuCompareCard->setAnchorPoint(ccp(1, 0)) ;
	menuCompareCard->setPosition(ccp(size.width-margin-item_width-padding, 0)) ;

	// 放弃
	CCMenuItemImage* menuGiveup = CCMenuItemImage::create("menu_giveup_n.png", "menu_giveup_s.png", 
														this, menu_selector(GameGroundView::menuGiveupClickCallback) ) ;
	menuGiveup->setAnchorPoint(ccp(1, 0)) ;
	menuGiveup->setPosition(ccp(size.width-margin, 0)) ;


	CCMenu* bottomMenu = CCMenu::create(menuFollowBet, menuAddBet, menuLookCard, menuCompareCard, menuGiveup, NULL) ;
	bottomMenu->setContentSize(CCSizeMake(size.width, item_height)) ;	
	// bottomMenu->setAnchorPoint(ccp(0, 0)) ;
	// bottomMenu->setPosition(ccp(0, (bottomBar_height-item_height)/2)) ;

	bottomMenu->setAnchorPoint(ccp(0, 0)) ;
	bottomMenu->setPosition(ccp(0, -bottomBar_height) );
	bottomBar->addChild(bottomMenu, 1, BOTTOM_PLAYER_OPERATION_MENU) ;
	
	CCLog("bottomBar_height: %f", bottomBar_height) ;

	CCLog("bottomMenu anchorPoint: x:%f, y:%f", bottomMenu->getAnchorPoint().x, bottomMenu->getAnchorPoint().y) ;
	
}

/**
* 	初始化玩家和机器人
* 	@param size 屏幕大小尺寸
*/
void GameGroundView::initPlayers(CCSize size)
{
	// 添加玩家
	GamePlayer* gamePlayer = NULL ;
	const float margin_left_right = 30 ;
	const float margin_top = 70 ;
	const float margin_bottom = 80 ;

	// 机器人1
	gamePlayer = new GamePlayerRight("user/head_default_f1.png", "唯我独尊", 1, 100000) ;
	//gamePlayer->setVisible(true) ;
	gamePlayer->setAnchorPoint(ccp(1, 0)) ;
	// 右侧玩家	
	gamePlayer->setPosition(ccp(size.width-margin_left_right, margin_bottom)) ;
	// gamePlayer->setPosition(ccp(0, 0)) ;
	gamePlayer->setState(kInitial) ;
	//this->addChild(gamePlayer, 1, 10) ;
	this->addChild(gamePlayer, 1) ;
	playerArray->addObject(gamePlayer) ; // 加入到集合里面
	gamePlayer->release() ;
	gamePlayer = NULL ;
	
	// 机器人2
	gamePlayer = new GamePlayerRight("user/head_default_m1.png", "好朋友01", 1, 100000) ;
	//gamePlayer->setVisible(true) ;
	gamePlayer->setAnchorPoint(ccp(1, 1)) ;
	// 右侧玩家	
	gamePlayer->setPosition(ccp(size.width-2*margin_left_right, size.height - margin_top)) ;
	// gamePlayer->setPosition(ccp(0, 0)) ;
	gamePlayer->setState(kInitial) ;
	//this->addChild(gamePlayer, 1, 10) ;
	this->addChild(gamePlayer, 1) ;
	playerArray->addObject(gamePlayer) ; // 加入到集合里面
	gamePlayer->release() ;
	gamePlayer = NULL ;


	// 机器人3，靠左布局
	gamePlayer = new GamePlayerLeft("user/head_default_m3.png", "好朋友02", 1, 100000) ;
	//gamePlayer->setVisible(true) ;
	gamePlayer->setAnchorPoint(ccp(0, 1)) ;
	// 右侧玩家	
	gamePlayer->setPosition(ccp(2*margin_left_right-10, size.height-margin_top) );
	// gamePlayer->setPosition(ccp(0, 0)) ;
	gamePlayer->setState(kInitial) ;
	//this->addChild(gamePlayer, 1, 10) ;
	this->addChild(gamePlayer, 1) ;
	playerArray->addObject(gamePlayer) ; // 加入到集合里面
	gamePlayer->release() ;
	gamePlayer = NULL ;


	// 机器人4，靠左布局
	gamePlayer = new GamePlayerLeft("user/head_default_f2.png", "好朋友03", 1, 100000) ;
	//gamePlayer->setVisible(true) ;
	gamePlayer->setAnchorPoint(ccp(0, 0)) ;
	// 右侧玩家	
	gamePlayer->setPosition(ccp(margin_left_right-10, margin_bottom)) ;
	// gamePlayer->setPosition(ccp(0, 0)) ;
	gamePlayer->setState(kInitial) ;
	//this->addChild(gamePlayer, 1, 10) ;
	this->addChild(gamePlayer, 1) ;
	playerArray->addObject(gamePlayer) ; // 加入到集合里面
	gamePlayer->release() ;
	gamePlayer = NULL ;

	


	// 玩家，靠中下
	gamePlayer = new GamePlayerCenter("user/head_default_m2.png", "绝对无敌", 1, 100000) ;
	//gamePlayer->setVisible(true) ;
	gamePlayer->setAnchorPoint(ccp(0.3, 0)) ;
	// 右侧玩家	
	gamePlayer->setPosition(ccp(size.width/2, margin_bottom-10) );
	// gamePlayer->setPosition(ccp(0, 0)) ;
	gamePlayer->setState(kInitial) ;
	//this->addChild(gamePlayer, 1, 10) ;
	this->addChild(gamePlayer, 1) ;
	playerArray->addObject(gamePlayer) ; // 加入到集合里面
	gamePlayer->release() ;

}