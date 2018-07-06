#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableLayer.h"
#include "Resources.h"

using namespace cocos2d;

class BackgroundBase : public SerializableLayer
{
protected:
	BackgroundBase(ValueMap* properties, std::string name);
	~BackgroundBase();

	void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) override;
};

