#include "MenuStartL.h"
#include "MenuItemImageSub.h"

using namespace cocos2d;


// enum eMenuTag
// {
// 	eMT_Start,
// 	eMT_Sound,
// 	eMT_Music,
// 	eMT_AboutUS,
// 	eMT_BtnCount,
// };
enum eMenuTag
{
	eMT_Start,
	eMT_MusicOn,
	eMT_MusicOff,
	eMT_SoundOn,
	eMT_SoundOff,
	eMT_AboutUS,
	eMT_BtnCount,
};

const char* g_MenuSprite[eMT_BtnCount] =
{
	"interface_01_002.png",
	"interface_01_004.png",
	"interface_01_005.png",
	"interface_01_006.png",
	"interface_01_007.png",
	"interface_01_008.png",
};

const CCPoint menuPos[eMT_BtnCount] =
{
	ccp(512, 70),
	ccp(800, 50),
	ccp(800, 50),
	ccp(870, 50),
	ccp(870, 50),
	ccp(940, 50),

};

bool CMenuStartL::init()
{
	bool bRet = false;
	do
	{

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite* pBG = CCSprite::create("interface_01_BG.png");
		pBG->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		this->addChild(pBG);

		CMenuItemImageSub* pBtnItem[eMT_BtnCount];
		for (int i = 0; i < eMT_BtnCount; i++)
		{
			
			pBtnItem[i] = Create_MenuItemImageSub(g_MenuSprite[i], g_MenuSprite[i], i, menuPos[i], this, CMenuStartL::menuCallBack);
		}

		CCMenu *menu = CCMenu::create( pBtnItem[0], pBtnItem[1], pBtnItem[2], pBtnItem[3], pBtnItem[4], pBtnItem[5], NULL);    
		menu->setPosition( CCPointMake(0,0) );
		this->addChild(menu, 1);

		bRet = true;
	} while (0);

	return bRet;
}

void CMenuStartL::update(float dt)
{

}

void CMenuStartL::vgEnter(bool bRight)
{
	this->setVisible(true);
	this->setPosition(ccp(-320, 0));
	CCMoveTo* pMoveTo = CCMoveTo::create(0.5f, ccp(0, 0));
	this->runAction(pMoveTo);
}

void CMenuStartL::vgExit(bool bRight)
{
	this->setPosition(ccp(0, 0));
	CCMoveTo* pMoveTo = CCMoveTo::create(0.3f, ccp(320, 0));
	this->runAction(pMoveTo);
}

void CMenuStartL::mouseDown(cocos2d::CCPoint& pos)
{

}

void CMenuStartL::mouseMove(cocos2d::CCPoint& pos)
{

}

void CMenuStartL::mouseUp(cocos2d::CCPoint& pos)
{

}

void CMenuStartL::menuCallBack(CCObject * pSender)
{
	CCNode* pMenu = (CCNode*)pSender;
	eMenuTag tag = (eMenuTag)(pMenu->getTag());
	switch (tag)
	{
	case eMT_Start:
		this->start();
		break;

	case eMT_MusicOn:
		this->sound();
		break;

	case eMT_MusicOff:
		this->store();
		break;

	case eMT_SoundOn:
		this->sound();
		break;

	case eMT_SoundOff:
		this->store();
		break;

	case eMT_AboutUS:
		this->aboutUs();
		break;
	default:
		break;
	}
}


void CMenuStartL::start()
{
	CMenuSence* pMenuSence = (CMenuSence*)this->getParent();
	pMenuSence->nextUI();
}

void CMenuStartL::sound()
{

}

void CMenuStartL::store()
{

}

void CMenuStartL::share()
{

}

void CMenuStartL::aboutUs()
{

}
