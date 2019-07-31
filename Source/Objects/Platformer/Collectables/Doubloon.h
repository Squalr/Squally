#pragma once

#include "Engine/Maps/GameObject.h"

class CollisionObject;
class LocalizedString;
class SmartAnimationSequenceNode;

class Doubloon : public GameObject
{
public:
	static Doubloon* create(cocos2d::ValueMap& initProperties);

	static std::string getIdentifier();
	static std::string getIconResource();
	static LocalizedString* getString();

	static const std::string MapKeyDoubloon;
	static const std::string SaveKeyIsCollected;

protected:
	Doubloon(cocos2d::ValueMap& initProperties);
	virtual ~Doubloon();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;
	void onObjectStateLoaded() override;

private:
	typedef GameObject super;

	void disableCollection();
	SmartAnimationSequenceNode* doubloon;
	CollisionObject* doubloonCollision;

	bool isCollected;
};
