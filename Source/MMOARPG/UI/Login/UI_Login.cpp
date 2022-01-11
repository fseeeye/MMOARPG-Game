// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Login.h"

#include "Components\Button.h"
#include "Components\EditableTextBox.h"

#include "UI_LoginMain.h"

void UUI_Login::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind methods to Button event
	SignInButton->OnReleased.AddDynamic(this, &UUI_Login::SignIn);
	SignUpButton->OnReleased.AddDynamic(this, &UUI_Login::SignUp);
}

void UUI_Login::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUI_Login::SignIn()
{
	if (UUI_LoginMain* InLoginMain = GetWidgetParent<UUI_LoginMain>())
	{
		// Get account & password text
		FString AccountString = Account->GetText().ToString();
		FString PasswordString = Password->GetText().ToString();

		// Call SignIn method in UI_LoginMain
		InLoginMain->SignIn(AccountString, PasswordString);
	}
}

void UUI_Login::SignUp()
{
	if (UUI_LoginMain* InLoginMain = GetWidgetParent<UUI_LoginMain>())
	{
		// TODO: Unimpl
		InLoginMain->SignUp();
	}
}
