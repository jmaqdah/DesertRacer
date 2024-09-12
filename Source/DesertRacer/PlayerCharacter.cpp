// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

APlayerCharacter::APlayerCharacter()
{
    
	PrimaryActorTick.bCanEverTick = true;
    
    CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
    // Set RootComponent (built-in Unreal variable) to CapsuleComp
    SetRootComponent(CapsuleComp);
    
    // The whole point of a spring arm to to be able to attach a spring arm to it
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    
    CarSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CarSprite"));
    CarSprite->SetupAttachment(RootComponent);
    
    

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
    
    // We need to register the input mapping context
    APlayerController* PlayerController = Cast<APlayerController>(Controller);
    if (PlayerController)
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
        if (Subsystem)
        {
            Subsystem->AddMappingContext(InputMappingContext, 0);
        }
    }
	
}


void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    // Get enhanced input component
    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (EnhancedInputComponent)
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
    }

}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MoveActionValue = Value.Get<FVector2D>();
    //GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::White, MoveActionValue.ToString());
    
    if (CanMove)
    {
        if (abs(MoveActionValue.Y) > 0.0f)
        {
            float DeltaTime = GetWorld()->DeltaTimeSeconds;
            
            if (abs(MoveActionValue.X) > 0.0f)
            {
                float RotationAmount = -RotationSpeed * MoveActionValue.X * DeltaTime;
                AddActorWorldRotation(FRotator(RotationAmount, 0.0f, 0.0f));
            }
            
            float FinalMovementSpeed = MovementSpeed;
            
            if (MoveActionValue.Y < 0.0f) FinalMovementSpeed *= 0.5;
            
            FVector CurrentLocation = GetActorLocation();
            FVector DistanceToMove = GetActorUpVector() * FinalMovementSpeed * MoveActionValue.Y * DeltaTime;
            
            FVector NewLocation = CurrentLocation + DistanceToMove;
            SetActorLocation(NewLocation);
        }
    }
}

