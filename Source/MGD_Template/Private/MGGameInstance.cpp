// Fill out your copyright notice in the Description page of Project Settings.


#include "MGGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
void UMGGameInstance::Init()
{
	Super::Init();
	
//store the online subsytem
	OssRef = Online::GetSubsystem(GetWorld());
	
//check if it was found and eorror if not
	if (!OssRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Online Subsystem not found"))
		return;
	}

	IdentityInterface = OssRef->GetIdentityInterface();

	if (!IdentityInterface)
	{
		UE_LOG(LogTemp, Error, TEXT("Identity Interface not found"))
		return;
	}

	//bind to the login complete delegate int he identity interface
	IdentityInterface->OnLoginChangedDelegates.AddUObject(this, &UMGGameInstance::OnLoginComplete);
}

void UMGGameInstance::LoginToEOS()
{
	if (!IdentityInterface)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot Login Identity Interface not found"))
		return;
	}

	FOnlineAccountCredentials creds;
	creds.Type = TEXT("accountportal");

	
	if (!IdentityInterface->Login(0, creds))
	{
		UE_LOG(LogTemp, Error, TEXT("Login failed synchronously"))
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Attempting to login..."))

	
}

void UMGGameInstance::OnLoginComplete(int32 LocalUserNum, bool bWashSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	BIEOnLoginComplete(bWashSuccessful, Error);
}
