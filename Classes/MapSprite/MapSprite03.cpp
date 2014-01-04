#include "MapSprite03.h"

USING_NS_CC;

bool CMapSprite03::initSprite()
{
	bool bRet = false;
	do 
	{
		CCSprite* pSprite = CCSprite::create("items_002.png");
		m_pSprite = pSprite;
		m_pMap = deGameManager->getMap();
		bRet = true;
	} while (0);

	return bRet;
}