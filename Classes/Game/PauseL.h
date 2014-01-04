#pragma once
#include "cocos2d.h"

class CPauseL: public cocos2d::CCLayer
{
public:
	CREATE_FUNC(CPauseL);
	virtual bool init(); 
public:
	void menuCallBack(cocos2d::CCObject * pSender);
	void clickResume();
	void clickSound();
	void clickMusic();
	void clickRestart();
	void clickMenu();
	void clickChangeHam();
private:

};
