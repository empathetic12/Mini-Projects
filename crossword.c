#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_WORD_LEN 100
#define MAX_GUESSES 5

const char *word_bank[] = {
    "mountain", "elephant", "library", "pyramid", "horizon",
    "oxygen", "galaxy", "desert", "planet", "harvest",
    "anchor", "beacon", "canyon", "dagger", "empire",
    "falcon", "glacier", "harbor", "island", "jungle",
    "kitten", "lantern", "magnet", "nebula", "oracle",
    "parade", "quartz", "rocket", "saturn", "tunnel",
    "unicorn", "volcano", "wanderer", "xenon", "yonder",
    "zephyr", "avalanche", "bamboo", "coral", "dynasty",
    "ember", "fossil", "geyser", "horizon", "icicle",
    "jigsaw", "karate", "labyrinth", "mirage", "nomad",
    "oasis", "phoenix", "quasar", "relic", "safari",
    "tornado", "utopia", "vortex", "whisper", "xylem",
    "yeti", "zenith", "acorn", "blizzard", "cactus",
    "delta", "echo", "fjord", "groove", "habitat",
    "inferno", "jungle", "kelvin", "lagoon", "magma",
    "nectar", "orbit", "plasma", "quill", "reef",
    "sphinx", "tidal", "uranium", "valley", "wilderness",
    "xenolith", "yarn", "zen", "archipelago", "bayou",
    "cliff", "dune", "estuary", "fjord", "gorge",
    "hill", "iceberg", "jetty", "knoll", "lagoon",
    "mesa", "narrows", "outcrop", "peninsula", "quagmire",
    "ridge", "savanna", "tundra", "upland", "vale",
    "wetland", "xerophyte", "yardang", "zodiac",
    "amber", "bison", "coral", "dolphin", "eagle",
    "ferret", "giraffe", "hippo", "ibis", "jaguar",
    "koala", "lemur", "meerkat", "narwhal", "ocelot",
    "panther", "quetzal", "raccoon", "sloth", "tapir",
    "urchin", "vulture", "walrus", "xerus", "yak",
    "zebra"};
const int word_bank_size = sizeof(word_bank) / sizeof(word_bank[0]);

typedef struct WordNode
{
    char word[MAX_WORD_LEN];
    int revealed[MAX_WORD_LEN];
    struct WordNode *next;
} WordNode;

WordNode *head = NULL;
int total_attempts = 0;
int wrong_guesses = 0;
char used_letters[100];
int used_count = 0;

void add_word_to_list(const char *w)
{
    WordNode *node = (WordNode *)malloc(sizeof(WordNode));
    strncpy(node->word, w, MAX_WORD_LEN);
    memset(node->revealed, 0, sizeof(node->revealed));
    node->next = NULL;
    head = node;
}

void load_random_word()
{
    int selected = rand() % word_bank_size;
    add_word_to_list(word_bank[selected]);

    int len = strlen(head->word);
    int reveal = len > 7 ? 2 : (len > 5 ? 1 : 0);
    for (int j = 0; j < reveal;)
    {
        int index = rand() % len;
        if (!head->revealed[index])
        {
            head->revealed[index] = 1;
            j++;
        }
    }
}

void print_word()
{
    printf("\n=== Crossword Word ===\n");
    WordNode *curr = head;
    int len = strlen(curr->word);
    printf("Word: ");
    for (int j = 0; j < len; j++)
    {
        if (curr->revealed[j])
            printf("%c ", curr->word[j]);
        else
            printf("_ ");
    }
    printf("\n");
}

void print_used_letters()
{
    printf("Used letters: ");
    for (int i = 0; i < used_count; i++)
    {
        printf("%c ", used_letters[i]);
    }
    printf("\n");
}

int all_revealed()
{
    WordNode *curr = head;
    int len = strlen(curr->word);
    for (int j = 0; j < len; j++)
    {
        if (!curr->revealed[j])
            return 0;
    }
    return 1;
}

int letter_already_used(char c)
{
    for (int i = 0; i < used_count; i++)
    {
        if (used_letters[i] == c)
            return 1;
    }
    return 0;
}

void add_used_letter(char c)
{
    if (!letter_already_used(c))
    {
        used_letters[used_count++] = c;
    }
}

int process_guess(char c)
{
    WordNode *curr = head;
    int found = 0;
    int len = strlen(curr->word);
    for (int j = 0; j < len; j++)
    {
        if (toupper(curr->word[j]) == c && !curr->revealed[j])
        {
            curr->revealed[j] = 1;
            found = 1;
        }
    }
    return found;
}

void reveal_answer()
{
    printf("\n--- Actual Word ---\n");
    printf("Word: %s\n", head->word);
}

void cleanup_list()
{
    WordNode *curr = head;
    while (curr)
    {
        WordNode *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
}

int main()
{
    srand((unsigned int)time(NULL));
    load_random_word();

    while (!all_revealed() && wrong_guesses < MAX_GUESSES)
    {
        print_word();
        print_used_letters();
        printf("Remaining guesses: %d || ", MAX_GUESSES - wrong_guesses);
        printf("Total guesses: %d\n", total_attempts);

        printf("Enter a letter: ");
        char guess;
        scanf(" %c", &guess);
        guess = toupper(guess);
        add_used_letter(guess);
        total_attempts++;

        if (!process_guess(guess))
        {
            wrong_guesses++;
            printf("Wrong! Total wrong guesses: %d\n", wrong_guesses);
        }
        else
        {
            printf("Correct!\n");
        }
    }

    if (all_revealed())
    {
        printf("\nYou completed the crossword in %d attempts!\n", total_attempts);
    }
    else
    {
        printf("\nGame Over! You hit %d wrong guesses.\n", MAX_GUESSES);
    }

    reveal_answer();
    cleanup_list();
    return 0;
}
