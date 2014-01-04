#include "MapSprite16.h"
using namespace cocos2d;

#define deMoving_Duration		0.5f

bool CMapSprite16::initSprite()
{
	bool bRet = false;
	do 
	{
		CCSprite* pSprite = CCSprite::createWithSpriteFrameName("npc_001_02_01.png");
		pSprite->setAnchorPoint(ccp(0.5, 0.1));
		m_pSprite = pSprite;
		m_pMap = deGameManager->getMap();

// 		CCSprite* pBG = CCSprite::create("npc_BG.png");	
// 		pBG->setPosition(ccp(25, 0));
// 		m_pSprite->addChild(pBG);

		bRet = true;
	} while (0);

	return bRet;

}

void CMapSprite16::changeAction(eActionState type)
{
	CCAction* pAction;
	pAction = deActionSprite->createAnimate(type);
	m_pSprite->runAction(pAction);
}

void CMapSprite16::standByAction()
{
	this->changeAction(kActionStateStandBy2);
	m_pMap->m_bSleep = true;
}

void CMapSprite16::playerMove(CCPoint direction, CMap::MapData& nextData)
{
	if (direction.x)
	{
		if (direction.x > 0)
		{
			m_pSprite->setFlipX(false);
		}
		else
		{
			m_pSprite->setFlipX(true);
		}
		this->changeAction(kActionStateWalkLeft);
	}
	else
	{
		m_pSprite->setFlipX(false);
		if (direction.y > 0)
		{
			this->changeAction(kActionStateWalkUp);
		}
		else
		{
			this->changeAction(kActionStateWalkDown);
		}				
	}

	CCMoveTo* pMoveTo = CCMoveTo::create(deMoving_Duration, nextData.pos);
	CCCallFuncND* pCallBack = CCCallFuncND::create(this, callfuncND_selector(CMapSprite16::playerMoveCB), &nextData);
	CCActionInterval* seq = (CCActionInterval*)(CCSequence::create(pMoveTo, pCallBack, NULL));

	m_pSprite->runAction(seq);
	m_pMap->m_pPlayer->tag = 0;

	nextData.pSprite = m_pMap->m_pPlayer->pSprite;
	nextData.pItem = m_pMap->m_pPlayer->pItem;

	m_pMap->m_pPlayer->pSprite = NULL;
	m_pMap->m_pPlayer->pItem = NULL;
	m_pMap->m_pPlayer->type = nextData.type;
	m_pMap->m_pPlayer->live = false;

	nextData.type = eMT_Player;
	nextData.tag += MapDataTag_Moving;
	nextData.live = true;
	m_pMap->m_pPlayer = &nextData;

}

void CMapSprite16::playerMoveCB(CCNode* pNode, void* pData)
{
	CMap::MapData* pMapData = (CMap::MapData*)pData;
	m_pMap->m_pPlayer->tag &= ~MapDataTag_Moving;

	if (m_pMap->m_bGameOver)
	{
		return;
	}
	m_pSprite->stopAllActions();

	m_pMap->m_pMapL->removeChildByTag(eMT_Player, false);
	m_pMap->m_pMapL->addChild(m_pSprite, Map_Height - m_pMap->m_pPlayer->y + 1, eMT_Player);

	if (m_pMap->m_bWin)
	{
		m_pMap->showSkipMatchAction();
		pMapData->pItem->changetTexture(*pMapData);
		return;
	}

	int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	for(int k = 0; k < 4; ++k)
	{
		int x = m_pMap->m_pPlayer->x  + dir[k][0];
		int y = m_pMap->m_pPlayer->y  + dir[k][1];

		if(m_pMap->validateCoord(x, y))
		{
			CMap::MapData& data = *(m_pMap->getMapData(x, y));
			if (eMT_Piranha_Close == data.type)
			{
				data.pItem->wakeUp();
			}
			else if (eMT_Piranha_Open == data.type)
			{
				data.pItem->judgeFood(data);
			}
			
		}
	}
}

void CMapSprite16::playerWakeUp()
{
	 CCActionInterval* pAct1 = (CCActionInterval*)deActionSprite->createAnimate(kActionStateWakeUp);
	 CCCallFunc* pCallBack = CCCallFunc::create(this, callfunc_selector(CMapSprite16::playerWakeUpCB));
	 m_pSprite->runAction(CCRepeat::create(CCSequence::create(pAct1, pCallBack, NULL), 1));
}

void CMapSprite16::playerWakeUpCB()
{
	m_pSprite->stopAllActions();
	m_pMap->m_bSleep = false;
}

void CMapSprite16::playerDead1()
{
	if (!m_pMap->m_pPlayer->live)
	{
		return;
	}

	m_pMap->m_pPlayer->live = false;
	m_pSprite->stopAllActions();
	this->changeAction(kActionStateDead1);
}

void CMapSprite16::playerDead2()
{
	if (!m_pMap->m_pPlayer->live)
	{
		return;
	}

	m_pMap->m_pPlayer->live = false;
	m_pSprite->stopAllActions();
	this->changeAction(kActionStateDead2);
}