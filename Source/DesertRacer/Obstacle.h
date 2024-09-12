// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"

#include "Sound/SoundBase.h"

#include "MyGameMode.h"

#include "Obstacle.generated.h"

UCLASS()
class DESERTRACER_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:
    UPROPERTY(VisibleAnywhere, BluePrintReadWrite)
    UCapsuleComponent* CapsuleComp;
    
    UPROPERTY(VisibleAnywhere, BluePrintReadWrite)
    UPaperSpriteComponent* ObstacleSprite;
    
    UPROPERTY(EditAnywhere, BluePrintReadWrite)
    USoundBase* HitSound;
    
    UPROPERTY(EditAnywhere, BluePrintReadWrite)
    bool IsFinishLine = false;
    
    AMyGameMode* MyGameMode;
    
	AObstacle();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
    
    UFUNCTION()
    void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSewwp, const FHitResult& SweepResult);

};
