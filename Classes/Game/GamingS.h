#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"
#include "GameManager.h"
#include "Map.h"

class CGamingS : public CGameSence
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(); 
	virtual void pause();
	virtual void resume();	

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	void menuCallBack(CCObject* pSender);

	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	void update(float dt);

	void gameOver();
	void win();
	void changeTime(float fTime);
	void changeScore(int nScore);

	void clickPause();

/*	void runChangeScore(int nScore);*/

    // implement the "static node()" method manually
    CREATE_FUNC(CGamingS);

	cocos2d::CCLayer* m_pGameL;
	cocos2d::CCLayer* m_pPauseL;
	cocos2d::CCLayer* m_pVictoryL;

	cocos2d::CCSpriteBatchNode *_actors;

private:
	cocos2d::CCMenu* m_pSkipMenu;
	cocos2d::CCSprite* m_pSkipSprite;
	cocos2d::CCSprite* m_pVicturySprite;
	cocos2d::CCMenuItem* m_pVicturyMenuItem[3];


	cocos2d::CCLabelTTF* m_pGoldLabel;
	cocos2d::CCLabelTTF* m_pScoreLabel;

	int m_nScore;

};

#endif  // __HELLOWORLD_SCENE_H__
