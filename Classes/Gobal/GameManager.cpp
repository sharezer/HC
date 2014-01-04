#include "GameManager.h"
#include "GamingS.h"
#include "MenuSence.h"
#include "MissionSelectL.h"
#include "UserData.h"

using namespace cocos2d;

CGameManager::~CGameManager(void)
{

}

bool CGameManager::init()
{
	return true;
}

CGameManager* CGameManager::getInst()
{
	static CGameManager* s_pInst = NULL;
	if(s_pInst == NULL)
	{
		s_pInst = new CGameManager();
		s_pInst->init();
	}
	return s_pInst;
}


void CGameManager::appRun()
{
	CCScene* pScene = CCScene::create();
	//CGamingS* pSubSence = CGamingS::create();
	CMenuSence* pSubSence = CMenuSence::create();
	pScene->addChild(pSubSence);
	m_pCurGameS = pSubSence;

	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->runWithScene(pScene);
}

void CGameManager::changeState(eGameState type)
{
	if(CCDirector::sharedDirector()->isPaused())
	{
		CCDirector::sharedDirector()->resume();
	}
	CCScene* pScene = CCScene::create();
	CGameSence* pSubSence;
	switch (type)
	{
	case CGameManager::eGameStateLogo:
		break;

	case CGameManager::eGameStateMenu:
		pSubSence = CMenuSence::create();
		break;

	case CGameManager::eGameStateGaming:
		{
			m_pGamingS = CGamingS::create();
			pSubSence = m_pGamingS;
		}	
		break;

	case CGameManager::eGameStateCourse:
		break;

	case CGameManager::eGameStateLoading:
		break;
	default:
		break;
	}
	pScene->addChild(pSubSence);
	m_pCurGameS = pSubSence;

	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->replaceScene(CCTransitionFade::create(0.5f, pScene));
}
