#include "ctype.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#define CHARACTERS "abcdefghijklmnopqrstuvwxyz1234567890"
#define CHARACTERS_LEN 36
#define EXTRA_ELEMENTS "!@#$&*()?:{}[].,+-"
#define EXTRA_ELEMENTS_LEN 18
#define DEFAULT_PASSWORD_SIZE 21
#define RAND_BOOL() (rand() & 1)

typedef struct Args {
    uint8_t argc;
    char** argv;
} Args;

bool ArgExists(const char* ARGUMENT_VALUE, const Args* args);

void GeneratePassword(char *response, const uint8_t SEARCH_SPACE, const bool insensitive); 

void GenerateDescription(char *response, const uint8_t SEARCH_SPACE, const bool insensitive);

int main(int argc, char** argv) {
    const char* INCLUDE_EXTRA_FLAG = "--include-extra";
    const char* INSENSITIVE_FLAG = "--insensitive";

    if (argc > 3) {
        fprintf(stderr, "Usage: passgen <INCLUDE-EXTRA?> | <INSENSITIVE?>\n");
        fprintf(stderr, "\t--include-extra: include extra characters (!@#$&*()?:/)\n");
        fprintf(stderr, "\t--insensitive: Does not care about case\n");

        return EXIT_FAILURE;
    }

    Args args = {
        .argc = (uint8_t) argc,
        .argv = argv
     };
    
    uint8_t searchSpace = CHARACTERS_LEN;

    if (ArgExists(INCLUDE_EXTRA_FLAG, &args)) {
        searchSpace+=EXTRA_ELEMENTS_LEN;
    }

    bool insensitive = ArgExists(INSENSITIVE_FLAG, &args);
  
    char password[DEFAULT_PASSWORD_SIZE] = "\0";

    char description[UINT8_MAX] = "\0";
    
    GeneratePassword(password, searchSpace, insensitive);
    
    GenerateDescription(description, searchSpace, insensitive);

    printf("Generated (%s): %s ", description, password);
    return EXIT_SUCCESS;
}


void GeneratePassword(char *response, const uint8_t SEARCH_SPACE, const bool insensitive) {
  srand(time(NULL));
  for (uint8_t i = 0; i < DEFAULT_PASSWORD_SIZE - 1; ++i) {
    uint8_t generatedValue = rand() % SEARCH_SPACE;
    char currentCharacter = 0;
    bool upper = RAND_BOOL();
    if (generatedValue > CHARACTERS_LEN) {
      generatedValue -= CHARACTERS_LEN;
      currentCharacter = EXTRA_ELEMENTS[generatedValue];
    } else {
      currentCharacter = CHARACTERS[generatedValue];
    }
    
    if (!insensitive && upper && isalpha(currentCharacter)) {
      currentCharacter = toupper(currentCharacter);
    }

    strncat(response, &currentCharacter, 1);
  }
} 

void GenerateDescription(char *response, const uint8_t SEARCH_SPACE, const bool insensitive) {
  char defaultGeneration[] = "Default, no flags";
  char extraCharactersUsed[] = "Extra characters";
  char insensitiveUsed[] = "Insensitive";
  if (SEARCH_SPACE == CHARACTERS_LEN && !insensitive) {
    strncpy(response, defaultGeneration, UINT8_MAX);
    return;
  }

  snprintf(response, UINT8_MAX - 1, "%s%s%s",
    SEARCH_SPACE > CHARACTERS_LEN ? extraCharactersUsed : "",
    SEARCH_SPACE > CHARACTERS_LEN && insensitive ? " + ": "",
    insensitive ? insensitiveUsed : ""
  );

}

bool ArgExists(const char* ARGUMENT_VALUE, const Args* args) {
    for (uint8_t i = 0; i < args->argc; ++i) {
        if (strncmp(args->argv[i], ARGUMENT_VALUE, UINT8_MAX) == 0) {
            return true;
        }
    }
    return false;
}
