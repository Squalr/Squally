#include "Ajax.h"

const std::string Ajax::MapKeyNpcAjax = "ajax";

Ajax* Ajax::deserialize(ValueMap* initProperties)
{
	Ajax* instance = new Ajax(initProperties);

	instance->autorelease();

	return instance;
}

Ajax::Ajax(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Ruins_Npcs_Ajax_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Ajax::~Ajax()
{
}
