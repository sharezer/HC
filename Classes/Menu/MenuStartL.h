#pragma once
#include "cocos2d.h"
#include "MenuSence.h"



class CMenuStartL: public CMenuChildLayer
{
public:
	CREATE_FUNC(CMenuStartL);

public:
	virtual bool init(); 
	void update(float dt);

	virtual void mouseDown(cocos2d::CCPoint& pos);
	virtual void mouseMove(cocos2d::CCPoint& pos);
	virtual void mouseUp(cocos2d::CCPoint& pos);

	virtual void vgEnter(bool bRight);
	virtual void vgExit(bool bRight);

	void menuCallBack(CCObject * pSender);

private:
	void start();
	void sound();
	void store();
	void share();
	void aboutUs();


};


