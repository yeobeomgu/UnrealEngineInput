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

		//자동으로 회전값 적용 CalculateDirection
		Direction = CalculateDirection (Pawn->GetCharacterMovement()->Velocity, Pawn->GetActorRotation());

		//IsCrouching (앉은 상태)
		//IsCrouched 앉을 수 있는가;
		
		bIsCrouch = Pawn->bIsCrouched;
	}
}