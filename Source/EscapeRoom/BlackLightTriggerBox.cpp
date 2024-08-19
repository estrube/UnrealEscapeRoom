// Fill out your copyright notice in the Description page of Project Settings.

#include "BlackLightTriggerBox.h"

ABlackLightTriggerBox::ABlackLightTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &ABlackLightTriggerBox::OverPoster);
	OnActorEndOverlap.AddDynamic(this, &ABlackLightTriggerBox::LeftPoster);
}

void ABlackLightTriggerBox::BeginPlay()
{
	Super::BeginPlay();
}

void ABlackLightTriggerBox::OverPoster(class AActor* overlappedActor, class AActor* otherActor)
{
	if (otherActor && otherActor != this)
	{
		APoster* const tempPost = Cast<APoster>(otherActor);
		if (tempPost)
		{
			ACharacter_Controller* character = Cast<ACharacter_Controller>(GetWorld()->GetFirstPlayerController()->GetCharacter());
			if (character)
			{
				if (character->blackTriggerBox)
				{
					tempPost->SetActorHiddenInGame(true);
				}
			}
		}
	}
}

void ABlackLightTriggerBox::LeftPoster(class AActor* overlappedActor, class AActor* otherActor)
{
	if (otherActor && otherActor != this)
	{
		APoster* const tempPost = Cast<APoster>(otherActor);
		if (tempPost)
		{
			ACharacter_Controller* character = Cast<ACharacter_Controller>(GetWorld()->GetFirstPlayerController()->GetCharacter());
			if (character)
			{
				if (character->blackTriggerBox)
				{
					tempPost->SetActorHiddenInGame(false);
				}
			}
		}
	}
}

