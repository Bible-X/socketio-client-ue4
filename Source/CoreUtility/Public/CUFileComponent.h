// Copyright 2018-current Getnamo. All Rights Reserved


#pragma once

#include "Components/ActorComponent.h"
#include "CUFileComponent.generated.h"

/**
* Convenience component to save/load data from files
*/
UCLASS(ClassGroup = "Utility", meta = (BlueprintSpawnableComponent, DeprecatedNode))
class COREUTILITY_API UCUFileComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()
public:

	/** Get the current project contents directory path*/
	UFUNCTION(BlueprintPure, Category = FileUtility, meta=(DeprecatedFunction))
	FString ProjectContentsDirectory();

	/** Get the current project directory path*/
	UFUNCTION(BlueprintPure, Category = FileUtility, meta=(DeprecatedFunction))
	FString ProjectDirectory();

	/** Get the current project saved directory path*/
	UFUNCTION(BlueprintPure, Category = FileUtility, meta=(DeprecatedFunction))
	FString ProjectSavedDirectory();

	/** External storage in android context, otherwise uses project saved directory*/
	UFUNCTION(BlueprintPure, Category = FileUtility, meta=(DeprecatedFunction))
	FString ExternalSaveDirectory();

	UFUNCTION(BlueprintPure, Category = FileUtility, meta=(DeprecatedFunction))
	void SplitFullPath(const FString& InFullPath, FString& OutDirectory, FString& OutFileName);

	UFUNCTION(BlueprintPure, Category = FileUtility, meta=(DeprecatedFunction))
	void ProjectRelativePath(const FString& InFullPath, FString& OutProjectRelativePath);

	/** Save array of bytes to file at specified directory */
	UFUNCTION(BlueprintCallable, Category = FileUtility, meta=(DeprecatedFunction))
	bool SaveBytesToFile(const TArray<uint8>& Bytes, const FString& Directory, const FString& FileName, bool bLogSave = false);

	/** Read array of bytes from file at specified directory */
	UFUNCTION(BlueprintCallable, Category = FileUtility, meta=(DeprecatedFunction))
	bool ReadBytesFromFile(const FString& Directory, const FString& FileName, TArray<uint8>& OutBytes);
};