#include "Collectables.h"

#include "base/CCValue.h"

#include "Engine/Save/SaveManager.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

std::vector<Collectables::CollectableData> Collectables::CollectableAnimalData = std::vector<Collectables::CollectableData>();

int Collectables::getCollectedAnimalTotal()
{
    Collectables::buildAnimalData();

    return Collectables::CollectableAnimalData.size();
}

int Collectables::getCollectedAnimalCount()
{
    Collectables::buildAnimalData();

    int collectedCount = 0;

    for (auto next : Collectables::CollectableAnimalData)
    {
        collectedCount += (SaveManager::GetProfileDataOrDefault(next.saveKey, Value(false)).asBool() ? 1 : 0);
    }

    return collectedCount;
}

std::vector<Collectables::CollectableData> Collectables::getCollectableAnimalData()
{
    Collectables::buildAnimalData();

    return Collectables::CollectableAnimalData;
}

void Collectables::buildAnimalData()
{
    static bool runOnce = false;

    if (runOnce)
    {
        return;
    }

    Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Bat, ObjectResources::Collectables_Animals_Bat_Locked, SaveKeys::SaveKeyCollectableAnimalBat));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Bear, ObjectResources::Collectables_Animals_Bear_Locked, SaveKeys::SaveKeyCollectableAnimalBear));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Beaver, ObjectResources::Collectables_Animals_Beaver_Locked, SaveKeys::SaveKeyCollectableAnimalBeaver));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Bee, ObjectResources::Collectables_Animals_Bee_Locked, SaveKeys::SaveKeyCollectableAnimalBee));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Bird, ObjectResources::Collectables_Animals_Bird_Locked, SaveKeys::SaveKeyCollectableAnimalBird));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Blowfish, ObjectResources::Collectables_Animals_Blowfish_Locked, SaveKeys::SaveKeyCollectableAnimalBlowfish));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Bull, ObjectResources::Collectables_Animals_Bull_Locked, SaveKeys::SaveKeyCollectableAnimalBull));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Bunny, ObjectResources::Collectables_Animals_Bunny_Locked, SaveKeys::SaveKeyCollectableAnimalBunny));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Cat, ObjectResources::Collectables_Animals_Cat_Locked, SaveKeys::SaveKeyCollectableAnimalCat));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Chicken, ObjectResources::Collectables_Animals_Chicken_Locked, SaveKeys::SaveKeyCollectableAnimalChicken));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Cow, ObjectResources::Collectables_Animals_Cow_Locked, SaveKeys::SaveKeyCollectableAnimalCow));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Crocodile, ObjectResources::Collectables_Animals_Crocodile_Locked, SaveKeys::SaveKeyCollectableAnimalCrocodile));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Dinosaur, ObjectResources::Collectables_Animals_Dinosaur_Locked, SaveKeys::SaveKeyCollectableAnimalDinosaur));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Dog, ObjectResources::Collectables_Animals_Dog_Locked, SaveKeys::SaveKeyCollectableAnimalDog));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Duck, ObjectResources::Collectables_Animals_Duck_Locked, SaveKeys::SaveKeyCollectableAnimalDuck));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Fox, ObjectResources::Collectables_Animals_Fox_Locked, SaveKeys::SaveKeyCollectableAnimalFox));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Giraffe, ObjectResources::Collectables_Animals_Giraffe_Locked, SaveKeys::SaveKeyCollectableAnimalGiraffe));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Goat, ObjectResources::Collectables_Animals_Goat_Locked, SaveKeys::SaveKeyCollectableAnimalGoat));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Hedgehog, ObjectResources::Collectables_Animals_Hedgehog_Locked, SaveKeys::SaveKeyCollectableAnimalHedgehog));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Hippo, ObjectResources::Collectables_Animals_Hippo_Locked, SaveKeys::SaveKeyCollectableAnimalHippo));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Horse, ObjectResources::Collectables_Animals_Horse_Locked, SaveKeys::SaveKeyCollectableAnimalHorse));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_KillerWhale, ObjectResources::Collectables_Animals_KillerWhale_Locked, SaveKeys::SaveKeyCollectableAnimalKillerWhale));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Koala, ObjectResources::Collectables_Animals_Koala_Locked, SaveKeys::SaveKeyCollectableAnimalKoala));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Ladybug, ObjectResources::Collectables_Animals_Ladybug_Locked, SaveKeys::SaveKeyCollectableAnimalLadybug));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Lion, ObjectResources::Collectables_Animals_Lion_Locked, SaveKeys::SaveKeyCollectableAnimalLion));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Lizard, ObjectResources::Collectables_Animals_Lizard_Locked, SaveKeys::SaveKeyCollectableAnimalLizard));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Monkey, ObjectResources::Collectables_Animals_Monkey_Locked, SaveKeys::SaveKeyCollectableAnimalMonkey));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_MountainLion, ObjectResources::Collectables_Animals_MountainLion_Locked, SaveKeys::SaveKeyCollectableAnimalMountainLion));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Mouse, ObjectResources::Collectables_Animals_Mouse_Locked, SaveKeys::SaveKeyCollectableAnimalMouse));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Panda, ObjectResources::Collectables_Animals_Panda_Locked, SaveKeys::SaveKeyCollectableAnimalPanda));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Parrot, ObjectResources::Collectables_Animals_Parrot_Locked, SaveKeys::SaveKeyCollectableAnimalParrot));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Penguin, ObjectResources::Collectables_Animals_Penguin_Locked, SaveKeys::SaveKeyCollectableAnimalPenguin));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Pig, ObjectResources::Collectables_Animals_Pig_Locked, SaveKeys::SaveKeyCollectableAnimalPig));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Raccoon, ObjectResources::Collectables_Animals_Raccoon_Locked, SaveKeys::SaveKeyCollectableAnimalRaccoon));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Reindeer, ObjectResources::Collectables_Animals_Reindeer_Locked, SaveKeys::SaveKeyCollectableAnimalReindeer));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Rhino, ObjectResources::Collectables_Animals_Rhino_Locked, SaveKeys::SaveKeyCollectableAnimalRhino));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Sheep, ObjectResources::Collectables_Animals_Sheep_Locked, SaveKeys::SaveKeyCollectableAnimalSheep));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Skunk, ObjectResources::Collectables_Animals_Skunk_Locked, SaveKeys::SaveKeyCollectableAnimalSkunk));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Snail, ObjectResources::Collectables_Animals_Snail_Locked, SaveKeys::SaveKeyCollectableAnimalSnail));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Snake, ObjectResources::Collectables_Animals_Snake_Locked, SaveKeys::SaveKeyCollectableAnimalSnake));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Squid, ObjectResources::Collectables_Animals_Squid_Locked, SaveKeys::SaveKeyCollectableAnimalSquid));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Squirrel, ObjectResources::Collectables_Animals_Squirrel_Locked, SaveKeys::SaveKeyCollectableAnimalSquirrel));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Tiger, ObjectResources::Collectables_Animals_Tiger_Locked, SaveKeys::SaveKeyCollectableAnimalTiger));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Tucan, ObjectResources::Collectables_Animals_Tucan_Locked, SaveKeys::SaveKeyCollectableAnimalTucan));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Turtle, ObjectResources::Collectables_Animals_Turtle_Locked, SaveKeys::SaveKeyCollectableAnimalTurtle));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Whale, ObjectResources::Collectables_Animals_Whale_Locked, SaveKeys::SaveKeyCollectableAnimalWhale));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Wolf, ObjectResources::Collectables_Animals_Wolf_Locked, SaveKeys::SaveKeyCollectableAnimalWolf));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Worm, ObjectResources::Collectables_Animals_Worm_Locked, SaveKeys::SaveKeyCollectableAnimalWorm));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Yeti, ObjectResources::Collectables_Animals_Yeti_Locked, SaveKeys::SaveKeyCollectableAnimalYeti));
	Collectables::CollectableAnimalData.push_back(CollectableData(ObjectResources::Collectables_Animals_Zebra, ObjectResources::Collectables_Animals_Zebra_Locked, SaveKeys::SaveKeyCollectableAnimalZebra));

    runOnce = true;
}
