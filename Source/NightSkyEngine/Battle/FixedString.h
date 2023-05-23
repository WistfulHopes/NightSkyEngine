#pragma once

template<int Length>
struct FixedString
{
private:
	
	char Data[Length] = { 0 };
	
public:
	FixedString()
	{
		std::memset(Data, 0, Length);
	}

	void SetString(const FString& InString)
	{
		std::memset(Data, 0, Length);
		strcpy(Data, TCHAR_TO_ANSI(*InString));
	}

	char* GetString()
	{
		return Data;
	}
};
