// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// TODO protect against no points

	// Get the patrol points
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	UPatrolRoute* Route = Pawn->FindComponentByClass<UPatrolRoute>();

	if (!ensure(Route)) { return EBTNodeResult::Failed; }

	// Set next waypoint
	TArray<AActor*> Points = Route->GetPatorlPoints();

	if (Points.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Guard '%s' Has No Patrol Points"), *Pawn->GetName());
		return EBTNodeResult::Failed;
	}


	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackboardComponent->GetValueAsInt(IndexKey.SelectedKeyName);
	// UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), Index);
	BlackboardComponent->SetValueAsObject(WaypointKey.SelectedKeyName, Points[Index]);

	int32 NextIndex = (Index + 1) % Points.Num();
	BlackboardComponent->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}
