#include <stdio.h>
#include <stdlib.h>
#include <trie.h>

int
main(int argc, char* argv[]) {
	Trie t = trie_new();
	for (int i = 1; (i + 1) < argc; i += 2) {
		Trie n = trie_set(t, argv[i], argv[i + 1]);

		if (!n) {
			printf("trie_set() failed");
			exit(EXIT_FAILURE);
		}

		const char* v = trie_get(t, argv[i]);
		if (!v || v != argv[i + 1]) {
			printf("%s != %s\n", v ? v : "(nil)", argv[i]);
			exit(EXIT_FAILURE);
		}
	}

	if (trie_get(t, "SHOULDNOTBE")) {
		printf("Should not be\n");
		exit(EXIT_FAILURE);
	}

	trie_repr(t, NULL);
	trie_delete(t);
	return 0;
}
