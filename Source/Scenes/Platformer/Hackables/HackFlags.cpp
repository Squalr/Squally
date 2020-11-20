#include "HackFlags.h"

#include "cocos/base/CCValue.h"

#include "Engine/Save/SaveManager.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

using namespace cocos2d;

std::map<std::string, int> HackFlagUtils::EssenceFlagMap = std::map<std::string, int>();

int HackFlagUtils::GetCurrentHackFlags()
{
    static bool init = false;

    if (!init)
    {
        HackFlagUtils::EssenceFlagMap[SaveKeys::SaveKeySpellBookArcane] = int(HackFlags::Arcane);
        HackFlagUtils::EssenceFlagMap[SaveKeys::SaveKeySpellBookFire] = int(HackFlags::Fire);
        HackFlagUtils::EssenceFlagMap[SaveKeys::SaveKeySpellBookFrost] = int(HackFlags::Frost);
        HackFlagUtils::EssenceFlagMap[SaveKeys::SaveKeySpellBookHoly] = int(HackFlags::Light);
        HackFlagUtils::EssenceFlagMap[SaveKeys::SaveKeySpellBookLightning] = int(HackFlags::Lightning);
        HackFlagUtils::EssenceFlagMap[SaveKeys::SaveKeySpellBookNature] = int(HackFlags::Nature);
        HackFlagUtils::EssenceFlagMap[SaveKeys::SaveKeySpellBookShadow] = int(HackFlags::Shadow);
        HackFlagUtils::EssenceFlagMap[SaveKeys::SaveKeySpellBookWater] = int(HackFlags::Water);
        HackFlagUtils::EssenceFlagMap[SaveKeys::SaveKeySpellBookWind] = int(HackFlags::Wind);

        init = true;
    }

	int flags = 0;

    for (auto next : HackFlagUtils::EssenceFlagMap)
    {
        if (SaveManager::GetProfileDataOrDefault(next.first, Value(false)).asBool())
        {
            flags |= next.second;
        }
    }

	return flags;
}
