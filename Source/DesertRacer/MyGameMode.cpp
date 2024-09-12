// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"

#include "Kismet/GameplayStatics.h"

void AMyGameMode::ResetMyLevel(bool IsWin)
{
    float ResetTime = LoseResetTime;
    
    if (IsWin) ResetTime = WinResetTime;
    
    // Set the timer. 1.0f --> inRate delay timer, ResetTimer --> inital delay
    GetWorldTimerManager().SetTimer(ResetGameTimer, this, &AMyGameMode::OnResetGameTimerTimeOut, 1.0f, false, ResetTime);
}

void AMyGameMode::OnResetGameTimerTimeOut()
{
    // Reset the game
    UGameplayStatics::OpenLevel(GetWorld(), FName("MainLevel"));
}

