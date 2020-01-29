#pragma once

#include "Objects/Platformer/Collectables/Collectable.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedString;
class SmartAnimationSequenceNode;

class IOUDrop : public Collectable
{
public:
	static IOUDrop* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyIOUDrop;

protected:
	IOUDrop(cocos2d::ValueMap& properties);
	virtual ~IOUDrop();

private:
	typedef Collectable super;

	cocos2d::Sprite* iou;
};
