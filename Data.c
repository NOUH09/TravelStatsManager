#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char name[50];
    char country[50];
    float num_vist;
    char place[50];
} city_info;

typedef struct
{
    char name[50];
    char country[50];
    float num_vist;
    char place[50];
} city_information;

void displayCities(FILE *file, int *num_cities);
void fill_array(city_info *array, FILE *file, int *num_cities);
int ranking(city_info *array, int num_cities, char *Target);
int search_information(city_info *array, city_information *arr, char *Target2, int num_cities);
int update_city(city_info *array, int num_cities, float tourist, char *target3);
void change(city_info *pt1, city_info *pt2);
void sorting(city_info *array, int num_cities);
void create_file(FILE *target_file, city_info *array, int num_cities, char *Target4, int *check5);
int delete(city_info *array, int *num_cities, char *Target5);
int MENU(void)
{
    int choice;
    printf("CHOOSE AN OPTION FROM THE MENU:\n");
    printf("_______________MENU_____________\n");
    printf("1. View File Content\n2. Load File Data to an Array\n3. Get ranking of a city X\n4. Get Information about a city X\n5. Update the number of yearly tourists of a city X\n6. Find the most visited cities in a country X\n7. Remove a city from the ranking\n8. QUIT\n");
    scanf("%d", &choice);
    return choice;
}

void displayCities(FILE *file, int *num_cities)
{
    char line[100];
    int current_city = 0;
    getchar();
    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s", line);
        current_city++;

        if ((current_city % 25) == 0)
        {
            printf("Press Enter to continue:\n");
            getchar();
        }
    }
    *num_cities = current_city / 5;
}

void fill_array(city_info *array, FILE *pf, int *num_cities)
{
    int i = 0;
    char line[100];
    fseek(pf, 0, 0);
    while (!feof(pf) && i < 100)
    {
        fgets(array[i].name, 50, pf);
        size_t len = strlen(array[i].name);
        while (len > 0 && isspace(array[i].name[len - 1]))
        {
            array[i].name[len - 1] = '\0';
            len--;
        }
        fgets(array[i].country, 50, pf);
        size_t lenv = strlen(array[i].country);
        while (lenv > 0 && isspace(array[i].country[lenv - 1]))
        {
            array[i].country[lenv - 1] = '\0';
            lenv--;
        }
        fscanf(pf, "%f", &array[i].num_vist);
        fgets(line, 50, pf);
        fgets(array[i].place, 50, pf);
        fgets(line, 50, pf);
        i++;
    }
    *num_cities = i;
}
int ranking(city_info *array, int num_cities, char *Target)
{

    size_t en = strlen(Target);
    while (en > 0 && isspace(Target[en - 1]))
    {
        Target[en - 1] = '\0';
        en--;
    }

    for (int i = 0; i < num_cities; i++)
    {

        if (strcmp(Target, array[i].name) == 0)
        {
            return i + 1;
        }
    }
    return -1;
}

int search_information(city_info *array, city_information *arr, char *Target2, int num_cities)
{
    size_t en = strlen(Target2);
    while (en > 0 && isspace(Target2[en - 1]))
    {
        Target2[en - 1] = '\0';
        en--;
    }

    for (int i = 0; i < num_cities; i++)
    {
        if (strcmp(Target2, array[i].name) == 0)
        {
            strncpy(arr[0].name, array[i].name, sizeof(arr[0].name));
            strncpy(arr[0].country, array[i].country, sizeof(arr[0].country));
            arr[0].num_vist = array[i].num_vist;
            strncpy(arr[0].place, array[i].place, sizeof(arr[0].place));
            return i + 1;
        }
    }
    return -1;
}

