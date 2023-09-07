// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* MyPawn = TryGetPawnOwner();
	//dynamic_cast로 해야하는데 언리얼에서는 Cast로 제공.
	ACharacter * MyCharacter = Cast<ACharacter>(MyPawn);
	if (MyCharacter)
	{
		//뛰는데 위아래는 필요 없으니 2D, SizeSquared2D는 루트를 빼는것.  루트가 많이느리다.
		Speed = MyCharacter->GetCharacterMovement()->Velocity.SizeSquared2D();
	}
}