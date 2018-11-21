#pragma once
#include "cocos2d.h"

#include "Engine/SmartNode.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/UI/Mouse.h"
#include "Resources.h"

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
