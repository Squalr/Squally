#pragma once
#include <string>

#include "Engine/SmartNode.h"

class Clippy;
class HackablePreview;
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
	std::string getHackBarResource();
	HackBarColor getHackBarColor();
	std::string getIconResource();
	LocalizedString* getName();
	HackablePreview* getHackablePreview();
	virtual void* getPointer();
	virtual void restoreState();
	void restoreStateIfUnique();

protected:
	HackableBase(
		std::string hackableIdentifier,
		int requiredHackFlags,
		float duration,
		float cooldown,
		HackBarColor hackBarColor,
		std::string iconResource,
		LocalizedString* name,
		HackablePreview* hackablePreview
	);
	virtual ~HackableBase();

	void onEnter() override;
	void initializeListeners() override;
	void update(float dt);
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

	std::string hackableIdentifier;
	LocalizedString* name;
	HackBarColor hackBarColor;
	std::string iconResource;
	HackablePreview* hackablePreview;
	int requiredHackFlag;
};
