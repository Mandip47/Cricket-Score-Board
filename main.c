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

void addPlayer(struct Player** players, int* numPlayers) {
    // Increment numPlayers
    (*numPlayers)++;
    // Reallocate memory to accommodate the new player
    *players = (struct Player*)realloc(*players, (*numPlayers) * sizeof(struct Player));
    if (*players == NULL) {
        printf("Memory reallocation failed. Exiting...\n");
        exit(EXIT_FAILURE);
    }
    // Input details of the new player
    printf("Enter name of the new player: ");
    scanf("%s", (*players)[*numPlayers - 1].name);
    printf("Enter runs scored by the new player: ");
    scanf("%d", &(*players)[*numPlayers - 1].runs);
    printf("Enter wickets taken by the new player: ");
    scanf("%d", &(*players)[*numPlayers - 1].wickets);
}


void removePlayer(struct Player* players, int* numPlayers, const char* playerName) {
    int found = 0;
    for (int i = 0; i < *numPlayers; i++) {
        if (strcmp(players[i].name, playerName) == 0) {
            found = 1;
            // Shift elements to the left to overwrite the player being removed
            for (int j = i; j < *numPlayers - 1; j++) {
                players[j] = players[j + 1];
            }
            (*numPlayers)--;
            break;
        }
    }
    if (!found) {
        printf("Player '%s' not found.\n", playerName);
    }
}

// void displayPlayerStatistics(const struct Player* player) {
//     printf("Player: %s\n", player->name);
//     printf("Runs: %d\n", player->runs);
//     printf("Wickets: %d\n", player->wickets);
// }
void printHorizontalLine(int length) {
    for(int i = 0; i < length; i++) {
        printf("-");
    }
    printf("\n");
}


void displayPlayerStatistics(const struct Player* player) {
    printf("| %-20s | %-6d | %-8d |\n", player->name, player->runs, player->wickets);
}


void displayTeamStatistics(const struct Player* players, int numPlayers) {
    int totalRuns = 0;
    int totalWickets = 0;
    for (int i = 0; i < numPlayers; i++) {
        totalRuns += players[i].runs;
        totalWickets += players[i].wickets;
    }
    printf("| %-20s | %-6d | %-8d |\n", "Total", totalRuns, totalWickets);

    // printf("Team Statistics:\n");
    // printf("Total Runs: %d\n", totalRuns);
    // printf("Total Wickets: %d\n", totalWickets);
}

void displayFilteredPlayers(const struct Player* players, int numPlayers, int filterRuns, int filterWickets) {
    printHorizontalLine(40);
    printf("Filtered Players:\n");
    printf("+----------------------+--------+----------+\n");
    printf("| Player Name          | Runs   | Wickets  |\n");
    printf("+----------------------+--------+----------+\n");
    for (int i = 0; i < numPlayers; i++) {
        if (players[i].runs > filterRuns || players[i].wickets > filterWickets) {
            displayPlayerStatistics(&players[i]);
            // printf("\n");
        }
    }
    printf("+----------------------+--------+----------+\n");
}

void searchAndDisplayPlayer(const struct Player* players, int numPlayers, const char* playerName) {
    int found = 0;
    printf("+----------------------+--------+----------+\n");
    printf("| Player Name          | Runs   | Wickets  |\n");
    printf("+----------------------+--------+----------+\n");
    for (int i = 0; i < numPlayers; i++) {
        if (strcmp(players[i].name, playerName) == 0) {
            found = 1;
            displayPlayerStatistics(&players[i]);
            break;
        }
    }
    printf("+----------------------+--------+----------+\n");

    if (!found) {
        printf("Player not found.\n");
    }
    
}


