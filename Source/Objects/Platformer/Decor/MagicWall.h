#pragma once
#include <set>

#include "Engine/Maps/GameObject.h"

class HackableData;
class ParticleObject;

class MagicWall : public GameObject
{
public:
	static MagicWall* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyMagicWall;

protected:
	MagicWall(cocos2d::ValueMap& properties);
	~MagicWall();

	void onEnter() override;

private:
	typedef GameObject super;

	ParticleObject* wallParticles;
	cocos2d::Size wallSize;
};
