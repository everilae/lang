#ifndef TRIE_H
#define TRIE_H 1

typedef struct TrieNode* Trie;
typedef void (*TrieFunc)(void* value, void* arg);
typedef void (*ValueReprFunc)(const void* value);

extern Trie trie_new();
extern Trie trie_copy(Trie src);
extern void trie_delete(Trie trie);
extern void* trie_get(Trie trie, const char* key);
extern Trie trie_set(Trie trie, const char* key, void* value);
extern void trie_for_each(Trie trie, TrieFunc f, void* arg);
extern void trie_repr(Trie trie, ValueReprFunc f);

#endif
