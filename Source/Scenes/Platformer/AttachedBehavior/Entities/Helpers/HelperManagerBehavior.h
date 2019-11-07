#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;
class PlatformerEntityDeserializer;

class HelperManagerBehavior : public AttachedBehavior
{
public:
	static HelperManagerBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	HelperManagerBehavior(GameObject* owner);
	~HelperManagerBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void spawnHelper(std::string helperName, bool notify);
	std::string getHelperAttachedBehavior(std::string helperName);
	void buildAttachedBehaviorMap();

	PlatformerEntity* entity;
	PlatformerEntity* helperRef;
	PlatformerEntityDeserializer* platformerEntityDeserializer;
	std::map<std::string, std::string> attachedBehaviorMap;
};
