#include "Map.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "GamingS.h"
//#include "ActionSprite.h"
#include "MapSprite.h"


using namespace cocos2d;
using namespace std;

#define MAP_OBJECT_TAG					5
#define deUnit_Width					56
#define deUnit_Height					56

#define deMoving_Duration				0.5f
#define dePiranha_Open_Duration			1.0f
#define dePiranha_Eating_Duration		10.0f
#define deBomb_Duration					10.0f
#define deJudge_Piranha_dt				0.1f
#define deMapCount						20

#define deGoldForBox					500
#define deGoldForFlower					50
#define deGoldForDoor					60
#define deGoldForObstacle				80

#define deStandByTime					20000

enum eMenuTag
{
	eMT_EditMap,
	eMT_Play,
	eMT_Next,
	eMT_Last,
	eMT_Save,
    eMT_Restart,
};

#ifdef WIN32
#define Map_File_Name "../Data/map.dat"
#else
string path = "map.dat";
string path2 = cocos2d::CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(path.c_str());
#define Map_File_Name path2.c_str()
#endif

//#define dbFor_Create_Init_Data

#ifdef dbFor_Create_Init_Data
void createInitData()
{

//    string path = Map_File_Name;
//    path = cocos2d::CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(path.c_str());
	FILE *fp = fopen(Map_File_Name , "wb");
	if (fp == 0)
		return;
	int mapCount = 15;
	fwrite(&mapCount, 1, sizeof(mapCount), fp);

	tagMapSaveData data;
	memset(&data, 0, sizeof(data));
	for (int i = 0; i < mapCount; ++i) 
	{
		fwrite(&data, 1, sizeof(data), fp);
	}
	fclose(fp);
}
#endif

bool CMap::load()
{
	if(!g_MapSaveData.empty())
		return true;
    
	FILE *fp = fopen(Map_File_Name , "rb");
	if (fp == 0)
		return false;

	int count;
	if (fread(&count, 1, sizeof(count), fp) != sizeof(count))
	{
		return false;
	}

	tagMapSaveData data;
	for(int i = 0; i < count; ++i)
	{
		if (fread(&data, 1, sizeof(data), fp) == sizeof(data)) 
		{
			g_MapSaveData.push_back(data);
		}
		else
		{
			return false;
		}
	}
	fclose(fp);
	return true;
}

void CMap::save()
{
	FILE *fp = fopen(Map_File_Name , "wb");
	if (fp == 0)
		return;
	int mapCount = g_MapSaveData.size();
	fwrite(&mapCount, 1, sizeof(mapCount), fp);

	for (int i = 0; i < mapCount; ++i) 
	{
		fwrite(&g_MapSaveData[i], 1, sizeof(g_MapSaveData[i]), fp);
	}
	fclose(fp);
}

void CMap::loadMap(int idx)
{
	this->unscheduleUpdate();
	if (m_pMapL)
	{
		m_pMapL->removeFromParentAndCleanup(true);
		m_pMapL = NULL;
	}
	
	if(!this->load())
		return;

	if(idx >= (int)g_MapSaveData.size())
		return;

	tagMapSaveData& mapData = g_MapSaveData.at(idx);

	m_pMapL = deMapSpriteManager->createMapLayer(idx, mapData, this);
	m_pMapL->setPosition(ccp(9, 22));
	this->addChild(m_pMapL, 2);
	m_pLastDirection = ccp(1.0f, 0.0f);	
	this->setPlayerDir(false);
	useTime = 0.0f;

	this->scheduleUpdate();

}

void CMap::saveMap(int idx)
{
	if(idx >= (int)g_MapSaveData.size())
		return;

	tagMapSaveData& mapData = g_MapSaveData.at(idx);
	for(int i = 0; i < Map_Width; ++i)
	{
		for(int j = 0; j < Map_Height; ++j)
		{
			mapData.data[i][j] = m_oDataSet[i][j].type;
		}
	}
	this->save();
}


