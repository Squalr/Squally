#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;
class PlatformerEntityDeserializer;

class HelperManagerBehavior : public Component
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
	typedef Component super;

	void despawnCurrentHelper();
	void spawnHelperFromState();
	void spawnHelper(std::string helperName, bool notify);
	const std::string& getHelperComponent(const std::string& helperName);
	void buildComponentMap();

	PlatformerEntity* entity;
	PlatformerEntity* helperRef;
	PlatformerEntityDeserializer* platformerEntityDeserializer;
	std::map<std::string, std::string> componentMap;
};
