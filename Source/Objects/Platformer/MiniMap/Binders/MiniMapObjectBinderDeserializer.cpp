#include "MiniMapObjectBinderDeserializer.h"

#include "Objects/Platformer/PlatformerObjects.h"

using namespace cocos2d;

#include "Objects/Platformer/MiniMap/Binders/Binders.h"

std::map<std::string, std::function<MiniMapObjectBinder*()>> MiniMapObjectBinderDeserializer::BindingTable = std::map<std::string, std::function<MiniMapObjectBinder*()>>();

MiniMapObjectBinder* MiniMapObjectBinderDeserializer::Deserialize(std::string objectName)
{
    MiniMapObjectBinderDeserializer::InitializeBindingTable();

    if (MiniMapObjectBinderDeserializer::BindingTable.find(objectName) != MiniMapObjectBinderDeserializer::BindingTable.end())
    {
        return MiniMapObjectBinderDeserializer::BindingTable[objectName]();
    }

    return BinderDefault::create();
}

void MiniMapObjectBinderDeserializer::InitializeBindingTable()
{
    static bool runOnce = false;

    if (runOnce)
    {
        return;
    }

    runOnce = true;

    // Puzzles
    MiniMapObjectBinderDeserializer::BindingTable[LogicGate::MapKey] = [=](){ return BinderLogicGate::create(); };

    // Traps
    MiniMapObjectBinderDeserializer::BindingTable[MechanicalFlail::MapKey] = [=](){ return BinderMechanicalFlail::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[PendulumBlade::MapKey] = [=](){ return BinderPendulumBlade::create(); };

    // Doors
    MiniMapObjectBinderDeserializer::BindingTable[AddDoor::MapKey] = [=](){ return BinderPortal::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[DragonDoor::MapKey] = [=](){ return BinderPortal::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[EdgePortal::MapKey] = [=](){ return BinderPortal::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[FloatTutorialPortal::MapKey] = [=](){ return BinderPortal::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[MagePortal::MapKey] = [=](){ return BinderPortal::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[MayanDoor::MapKey] = [=](){ return BinderPortal::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[MulDoor::MapKey] = [=](){ return BinderPortal::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[OptionWarp::MapKey] = [=](){ return BinderPortal::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[Portal::MapKey] = [=](){ return BinderPortal::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[TempleDoor::MapKey] = [=](){ return BinderPortal::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[Warp::MapKey] = [=](){ return BinderPortal::create(); };
}
