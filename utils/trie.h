#ifndef TRIE_H
#define TRIE_H 1

typedef struct TrieNode* Trie;

extern Trie trie_new();
extern Trie trie_copy(Trie src);
extern void trie_delete(Trie trie);
extern void* trie_get(Trie trie, const char* key);
extern Trie trie_set(Trie trie, const char* key, void* value);

#endif
