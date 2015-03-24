#include <stdlib.h>
#include <string.h>

#include <trie.h>
#include <map.h>
#include <debug.h>

struct TrieNode {
	/* NULL for leafs or pointer to Map of children */
	Map children;
	/* "Maybe a", aka NULL or valid pointer (not all keys have values along the way) */
	void* value;
	/* Map key */
	char key;
};

Trie
trie_new()
{
	Trie t = calloc(1, sizeof(struct TrieNode));

	if (t && !(t->children = map_new('?', NULL))) {
		free(t);
		return NULL;
	}

	return t;
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

static void
trie_delete_recur(void* value, void* arg)
{
	if (value) {
		trie_delete((Trie) value);
	}
}

void
trie_delete(Trie trie)
{
	if (!trie) {
		return;
	}

	if (trie->children) {
		map_for_each(trie->children, trie_delete_recur, NULL);
		map_delete(trie->children);
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

	return trie_get(map_get(trie->children, *key), key + 1);
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

	Trie child = map_get(trie->children, *key);
	if (!child) {
		if (!(child = trie_new())) {
			/* OUT OF MEMORY */
			return NULL;
		}

		child->key = *key;
		map_set(trie->children, *key, child);
	}

	return trie_set(child, key + 1, value);
}

typedef struct {
	TrieFunc f;
	void* arg;
} TrieFuncClosure;

static void
trie_for_each_recur(void* value, void* arg)
{
	if (value && arg) {
		TrieFuncClosure* closure = arg;
		trie_for_each((Trie) value, closure->f, closure->arg);
	}
}

void
trie_for_each(Trie trie, TrieFunc f, void* arg)
{
	if (!trie || !f) {
		return;
	}

	f(trie->value, arg);

	if (trie->children) {
		map_for_each(trie->children, trie_for_each_recur, (void*) &((TrieFuncClosure) {
			f, arg,
		}));
	}
}

typedef struct {
	ValueReprFunc f;
} ValueReprFuncCont;

static void
trie_repr_recur(void* value, void* arg)
{
	if (value && arg) {
		trie_repr(value, ((ValueReprFuncCont*) arg)->f);
	}
}

#include <stdio.h>

void
trie_repr(Trie trie, ValueReprFunc f)
{
	if (!trie) {
		return;
	}
	
	if (f) {
		f(trie->value);
	} else {
		printf("<TrieNode '%c' = %p at %p>\n", trie->key, trie->value, (void*) trie);
	}

	map_for_each(trie->children, trie_repr_recur, &((ValueReprFuncCont) {
		f,
	}));
}
