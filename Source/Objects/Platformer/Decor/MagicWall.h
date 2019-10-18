#pragma once
#include <set>

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class ParticleSystem;
}

class CollisionObject;
class HackableData;

class MagicWall : public HackableObject
{
public:
	static MagicWall* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyMagicWall;

protected:
	MagicWall(cocos2d::ValueMap& properties);
	~MagicWall();
	void onEnter() override;

private:
	typedef HackableObject super;

	cocos2d::ParticleSystem* wallParticles;
	cocos2d::Size wallSize;
};
