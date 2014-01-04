#include "UserData.h"
#include "cocos2d.h"
USING_NS_CC;

#define SaveStringToXML(name, value)					CCUserDefault::sharedUserDefault()->setStringForKey(name, value)
#define SaveIntegerToXML(name, value)					CCUserDefault::sharedUserDefault()->setIntegerForKey(name, value)
#define SaveBooleanToXML(name, value)					CCUserDefault::sharedUserDefault()->setBoolForKey(name, value) 
#define LoadStringFromXML(name, default)				CCUserDefault::sharedUserDefault()->getStringForKey(name, default) 
#define LoadIntegerFromXML(name, default)				CCUserDefault::sharedUserDefault()->getIntegerForKey(name, default)
#define LoadBooleanFromXML(name, default)				CCUserDefault::sharedUserDefault()->getBoolForKey(name, default)

#define deIsHaveXML			 "isHaveSaveFileXml"
#define deScoreXML			 "socreXml"
#define deGoldXML			 "goldXml"
#define deMusicXML			 "musicXml"
#define deSoundXML			 "soundXml"
#define deLockXML			 "lockXml"

CUserData* CUserData::getInst()
{
	static CUserData* pRet = NULL;
	if (pRet == NULL)
	{
		pRet = new CUserData();
		pRet->init();
	}
	return pRet;
}

bool CUserData::init()
{
	if (!this->isHaveSaveFile())
	{
		SaveIntegerToXML(deGoldXML, 0);
		SaveIntegerToXML(deScoreXML, 0);
		SaveBooleanToXML(deMusicXML, true);
		SaveBooleanToXML(deSoundXML, true);
		SaveIntegerToXML(deLockXML, 0);
	}
	this->load();
	
	return true;
}

CUserData::~CUserData(void)
{

}

void CUserData::load()
{
	m_oUserInfo.gold = LoadIntegerFromXML(deGoldXML, 0);
	m_oUserInfo.score = LoadIntegerFromXML(deScoreXML, 0);
	m_oUserInfo.music = LoadBooleanFromXML(deMusicXML, false);
	m_oUserInfo.sound = LoadBooleanFromXML(deSoundXML, false);
	m_oUserInfo.lock =  LoadIntegerFromXML(deLockXML, 0);
	CCUserDefault::sharedUserDefault()->flush();
}

void CUserData::save()
{
	SaveIntegerToXML(deGoldXML, m_oUserInfo.gold);
	SaveIntegerToXML(deScoreXML, m_oUserInfo.score);
	SaveBooleanToXML(deMusicXML, m_oUserInfo.music);
	SaveBooleanToXML(deSoundXML, m_oUserInfo.sound);
	SaveIntegerToXML(deLockXML, m_oUserInfo.lock);
    CCUserDefault::sharedUserDefault()->flush();
}

bool CUserData::isHaveSaveFile()
{ 
	if( !LoadBooleanFromXML(deIsHaveXML, false)) 
	{ 
		SaveBooleanToXML(deIsHaveXML, true); 
		CCUserDefault::sharedUserDefault()->flush();//提交 
		//        CCLog("存储文件不存在,头次开始加载游戏"); 
		return false; 
	}
	else
	{ 
		//        CCLog("存储文件已存在"); 
		return true; 
	} 
} 

void CUserData::changeGold(int nGold)
{
	m_oUserInfo.gold += nGold;
}