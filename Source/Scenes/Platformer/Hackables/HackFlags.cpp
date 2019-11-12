#include "HackFlags.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

std::map<std::string, int> HackFlagUtils::EssenceFlagMap = std::map<std::string, int>();

int HackFlagUtils::GetCurrentHackFlags(Inventory* inventory)
{
    static bool init = false;

    if (!init)
    {
        HackFlagUtils::EssenceFlagMap[EssenceOfFire::SaveKeyEssenceOfFire] = int(HackFlags::Fire);
        HackFlagUtils::EssenceFlagMap[EssenceOfFrost::SaveKeyEssenceOfFrost] = int(HackFlags::Frost);
        HackFlagUtils::EssenceFlagMap[EssenceOfLight::SaveKeyEssenceOfLight] = int(HackFlags::Light);
        HackFlagUtils::EssenceFlagMap[EssenceOfLightning::SaveKeyEssenceOfLightning] = int(HackFlags::Lightning);
        HackFlagUtils::EssenceFlagMap[EssenceOfNature::SaveKeyEssenceOfNature] = int(HackFlags::Nature);
        HackFlagUtils::EssenceFlagMap[EssenceOfShadow::SaveKeyEssenceOfShadow] = int(HackFlags::Shadow);
        HackFlagUtils::EssenceFlagMap[EssenceOfUndeath::SaveKeyEssenceOfUndeath] = int(HackFlags::Undeath);
        HackFlagUtils::EssenceFlagMap[EssenceOfWind::SaveKeyEssenceOfWind] = int(HackFlags::Wind);

        init = true;
    }

	int flags = 0;
	std::vector<Item*> items = inventory->getItems();

	for (auto it = items.begin(); it != items.end(); it++)
	{
		if (HackFlagUtils::EssenceFlagMap.find((*it)->getItemName()) != HackFlagUtils::EssenceFlagMap.end())
		{
			flags |= HackFlagUtils::EssenceFlagMap[(*it)->getItemName()];
		}
	}

	return flags;
}
