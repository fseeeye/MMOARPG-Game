// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_Base.h"
#include "UI_Login.generated.h"

class UEditableTextBox;
class UButton;
/**
 * 
 */
UCLASS()
class MMOARPG_API UUI_Login : public UUI_Base
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Account;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Password;

	UPROPERTY(meta = (BindWidget))
	UButton* SignInButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SignUpButton;

public:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	bool EncryptToLocal(const FString& Path); // encrypt correct passwd to local path
	bool DecryptFromLocal(const FString& Path); // decrypt passwd from local path

protected:
	UFUNCTION()
	void SignIn();

	UFUNCTION()
	void SignUp();
};
