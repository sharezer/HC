#pragma once
#include "cocos2d.h"
#include "ActionSprite.h"
#include "GameManager.h"
#include "Map.h"

enum eMapType
{
	eMT_NotDefine,
	eMT_Road,	//1
	eMT_Door_Lock,	//2
	eMT_Key,	//3

	eMT_Piranha_Close,	//4
	eMT_Piranha_Open,	//5
	eMT_Piranha_Food,	//6

	eMT_Flower,	//7

	eMT_EndPos,	//8

	eMT_Bomb,	//9

	eMT_Wall1,	//10
	eMT_Wall2,	//11

	eMT_Gold,	//12

	eMT_Obstacle1,	//13¶¾Ò©
	eMT_Obstacle2,	//14Çò
	eMT_Obstacle3,	//15¾§Ìå

	eMT_Player,	//16
	eMT_Poisonous_Mushroom,	//17
};

class CMapSprite : public cocos2d::CCLayer
{
public:
	cocos2d::CCSprite* m_pSprite;
	CMap* m_pMap;
public:
	CMapSprite(void);
	~CMapSprite(void);

	CREATE_FUNC(CMapSprite);
	//action methods

	static CMapSprite* getInst();
	cocos2d::CCSprite* createWithMapType(eMapType type, CMap::MapData& data);
	cocos2d::CCSprite* getSprite(){return m_pSprite;}
	cocos2d::CCLayer* createMapLayer(int idx, tagMapSaveData& mapData, CMap* pMap);

	//void update(float dt);
	//virtual void update(float dt);
	
	virtual void updateAll();

	virtual void judgeFood(CMap::MapData& data);
	virtual void wakeUp();
	virtual void wakeUpCB();
	virtual void close();

	virtual void clearUp(CMap::MapData& data);

	virtual void changeAction(eActionState type);
	virtual void playerMove(cocos2d::CCPoint direction, CMap::MapData& nextData);
	virtual void playerWakeUp();
	virtual void standByAction();
	virtual void playerDead1();
	virtual void playerDead2();

	virtual void startUpdate();
	virtual void stopUpdate();

	virtual void changetTexture(CMap::MapData&data);	

	virtual void workAction(CMap::MapData&data);
	virtual void endAction(CMap::MapData&data);

	virtual void beBomb(CMap::MapData&data);
	virtual void beBombCB(cocos2d::CCNode* pNode, void* pData);

private:
	bool init();

public:
	virtual bool initSprite();
};

#define deMapSpriteManager	CMapSprite::getInst()