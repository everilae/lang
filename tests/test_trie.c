#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <trie.h>

static char* pairs[][2] = {
	{"asdf", "foo"},
	{"asdg", "bar"},
	{"asdd", "baz"},
	{"zsdf", "bard"},
	{"Zsdf", "gar"},
	{"Zsrf", "har"},
	{"zcvb", "sar"},
	{NULL, NULL},
};

int
main(int argc, char* argv[])
{
	Trie t = trie_new();
	assert(t);

	for (size_t i = 0; pairs[i][0]; i++) {
		assert(trie_set(t, pairs[i][0], pairs[i][1]) != NULL);
		assert(trie_get(t, pairs[i][0]) == pairs[i][1]);
	}

	assert(trie_get(t, "SHOULDNOTBE") == NULL);
	trie_repr(t, NULL);
	trie_delete(t);
}
