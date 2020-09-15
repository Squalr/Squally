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

    MiniMapObjectBinderDeserializer::BindingTable[LogicGate::MapKey] = [=](){ return BinderLogicGate::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[MechanicalFlail::MapKey] = [=](){ return BinderMechanicalFlail::create(); };
    MiniMapObjectBinderDeserializer::BindingTable[PendulumBlade::MapKey] = [=](){ return BinderPendulumBlade::create(); };
}
