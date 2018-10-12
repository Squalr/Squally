#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Resources.h"

using namespace cocos2d;

class Cookie : public NpcBase
{
public:
	static Cookie * deserialize(ValueMap* initProperties);

	static const std::string MapKeyNpcCookie;

private:
	Cookie(ValueMap* initProperties);
	~Cookie();
};
