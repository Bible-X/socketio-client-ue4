// Copyright 2018-current Getnamo. All Rights Reserved


#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Async/Future.h"
#include "Engine/Classes/Sound/SoundWaveProcedural.h"
#include "CUBlueprintLibrary.generated.h"

/** Wrapper for EImageFormat::Type for BP */
UENUM()
enum class EImageFormatBPType : uint8
{
	/** Invalid or unrecognized format. */
	Invalid = 254,

	/** Portable Network Graphics. */
	PNG = 0,

	/** Joint Photographic Experts Group. */
	JPEG,

	/** Single channel JPEG. */
	GrayscaleJPEG,

	/** Windows Bitmap. */
	BMP,

	/** Windows Icon resource. */
	ICO,

	/** OpenEXR (HDR) image file format. */
	EXR,

	/** Mac icon. */
	ICNS
};

/** Callback threading option */
UENUM(BlueprintType)
enum ESIOCallbackType
{
	CALLBACK_GAME_THREAD,
	CALLBACK_BACKGROUND_THREADPOOL,
	CALLBACK_BACKGROUND_TASKGRAPH
};

/**
 * Useful generic blueprint functions, mostly conversion
 */
UCLASS()
class COREUTILITY_API UCUBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	//Conversion Nodes

	/**
	*	Convert any unicode bytes to string
	*/
	UFUNCTION()
	static FString Conv_BytesToString(const TArray<uint8>& InBytes);

	/**
	*	Convert string to UTF8 bytes
	*/
	UFUNCTION()
	static TArray<uint8> Conv_StringToBytes(FString InString);

	/**
	*	Convert bytes to UTexture2D using auto-detection - optimized, but can still have performance implication
	*/
	UFUNCTION()
	static UTexture2D* Conv_BytesToTexture(const TArray<uint8>& InBytes);

	/**
	*	Audio decompression - Convert opus (currently raw serialized) to wav
	*/
	UFUNCTION()
	static TArray<uint8> Conv_OpusBytesToWav(const TArray<uint8>& InBytes);

	/**
	*	Audio compression - Convert wav to opus (currently raw serialized)
	*/
	UFUNCTION()
	static TArray<uint8> Conv_WavBytesToOpus(const TArray<uint8>& InBytes);

	/**
	*	Assumes .wav chunks - handles async alloc, callable from any thread
	*/
	UFUNCTION()
	static USoundWave* Conv_WavBytesToSoundWave(const TArray<uint8>& InBytes);

	/**
	*	convert a soundwave into wav bytes
	*/
	UFUNCTION()
	static TArray<uint8> Conv_SoundWaveToWavBytes(USoundWave* SoundWave);


	/** 
	* Compact Transform bytes are [[pitch,yaw,roll,x,y,z,sx,sy,sz],...]
	*/
	UFUNCTION()
	static void Conv_CompactBytesToTransforms(const TArray<uint8>& InCompactBytes, TArray<FTransform>& OutTransforms);

	/** 
	* Compact Position bytes are [[x,y,z],...]
	*/
	UFUNCTION()
	static void Conv_CompactPositionBytesToTransforms(const TArray<uint8>& InCompactBytes, TArray<FTransform>& OutTransforms);

	/**
	*	Sets and updates soundwave if needed from incoming bytes. Callable on background threads
	*/
	UFUNCTION()
	static void SetSoundWaveFromWavBytes(USoundWaveProcedural* InSoundWave, const TArray<uint8>& InBytes);

	/**
	*	Fully Async texture conversion from bytes will auto-detect format, depends on TFuture, cannot be called in blueprint. Latent graph callback may be used
	*/
	static TFuture<UTexture2D*> Conv_BytesToTexture_Async(const TArray<uint8>& InBytes);

	/**
	*	Convert UTexture2D to bytes in given format - can have performance implication
	*/
	UFUNCTION()
	static bool Conv_TextureToBytes(UTexture2D* Texture, TArray<uint8>& OutBuffer, EImageFormatBPType Format = EImageFormatBPType::PNG);

	/**
	*	Current UTC time in string format
	*/
	UFUNCTION()
	static FString NowUTCString();

	/**
	* Returns a type of Unique Hardware ID
	*/
	UFUNCTION()
	static FString GetLoginId();

	/** 
	* Return a somewhat unique int for given string
	*/
	UFUNCTION()
	static int32 ToHashCode(const FString& String);

	/**
	* Time inter-tick durations for simple
	*/
	UFUNCTION()
	static void MeasureTimerStart(const FString& Category = TEXT("TimeTaken"));

	/** 
	* Stops the timer started for this category and returns the duration taken in milliseconds 
	*/
	UFUNCTION()
	static float MeasureTimerStop(const FString& Category = TEXT("TimeTaken"), bool bShouldLogResult = true);

	/** 
	*	Calls function by name given calling context on thread specified. Use e.g. delay (0) to return to game thread
	*	or use game thread callback for threadtype. This allows you to run certain functions on a background thread or
	*	taskgraph in blueprints. Keep in mind that you should not create or destroy UObjects non-game threads.
	*/
	UFUNCTION()
	static void CallFunctionOnThread(const FString& Function, ESIOCallbackType ThreadType, UObject* WorldContextObject = nullptr);

	/**
	*	Calls specified function on thread type with a latent graph return. This allows you to run certain functions on a background thread or
	*	taskgraph in blueprints. Keep in mind that you should not create or destroy UObjects non-game threads.
	*/
	UFUNCTION()
	static void CallFunctionOnThreadGraphReturn(const FString& Function, ESIOCallbackType ThreadType, struct FLatentActionInfo LatentInfo, UObject* WorldContextObject = nullptr);
};
