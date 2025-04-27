#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"

#define MAX_PROPERTIES 100
#define MAX_FAVORITES 50
#define MAX_TITLE_LENGTH 49
#define MAX_PARKING_LENGTH 3

typedef struct {
    int id;
    char title[50];
    int price;
    int size;
    int rooms;
    int bathrooms;
    char parking[4];
} Property;

void clearScreen() {
    printf("\033[H\033[J");
}

void mainMenu();
void searchListings();
void viewFavorites();
void loadProperties();
void saveFavorites();
void loadFavorites();
void addToFavorites(int propertyId);
int getValidInt(const char* prompt, int min, int max);
int isValidParking(const char* parking);

Property properties[MAX_PROPERTIES];
Property favorites[MAX_FAVORITES];
int propertyCount = 0;
int favoritesCount = 0;

int getValidInt(const char* prompt, int min, int max) {
    int value;
    char input[100];
    
    while (1) {
        printf("%s", prompt);
        fgets(input, sizeof(input), stdin);
        
        if (sscanf(input, "%d", &value) == 1 && value >= min && value <= max) {
            return value;
        }
        
        printf(COLOR_RED "Invalid input. Please enter a number between %d and %d.\n" COLOR_RESET, min, max);
    }
}

int isValidParking(const char* parking) {
    return (strcmp(parking, "yes") == 0 || strcmp(parking, "no") == 0);
}

void loadProperties() {
    FILE *file = fopen("properties.txt", "r");
    if (!file) {
        printf(COLOR_RED "Error: Could not open properties.txt.\n" COLOR_RESET);
        return;
    }
    
    propertyCount = 0;
    while (fscanf(file, "%d,%49[^,],%d,%d,%d,%d,%3s", &properties[propertyCount].id, properties[propertyCount].title, &properties[propertyCount].price,
                  &properties[propertyCount].size, &properties[propertyCount].rooms, &properties[propertyCount].bathrooms, properties[propertyCount].parking) == 7) {
        propertyCount++;
        if (propertyCount >= MAX_PROPERTIES) break;
    }
    fclose(file);
}

void loadFavorites() {
    FILE *file = fopen("favorites.txt", "r");
    if (!file) {
        return;
    }
    
    favoritesCount = 0;
    while (fscanf(file, "%d,%49[^,],%d,%d,%d,%d,%3s", &favorites[favoritesCount].id, favorites[favoritesCount].title, &favorites[favoritesCount].price,
                  &favorites[favoritesCount].size, &favorites[favoritesCount].rooms, &favorites[favoritesCount].bathrooms, favorites[favoritesCount].parking) == 7) {
        favoritesCount++;
        if (favoritesCount >= MAX_FAVORITES) break;
    }
    fclose(file);
}

void saveFavorites() {
    FILE *file = fopen("favorites.txt", "w");
    if (!file) {
        printf(COLOR_RED "Error: Could not save favorites.\n" COLOR_RESET);
        return;
    }
    
    for (int i = 0; i < favoritesCount; i++) {
        fprintf(file, "%d,%s,%d,%d,%d,%d,%s\n", favorites[i].id, favorites[i].title, favorites[i].price,
                favorites[i].size, favorites[i].rooms, favorites[i].bathrooms, favorites[i].parking);
    }
    fclose(file);
}

void addToFavorites(int propertyId) {
    for (int i = 0; i < favoritesCount; i++) {
        if (favorites[i].id == propertyId) {
            printf(COLOR_YELLOW "Property is already in favorites.\n" COLOR_RESET);
            return;
        }
    }
    
    for (int i = 0; i < propertyCount; i++) {
        if (properties[i].id == propertyId) {
            if (favoritesCount < MAX_FAVORITES) {
                favorites[favoritesCount] = properties[i];
                favoritesCount++;
                saveFavorites();
                printf(COLOR_GREEN "Property added to favorites successfully!\n" COLOR_RESET);
            } else {
                printf(COLOR_RED "Favorites list is full.\n" COLOR_RESET);
            }
            return;
        }
    }
    printf(COLOR_RED "Property not found.\n" COLOR_RESET);
}

