#include "Core/SimpleRotate.h"


namespace SimpleActorBrowse
{

	FSimpleRotate::FSimpleRotate(APlayerController* InPlayerController, AActor* InTargetActor) 
		: m_bRotateCharacter(false), m_PlayerController(InPlayerController), m_TargetActor(InTargetActor)
	{
	}

	FSimpleRotate::FSimpleRotate()
		: m_bRotateCharacter(false), m_PlayerController(NULL), m_TargetActor(NULL)
	{

	}

	void FSimpleRotate::Register(APlayerController* InPlayerController, AActor* InTargetActor)
	{
		m_PlayerController = InPlayerController;
		m_TargetActor = InTargetActor;
	}

	void FSimpleRotate::Tick(float DeltaTime)
	{
		if (m_PlayerController && m_TargetActor.IsValid())
		{
			if (m_bRotateCharacter)
			{
				// get actor current rotation
				FRotator CurrentRotation = m_TargetActor->GetActorRotation();
				// get current mouse position when is browsed
				FVector2D NewMousePos;
				m_PlayerController->GetMousePosition(NewMousePos.X, NewMousePos.Y);

				// Rotate Actor
				float Rotation = (NewMousePos.X - m_MousePos.X) * -1.0f;
				CurrentRotation.Yaw += Rotation;
				m_TargetActor->SetActorRotation(CurrentRotation);

				m_MousePos = NewMousePos;
			}
			else
			{
				// get current mouse position when is not browsed
				m_PlayerController->GetMousePosition(m_MousePos.X, m_MousePos.Y);
			}
		}
	}

}