#pragma once
#include "cocos2d.h"
#include "GameManager.h"

#define dg_For_Use_Test_UI


class CMenuChildLayer: public cocos2d::CCLayer
{
public:
	virtual void mouseDown(cocos2d::CCPoint& pos) = 0;
	virtual void mouseMove(cocos2d::CCPoint& pos) = 0;
	virtual void mouseUp(cocos2d::CCPoint& pos) = 0;

public:
	virtual void vgEnter(bool bRight) = 0;
	virtual void vgExit(bool bRight) = 0;
};


class CMenuSence: public CGameSence
{
	enum eMenuChildType
	{
		eStartL,
		eMissionSelectL,
		eMCT_Count,

		eMCT_Start = eStartL,
		eMCT_End = eMissionSelectL,
	};

public:

	CREATE_FUNC(CMenuSence);
	virtual void pause();
	virtual void resume();

public:
	virtual bool init(); 
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void update(float dt);

public:
	void previousUI();
	void nextUI();

private:
	CMenuChildLayer* m_pMenuChildL[eMCT_Count];
	int m_nCurChildL;
};


