// Fill out your copyright notice in the Description page of Project Settings.

#include "StatueTriggerBox.h"

AStatueTriggerBox::AStatueTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &AStatueTriggerBox::PlaceIntoBox);
}

void AStatueTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < statues.Num(); i++)
	{
		AItem* const testItem = Cast<AItem>(statues[i]);
		if (testItem)
		{
			testItem->SetActive(false);
		}
		statues[i]->SetActorHiddenInGame(true);
	}
}

void AStatueTriggerBox::SetRemovedFalse()
{
	ACharacter_Controller* character = Cast<ACharacter_Controller>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (character)
	{
		character->justRemoved = false;
	}
}

void AStatueTriggerBox::PlaceIntoBox(class AActor* overlappedActor, class AActor* otherActor)
{
	if (otherActor && otherActor != this)
	{
		for (int i = 0; i < statues.Num(); i++)
		{
			AItem* const testItem = Cast<AItem>(statues[i]);
			if (testItem)
			{
				if (testItem->GetActive())
				{
					present = true;
					break;
				}
				else
				{
					present = false;
				}
			}
		}
		if (!present)
		{
			AItem* const tempItem = Cast<AItem>(otherActor);
			if (tempItem)
			{
				ACharacter_Controller* character = Cast<ACharacter_Controller>(GetWorld()->GetFirstPlayerController()->GetCharacter());
				if (character)
				{
					if (tempItem->name == "Blue Statue" && character->wield.itemId == "1")
					{
						character->justRemoved = true;
						character->RemoveFromInventory();
						GetWorld()->GetTimerManager().SetTimer(removedTimerHandle, this, &AStatueTriggerBox::SetRemovedFalse, 0.01f, false);
						if (statues[0])
						{
							statues[0]->SetActorHiddenInGame(false);
							AItem* const trueItem = Cast<AItem>(statues[0]);
							if (trueItem)
							{
								trueItem->SetActive(true);
							}
						}
						if (answer == 1)
						{
							character->statueAnswers[0] = true;
						}
						else
						{
							character->statueAnswers[0] = false;
						}
					}
					else if (tempItem->name == "Red Statue" && character->wield.itemId == "3")
					{
						character->justRemoved = true;
						character->RemoveFromInventory();
						GetWorld()->GetTimerManager().SetTimer(removedTimerHandle, this, &AStatueTriggerBox::SetRemovedFalse, 0.01f, false);
						if (statues[1])
						{
							statues[1]->SetActorHiddenInGame(false);
							AItem* const trueItem = Cast<AItem>(statues[1]);
							if (trueItem)
							{
								trueItem->SetActive(true);
							}
						}
						if (answer == 2)
						{
							character->statueAnswers[1] = true;
						}
						else
						{
							character->statueAnswers[1] = false;
						}
					}
					else if(tempItem->name == "Green Statue" && character->wield.itemId == "2")
					{
						character->justRemoved = true;
						character->RemoveFromInventory();
						GetWorld()->GetTimerManager().SetTimer(removedTimerHandle, this, &AStatueTriggerBox::SetRemovedFalse, 0.01f, false);
						if (statues[2])
						{
							statues[2]->SetActorHiddenInGame(false);
							AItem* const trueItem = Cast<AItem>(statues[2]);
							if (trueItem)
							{
								trueItem->SetActive(true);
							}
						}
						if (answer == 3)
						{
							character->statueAnswers[2] = true;
						}
						else
						{
							character->statueAnswers[2] = false;
						}
					}
					character->CheckAnswer();
				}
			}
		}
	}
}

