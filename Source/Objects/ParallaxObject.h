#pragma once
#include "cocos2d.h"

#include "Objects/Hackables/HackableObject.h"
#include "Scenes/Level/LevelCamera.h"

using namespace cocos2d;

class ParallaxObject : public HackableObject
{
public:
	static ParallaxObject* create(ValueMap* initProperties, Node* parallaxChild, Vec2 parallaxSpeed);

private:
	ParallaxObject(ValueMap* initProperties, Node* parallaxChild, Vec2 parallaxSpeed);
	~ParallaxObject();

	void update(float) override;

	Vec2 speed;
	Node* child;
};
