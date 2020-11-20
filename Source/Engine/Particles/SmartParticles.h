#pragma once
#include <string>

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class DrawNode;
	class ParticleSystem;
}

class SmartParticles : public GameObject
{
public:

	struct CullInfo
	{
		bool cull;
		cocos2d::Size size;

		CullInfo() : cull(false), size(cocos2d::Size::ZERO) { }
		CullInfo(cocos2d::Size size) : cull(true), size(size) { }
	};

	static SmartParticles* create(std::string particleResource, CullInfo cullInfo = CullInfo());

	void start();
	void restart();
	void stop(float disableUpdateAfter = 0.0f);
	bool isActive();
	void accelerate(float duration);

	void setTotalParticles(int totalParticles);
	void setPosVar(cocos2d::Vec2 posVar);
	void setSourcePosition(cocos2d::Vec2 sourcePosition);
	void setAngle(float angle);
	void setParticleAnchorPoint(cocos2d::Vec2 anchorPoint);
	void setGrouped();
	void setRelative();
	void setFree();

protected:
	SmartParticles(std::string particleResource, CullInfo cullInfo);
	virtual ~SmartParticles();

	void onEnter() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;
	void update(float dt) override;

private:
	typedef GameObject super;

	void tryCreateParticleInstance();
	void optimizationHideOffscreenParticles();

	bool canUpdate;
	CullInfo cullInfo;

	std::string particleResource;

	// Pass through variables to cocos particles. We store them locally for better lazy initialization
	int particleTotalParticles;
	cocos2d::Vec2 particlePosVar;
	cocos2d::Vec2 particleSourcePosition;
	float particleAngle;
	cocos2d::Vec2 particleAnchor;
	int particlePositionType;

	bool hasAnchorOverride;
	bool hasPosVarOverride;
	bool hasSourcePositionOverride;
	bool hasTotalParticlesOverride;
	bool hasAngleOverride;
	bool hasPositionTypeOverride;

	cocos2d::Rect boundsRect;
	cocos2d::DrawNode* debugDrawNode;
	cocos2d::Node* cullContainer;
	cocos2d::ParticleSystem* particles;
};
