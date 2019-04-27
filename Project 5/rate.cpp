#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;

const int MAX_WORD_LENGTH = 20;

int makeProper(char word1[][MAX_WORD_LENGTH + 1],
	char word2[][MAX_WORD_LENGTH + 1],
	int separation[],
	int nPatterns)
{
	int failed = 0;

    // iterates through each pattern, checking for validity
	for (int i = 0; i < nPatterns - failed; i++) {
		bool invalid = false; // sets the pattern as valid 

		if (word1[i][0] == '\0' || word2[i][0] == '\0')
			invalid = true; // sets the pattern as invalid if both words are empty

		if (separation[i] < 0)
			invalid = true; // sets the pattern as invalid the separation is negative

		for (int c = 0; word1[i][c] != '\0'; c++) {
			if (!isalpha(word1[i][c])) {
				invalid = true; // sets the pattern as invalid if there is a non-alpha character in word1
				continue;
			}
			word1[i][c] = tolower(word1[i][c]);
		}

		for (int c = 0; word2[i][c] != '\0'; c++) {
			if (!isalpha(word2[i][c])) {
				invalid = true; // sets the pattern as invalid if there is a non-alpha character in word2
				continue;
			}
			word2[i][c] = tolower(word2[i][c]);
		}

        // flags duplicates as invalid and sets the separation value to the minimum separation value
		for (int j = 0; j < i; j++) {
			if ((strcmp(word1[j], word1[i]) == 0 && strcmp(word2[j], word2[i]) == 0) || ((strcmp(word2[j], word1[i]) == 0 && strcmp(word1[j], word2[i]) == 0))) {
				separation[j] = separation[j] > separation[i] ? separation[j] : separation[i];
				invalid = true;
				continue;
			}
		}

        // removes invalid patterns
		if (invalid) {
			strcpy(word1[i], word1[nPatterns - 1 - failed]);
			strcpy(word2[i], word2[nPatterns - 1 - failed]);
			separation[i] = separation[nPatterns - 1 - failed];
			i--;
			failed++;
		}
	}
	return nPatterns - failed; // returns number of valid patterns
}

int rate(const char document[],
	const char word1[][MAX_WORD_LENGTH + 1],
	const char word2[][MAX_WORD_LENGTH + 1],
	const int separation[],
	int nPatterns)
{

    // creates a cstring representing the successfully parsed document
	char parsedDoc[250] = { '\0' };
	bool lastSpace = false;
	for (int i = 0, doc = 0; document[i] != '\0'; i++) {
		if (isalpha(document[i])) {
			parsedDoc[doc] = tolower(document[i]); // makes all charcters lower
			doc++;
			parsedDoc[doc] = '\0';
			lastSpace = false;
		}
		else if (document[i] == ' ' && !lastSpace) { // turns consecutive spaces into single spaces
			parsedDoc[doc] = ' ';
			doc++;
			parsedDoc[doc] = '\0';
			lastSpace = true;
		}
	}

	int patternsFound = 0;

	for (int p = 0; p < nPatterns; p++) {
		bool found1 = false;
		bool found2 = false;

		int word1counter = 0;
		int word2counter = 0;

		// searches for the pattern if the words are the same
		if(strcmp(word1[p], word2[p]) == 0) {
			bool found = false;
			int counter = 0;

			for(int i = 0; parsedDoc[i] != '\0'; i++) {
				// searches for the word within parsedDoc
				if (parsedDoc[i] == word1[p][0] && (i == 0 || parsedDoc[i - 1] == ' ')) {
					bool match = true;
					int c;
					for (c = 0; word1[p][c] != '\0'; c++) {
						if (parsedDoc[i + c] != word1[p][c]) {
							match = false;
							continue;
						}
					}
					if (parsedDoc[i + c] != '\0' && parsedDoc[i + c] != ' ')
						match = false;
					if (match) { // if the word is found and has been found within separation ago pattern is found
						if (found) {
							patternsFound++;
							goto out; // jumps out of multiple nested loops to go to next pattern
						}
						found = true;
						counter = separation[p] + 1;
					}
				}

				if (parsedDoc[i] == ' ') {
					if (found) {
						counter--;
						if(counter < 0) {
							found = false;
						}
					}
				}
			}
			goto out;
		}

        // sets flag determining if both words are found within separation of each other
		for (int i = 0; parsedDoc[i] != '\0'; i++) {

			if (parsedDoc[i] == ' ') {
				if (found1) {
					word1counter--;
					if (word1counter < 0) {
						found1 = false; // sets flag for word1 being found to false if separation has passed
					}
				}
				if (found2) {
					word2counter--;
					if (word2counter < 0) {
						found2 = false; // sets flag for word2 being found to false if separation has passed
					}
				}
			}

            // searches for word1 within parsedDoc and sets the flag for found to be true if found
			if (parsedDoc[i] == word1[p][0] && (i == 0 || parsedDoc[i - 1] == ' ')) {
				bool match = true;
				int c;
				for (c = 0; word1[p][c] != '\0'; c++) {
					if (parsedDoc[i + c] != word1[p][c]) {
						match = false;
						continue;
					}
				}
				if (parsedDoc[i + c] != '\0' && parsedDoc[i + c] != ' ')
					match = false;
				if (match) {
					found1 = true;
					word1counter = separation[p] + 1;
				}
			}

            // searches for word2 within parsedDoc and sets the flag for found to be true if found
			if (parsedDoc[i] == word2[p][0] && (i == 0 || parsedDoc[i - 1] == ' ')) {
				bool match = true;
				int c;
				for (c = 0; word2[p][c] != '\0'; c++) {
					if (parsedDoc[i + c] != word2[p][c]) {
						match = false;
						continue;
					}
				}
				if (parsedDoc[i + c] != '\0' && parsedDoc[i + c] != ' ')
					match = false;
				if (match) {
					found2 = true;
					word2counter = separation[p] + 1;
				}
			}

			if (found1 && found2) {
				patternsFound++; // increases patternsFound by 1 if pattern is found then goes to next pattern
				break;
			}
		}
		out:; // label for escaping to next pattern
	}
	return patternsFound;
}

int main()
{
	const int TEST1_NRULES = 4;
	char test1w1[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
		"mad",       "deranged", "nefarious", "have"
	};
	char test1w2[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
		"scientist", "robot",    "plot",      "mad"
	};
	int test1dist[TEST1_NRULES] = {
		1,           3,          0,           12
	};
	assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
	assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
	assert(rate("**** 2018 ****",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
	assert(rate("  That plot: NEFARIOUS!",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
	assert(rate("deranged deranged robot deranged robot robot",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
	assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
	cerr << "All tests succeeded" << endl;
}