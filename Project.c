#include <stdio.h>     
#include <string.h>    

#define MAX_NAME_LENGTH 50   
#define MAX_TYPE_LENGTH 20   
#define FILE_NAME "books.txt"   

// Dinh nghia cau truc du lieu cho moi loai sach
struct Book {
    char name[MAX_NAME_LENGTH];  
    char type[MAX_TYPE_LENGTH];  
    int year;                      
    float price;                   
};

// Ham de them mot loai sach moi vao file
void addBookToFile(struct Book book) {
    FILE *file = fopen(FILE_NAME, "a");   
    if (file == NULL) {                   
        printf("Khong the mo file.\n");   
        return;
    }
    fprintf(file, "%s;%s;%d;%.2f\n", book.name, book.type, book.year, book.price);   
    fclose(file);   // Dong file sau khi ghi xong
}

// Ham de hien thi tat ca cac loai sach trong file
void displayAllBooks() {
    FILE *file = fopen(FILE_NAME, "r");  
    if (file == NULL) {                   
        printf("Khong the mo file.\n");   
        return;
    }
    struct Book book;   
    printf("Danh sach cac loai sach:\n");   
    printf("Ten\t\tLoai\tNam\tGia\n");     
    while (fscanf(file, "%[^;];%[^;];%d;%f\n", book.name, book.type, &book.year, &book.price) != EOF) {
        // Doc thong tin cua sach tu file va in ra man hinh cho den khi het file
        printf("%s\t\t%s\t%d\t%.2f\n", book.name, book.type, book.year, book.price);
    }
    fclose(file);   
}

// Ham de tim kiem va hien thi thong tin ve mot loai sach cu the
void searchBook(char name[]) {
    FILE *file = fopen(FILE_NAME, "r"); 
    if (file == NULL) {                  
        printf("Khong the mo file.\n");   
        return;
    }
    struct Book book;   
    int found = 0;      
    while (fscanf(file, "%[^;];%[^;];%d;%f\n", book.name, book.type, &book.year, &book.price) != EOF) {
        // Doc thong tin cua sach tu file cho den khi het file
        if (strcmp(book.name, name) == 0) {  
            printf("Thong tin ve sach %s:\n", name);   
            printf("Ten: %s\n", book.name);          
            printf("Loai: %s\n", book.type);          
            printf("Nam: %d\n", book.year);           
printf("Gia: %.2f\n", book.price);       
            found = 1;   
            break;      
        }
    }
    if (!found) {    // Neu khong tim thay sach trong file
        printf("Khong tim thay thong tin ve sach %s.\n", name); 
    }
    fclose(file);   // Dong file sau khi doc xong
}

// Ham de xoa mot loai sach khoi file
void deleteBook(char name[]) {
    FILE *file = fopen(FILE_NAME, "r");   
    if (file == NULL) {                  
        printf("Khong the mo file.\n");  
        return;
    }
    FILE *tempFile = fopen("temp.txt", "w");  
    if (tempFile == NULL) {                     
        printf("Khong the tao file tam thoi.\n");   
        fclose(file);   
        return;
    }
    struct Book book;  
    while (fscanf(file, "%[^;];%[^;];%d;%f\n", book.name, book.type, &book.year, &book.price) != EOF) {

        if (strcmp(book.name, name) != 0) {   
            fprintf(tempFile, "%s;%s;%d;%.2f\n", book.name, book.type, book.year, book.price);
         
        } else {
            found = 1;   
    }
    fclose(file);  
    fclose(tempFile);   
    remove(FILE_NAME);   
    rename("temp.txt", FILE_NAME);   
    if (found) {  
        printf("Da xoa sach %s khoi danh sach.\n", name);
    } else {
        printf("Khong tim thay sach %s trong danh sach.\n", name); 
    }
}

int main() {
    int choice;   
    struct Book book;  
    char bookName[MAX_NAME_LENGTH];  

    while (1) {
        printf("\nChuong trinh quan ly sach\n");  
        printf("1. Them sach\n");   
        printf("2. Hien thi tat ca cac loai sach\n");   
        printf("3. Tim kiem sach\n");   
        printf("4. Xoa sach\n");   
        printf("5. Thoat\n");   
        printf("Nhap lua chon cua ban: ");   
        scanf("%d", &choice);   

        switch (choice) {   
case 1:
                printf("Nhap ten sach: ");
                scanf(" %[^\n]s", book.name);
                printf("Nhap loai sach: ");
                scanf(" %[^\n]s", book.type);
                printf("Nhap nam: ");
                scanf("%d", &book.year);
                printf("Nhap gia: ");
                scanf("%f", &book.price);
                addBookToFile(book);
                break;
            case 2:
                displayAllBooks();
                break;
            case 3:
                printf("Nhap ten sach can tim: ");
                scanf(" %[^\n]s", bookName);
                searchBook(bookName);
                break;
            case 4:
                printf("Nhap ten sach can xoa: ");
                scanf(" %[^\n]s", bookName);
                deleteBook(bookName);
                break;
            case 5:
                printf("Thoat khoi chuong trinh.\n");
                exit(0);   
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");   
        }
    }

    return 0;
}

