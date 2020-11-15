#pragma once
#include <string>

#include "Engine/Hackables/HackableBase.h"

class Clippy;
class LocalizedString;

class HackActivatedAbility : public HackableBase
{
public:
	static HackActivatedAbility* create(
		std::string hackableIdentifier,
		std::function<void()> onActivate,
		std::function<void()> onDeactivate,
		int hackFlags,
		float duration,
		HackBarColor hackBarColor,
		std::string iconResource,
		LocalizedString* name,
		HackablePreview* hackablePreview,
		Clippy* clippy = nullptr);

	void activate();

protected:
	HackActivatedAbility(
		std::string hackableIdentifier,
		std::function<void()> onActivate,
		std::function<void()> onDeactivate,
		int hackFlags, 
		float duration,
		HackBarColor hackBarColor,
		std::string iconResource,
		LocalizedString* name,
		HackablePreview* hackablePreview,
		Clippy* clippy = nullptr);
	virtual ~HackActivatedAbility();
	
	void restoreState() override;

private:
	typedef HackableBase super;
	friend class GlobalHackAttributeContainer;

	std::function<void()> onActivate;
	std::function<void()> onDeactivate;
};
