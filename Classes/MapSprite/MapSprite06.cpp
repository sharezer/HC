#include "MapSprite06.h"

USING_NS_CC;

bool CMapSprite06::initSprite()
{
	bool bRet = false;
	do 
	{
		CCSprite* pSprite = CCSprite::create("items_004.png");
		m_pSprite = pSprite;
		m_pMap = deGameManager->getMap();
		bRet = true;
	} while (0);

	return bRet;
}

void CMapSprite06::changetTexture(CMap::MapData& data)
{
	CCTexture2D* texture;
	texture = CCTextureCache::sharedTextureCache()->addImage("items_00401.png");
	m_pSprite->setTexture(texture);
}

void CMapSprite06::endAction(CMap::MapData&data)
{
	if (!data.live)
	{
		return;
	}
	this->changetTexture(data);
	CCScaleTo* pScaleTo = CCScaleTo::create(0.5, 0);
	CCCallFuncND* pCallBack = CCCallFuncND::create(this, callfuncND_selector(CMapSprite06::endActionCB), &data);
	data.pSprite->runAction(CCSequence::create(pScaleTo, pCallBack, NULL));

}

void CMapSprite06::endActionCB(cocos2d::CCNode* pNode, void* pData)
{
	CMap::MapData* pMapData = (CMap::MapData*)pData;
	pMapData->pSprite = NULL;
	pMapData->type = eMT_Road;
	pMapData->live = false;
	pMapData->pItem->clearUp(*pMapData);
	pNode->removeFromParentAndCleanup(true);
}