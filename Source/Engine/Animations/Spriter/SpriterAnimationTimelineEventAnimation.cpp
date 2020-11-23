#include "SpriterAnimationTimelineEventAnimation.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/Spriter/SpriterAnimationTimelineEventMainline.h"

using namespace cocos2d;

SpriterAnimationTimelineEventAnimation* SpriterAnimationTimelineEventAnimation::create(SpriterAnimationNode* animations, const SpriterAnimation& animationData)
{
	SpriterAnimationTimelineEventAnimation* instance = new SpriterAnimationTimelineEventAnimation(animations, animationData);

	instance->autorelease();

	return instance;
}

SpriterAnimationTimelineEventAnimation::SpriterAnimationTimelineEventAnimation(SpriterAnimationNode* animations, const SpriterAnimation& animationData) : super(animations, 0.0f, animationData.length)
{
	this->animationData = animationData;
	this->mainlineEvents = std::vector<SpriterAnimationTimelineEventMainline*>();
	this->elapsedTime = 0.0f;

	for (int index = 0; index < int(animationData.mainline.keys.size()); index++)
	{
		float endTime = index == int(animationData.mainline.keys.size()) - 1 ? animationData.length : animationData.mainline.keys[index].time;
		SpriterAnimationTimelineEventMainline* mainlineEvent = SpriterAnimationTimelineEventMainline::create(animations, animationData.mainline.keys[index], endTime);

		this->mainlineEvents.push_back(mainlineEvent);
		
		this->addChild(mainlineEvent);
	}
}

void SpriterAnimationTimelineEventAnimation::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void SpriterAnimationTimelineEventAnimation::update(float dt)
{
	super::update(dt);

	this->elapsedTime += dt;
	
	this->advance(this->elapsedTime);
}

void SpriterAnimationTimelineEventAnimation::advance(float elapsedTime)
{
	super::advance(elapsedTime);

	for (auto& next : this->mainlineEvents)
	{
		next->advance(elapsedTime);
	}
}

void SpriterAnimationTimelineEventAnimation::onFire()
{
}
