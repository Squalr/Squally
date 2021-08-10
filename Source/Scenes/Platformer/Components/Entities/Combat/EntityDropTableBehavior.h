#pragma once

#include "Engine/Components/GameComponent.h"

class DropPoolDeserializer;
class PlatformerEntity;
class DropPool;

class EntityDropTableBehavior : public GameComponent
{
public:
	static EntityDropTableBehavior* create(GameObject* owner);

	void setDropTable(std::string dropTable);
	DropPool* getDropPool();

	static const std::string MapKey;

protected:
	EntityDropTableBehavior(GameObject* owner);
	virtual ~EntityDropTableBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	PlatformerEntity* entity;
	DropPoolDeserializer* dropPoolDeserializer;
	DropPool* dropPool;
};
