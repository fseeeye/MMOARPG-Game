#include "Core/SimpleZoom.h"


namespace SimpleActorBrowse
{

	FSimpleZoom::FSimpleZoom()
		: m_TotalDistance(INDEX_NONE)
	{
	}

	void FSimpleZoom::Register(AActor* InTargetActor, float InTotalDistance)
	{
		m_TargetActor = InTargetActor;
		m_TotalDistance = InTotalDistance;
		m_TargetLocation = InTargetActor->GetActorLocation();
	}

	void FSimpleZoom::ZoomPositive(float InMovement)
	{
		if (m_TargetActor.IsValid() && InMovement > 0)
		{
			float MaxMovement = m_TargetLocation.X + m_TotalDistance / 2.f;

			FVector NewLocation = m_TargetActor->GetActorLocation();
			NewLocation.X += InMovement;

			if (NewLocation.X < MaxMovement)
			{
				m_TargetActor->SetActorLocation(NewLocation);
			}
		}
	}

	void FSimpleZoom::ZoomNegative(float InMovement)
	{
		if (m_TargetActor.IsValid() && InMovement < 0)
		{
			float MinMovement = m_TargetLocation.X - m_TotalDistance / 2.f;

			FVector NewLocation = m_TargetActor->GetActorLocation();
			NewLocation.X += InMovement;

			if (NewLocation.X > MinMovement)
			{
				m_TargetActor->SetActorLocation(NewLocation);
			}
		}
	}

}