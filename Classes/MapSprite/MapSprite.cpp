#include "MapSprite.h"
#include "MapSprite02.h"
#include "MapSprite03.h"
#include "MapSprite04.h"
#include "MapSprite05.h"
#include "MapSprite06.h"
#include "MapSprite07.h"
#include "MapSprite08.h"
#include "MapSprite09.h"
#include "MapSprite10.h"
#include "MapSprite12.h"
#include "MapSprite13.h"
#include "MapSprite14.h"
#include "MapSprite15.h"
#include "MapSprite16.h"
#include "MapSprite17.h"

using namespace cocos2d;
#define deMoveDelayTime		0.5f

#define deNewMapSprite(idx)		{ CMapSprite##idx* pMapSprite = new CMapSprite##idx();\
		pMapSprite->initSprite();\
		pSprite = pMapSprite->getSprite(); \
		data.pItem = pMapSprite; }\
		break

CMapSprite::CMapSprite(void)
{
	m_pSprite = NULL;
}

CMapSprite::~CMapSprite(void)
{

}

bool CMapSprite::init()
{
	deActionSprite->initFrameCache();
	return true;
}

CMapSprite* CMapSprite::getInst()
{
	static CMapSprite* s_pInst = NULL;
	if(s_pInst == NULL)
	{
		s_pInst = new CMapSprite();
		s_pInst->init();
	}
	return s_pInst;
}

bool CMapSprite::initSprite()
{
	return true;
}


cocos2d::CCSprite* CMapSprite::createWithMapType(eMapType type, CMap::MapData& data)
{
	CCSprite* pSprite = NULL;

	//CMap* pMap = deGameManager->getMap();

	switch (type)
	{
	case eMT_NotDefine:
		break;
	case eMT_Road:
		break;
	case eMT_Door_Lock:
		deNewMapSprite(02);
	case eMT_Key:
		deNewMapSprite(03);
	case eMT_Piranha_Close:
		deNewMapSprite(04);
	case eMT_Piranha_Open:
		deNewMapSprite(05);
	case eMT_Piranha_Food:
		deNewMapSprite(06);
	case eMT_Flower:
		deNewMapSprite(07);
	case eMT_EndPos:
		deNewMapSprite(08);
	case eMT_Bomb:
		deNewMapSprite(09);
	case eMT_Wall1:
	case eMT_Wall2:
		deNewMapSprite(10);
	case eMT_Gold:
		deNewMapSprite(12);
	case eMT_Obstacle1:
		deNewMapSprite(13);
	case eMT_Obstacle2:
		deNewMapSprite(14);
	case eMT_Obstacle3:
		deNewMapSprite(15);
	case eMT_Player:
		deNewMapSprite(16);
	case eMT_Poisonous_Mushroom:
		deNewMapSprite(17);
	default:
		break;
	}
	return pSprite;
}

cocos2d::CCLayer* CMapSprite::createMapLayer(int idx, tagMapSaveData& mapData, CMap* pMap)
{
	CCLayer* pLayer = CCLayer::create();
	m_pMap = deGameManager->getMap();

	for(int i = 0; i < Map_Width; ++i)
	{
		for(int j = 0; j < Map_Height; ++j)
		{
			CMap::MapData& data = *m_pMap->getMapData(i, j);
			data.reset();
			data.type = mapData.data[i][j];

			if(data.type == eMT_Road || data.type == eMT_NotDefine || data.type == -1)
			{
				data.pItem = NULL;
				data.pSprite = NULL;
				data.type = eMT_Road;
				data.live = false;
				data.eating = false;
			}
			else
			{	
				data.pItem = NULL;
				data.pSprite = NULL;
				data.live = true;
				data.eating = false;
				CCSprite* pSprite;

				pSprite = this->createWithMapType((eMapType)data.type, data);

				if (data.type == eMT_Player)
				{
					m_pMap->m_pPlayer = &data;
				}			
				pLayer->addChild(pSprite, Map_Height - j, data.type);

				pSprite->setPosition(data.pos);
				data.pSprite = pSprite;
				data.pSprite->setUserData(&data);

				if (data.type == eMT_Piranha_Open || data.type == eMT_Piranha_Close)
				{
					m_pMap->piranhaA->addObject(data.pSprite);
				}
		
			}
		}
	}
	return pLayer;
}

void CMapSprite::clearUp(CMap::MapData& data)
{
	data.pSprite = NULL;
	data.type = eMT_Road;
	data.live = false;
	CC_SAFE_RELEASE(data.pItem);
	data.pItem = NULL;
}

void CMapSprite::updateAll()
{

}

void CMapSprite::judgeFood(CMap::MapData& data)
{

}

void CMapSprite::wakeUp()
{

}

void CMapSprite::wakeUpCB()
{

}

void CMapSprite::close()
{

}

void CMapSprite::changeAction(eActionState type)
{

}

void CMapSprite::playerMove(CCPoint direction, CMap::MapData& nextData)
{

}

void CMapSprite::playerWakeUp()
{

}

void CMapSprite::standByAction()
{

}

void CMapSprite::startUpdate()
{

}
void CMapSprite::stopUpdate()
{

}

void CMapSprite::playerDead1()
{

}

void CMapSprite::playerDead2()
{

}

void CMapSprite::changetTexture(CMap::MapData& data)
{

}

void CMapSprite::workAction(CMap::MapData&data)
{

}

void CMapSprite::endAction(CMap::MapData&data)
{
	CCScaleTo* pScaleTo = CCScaleTo::create(deMoveDelayTime, 0);
	CCCallFuncND* pCallBack = CCCallFuncND::create(m_pMap, callfuncND_selector(CMap::objectDisppearCB), &data);
	data.pSprite->runAction(CCSequence::create(pScaleTo, pCallBack, NULL));
}

void CMapSprite::beBomb(CMap::MapData&data)
{
	if (!data.live)
	{
		return;
	}

	m_pMap->unscheduleUpdate();
	this->endAction(data);
	data.pSprite = NULL;
	data.type = eMT_Road;
	data.live = false;
	data.pItem->clearUp(data);
	m_pMap->scheduleUpdate();
}

void CMapSprite::beBombCB(CCNode* pNode, void* pData)
{
	CMap::MapData* pMapData = (CMap::MapData*) pData;
	pMapData->pSprite = NULL;
	pMapData->type = eMT_Road;
	pMapData->live = false;
	/*pMapData->pItem->clearUp(*pMapData);*/
	/*pNode->removeFromParentAndCleanup(true);*/
}