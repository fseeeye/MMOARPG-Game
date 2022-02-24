#pragma once

#include "CoreMinimal.h"


namespace MethodUnit
{
	enum EServerCallResult : uint8
	{
		INPROGRESS,
		PROGRESS_COMPLETE
	};

	template<class T>
	void CallAllPlayerControllersOnServer(UWorld* InWorld, TFunction<EServerCallResult(T*)> InImplement)
	{
		// Traverse all player controllers
		for (FConstPlayerControllerIterator It = InWorld->GetPlayerControllerIterator(); It; ++It)
		{
			if (T* PlayerController = Cast<T>(It->Get()))
			{
				// Call function
				if (InImplement(PlayerController) == EServerCallResult::PROGRESS_COMPLETE)
					break;
			}
		}
	}

	template<class T>
	void CallAllPlayersOnServer(UWorld* InWorld, TFunction<EServerCallResult(T*)> InImplement)
	{
		CallAllPlayerControllersOnServer<APlayerController>(InWorld, [&](APlayerController* InPlayerController)->EServerCallResult
		{
			if (T* Pawn = Cast<T>(InPlayerController->GetPawn()))
			{
				return InImplement(Pawn);
			}

			return EServerCallResult::INPROGRESS;
		});
	}

}