#pragma once
#include "MapSprite.h"

class CMapSprite06 : public CMapSprite
{
public:
	virtual bool initSprite();
	virtual void changetTexture(CMap::MapData& data);
	virtual void endAction(CMap::MapData&data);
private:
	void endActionCB(cocos2d::CCNode* pNode, void* pData);
};