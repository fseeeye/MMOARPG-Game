#pragma once

#include "CoreMinimal.h"


namespace SimpleActorBrowse
{

	class SIMPLEACTORBROWSING_API FSimpleZoom
	{
	public:
		FSimpleZoom();

		void Register(AActor* InTargetActor, float InTotalDistance);

		void ZoomPositive(float InMovement);
		void ZoomNegative(float InMovement);

	protected:
		TWeakObjectPtr<AActor> m_TargetActor; // zoom target actor
		FVector m_TargetLocation; // zoom target actor location
		float m_TotalDistance; // the total distance that target actor can move
	};

}