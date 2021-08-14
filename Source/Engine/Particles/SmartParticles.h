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
		cocos2d::CSize size;

		CullInfo() : cull(false), size(cocos2d::CSize::ZERO) { }
		CullInfo(cocos2d::CSize size) : cull(true), size(size) { }
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

	bool canUpdate = false;
	CullInfo cullInfo;

	std::string particleResource;

	// Pass through variables to cocos particles. We store them locally for better lazy initialization
	int particleTotalParticles = 0;
	cocos2d::Vec2 particlePosVar;
	cocos2d::Vec2 particleSourcePosition;
	float particleAngle = 0.0f;
	cocos2d::Vec2 particleAnchor;
	int particlePositionType = 0;

	bool hasAnchorOverride = false;
	bool hasPosVarOverride = false;
	bool hasSourcePositionOverride = false;
	bool hasTotalParticlesOverride = false;
	bool hasAngleOverride = false;
	bool hasPositionTypeOverride = false;

	cocos2d::CRect boundsRect;
	cocos2d::DrawNode* debugDrawNode = nullptr;
	cocos2d::Node* cullContainer = nullptr;
	cocos2d::ParticleSystem* particles = nullptr;
};
