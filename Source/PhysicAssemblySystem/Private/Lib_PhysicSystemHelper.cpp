// Fill out your copyright notice in the Description page of Project Settings.


#include "Lib_PhysicSystemHelper.h"
#include "EngineUtils.h"


bool ULib_PhysicSystemHelper::Lib_FindBestConnectPath(const TArray<FHitResult>& HitResults,
	const TArray<UConnectPointComponent*>& ConnectList, FConnectPath& BestPath)
{
	if (HitResults.Num() <= 0 || ConnectList.Num() <=0)
	{
		return false;
	}
	AActor* Owner = ConnectList[0]->GetOwner();
	if (!Owner)
	{
		return false;
	}
	const FName SelfTag = Owner->Tags[0];

	TArray<FConnectPath> PathList;
	
	for (const FHitResult & HitResult : HitResults)
	{
		if (HitResult.GetActor()->ActorHasTag(SelfTag))
		{
			continue;
		}
		UPrimitiveComponent * HitComponent = HitResult.GetComponent();
		
		for (UConnectPointComponent* List : ConnectList)
		{
			PathList.Emplace(HitComponent,List);
		} 
	}

	PathList.Sort([](const FConnectPath & A,const FConnectPath & B)->bool
	{
		return A.Dis < B.Dis;
	});

	if (PathList.Num())
	{
		BestPath = PathList[0];
		return true;
	}

	return false;
}

void ULib_PhysicSystemHelper::Lib_UpdateTagWhenConnect(AActor* ConnectTo, AActor* ConnectFrom)
{
	if (ConnectTo && ConnectFrom)
	{
		ConnectFrom->Tags.Reset();
		ConnectFrom->Tags.Append(ConnectTo->Tags);
	}
}

TArray<UConnectPointComponent*> ULib_PhysicSystemHelper::Lib_AppendConnectPointList(
	const TArray<UConnectPointComponent*>& A, const TArray<UConnectPointComponent*>& B)
{
	TArray<UConnectPointComponent*> Tmp;
	Tmp.Append(A);
	Tmp.Append(B);
	return Tmp;
}

void ULib_PhysicSystemHelper::Lib_ResetTag(AActor* InActor, int32 ID)
{
	if (InActor)
	{
		InActor->Tags.Reset();
		InActor->Tags.Add(*FString::FromInt(ID));
	}
}

void ULib_PhysicSystemHelper::Lib_RemoveListFromList(TArray<UConnectPointComponent*>& List,
	const TArray<UConnectPointComponent*>& NeedRemoved)
{
	for (UConnectPointComponent* Removed : NeedRemoved)
	{
		List.RemoveSwap(Removed);
	} 
}

TArray<AActor*> ULib_PhysicSystemHelper::Lib_FindAllAttachedParent(AActor* InActor)
{
	TArray<AActor*> List;
	if (!InActor)
	{
		return List;
	}

	AActor * FindParent = InActor->GetAttachParentActor();
	
	while (FindParent)
	{
		List.Add(FindParent);
		FindParent = FindParent->GetAttachParentActor();	
	}

	return List;
}

void ULib_PhysicSystemHelper::Lib_AppendTo(TArray<UConnectPointComponent*>& List,
	const TArray<UConnectPointComponent*>& NeedAdded)
{
	for (UConnectPointComponent* it : NeedAdded)
	{
		List.AddUnique(it);
	} 
}

AActor* ULib_PhysicSystemHelper::Lib_FindTopActor(AActor* InActor)
{
	if (!InActor)
	{
		return nullptr;
	}
	
	AActor* TopActor = InActor->GetAttachParentActor();
	AActor* TmpActor = TopActor;
	
	// no top , return self as top
	if (!TopActor)
	{
		return InActor;	
	}
	
	while (TmpActor)
	{
		TmpActor = TopActor->GetAttachParentActor();
		if (TmpActor)
		{
			TopActor = TmpActor;
		}
	}

	return TopActor;
}

TArray<AActor*> ULib_PhysicSystemHelper::Lib_GetAllChildActor(AActor* InTopActor)
{
	TArray<AActor*> Results;
	
	if (!InTopActor)
	{
		return Results;
	}
	
	// add self to list
	Results.Add(InTopActor);
	
	CF_GetChildActor(InTopActor,Results);
	
	return Results;
}

FString ULib_PhysicSystemHelper::Lib_GetActorLabel(AActor* InActor)
{
	if (!InActor)
	{
		return TEXT("");
	}
	FString Tmp = InActor->GetName();
#if WITH_EDITOR
	Tmp = InActor->GetActorLabel();
#endif
	return Tmp;
}

FLinearColor ULib_PhysicSystemHelper::Lib_GetRandomLinearColor()
{
	return FLinearColor::MakeRandomColor();
}

int32 ULib_PhysicSystemHelper::Lib_GeneratedUniqueID(UObject*Obj)
{
	if (!Obj)
	{
		return FMath::Rand();
	}

	UWorld * World = Obj->GetWorld();
	if (!World)
	{
		return FMath::Rand();
	}

	TArray<AActor*> FindActorList;

	for (TActorIterator<AActor> it(World); it;++it)
	{
		FindActorList.Emplace(*it);
	}

	int32 ID = FMath::Rand();
	while (!CF_CheckIDValid(ID,FindActorList))
	{
		ID = FMath::Rand();
	}
	return ID;
}

void ULib_PhysicSystemHelper::CF_GetChildActor(AActor * InActor,TArray<AActor*>& List)
{
	if (InActor)
	{
		TArray<AActor*>Tmp;
		InActor->GetAttachedActors(Tmp);
		
		for (AActor* it : Tmp)
		{
			List.AddUnique(it);
			CF_GetChildActor(it,List);
		} 
	}
}

bool ULib_PhysicSystemHelper::CF_CheckIDValid(int32 ID, const TArray<AActor*>& List)
{
	for (AActor* it : List)
	{
		if (it->Tags.Num())
		{
			if (ID == FCString::Atoi(*it->Tags[0].ToString()))
			{
				return false;
			}
		}
	}
	return true;
}
