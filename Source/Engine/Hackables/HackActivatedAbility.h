#pragma once
#include <string>

#include "Engine/Hackables/HackableAttribute.h"
#include "Engine/Utils/HackUtils.h"

class HackableCode;
class LocalizedString;

class HackActivatedAbility : public HackableAttribute
{
public:
	static HackActivatedAbility* create(
		std::function<void()> onActivate,
		std::function<void()> onDeactivate,
		int requiredEq,
		float duration,
		std::string iconResource,
		LocalizedString* name,
		HackablePreview* hackablePreview,
		Clippy* clippy = nullptr);

	void activate();

protected:
	HackActivatedAbility(std::function<void()> onActivate,
		std::function<void()> onDeactivate,
		int requiredEq, 
		float duration,
		std::string iconResource,
		LocalizedString* name,
		HackablePreview* hackablePreview,
		Clippy* clippy = nullptr);
	virtual ~HackActivatedAbility();
	
	void restoreState() override;

private:
	typedef HackableAttribute super;

	std::function<void()> onActivate;
	std::function<void()> onDeactivate;
};
