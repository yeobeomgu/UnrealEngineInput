// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
//복잡한 수학 함수가 들어 있음.
#include "Kismet/KismetMathLibrary.h"



// Sets default valuesw
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//매번 캐릭터 설정하기 귀찮으니 C++에서 구현
	//GetCapsuleComponent()는 캡슐 높이의 반으로 변동이 생기면 캐릭터 위치도 바뀌 같이 넣어둠.
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		//캐릭터는 Yaw만 쓴다.
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
	//Cast<APlayerController>(GetController()); -> 용도에 맞게 위 아래중 하나 선택

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
	
	//방향을 잡아준다.
	//FVector MoveDirection(MoveVector.X, MoveVector.Y, 0);
	
	//절대 Rotation
	//Yaw 축을 잡아서 다른애들을 무시한다.
	FRotator Rotation = GetControlRotation();
	FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);

	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(YawRotation);
	FVector RightVector = UKismetMathLibrary::GetRightVector(YawRotation);

	AddMovementInput(ForwardVector, MoveVector.Y);
	AddMovementInput(RightVector, MoveVector.X);


	
	//Normalize는 크기를 1로 바꿔줌. (AddMovementInput은 자체적으로 노멀라이즈를 해서 안써도 됨)
	//AddMovementInput(MoveDirection);

}

void AMyCharacter::Look(const FInputActionValue& Value)
{
	FVector2D CameraVector = Value.Get<FVector2D>();

	//마우스 위아래로 이동하기 위해 Y
	AddControllerPitchInput(CameraVector.Y);
	AddControllerYawInput(CameraVector.X);

}

void AMyCharacter::JumpUp(const FInputActionValue& Value)
{
	Jump();
	UE_LOG(LogTemp, Display, TEXT("Jump"));
}

