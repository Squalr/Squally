#pragma once

#include "Engine/Events/DeserializationEvents.h"
#include "Engine/GlobalNode.h"

class RegisterStateDeserializer : public GlobalNode
{
public:
	static void registerGlobalNode();

private:
	typedef GlobalNode super;
	void initializeListeners() override;
	void onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args);

	static const std::string MapKeyRegisterState;
	static const std::string MapKeyRegisterEax;
	static const std::string MapKeyRegisterEbx;
	static const std::string MapKeyRegisterEcx;
	static const std::string MapKeyRegisterEdx;
	static const std::string MapKeyRegisterEdi;
	static const std::string MapKeyRegisterEsi;
	static const std::string MapKeyRegisterEbp;
	static const std::string MapKeyRegisterEsp;
	static const std::string MapKeyRegisterEip;
	static RegisterStateDeserializer* instance;
};
