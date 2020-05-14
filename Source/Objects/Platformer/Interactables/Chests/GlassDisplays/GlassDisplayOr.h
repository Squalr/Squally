#pragma once

#include "Objects/Platformer/Interactables/Chests/GlassDisplays/GlassDisplayBase.h"

using namespace cocos2d;

class MinMaxPool;

class GlassDisplayOr : public GlassDisplayBase
{
public:
	static GlassDisplayOr* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	GlassDisplayOr(cocos2d::ValueMap& properties);
	virtual ~GlassDisplayOr();

	bool tryOpen() override;

private:
	typedef GlassDisplayBase super;
};
