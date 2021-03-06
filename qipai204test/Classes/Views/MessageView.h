/********************************************************************************
	File: MessageView.h
	
	Written by: 杨杰
	Copyright:  www.zyios.com 2013-05-25
	
	MessageView 类是一个短信消息界面类，用来显示短信消息内容

********************************************************************************/
#ifndef __GOLDENFRAUD__MessageView__
#define __GOLDENFRAUD__MessageView__

/********************************************************************************
	引入需要的头文件信息
********************************************************************************/

#include "cocos2d.h"
#include "cocos-ext.h"

/********************************************************************************
	using namespace
********************************************************************************/
using namespace cocos2d;
USING_NS_CC_EXT ;

/********************************************************************************
	类型声明定义
********************************************************************************/
typedef struct 
{
	char theme[50] ; // 主题
	char content[150] ; // 内容
} Message ;


/********************************************************************************
	MessageView 类定义
********************************************************************************/
class MessageView : public CCLayer, public CCListViewDelegate {
public:
	/**
	 * 构造函数
	 */
	MessageView() ;

	/**
	 * 析构函数
	 */
	~MessageView() ;

	/**
	* 创建一个场景，并将布景层加入到该场景中
	* return  返回创建好的场景对象
	*/
	static CCScene* CreateScene() ;

	/**
	 * 初始化方法
	 */	
	virtual bool init() ;


	/**
	 * 当该layer进入了运行的scene中运行
	 */
	virtual void onEnter() ;

	/**
	 * 当该layer离开了scene时调用
	 */
	virtual void onExit() ;

	/**
	 * 处理返回键事件
	 */
	virtual void keyBackClicked() ;



// ListView响应事件
	virtual void CCListView_numberOfCells(CCListView *listView, CCListViewProtrolData *data) ;
 
	virtual void CCListView_cellForRow(CCListView *listView, CCListViewProtrolData *data) ;
	 
	virtual void CCListView_didClickCellAtRow(CCListView *listView, CCListViewProtrolData *data) ;
	 
	virtual void CCListView_didScrollToRow(CCListView *listView, CCListViewProtrolData *data) ;

// 菜单项点击事件

	/**
	 * 礼包菜单点击事件处理函数
	 */
	void menuGiftsClickCallback(CCObject* pSender) ;

	/**
	 * 返回菜单点击事件处理函数
	 */
	void menuBackClickCallback(CCObject* pSender) ;

	/**
	 * 设置菜单点击事件处理函数
	 */
	void menuSettingClickCallback(CCObject* pSender) ;



	/**
	 * 存值菜单点击事件处理函数
	 */
	void menuStoreClickCallback(CCObject* pSender) ;


	/**
	 *	底部信息菜单
	 */
	void menuInfoClickCallback(CCObject* pSender) ;

	/*
	 * 底部任务菜单
	 */
	void menuTaskClickCallback(CCObject* pSender) ;

	/**
	 * 底部商城菜单
	 */
	void menuShopClickCallback(CCObject* pSender) ;

	/**
	* 底部活动菜单项
	*/
	void menuActivityClickCallback(CCObject* pSender) ;

	/**
	* 底部活动菜单项
	*/
	void menuMoreClickCallback(CCObject* pSender) ;


	/**
	* 更多 排行榜菜单项
	*/
	void menuRankingClickCallback(CCObject* pSender) ;

	/**
	 * 好友菜单点击事件处理函数
	 */
	void menuFriendClickCallback(CCObject* pSender) ;

	/**
	 * 客服菜单点击事件处理函数
	 */
	void menuCustomServiceClickCallback(CCObject* pSender) ;

	/**
	 * 更新时间标签里面显示的时间，schedule
	
	void updateTimeLabel() ;
	 */

	CREATE_FUNC(MessageView);

private:
	// 列表
	CCListView* contentListView ;

	// 初始化顶部bar
	void initTopBar(CCSize winSize) ;

	// 初始化中间部分bar
	void initCenterBar(CCSize winSize) ;

	// 初始化底部Bar
	void initBottomBar(CCSize winSize) ;


// 属性定义 /////////////////////////////////////////////////////

	/**
	 * 顶部条
	 */
	CCNode* topBarNode ;

	 /**
	  *	喇叭信息以及系统信息显示框
	  */
	CCNode* infoTipNode ;

	/**
	 * 游戏模式选择框
	 */
	CCNode* modeSelectNode ;

	/**
	 * 底部条
	 */
	CCNode* footerBarNode ;

	/**
	* 	更多菜单
	*/
	CCNode* moreMenuNode ;

	/**
	*	是否显示更多菜单，默认为false
	*/
	bool moreMenuShow  ;
}; 

#endif
/********************************************************************************
	End of File: MessageView.h
********************************************************************************/