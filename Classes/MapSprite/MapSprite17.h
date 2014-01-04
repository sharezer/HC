#pragma once
#include "MapSprite.h"

class CMapSprite17 : public CMapSprite
{
public:
	void firstAction();
	virtual void changetTexture(CMap::MapData& data);	

public:
	virtual bool initSprite();
	virtual void endAction(CMap::MapData& data);
private:
	void endActionCB(cocos2d::CCNode* pNode, void* pData);
};