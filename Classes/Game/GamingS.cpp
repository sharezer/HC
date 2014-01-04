#include "GamingS.h"
#include "UserData.h"
#include "MenuItemImageSub.h"
#include "PauseL.h"

using namespace cocos2d;

enum eMenuTag
{
	eMT_Menu,
	eMT_Next,
	eMT_Restart,
	eMT_Pause,
};

const char* g_NormalImage[3] =
{
	"interface_02_017.png",	
	"interface_02_019.png",
	"interface_02_018.png",
};

const char* g_SelectImage[3] =
{
	"interface_02_017-02.png",
	"interface_02_019-02.png",
	"interface_02_018-02.png",
};


void CGamingS::pause()
{

}

void CGamingS::resume()
{

}

// on "init" you need to initialize your instance
bool CGamingS::init()
{
    bool bRet = false;
    do 
    {
		CC_BREAK_IF(! CCLayer::init());

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CGameManager::GameStartInfo& info = deGameManager->getGameStartInfo();

		CCLayer*  pLayer = CCLayer::create();
		m_pGameL = pLayer;
		this->addChild(m_pGameL);

		CMap* pMap = CMap::create();
		m_pGameL->addChild(pMap, 1);
		deGameManager->setMap(pMap);
		pMap->loadMap(info.missionType);

		CPauseL* pPauseL = CPauseL::create();
		pPauseL->setVisible(false);
		m_pPauseL = pPauseL;
		m_pGameL->addChild(m_pPauseL, 3);
		
		/******************************************victoryL start**************************************/
		m_pVictoryL = CCLayer::create();
		m_pVictoryL->setVisible(false);
		this->addChild(m_pVictoryL, 2);

		CCSprite* pMask = CCSprite::create("game_mask.png");
		pMask->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		m_pVictoryL->addChild(pMask, 0);

		m_pSkipSprite = CCSprite::create("interface_02_013.png");
		m_pSkipSprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		m_pVictoryL->addChild(m_pSkipSprite, 1);

		m_pVicturySprite = CCSprite::create("interface_02_014.png");
		m_pVicturySprite->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 70));
		m_pVictoryL->addChild(m_pVicturySprite, 2);

		int nTag = 0;
		float fPx = 427.0f;
		float fPy = 340.0f;
		for (int i = 0; i < 3; i++)
		{
			m_pVicturyMenuItem[i] = Create_MenuItemImageSub(g_NormalImage[i], g_SelectImage[i], nTag, ccp(fPx, fPy), this, CGamingS::menuCallBack);
			fPx += 85;
			nTag++;
		}

		m_pSkipMenu = CCMenu::create(m_pVicturyMenuItem[0], m_pVicturyMenuItem[1], m_pVicturyMenuItem[2], NULL);
		m_pSkipMenu->setPosition(CCPointZero);
		m_pVictoryL->addChild(m_pSkipMenu, 2);	

// 		m_pGameOverSprite = CCSprite::create("gameOver.png");
// 		m_pGameOverSprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
// 		m_pVictoryL->addChild(m_pGameOverSprite, 3);

		/******************************************victoryL end**************************************/

// 		CCLabelTTF* pLabel = CCLabelTTF::create(CCString::createWithFormat("Mission %d", info.missionType + 1)->getCString(), "Arial", 50);
// 		pLabel->setPosition(ccp(winSize.width - 120, winSize.height - 45));
// 		m_pGameL->addChild(pLabel, 3);
// 
// 		m_pMapIdxLabel = pLabel;

		m_nScore = 0;

		m_pScoreLabel = CCLabelTTF::create(CCString::createWithFormat("%d", m_nScore)->getCString(), "interface_02_016", 45);
		m_pScoreLabel->setPosition(ccp(winSize.width - 150, winSize.height - 45));
		m_pGameL->addChild(m_pScoreLabel, 3);
		CCSprite* pScoreBG = CCSprite::create("interface_02_001.png");
		pScoreBG->setPosition(m_pScoreLabel->getPosition());
		m_pGameL->addChild(pScoreBG, 2);

		m_pGoldLabel = CCLabelTTF::create(CCString::createWithFormat("%.1f", 0)->getCString(), "interface_02_016", 45);
		m_pGoldLabel->setPosition(ccp( winSize.width / 2, winSize.height - 45));
		m_pGameL->addChild(m_pGoldLabel, 3);

		CCSprite* pGoldBG = CCSprite::create("interface_02_001.png");
		pGoldBG->setPosition(m_pGoldLabel->getPosition());
		m_pGameL->addChild(pGoldBG, 2);

		CMenuItemImageSub* pPauseBtn = Create_MenuItemImageSub("interface_02_007.png", "interface_02_007.png", eMT_Pause, ccp(70, 700), this, CGamingS::menuCallBack);
		CCMenu* pMenu = CCMenu::create(pPauseBtn, NULL);
		pMenu->setPosition(CCPointZero);
		m_pGameL->addChild(pMenu, 3);

		/* CCLabelTTF* pLabel = CCLabelTTF::create(CCString::createWithFormat("µÚ%d¹Ø", m_nCurMapIdx + 1)->getCString(), "Arial", 50);*/
		this->setTouchEnabled(true);
        bRet = true;
    } while (0);
    return bRet;

}

