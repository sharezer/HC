#include "MissionSelectL.h"
#include "GameManager.h"
#include "UserData.h"
#include "MenuItemImageSub.h"

USING_NS_CC;


bool CMissionSelectL::init()
{
	bool bRet = false;
	do
	{
		m_pStageL = NULL;

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

#define Create_Sprite(varName, fileName, pos, ez)\
		CCSprite* varName = CCSprite::create(fileName);\
		varName->setPosition(pos);\
		this->addChild(varName, ez);

#ifdef dg_For_Use_Test_UI

		//CUserData::MissionLockInfo& lockInfo = CUserData::getInst()->getMissionLockInfo();

		CUserData::UserDataInfo& info = CUserData::getInst()->getUserInfo();

		CCSprite* pBG = CCSprite::create("interface_mission_bg.png");
		pBG->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		this->addChild(pBG);

		CMenuItemImageSub* pBackBtn = Create_MenuItemImageSub("interface_01_012.png", "interface_01_012.png", 1, ccp(900, 80), this, CMissionSelectL::back);
		CCMenu* pMenu = CCMenu::create(pBackBtn, NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu, 1);

		CCSpriteBatchNode* batchNodeBG = CCSpriteBatchNode::create("button.png");  
		this->addChild(batchNodeBG);
		CCSpriteBatchNode* batchNodeLock = CCSpriteBatchNode::create("interface_01_011.png"); 
		this->addChild(batchNodeLock);

		float fPx = 0;
		float fPy = 650.0f;
		char s[16];
		for (int i = 0; i < 4; i++)
		{	
			fPx = 212.0f;
			CMenuItemImageSub* item[5];
			for (int j = 0; j < 5; j++)
			{
				int nMission = 5 * i + j;
				item[j] = Create_MenuItemImageSub("button.png", "button.png", nMission, ccp(fPx, fPy), this, CMissionSelectL::menuCallBack);
				item[j]->setOpacityModifyRGB(true);
				if (nMission <= info.lock)
				{
					sprintf(s, "%d", nMission + 1);
					CCLabelAtlas* pLabel = CCLabelAtlas::create(s, "mission_select_fnt.png", 40, 50,'0'); 
					pLabel->setAnchorPoint(ccp(0.5, 0.5));
					pLabel->setPosition(ccp(fPx, fPy));
					this->addChild(pLabel, 2);

				}
				else
				{
					
					CCSprite* pSprite = CCSprite::createWithTexture(batchNodeLock->getTexture());
					pSprite->setPosition(ccp(fPx, fPy));
					this->addChild(pSprite, 2);
				}

				fPx += 150;

			}

			CCMenu *menu = CCMenu::create(item[0], item[1], item[2], item[3], item[4], NULL);    
			menu->setPosition( CCPointMake(0,0) );
			this->addChild(menu, 1);

			fPy -= 150;
		}		
		
#endif
		bRet = true;
	} while (0);
	return bRet;
}

void CMissionSelectL::update(float dt)
{

}

void CMissionSelectL::vgEnter(bool bRight)
{
	this->setVisible(true);
	this->setPosition(ccp(-320, 0));
	CCMoveTo* pMoveTo = CCMoveTo::create(0.5f, ccp(0, 0));
	this->runAction(pMoveTo);
}

void CMissionSelectL::vgExit(bool bRight)
{
	this->setPosition(ccp(0, 0));
	CCMoveTo* pMoveTo = CCMoveTo::create(0.3f, ccp(320, 0));
	this->runAction(pMoveTo);
}

void CMissionSelectL::mouseDown(cocos2d::CCPoint& pos)
{
	if(m_pStageL)
	{
		this->closeStageL();
	}
}

void CMissionSelectL::mouseMove(cocos2d::CCPoint& pos)
{

}

void CMissionSelectL::mouseUp(cocos2d::CCPoint& pos)
{

}

void CMissionSelectL::menuCallBack(CCObject * pSender)
{
	CUserData::UserDataInfo& info = CUserData::getInst()->getUserInfo();
	CCNode* pMenu = (CCNode*)pSender;
	int idx = pMenu->getTag();
	if (idx <= info.lock)
	{
		this->stageSelect(idx);
	}
}


void CMissionSelectL::stageSelect(int idx)
{
	CGameManager::GameStartInfo& info = deGameManager->getGameStartInfo();
	info.missionType = idx;
	deGameManager->changeState(CGameManager::eGameStateGaming);
}

void CMissionSelectL::closeStageL()
{
	if(m_pStageL)
	{
		m_pStageL->removeFromParentAndCleanup(true);
		m_pStageL = NULL;
	}
}

void CMissionSelectL::back(CCObject* pSender)
{
	CMenuSence* pMenuSence = (CMenuSence*)this->getParent();
	pMenuSence->previousUI();
}
