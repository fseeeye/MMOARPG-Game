#pragma once

#include "CoreMinimal.h"
#include "Tickable.h" // make SimpleRotate tickable in game process


namespace SimpleActorBrowse
{

	class SIMPLEACTORBROWSING_API FSimpleRotate : public FTickableGameObject
	{
	public:
		FSimpleRotate(APlayerController* InPlayerController, AActor* InTargetActor);
		FSimpleRotate();

		void Register(APlayerController* InPlayerController, AActor* InTargetActor);

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

		FORCEINLINE void StartRotating() { m_bRotateCharacter = true; }
		FORCEINLINE void EndRotating() { m_bRotateCharacter = false; }
		FORCEINLINE void ResetTargetActor(AActor* InNewTarget) { m_TargetActor = InNewTarget; }

	protected:
		bool m_bRotateCharacter; // whether is rotate character
		APlayerController* m_PlayerController; // controller of the target acter
		TWeakObjectPtr<AActor> m_TargetActor; // rotate target actor
		FVector2D m_MousePos; // trace mouse position
	};

}