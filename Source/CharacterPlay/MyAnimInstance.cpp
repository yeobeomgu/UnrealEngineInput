// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* MyPawn = TryGetPawnOwner();
	//dynamic_cast�� �ؾ��ϴµ� �𸮾󿡼��� Cast�� ����.
	ACharacter * MyCharacter = Cast<ACharacter>(MyPawn);
	if (MyCharacter)
	{
		//�ٴµ� ���Ʒ��� �ʿ� ������ 2D, SizeSquared2D�� ��Ʈ�� ���°�.  ��Ʈ�� ���̴�����.
		Speed = MyCharacter->GetCharacterMovement()->Velocity.SizeSquared2D();
	}
}