#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class LocalizedString;
class SmartAnimationSequenceNode;

class IOU : public GameObject
{
public:
	static IOU* create(cocos2d::ValueMap& initProperties);

	static std::string getIdentifier();
	static std::string getIconResource();
	static LocalizedString* getString();

	static const std::string MapKeyIOU;
	static const std::string SaveKeyIsCollected;

protected:
	IOU(cocos2d::ValueMap& initProperties);
	virtual ~IOU();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;
	void onObjectStateLoaded() override;

private:
	typedef GameObject super;

	void disableCollection();
	cocos2d::Sprite* iou;
	CollisionObject* iouCollision;

	bool isCollected;
};
