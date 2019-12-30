#include "HackFlags.h"

#include "cocos/base/CCValue.h"

#include "Engine/Save/SaveManager.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

using namespace cocos2d;

std::map<std::string, int> HackFlagUtils::EssenceFlagMap = std::map<std::string, int>();

int HackFlagUtils::GetCurrentHackFlags(Inventory* inventory)
{
    static bool init = false;

    if (!init)
    {
        HackFlagUtils::EssenceFlagMap[SaveKeys::SaveKeyBlessingOfFire] = int(HackFlags::Fire);
        HackFlagUtils::EssenceFlagMap[SaveKeys::SaveKeyBlessingOfFrost] = int(HackFlags::Frost);
        HackFlagUtils::EssenceFlagMap[SaveKeys::SaveKeyBlessingOfLight] = int(HackFlags::Light);
        HackFlagUtils::EssenceFlagMap[SaveKeys::SaveKeyBlessingOfLightning] = int(HackFlags::Lightning);
        HackFlagUtils::EssenceFlagMap[SaveKeys::SaveKeyBlessingOfNature] = int(HackFlags::Nature);
        HackFlagUtils::EssenceFlagMap[SaveKeys::SaveKeyBlessingOfShadow] = int(HackFlags::Shadow);
        HackFlagUtils::EssenceFlagMap[SaveKeys::SaveKeyBlessingOfUndeath] = int(HackFlags::Undeath);
        HackFlagUtils::EssenceFlagMap[SaveKeys::SaveKeyBlessingOfWind] = int(HackFlags::Wind);

        init = true;
    }

	int flags = 0;

    for (auto next : HackFlagUtils::EssenceFlagMap)
    {
        if (SaveManager::getProfileDataOrDefault(next.first, Value(false)).asBool())
        {
            flags |= next.second;
        }
    }

	return flags;
}
