// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
//������ ���� �Լ��� ��� ����.
#include "Kismet/KismetMathLibrary.h"



// Sets default valuesw
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//�Ź� ĳ���� �����ϱ� �������� C++���� ����
	//GetCapsuleComponent()�� ĸ�� ������ ������ ������ ����� ĳ���� ��ġ�� �ٲ� ���� �־��.
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		//ĳ���ʹ� Yaw�� ����.
		FRotator(0, 90.0f, 0)
	);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);



}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	//Cast<APlayerController>(GetController()); -> �뵵�� �°� �� �Ʒ��� �ϳ� ����

	UEnhancedInputLocalPlayerSubsystem* LocalPlayerSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	if (LocalPlayerSystem && DefaultMappingContext)
	{
		LocalPlayerSystem->AddMappingContext(DefaultMappingContext, 0);
	}
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
		EnhancedInputComponent->BindAction(IA_MoveForwardAndRight, ETriggerEvent::Triggered, this, &AMyCharacter::MoveForwardAndRight);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AMyCharacter::JumpUp);


	}


}

void AMyCharacter::MoveForwardAndRight(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();
	
	//������ ����ش�.
	//FVector MoveDirection(MoveVector.X, MoveVector.Y, 0);
	
	//���� Rotation
	//Yaw ���� ��Ƽ� �ٸ��ֵ��� �����Ѵ�.
	FRotator Rotation = GetControlRotation();
	FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);

	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(YawRotation);
	FVector RightVector = UKismetMathLibrary::GetRightVector(YawRotation);

	AddMovementInput(ForwardVector, MoveVector.Y);
	AddMovementInput(RightVector, MoveVector.X);


	
	//Normalize�� ũ�⸦ 1�� �ٲ���. (AddMovementInput�� ��ü������ ��ֶ���� �ؼ� �Ƚᵵ ��)
	//AddMovementInput(MoveDirection);

}

void AMyCharacter::Look(const FInputActionValue& Value)
{
	FVector2D CameraVector = Value.Get<FVector2D>();

	//���콺 ���Ʒ��� �̵��ϱ� ���� Y
	AddControllerPitchInput(CameraVector.Y);
	AddControllerYawInput(CameraVector.X);

}

void AMyCharacter::JumpUp(const FInputActionValue& Value)
{
	Jump();
	UE_LOG(LogTemp, Display, TEXT("Jump"));
}

