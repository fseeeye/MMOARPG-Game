// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "../../../DataTable/CharacterAnimTableRow.h"
#include "../MMOARPGGameMode.h"
#include "../../../MMOARPGGameType.h"

// Plugins
#include "Interface/SimpleCombatInterface.h"

#include "MMOARPGCharacterBase.generated.h"


class UFlyComponent;

UCLASS()
class MMOARPG_API AMMOARPGCharacterBase : public ACharacter, public ISimpleCombatInterface
{
	GENERATED_BODY()

	friend class AMMOARPGGameMode;

	/* Fly Component */
	UPROPERTY()
	TObjectPtr<UFlyComponent> FlyComponent;

public:
	// Sets default values for this character's properties
	AMMOARPGCharacterBase();

	// For Replicated property
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*** Kneading Face Data ***/
public:
	UPROPERTY()
	int32 UserID;

public:
	FORCEINLINE int32 GetUserID() { return UserID; }

	/*** Switch Action State ***/
public:
	FORCEINLINE ECharacterActionState GetActionState() { return ActionState; }
	FORCEINLINE int32 GetCharacterID() { return CharacterID; }
	FORCEINLINE FCharacterAnimTableRow* GetCharacterSwitchStateAnimTableRow() { return SwitchStateAnimTableRow; }
	FORCEINLINE UFlyComponent* GetFlyComponent() { return FlyComponent; }

	void SwitchActionState(ECharacterActionState InTargetActionState);

public:
	virtual void AnimSignal(int32 InSignal) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, DisplayName = "AnimSignal", Category = "Anim Event")
	void K2_AnimSignal(int32 InSignal);

protected:
	// Do sth. when Action State changed
	UFUNCTION()
	virtual void OnRep_ActionStateChanged() {}

	// Change Action State property by RPC (Authority)
	UFUNCTION(Server, Reliable)
	void ChangeActionStateOnServer(ECharacterActionState InActionState);

protected:
	UPROPERTY(ReplicatedUsing = OnRep_ActionStateChanged)
	ECharacterActionState ActionState;

	UPROPERTY()
	ECharacterActionState LastActionState;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	int32 CharacterID;
	
protected:
	FCharacterAnimTableRow* SwitchStateAnimTableRow;

};
