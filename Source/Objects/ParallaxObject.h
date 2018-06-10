#pragma once
#include "cocos2d.h"
#include "Level/LevelCamera.h"
#include "SerializableObject.h"

using namespace cocos2d;

class ParallaxObject : public SerializableObject
{
public:
	static ParallaxObject* create(Node* parallaxChild, Vec2 parallaxPosition, Vec2 parallaxSpeed);

private:
	ParallaxObject(Node* parallaxChild, Vec2 parallaxPosition, Vec2 parallaxSpeed);
	~ParallaxObject();

	void update(float) override;

	Vec2 initialPosition;
	Vec2 speed;
	Node* child;
};
