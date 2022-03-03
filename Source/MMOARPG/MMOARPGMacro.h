#pragma once

#include "Core/Common/MMOARPGGameInstance.h"

#define MMOARPG_DEBUG_DS 1

#if PLATFORM_WINDOWS
#define SEND_DATA(InProtocols, ...) \
if (UMMOARPGGameInstance* MMOGameInstance = GetGameInstance<UMMOARPGGameInstance>()) \
{\
	SIMPLE_CLIENT_SEND(MMOGameInstance->GetNetClient(), InProtocols, __VA_ARGS__); \
}
#else
#define SEND_DATA(InProtocols, args...) \
if (UMMOARPGGameInstance* MMOGameInstance = GetGameInstance<UMMOARPGGameInstance>()) \
{\
	SIMPLE_CLIENT_SEND(MMOGameInstance->GetNetClient(), InProtocols, ##args); \
}
#endif