void mainMenu() {
    int choice;
    while (1) {
        clearScreen();
        printf(COLOR_CYAN "\nReal Estate Buying/Selling System\n" COLOR_RESET);
        printf(COLOR_WHITE "1. Search Property Listings\n" COLOR_RESET);
        printf(COLOR_WHITE "2. View Favorites\n" COLOR_RESET);
        printf(COLOR_WHITE "3. Exit\n" COLOR_RESET);
        printf(COLOR_YELLOW "Enter your choice (1-3): " COLOR_RESET);
        
        choice = getValidInt("", 1, 3);
        
        switch (choice) {
            case 1:
                searchListings();
                break;
            case 2:
                viewFavorites();
                break;
            case 3:
                printf(COLOR_GREEN "Exiting the program.\n" COLOR_RESET);
                return;
        }
    }
}

void searchListings() {
    int choice;
    while (1) {
        clearScreen();
        printf(COLOR_CYAN "\nSearch Property Listings\n" COLOR_RESET);
        if (propertyCount == 0) {
            printf(COLOR_YELLOW "No properties available.\n" COLOR_RESET);
        } else {
            for (int i = 0; i < propertyCount; i++) {
                printf(COLOR_WHITE "%d. " COLOR_RESET, properties[i].id);
                printf(COLOR_BLUE "%s" COLOR_RESET, properties[i].title);
                printf(COLOR_WHITE " - " COLOR_RESET);
                printf(COLOR_GREEN "$%d" COLOR_RESET, properties[i].price);
                printf(COLOR_WHITE ", %d sqm, %d rooms, %d bathrooms, Parking: " COLOR_RESET, 
                       properties[i].size, properties[i].rooms, properties[i].bathrooms);
                printf(COLOR_MAGENTA "%s\n" COLOR_RESET, properties[i].parking);
            }
        }
        
        printf(COLOR_WHITE "\n1. Back to main menu\n" COLOR_RESET);
        printf(COLOR_WHITE "2. Add property to favorites\n" COLOR_RESET);
        printf(COLOR_YELLOW "Enter your choice: " COLOR_RESET);
        
        choice = getValidInt("", 1, 2);
        
        if (choice == 1) {
            return;
        } else if (choice == 2) {
            int propertyId;
            printf(COLOR_YELLOW "Enter the property ID to add to favorites: " COLOR_RESET);
            propertyId = getValidInt("", 1, MAX_PROPERTIES);
            addToFavorites(propertyId);
            printf(COLOR_WHITE "Press Enter to continue..." COLOR_RESET);
            getchar(); getchar();
        }
    }
}

void viewFavorites() {
    int choice;
    while (1) {
        clearScreen();
        printf(COLOR_CYAN "\nView Favorites\n" COLOR_RESET);
        if (favoritesCount == 0) {
            printf(COLOR_YELLOW "No favorite properties yet.\n" COLOR_RESET);
        } else {
            for (int i = 0; i < favoritesCount; i++) {
                printf(COLOR_WHITE "%d. " COLOR_RESET, favorites[i].id);
                printf(COLOR_BLUE "%s" COLOR_RESET, favorites[i].title);
                printf(COLOR_WHITE " - " COLOR_RESET);
                printf(COLOR_GREEN "$%d" COLOR_RESET, favorites[i].price);
                printf(COLOR_WHITE ", %d sqm, %d rooms, %d bathrooms, Parking: " COLOR_RESET, 
                       favorites[i].size, favorites[i].rooms, favorites[i].bathrooms);
                printf(COLOR_MAGENTA "%s\n" COLOR_RESET, favorites[i].parking);
            }
        }
        
        printf(COLOR_WHITE "\n1. Back to main menu\n" COLOR_RESET);
        printf(COLOR_YELLOW "Enter your choice: " COLOR_RESET);
        
        choice = getValidInt("", 1, 1);
        
        if (choice == 1) {
            return;
        }
    }
}

int main() {
    loadProperties();
    loadFavorites();
    mainMenu();
    return 0;
}