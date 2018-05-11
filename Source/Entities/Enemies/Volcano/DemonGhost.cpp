#include "DemonGhost.h"

DemonGhost* DemonGhost::create()
{
	DemonGhost* instance = new DemonGhost();

	instance->autorelease();

	return instance;
}

DemonGhost::DemonGhost() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_DemonGhost_Animations,
	false)
{
}

DemonGhost::~DemonGhost()
{
}
