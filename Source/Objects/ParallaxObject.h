#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableObject.h"
#include "Scenes/Level/LevelCamera.h"

using namespace cocos2d;

class ParallaxObject : public SerializableObject
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
