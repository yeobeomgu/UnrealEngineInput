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
};
