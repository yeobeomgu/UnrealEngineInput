// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMyCharacter* Pawn = Cast<AMyCharacter>(TryGetPawnOwner());
	if (Pawn)
	{
		Speed = Pawn->GetCharacterMovement()->Velocity.SizeSquared2D();

		//�ڵ����� ȸ���� ���� CalculateDirection
		Direction = CalculateDirection (Pawn->GetCharacterMovement()->Velocity, Pawn->GetActorRotation());

		//IsCrouching (���� ����)
		//IsCrouched ���� �� �ִ°�;
		
		bIsCrouch = Pawn->bIsCrouched;
	}
}