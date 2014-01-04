#include "MapSprite02.h"

#define deDoorOpenDelayTime		2.0f
using namespace cocos2d;

bool CMapSprite02::initSprite()
{
	bool bRet = false;
	do 
	{
		CCSprite* pSprite = CCSprite::create("tool_002.png");
		m_pSprite = pSprite;
		m_pMap = deGameManager->getMap();
		bRet = true;
	} while (0);

	return bRet;

}

void CMapSprite02::changetTexture(CMap::MapData& data)
{
	CCTexture2D* texture;
	texture = CCTextureCache::sharedTextureCache()->addImage("tool_002_002.png");
	m_pSprite->setTexture(texture);
}

void CMapSprite02::endAction(CMap::MapData&data)
{
	if (!data.live)
	{
		return;
	}
	this->changetTexture(data);
	CCScaleTo* pScaleTo = CCScaleTo::create(2.0f, 0);
	CCCallFuncND* pCallBack = CCCallFuncND::create(this, callfuncND_selector(CMapSprite02::endActionCB), &data);
	data.pSprite->runAction(CCSequence::create(pScaleTo, pCallBack, NULL));

}

void CMapSprite02::endActionCB(cocos2d::CCNode* pNode, void* pData)
{
	CMap::MapData* pMapData = (CMap::MapData*)pData;
	pMapData->pSprite = NULL;
	pMapData->type = eMT_Road;
	pMapData->live = false;
	pMapData->pItem->clearUp(*pMapData);
	pNode->removeFromParentAndCleanup(true);
}