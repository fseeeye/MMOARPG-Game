#include "Core/SimplePanelMove.h"

namespace SimpleActorBrowse
{



	FSimplePanelMove::FSimplePanelMove()
		: m_bMovePanel(false), m_TotalDistance(INDEX_NONE)
	{

	}

	void FSimplePanelMove::Register(APlayerController* InPlayerController, AActor* InTargetActor, float InTotalDistance)
	{
		m_PlayerController = InPlayerController;
		m_TargetActor = InTargetActor;
		m_TotalDistance = InTotalDistance;
		m_TargetLocation = InTargetActor->GetActorLocation();
	}

	void FSimplePanelMove::Tick(float DeltaTime)
	{
		if (m_PlayerController && m_TargetActor.IsValid())
		{
			if (m_bMovePanel)
			{
				float MaxMovement = m_TargetLocation.Z + m_TotalDistance / 2.f;
				float MinMovement = m_TargetLocation.Z - m_TotalDistance / 2.f;

				// get actor current rotation
				FVector CurrentLocation = m_TargetActor->GetActorLocation();
				// get current mouse position when is browsed
				FVector2D NewMousePos;
				m_PlayerController->GetMousePosition(NewMousePos.X, NewMousePos.Y);

				// Rotate Actor
				float Movement = (NewMousePos.Y - m_MousePos.Y) * -1.0f;
				CurrentLocation.Z += Movement;
				if (CurrentLocation.Z < MaxMovement && CurrentLocation.Z > MinMovement)
				{
					m_TargetActor->SetActorLocation(CurrentLocation);
				}

				m_MousePos = NewMousePos;
			}
			else
			{
				// get current mouse position when is not moved
				m_PlayerController->GetMousePosition(m_MousePos.X, m_MousePos.Y);
			}
		}
	}

}