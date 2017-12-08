#include "Level.h"
#include "Resources.h"
#include "../Entities/Player.h"

// Scene* scene;

Level::Level()
{
	this->backGround = Sprite::create(Resources::Background_GrassBG);
	this->player = new Player();

	this->addChild(this->backGround);
	this->addChild(this->player->sprite);
}


Level::~Level()
{
	delete(this->backGround);
	delete(this->player);
}
