#include "localization.h"
#include <assert.h>
#include <unordered_map>
#include <pthread.h>


pthread_mutex_t mtx = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
static std::unordered_map<uint32_t,char*> localized_strings;
static std::unordered_map<std::string,uint32_t> string_mappings;

char *nx_localize_str(const uint32_t identifier) {
	pthread_mutex_lock(&mtx);
	const auto i = localized_strings.find(identifier);
	char *ret = (i != localized_strings.end()) ? localized_strings[identifier] : NULL;
	pthread_mutex_unlock(&mtx);
	return ret;
}

static uint32_t fetch_mapping(const char *str) {
	uint32_t ret = 0;
	const auto i = string_mappings.find(str);
	if (i != string_mappings.end()) {
		ret = string_mappings[str];
	}
	return ret;
}

void nx_map_identifier(const char *str, const uint32_t identifier) {
	pthread_mutex_lock(&mtx);	
	#ifndef NDEBUG
		// make sure we aren't overwriting a currently mapped identifier.
		const uint32_t current = fetch_mapping(str);
		assert(!current);
	#endif
	string_mappings[std::string(str)] = identifier;
	pthread_mutex_unlock(&mtx);
}

static void map_string(const char *input, const uint32_t identifier) {
	assert(input);
	assert(strlen(input));
	// make sure we aren't overwriting a currently mapped string.
	assert(localized_strings.find(identifier) == localized_strings.end());
	
	const size_t len = strlen(input) + 1;
	char *copy = (char*)malloc(len);
	memcpy(copy, input, len);
	
	localized_strings[identifier] = copy;
}

// this function is only called in debug mode, so the error message has a high priority.
static void verify_string_db() {
	for (auto i : string_mappings) {
		if (localized_strings.find(i.second) == localized_strings.end()) {
			nx_log_msg("No string found for identifier \"%s\".",2,i.first.c_str());
		}
	}
}

int nx_parse_localization_file(char *data) {
	assert(strlen(data));
	const size_t len = strlen(data);
	size_t at = 0;
	printf("file length is %u\n",len);
	fflush(stdout);
	pthread_mutex_lock(&mtx);
	while (at < len) {
		const size_t line_len = strcspn(&data[at],"\n");
		const size_t id_len = strcspn(&data[at], " ");
		if (data[at] == '/') { // this is a comment
			at += line_len;
		} else {
			if (id_len && line_len > id_len) {
				char save = data[at + line_len];
				data[at + id_len] = 0;
				data[at + line_len] = 0;
				const uint32_t id = fetch_mapping(&data[at]);
				if (id) {
					map_string(&data[at + id_len + 1], id);
					#ifndef NDEBUG
					printf("Mapped string '%s' to %u\n",&data[at + id_len + 1],id);
					#endif
				}
				#ifndef NDEBUG
					printf("No identifier found for string '%s'.\n",&data[at]);
				#endif
				// restore chars
				data[at + id_len] = ' '; 
				data[at + line_len] = save;
				at += line_len;
			}
			at++;
		}
		printf("at %u, len %u\n",at,len);fflush(stdout);
	}
	#ifndef NDEBUG
	verify_string_db();
	#endif
	pthread_mutex_unlock(&mtx);
	return 0;
}
