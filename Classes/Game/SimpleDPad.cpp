#include "SimpleDPad.h"
using namespace cocos2d;

// #define deSCREEN CCDirector::sharedDirector()->getWinSize()
// #define deCENTER ccp(deSCREEN.width / 2, deSCREEN.height / 2)

SimpleDPad::SimpleDPad(void)
{
	_delegate = NULL;
}

SimpleDPad::~SimpleDPad(void)
{
}

SimpleDPad* SimpleDPad::dPadWithFile(CCString *fileName, float radius)
{
	SimpleDPad *pRet = new SimpleDPad();
	if (pRet && pRet->initWithFile(fileName, radius))
	{
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool SimpleDPad::initWithFile(CCString *filename, float radius)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCSprite::initWithFile(filename->getCString()));
		
		_radius = radius;
		_direction = CCPointZero;
		_isHeld = false;
		this->scheduleUpdate();

		bRet = true;
	} while (0);

	return bRet;
}

void SimpleDPad::onEnterTransitionDidFinish()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
}

void SimpleDPad::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void SimpleDPad::update(float dt)
{
	if (_isHeld)
	{
		_delegate->isHoldingDirection(this, _direction);
	}
}

bool SimpleDPad::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint location = pTouch->getLocation();
#ifdef deSimpleDPad2
	_beginPos = pTouch->getLocation();
	//this->updateDirectionForTouchLocation(location);
	_isHeld = true;
	return true;
#else
	float distanceSQ = ccpDistanceSQ(location, this->getPosition());
	if (distanceSQ <= _radius * _radius)
	{
		this->updateDirectionForTouchLocation(location);
		_isHeld = true;
		return true;
	}
#endif
	return false;
}

void SimpleDPad::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint location = pTouch->getLocation();
	this->updateDirectionForTouchLocation(location);
}

void SimpleDPad::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	_direction = CCPointZero;
	_isHeld = false;
	_delegate->simpleDPadTouchEnded(this);
}

void SimpleDPad::updateDirectionForTouchLocation(CCPoint location)
{
#ifdef deSimpleDPad2
	float radians = ccpToAngle(ccpSub(location, _beginPos));
#else
	float radians = ccpToAngle(ccpSub(location, this->getPosition()));
#endif
	float degrees = -1 * CC_RADIANS_TO_DEGREES(radians);

	if (degrees <= 45 && degrees >= -45) 
	{
		//right
		_direction = ccp(1.0, 0.0);
	}
	else if (degrees >= 45 && degrees <= 135)
	{
		//bottom
		_direction = ccp(0.0, -1.0);
	}
	else if (degrees >= 135 || degrees <= -135)
	{
		//left
		_direction = ccp(-1.0, 0.0);
	}
	else if (degrees <= -45 && degrees >= -135)
	{
		//top
		_direction = ccp(0.0, 1.0);
	}
	_delegate->didChangeDirectionTo(this, _direction);
}
