#include "MiniMapObjectBinderDeserializer.h"

#include "Objects/Platformer/PlatformerObjects.h"

using namespace cocos2d;

#include "Objects/Platformer/MiniMap/Binders/Binders.h"

std::map<std::string, std::function<MiniMapObjectBinder*()>> MiniMapObjectBinderDeserializer::BindingTable = std::map<std::string, std::function<MiniMapObjectBinder*()>>();

MiniMapObjectBinder* MiniMapObjectBinderDeserializer::Deserialize(std::string objectName)
{
    MiniMapObjectBinderDeserializer::InitializeBindingTable();

    if (MiniMapObjectBinderDeserializer::BindingTable.contains(objectName))
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

    // Physics
    MiniMapObjectBinderDeserializer::BindingTable[FloatingAsteroid::MapKey] = [=](){ return BinderDensityObject::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[FloatingBomb::MapKey] = [=](){ return BinderDensityObject::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[FloatingCrate::MapKey] = [=](){ return BinderDensityObject::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[FloatingRock::MapKey] = [=](){ return BinderDensityObject::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[FloatingWoodenBeam::MapKey] = [=](){ return BinderDensityObject::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[TrapDoor::MapKey] = [=](){ return BinderTrapDoor::create(); };
    
    // Collectables
    MiniMapObjectBinderDeserializer::BindingTable[IOUDrop::MapKey] = [=](){ return BinderCollectable::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[IOUDrop5::MapKey] = [=](){ return BinderCollectable::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[IOUDrop10::MapKey] = [=](){ return BinderCollectable::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[IOUDrop25::MapKey] = [=](){ return BinderCollectable::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[ManaOrb::MapKey] = [=](){ return BinderCollectable::create(); };

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
    MiniMapObjectBinderDeserializer::BindingTable[ScreamingDoor::MapKey] = [=](){ return BinderPortal::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[TempleDoor::MapKey] = [=](){ return BinderPortal::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[Warp::MapKey] = [=](){ return BinderPortal::create(); };
}
