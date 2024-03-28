#include <stdio.h>
#include <string.h>

#define MAX_CLUES 10
#define MAX_LENGTH 100

typedef struct {
    char relation[MAX_LENGTH];
    char relationValue[MAX_LENGTH];
} CluesType;

int main() {
    char line[MAX_LENGTH] = "Kind of: Home Decor!";

    // Example usage:
    CluesType clues;

    // Find the position of the colon (':') in the string
    char *colon_pos = strchr(line, ':'); // returns the index of the ':'

    if (colon_pos != NULL) {
        // Calculate the length of the relation (characters before the colon)
        int relation_length = colon_pos - line; // 7 - 0 = 7, note that colon_pos and line are char pointers (strings) that points to the first character of the string/char array
        printf("%d\n", relation_length);

        // Copy the relation (characters before the colon) to CluesType.relation
        strncpy(clues.relation, line, relation_length); // copy the first 7 characters (from index 0 to index 6) of line to clues.relation
        clues.relation[relation_length] = '\0'; // Null-terminate the string for the last character (index 7)

        // Move past the colon (':') and any subsequent spaces
        colon_pos += 2;
        // colon_pos++;
        // while (*colon_pos == ' ') {
        //     colon_pos++;
        // }

        // then Copy the relation value (characters after the colon and any spaces) to CluesType.relationValue
        strcpy(clues.relationValue, colon_pos);
    }

    // Print the result
    printf("Relation: %s\n", clues.relation);
    printf("Relation Value: %s\n", clues.relationValue);

    return 0;
}
