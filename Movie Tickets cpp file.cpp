#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Movie {
    char theatrename[100];
    char moviename1[100];
    char *showtime1; // HH:MM
    char *showtime2;
    char *showtime3;
    int start_date;
    int start_month;
    int start_year; // DD-MM-YYYY
    int end_date;
    int end_month;
    int end_year;
} details;

void add_theatres_data();
void list_of_theatres();
void movie_available();
void range_of_dates();

int main() {
    int choice;

    do {
    	printf("\t\t\t\t\t***************************\n");
        printf("\t\t\t\t\t***** Movies in a city*****\n");
        printf("\t\t\t\t\t1. Add theatres list\n");
        printf("\t\t\t\t\t2. List of all theatres\n");
        printf("\t\t\t\t\t3. Movies available on a particular date\n");
        printf("\t\t\t\t\t4. Movies available in a date range\n");
        printf("\t\t\t\t\t5. Exit the program\n");
        printf("\t\t\t\t\tEnter your choice: ");
        scanf("\t\t\t\t\t%d", &choice);

        switch (choice) {
            case 1:
                add_theatres_data();
                break;
            case 2:
                list_of_theatres();
                break;
            case 3:
                movie_available();
                break;
            case 4:
                range_of_dates();
                break;
            case 5:
                printf("Exit the program.\n");
                break;
            default:
                printf("Your choice doesn't match.\n");
                break;
        }

    } while (choice != 5);

    // Don't forget to free allocated memory
    free(details.showtime1);
    free(details.showtime2);
    free(details.showtime3);

    return 0;
}

void add_theatres_data() {
    int i, num;
    FILE *fp;

    fp = fopen("121.bin", "ab+");
    if (fp == NULL) {
        printf("ERROR..! File cannot be opened.\n");
        return;
    }

    printf("Enter the number of theatres: ");
    scanf("%d", &num);

    for (i = 0; i < num; i++) {
        struct Movie details;

        details.showtime1 = (char *)malloc(6 * sizeof(char));
        details.showtime2 = (char *)malloc(6 * sizeof(char));
        details.showtime3 = (char *)malloc(6 * sizeof(char));

        printf("\nEnter theatre name: ");
        fflush(stdin); // Clear input buffer
        gets(details.theatrename);

        printf("Enter the date of movie coming into theatre (DD MM YYYY): ");
        scanf("%d %d %d", &details.start_date, &details.start_month, &details.start_year);

        printf("Enter the date of movie going out from theatre (DD MM YYYY): ");
        scanf("%d %d %d", &details.end_date, &details.end_month, &details.end_year);

        printf("Enter movie name 1: ");
        fflush(stdin); // Clear input buffer
        gets(details.moviename1);

        printf("\nShow 1 is at: ");
        fflush(stdin); // Clear input buffer
        gets(details.showtime1);

        printf("Show 2 is at: ");
        fflush(stdin); // Clear input buffer
        gets(details.showtime2);

        printf("Show 3 is at: ");
        fflush(stdin); // Clear input buffer
        gets(details.showtime3);

        fwrite(&details, sizeof(struct Movie), 1, fp);

        printf("\n-------------------------------------------------------\n");
    }

    fclose(fp);
    printf("\nYou entered data is stored successfully.\n");
}

void list_of_theatres() {
    FILE *fp;

    fp = fopen("121.bin", "ab+");
    if (fp == NULL) {
        printf("ERROR..! File cannot be opened.\n");
        return;
    }

    while (fread(&details, sizeof(struct Movie), 1, fp) == 1) {
        printf("\n");
        printf("Theatre name: %s\n", details.theatrename);
        printf("RUNNING DAYs	%d-%d-%d TO %d-%d-%d\n", details.start_date, details.start_month, details.start_year, details.end_date, details.end_month, details.end_year);
        printf("Movie name is:%s\n", details.moviename1);
        printf("Show 1 is at %s\t", details.showtime1);
        printf("Show 2 is at %s\t", details.showtime2);
        printf("Show 3 is at %s\t", details.showtime3);
        printf("\n \n");
        printf("-------------------------------------------------------\n");
    }

    fclose(fp);
}

void movie_available() {
    FILE *fp;
    struct Movie id;
    int searchdate, searchmonth, searchyear;

    printf("Enter the particular date to find the movie (DD MM YYYY): ");
    scanf("%d %d %d", &searchdate, &searchmonth, &searchyear);

    fp = fopen("121.bin", "rb+");

    if (fp == NULL) {
        printf("ERROR..! File cannot be opened.\n");
        return;
    }

    while (fread(&id, sizeof(struct Movie), 1, fp) == 1) {
        if (id.start_date <= searchdate && searchdate <= id.end_date && id.start_month <= searchmonth && searchmonth <= id.end_month && id.start_year <= searchyear && searchyear <= id.start_year) {
            printf("\nTheatre name: %s", id.theatrename);
            printf("\nMovie name: %s", id.moviename1);
             printf("RUNNING DAYs	%d-%d-%d TO %d-%d-%d\n", details.start_date, details.start_month, details.start_year, details.end_date, details.end_month, details.end_year);
            printf("\nShow 1 is at %s\t", id.showtime1);
            printf("\nShow 2 is at %s\t", id.showtime2);
            printf("\nShow 3 is at %s\t\n", id.showtime3);
            puts(".......................................................");
        }
    }

    fclose(fp);
}

void range_of_dates() {
    FILE *fp;
    int startdt, stopdt, startmon, startyr, stopmon, stopyr;
    struct Movie id;

    printf("Enter the start range (DD MM YYYY): ");
    scanf("%d %d %d", &startdt, &startmon, &startyr);
    printf("Enter the stop range (DD MM YYYY): ");
    scanf("%d %d %d", &stopdt, &stopmon, &stopyr);

    fp = fopen("121.bin", "rb+");

    if (fp == NULL) {
        printf("ERROR..! File cannot be opened.\n");
        return;
    }

    while (fread(&id, sizeof(struct Movie), 1, fp) == 1) {
        if ((startdt >= id.start_date) ){
            printf("\nTheatre name: %s\n", id.theatrename);
            printf("\nMovie name: %s\n", id.moviename1);
            printf("RUNNING DAYs	%d-%d-%d TO %d-%d-%d\n", details.start_date, details.start_month, details.start_year, details.end_date, details.end_month, details.end_year);
            printf("\nShow 1 is at %s\t", id.showtime1);
            printf("\nShow 2 is at %s\t", id.showtime2);
            printf("\nShow 3 is at %s\t", id.showtime3);

            printf("\n-------------------------------------------------------\n");
        }
    }

    fclose(fp);
}
