// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "MGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MGD_TEMPLATE_API UMGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	
	UFUNCTION(BlueprintCallable, category = Login)
	void LoginToEOS();


protected:
	UFUNCTION(BlueprintCallable, category = Login)
	void BIEOnLoginComplete(bool sucess, FString error);

	// the login function that will run when the onlogincomplete delgate is run
	void OnLoginComplete(int32 localUserNum, bool bWashSuccessful, const FUniqueNetId& userId, const FString& Error);
	//this will store a reference to the online subsystem
	const IOnlineSubsystem* OssRef;

// this will stor e a reference to the identity inetrface in the online sybsystem
	IOnlineIdentityPtr IdentityInterface;
};
	