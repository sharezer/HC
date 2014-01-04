#include "MenuSence.h"
#include "MenuStartL.h"
#include "MissionSelectL.h"


using namespace cocos2d;

void CMenuSence::pause()
{
	//CCSprite* pSprite;
}

void CMenuSence::resume()
{

}

bool CMenuSence::init()
{
	bool bRet = false;
	do
	{
		this->setTouchEnabled(true);
		for(int i = 0; i < eMCT_Count; ++i)
		{
			m_pMenuChildL[i] = NULL;
		}
		m_nCurChildL = eMCT_Start;

		
		m_pMenuChildL[eStartL] = CMenuStartL::create();
		this->addChild(m_pMenuChildL[eStartL]);


		m_pMenuChildL[eMissionSelectL] = CMissionSelectL::create();
		this->addChild(m_pMenuChildL[eMissionSelectL]);


		for(int i = 0; i < eMCT_Count; ++i)
		{
			if(m_pMenuChildL[i] != NULL)
			{
				if(i == 0)
				{
					m_pMenuChildL[i]->vgEnter(true);
				}
				else
				{
					m_pMenuChildL[i]->setVisible(false);
				}
			}
		}
		bRet = true;
	} while (0);

	return bRet;
}

void CMenuSence::update(float dt)
{

}


void CMenuSence::ccTouchesBegan(CCSet *touches, CCEvent *pEvent)
{
	CCTouch* pTouch = (CCTouch*)touches->anyObject();
	CCPoint touchLocation = pTouch->getLocationInView();
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);

}

void CMenuSence::ccTouchesMoved(CCSet *touches, CCEvent *pEvent)
{
	CCTouch* pTouch = (CCTouch*)touches->anyObject();
	CCPoint touchLocation = pTouch->getLocationInView();
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
	m_pMenuChildL[m_nCurChildL]->mouseMove(touchLocation);

}

void CMenuSence::ccTouchesEnded(CCSet *touches, CCEvent *pEvent)
{
	CCTouch* pTouch = (CCTouch*)touches->anyObject();
	CCPoint touchLocation = pTouch->getLocationInView();
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
	m_pMenuChildL[m_nCurChildL]->mouseUp(touchLocation);
}

void CMenuSence::previousUI()
{
	if(m_nCurChildL == eMCT_Start)
		return;
	int cur = m_nCurChildL;
	int pre = m_nCurChildL - 1;

	m_pMenuChildL[cur]->setVisible(false);
	m_pMenuChildL[pre]->setVisible(true);

	//m_pMenuChildL[cur]->vgExit(false);
	//m_pMenuChildL[pre]->vgEnter(false);
	--m_nCurChildL;
}

void CMenuSence::nextUI()
{
	if(m_nCurChildL == eMCT_End)
		return;
	int cur = m_nCurChildL;
	int next = m_nCurChildL + 1;
	m_pMenuChildL[cur]->setVisible(false);
	m_pMenuChildL[next]->setVisible(true);

	//m_pMenuChildL[cur]->vgExit(true);
	//m_pMenuChildL[next]->vgEnter(true);
	++m_nCurChildL;
}
