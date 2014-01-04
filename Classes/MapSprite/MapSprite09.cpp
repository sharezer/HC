#include "MapSprite09.h"

#define deActionSpeed		(float)(1.0 / 12)
#define deBombDelayTime		10.0f

USING_NS_CC;

bool CMapSprite09::initSprite()
{
	bool bRet = false;
	do 
	{
		CCSprite* pSprite = CCSprite::create("tool_007.png");
		m_pSprite = pSprite;
		m_pMap = deGameManager->getMap();
		bRet = true;
	} while (0);

	return bRet;
}

void CMapSprite09::changetTexture(CMap::MapData&data)
{
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("tool_007_02.png");
	m_pSprite->setTexture(texture);
}

void CMapSprite09::endAction(CMap::MapData&data)
{
	CCArray *Array = CCArray::createWithCapacity(6);  
	char str[30];
	for(int i = 1;i < 7; i++)
	{
		sprintf(str, "sound_007_00%02d.png", i);
		Array->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(Array, deActionSpeed);
	CC_SAFE_DELETE(Array);
	CCAnimate* animate = CCAnimate::create(animation);
	CCCallFuncND* pCallBack = CCCallFuncND::create(this, callfuncND_selector(CMapSprite09::endActionCB), &data);
	CCAction* action = (CCAction*)CCSequence::create(animate, pCallBack,NULL);
	m_pSprite->runAction(action);
}

void CMapSprite09::endActionCB(CCNode* pNode, void* pData)
{
	CMap::MapData* pMapData = (CMap::MapData*)pData;
	pMapData->pSprite = NULL;
	pMapData->type = eMT_Road;
	pMapData->live = false;
	pMapData->pItem->clearUp(*pMapData);
	pNode->removeFromParentAndCleanup(true);
}

void CMapSprite09::workAction(CMap::MapData& data)
{
	this->changetTexture(data);
	CCCallFuncND* pCallBack = CCCallFuncND::create(this, callfuncND_selector(CMapSprite09::workActionCB), &data);
	CCBlink* blink = CCBlink::create(deBombDelayTime, 20);
	m_pSprite->runAction(CCSequence::create(blink, pCallBack, NULL));
}

void CMapSprite09::workActionCB(CCNode* pNode, void* pData)
{
	int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	CMap::MapData* to = (CMap::MapData*)pNode->getUserData();
	for(int k = 0; k < 4; ++k)
	{
		int x = to->x  + dir[k][0];
		int y = to->y  + dir[k][1];

		if(m_pMap->validateCoord(x, y))
		{
			if (m_pMap->m_bWin)
			{
				break;
			}

			CMap::MapData& beBombdata = *(m_pMap->getMapData(x, y));

			switch (beBombdata.type)
			{

			case eMT_Player:
				m_pMap->m_pPlayer->pItem->playerDead1();
				break;

			case eMT_EndPos:
			case eMT_Piranha_Close:
			case eMT_Piranha_Open:
			case eMT_Piranha_Food:
			case eMT_Key:
			case eMT_Flower:
			case eMT_Wall2:
			case eMT_Obstacle2:
			case eMT_Poisonous_Mushroom:
				deMapSpriteManager->beBomb(beBombdata);
				break;
			case eMT_Bomb:
				beBombdata.pItem->workAction(beBombdata);
				break;

			default:
				break;
			}
		}
	}
	this->endAction(*to);
}
