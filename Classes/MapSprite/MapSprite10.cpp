#include "MapSprite10.h"
using namespace cocos2d;

const char* g_MapName2[4] =
{
	"map_001_01.png",
	"map_001_02.png",
	"map_002_01.png",
	"map_002_02.png",
};

bool CMapSprite10::initSprite()
{
	bool bRet = false;
	do 
	{
		CCSpriteBatchNode* pMapBatchNode[4];
		for (int i = 0; i != 4; i++)
		{
			pMapBatchNode[i] = CCSpriteBatchNode::create(g_MapName2[i]);
			this->addChild(pMapBatchNode[i]);
		}

		int random =CCRANDOM_0_1() * 100;
		int nRand = random % 4;
		CCSprite* pSprite = CCSprite::createWithTexture(pMapBatchNode[nRand]->getTexture());
		m_pSprite = pSprite;
		m_pMap = deGameManager->getMap();
		bRet = true;
	} while (0);

	return bRet;

}