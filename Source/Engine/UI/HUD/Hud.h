#pragma once
#include "cocos2d.h"

#include "Engine/SmartNode.h"

using namespace cocos2d;

class Hud : public SmartNode
{
public:
	static Hud * create();

protected:
	Hud();
	~Hud();

	void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) override;
};
