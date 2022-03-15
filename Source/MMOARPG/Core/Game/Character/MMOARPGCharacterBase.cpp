// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOARPGCharacterBase.h"

#include "../MMOARPGGameState.h"
#include "../Animation/Instance/MMOARPGAnimInstanceBase.h"

#include <Net/UnrealNetwork.h>

// Components
#include <Components/SkeletalMeshComponent.h>
#include "../../Components/FlyComponent.h"
#include "../../Components/SwimComponent.h"
#include "../../Components/FightComponent.h"


// Sets default values
AMMOARPGCharacterBase::AMMOARPGCharacterBase()
	: UserID(INDEX_NONE)
	, ActionState(ECharacterActionState::NORMAL_STATE)
	, LastActionState(ECharacterActionState::NORMAL_STATE)
	, CharacterID(INDEX_NONE)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Init Character Fly Component
	FlyComponent = CreateDefaultSubobject<UFlyComponent>(TEXT("CharacterFlyComponent"));
	//FlyComponent->SetupAttachment(RootComponent);
	
	// Init Character Swim Component
	SwimComponent = CreateDefaultSubobject<USwimComponent>(TEXT("CharacterSwimComponent"));

	// Init Character Fight Component
	FightComponent = CreateDefaultSubobject<UFightComponent>(TEXT("CharacterFightComponent"));

	// Init MMOARPG GAS Component
	GASComponent = CreateDefaultSubobject<UMMOARPGAbilitySystemComponent>(TEXT("MMOARPGAbilitySystemComponent"));
	GASComponent->SetIsReplicated(true); // set GAS component is replicated
}

void AMMOARPGCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// Register `ActionState` only update for Simulated Player (on other client)
	DOREPLIFETIME_CONDITION(AMMOARPGCharacterBase, ActionState, COND_SimulatedOnly);
}

// Called when the game starts or when spawned
void AMMOARPGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetWorld())
	{
		if (AMMOARPGGameState* GameState = GetWorld()->GetGameState<AMMOARPGGameState>())
		{
			// Init Switch Action State animation
			if (FCharacterAnimTableRow* SwitchStateAnimTR = GameState->GetCharacterAnimTableRow(GetCharacterID()))
			{
				SwitchStateAnimTableRow = SwitchStateAnimTR;
			}

			// Add inherent abilities
			if (FCharacterAbilityTableRow* AbilityTR = GameState->GetCharacterAbilityTableRow(GetCharacterID()))
			{
				CharacterAbilities.Add(TEXT("NormalAttack"), AddAbility(AbilityTR->NormalAttack));
			}
		}

		// Init FootIK
		if (!GetWorld()->IsServer())
		{
			if (GetMesh())
			{
				if (UMMOARPGAnimInstanceBase* AnimInstanceBase = Cast<UMMOARPGAnimInstanceBase>(GetMesh()->GetAnimInstance()))
				{
					AnimInstanceBase->InitAnimInstance(this);
				}
			}
		}
	}

	// Init GAS info
	GASComponent->InitAbilityActorInfo(this, this); 
}

// Called every frame
void AMMOARPGCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMMOARPGCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMMOARPGCharacterBase::SwitchActionState(ECharacterActionState InTargetActionState)
{
	if (ActionState == InTargetActionState)
	{
		// Switch into normal state
		ActionState = ECharacterActionState::NORMAL_STATE;
	}
	else
	{
		// Switch into target state
		ActionState = InTargetActionState;
	}
}

void AMMOARPGCharacterBase::AnimSignal(int32 InSignal)
{
	K2_AnimSignal(InSignal);
}

void AMMOARPGCharacterBase::ChangeActionStateOnServer_Implementation(ECharacterActionState InActionState)
{
	ActionState = InActionState;
	LastActionState = ActionState;
}

UAbilitySystemComponent* AMMOARPGCharacterBase::GetAbilitySystemComponent() const
{
	return GASComponent;
}

FGameplayAbilitySpecHandle AMMOARPGCharacterBase::AddAbility(TSubclassOf<UGameplayAbility> InNewAbility)
{
	if (IsValid(InNewAbility) && GASComponent)
	{
		return GASComponent->GiveAbility(FGameplayAbilitySpec(InNewAbility));
	}

	return FGameplayAbilitySpecHandle();
}

void AMMOARPGCharacterBase::NormalAttack(int32 InAnimIndex)
{
	if (GASComponent)
	{
		if (FGameplayAbilitySpecHandle* NormalAttackHandle = CharacterAbilities.Find(TEXT("NormalAttack")))
		{
			GASComponent->TryActivateAbility(*NormalAttackHandle);
		}
	}
}
