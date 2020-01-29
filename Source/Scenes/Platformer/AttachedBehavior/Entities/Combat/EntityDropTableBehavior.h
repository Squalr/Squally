#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class DropPoolDeserializer;
class PlatformerEntity;
class DropPool;

class EntityDropTableBehavior : public AttachedBehavior
{
public:
	static EntityDropTableBehavior* create(GameObject* owner);

	void setDropTable(std::string dropTable);
	DropPool* getDropPool();

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityDropTableBehavior(GameObject* owner);
	~EntityDropTableBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	DropPoolDeserializer* dropPoolDeserializer;
	DropPool* dropPool;
};
