#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROPERTIES 100
#define MAX_FAVORITES 50

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

Property properties[MAX_PROPERTIES];
Property favorites[MAX_FAVORITES];
int propertyCount = 0;
int favoritesCount = 0;

void loadProperties() {
    FILE *file = fopen("properties.txt", "r");
    if (!file) {
        printf("Error: Could not open properties.txt.\n");
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
        printf("Error: Could not save favorites.\n");
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
            printf("Property is already in favorites.\n");
            return;
        }
    }
    
    for (int i = 0; i < propertyCount; i++) {
        if (properties[i].id == propertyId) {
            if (favoritesCount < MAX_FAVORITES) {
                favorites[favoritesCount] = properties[i];
                favoritesCount++;
                saveFavorites();
                printf("Property added to favorites successfully!\n");
            } else {
                printf("Favorites list is full.\n");
            }
            return;
        }
    }
    printf("Property not found.\n");
}

void mainMenu() {
    int choice;
    while (1) {
        clearScreen();
        printf("\nReal Estate Buying/Selling System\n");
        printf("1. Search Property Listings\n");
        printf("2. View Favorites\n");
        printf("3. Exit\n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                searchListings();
                break;
            case 2:
                viewFavorites();
                break;
            case 3:
                printf("Exiting the program.\n");
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void searchListings() {
    int choice;
    while (1) {
        clearScreen();
        printf("\nSearch Property Listings\n");
        if (propertyCount == 0) {
            printf("No properties available.\n");
        } else {
            for (int i = 0; i < propertyCount; i++) {
                printf("%d. %s - $%d, %d sqm, %d rooms, %d bathrooms, Parking: %s\n", 
                       properties[i].id, properties[i].title, properties[i].price,
                       properties[i].size, properties[i].rooms, properties[i].bathrooms, properties[i].parking);
            }
        }
        
        printf("\n1. Back to main menu\n");
        printf("2. Add property to favorites\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            return;
        } else if (choice == 2) {
            int propertyId;
            printf("Enter the property ID to add to favorites: ");
            scanf("%d", &propertyId);
            addToFavorites(propertyId);
            printf("Press Enter to continue...");
            getchar(); getchar();
        }
    }
}

void viewFavorites() {
    int choice;
    while (1) {
        clearScreen();
        printf("\nView Favorites\n");
        if (favoritesCount == 0) {
            printf("No favorite properties yet.\n");
        } else {
            for (int i = 0; i < favoritesCount; i++) {
                printf("%d. %s - $%d, %d sqm, %d rooms, %d bathrooms, Parking: %s\n", 
                       favorites[i].id, favorites[i].title, favorites[i].price,
                       favorites[i].size, favorites[i].rooms, favorites[i].bathrooms, favorites[i].parking);
            }
        }
        
        printf("\n1. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
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