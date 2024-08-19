// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "DoorRotator.generated.h"

UCLASS()
class ESCAPEROOM_API ADoorRotator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorRotator();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, Category = "Animation")
		UCurveFloat* animation;

	UPROPERTY(EditAnywhere, Category = "Animation")
		float angle = 115;

	FTimeline timeline;

	UFUNCTION(BlueprintCallable)
		void CallAnimation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	FRotator initialRot;
	FRotator targetRot;

	UFUNCTION()
		void UpdateRotation(float value);
	
};
