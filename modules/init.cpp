#include <modules/init.h>

static void remove_newlines(char *str) {
	uint32_t at = 0, to = 0;
	while (str[at]) {
		if (str[at] != '\n') {
			str[to] = str[at];
			to++;
		}
		at++;
	}
	str[to] = 0;
}
/*
static void tokenize_str(char *str, char ***output, const char token, uint32_t *n_tokens) {
	uint32_t at = 0;
	*n_tokens = 0;
	while (str[at]) {
		if (str[at] == token) *n_tokens++;
	}
	**output = 
}

static int read_settings_file(char *file, const uint32_t len) {
	
}
*/
static inline void interpret_args(const int argc, char **argv) {
	float f;
	int i;
	uint32_t use_threads = 0;
	for (int x = 1; x < argc; ++x) {
		if (sscanf(argv[x], "--loglevel=%i",&i) == 1) nx_log_suppress(i);
		else if (sscanf(argv[x], "--threads=%i",&i) == 1) use_threads = i;
		else if (sscanf(argv[x], "--framerate=%f", &f) == 1) printf("framerate target NYI\n"); // TODO: this
		else if (strcmp(argv[x], "--no-renderer") == 0) game_state.set_renderer(NX_NO_RENDERER);
		else {
			nx_log_msg("init: Unknown argument \"%s\".",2,argv[x]);
		}
	}
	if (!use_threads) use_threads = NXT_get_nprocs() + 1;
	game_state.set_n_cores(use_threads);
}

int mc_init(const int argc, char **argv) {
	const int ret = nx_init_asset_handler(argv[0]);
	if (ret) {
		// troubling indeed
		printf("nx_init_asset_handler() returned %i\n",ret);
		return -1;
	}
	
	char *error_path = nx_asset_translate_path("error.log");
	nx_log_init(error_path);
	free(error_path);
	
	interpret_args(argc, argv);
	if (NXT_init(game_state.get_n_cores(), 1)) {
		nx_log_msg("init: Failed to start worker pool.",1);
		return -1;
	}
	if (game_state.init_threads()) {
		return -1;
	}
	return 0;
}

void mc_close() {
	game_state.wait_close();
	NXT_exit();
	nx_log_exit();
}