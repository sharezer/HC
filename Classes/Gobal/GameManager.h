#pragma once
#include "cocos2d.h"

class CGamingS;
class CMap;

class CGameSence: public cocos2d::CCLayer
{
public:
	virtual void pause() = 0;
	virtual void resume() = 0;
};

class CGameManager
{
private:
	~CGameManager(void);

public:
	enum eGameState
	{
		eGameStateLogo,
		eGameStateMenu,
		eGameStateGaming,
		eGameStateCourse,
		eGameStateLoading,
	};

	//��Ϸ��������
	typedef struct tagGameStartInfo
	{
		//eBackGroundType bgType;				//����ͼ
		int missionType;                        //�ڼ���
	}GameStartInfo;

private:
	bool init();

public:
	static CGameManager* getInst();
	void appRun();
	void changeState(eGameState type);

public:
	GameStartInfo& getGameStartInfo(){return m_oGameStartInfo;}
	CGameSence* getGameSence(){return m_pCurGameS;}
	CGamingS* getGamingS(){return m_pGamingS;}
	CMap* getMap(){return m_pMap;}
	void setMap(CMap* pMap){m_pMap = pMap;}

private:
	CGameSence* m_pCurGameS;
	GameStartInfo m_oGameStartInfo;
	CGamingS* m_pGamingS;
	CMap* m_pMap;
	//user data

};

#define deGameManager CGameManager::getInst()

