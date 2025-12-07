// gui.c
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "student.h"

// Control IDs
#define IDC_EDIT_ID       1001
#define IDC_EDIT_NAME     1002
#define IDC_EDIT_AGE      1003
#define IDC_EDIT_GENDER   1004
#define IDC_EDIT_ADDRESS  1005
#define IDC_EDIT_PHONE    1006
#define IDC_EDIT_EMAIL    1007
#define IDC_EDIT_MATH     1008
#define IDC_EDIT_PHYS     1009
#define IDC_EDIT_CHEM     1010
#define IDC_EDIT_ENG      1011
#define IDC_EDIT_COMP     1012
#define IDC_EDIT_OUTPUT   1013

#define ID_BTN_ADD        2001
#define ID_BTN_SEARCH     2002
#define ID_BTN_UPDATE     2003
#define ID_BTN_DELETE     2004
#define ID_BTN_DISPLAY    2005
#define ID_BTN_CLEAR      2006
#define ID_BTN_EXIT       2007

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Helpers
void SetStudentToForm(HWND hwnd, const Student *s);
int  GetStudentFromForm(HWND hwnd, Student *s, int requireIdForUpdate);
void ClearForm(HWND hwnd);
void ShowAllStudents(HWND hwnd);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrev,
                   LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc = {0};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = "StudentRecordWindowClass";
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Failed to register window class!", "Error", MB_ICONERROR);
        return 0;
    }

    HWND hwnd = CreateWindow(
        "StudentRecordWindowClass",
        "Student Record Management System",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        900, 600,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) {
        MessageBox(NULL, "Failed to create window!", "Error", MB_ICONERROR);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_CREATE:
    {
        // Labels + fields
        CreateWindow("STATIC", "ID:",
                     WS_VISIBLE | WS_CHILD,
                     20, 20, 50, 20,
                     hwnd, NULL, NULL, NULL);
        CreateWindow("EDIT", "",
                     WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                     80, 20, 80, 20,
                     hwnd, (HMENU)IDC_EDIT_ID, NULL, NULL);

        CreateWindow("STATIC", "Name:",
                     WS_VISIBLE | WS_CHILD,
                     180, 20, 50, 20,
                     hwnd, NULL, NULL, NULL);
        CreateWindow("EDIT", "",
                     WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                     240, 20, 200, 20,
                     hwnd, (HMENU)IDC_EDIT_NAME, NULL, NULL);

        CreateWindow("STATIC", "Age:",
                     WS_VISIBLE | WS_CHILD,
                     460, 20, 40, 20,
                     hwnd, NULL, NULL, NULL);
        CreateWindow("EDIT", "",
                     WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                     510, 20, 50, 20,
                     hwnd, (HMENU)IDC_EDIT_AGE, NULL, NULL);

        CreateWindow("STATIC", "Gender (M/F):",
                     WS_VISIBLE | WS_CHILD,
                     580, 20, 100, 20,
                     hwnd, NULL, NULL, NULL);
        CreateWindow("EDIT", "",
                     WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                     690, 20, 40, 20,
                     hwnd, (HMENU)IDC_EDIT_GENDER, NULL, NULL);

        CreateWindow("STATIC", "Address:",
                     WS_VISIBLE | WS_CHILD,
                     20, 60, 60, 20,
                     hwnd, NULL, NULL, NULL);
        CreateWindow("EDIT", "",
                     WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                     80, 60, 300, 20,
                     hwnd, (HMENU)IDC_EDIT_ADDRESS, NULL, NULL);

        CreateWindow("STATIC", "Phone:",
                     WS_VISIBLE | WS_CHILD,
                     400, 60, 50, 20,
                     hwnd, NULL, NULL, NULL);
        CreateWindow("EDIT", "",
                     WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                     460, 60, 150, 20,
                     hwnd, (HMENU)IDC_EDIT_PHONE, NULL, NULL);

        CreateWindow("STATIC", "Email:",
                     WS_VISIBLE | WS_CHILD,
                     630, 60, 50, 20,
                     hwnd, NULL, NULL, NULL);
        CreateWindow("EDIT", "",
                     WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                     690, 60, 180, 20,
                     hwnd, (HMENU)IDC_EDIT_EMAIL, NULL, NULL);

        // Marks
        CreateWindow("STATIC", "Math:",
                     WS_VISIBLE | WS_CHILD,
                     20, 100, 50, 20,
                     hwnd, NULL, NULL, NULL);
        CreateWindow("EDIT", "",
                     WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                     80, 100, 60, 20,
                     hwnd, (HMENU)IDC_EDIT_MATH, NULL, NULL);

        CreateWindow("STATIC", "Physics:",
                     WS_VISIBLE | WS_CHILD,
                     160, 100, 60, 20,
                     hwnd, NULL, NULL, NULL);
        CreateWindow("EDIT", "",
                     WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                     230, 100, 60, 20,
                     hwnd, (HMENU)IDC_EDIT_PHYS, NULL, NULL);

        CreateWindow("STATIC", "Chemistry:",
                     WS_VISIBLE | WS_CHILD,
                     310, 100, 70, 20,
                     hwnd, NULL, NULL, NULL);
        CreateWindow("EDIT", "",
                     WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                     390, 100, 60, 20,
                     hwnd, (HMENU)IDC_EDIT_CHEM, NULL, NULL);

        CreateWindow("STATIC", "English:",
                     WS_VISIBLE | WS_CHILD,
                     470, 100, 60, 20,
                     hwnd, NULL, NULL, NULL);
        CreateWindow("EDIT", "",
                     WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                     540, 100, 60, 20,
                     hwnd, (HMENU)IDC_EDIT_ENG, NULL, NULL);

        CreateWindow("STATIC", "Computer:",
                     WS_VISIBLE | WS_CHILD,
                     620, 100, 70, 20,
                     hwnd, NULL, NULL, NULL);
        CreateWindow("EDIT", "",
                     WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                     700, 100, 60, 20,
                     hwnd, (HMENU)IDC_EDIT_COMP, NULL, NULL);

        // Buttons
        CreateWindow("BUTTON", "Add",
                     WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                     20, 140, 80, 30,
                     hwnd, (HMENU)ID_BTN_ADD, NULL, NULL);

        CreateWindow("BUTTON", "Search",
                     WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                     120, 140, 80, 30,
                     hwnd, (HMENU)ID_BTN_SEARCH, NULL, NULL);

        CreateWindow("BUTTON", "Update",
                     WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                     220, 140, 80, 30,
                     hwnd, (HMENU)ID_BTN_UPDATE, NULL, NULL);

        CreateWindow("BUTTON", "Delete",
                     WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                     320, 140, 80, 30,
                     hwnd, (HMENU)ID_BTN_DELETE, NULL, NULL);

        CreateWindow("BUTTON", "Display All",
                     WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                     420, 140, 100, 30,
                     hwnd, (HMENU)ID_BTN_DISPLAY, NULL, NULL);

        CreateWindow("BUTTON", "Clear",
                     WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                     540, 140, 80, 30,
                     hwnd, (HMENU)ID_BTN_CLEAR, NULL, NULL);

        CreateWindow("BUTTON", "Exit",
                     WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                     640, 140, 80, 30,
                     hwnd, (HMENU)ID_BTN_EXIT, NULL, NULL);

        // Output box
        CreateWindow("STATIC", "Records / Output:",
                     WS_VISIBLE | WS_CHILD,
                     20, 190, 120, 20,
                     hwnd, NULL, NULL, NULL);
        CreateWindow("EDIT", "",
                     WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT |
                     ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | ES_READONLY,
                     20, 220, 840, 320,
                     hwnd, (HMENU)IDC_EDIT_OUTPUT, NULL, NULL);
    }
    break;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_BTN_ADD:
        {
            Student s;
            if (!GetStudentFromForm(hwnd, &s, 0)) {
                MessageBox(hwnd, "Please fill all required fields correctly.",
                           "Input Error", MB_ICONWARNING);
                break;
            }

            if (!addStudentToFile(&s)) {
                MessageBox(hwnd, "Failed to add student.",
                           "Error", MB_ICONERROR);
            } else {
                char msg[256];
                sprintf(msg, "Student added.\nID: %d\nTotal: %.2f\nPercentage: %.2f%%\nGrade: %c",
                        s.id, s.total, s.percentage, s.grade);
                MessageBox(hwnd, msg, "Success", MB_ICONINFORMATION);
                SetStudentToForm(hwnd, &s);  // update ID + marks
            }
        }
        break;

        case ID_BTN_SEARCH:
        {
            char buf[32];
            GetWindowText(GetDlgItem(hwnd, IDC_EDIT_ID), buf, sizeof(buf));
            int id = atoi(buf);
            if (id <= 0) {
                MessageBox(hwnd, "Please enter a valid ID for search.",
                           "Input Error", MB_ICONWARNING);
                break;
            }

            Student s;
            HWND hOut = GetDlgItem(hwnd, IDC_EDIT_OUTPUT);

            if (findStudentById(id, &s)) {
                char out[1024];
                sprintf(out,
                    "ID: %d\r\n"
                    "Name: %s\r\n"
                    "Age: %d, Gender: %c\r\n"
                    "Address: %s\r\n"
                    "Phone: %s, Email: %s\r\n"
                    "Marks - Math: %.2f, Physics: %.2f, Chemistry: %.2f, English: %.2f, Computer: %.2f\r\n"
                    "Total: %.2f / 500, Percentage: %.2f%%, Grade: %c\r\n"
                    "---------------------------------------------\r\n\r\n",
                    s.id, s.name, s.age, s.gender,
                    s.address, s.phone, s.email,
                    s.math, s.physics, s.chemistry, s.english, s.computer,
                    s.total, s.percentage, s.grade);

                SetWindowText(hOut, out);  // only show here
            } else {
                SetWindowText(hOut, "Student not found.");
            }
        }
        break;

        case ID_BTN_UPDATE:
        {
            Student s;
            if (!GetStudentFromForm(hwnd, &s, 1)) {
                MessageBox(hwnd, "Please enter a valid ID and all fields.",
                           "Input Error", MB_ICONWARNING);
                break;
            }
            calculateMarks(&s);
            if (updateStudentInFile(&s)) {
                MessageBox(hwnd, "Student record updated.",
                           "Success", MB_ICONINFORMATION);
            } else {
                MessageBox(hwnd, "Student ID not found.",
                           "Error", MB_ICONERROR);
            }
        }
        break;

        case ID_BTN_DELETE:
        {
            char buf[32];
            GetWindowText(GetDlgItem(hwnd, IDC_EDIT_ID), buf, sizeof(buf));
            int id = atoi(buf);
            if (id <= 0) {
                MessageBox(hwnd, "Please enter a valid ID to delete.",
                           "Input Error", MB_ICONWARNING);
                break;
            }

            if (deleteStudentFromFile(id)) {
                MessageBox(hwnd, "Student record deleted.",
                           "Success", MB_ICONINFORMATION);
                ClearForm(hwnd);
            } else {
                MessageBox(hwnd, "Student ID not found.",
                           "Error", MB_ICONERROR);
            }
        }
        break;

        case ID_BTN_DISPLAY:
            ShowAllStudents(hwnd);
            break;

        case ID_BTN_CLEAR:
            ClearForm(hwnd);
            SetWindowText(GetDlgItem(hwnd, IDC_EDIT_OUTPUT), "");
            break;

        case ID_BTN_EXIT:
            PostQuitMessage(0);
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// ------- Helpers ---------

void SetStudentToForm(HWND hwnd, const Student *s) {
    char buf[256];

    sprintf(buf, "%d", s->id);
    SetWindowText(GetDlgItem(hwnd, IDC_EDIT_ID), buf);
    SetWindowText(GetDlgItem(hwnd, IDC_EDIT_NAME), s->name);
    sprintf(buf, "%d", s->age);
    SetWindowText(GetDlgItem(hwnd, IDC_EDIT_AGE), buf);

    buf[0] = s->gender;
    buf[1] = '\0';
    SetWindowText(GetDlgItem(hwnd, IDC_EDIT_GENDER), buf);

    SetWindowText(GetDlgItem(hwnd, IDC_EDIT_ADDRESS), s->address);
    SetWindowText(GetDlgItem(hwnd, IDC_EDIT_PHONE), s->phone);
    SetWindowText(GetDlgItem(hwnd, IDC_EDIT_EMAIL), s->email);

    sprintf(buf, "%.2f", s->math);
    SetWindowText(GetDlgItem(hwnd, IDC_EDIT_MATH), buf);
    sprintf(buf, "%.2f", s->physics);
    SetWindowText(GetDlgItem(hwnd, IDC_EDIT_PHYS), buf);
    sprintf(buf, "%.2f", s->chemistry);
    SetWindowText(GetDlgItem(hwnd, IDC_EDIT_CHEM), buf);
    sprintf(buf, "%.2f", s->english);
    SetWindowText(GetDlgItem(hwnd, IDC_EDIT_ENG), buf);
    sprintf(buf, "%.2f", s->computer);
    SetWindowText(GetDlgItem(hwnd, IDC_EDIT_COMP), buf);
}

int GetStudentFromForm(HWND hwnd, Student *s, int requireIdForUpdate) {
    char buf[256];

    GetWindowText(GetDlgItem(hwnd, IDC_EDIT_ID), buf, sizeof(buf));
    int id = atoi(buf);
    if (requireIdForUpdate && id <= 0) return 0;
    s->id = id;

    GetWindowText(GetDlgItem(hwnd, IDC_EDIT_NAME), s->name, MAX_NAME);
    if (s->name[0] == '\0') return 0;

    GetWindowText(GetDlgItem(hwnd, IDC_EDIT_AGE), buf, sizeof(buf));
    s->age = atoi(buf);
    if (s->age <= 0) return 0;

    GetWindowText(GetDlgItem(hwnd, IDC_EDIT_GENDER), buf, sizeof(buf));
    if (buf[0] == '\0') return 0;
    s->gender = buf[0];

    GetWindowText(GetDlgItem(hwnd, IDC_EDIT_ADDRESS), s->address, MAX_ADDRESS);
    if (s->address[0] == '\0') return 0;

    GetWindowText(GetDlgItem(hwnd, IDC_EDIT_PHONE), s->phone, sizeof(s->phone));
    if (s->phone[0] == '\0') return 0;

    GetWindowText(GetDlgItem(hwnd, IDC_EDIT_EMAIL), s->email, MAX_NAME);
    if (s->email[0] == '\0') return 0;

    GetWindowText(GetDlgItem(hwnd, IDC_EDIT_MATH), buf, sizeof(buf));
    s->math = (float)atof(buf);
    GetWindowText(GetDlgItem(hwnd, IDC_EDIT_PHYS), buf, sizeof(buf));
    s->physics = (float)atof(buf);
    GetWindowText(GetDlgItem(hwnd, IDC_EDIT_CHEM), buf, sizeof(buf));
    s->chemistry = (float)atof(buf);
    GetWindowText(GetDlgItem(hwnd, IDC_EDIT_ENG), buf, sizeof(buf));
    s->english = (float)atof(buf);
    GetWindowText(GetDlgItem(hwnd, IDC_EDIT_COMP), buf, sizeof(buf));
    s->computer = (float)atof(buf);

    return 1;
}

void ClearForm(HWND hwnd) {
    int ids[] = {
        IDC_EDIT_ID, IDC_EDIT_NAME, IDC_EDIT_AGE, IDC_EDIT_GENDER,
        IDC_EDIT_ADDRESS, IDC_EDIT_PHONE, IDC_EDIT_EMAIL,
        IDC_EDIT_MATH, IDC_EDIT_PHYS, IDC_EDIT_CHEM,
        IDC_EDIT_ENG, IDC_EDIT_COMP
    };
    for (int i = 0; i < (int)(sizeof(ids)/sizeof(ids[0])); ++i) {
        SetWindowText(GetDlgItem(hwnd, ids[i]), "");
    }
}

void ShowAllStudents(HWND hwnd) {
    const int MAX_STUDENTS = 1000;
    Student *arr = (Student*)malloc(sizeof(Student) * MAX_STUDENTS);
    if (!arr) {
        MessageBox(hwnd, "Memory allocation failed.", "Error", MB_ICONERROR);
        return;
    }

    int count = readAllStudents(arr, MAX_STUDENTS);
    HWND hOut = GetDlgItem(hwnd, IDC_EDIT_OUTPUT);

    if (count == 0) {
        SetWindowText(hOut, "No records found.");
        free(arr);
        return;
    }

    char *buffer = (char*)malloc(count * 512);
    if (!buffer) {
        free(arr);
        MessageBox(hwnd, "Memory allocation failed.", "Error", MB_ICONERROR);
        return;
    }
    buffer[0] = '\0';

    char line[512];
    for (int i = 0; i < count; ++i) {
        Student *s = &arr[i];
        sprintf(line,
            "ID: %d\r\n"
            "Name: %s\r\n"
            "Age: %d, Gender: %c\r\n"
            "Address: %s\r\n"
            "Phone: %s, Email: %s\r\n"
            "Marks - Math: %.2f, Physics: %.2f, Chemistry: %.2f, English: %.2f, Computer: %.2f\r\n"
            "Total: %.2f / 500, Percentage: %.2f%%, Grade: %c\r\n"
            "---------------------------------------------\r\n\r\n",
            s->id, s->name, s->age, s->gender,
            s->address, s->phone, s->email,
            s->math, s->physics, s->chemistry, s->english, s->computer,
            s->total, s->percentage, s->grade);

        strcat(buffer, line);
    }

    SetWindowText(hOut, buffer);

    free(buffer);
    free(arr);
}
