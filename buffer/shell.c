#include <system.h>

void shell(void) {
	static char s[80];
	char c;

	int i = 0;
	s[0] = '\0';

	print("c:> ");
	while (1) {
		if ((c = getchar())) {
			if (c == '\n') {
				print("\r");
				execute(s);
				s[0] = '\0';
				i = 0;
				print("c:> ");
			} else {
				s[i++] = c;
				s[i] = '\0';
			}
		}
	}

	print("exit shell\r\n");

	return;
}
