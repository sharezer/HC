#pragma once
#include "cocos2d.h"
#include "MenuSence.h"

class CMissionSelectL: public CMenuChildLayer
{
public:
	CREATE_FUNC(CMissionSelectL);

public:
	virtual bool init(); 
	
	void update(float dt);

	virtual void mouseDown(cocos2d::CCPoint& pos);
	virtual void mouseMove(cocos2d::CCPoint& pos);
	virtual void mouseUp(cocos2d::CCPoint& pos);

	virtual void vgEnter(bool bRight);
	virtual void vgExit(bool bRight);

	void createStageSelectMenu(int idx);
	void createMissionInstruct(int idx, const cocos2d::CCPoint& pos, float rotation);
	
	void menuCallBack(CCObject* pSender);
	void mainMissionSelect(int idx);
	void stageSelect(int idx);
	void closeStageL();
	void back(CCObject* pSender);

protected:
	cocos2d::CCLayer* m_pStageL;
};


