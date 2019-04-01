// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "NPCs/Characters/PoliceChar.h"
#include "Kismet/KismetMathLibrary.h"
#include "PoliceAI.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;

/**
 * 
 */
UCLASS()
class RAID_API APoliceAI : public AAIController
{
	GENERATED_UCLASS_BODY()

private:
	UPROPERTY(transient)
		UBlackboardComponent* BlackboardComp;

	/* Cached BT component */
	UPROPERTY(transient)
		UBehaviorTreeComponent* BehaviorComp;

	APoliceChar* ControlledNpc;

protected:

	//Blackboard Keys
	int32 SelfActor;
	int32 Enemy;
	int32 CanSeePlayer;
	int32 LastSeenLocation;
	int32 SearchLocation;


public:

	virtual void Possess(class APawn *InPawn) override;

	UObject * GetSelf();

	/** Returns BlackboardComp subobject **/
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	/** Returns BehaviorComp subobject **/
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComp; }
	
	
	
	
};
