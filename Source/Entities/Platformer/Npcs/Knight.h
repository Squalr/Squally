#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/Npcs/NpcBase.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Resources.h"

using namespace cocos2d;

class Knight : public NpcBase
{
public:
	static Knight * deserialize(ValueMap* initProperties);

	static const std::string KeyNpcKnight;

protected:
	void initializeCardData() override;

private:
	Knight(ValueMap* initProperties);
	~Knight();

	void update(float) override;
};
