#ifndef DOUBLETS_H
#define DOUBLETS_H

/*  This pre-supplied function looks up a given word in the dictionary
    of approved words. It is assumed that the input word is in uppercase.
    The function returns true if the word is in the dictionary.
    Otherwise returns false. */

#define MAX_STEPS 30

bool dictionary_search(const char *word);

/* add your function prototypes here */

bool valid_step(const char *source, const char *target);

bool display_chain(const char *chain[MAX_STEPS], ostream&);

bool valid_chain(const char *chain[MAX_STEPS]);

bool find_chain(const char*, const char*, const char* answer[100], int, int depth = 0, int prev_change = -1);

#endif
