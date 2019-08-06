#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEnemy;
class Squally;

class SquallyEquipmentVisualBehaviors : public AttachedBehavior
{
public:
	static SquallyEquipmentVisualBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyEquipmentVisualBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyEquipmentVisualBehaviors();

	void onLoad() override;

private:
	typedef AttachedBehavior super;
	
	void updateEquipmentVisual();

	Squally* squally;
};