int update_city(city_info *array, int num_cities, float tourist, char *Target3)
{
    size_t en = strlen(Target3);
    while (en > 0 && isspace(Target3[en - 1]))
    {
        Target3[en - 1] = '\0';
        en--;
    }
    for (int i = 0; i < num_cities; i++)
    {
        if (strcmp(Target3, array[i].name) == 0)
        {
            array[i].num_vist = tourist;
            sorting(array, num_cities);
            return i + 1;
        }
    }
    return -1;
}
void sorting(city_info *array, int num_cities)
{
    int swapped;
    for (int i = 0; i < num_cities - 1; i++)
    {
        swapped = 0;
        for (int j = 0; j < num_cities - i - 1; j++)
        {
            if (array[j].num_vist < array[j + 1].num_vist)
            {
                city_info temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
    }
}

void create_file(FILE *target_file, city_info *array, int num_cities, char *Target4, int *check5)
{
    int flag = 0;
    int i;

    for (i = 0; i < num_cities; i++)
    {
        if (strcmp(Target4, array[i].country) == 0)
        {
            target_file = fopen("country.txt", "w"); // Open the file in write mode to overwrite any existing data
            flag = 1;
            break;
        }
    }

    if (flag == 1)
    {

        for (i = 0; i < num_cities; i++)

        {
            if (strcmp(Target4, array[i].country) == 0)
            {

                fprintf(target_file, "%s, %0.3f, %s\n", array[i].name, array[i].num_vist, array[i].place);
            }
        }
    }

    if (flag == 1)
    {
        fclose(target_file);
        *check5 = 1; // File created successfully
    }
    else
    {
        *check5 = 0; // Country not found or no cities matching the country
    }
}

int delete(city_info *array, int *num_cities, char *Target5)
{
    for (int i = 0; i < (*num_cities); i++)
    {
        if (strcmp(Target5, array[i].name) == 0)
        {
            for (int j = i; j < (*num_cities) - 1; j++)
            {
                array[j] = array[j + 1];
            }
            (*num_cities)--;

            return 1;
        }
    }
    return -1;
}

int main(void)
{
    FILE *file;
    FILE *target_file;
    int num_cities;
    char str[4] = "YES";
    city_info array[100];
    city_information arr[1];
    int Flag = 0;
    char Target[50];  // will have the name of the city that we are looking for in the function 3
    char Target2[50]; // will have the name of the city that we are looking for in the function 4
    char Target3[50]; // will have the name of the city that we are looking to update the yearly tourist function 5
    char Target4[50]; // will have the name of the city that we are looking in which we will produce that file
    char Target5[50];
    int check;     // will have the ranking return by the 3 function
    int check2;    // will have the ranking returned by the 4 function
    int check3;    // will use to check if the city exist or not in the array
    int check4;    // will have the ranking of the city that we are looking for by the function 6
    int check5;    // will be used to check if the file was created succssefully
    float tourist; // will be to store the new number of tourist
    do
    {
        int choice = MENU();

        switch (choice)
        {
        case 1:
            file = fopen("data.txt", "r");
            if (file == NULL)
            {
                printf("Failed to open the file.\n");
                break;
            }
            displayCities(file, &num_cities);
            fclose(file);
            printf("The number of cities is %d\n", num_cities);
            printf("\n");
            break;
        case 2:
            file = fopen("data.txt", "r");
            if (file == NULL)
            {
                printf("Failed to open the file.\n");
                break;
            }
            else
            {
                fill_array(array, file, &num_cities);
            }
            fclose(file);
            Flag = 1;
            break;
        case 3:

            if (Flag == 1)
            {
                getchar();
                printf("ENTER THE CITY THAT YOU WANT HERE RANKING:\n");
                fgets(Target, sizeof(Target), stdin);
                check = ranking(array, num_cities, Target); // check have the ranking of the that we are looking for city
                if (check == -1)
                {
                    printf("The city that you are looking for don't exist\n");
                }
                else
                {
                    printf("The ranking of your city is %d\n", check);
                }
            }
            else
            {
                printf("YOU MUST OPEN CASE 2 BEFORE CHOOSING THE CHOICE FROM 3 TO 7\n");
            }

            break;
        case 4:
            getchar();
            printf("ENTER THE CITY THAT YOU ARE LOOKING FOR HERE INFORMATION:\n");
            fgets(Target2, sizeof(Target2), stdin);
            check2 = search_information(array, arr, Target2, num_cities);
            if (check2 != -1)
            {
                size_t leng = strlen(arr[0].country);
                while (leng > 0 && isspace(arr[0].country[leng - 1]))
                {
                    arr[0].country[leng - 1] = '\0';
                    leng--;
                }
                printf("%s is ranked# %d located in %s receiving %0.3f tourists yearly and the most visited place is %s", arr[0].name, check2, arr[0].country, arr[0].num_vist, arr[0].place);
            }
            else
                printf("THE CITY THAT YOUR ARE LOOKING FOR DOES NOT EXIST\n");
            break;
        case 5:
            if (Flag == 1)
            {
                getchar();
                printf("ENTER THE CITY THAT YOU WANNA UPDATE:\n");
                fgets(Target3, 50, stdin);
                size_t len = strlen(Target3);
                while (len > 0 && Target3[len - 1] == '\n')
                {
                    Target3[len - 1] = '\0'; // remove the \n and spaces
                }
                printf("ENTER THE NEW NUMBER OF VISITORS FOR THAT CITY IN FORM OF  0.0000\n");
                scanf("%f", &tourist);
                check3 = update_city(array, num_cities, tourist, Target3);
                if (check3 != -1)
                {
                    printf("THE CITY EXISTS, AND THE NUMBER OF VISITORS IS UPDATED\n");
                    sorting(array, num_cities);
                }
                else
                    printf("THE CITY THAT YOU ARE LOOKING FOR DOES NOT EXIST\n");
            }
            else
                printf("YOU MUST OPEN CASE 2 BEFORE CHOOSING THE CHOICE FROM 3 TO 7\n");
            break;
        case 6:
            if (Flag == 1)
            {
                getchar();
                printf("ENTER A COUNTRY:\n");
                fgets(Target4, 50, stdin);
                size_t lent = strlen(Target4);
                while (lent > 0 && Target4[lent - 1] == '\n')
                {
                    Target4[lent - 1] = '\0';
                }
                create_file(target_file, array, num_cities, Target4, &check5);
                if (check5 == 1)
                {
                    printf("THE COUNTRY EXIST AND FILE WAS CREATED SUCCESSFULLY\n");
                }
                else
                {
                    printf("THE COUNTRY DON'T EXIST AND FILE WASN'T CREATED SUCCESSFULLY\n");
                }
            }
            else
                printf("YOU MUST OPEN CASE 2 BEFORE CHOOSING THE CHOICE FROM 3 TO 7\n");
            break;
        case 7:
            getchar();
            if (Flag == 1)
            {
                printf("ENTER THE NAME OF CITY THAT YOU WANT TO DELETE \n");
                fgets(Target5, 50, stdin);
                size_t lentr = strlen(Target5);
                while (lentr > 0 && Target5[lentr - 1] == '\n')
                {
                    Target5[lentr - 1] = '\0';
                }

                check4 = delete (array, &num_cities, Target5);
                if (check4 == 1)
                {
                    printf("THE CITY EXIST AND IT WAS DELETE \n");
                }
                else
                    printf("THE CITY DON T EXIST\n");
            }
            else
                printf("YOU MUST OPEN CASE 2 BEFORE CHOOSING THE CHOICE FROM 3 TO 7\n");
            break;
        case 8:
            strcpy(str, "NO"); // change the value of str  to stop the loop
            break;

        default:
            printf("Invalid choice. Please choose a valid option.\n");
        }
    } while (strcmp(str, "YES") == 0);

    return 0;
}
