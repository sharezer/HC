#include "MapSprite17.h"

#define deMoveDelayTime		0.5f
#define deEndActionSpeed	(float)(1.0 / 12)
USING_NS_CC;

bool CMapSprite17::initSprite()
{
	bool bRet = false;
	do 
	{
		CCSprite* pSprite = CCSprite::create("tool_003.png");
		m_pSprite = pSprite;
		m_pMap = deGameManager->getMap();
		bRet = true;
	} while (0);

	return bRet;
}

void CMapSprite17::changetTexture(CMap::MapData& data)
{
	CCTexture2D* texture;
	texture = CCTextureCache::sharedTextureCache()->addImage("tool_00302.png");
	m_pSprite->setTexture(texture);
}

void CMapSprite17::endAction(CMap::MapData& data)
{
	CCDelayTime* pDelay = CCDelayTime::create(deMoveDelayTime);
	CCAnimation *animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName("tool_00302.png");
	animation->setDelayPerUnit(deEndActionSpeed);
	CCAction* pAction = CCAnimate::create(animation);
	CCCallFuncND* pCallBack = CCCallFuncND::create(this, callfuncND_selector(CMapSprite17::endActionCB), &data);
	m_pSprite->runAction(CCSequence::create(pDelay, pAction, pCallBack, NULL));
}

void CMapSprite17::endActionCB(cocos2d::CCNode* pNode, void* pData)
{
	m_pMap->m_pPlayer->pItem->playerDead2();
}
