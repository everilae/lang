#include <stdlib.h>
#include <string.h>

#include <trie.h>
#include <debug.h>

struct TrieNode {
	/* NULL for leafs or pointer to linked list of children */
	struct TrieNode* children;
	/* NULL-terminated linked list of children */
	struct TrieNode* next;
	/* "Maybe a", aka NULL or valid pointer (not all keys have values along the way) */
	void* value;
	/* Map key */
	char key;
};

Trie
trie_new()
{
	return calloc(1, sizeof(struct TrieNode));
}

Trie
trie_copy(Trie src)
{
	Trie dest = trie_new();

	if (dest) {
		memmove(dest, src, sizeof(*dest));
	}

	return dest;
}

void
trie_delete(Trie trie)
{
	if (!trie) {
		return;
	}

	if (trie->next) {
		trie_delete(trie->next);
	}

	if (trie->children) {
		trie_delete(trie->children);
	}

	free(trie);
}

void*
trie_get(Trie trie, const char* key)
{
	if (!key || !trie) {
		return NULL;
	}

	if (!(*key)) {
		return trie->value;
	}

	Trie child = trie->children;
	for (; child; child = child->next) {
		if (child->key == *key) {
			break;
		}
	}

	return trie_get(child, key + 1);
}

Trie
trie_set(Trie trie, const char* key, void* value)
{
	if (!key || !trie) {
		return NULL;
	}

	if (!(*key)) {
		trie->value = value;
		return trie;
	}

	Trie child = trie->children;
	for (; child; child = child->next) {
		if (child->key == *key) {
			break;
		}
	}

	if (!child) {
		if (!(child = trie_new())) {
			/* OUT OF MEMORY */
			return NULL;
		}

		child->key = *key;
		/* Insert at the head of list */
		child->next = trie->children;
		trie->children = child;
	}

	return trie_set(child, key + 1, value);
}

static void
trie_repr(Trie trie)
{
	if (!trie) {
		return;
	}

	printf("<TrieNode '%c' = %p at %p>\n", trie->key, trie->value, (void*) trie);
	trie_repr(trie->next);
	trie_repr(trie->children);
}

#ifdef TEST
#include <stdio.h>

int
main(int argc, char* argv[]) {
	Trie t = trie_new();
	for (int i = 1; (i + 1) < argc; i += 2) {
		trie_set(t, argv[i], argv[i + 1]);
		const char* v = trie_get(t, argv[i]);
		if (!v || v != argv[i + 1]) {
			fprintf(stderr, "%s != %s", v ? v : "(nil)", argv[i]);
			exit(EXIT_FAILURE);
		}
	}
	trie_repr(t);
	trie_delete(t);
	return 0;
}

#endif
