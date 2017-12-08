#include "Player.h"
#include "Resources.h"
#include "cocos2d.h"

using namespace cocos2d;

static int health;

Player::Player()
{
	this->sprite = Sprite::create(Resources::Sprites_Player_Idle);
}


Player::~Player()
{
	delete(this->sprite);
}
