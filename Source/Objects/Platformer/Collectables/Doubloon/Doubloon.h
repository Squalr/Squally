#pragma once

#include "Engine/Maps/SerializableObject.h"

class CollisionObject;
class SmartAnimationSequenceNode;

class Doubloon : public SerializableObject
{
public:
	static Doubloon* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyDoubloon;

protected:
	Doubloon(cocos2d::ValueMap& initProperties);
	virtual ~Doubloon();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;

private:
	typedef SerializableObject super;

	SmartAnimationSequenceNode* doubloon;
	CollisionObject* doubloonCollision;
};
