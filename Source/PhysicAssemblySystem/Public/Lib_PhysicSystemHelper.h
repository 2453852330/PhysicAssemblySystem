// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ConnectPointComponent.h"
#include "PhysicDataType.h"
#include "Lib_PhysicSystemHelper.generated.h"


/**
 * 
 */
UCLASS()
class PHYSICASSEMBLYSYSTEM_API ULib_PhysicSystemHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** 寻找最短连接路径 */
	UFUNCTION(BlueprintCallable)
	static bool Lib_FindBestConnectPath(const TArray<FHitResult> & HitResults,const TArray<UConnectPointComponent*> & ConnectList,FConnectPath & BestPath);

	/** 更新连接模型的Tag */
	UFUNCTION(BlueprintCallable)
	static void Lib_UpdateTagWhenConnect(AActor * ConnectTo,AActor * ConnectFrom);

	/** 合并连接点数组 */
	UFUNCTION(BlueprintCallable,BlueprintPure)
	static TArray<UConnectPointComponent*> Lib_AppendConnectPointList(const TArray<UConnectPointComponent*> & A,const TArray<UConnectPointComponent*> & B);

	/** Reset Tag */
	UFUNCTION(BlueprintCallable)
	static void Lib_ResetTag(AActor * InActor,int32 ID);

	/** 从连接点列表中移除一个列表 */
	UFUNCTION(BlueprintCallable)
	static void Lib_RemoveListFromList(UPARAM(ref)  TArray<UConnectPointComponent*> & List ,const TArray<UConnectPointComponent*> & NeedRemoved);

	/** 寻找Actor的所有父类 */
	UFUNCTION(BlueprintCallable,BlueprintPure)
	static TArray<AActor*> Lib_FindAllAttachedParent(AActor * InActor);

	/** 检测加入 */
	UFUNCTION(BlueprintCallable)
	static void Lib_AppendTo(UPARAM(ref)  TArray<UConnectPointComponent*> & List , const TArray<UConnectPointComponent *> & NeedAdded);

	/** 寻找最顶层Actor */
	UFUNCTION(BlueprintCallable,BlueprintPure)
	static AActor * Lib_FindTopActor(AActor * InActor);

	/** 寻找所有子级Actor */
	UFUNCTION(BlueprintCallable,BlueprintPure)
	static TArray<AActor*> Lib_GetAllChildActor(AActor * InTopActor);


	UFUNCTION(BlueprintCallable,BlueprintPure)
	static FString Lib_GetActorLabel(AActor * InActor);


	UFUNCTION(BlueprintCallable,BlueprintPure)
	static FLinearColor Lib_GetRandomLinearColor();


	UFUNCTION(BlueprintCallable,BlueprintPure,meta=(WorldContext=Obj))
	static int32 Lib_GeneratedUniqueID(UObject*Obj);
	
private:
	static void CF_GetChildActor(AActor * InActor,TArray<AActor*> & List);
	static bool CF_CheckIDValid(int32 ID,const TArray<AActor*> & List);
};
