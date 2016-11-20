#include <nx_audio.h>



int open_device() {
	ALCdevice *device = alcOpenDevice(NULL);
	if (!device) {
		nx_log_msg("Failed to open audio device.",2);
		return -1;
	}
	ALCcontext *context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);
	if (!context) {
		nx_log_msg("Failed to create ALC context.",2);
		return -2;
	}
	return 0;
}