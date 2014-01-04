#include "ActionSprite.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "GamingS.h"
#include "Map.h"

using namespace cocos2d;

#define deStandBy1Delay			(float)(1.0 / 12)
#define deStandBy2Delay			(float)(1.0 / 12)
#define deStandBy2CBDelay		(float)(1.0 / 12)

#define deWakeUpDelay			(float)(1.0 / 24)

#define deWalkUpDelay			(float)(0.5 / 5)

#define deWalkDownDelay			(float)(0.5 / 10)
#define deWalkLeftDelay			(float)(0.5 / 4)

#define deWalkUpDelayPush		(float)(0.5 / 5)
#define deWalkDownDelayPush		(float)(0.5 / 5)
#define deWalkLeftDelayPush		(float)(0.5 / 4)

#define deDeadDelay				(float)(1.0 / 12)
#define dePoisoningDelay		(float)(1.0 / 12)

#define deSkipMatchDelay		(float)(1.0 / 12)


ActionSprite::ActionSprite(void)
{
	_standBy1Action = NULL;
	_standBy2Action = NULL;
	_standBy2CBAction = NULL;

	_wakeUpAction = NULL;

	_walkUpAction = NULL;
	_walkDownAction = NULL;
	_walkLeftAction = NULL;

	_walkUpActionPush = NULL;
	_walkDownActionPush = NULL;
	_walkLeftActionPush = NULL;

	_dead1Action = NULL;
	_dead2Action = NULL;
	_poisoningAction = NULL;

	_skipMatchAction = NULL;

}

ActionSprite::~ActionSprite(void)
{

}

bool ActionSprite::init()
{
	return true;
}

