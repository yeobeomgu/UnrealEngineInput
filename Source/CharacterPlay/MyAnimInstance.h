// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERPLAY_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	// 애님블루프린트에서 사용하기 위해 변수 생성.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float Direction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float AimYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float AimPitch;

	//8비트를 1바이트로 압축해서 보냄.
	//인트형이지만 1비트로 쓰겠다. (bool로 뜨게된다.)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	uint32 bIsCrouch:1;

};
