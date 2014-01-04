#include "PauseL.h"
#include "MenuItemImageSub.h"

#include "GameManager.h"

using namespace cocos2d;

enum ePauseLBtn
{
	e_Music,
	e_Sound,
	e_Menu,
	e_Restart,
	
	e_BtnCount,
};

const char* g_PauseNormalSprite[e_BtnCount] =
{
	"interface_02_009.png",
	"interface_02_011.png",
	"interface_02_017.png",
	"interface_02_022.png",
};

const char* g_PauseSelectSprite[e_BtnCount] =
{
	"interface_02_009-02.png",
	"interface_02_011-02.png",
	"interface_02_017-02.png",
	"interface_02_022-02.png",	
};

#define Create_Sprite(varName, fileName, pos, ez)\
	CCSprite* varName = CCSprite::create(fileName);\
	varName->setPosition(pos);\
	this->addChild(varName, ez);

bool CPauseL::init()
{
	bool bRet = false;
	do 
	{	
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		CCSprite* pBg1 = CCSprite::create("game_mask.png");
		pBg1->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		this->addChild(pBg1, 1);

		CCSprite* pBg2 = CCSprite::create("interface_02_008.png");
		pBg2->setAnchorPoint(ccp(0.5, 0));
		pBg2->setPosition(ccp(winSize.width / 2, 0));
		this->addChild(pBg2, 2);
		float fX,fY;
		fX = 550.0f;
		fY = 50.0f;
		CMenuItemImageSub* pItem[e_BtnCount];
		int j = 0;
		for (int i = 0; i < e_BtnCount; i++)
		{
			if (i == 3)
			{
				fX += 60;
				fY -= 20;
			}
			pItem[j] = Create_MenuItemImageSub(g_PauseNormalSprite[j], g_PauseSelectSprite[j], j, ccp(fX, fY), this, CPauseL::menuCallBack);
			pItem[j]->setAnchorPoint(ccp(0.5, 0));
			j++;
			fX += 100.0f;
		}
		CCMenu* pMenu = CCMenu::create(pItem[0], pItem[1], pItem[2], pItem[3], NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu, 3);
		bRet = true;

	} while (0);
	return bRet;

}

void CPauseL::menuCallBack(cocos2d::CCObject * pSender)
{
	if (!this->isVisible())
	{
		return;
	}
	CCMenuItemLabel * pItem = (CCMenuItemLabel *) pSender;
	switch (pItem->getTag())
	{
	case e_Sound:
		CPauseL::clickSound();
		break;
	case e_Music:
		CPauseL::clickMusic();
		break;
	case e_Restart:
		CPauseL::clickRestart();
		break;
	case e_Menu:
		CPauseL::clickMenu();
		break;
	default:
		break;
	}
}

void CPauseL::clickResume()
{

}

void CPauseL::clickSound()
{

}

void CPauseL::clickMusic()
{

}

void CPauseL::clickRestart()
{
	deGameManager->changeState(CGameManager::eGameStateGaming);
}

void CPauseL::clickMenu()
{
	deGameManager->changeState(CGameManager::eGameStateMenu);
}

void CPauseL::clickChangeHam()
{

}

