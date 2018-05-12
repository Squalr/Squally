#include "DemonGhost.h"

DemonGhost* DemonGhost::create()
{
	DemonGhost* instance = new DemonGhost();

	instance->autorelease();

	return instance;
}

DemonGhost::DemonGhost() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_DemonGhost_Animations,
	false,
	Size(256.0f, 320.0f),
	0.7f,
	Vec2(0.0f, 40.0f))
{
}

DemonGhost::~DemonGhost()
{
}
