// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrollingGuard.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// Get the patrol points
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* Pawn = AIController->GetPawn();
	APatrollingGuard* Guard = Cast<APatrollingGuard>(Pawn);
	TArray<AActor*> Points = Guard->PatorlPointsCPP;

	// Set next waypoint
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackboardComponent->GetValueAsInt(IndexKey.SelectedKeyName);
	// UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), Index);
	BlackboardComponent->SetValueAsObject(WaypointKey.SelectedKeyName, Points[Index]);

	int32 NextIndex = (Index + 1) % Points.Num();
	BlackboardComponent->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}
