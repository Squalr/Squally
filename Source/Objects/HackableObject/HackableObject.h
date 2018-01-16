#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class HackableObject : public Node
{
public:
	static HackableObject * create(Node* parentNode, Vec2 offset);

private:
	HackableObject(Node* parentNode, Vec2 offset);
	~HackableObject();

	void update(float) override;

	Node* parent;
	Vec2 buttonOffset;
};

