#include "SpriterAnimationBone.h"

using namespace cocos2d;

SpriterAnimationBone* SpriterAnimationBone::create(CSize boneSize)
{
	SpriterAnimationBone* instance = new SpriterAnimationBone(boneSize);

	instance->autorelease();

	return instance;
}

SpriterAnimationBone::SpriterAnimationBone(CSize boneSize)
{
	this->boneSize = boneSize;
}

SpriterAnimationBone::~SpriterAnimationBone()
{
}

void SpriterAnimationBone::setDebugDrawHeirarchyDepth(int heirarchyDepth)
{
	// No-op: bone debug draw removed
}