void displaySystemState(const struct Player* players, int numPlayers) {
    printf("+----------------------+--------+----------+\n");
    printf("| Players Name         | Runs   | Wickets  |\n");
    printf("+----------------------+--------+----------+\n");
    for (int i = 0; i < numPlayers; i++) {
        displayPlayerStatistics(&players[i]);
        // printf("\n");
    }
    printf("+----------------------+--------+----------+\n");
    displayTeamStatistics(players, numPlayers);
    printf("+----------------------+--------+----------+\n");
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

void recordRunOptions(){

}


int main() {
    int numPlayers,length = 40,defaultFile = 0,loadFromFile,MAX_PLAYERS = 11;
    printHorizontalLine(10);
    printf("Do you want to load player data from a file? (1 for yes, 0 for no): ");
    scanf("%d", &loadFromFile);
    char fileName[50]; // Declare the filename variable outside the if block

    if (loadFromFile) {
        printHorizontalLine(length);
        printf("Enter the filename to load data from: ");
        scanf("%s", fileName);
        system("clear");

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
        defaultFile = 1;
        fclose(file);
    } else {
        printHorizontalLine(length);
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
    printHorizontalLine(length);
    displaySystemState(players, numPlayers);
    // Main menu-driven loop
    do {
        printHorizontalLine(length);
        printf("Cricket Score Board\n");
        printHorizontalLine(length);
        printf("1. Record Runs\n");
        printf("2. Record Wickets\n");
        printf("3. Display all Statics\n");
        printf("4. Display Filtered Players\n");
        printf("5. Search and Display Player\n");
        printf("6. Save Player Data to File\n");
        printf("7. Add Player\n");
        printf("8. Remove Player\n");
        printf("9. Exit\n");
        printHorizontalLine(length);
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printHorizontalLine(length);

        switch (choice) {

            case 1: {
                // Record Runs
                int playerIndex, runs,runChoice;

                 printf("Enter player index (1-%d): ", numPlayers);
                 scanf("%d", &playerIndex);

                if (playerIndex >= 1 && playerIndex <= numPlayers) {

                printHorizontalLine(length);
                printf("1. Add 6 Run\n");
                printf("2. Add 4 Run\n");
                printf("3. Record Custom Runs\n");
                printf("Enter your choice: ");
                scanf("%d", &runChoice);

                switch(runChoice){
                    case 1:{
                           recordRuns(&players[playerIndex - 1], 6);
                           printf("SIX Run Added.\n");
                        break;
                    }
                    case 2:{
                           recordRuns(&players[playerIndex - 1], 4);
                           printf("FOUR Run Added.\n");
                        break;
                    }
                    case 3:{
                           printf("\nEnter runs scored: ");
                           scanf("%d", &runs);
                           recordRuns(&players[playerIndex - 1], runs);
                           printf("Runs recorded.\n");
                           break;
                    }
                    default:{
                        printf("Invalid choice.\n");
                        break;
                    }
                }


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
                if(defaultFile == 0) 
                {
                    char fileName2[50];
                    int option;
                    printf("Enter the filename to save data to  : ");
                    scanf("%s", fileName2);
                    savePlayersToFile(players, numPlayers, fileName2);
                    printf("Player data saved to %s.\n", fileName2);
                    printf("Do you want to make file default? (yes for 1):");
                    scanf("%d",&option);
                    if(option == 1){
                        defaultFile = 1;
                        strcpy(fileName,fileName2);
                    }
                }else{
                savePlayersToFile(players, numPlayers, fileName);
                printf("Player data saved to %s.\n", fileName);
                }
                break;
            }
            case 7: {
                    if (numPlayers < MAX_PLAYERS) { // MAX_PLAYERS is the maximum number of players allowed
                        addPlayer(&players, &numPlayers);
                        printf("Player added successfully.\n");
                    } else {
                        printf("Cannot add more players. Team is full.\n");
                    }
                    break;
                }
            case 8: {
                char playerName[50];
                printf("Enter the name of the player to remove: ");
                scanf("%s", playerName);
                removePlayer(players, &numPlayers, playerName);
                break;
            }
            case 9:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
        // system("clear");
    } while (choice != 9);
    // Free allocated memory
    free(players);

    return 0;
}