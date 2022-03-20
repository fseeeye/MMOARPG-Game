// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "MMOARPGCharacterBase.h"
#include "SimpleComboType.h"

#include "MMOARPGCharacter.generated.h"

UCLASS(config=Game)
class AMMOARPGCharacter : public AMMOARPGCharacterBase
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AMMOARPGCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector InLocation);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector InLocation);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE virtual class UCameraComponent* GetFollowCamera() const override { return FollowCamera; }

	/*** Switch State ***/
protected:
	// Switch Action state to FIGHT (Autonomous Proxy)
	void SwitchFight();

	// Play Fight animation montage
	void PlayFightMontage();

	// Switch Action state to FLY (Autonomous Proxy)
	UFUNCTION(Server, Reliable)
	void SwitchFlyOnServer();

	UFUNCTION(NetMulticast, Reliable)
	void SwitchFlyMulticast();
	
	// Switch to Speed Up when at some Action State
	UFUNCTION(Server, Reliable)
	void SwitchSpeedUpOnServer();

	UFUNCTION(Server, Reliable)
	void SwitchSpeedUpReleasedOnServer();

	UFUNCTION(NetMulticast, Reliable)
	void SwitchSpeedUpMulticast();

	UFUNCTION(NetMulticast, Reliable)
	void SwitchSpeedUpReleasedMulticast();

	// Switch Dodge state when fast fly (flying speedup)
	UFUNCTION(Server, Reliable)
	void SwitchDodgeLeft();

	UFUNCTION(Server, Reliable)
	void SwitchDodgeRight();

	UFUNCTION(NetMulticast, Reliable)
	void SwitchDodgeLeftMulticast();

	UFUNCTION(NetMulticast, Reliable)
	void SwitchDodgeRightMulticast();

	// Play anim montage when Action state changed (Simulated Proxy)
	virtual void OnRep_ActionStateChanged() override;

	/*** Gameplay Ability ***/
public:
	// Normal Attack
	UFUNCTION(Server, Reliable)
	void MouseLeftPressed();

	UFUNCTION(Server, Reliable)
	void MouseLeftReleased();

	// Dodge
	UFUNCTION(Server, Reliable)
	void MouseRightPressed();

	UFUNCTION(Server, Reliable)
	void MouseRightReleased();

	// Sprint
	UFUNCTION(Server, Reliable)
	void SprintPressed();

	virtual FSimpleComboAttack* GetComboAttack() override;
	virtual void AnimSignal(int32 InSignal) override;
};

