#pragma once

/**
 * A string with length known at compile time.
 * 
 * @tparam Length The length of the string.
 */
template<int Length>
struct FixedString
{
private:

	/**
	 * The string data as a char array.
	 */
	char Data[Length] = { 0 };
	
public:
	/**
	 * Initializes the string with null bytes..
	 */
	FixedString()
	{
		std::memset(Data, 0, Length);
	}

	/**
	 * Sets the char array from an FString.
	 * 
	 * @param InString The FString to use as a basis.
	 */
	void SetString(const FString& InString)
	{
		std::memset(Data, 0, Length);
#if PLATFORM_WINDOWS
		strcpy_s(Data, Length, TCHAR_TO_ANSI(*InString));
#else
		strcpy(Data, TCHAR_TO_ANSI(*InString));
#endif
	}

	/**
	 * Gets the string data.
	 * 
	 * @return The char array as a pointer.
	 */
	char* GetString()
	{
		return Data;
	}
};