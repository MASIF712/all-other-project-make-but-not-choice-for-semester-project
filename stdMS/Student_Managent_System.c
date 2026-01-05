#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define current_subject 6
#define number_test 10
#define MAX_STUDENTS 100

struct student {
    int reg_number;
    int current_semester;
    float C_GPA;
    float marks;
    char name[50];
    char department[50];
    char section[5];
    char address[100];
    char phone_number[15];
    char email[50];
    char date_of_birth[15];
    char gender[10];
    int attendance_percentage;
    int extracurricular_activities;
    int disciplinary_actions;
    int library_fines;
    int hostel_room_number;
    int admission_year;
    int graduation_year;
    int scholarship_status;
    int internship_details;
    int placement_status;
    int alumni_status;
};

struct student students[MAX_STUDENTS];
int student_count = 0;

void displayMenu() {
    printf("\n========== STUDENT MANAGEMENT SYSTEM ==========\n");
    printf("1. Add New Student\n");
    printf("2. View Student Details\n");
    printf("3. Update Student Details\n");
    printf("4. Delete Student\n");
    printf("5. Display All Students\n");
    printf("6. Search Student\n");
    printf("7. Calculate GPA Statistics\n");
    printf("8. Exit\n");
    printf("===============================================\n");
    printf("Enter your choice: ");
}

void addStudent() {
    if (student_count >= MAX_STUDENTS) {
        printf("Cannot add more students. Maximum limit reached.\n");
        return;
    }
    
    struct student s;
    printf("\n--- Add New Student ---\n");
    printf("Enter student registration number: ");
    scanf("%d", &s.reg_number);
    
    printf("Enter student name: ");
    scanf("%s", s.name);
    
    printf("Enter student department: ");
    scanf("%s", s.department);
    
    printf("Enter student section: ");
    scanf("%s", s.section);
    
    printf("Enter current semester: ");
    scanf("%d", &s.current_semester);
    
    printf("Enter C_GPA: ");
    scanf("%f", &s.C_GPA);
    
    printf("Enter total marks: ");
    scanf("%f", &s.marks);
    
    printf("Enter attendance percentage: ");
    scanf("%d", &s.attendance_percentage);
    
    printf("Enter phone number: ");
    scanf("%s", s.phone_number);
    
    printf("Enter email: ");
    scanf("%s", s.email);
    
    printf("Enter address: ");
    scanf("%s", s.address);
    
    printf("Enter date of birth (DD/MM/YYYY): ");
    scanf("%s", s.date_of_birth);
    
    printf("Enter gender: ");
    scanf("%s", s.gender);
    
    printf("Enter admission year: ");
    scanf("%d", &s.admission_year);
    
    printf("Enter graduation year: ");
    scanf("%d", &s.graduation_year);
    
    printf("Scholarship status (0=No, 1=Yes): ");
    scanf("%d", &s.scholarship_status);
    
    printf("Internship details (0=No, 1=Yes): ");
    scanf("%d", &s.internship_details);
    
    printf("Placement status (0=Not Placed, 1=Placed): ");
    scanf("%d", &s.placement_status);
    
    printf("Extracurricular activities count: ");
    scanf("%d", &s.extracurricular_activities);
    
    printf("Disciplinary actions count: ");
    scanf("%d", &s.disciplinary_actions);
    
    printf("Library fines amount: ");
    scanf("%d", &s.library_fines);
    
    printf("Hostel room number: ");
    scanf("%d", &s.hostel_room_number);
    
    students[student_count++] = s;
    printf("Student added successfully!\n");
}

void viewStudent() {
    int reg_num;
    printf("\nEnter registration number to search: ");
    scanf("%d", &reg_num);
    
    for (int i = 0; i < student_count; i++) {
        if (students[i].reg_number == reg_num) {
            printf("\n--- Student Details ---\n");
            printf("Registration Number: %d\n", students[i].reg_number);
            printf("Name: %s\n", students[i].name);
            printf("Department: %s\n", students[i].department);
            printf("Section: %s\n", students[i].section);
            printf("Current Semester: %d\n", students[i].current_semester);
            printf("C_GPA: %.2f\n", students[i].C_GPA);
            printf("Total Marks: %.2f\n", students[i].marks);
            printf("Attendance: %d%%\n", students[i].attendance_percentage);
            printf("Phone: %s\n", students[i].phone_number);
            printf("Email: %s\n", students[i].email);
            printf("Address: %s\n", students[i].address);
            printf("Date of Birth: %s\n", students[i].date_of_birth);
            printf("Gender: %s\n", students[i].gender);
            printf("Admission Year: %d\n", students[i].admission_year);
            printf("Graduation Year: %d\n", students[i].graduation_year);
            printf("Scholarship: %s\n", students[i].scholarship_status ? "Yes" : "No");
            printf("Internship: %s\n", students[i].internship_details ? "Yes" : "No");
            printf("Placement: %s\n", students[i].placement_status ? "Placed" : "Not Placed");
            printf("Hostel Room: %d\n", students[i].hostel_room_number);
            return;
        }
    }
    printf("Student not found!\n");
}

