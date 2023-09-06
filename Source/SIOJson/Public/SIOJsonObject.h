// Modifications Copyright 2018-current Getnamo. All Rights Reserved


// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
// Copyright 2014 Vladimir Alyamkin. All Rights Reserved.

#pragma once

#include "Runtime/Json/Public/Dom/JsonObject.h"
#include "SIOJsonObject.generated.h"

class USIOJsonValue;

/**
 * Blueprintable FJsonObject wrapper
 */
UCLASS(BlueprintType, Blueprintable)
class SIOJSON_API USIOJsonObject : public UObject
{
	GENERATED_UCLASS_BODY()

	/** Create new Json object, cannot be pure  */
	UFUNCTION()
	static USIOJsonObject* ConstructJsonObject(UObject* WorldContextObject);

	/** Reset all internal data */
	UFUNCTION()
	void Reset();

	/** Get the root Json object */
	TSharedPtr<FJsonObject>& GetRootObject();

	/** Set the root Json object */
	void SetRootObject(const TSharedPtr<FJsonObject>& JsonObject);


	//////////////////////////////////////////////////////////////////////////
	// Serialization

	/** Serialize Json to string (formatted with line breaks) */
	UFUNCTION()
	FString EncodeJson() const;

	/** Serialize Json to string (single string without line breaks) */
	UFUNCTION()
	FString EncodeJsonToSingleString() const;

	/** Construct Json object from string */
	UFUNCTION()
	bool DecodeJson(const FString& JsonString);


	//////////////////////////////////////////////////////////////////////////
	// FJsonObject API

	/** Returns a list of field names that exist in the object */
	UFUNCTION()
	TArray<FString> GetFieldNames();

	/** Checks to see if the FieldName exists in the object */
	UFUNCTION()
	bool HasField(const FString& FieldName) const;

	/** Remove field named FieldName */
	UFUNCTION()
	void RemoveField(const FString& FieldName);

	/** Get the field named FieldName as a JsonValue */
	UFUNCTION()
	USIOJsonValue* GetField(const FString& FieldName) const;

	/** Add a field named FieldName with a Value */
	UFUNCTION()
	void SetField(const FString& FieldName, USIOJsonValue* JsonValue);

	/** Get the field named FieldName as a Json Array */
	UFUNCTION()
	TArray<USIOJsonValue*> GetArrayField(const FString& FieldName);

	/** Set an ObjectField named FieldName and value of Json Array */
	UFUNCTION()
	void SetArrayField(const FString& FieldName, const TArray<USIOJsonValue*>& InArray);
	
	/** Adds all of the fields from one json object to this one */
	UFUNCTION()
	void MergeJsonObject(USIOJsonObject* InJsonObject, bool Overwrite);


	//////////////////////////////////////////////////////////////////////////
	// FJsonObject API Helpers (easy to use with simple Json objects)

	/** Get the field named FieldName as a number. Ensures that the field is present and is of type Json number.
	 * Attn.!! float used instead of double to make the function blueprintable! */
	UFUNCTION()
	float GetNumberField(const FString& FieldName) const;

	/** Add a field named FieldName with Number as value
	 * Attn.!! float used instead of double to make the function blueprintable! */
	UFUNCTION()
	void SetNumberField(const FString& FieldName, float Number);

	/** Get the field named FieldName as a string. */
	UFUNCTION()
	FString GetStringField(const FString& FieldName) const;

	/** Add a field named FieldName with value of StringValue */
	UFUNCTION()
	void SetStringField(const FString& FieldName, const FString& StringValue);

	/** Get the field named FieldName as a boolean. */
	UFUNCTION()
	bool GetBoolField(const FString& FieldName) const;

	/** Set a boolean field named FieldName and value of InValue */
	UFUNCTION()
	void SetBoolField(const FString& FieldName, bool InValue);

	/** Get the field named FieldName as a Json object. */
	UFUNCTION()
	USIOJsonObject* GetObjectField(const FString& FieldName) const;

	/** Set an ObjectField named FieldName and value of JsonObject */
	UFUNCTION()
	void SetObjectField(const FString& FieldName, USIOJsonObject* JsonObject);

	/** Get the field named FieldName as a binary buffer array. */
	UFUNCTION()
	void GetBinaryField(const FString& FieldName, TArray<uint8>& OutBinary) const;

	/** Set an BinaryField named FieldName and binary buffer array */
	UFUNCTION()
	void SetBinaryField(const FString& FieldName, const TArray<uint8>& Bytes);


	//////////////////////////////////////////////////////////////////////////
	// Array fields helpers (uniform arrays)

	/** Get the field named FieldName as a Number Array. Use it only if you're sure that array is uniform!
	 * Attn.!! float used instead of double to make the function blueprintable! */
	UFUNCTION()
	TArray<float> GetNumberArrayField(const FString& FieldName);

	/** Set an ObjectField named FieldName and value of Number Array
	 * Attn.!! float used instead of double to make the function blueprintable! */
	UFUNCTION()
	void SetNumberArrayField(const FString& FieldName, const TArray<float>& NumberArray);

	/** Get the field named FieldName as a String Array. Use it only if you're sure that array is uniform! */
	UFUNCTION()
	TArray<FString> GetStringArrayField(const FString& FieldName);

	/** Set an ObjectField named FieldName and value of String Array */
	UFUNCTION()
	void SetStringArrayField(const FString& FieldName, const TArray<FString>& StringArray);

	/** Get the field named FieldName as a Bool Array. Use it only if you're sure that array is uniform! */
	UFUNCTION()
	TArray<bool> GetBoolArrayField(const FString& FieldName);

	/** Set an ObjectField named FieldName and value of Bool Array */
	UFUNCTION()
	void SetBoolArrayField(const FString& FieldName, const TArray<bool>& BoolArray);

	/** Get the field named FieldName as an Object Array. Use it only if you're sure that array is uniform! */
	UFUNCTION()
	TArray<USIOJsonObject*> GetObjectArrayField(const FString& FieldName);

	/** Set an ObjectField named FieldName and value of Ob Array */
	UFUNCTION()
	void SetObjectArrayField(const FString& FieldName, const TArray<USIOJsonObject*>& ObjectArray);


	//////////////////////////////////////////////////////////////////////////
	// Data

private:
	/** Internal JSON data */
	TSharedPtr<FJsonObject> JsonObj;

};
