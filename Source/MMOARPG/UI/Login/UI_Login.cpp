// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Login.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"

#include "Stream/SimpleIOStream.h" // Plugin: SimpleNetChannel

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

bool UUI_Login::EncryptToLocal(const FString& Path)
{
	FString AccountString = Account->GetText().ToString();
	FString PasswordString = Password->GetText().ToString();

	// Fix Path
	FString NormalizedPath = Path;
	FPaths::NormalizeFilename(NormalizedPath); // `\\`->`/`
	NormalizedPath.RemoveFromEnd(TEXT("/"));

	if (!AccountString.IsEmpty() && !PasswordString.IsEmpty() && !NormalizedPath.IsEmpty())
	{
		// Account MD5 Hashing 32 times
		FString AccountHash = FMD5::HashAnsiString(*AccountString);
		for (int32 i = 0; i < 32; i++)
		{
			AccountHash = FMD5::HashAnsiString(*AccountHash);
		}

		// Password AES Encryption
		if (!AccountHash.IsEmpty())
		{
			TArray<uint8> PasswdBuff;
			FSimpleIOStream Stream(PasswdBuff);
			Stream << PasswordString;

			// Add padding to Password Buffer until it's multiples of 16
			int32 PaddingLen = 0;
			int32 HashLen = PasswdBuff.Num();
			if (HashLen % 16 != 0)
			{
				int32 TargetLen = FMath::CeilToInt((float)HashLen / 16.f) * 16;
				PaddingLen = TargetLen - HashLen;
			}

			for (int32 i = 0; i < PaddingLen; i++)
			{
				uint8 HashPadding = 0;
				Stream << HashPadding;
			}

			// Set Account Hash as AES Key
			ANSICHAR* Key = TCHAR_TO_UTF8(*AccountHash);

			// Encrypt Password
			FAES::EncryptData(PasswdBuff.GetData(), PasswdBuff.Num(), Key);

			// Store Account & its encrypted Password
			IFileManager::Get().Delete(*(NormalizedPath / AccountString + TEXT(".rpguser")));
			FFileHelper::SaveArrayToFile(PasswdBuff, *(NormalizedPath / AccountString + TEXT(".rpguser")));

			return true;
		}
	}

	return false;
}


bool UUI_Login::DecryptFromLocal(const FString& InPath)
{
	// Fix Path
	FString NormalizedInPath = InPath;
	FPaths::NormalizeFilename(NormalizedInPath); // `\\`->`/`
	NormalizedInPath.RemoveFromEnd(TEXT("/"));

	// Get all files in path
	TArray<FString> Filenames;
	IFileManager::Get().FindFilesRecursive(Filenames, *InPath, TEXT("*.*"), true, false);

	// Read content in files
	for (auto& Filename : Filenames)
	{
		FString CleanFilename = FPaths::GetCleanFilename(Filename);
		// Check file extention
		if (CleanFilename.Contains(TEXT(".rpguser")))
		{
			// Get Encrypted Password
			TArray<uint8> PasswdBuffer;
			FFileHelper::LoadFileToArray(PasswdBuffer, *Filename);

			// Get Account
			CleanFilename.RemoveFromEnd(TEXT(".rpguser"));

			// Decrypt Password
			FString AccountHash = FMD5::HashAnsiString(*CleanFilename);
			for (int32 i = 0; i < 32; i++)
			{
				AccountHash = FMD5::HashAnsiString(*AccountHash);
			}

			if (!AccountHash.IsEmpty())
			{
				FSimpleIOStream Stream(PasswdBuffer);

				// Set Account Hash as AES Key
				ANSICHAR* Key = TCHAR_TO_UTF8(*AccountHash);

				// Decrypt encrypted Password 
				FAES::DecryptData(PasswdBuffer.GetData(), PasswdBuffer.Num(), Key);

				FString PasswordString;
				Stream >> PasswordString;

				// set storaged Account & Password to UI
				Account->SetText(FText::FromString(CleanFilename));
				Password->SetText(FText::FromString(PasswordString));

				return true;
			}
		}
	}

	return false;
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
