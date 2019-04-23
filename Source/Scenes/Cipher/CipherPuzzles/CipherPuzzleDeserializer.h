#pragma once

#include "Events/CipherEvents.h"
#include "Engine/GlobalNode.h"

class CipherPuzzleDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	typedef GlobalNode super;
	void initializeListeners() override;
	void onDeserializationRequest(CipherEvents::CipherOpenArgs* args);

	static CipherPuzzleDeserializer* instance;
};
