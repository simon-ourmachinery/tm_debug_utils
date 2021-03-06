#pragma once
#include <foundation/api_types.h>

#define TM_DEBUG_UTILS_API_NAME "tm_debug_utils"

struct tm_temp_allocator_i;

struct tm_debug_utils_api
{
	// Reverses the specified hash into the string that generated it.
	// Result is allocated with the specified allocator or null if the hash was not found.
	const char *(*decode_hash)(uint64_t hash, struct tm_temp_allocator_i *ta);
	// Attempts to reverse the specified hash into the string that generated it.
	// If the string could not be found it returns the hash in string form instead.
	// Result is allocated with the specified allocator or null if the hash was not found.
	const char *(*try_decode_hash)(uint64_t hash, struct tm_temp_allocator_i *ta);
	// Searches the specified path and sub directories for The Machinery symbols.
	void (*add_symbol_database)(const char *path);
	// Adds the specified string to a runtime database that shares its lifetime with the dll.
	// Returns the hash generated.
	uint64_t(*add_hash)(const char *string);
};

#if defined(TM_LINKS_DEBUG_UTILS)
extern struct tm_debug_utils_api *tm_debug_utils_api;
#endif