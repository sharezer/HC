#pragma once
#include "cocos2d.h"

USING_NS_CC;
#define Create_MenuItemImageSub(fileName1, fileName2, tag, pos, target,cb)\
	CMenuItemImageSub::create(fileName1, fileName2, tag, pos, target, menu_selector(cb))

class CMenuItemImageSub : public CCMenuItemImage
{
public:
	CMenuItemImageSub(){}
	virtual ~CMenuItemImageSub(){}

    CC_DEPRECATED_ATTRIBUTE static CMenuItemImageSub* itemWithNormalImage(const char *normalImage, const char *selectedImage);
    /** creates a menu item with a normal,selected  and disabled image
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CMenuItemImageSub* itemWithNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage);
    /** creates a menu item with a normal and selected image with target/selector 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CMenuItemImageSub* itemWithNormalImage(const char *normalImage, const char *selectedImage, CCObject* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal,selected  and disabled image with target/selector 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CMenuItemImageSub* itemWithNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, CCObject* target, SEL_MenuHandler selector);
    
    /** creates a menu item with a normal and selected image*/
    static CMenuItemImageSub* create(const char *normalImage, const char *selectedImage);
    /** creates a menu item with a normal,selected  and disabled image*/
    static CMenuItemImageSub* create(const char *normalImage, const char *selectedImage, const char *disabledImage);
    /** creates a menu item with a normal and selected image with target/selector */
    static CMenuItemImageSub* create(const char *normalImage, const char *selectedImage, CCObject* target, SEL_MenuHandler selector);
    /** creates a menu item with a normal,selected  and disabled image with target/selector */
    static CMenuItemImageSub* create(const char *normalImage, const char *selectedImage, const char *disabledImage, CCObject* target, SEL_MenuHandler selector);

	bool init();
    /** initializes a menu item with a normal, selected  and disabled image with target/selector */
    bool initWithNormalImage(const char *normalImage, const char *selectedImage, const char *disabledImage, CCObject* target, SEL_MenuHandler selector);
    /** sets the sprite frame for the normal image */
    void setNormalSpriteFrame(CCSpriteFrame* frame);
    /** sets the sprite frame for the selected image */
    void setSelectedSpriteFrame(CCSpriteFrame* frame);
    /** sets the sprite frame for the disabled image */
    void setDisabledSpriteFrame(CCSpriteFrame* frame);
    /** Creates an CCMenuItemImage.
    @deprecated: This interface will be deprecated sooner or later.
     */
    CC_DEPRECATED_ATTRIBUTE static CMenuItemImageSub* node();

    /** Creates an CCMenuItemImage.
     */
    static CMenuItemImageSub* create();
	/**************************selectedSprite居中放大*************************/
	bool initWithNormalSprite(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite, CCObject* target, SEL_MenuHandler selector);
	/**************************selectedSprite放大比例*************************/
	void setSelectedScale(float fScale);
	void setNormalScale(float fScale);
	/****************************快捷创建***************************/
	static CMenuItemImageSub* create(const char *normalImage, int tag, const CCPoint& pos, CCObject* target, SEL_MenuHandler selector);
	static CMenuItemImageSub* create(const char *normalImage, const char *selectedImage, int tag, const CCPoint& pos, CCObject* target, SEL_MenuHandler selector);
	static CMenuItemImageSub* create(const char *normalImage, const char *selectedImage, const char *disabledImage,int tag, const CCPoint& pos, CCObject* target, SEL_MenuHandler selector);
};