#pragma once
#include "cocos2d.h"

#include "Resources.h"

using namespace cocos2d;

class UILayer : public Node
{
public:
	static UILayer* create();

protected:
	UILayer();
	~UILayer();

	void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
};

