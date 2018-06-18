#pragma once
#include "cocos2d.h"

#include "Entities/Entity.h"
#include "Entities/Npcs/NpcBase.h"
#include "Objects/Collision/CategoryGroup.h"
#include "Resources.h"

using namespace cocos2d;

class Knight : public NpcBase
{
public:
	static Knight * create();

	static const std::string KeyNpcKnight;

protected:
	void initializeCardData() override;

private:
	Knight();
	~Knight();

	void update(float) override;
};
