#pragma once

// Macro that checks if a pointer is nullptr or not
// Intended use: e.g if (player) player->Func(); becomes valid(player)->Func() 
#define valid(x) if (x != nullptr)x

// Function that returns true if a pointer is valid, else false
// Intended use: e.g if (player) { .. }; becomes if(isValid(player)) { .. }; more explicit
template<typename T>
inline constexpr bool isValid(T const& ptrType) {
	return ptrType != nullptr;
}