#include "MenuItemImageSub.h"

bool CMenuItemImageSub::initWithNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector)
{
	CCMenuItem::initWithTarget(target, selector);
	setNormalImage(normalSprite);
	setSelectedImage(selectedSprite);
	setDisabledImage(disabledSprite);

	//设置按钮从中心点放大
	if (selectedSprite && normalSprite) 
	{
		selectedSprite->setPosition(
			(normalSprite->getContentSize().width-selectedSprite->getContentSize().width)/2.0f,
			(normalSprite->getContentSize().height-selectedSprite->getContentSize().height)/2.0f);
	}
	//end

	if(m_pNormalImage)
	{
		this->setContentSize(m_pNormalImage->getContentSize());

	}
	return true;
}

CMenuItemImageSub* CMenuItemImageSub::node()
{
	return CMenuItemImageSub::create();
}

CMenuItemImageSub* CMenuItemImageSub::create()
{
	CMenuItemImageSub *pRet = new CMenuItemImageSub();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CMenuItemImageSub::init(void)
{
	return initWithNormalImage(NULL, NULL, NULL, NULL, NULL);
}
CMenuItemImageSub * CMenuItemImageSub::itemWithNormalImage(const char *normalImage, const char *selectedImage)
{
	return CMenuItemImageSub::create(normalImage, selectedImage);
}

CMenuItemImageSub * CMenuItemImageSub::create(const char *normalImage, const char *selectedImage)
{
	return CMenuItemImageSub::create(normalImage, selectedImage, NULL, NULL, NULL);
}

CMenuItemImageSub * CMenuItemImageSub::itemWithNormalImage(const char *normalImage, const char *selectedImage, CCObject* target, SEL_MenuHandler selector)
{
	return CMenuItemImageSub::create(normalImage, selectedImage, target, selector);
}

CMenuItemImageSub * CMenuItemImageSub::create(const char *normalImage, const char *selectedImage, CCObject* target, SEL_MenuHandler selector)
{
	return CMenuItemImageSub::create(normalImage, selectedImage, NULL, target, selector);
}

CMenuItemImageSub * CMenuItemImageSub::itemWithNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, CCObject* target, SEL_MenuHandler selector)
{
	return CMenuItemImageSub::create(normalImage, selectedImage, disabledImage, target, selector);
}

CMenuItemImageSub * CMenuItemImageSub::create(const char *normalImage, const char *selectedImage, const char *disabledImage, CCObject* target, SEL_MenuHandler selector)
{
	CMenuItemImageSub *pRet = new CMenuItemImageSub();
	if (pRet && pRet->initWithNormalImage(normalImage, selectedImage, disabledImage, target, selector))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

CMenuItemImageSub * CMenuItemImageSub::create(const char *normalImage, int tag, const CCPoint& pos, CCObject* target, SEL_MenuHandler selector)
{
	return CMenuItemImageSub::create(normalImage, NULL, NULL, tag, pos, target, selector);
}

CMenuItemImageSub * CMenuItemImageSub::create(const char *normalImage, const char *selectedImage, int tag, const CCPoint& pos, CCObject* target, SEL_MenuHandler selector)
{
	return CMenuItemImageSub::create(normalImage, selectedImage, NULL, tag, pos, target, selector);
}

CMenuItemImageSub * CMenuItemImageSub::create(const char *normalImage, const char *selectedImage, const char  *disabledImage,int tag, const CCPoint& pos, CCObject* target, SEL_MenuHandler selector)
{
	CMenuItemImageSub *pRet = new CMenuItemImageSub();

	if (pRet && pRet->initWithNormalImage(normalImage, selectedImage, disabledImage, target, selector))
	{
		pRet->autorelease();
		pRet->setTag(tag);
		pRet->setPosition(pos);
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

CMenuItemImageSub * CMenuItemImageSub::itemWithNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage)
{
	return CMenuItemImageSub::create(normalImage, selectedImage, disabledImage);
}

CMenuItemImageSub * CMenuItemImageSub::create(const char *normalImage, const char *selectedImage, const char *disabledImage)
{
	CMenuItemImageSub *pRet = new CMenuItemImageSub();
	if (pRet && pRet->initWithNormalImage(normalImage, selectedImage, disabledImage, NULL, NULL))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool CMenuItemImageSub::initWithNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, CCObject* target, SEL_MenuHandler selector)
{
	CCNode *normalSprite = NULL;
	CCNode *selectedSprite = NULL;
	CCNode *disabledSprite = NULL;

	if (normalImage)
	{
		normalSprite = CCSprite::create(normalImage);
	}

	if (selectedImage)
	{
		selectedSprite = CCSprite::create(selectedImage);
	}
	else
	{
		selectedSprite = CCSprite::create(normalImage);
		selectedSprite->setScale(1.2f);
	}

	if(disabledImage)
	{
		disabledSprite = CCSprite::create(disabledImage);
	}
	return initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, target, selector);
}
//
// Setter of sprite frames
//
void CMenuItemImageSub::setNormalSpriteFrame(CCSpriteFrame * frame)
{
	setNormalImage(CCSprite::createWithSpriteFrame(frame));
}

void CMenuItemImageSub::setSelectedSpriteFrame(CCSpriteFrame * frame)
{
	setSelectedImage(CCSprite::createWithSpriteFrame(frame));
}

void CMenuItemImageSub::setDisabledSpriteFrame(CCSpriteFrame * frame)
{
	setDisabledImage(CCSprite::createWithSpriteFrame(frame));
}
// end

void CMenuItemImageSub::setSelectedScale(float fScale)
{
	m_pSelectedImage->setScale(fScale);
}

void CMenuItemImageSub::setNormalScale(float fScale)
{
	m_pNormalImage->setScale(fScale);
}