bool CMap::init()
{
	bool bRet = false;
	do 
	{

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CGameManager::GameStartInfo& info = deGameManager->getGameStartInfo();


		CCSprite* pBG = CCSprite::create("interface_02_021.png");
		pBG->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		this->addChild(pBG, 3);

		m_pPlayer = NULL;
		m_nKeyCount = 0;
		m_bGameOver = false;
		m_bWin = false;
		m_bSleep = false;

		struct cc_timeval nVal;
		CCTime::gettimeofdayCocos2d(&nVal, NULL);
		oldTime = nVal.tv_sec * 1000 + nVal.tv_usec / 1000;

// 		CCLayer* pLayer = CCLayer::create();
// 		m_pMapL = pLayer;
// 		this->addChild(m_pMapL, 2);

		m_pMapL = NULL;
		m_pBGL = NULL;

		piranhaA = CCArray::create();
		piranhaA->retain();		

#ifdef dbFor_Create_Init_Data
		createInitData();
#endif
		this->createMap(deUnit_Width, deUnit_Height, Map_Width, Map_Height);

#define createItemLabel(idx, var, name, tag, pos) CCLabelTTF* label##idx = CCLabelTTF::create(name, "Arial", 28);\
		var = CCMenuItemLabel::create(label##idx , this, menu_selector(CMap::menuCallBack) );\
		var->setPosition(pos);\
		var->setTag(tag)   

		m_pSimpleDpad = SimpleDPad::dPadWithFile(CCString::create("pd_dpad.png"), 100);
		m_pSimpleDpad->setPosition(ccp(924, 100));
		m_pSimpleDpad->setDelegate(this);
		m_pSimpleDpad->setOpacity(150);
		this->addChild(m_pSimpleDpad, 4);

		bRet = true;

	} while (0);

	return bRet;
}

void CMap::update(float dt)
{
	if (m_bWin || m_bGameOver)
	{
		return;
	}
	useTime += dt;
	deGameManager->getGamingS()->changeTime(useTime);

	if(m_pPlayer->tag & MapDataTag_Moving)
			return;

	this->judgePiranha();

	struct cc_timeval nVal;
	CCTime::gettimeofdayCocos2d(&nVal, NULL);
	nowTime = nVal.tv_sec * 1000 + nVal.tv_usec / 1000;

	if (nowTime - oldTime > deStandByTime && !m_bSleep)
	{
		m_pPlayer->pItem->standByAction();
	}
}

void CMap::judgePiranha()
{
	for(int i = 0; i < Map_Width; ++i)
	{
		for(int j = 0; j < Map_Height; ++j)
		{
			CMap::MapData& data = *this->getMapData(i, j);

			if(data.type == eMT_Piranha_Close || data.type == eMT_Piranha_Open)
			{
				if (!data.live)
				{
					return;
				}

				data.pItem->updateAll();

			}
		}
	}
}

bool CMap::judgeFit(MapData& data)
{
	bool bRet = false;
	int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	for(int k = 0; k < 4; ++k)
	{
		int x = data.x + dir[k][0];
		int y = data.y + dir[k][1];

		if(this->validateCoord(x, y))
		{
			MapData& fit = *(this->getMapData(x, y));
			if(fit.type == eMT_Obstacle3)
			{
				this->gainObject(fit, fit.type);
				bRet = true;
			}
		}
	}
	return bRet;
}

void CMap::didChangeDirectionTo(SimpleDPad *simpleDPad, CCPoint direction)
{
	if (deGameManager->getGamingS()->m_pPauseL->isVisible())
	{
		return;
	}
	
	struct cc_timeval nVal;
	CCTime::gettimeofdayCocos2d(&nVal, NULL);
	oldTime = nVal.tv_sec * 1000 + nVal.tv_usec / 1000;

	if(!m_pPlayer->live || m_bGameOver || m_bWin)
		return;

	if(m_pPlayer->tag & MapDataTag_Moving)
		return;

	if (m_bSleep)
	{
		m_pPlayer->pItem->playerWakeUp();
		return;
	}

	int i = m_pPlayer->x;
	int j = m_pPlayer->y;

	i += direction.x;
	j += direction.y;

	if(this->validateCoord(i, j))
	{
		MapData& nextData = *(this->getMapData(i, j));
		if(this->collision(*m_pPlayer, nextData, direction))
		{
			m_pPlayer->pItem->playerMove(direction, nextData);		
		}
	}
}

void CMap::isHoldingDirection(SimpleDPad *simpleDPad, CCPoint direction)
{
	if(!m_pPlayer->live || m_bGameOver || m_bWin)
		return;
	this->didChangeDirectionTo(simpleDPad, direction);
}

void CMap::simpleDPadTouchEnded(SimpleDPad *simpleDPad)
{
	if(!m_pPlayer || !m_pPlayer->live)
		return;

	if (m_bGameOver || m_bWin)
	{
		return;
	}
	
	if(m_pPlayer->tag & MapDataTag_Moving)
		return;
}

void CMap::objectMove(MapData& from, MapData& to)
{
	CCMoveTo* pMoveTo = CCMoveTo::create(deMoving_Duration, to.pos);
	CCCallFuncND* pCallBack = CCCallFuncND::create(this, callfuncND_selector(CMap::objectMoveCB), &to);
	from.pSprite->runAction(CCSequence::create(pMoveTo, pCallBack, NULL));
	from.pSprite->setUserData(&to);
	from.tag = 0;

	to.pItem = from.pItem;
	to.pSprite = from.pSprite;
	to.type = from.type;
	to.live = from.live;

	from.pItem = NULL;
	from.pSprite = NULL;
	from.type = eMT_Road;
	from.live = false;
}

void CMap::objectMoveCB(CCNode* pNode, void* pData)
{
	MapData* to = (MapData*)pNode->getUserData();
	if(to->type != eMT_Road)
	{
		switch (to->type)
		{
		case eMT_Bomb:
			to->pItem->workAction(*to);
			/*this->startTimeBomb(pNode, to);*/
			break;
		case eMT_Obstacle3:
			if (this->judgeFit(*to))
			{
				this->gainObject(*to, to->type);
			}		
			break;
		default:
			break;
		}
	}

}

void CMap::gainObject(MapData&data, int type)
{
	this->objectDisppear(data);
}

void CMap::objectDisppear(MapData& data)
{
	if (!data.live)
	{
		return;
	}
	this->unscheduleUpdate();
	data.pItem->endAction(data);
	data.pSprite = NULL;
	data.type = eMT_Road;
	data.live = false;
	data.pItem->clearUp(data);
	this->scheduleUpdate();
}

void CMap::objectDisppearCB(CCNode* pNode, void* pData)
{
	pNode->removeFromParentAndCleanup(true);
}

void CMap::showGameOver()
{
	m_bGameOver = true;
	deGameManager->getGamingS()->gameOver();
}

void CMap::showSkipMatchAction()
{
	m_bWin = true;
	this->stopAllActions();
	m_pPlayer->pItem->changeAction(kActionStateSkipMatch);
}

void CMap::skipMacth()
{
	m_pPlayer->pSprite->setOpacity(0);
	deGameManager->getGamingS()->win();
}


bool CMap::collision(MapData& from, MapData& to, cocos2d::CCPoint& direction)
{
	bool bRet = false;
	if(to.type != eMT_Road)
	{
		eMapType type = (eMapType)to.type;
		switch (type)
		{
		case eMT_NotDefine:
			break;
		case eMT_Road:
			break;

		case eMT_Door_Lock:
			if (m_nKeyCount > 0)
			{
				m_nKeyCount--;
				to.pItem->endAction(to);
				bRet = false;
			}
			break;

		case eMT_Key:
			if (m_nKeyCount == 0)
			{			
				this->gainObject(to, type);
				m_nKeyCount++;
				bRet = true;
			}
			break;
		case eMT_Flower:
			{
				/*this->updateGold(deGoldForFlower);*/
				this->updateSocre(1000);
				this->gainObject(to, type);
				bRet = true;
			}
			break;
		case eMT_Gold:
			{
				this->updateGold(deGoldForFlower);
				this->gainObject(to, type);
				bRet = true;
			}
			break;
		case eMT_EndPos:
			{
				/*this->gainObject(to, type);*/
				m_bWin = true;
				bRet = true;
			}
			break;
		case eMT_Poisonous_Mushroom:
			{
				this->gainObject(to, type);
				bRet = true;
			}
			break;
		
		case eMT_Wall1:
			break;
		case eMT_Wall2:
			break;
		case eMT_Obstacle1:
			break;

		case eMT_Piranha_Food:
		case eMT_Obstacle2:
		case eMT_Obstacle3:
		case eMT_Bomb:
			{
				int i = to.x + direction.x;
				int j = to.y + direction.y;
				MapData* pNextData = this->getMapData(i, j);
				if(pNextData)
				{
					MapData& nextData = *pNextData;
					if(nextData.type == eMT_Road)
					{
						this->objectMove(to, nextData);
						bRet = true;
					}
				}
			}
			break;
		default:
			break;
		}
	}
	else
	{
		bRet = true;
	}
	return bRet;
}

void CMap::createMap(int sx, int sy, int row, int column)
{
	CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create("map_003.png");  
	this->addChild(batchNode);
	CCLayer* pLayer = CCLayer::create();
	pLayer->setPosition(ccp(9, 22));
	int x, y;
	x = sx;
	for(int i = 0; i < row; ++i)
	{
		y = sy;
		for(int j = 0; j < column; ++j)
		{
			CCSprite* pBg = CCSprite::createWithTexture(batchNode->getTexture());
			pBg->setPosition(ccp(x, y));
			pBg->setAnchorPoint(ccp(0.5, 0.6));
			pLayer->addChild(pBg, 0);

			MapData& data = m_oDataSet[i][j];
			data.reset();
			data.pItem = NULL;
			data.pSprite = NULL;
			data.type = eMT_Road;
			data.live = false;
			data.x = i;
			data.y = j;
			data.pos = ccp(x, y);
			y += sy;
		}
		x += sx;
	}

	m_pBGL = pLayer;
	this->addChild(m_pBGL, 1);
}

CMap::MapData* CMap::getMapData(int x, int y)
{
	if(x >= Map_Width || y >= Map_Height)
		return NULL;

	return &m_oDataSet[x][y];
}

bool CMap::validateCoord(int x, int y)
{
	if(x < 0 || y < 0 || x >= Map_Width || y >= Map_Height)
		return false;
	return true;
}

void CMap::updateGold(int Gold)
{
	//deGameManager->getGamingS()->changeGold(Gold);
}

void CMap::updateSocre(int Score)
{
	deGameManager->getGamingS()->changeScore(Score);
}