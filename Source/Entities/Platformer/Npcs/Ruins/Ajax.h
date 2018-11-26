#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Ajax : public NpcBase
{
public:
	static Ajax* deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcAjax;

private:
	Ajax(ValueMap* initProperties);
	~Ajax();
};
