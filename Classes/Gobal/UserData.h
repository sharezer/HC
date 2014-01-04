#pragma once

#include <vector>

#define MMT_COUNT 20


class CUserData
{
public:
	
	typedef struct tagUserDataInfo
	{
		bool music;
		bool sound;
		long gold; 
		long score;
		int lock;
	}UserDataInfo;

	typedef struct tagMissionLockInfo
	{
		int status[MMT_COUNT];//对应每个关卡的是否解锁的数据，1：为解锁，0：为没解锁
	}MissionLockInfo;

private:
	UserDataInfo m_oUserInfo;
	MissionLockInfo m_oMissionLockInfo;

public:
	static CUserData* getInst();
	UserDataInfo& getUserInfo(){return m_oUserInfo;}
	MissionLockInfo& getMissionLockInfo(){return m_oMissionLockInfo;}

	void load();
	void save();
	bool isHaveSaveFile();

	void changeGold(int nGold);

private:
	bool init();

private:
	~CUserData(void);
};

