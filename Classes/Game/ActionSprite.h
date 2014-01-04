#pragma once
#include "cocos2d.h"

enum eActionState
{
	kActionStateNone = 0,
	kActionStateStandBy1,
	kActionStateStandBy2,
	/*kActionStateStandBy2CB,*/

	kActionStateWakeUp,

	kActionStateWalkUp,
	kActionStateWalkDown,
	kActionStateWalkLeft,
	//kActionStateWalkRight,

	kActionStateWalkUpPush,
	kActionStateWalkDownPush,
	kActionStateWalkLeftPush,
	//kActionStateWalkRightPush,

	kActionStateDead1,
	kActionStateDead2,
	kActionStatePoisoning,

	kActionStateSkipMatch,
};

// 1 - convenience measurements
#define SCREEN CCDirector::sharedDirector()->getWinSize()
#define CENTER ccp(SCREEN.width / 2, SCREEN.height / 2)
#define CURTIME GetCurTime()

// 2 - convenience functions
#ifndef UINT64_C
#define UINT64_C(val) val##ui64
#endif
#define random_range(low, high) (rand() % (high - low + 1)) + low
#define frandom (float)rand() / UINT64_C(0x100000000)
#define frandom_range(low, high) ((high - low) * frandom) + low



class ActionSprite : public cocos2d::CCLayer
{
protected:
	cocos2d::CCSprite* m_pSprite;

public:
	ActionSprite(void);
	~ActionSprite(void);

	CREATE_FUNC(ActionSprite);
	//action methods
	//static void createActionWithType(eActionState type);

	static ActionSprite* getInst();

	cocos2d::CCAction* createAnimate(eActionState type);
	void initFrameCache();

private:

	bool init();

	cocos2d::CCAction* standBy1();

	cocos2d::CCAction* standBy2();

	cocos2d::CCAction* wakeUp();

	cocos2d::CCAction* walkUp();
	cocos2d::CCAction* walkDown();
	cocos2d::CCAction* walkLeft();

	cocos2d::CCAction* walkUpPush();
	cocos2d::CCAction* walkDownPush();
	cocos2d::CCAction* walkLeftPush();

	cocos2d::CCAction* dead1();
	cocos2d::CCAction* dead2();

	cocos2d::CCAction* Poisoning();

	cocos2d::CCAction* skipMatch();

	void skipMatchEnd();
	void deadEnd();
	void standBy2CB();
// 	CC_SYNTHESIZE_READONLY(bool, _bShield, IsShield);
// 	CC_SYNTHESIZE_READONLY(bool, _bInvincible, IsInvincible);
// 	CC_SYNTHESIZE_READONLY(bool, _bMagnet, IsMagnet);
// 	CC_SYNTHESIZE_READONLY(bool, _bAntiskid, IsAntiskid);

	//actions

	CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimate*, _standBy1Action, StandBy1Action);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimate*, _standBy2Action, StandBy2Action);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimate*, _standBy2CBAction, StandBy2CBAction);

	CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimate*, _wakeUpAction, WakeUpAction);

	CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimate*, _walkUpAction, WalkUpAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimate*, _walkDownAction, WalkDownAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimate*, _walkLeftAction, WalkLeftAction);

	CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimate*, _walkUpActionPush, WalkUpActionPush);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimate*, _walkDownActionPush, WalkDownActionPush);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimate*, _walkLeftActionPush, WalkLeftActionPush);

	CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimate*, _dead1Action, Dead1Action);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimate*, _dead2Action, Dead2Action);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimate*, _poisoningAction, PoisoningAction);

	CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimate*, _skipMatchAction, SkipMatchAction);
};

#define deActionSprite ActionSprite::getInst()