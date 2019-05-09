#pragma once

#include "Events/CipherEvents.h"
#include "Engine/GlobalNode.h"

class CipherPuzzleData;

class CipherPuzzleDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();
	
	static CipherPuzzleData* deserialize(std::string json, bool isHardMode);

private:
	typedef GlobalNode super;
	void initializeListeners() override;
	void onDeserializationRequest(CipherEvents::CipherOpenArgs* args);

	static CipherPuzzleDeserializer* instance;
};
