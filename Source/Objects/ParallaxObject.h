#pragma once
#include "cocos2d.h"

#include "Scenes/Level/LevelCamera.h"

using namespace cocos2d;

class ParallaxObject : public Node
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
