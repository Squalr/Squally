#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Item;
class LocalizedString;
class Squally;

class SquallyReceiveItemBehavior : public AttachedBehavior
{
public:
	static SquallyReceiveItemBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyReceiveItemBehavior(GameObject* owner);
	virtual ~SquallyReceiveItemBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	void obtainItems(const std::vector<Item*>& items, LocalizedString* messageOverride, bool keepOpen);

	Squally* squally;
};
