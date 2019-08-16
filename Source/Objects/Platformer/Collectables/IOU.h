#pragma once

#include "Objects/Platformer/Collectables/Collectable.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedString;
class SmartAnimationSequenceNode;

class IOU : public Collectable
{
public:
	static IOU* create(cocos2d::ValueMap& properties);

	static std::string getIdentifier();
	static std::string getIconResource();
	static LocalizedString* getString();

	static const std::string MapKeyIOU;

protected:
	IOU(cocos2d::ValueMap& properties);
	~IOU();

private:
	typedef Collectable super;

	cocos2d::Sprite* iou;
};
