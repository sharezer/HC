#pragma once

#include "cocos2d.h"
#include <vector>
#include "SimpleDPad.h"


#define MapDataTag_Moving 0x0001

#define Map_Width 17
#define Map_Height 12
#define Map_MaxLenght 40

struct tagMapSaveData
{
	int data[Map_MaxLenght][Map_MaxLenght];
};

class CMapSprite;

class CMap : public cocos2d::CCLayer, public SimpleDPadDelegate
{

public:
	CREATE_FUNC(CMap);

	typedef struct tagMapData
	{
		CMapSprite* pItem;
		cocos2d::CCSprite* pSprite;
		cocos2d::CCPoint pos;
		int type;
		int tag;
		int x, y;
		bool live;
		bool eating;
		void reset()
		{
			pItem = NULL;
			pSprite = NULL;
			tag = 0;
			live = false;
			eating = false;
		}
	}MapData;
	//typedef std::vector<MapData> _tmapVec;

	 std::vector<tagMapSaveData> g_MapSaveData;

public:
	MapData* getMapData(int x, int y);
	void showGameOver();
	void showSkipMatchAction();
	void skipMacth();

	void wakeUpPiranha(MapData& data);
	void wakeUpPiranhaCB(cocos2d::CCNode* pNode, void* pData);

	void gainObject(MapData&data, int type);
	void objectDisppear(MapData& data);
	void objectDisppearCB(cocos2d::CCNode* pNode, void* pData);

	void objectMove(MapData& from, MapData& to);
	void objectMoveCB(cocos2d::CCNode* pNode, void* pData);

	void startTimeBomb(cocos2d::CCNode* pNode, void* pData);
	void bombObjectCB(cocos2d::CCNode* pNode, void* pData);

	void judgePiranha();

	bool judgeFit(MapData& data);

	void updateGold(int Gold);
	void updateSocre(int Score);

	bool validateCoord(int x, int y);

	void loadMap(int idx);

private:
	bool load();
	void save();

	void saveMap(int idx);

	bool init();
	void update(float dt);
	void menuCallBack(CCObject* pSender);

	virtual void didChangeDirectionTo(SimpleDPad *simpleDPad, cocos2d::CCPoint direction);
	virtual void isHoldingDirection(SimpleDPad *simpleDPad, cocos2d::CCPoint direction);
	virtual void simpleDPadTouchEnded(SimpleDPad *simpleDPad);
	
	bool collision(MapData& from, MapData& to, cocos2d::CCPoint& direction);
	void createMap(int sx, int sy, int row, int column);
	

public:
	cocos2d::CCArray* piranhaA;
	MapData* m_pPlayer;
	cocos2d::CCLayer* m_pMapL;
	cocos2d::CCLayer* m_pBGL;
	bool m_bGameOver;
	bool m_bWin;
	bool m_bSleep;
/*	int nBeKill;*/

	CC_SYNTHESIZE_READONLY(int, m_nKeyCount, KeyCount);
	CC_SYNTHESIZE(bool, m_bPlayerDir, PlayerDir);

private:
	//cocos2d::CCLayer*  m_pEditL;
	cocos2d::CCSprite* m_pMapSetS;
	cocos2d::CCSprite* m_pUnitShowS;
	cocos2d::CCPoint m_pLastDirection;

	MapData m_oDataSet[Map_Width][Map_Height];
	SimpleDPad* m_pSimpleDpad;
	cocos2d::CCRect m_oGamingRect;

	long oldTime, nowTime;
	float useTime;
	
};
