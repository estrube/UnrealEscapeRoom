// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Engine/DataTable.h"
#include "Engine/World.h"
#include "EscapeRoomGameModeBase.h"
#include "DoorRotator.h"
#include "Item.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Character_Controller.generated.h"


USTRUCT(BlueprintType)
struct FInventoryItem : public FTableRowBase
{
	GENERATED_BODY()

public:

	FInventoryItem()
	{
		name = FText::FromString("item");
		isVisible = false;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName itemId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AItem> item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isVisible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* image;

	bool operator==(const FInventoryItem& item) const
	{
		if (itemId == item.itemId)
			return true;
		else return false;
	}
};

UCLASS()
class ESCAPEROOM_API ACharacter_Controller : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_Controller();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Items")
		void Collect();

	UFUNCTION()
		void InventoryPlus();

	UFUNCTION()
		void InventoryMinus();

private:

	void RayCast();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Horizontal_Movement(float axis);
	
	void Vertical_Movement(float axis);

	UPROPERTY(EditAnywhere, Category = "Animation")
		AActor* animDoor;

	UPROPERTY(EditAnywhere, Category = "Animation")
		AActor* finalAnimDoor;

	UPROPERTY()
		TArray<int> inputtedCode;

	UFUNCTION(BlueprintCallable, Category = "Utilities")
		void AddToInventory(FName id);

	UFUNCTION(BlueprintCallable, Category = "Utilities")
		void RemoveFromInventory();

	UFUNCTION()
		void Wielding();

	UFUNCTION(BlueprintCallable)
		bool GetPickedUp();

	UFUNCTION(BlueprintCallable)
		bool GetRemoved();

	UFUNCTION()
		void CheckAnswer();

	UPROPERTY(EditAnywhere)
		TArray<bool> statueAnswers;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FInventoryItem> inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int inventoryI;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* collectionRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FInventoryItem wield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FInventoryItem empty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FInventoryItem> pickupableObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wielding Items")
		TArray<AActor*> wieldObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool justPickedUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool justRemoved;

	UPROPERTY(EditAnywhere)
		bool blackTriggerBox;

	FORCEINLINE class USphereComponent* GetCollectionRange() const { return collectionRange; }
	
};
