#pragma once
#include <string>

#include "Engine/SmartNode.h"

class HackablePreview;
template <class T>
class LazyNode;
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

	std::string getHackableIdentifier();
	int getRequiredHackFlag();
	float getElapsedDuration();
	float getDuration();
	bool isComplete();
	bool isCooldownComplete();
	float getElapsedCooldown();
	float getCooldown();
	void tryRefreshCooldown();
	std::string getHackBarResource();
	std::string getHackBarCooldownResource();
	HackBarColor getHackBarColor();
	std::string getIconResource();
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

	float duration;
	float cooldown;
	float elapsedDuration;
	float elapsedCooldown;
	bool isHackActive;

	std::string hackableIdentifier;
	LocalizedString* name;
	HackBarColor hackBarColor;
	std::string iconResource;
	LazyNode<HackablePreview>* hackablePreview;
	int requiredHackFlag;
};
