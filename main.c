#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Player {
    char name[50];
    int runs;
    int wickets;
};

void recordRuns(struct Player* player, int runs) {
    player->runs += runs;
}

void recordWickets(struct Player* player, int wickets) {
    player->wickets += wickets;
}

void displayPlayerStatistics(const struct Player* player) {
    printf("Player: %s\n", player->name);
    printf("Runs: %d\n", player->runs);
    printf("Wickets: %d\n", player->wickets);
}

void displayTeamStatistics(const struct Player* players, int numPlayers) {
    int totalRuns = 0;
    int totalWickets = 0;
    for (int i = 0; i < numPlayers; i++) {
        totalRuns += players[i].runs;
        totalWickets += players[i].wickets;
    }
    printf("Team Statistics:\n");
    printf("Total Runs: %d\n", totalRuns);
    printf("Total Wickets: %d\n", totalWickets);
}

void displayFilteredPlayers(const struct Player* players, int numPlayers, int filterRuns, int filterWickets) {
    printf("Filtered Players:\n");
    for (int i = 0; i < numPlayers; i++) {
        if (players[i].runs > filterRuns || players[i].wickets > filterWickets) {
            displayPlayerStatistics(&players[i]);
            printf("\n");
        }
    }
}

void searchAndDisplayPlayer(const struct Player* players, int numPlayers, const char* playerName) {
    int found = 0;
    for (int i = 0; i < numPlayers; i++) {
        if (strcmp(players[i].name, playerName) == 0) {
            found = 1;
            displayPlayerStatistics(&players[i]);
            break;
        }
    }

    if (!found) {
        printf("Player not found.\n");
    }
    
}


void displaySystemState(const struct Player* players, int numPlayers) {
    for (int i = 0; i < numPlayers; i++) {
        displayPlayerStatistics(&players[i]);
        printf("\n");
    }
    displayTeamStatistics(players, numPlayers);
}

void savePlayersToFile(const struct Player* players, int numPlayers, const char* fileName) {
    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error opening file for writing. Exiting...\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numPlayers; i++) {
        fprintf(file, "%s %d %d\n", players[i].name, players[i].runs, players[i].wickets);
    }

    fclose(file);
}

void loadPlayersFromFile(struct Player* players, int numPlayers, const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file for reading. Exiting...\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numPlayers; i++) {
        if (fscanf(file, "%s %d %d", players[i].name, &players[i].runs, &players[i].wickets) != 3) {
            printf("Error reading data from file. Exiting...\n");
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
}

int main() {
    // int numPlayers;
    // printf("Enter the number of players in the cricket team: ");
    // scanf("%d", &numPlayers);

    // struct Player* players = (struct Player*)malloc(numPlayers * sizeof(struct Player));
    // if (players == NULL) {
    //     printf("Memory allocation failed. Exiting...\n");
    //     exit(EXIT_FAILURE);
    // }

    // // Initialize player information or load from a file
    // printf("Do you want to load player data from a file? (1 for yes, 0 for no): ");
    // int loadFromFile;
    // scanf("%d", &loadFromFile);

    // if (loadFromFile) {
    //     char fileName[50];
    //     printf("Enter the filename to load data from: ");
    //     scanf("%s", fileName);
    //     loadPlayersFromFile(players, numPlayers, fileName);
    // } else {
    //     for (int i = 0; i < numPlayers; i++) {
    //         printf("Enter name of player %d: ", i + 1);
    //         scanf("%s", players[i].name);
    //         players[i].runs = 0;
    //         players[i].wickets = 0;
    //     }
    // }

// new 
     int numPlayers;
    printf("Do you want to load player data from a file? (1 for yes, 0 for no): ");
    int loadFromFile;
    scanf("%d", &loadFromFile);
    char fileName[50]; // Declare the filename variable outside the if block

    if (loadFromFile) {
        printf("Enter the filename to load data from: ");
        scanf("%s", fileName);

        FILE* file = fopen(fileName, "r");
        if (file == NULL) {
            printf("Error opening file for reading. Exiting...\n");
            exit(EXIT_FAILURE);
        }

        // Declare and initialize variable to store player data
        struct Player tempPlayer;
        
        // Count the number of players in the file
        numPlayers = 0;
        while (fscanf(file, "%s %*d %*d", tempPlayer.name) != EOF) {
            numPlayers++;
        }

        fclose(file);
    } else {
        printf("Enter the number of players in the cricket team: ");
        scanf("%d", &numPlayers);
    }

    // Dynamically allocate memory for players
    struct Player* players = (struct Player*)malloc(numPlayers * sizeof(struct Player));
    if (players == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        exit(EXIT_FAILURE);
    }

    // Load players from file or input from user
    if (loadFromFile) {
        loadPlayersFromFile(players, numPlayers, fileName); // Use the filename obtained earlier
    } else {
        for (int i = 0; i < numPlayers; i++) {
            printf("Enter name of player %d: ", i + 1);
            scanf("%s", players[i].name);
            players[i].runs = 0;
            players[i].wickets = 0;
        }
    }
    ///////////////
    int choice;
    // Main menu-driven loop
    do {
        // displaySystemState(players, numPlayers);

        // Display menu options
        printf("\nCricket Score Board\n");
        printf("1. Record Runs\n");
        printf("2. Record Wickets\n");
        printf("3. Display all Statics\n");
        printf("4. Display Filtered Players\n");
        printf("5. Search and Display Player\n");
        printf("6. Save Player Data to File\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Record Runs
                int playerIndex, runs;
                printf("Enter player index (1-%d): ", numPlayers);
                scanf("%d", &playerIndex);
                if (playerIndex >= 1 && playerIndex <= numPlayers) {
                    printf("Enter runs scored: ");
                    scanf("%d", &runs);
                    recordRuns(&players[playerIndex - 1], runs);
                    printf("Runs recorded.\n");
                } else {
                    printf("Invalid player index.\n");
                }
                break;
            }
            case 2: {
                // Record Wickets
                int playerIndex, wickets;
                printf("Enter player index (1-%d): ", numPlayers);
                scanf("%d", &playerIndex);
                if (playerIndex >= 1 && playerIndex <= numPlayers) {
                    printf("Enter wickets taken: ");
                    scanf("%d", &wickets);
                    recordWickets(&players[playerIndex - 1], wickets);
                    printf("Wickets recorded.\n");
                } else {
                    printf("Invalid player index.\n");
                }
                break;
            }
            case 3:{
                displaySystemState(players, numPlayers);
                break;
            }
            case 4: {
                // Display Filtered Players
                int filterRuns, filterWickets;
                printf("Enter minimum runs to display: ");
                scanf("%d", &filterRuns);
                printf("Enter minimum wickets to display: ");
                scanf("%d", &filterWickets);
                displayFilteredPlayers(players, numPlayers, filterRuns, filterWickets);
                break;
            }
            case 5: {
                // Search and Display Player
                char playerName[50];
                printf("Enter player name to search: ");
                scanf("%s", playerName);
                searchAndDisplayPlayer(players, numPlayers, playerName);
                break;
            }
            case 6: {
                // Save Player Data to File
                char fileName[50];
                printf("Enter the filename to save data to  : ");
                scanf("%s", fileName);
                savePlayersToFile(players, numPlayers, fileName);
                printf("Player data saved to %s.\n", fileName);
                break;
            }
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 7);

    // Free allocated memory
    free(players);

    return 0;
}