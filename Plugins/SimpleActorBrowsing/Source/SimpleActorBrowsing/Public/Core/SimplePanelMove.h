#pragma once

#include "CoreMinimal.h"
#include "Tickable.h" // make SimplePanelMove tickable in game process


namespace SimpleActorBrowse
{

	class SIMPLEACTORBROWSING_API FSimplePanelMove : public FTickableGameObject
	{
	public:
		FSimplePanelMove();

		void Register(APlayerController* InPlayerController, AActor* InTargetActor, float InTotalDistance);

		/**
		 * Pure virtual that must be overloaded by the inheriting class. It will
		 * be called from within LevelTick.cpp after ticking all actors or from
		 * the rendering thread (depending on bIsRenderingThreadObject)
		 *
		 * @param DeltaTime	Game time passed since the last call.
		 */
		virtual void Tick(float DeltaTime);
		/** return the stat id to use for this tickable **/
		FORCEINLINE TStatId GetStatId() const { return TStatId(); }

		FORCEINLINE void StartMove() { m_bMovePanel = true; }
		FORCEINLINE void EndMove() { m_bMovePanel = false; }
		FORCEINLINE void ResetTargetActor(AActor* InNewTarget) { m_TargetActor = InNewTarget; }

	protected:
		bool m_bMovePanel; // whether is move character
		APlayerController* m_PlayerController; // controller of the target acter
		TWeakObjectPtr<AActor> m_TargetActor; // move target actor
		FVector m_TargetLocation; // current target actor location
		FVector2D m_MousePos; // trace mouse position
		float m_TotalDistance; // distance that panel can move
	};

}