#pragma once
#include <string>

#include "Engine/SmartNode.h"

class HackablePreview;
template <class T> class LazyNode;
class LocalizedString;

class HackableBase : public SmartNode
{
public:
	enum class HackBarColor
	{
		Blue,
		Gray,
		Green,
		Orange,
		Pink,
		Purple,
		Red,
		Teal,
		Yellow
	};

	const std::string& getHackableIdentifier();
	int getRequiredHackFlag();
	float getElapsedDuration();
	float getDuration();
	bool isComplete();
	bool isCooldownComplete();
	float getElapsedCooldown();
	float getCooldown();
	void tryRefreshCooldown();
	const std::string& getHackBarResource();
	const std::string& getHackBarCooldownResource();
	HackBarColor getHackBarColor();
	const std::string& getIconResource();
	LocalizedString* getName();
	LazyNode<HackablePreview>* getHackablePreview();
	virtual void* getPointer();
	virtual void restoreState();

protected:
	HackableBase(
		std::string hackableIdentifier,
		int requiredHackFlags,
		float duration,
		float cooldown,
		HackBarColor hackBarColor,
		std::string iconResource,
		LocalizedString* name,
		LazyNode<HackablePreview>* hackablePreview
	);
	virtual ~HackableBase();

	void onEnter() override;
	void initializeListeners() override;
	void update(float dt) override;
	void startTimer();
	void resetTimer();

	static bool HackTimersPaused;

private:
	typedef SmartNode super;
	friend class GlobalHackAttributeContainer;

	float duration = 0.0f;
	float cooldown = 0.0f;
	float elapsedDuration = 0.0f;
	float elapsedCooldown = 0.0f;
	bool isHackActive = false;

	std::string hackableIdentifier;
	LocalizedString* name = nullptr;
	HackBarColor hackBarColor;
	std::string iconResource;
	LazyNode<HackablePreview>* hackablePreview = nullptr;
	int requiredHackFlag = 0;
};
