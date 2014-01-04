#pragma once
#include "MapSprite.h"

class CMapSprite16 : public CMapSprite
{
public:
	void firstAction();
	virtual bool initSprite();
	virtual void changeAction(eActionState type);
	virtual void playerMove(cocos2d::CCPoint direction,  CMap::MapData& nextData);
	virtual void playerWakeUp();
	virtual void standByAction();
	virtual void playerDead1();
	virtual void playerDead2();

private:
	void playerMoveCB(cocos2d::CCNode* pNode, void* pData);
	void playerWakeUpCB();

private:
	cocos2d::CCPoint m_pDirection;
};