void CGamingS::menuCallBack(CCObject* pSender)
{
	eMenuTag tag = (eMenuTag)((CCNode*)pSender)->getTag();

	if (tag == eMT_Pause)
	{
		this->clickPause();
	}
	

	if (m_pVictoryL->isVisible())
	{
		eMenuTag tag = (eMenuTag)((CCNode*)pSender)->getTag();
		CGameManager::GameStartInfo& info = deGameManager->getGameStartInfo();
		CUserData::UserDataInfo&UserInfo = CUserData::getInst()->getUserInfo();

		switch (tag)
		{
		case eMT_Menu:
			deGameManager->changeState(CGameManager::eGameStateMenu);	
			break;

		case eMT_Next:
			{
				info.missionType += 1;
				deGameManager->changeState(CGameManager::eGameStateGaming);
			}
			
			break;

		case eMT_Restart:
			deGameManager->changeState(CGameManager::eGameStateGaming);
			break;

		default:
			break;
		}      

	}
}

void CGamingS::gameOver()
{

	CCTexture2D* texture =  CCTextureCache::sharedTextureCache()->addImage("interface_02_015.png");
	m_pVicturySprite->setTexture(texture);
	m_pVicturyMenuItem[1]->setVisible(false);
	m_pVicturyMenuItem[1]->setEnabled(false);
	m_pVictoryL->setVisible(true);

}

void CGamingS::win()
{
	CUserData::UserDataInfo& userInfo = CUserData::getInst()->getUserInfo();
	CGameManager::GameStartInfo& gameInfo = deGameManager->getGameStartInfo();
	if (gameInfo.missionType == userInfo.lock)
	{
		userInfo.lock += 1;
	}
	CUserData::getInst()->save();
	/*deGameManager->changeState(CGameManager::eGameStateMenu);*/
	CCTexture2D* texture =  CCTextureCache::sharedTextureCache()->addImage("interface_02_014.png");
	m_pVicturySprite->setTexture(texture);
	m_pVicturyMenuItem[1]->setVisible(true);
	m_pVicturyMenuItem[1]->setEnabled(true);
	m_pVictoryL->setVisible(true);

//  gameInfo.missionType += 1;
// 	m_pSkipSprite->setVisible(true);
// 	m_pSkipMenu->setVisible(true);
	
}

void CGamingS::changeTime(float fTime)
{
	m_pGoldLabel->setString(CCString::createWithFormat("%.1f", fTime)->getCString());
}

void CGamingS::changeScore(int nScore)
{
	CUserData::UserDataInfo& info = CUserData::getInst()->getUserInfo();
	/*info.score += nScore;*/
	m_nScore += nScore;
	m_pScoreLabel->setString(CCString::createWithFormat("%d", m_nScore)->getCString());	
}

void CGamingS::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	if (m_pPauseL->isVisible())
	{
		m_pPauseL->setVisible(false);
		CCDirector::sharedDirector()->resume();
	}
	
}

void CGamingS::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	
}

void CGamingS::update(float dt)
{
	
}

void CGamingS::clickPause()
{
	CMap* pMapL = deGameManager->getMap();
	if (pMapL->m_bWin || pMapL->m_bGameOver)
	{
		return;
	}
	m_pPauseL->setVisible(true);
	CCDirector::sharedDirector()->pause();
}