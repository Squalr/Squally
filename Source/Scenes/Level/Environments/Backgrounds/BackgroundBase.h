#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableLayer.h"
#include "Resources.h"

using namespace cocos2d;

class BackgroundBase : public SerializableLayer
{
protected:
	BackgroundBase(std::string name, ValueMap properties);
	~BackgroundBase();

	void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
};

