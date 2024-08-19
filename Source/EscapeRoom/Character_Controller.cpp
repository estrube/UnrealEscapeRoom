// Fill out your copyright notice in the Description page of Project Settings.

#include "Character_Controller.h"


// Sets default values
ACharacter_Controller::ACharacter_Controller()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	inventoryI = 0;
	//change to 4
	empty.itemId = "4";

	collectionRange = CreateDefaultSubobject<USphereComponent>(TEXT("collectionRange"));
	collectionRange->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
	collectionRange->SetSphereRadius(100.0f);

}

// Called when the game starts or when spawned
void ACharacter_Controller::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < wieldObjects.Num(); i++)
	{
		if (wieldObjects[i])
		{
			wieldObjects[i]->SetActorHiddenInGame(true);
		}
	}
	
	for (int i = 0; i < 3; i++)
	{
		statueAnswers.Add(false);
	}
}

// Called every frame
void ACharacter_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacter_Controller::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveX", this, &ACharacter_Controller::Vertical_Movement);
	InputComponent->BindAxis("MoveY", this, &ACharacter_Controller::Horizontal_Movement);

	InputComponent->BindAxis("CameraSide", this, &ACharacter_Controller::AddControllerYawInput);
	InputComponent->BindAxis("CameraUp", this, &ACharacter_Controller::AddControllerPitchInput);

	InputComponent->BindAction("Interaction", IE_Pressed, this, &ACharacter_Controller::Collect);
	InputComponent->BindAction("Ray", IE_Pressed, this, &ACharacter_Controller::RayCast);
	InputComponent->BindAction("InventoryPlus", IE_Pressed, this, &ACharacter_Controller::InventoryPlus);
	InputComponent->BindAction("InventoryMinus", IE_Pressed, this, &ACharacter_Controller::InventoryMinus);
}

void ACharacter_Controller::Horizontal_Movement(float axis)
{
	if (axis)
	{
		AddMovementInput(GetActorRightVector(), axis);
	}
}

void ACharacter_Controller::Vertical_Movement(float axis)
{
	if (axis)
	{
		AddMovementInput(GetActorForwardVector(), axis);
	}
}

void ACharacter_Controller::Collect()
{
	TArray<AActor*> collectedItems;
	collectionRange->GetOverlappingActors(collectedItems);

	for (int i = 0; i < collectedItems.Num(); i++)
	{
		AItem* const testItem = Cast<AItem>(collectedItems[i]);
		if (testItem && !testItem->IsPendingKill() && testItem->GetActive())
		{
			testItem->Touched();
			AddToInventory(testItem->itemID);
			testItem->SetActive(false);
		}
	}
}

void ACharacter_Controller::InventoryPlus()
{
	inventoryI += 1;
	if (inventoryI >= 5)
	{
		inventoryI = 0;
	}
	Wielding();
}

void ACharacter_Controller::InventoryMinus()
{
	inventoryI -= 1;
	if (inventoryI < 0)
	{
		inventoryI = 4;
	}
	Wielding();
}

void ACharacter_Controller::AddToInventory(FName id)
{
	AEscapeRoomGameModeBase* gameMode = Cast<AEscapeRoomGameModeBase>(GetWorld()->GetAuthGameMode());
	UDataTable* itemTable = gameMode->GetItemsDB();

	if (gameMode)
	{
		if (itemTable)
		{
			FInventoryItem* itemAdded = itemTable->FindRow<FInventoryItem>(id, "");
			if (itemAdded)
			{
				inventory.Add(*itemAdded);
				Wielding();
				justPickedUp = true;
			}
		}
	}
}

void ACharacter_Controller::RemoveFromInventory()
{
	if (inventory.Num() > inventoryI)
	{
		inventory.RemoveAt(inventoryI);
		Wielding();
	}
}

void ACharacter_Controller::Wielding()
{
	blackTriggerBox = false;
	if (inventory.Num() > inventoryI)
	{
		wield = inventory[inventoryI];
		if (&wield)
		{
			FString wieldValue = wield.itemId.ToString();
			int wieldI = FCString::Atoi(*wieldValue);
			for (int i = 0; i < pickupableObjects.Num(); i++)
			{
				if (wield.itemId == pickupableObjects[i].itemId)
				{
					//get rid of minus 1
					if (wieldObjects[wieldI])
					{
						if (wieldI == 0)
						{
							blackTriggerBox = true;
						}
						wieldObjects[wieldI]->SetActorHiddenInGame(false);
					}
				}
				else
				{
					if (wieldObjects[i])
					{
						wieldObjects[i]->SetActorHiddenInGame(true);
					}
				}
			}
		}
	}
	else
	{
		wield = empty;
	}

	if (wield == empty)
	{
		for (int i = 0; i < pickupableObjects.Num(); i++)
		{
			wieldObjects[i]->SetActorHiddenInGame(true);
		}
	}
	
}


bool ACharacter_Controller::GetPickedUp()
{
	return justPickedUp;
}

bool ACharacter_Controller::GetRemoved()
{
	return justRemoved;
}

void ACharacter_Controller::CheckAnswer()
{
	if (statueAnswers[0] && statueAnswers[1] && statueAnswers[2])
	{
		ADoorRotator* tempDoor = Cast<ADoorRotator>(animDoor);
		if (tempDoor)
		{
			tempDoor->CallAnimation();
		}
	}
}

void ACharacter_Controller::RayCast()
{
	FHitResult* hit = new FHitResult();
	FVector forward = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorForwardVector();
	FVector start = GetActorLocation();
	start.Z = 300.f;
	FVector end = (forward * 1000.f) + start;
	FCollisionQueryParams* col = new FCollisionQueryParams();
	col->AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(*hit, start, end, ECC_WorldStatic, *col))
	{
		DrawDebugLine(GetWorld(), start, end, FColor::Orange, true);
		if (hit->GetActor() != NULL)
		{
			UE_LOG(LogClass, Log, TEXT("Component: %s"), *hit->GetComponent()->GetName());
			if (*hit->GetComponent()->GetName() == FString("1"))
			{
				inputtedCode.Add(1);
			}
			else if (*hit->GetComponent()->GetName() == FString("2"))
			{
				inputtedCode.Add(2);
			}
			else if (*hit->GetComponent()->GetName() == FString("3"))
			{
				inputtedCode.Add(3);
			}

			if (inputtedCode.Num() == 3)
			{
				bool correct = false;
				for (int i = 0; i < inputtedCode.Num(); i++)
				{
					if (inputtedCode[i] == i + 1)
					{
						correct = true;
						UE_LOG(LogClass, Log, TEXT("Correct"));
					}
					else
					{
						correct = false;
						UE_LOG(LogClass, Log, TEXT("Incorrect"));
						break;
					}
				}

				inputtedCode.Empty();

				if (correct)
				{
					UE_LOG(LogClass, Log, TEXT("Open"));
					ADoorRotator* tempDoor = Cast<ADoorRotator>(finalAnimDoor);
					if (tempDoor)
					{
						tempDoor->CallAnimation();
					}
				}
			}
		}
	}
}