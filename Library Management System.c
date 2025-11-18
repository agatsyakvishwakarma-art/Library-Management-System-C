#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define pf printf 
#define sf scanf 

void voidline1(){
    pf("\n|=================================================================|\n");
}
void voidline2(){
    pf("\n|-----------------------------------------------------------------|\n");
}

void menu() {
    pf("\n|============================= MENU ==============================|\n");
    pf(" 1. Add New Book\n");
    pf(" 2. Display Books\n");
    pf(" 3. Search Book\n");
    pf(" 4. Edit Book\n");
    pf(" 5. Delete Book\n");
    pf(" 6. Save & Exit\n");
    pf("|=================================================================|\n");
}

struct book{
    int ID;
    char Name[50];
    char Author[50];
    int Quantity;
};

void addBook(){
    char choice;
    struct book b;
    FILE *p;

    p = fopen("books.dat","ab");
    if (p==NULL) {
        pf(" Error Opening File!\n");
    }
    
    do{
        voidline2();
        pf(" Enter Book ID: ");
        sf("%d", &b.ID);
        pf(" Enter Book Name: ");
        sf(" %[^\n]", b.Name);
        pf(" Enter Author Name: ");
        sf(" %[^\n]", b.Author);
        pf(" Enter Quantity: ");
        sf("%d", &b.Quantity);

        fwrite(&b, sizeof(b),1,p);
        voidline1();

        pf("\n Book Added And Saved Successfully!\n");
        pf(" Do You Wish To Add Another Book?(y or n): ");
        sf(" %c",&choice);

    }while((choice=='y'|| choice=='Y'));
    fclose(p);    
}

void displayBooks(){
    int i;
    struct book b;
    FILE *p;

    p=fopen("books.dat","rb");
    if (p==NULL){
        pf(" No Books Found!\n");
    }
    else{
        pf("\n|=========================== BOOK LIST ===========================|\n");
        pf(" %-8s %-25s %-25s %-10s\n", "ID", "Name", "Author", "Qty");
        voidline2();        
        while (fread(&b, sizeof(b), 1, p)) {
            pf(" %-8d %-25s %-25s %-10d\n",
                b.ID, b.Name, b.Author, b.Quantity);
        }
    }
    pf("\n");
    fclose(p);
}

void searchBook(){
    int read,search,count=0;
    struct book b;
    FILE *p;

    voidline2();
    p=fopen("books.dat","rb");
    if(p==NULL){
        pf(" Error Opening File!");
    }
    read=fread(&b,sizeof(b),1,p);

    pf(" Which Book Do You Want To Search?\n Enter Book ID: ");
    sf("%d",&search);

    while(read==1){
        if(b.ID==search){
            pf("\n|=========================== BOOK FOUND ==========================|\n");
            pf(" %-8s %-25s %-25s %-10s\n", "ID", "Name", "Author", "Qty");
            voidline2();            
            pf(" %-8d %-25s %-25s %-10d\n",b.ID, b.Name, b.Author, b.Quantity);
            voidline1();            
            count=1;
            break;
        }
        read=fread(&b,sizeof(b),1,p);
    }
    if(count==0){
        pf(" No Book Found!");
    }
    fclose(p);
}

void editBook(){
    int edit,read;
    char ch;
    struct book b;
    FILE *p,*q;

    displayBooks();
    p=fopen("books.dat","rb");
    q=fopen("temp.dat","wb");
    if(p==NULL || q==NULL){
        pf(" Error Opening File!");
    }
    read=fread(&b,sizeof(b),1,p);
    
    voidline2();    
    pf(" Which Book Do You Want To Edit?\n Enter Book ID: ");
    sf("%d",&edit);
    voidline2();

    while(read==1){
        if(b.ID==edit){
            pf(" Enter New Name: ");
            scanf(" %[^\n]",b.Name);
            pf(" Enter New Author: ");
            scanf(" %[^\n]",b.Author);
            pf(" Enter New Quantity: ");
            scanf(" %d",&b.Quantity);
        }
        fwrite(&b,sizeof(b),1,q);
        read=fread(&b,sizeof(b),1,p);
    }

    fclose(p);
    fclose(q);

    q=fopen("temp.dat","rb");
    p=fopen("books.dat","wb");
    
    while(fread(&b,sizeof(b),1,q)){
        fwrite(&b,sizeof(b),1,p);
    }

    fclose(p);
    fclose(q);

    displayBooks();
    pf(" Book Updated Successfully!\n");    
}

void deleteBook(){
    int delete,read;
    struct book b;
    FILE *p,*q,*r;

    displayBooks();
    p=fopen("books.dat","rb");
    q=fopen("temp.dat","wb");    
    if(p==NULL || q==NULL || r==NULL){
        pf(" Error Opening File!");
    }
    read=fread(&b,sizeof(b),1,p);

    pf(" Enter Book ID Which You Want To Delete: ");
    sf("%d",&delete);
    voidline2();

    while(read==1){
        if(b.ID!=delete){
            fwrite(&b,sizeof(b),1,q);
        }        
        read=fread(&b,sizeof(b),1,p);
    }

    fclose(p);
    fclose(q);
    
    q=fopen("temp.dat","rb");
    p=fopen("books.dat","wb");

    while(fread(&b,sizeof(b),1,q)){
        fwrite(&b,sizeof(b),1,p);
    }

    fclose(q);
    fclose(p);

    pf("\n Record Successfully Deleted!\n");
}

void saveandexit(){
    voidline2();
    pf("\n Saving and Exiting");
    fflush(stdout);
    for(int i=1;i<=5;i++){
        sleep(1);
        pf(".");
        fflush(stdout);
    }
    pf("Exited!\n");
    voidline1();
    exit(0);
}

int main(){
    int choice;
    voidline1();
    pf("                    LIBRARY MANAGEMENT SYSTEM");
    voidline1();

    while (1){
        menu();      
        pf("\nEnter Your Choice:");
        sf("%d",&choice);
        switch(choice){
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                editBook();
                break;
            case 5:
                deleteBook();
                break;
            case 6:
                saveandexit();
                break;
            default:
                voidline1();
                pf("\nInvalid Choice! Try again.\n");
                voidline1();
        }
    }
    return 0;
}