#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;
class PlatformerEntityDeserializer;

class HelperManagerBehavior : public AttachedBehavior
{
public:
	static HelperManagerBehavior* create(GameObject* owner);

	PlatformerEntity* getHelperRef();

	static const std::string MapKey;

protected:
	HelperManagerBehavior(GameObject* owner);
	virtual ~HelperManagerBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	void despawnCurrentHelper();
	void spawnHelperFromState();
	void spawnHelper(std::string helperName, bool notify);
	const std::string& getHelperAttachedBehavior(const std::string& helperName);
	void buildAttachedBehaviorMap();

	PlatformerEntity* entity;
	PlatformerEntity* helperRef;
	PlatformerEntityDeserializer* platformerEntityDeserializer;
	std::map<std::string, std::string> attachedBehaviorMap;
};
