#include "MapSprite15.h"

USING_NS_CC;

bool CMapSprite15::initSprite()
{
	bool bRet = false;
	do 
	{
		CCSprite* pSprite = CCSprite::create("tool_006.png");
		m_pSprite = pSprite;
		m_pMap = deGameManager->getMap();
		bRet = true;
	} while (0);

	return bRet;
}