void updateStudent() {
    int reg_num;
    printf("\nEnter registration number to update: ");
    scanf("%d", &reg_num);
    
    for (int i = 0; i < student_count; i++) {
        if (students[i].reg_number == reg_num) {
            printf("\nWhat do you want to update?\n");
            printf("1. C_GPA\n2. Attendance\n3. Marks\n");
            int choice;
            scanf("%d", &choice);
            
            switch (choice) {
                case 1:
                    printf("Enter new C_GPA: ");
                    scanf("%f", &students[i].C_GPA);
                    break;
                case 2:
                    printf("Enter new attendance percentage: ");
                    scanf("%d", &students[i].attendance_percentage);
                    break;
                case 3:
                    printf("Enter new marks: ");
                    scanf("%f", &students[i].marks);
                    break;
                default:
                    printf("Invalid choice!\n");
                    return;
            }
            printf("Student updated successfully!\n");
            return;
        }
    }
    printf("Student not found!\n");
}

void deleteStudent() {
    int reg_num;
    printf("\nEnter registration number to delete: ");
    scanf("%d", &reg_num);
    
    for (int i = 0; i < student_count; i++) {
        if (students[i].reg_number == reg_num) {
            for (int j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;
            printf("Student deleted successfully!\n");
            return;
        }
    }
    printf("Student not found!\n");
}

void displayAllStudents() {
    if (student_count == 0) {
        printf("No students in the system.\n");
        return;
    }
    
    printf("\n--- All Students ---\n");
    printf("%-8s %-20s %-15s %-10s\n", "Reg No", "Name", "Department", "C_GPA");
    printf("---------------------------------------------------------\n");
    
    for (int i = 0; i < student_count; i++) {
        printf("%-8d %-20s %-15s %-10.2f\n", 
               students[i].reg_number, 
               students[i].name, 
               students[i].department, 
               students[i].C_GPA);
    }
}

void searchStudent() {
    char name[50];
    printf("\nEnter student name to search: ");
    scanf("%s", name);
    
    int found = 0;
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("\nFound - Registration Number: %d, Department: %s, C_GPA: %.2f\n",
                   students[i].reg_number, students[i].department, students[i].C_GPA);
            found = 1;
        }
    }
    if (!found) {
        printf("No student with that name found.\n");
    }
}

void calculateStatistics() {
    if (student_count == 0) {
        printf("No students in the system.\n");
        return;
    }
    
    float totalGPA = 0, totalMarks = 0;
    float maxGPA = students[0].C_GPA, minGPA = students[0].C_GPA;
    
    for (int i = 0; i < student_count; i++) {
        totalGPA += students[i].C_GPA;
        totalMarks += students[i].marks;
        if (students[i].C_GPA > maxGPA) maxGPA = students[i].C_GPA;
        if (students[i].C_GPA < minGPA) minGPA = students[i].C_GPA;
    }
    
    printf("\n--- GPA Statistics ---\n");
    printf("Total Students: %d\n", student_count);
    printf("Average GPA: %.2f\n", totalGPA / student_count);
    printf("Total Marks: %.2f\n", totalMarks);
    printf("Highest GPA: %.2f\n", maxGPA);
    printf("Lowest GPA: %.2f\n", minGPA);
    printf("Average Marks: %.2f\n", totalMarks / student_count);
}

int main(void) {
    int choice;
    
    printf("\n========================================\n");
    printf("  WELCOME TO STUDENT MANAGEMENT SYSTEM  \n");
    printf("========================================\n");
    
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudent();
                break;
            case 3:
                updateStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                displayAllStudents();
                break;
            case 6:
                searchStudent();
                break;
            case 7:
                calculateStatistics();
                break;
            case 8:
                printf("\nThank you for using Student Management System!\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}