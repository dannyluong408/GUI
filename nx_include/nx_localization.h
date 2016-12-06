#pragma once
#include <stdint.h>
#include <nx_include/nx_error.h>

// Returns localized string for @identifier.
// Calling functions should check for NULL before using this string. It may not be loaded yet.
char *nx_localize_str(const uint32_t identifier);

// Maps a string identifier to an integer identifier. 
void nx_map_identifier(const char *str, const uint32_t identifier);

// Parses a localization file. @data is temporarily modified at times.
// All strings must be formatted properly. 
// Returns 0 on success.
int nx_parse_localization_file(char *data);

// This function must be called after all utilizing threads are joined.
void nx_localization_exit();