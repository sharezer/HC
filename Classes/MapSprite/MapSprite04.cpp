#include "MapSprite04.h"

#define dePiranha_Open_Duration		1.0f
#define dePiranha_Eating_Duration	10.0f
#define deUpdateAll_Duration		0.1f
#define deKillPlayerActionDuration	(float)(1.0 / 40)

USING_NS_CC;

bool CMapSprite04::initSprite()
{
	bool bRet = false;
	do 
	{
		CCSprite* pSprite = CCSprite::create("tool_010.png");
		m_pSprite = NULL;
		m_pSprite = pSprite;
		m_pMap = deGameManager->getMap();
		bRet = true;
	} while (0);

	return bRet;
}

void CMapSprite04::changetTexture(CMap::MapData& data)
{
	CCTexture2D* texture;
	if (data.type == eMT_Piranha_Open)
	{
		texture = CCTextureCache::sharedTextureCache()->addImage("tool_001.png");
	}
	else if(data.type == eMT_Piranha_Close)
	{
		texture = CCTextureCache::sharedTextureCache()->addImage("tool_010.png");
	}

	m_pSprite->setTexture(texture);

}

void CMapSprite04::updateAll()
{
	m_pMap = deGameManager->getMap();

	CMap::MapData* data = (CMap::MapData*)m_pSprite->getUserData();

	if (data->eating)
	{
		return;
	}
	
	if (data->type == eMT_Piranha_Open)
	{
		this->judgeFood(*data);
	}
}

void CMapSprite04::judgeFood(CMap::MapData& data)
{
	int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	int nPlayerCount = 0;
	for(int k = 0; k < 4; ++k)
	{
		int x = data.x + dir[k][0];
		int y = data.y + dir[k][1];

		if(m_pMap->validateCoord(x, y))
		{
			CMap::MapData& food = *(m_pMap->getMapData(x, y));

			switch (food.type)
			{
			case eMT_Piranha_Food:
				{
					data.eating = true;
					this->eat(data, food);
					return;
				}
				break;
			case eMT_Player:
				nPlayerCount ++;
				break;
			default:
				break;
			}		
		}
	}

	if (nPlayerCount > 0 && m_pMap->m_pPlayer->live && !data.eating)
	{
		data.pSprite->runAction(CMapSprite04::killPlayerAction());
	}
}

CCAction* CMapSprite04::killPlayerAction()
{
	CCArray *Array = CCArray::createWithCapacity(6);  
	char str[30];
	for(int i = 1;i < 7; i++)
	{
		sprintf(str, "tool_001_00%02d.png", i);
		Array->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(Array, deKillPlayerActionDuration);
	CC_SAFE_DELETE(Array);
	CCAnimate* animate = CCAnimate::create(animation);
	CCCallFunc *pCallBack = CCCallFunc::create(this, callfunc_selector(CMapSprite04::killPlayerActionCB));
	CCAction* action = (CCAction*)CCSequence::create(animate, pCallBack,NULL);
	return action;

}

void CMapSprite04::killPlayerActionCB()
{
	m_pMap->m_pPlayer->pItem->playerDead1();
}

void CMapSprite04::judgeWakeUp(CMap::MapData& data)
{
	int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	for(int k = 0; k < 4; ++k)
	{
		int x = data.x + dir[k][0];
		int y = data.y + dir[k][1];

		if(m_pMap->validateCoord(x, y))
		{
			CMap::MapData& to = *(m_pMap->getMapData(x, y));

			if (to.type == eMT_Player)
			{
				this->wakeUp();
			}	
		}
	}
}

void CMapSprite04::eat(CMap::MapData& data, CMap::MapData& food)
{
	data.eating = true;
	food.pItem->endAction(food);
	this->eatAction(data, food);
}

void CMapSprite04::eatAction(CMap::MapData& data, CMap::MapData& food)
{
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("tool_001.png");
	m_pSprite->setTexture(texture);
	CCBlink* blink = CCBlink::create(dePiranha_Eating_Duration, 20);
	//CCDelayTime* pDelay = CCDelayTime::create(dePiranha_Eating_Duration);
	CCCallFuncND* pCallBack = CCCallFuncND::create(this, callfuncND_selector(CMapSprite04::eatCB), &data);
	CCActionInterval* seq = (CCActionInterval*)(CCSequence::create(blink, pCallBack,NULL));
	m_pSprite->runAction(seq);
}

void CMapSprite04::eatCB(CCNode* pNode, void* pData)
{
	CMap::MapData* pMapData = (CMap::MapData*)pData;
	if (!pMapData->live)
	{
		return;
	}
	m_pSprite->stopAllActions();
	this->close();
}



void CMapSprite04::wakeUp()
{
	CCDelayTime* pDelay = CCDelayTime::create(dePiranha_Open_Duration);
	CCCallFunc* pCallBack = CCCallFunc::create(this, callfunc_selector(CMapSprite04::wakeUpCB));
	m_pSprite->runAction(CCSequence::create(pDelay, pCallBack, NULL));
}

void CMapSprite04::wakeUpCB()
{
	CMap::MapData* data = (CMap::MapData*)m_pSprite->getUserData();
	data->type = eMT_Piranha_Open;
	data->eating = false;
	this->changetTexture(*data);
}

void CMapSprite04::close()
{
	CMap::MapData* data = (CMap::MapData*)m_pSprite->getUserData();
	data->type = eMT_Piranha_Close;
	data->eating = false;
	this->changetTexture(*data);
}

void CMapSprite04::startUpdate()
{
	this->scheduleUpdate();
}

void CMapSprite04::stopUpdate()
{
	this->unscheduleUpdate();
}