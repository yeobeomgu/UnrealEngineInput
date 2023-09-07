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
	
	// �ִԺ������Ʈ���� ����ϱ� ���� ���� ����.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float Direction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float AimYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float AimPitch;

	//8��Ʈ�� 1����Ʈ�� �����ؼ� ����.
	//��Ʈ�������� 1��Ʈ�� ���ڴ�. (bool�� �߰Եȴ�.)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	uint32 bIsCrouch:1;

};
