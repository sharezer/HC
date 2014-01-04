#pragma once
#include "MapSprite.h"

class CMapSprite04 : public CMapSprite
{
public:
	virtual bool initSprite();
	virtual void updateAll();
	virtual void startUpdate();
	virtual void stopUpdate();
protected:

	virtual void eat(CMap::MapData& data, CMap::MapData& food);
	virtual void eatCB(cocos2d::CCNode* pNode, void* pData);

	virtual void eatAction(CMap::MapData& data, CMap::MapData& food);

	virtual void wakeUp();
	virtual void wakeUpCB();
	virtual void close();

	virtual void judgeFood(CMap::MapData& data);
	virtual void judgeWakeUp(CMap::MapData& data);
	virtual void changetTexture(CMap::MapData& data);	

private:
	cocos2d::CCAction* killPlayerAction();
	void killPlayerActionCB();

private:
	cocos2d::CCSprite* m_pFire;
	
};