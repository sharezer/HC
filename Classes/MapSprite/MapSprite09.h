#pragma once
#include "MapSprite.h"

class CMapSprite09 : public CMapSprite
{
public:
	virtual bool initSprite();
	virtual void endAction(CMap::MapData& data);
	virtual void workAction(CMap::MapData& data);
	virtual void changetTexture(CMap::MapData&data);
private:
	void endActionCB(cocos2d::CCNode* pNode, void* pData);
	void workActionCB(cocos2d::CCNode* pNode, void* pData);
};