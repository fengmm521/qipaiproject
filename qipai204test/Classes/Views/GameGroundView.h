/********************************************************************************
	File: GameGroundView.h
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-22
	
	该类是描述比赛场，分为初级场、中级场和高级场

********************************************************************************/
	
#ifndef __GOLDENFRAUD_GameGroundView__
#define __GOLDENFRAUD_GameGroundView__

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/

#include "cocos2d.h"
#include "GameLogic.h"

/********************************************************************************
	类型定义
********************************************************************************/

// 游戏状态
typedef enum 
{
	kInitialGame = 10 ,	// 初始化游戏
	kBetBasic,			// 下底注
	kProvideCard, 		// 发牌
	kTurn				// 
} GameState ;

/********************************************************************************
	using namespace
********************************************************************************/
USING_NS_CC ;

/********************************************************************************
	GameGroundView 类定义
********************************************************************************/
class GameGroundView : public CCLayer
{
public:
	/**
	 *	构造函数  	
	 */
	GameGroundView() ;
	/**
	 * 析构函数
	 */
	~GameGroundView() ;

	/**
	 * 	创建展示该Layer的场景对象
	 *	@return 返回加入了该Layer的场景对象
	 */
	static CCScene* CreateScene() ;

	/**
	 *	初始化函数，这个函数在CCLayer类的create方法中调用
	 * 	@return 初始化成功返回true，否者返回false
	 */
	virtual bool init() ;


	virtual void onEnter() ;

	virtual void onExit() ;

	/**
	 * 处理返回键事件
	 */
	virtual void keyBackClicked() ;


public:
	/**
	*	返回按钮点击事件处理函数
	*/
	void menuBackClickCallback(CCObject* pSender) ;

	/**
	*	设置按钮点击事件处理函数
	*/
	void menuSettingClickCallback(CCObject* pSender) ;

	/**
	*	礼物按钮点击事件处理函数
	*/
	void menuGiftsClickCallback(CCObject* pSender) ;

	/**
	*	准备按钮点击事件处理函数
	*/
	void menuReadyClickCallback(CCObject* pSender) ;

	/**
	*	跟注菜单点击事件处理函数
	*/
	void menuFollowBetClickCallback(CCObject* pSender) ;

	/**
	*	加注菜单点击事件处理函数
	*/
	void menuAddBetClickCallback(CCObject* pSender) ;

	/**
	*	看牌菜单点击事件处理函数
	*/
	void menuLookCardClickCallback(CCObject* pSender) ;

	/**
	*	比牌菜单点击事件处理函数
	*/
	void menuCompareCardClickCallback(CCObject* pSender) ;

	/**
	*	放弃菜单点击事件处理函数
	*/
	void menuGiveupClickCallback(CCObject* pSender) ;

	/**
	*	发每张牌后调用的函数
	*/
	void provideCardCallback() ;

	/**
	*	发完牌后调用的函数
	*/
	void provideCardFinishedCallback() ;

	// 等待下注
	void waitBetFinishedCallback() ;

	/**
	*	开始游戏
	*/
	void startingGameSchedule() ;

	// 累加总注
	void appendTotalBet(DWORD bet) ;

	// 新游戏，用来初始化和调整参数使用
	void newGame() ;

	// 设置单注
	void setSingleBet(DWORD bet) ;

	CREATE_FUNC(GameGroundView);

private:
	// 初始化背景
	void initBg(CCSize size) ;

	// 初始化顶部背景
	void initTopBar(CCSize size) ;

	// 初始化底部操作menu
	void initBottomMenu(CCSize size) ;

	// 初始化机器人和玩家
	void initPlayers(CCSize size) ;

	/**
	*	初始化发牌动作
	*/
	void initActions(CCSize size) ;

	// 发牌
	void provideCard() ;

	// 下一玩家
	void nextPlayer() ;

	// 显示玩家操作菜单
	void showPlayerOperationMenu() ;

	// 隐藏玩家操作菜单
	void hidePlayerOperationMenu() ;

	// 底部玩家操作菜单
	CCNode* bottomBar ;

	CCNode* topBar ;

	// 单注
	CCLabelTTF* singleBetLabel ;

	// 总注
	CCLabelTTF* allBetLabel ;

	// 扑克牌发牌动作
	CCSprite* cardAnimate ;

	// 游戏逻辑
	GameLogic* gameLogic ;

	// 筹码所在区域
	CCNode* jetonAreaNode ;	
} ;


#endif