void ActionSprite::initFrameCache()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("npc_001_01.plist", "npc_001_01.png");
/*	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("npc_001_02.plist", "npc_001_02.png");*/
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("npc_001_04.plist", "npc_001_04.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("npc_001_05.plist", "npc_001_05.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("npc_001_06.plist", "npc_001_06.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("npc_001_07.plist", "npc_001_07.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("npc_001_08.plist", "npc_001_08.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("npc_001_09.plist", "npc_001_09.png");

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("tool_001_action.plist", "tool_001_action.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sound_007.plist", "sound_007.png");
}

ActionSprite* ActionSprite::getInst()
{
	static ActionSprite* s_pInst = NULL;
	if(s_pInst == NULL)
	{
		s_pInst = new ActionSprite();
		s_pInst->init();
	}
	return s_pInst;
}

CCAction* ActionSprite::createAnimate(eActionState type)
{
	CCAction* pAction = NULL;
	switch (type)
	{
	case kActionStateNone:
		pAction = NULL;
		break;

	case kActionStateStandBy1:
		{
			pAction = this->standBy1();
		}
		break;

	case kActionStateStandBy2:
		{
			pAction = this->standBy2();

		}
		break;

// 	case kActionStateStandBy2CB:
// 		{
// 			pAction = this->standBy2CB();
// 		}
// 		break;

	case kActionStateWakeUp:
		{
			pAction = this->wakeUp();
		}
		break;

	case kActionStateWalkUp:
		{
			pAction = this->walkUp();
		}
		break;

	case kActionStateWalkDown:
		{
			pAction = this->walkDown();
		}
		break;

	case kActionStateWalkLeft:
		{
			pAction = this->walkLeft();
		}
		break;

	case kActionStateWalkUpPush:
		{
			pAction = this->walkDown();
		}
		break;

	case kActionStateWalkDownPush:
		{
			pAction = this->walkDown();
		}
		break;

	case kActionStateWalkLeftPush:
		{

		}
		break;

	case kActionStateDead1:
		{
			pAction = this->dead1();
		}
		break;

	case kActionStateDead2:
		{
			pAction = this->dead2();
		}
		break;

	case kActionStatePoisoning:
		{

		}
		break;

	case kActionStateSkipMatch:
		{
			pAction = this->skipMatch();
		}
		break;

	default:
		break;
	}
	return pAction;
}



CCAction* ActionSprite::standBy1()
{
	CCArray *Array = CCArray::createWithCapacity(28);  
	char str[30];
	for(int i = 1;i < 29; i++)
	{
		sprintf(str, "npc_001_06_00%02d.png", i);
		Array->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(Array, deStandBy1Delay);
	CC_SAFE_DELETE(Array);
	_standBy1Action = CCAnimate::create(animation);
// 	CCCallFunc *pCallBack = CCCallFunc::create(this, callfunc_selector(ActionSprite::skipMatchEnd));
// 	CCAction* action = (CCAction*)CCSequence::create(_standBy1Action, pCallBack, NULL);

 	return CCRepeatForever::create(_standBy1Action);
}

CCAction* ActionSprite::standBy2()
{
	CCArray *Array = CCArray::createWithCapacity(2);  
	char str[30];
	for(int i = 1;i < 3; i++)
	{
		sprintf(str, "npc_001_07_00%02d.png", i);
		Array->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(Array, deStandBy1Delay);
	CC_SAFE_DELETE(Array);
	_standBy2Action = CCAnimate::create(animation);
	CCCallFunc *pCallBack = CCCallFunc::create(this, callfunc_selector(ActionSprite::standBy2CB));
	CCAction* action = (CCAction*)CCSequence::create(_standBy2Action, pCallBack, NULL);

	return action;
}

void ActionSprite::standBy2CB()
{
	CMap* pMap = deGameManager->getMap();
	/*pMap->skipMacth();*/
	CCArray *Array = CCArray::createWithCapacity(8);  
	char str[30];
	for(int i = 3;i < 11; i++)
	{
		sprintf(str, "npc_001_07_00%02d.png", i);
		Array->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(Array, deStandBy2Delay);
	CC_SAFE_DELETE(Array);
	_standBy2CBAction = CCAnimate::create(animation);
	CCAction* action = CCRepeatForever::create(static_cast<CCSequence*> (CCSequence::create(_standBy2CBAction, _standBy2CBAction->reverse(), NULL)));
	pMap->m_pPlayer->pSprite->runAction(action);
	// 	CCCallFunc *pCallBack = CCCallFunc::create(this, callfunc_selector(ActionSprite::skipMatchEnd));
	// 	CCAction* action = (CCAction*)CCSequence::create(_standBy1Action, pCallBack, NULL);
}

CCAction* ActionSprite::wakeUp()
{
	CCArray *Array = CCArray::createWithCapacity(12);  
	char str[30];
	for(int i = 1;i < 13; i++)
	{
		sprintf(str, "npc_001_08_00%02d.png", i);
		Array->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(Array, deWakeUpDelay);
	CC_SAFE_DELETE(Array);
	_wakeUpAction = CCAnimate::create(animation);
	// 	CCCallFunc *pCallBack = CCCallFunc::create(this, callfunc_selector(ActionSprite::skipMatchEnd));
	// 	CCAction* action = (CCAction*)CCSequence::create(_standBy1Action, pCallBack, NULL);
	return _wakeUpAction;
}


CCAction* ActionSprite::walkUp()
{
	CCArray *Array = CCArray::createWithCapacity(5);  
	char str[30];
	for(int i = 1;i <6; i++)
	{
		sprintf(str,"npc_001_03_%02d.png",i); 
		Array->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(Array, deWalkUpDelay);
	CC_SAFE_DELETE(Array);
	_walkUpAction = CCAnimate::create(animation);	
	return CCRepeatForever::create(_walkUpAction);
}
CCAction* ActionSprite::walkDown()
{
	CCArray *Array = CCArray::createWithCapacity(5);
	char str[30];
	for(int i=1;i<6;i++)
	{
		sprintf(str,"npc_001_02_%02d.png",i); 
		Array->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(Array, deWalkDownDelay);
	CC_SAFE_DELETE(Array);
	_walkDownAction = CCAnimate::create(animation);

	return CCRepeatForever::create(_walkDownAction);
}
CCAction* ActionSprite::walkLeft()
{
	CCArray *Array = CCArray::createWithCapacity(4);
	char str[30];
	for(int i=1;i<5;i++)
	{
		sprintf(str,"npc_001_01_%02d.png",i); 
		Array->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(Array, deWalkLeftDelay);
	CC_SAFE_DELETE(Array);
	_walkLeftAction = CCAnimate::create(animation);

	return CCRepeatForever::create(_walkLeftAction);
}

CCAction* ActionSprite::walkUpPush()
{
	return CCRepeatForever::create(_walkLeftAction);
}
CCAction* ActionSprite::walkDownPush()
{
	return CCRepeatForever::create(_walkLeftAction);

}
CCAction* ActionSprite::walkLeftPush()
{
	return CCRepeatForever::create(_walkLeftAction);
}

CCAction* ActionSprite::dead1()
{
	CCArray *Array = CCArray::createWithCapacity(25);  
	char str[30];
	for(int i = 1;i < 26; i++)
	{
		sprintf(str, "npc_001_04_%02d.png", i);
		Array->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(Array, deDeadDelay);
	CC_SAFE_DELETE(Array);
	_dead1Action = CCAnimate::create(animation);
	CCCallFunc *pCallBack = CCCallFunc::create(this, callfunc_selector(ActionSprite::deadEnd));
	CCAction* action = (CCAction*)CCSequence::create(_dead1Action, pCallBack, NULL);

	return action;
}

CCAction* ActionSprite::dead2()
{
	CCArray *Array = CCArray::createWithCapacity(23);  
	char str[30];
	for(int i = 1;i < 24; i++)
	{
		sprintf(str, "npc_001_09_00%02d.png", i);
		Array->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(Array, deDeadDelay);
	CC_SAFE_DELETE(Array);
	_dead2Action = CCAnimate::create(animation);
	CCCallFunc *pCallBack = CCCallFunc::create(this, callfunc_selector(ActionSprite::deadEnd));
	CCAction* action = (CCAction*)CCSequence::create(_dead2Action, pCallBack, NULL);

	return action;
}

CCAction* ActionSprite::Poisoning()
{
	return CCRepeatForever::create(_walkLeftAction);
}

CCAction* ActionSprite::skipMatch()
{
	CCArray *Array = CCArray::createWithCapacity(19);  
	char str[30];
	for(int i = 1;i < 20; i++)
	{
		sprintf(str, "npc_001_05_00%02d.png", i);
		Array->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(Array, deSkipMatchDelay);
	CC_SAFE_DELETE(Array);
	_skipMatchAction = CCAnimate::create(animation);
	CCCallFunc *pCallBack = CCCallFunc::create(this, callfunc_selector(ActionSprite::skipMatchEnd));
	CCAction* action = (CCAction*)CCSequence::create(_skipMatchAction, pCallBack, NULL);

	return action;
}

void ActionSprite::skipMatchEnd()
{
	CMap* pMap = deGameManager->getMap();
	pMap->skipMacth();
}

void ActionSprite::deadEnd()
{
	CMap* pMap = deGameManager->getMap();
	pMap->showGameOver();
}