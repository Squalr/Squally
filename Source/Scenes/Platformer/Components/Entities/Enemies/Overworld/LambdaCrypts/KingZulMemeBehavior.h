#pragma once

#include "Engine/Components/GameComponent.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class WorldSound;

class KingZulMemeBehavior : public GameComponent
{
public:
	static KingZulMemeBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	KingZulMemeBehavior(GameObject* owner);
	virtual ~KingZulMemeBehavior();

	void onLoad() override;

private:
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
};
