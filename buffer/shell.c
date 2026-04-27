#include <system.h>

void shell(void) {
	char c;

	print("c:> ");
	while (1) {
		if ((c = getchar())) {
			if (c == '\n') {
				print("\rCommand empfangen\r\n");
				print("c:> ");
			} else {
			}
		}
	}

	print("exit shell\r\n");

	return;
}
