#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

// Structure to store student information
struct Student {
    int studentNumber;
    char name[50];
    float midtermGrade;
    float finalGrade;
    float average;
};

// Global variables
struct Student* students[MAX_STUDENTS];
int numStudents = 0;

// Function prototypes
void addNewRecord();
void listRecords();
void updateRecord();
void calculateClassAverage();
void showBestStudentRecord();

int main() {
    int choice;

    while (1) {
        printf("\nMain Menu:\n");
        printf("1- Add New Record\n");
        printf("2- List Records\n");
        printf("3- Update Record\n");
        printf("4- Calculate Class Average\n");
        printf("5- Show Best Student Record According to Average\n");
        printf("6- Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 1:
                addNewRecord();
                break;
            case 2:
                listRecords();
                break;
            case 3:
                updateRecord();
                break;
            case 4:
                calculateClassAverage();
                break;
            case 5:
                showBestStudentRecord();
                break;
            case 6:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void addNewRecord() {
    if (numStudents >= MAX_STUDENTS) {
        printf("Maximum number of students reached.\n");
        return;
    }

    students[numStudents] = (struct Student*)malloc(sizeof(struct Student));

    printf("Enter student number: ");
    scanf("%d", &students[numStudents]->studentNumber);
    printf("Enter student name: ");
    scanf("%s", students[numStudents]->name);
    printf("Enter midterm grade: ");
    scanf("%f", &students[numStudents]->midtermGrade);
    printf("Enter final grade: ");
    scanf("%f", &students[numStudents]->finalGrade);

    // Calculate average
    students[numStudents]->average = (students[numStudents]->midtermGrade + students[numStudents]->finalGrade) / 2.0;

    numStudents++;
    printf("Record added successfully.\n\n");
}

void listRecords() {
    int i, j;
    int choice;
    float lowerLimit, upperLimit;

    if (numStudents == 0) {
        printf("No records to list.\n");
        return;
    }

    printf("List Records Menu:\n");
    printf("1- List by Student Number\n");
    printf("2- List by Average Grade\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    printf("\n");

    switch (choice) {
        case 1:
            // Sort by student number
            for (i = 0; i < numStudents - 1; i++) {
                for (j = 0; j < numStudents - i - 1; j++) {
                    if (students[j]->studentNumber > students[j + 1]->studentNumber) {
                        struct Student* temp = students[j];
                        students[j] = students[j + 1];
                        students[j + 1] = temp;
                    }
                }
            }
            break;
        case 2:
            // Sort by average grade
            for (i = 0; i < numStudents - 1; i++) {
                for (j = 0; j < numStudents - i - 1; j++) {
                    if (students[j]->average < students[j + 1]->average) {
                        struct Student* temp = students[j];
                        students[j] = students[j + 1];
                        students[j + 1] = temp;
                    }
                }
            }
            break;
        default:
            printf("Invalid choice.\n");
            return;
    }

    printf("Enter lower limit for grade filtering (or -1 to skip): ");
    scanf("%f", &lowerLimit);
    printf("Enter upper limit for grade filtering (or -1 to skip): ");
    scanf("%f", &upperLimit);

    printf("\nStudent Records:\n");
    printf("Student Number\tName\tMidterm Grade\tFinal Grade\tAverage Grade\n");
    for (i = 0; i < numStudents; i++) {
        if ((lowerLimit == -1 || students[i]->average >= lowerLimit) &&
            (upperLimit == -1 || students[i]->average <= upperLimit)) {
            printf("%d\t\t%s\t%.2f\t\t%.2f\t\t%.2f\n", students[i]->studentNumber,
                   students[i]->name, students[i]->midtermGrade, students[i]->finalGrade, students[i]->average);
        }
    }
    printf("\n\n");
}

void updateRecord() {
    int studentNumber, i;
    printf("Enter student number to update: ");
    scanf("%d", &studentNumber);

    for (i = 0; i < numStudents; i++) {
        if (students[i]->studentNumber == studentNumber) {
            printf("Enter new midterm grade: ");
            scanf("%f", &students[i]->midtermGrade);
            printf("Enter new final grade: ");
            scanf("%f", &students[i]->finalGrade);

            // Recalculate average
            students[i]->average = (students[i]->midtermGrade + students[i]->finalGrade) / 2.0;

            printf("Record updated successfully.\n");
            return;
        }
    }

    printf("Student not found.\n\n");
}

void calculateClassAverage() {
    int i;
    float totalAverage = 0;

    if (numStudents == 0) {
        printf("No records to calculate class average.\n");
        return;
    }

    for (i = 0; i < numStudents; i++) {
        totalAverage += students[i]->average;
    }

    float classAverage = totalAverage / numStudents;
    printf("Class Average: %.2f\n\n", classAverage);
}

void showBestStudentRecord() {
    int i;
    float maxAverage = 0;
    int bestStudentIndex = -1;

    if (numStudents == 0) {
        printf("No records to show best student.\n");
        return;
    }

    for (i = 0; i < numStudents; i++) {
        if (students[i]->average > maxAverage) {
            maxAverage = students[i]->average;
            bestStudentIndex = i;
        }
    }

    if (bestStudentIndex != -1) {
        printf("Best Student Record According to Average:\n");
        printf("Student Number\tName\tMidterm Grade\tFinal Grade\tAverage Grade\n");
        printf("%d\t\t%s\t%.2f\t\t%.2f\t\t%.2f\n", students[bestStudentIndex]->studentNumber);

    }
    printf("\n\n");
}
