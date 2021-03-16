#include<stdio.h>
#include<string.h>
#define NMAX 200
typedef struct book {
    char book_name[30];
    char author_name[30];
    char publisher[20];
    int year;
    double price;
} Book;

int main(){
    Book list[NMAX];
    int n;
    int option;

    do {
        printf("MENU\n");
        printf("1.Enter information of n books of HUST.\n");
        printf("2.Printf the information of the entered books on the screen.\n");
        printf("3.Sort.\n");
        printf("4.Search book by title\n");
        printf("5.Search book by auhtor's name\n");
        printf("6.Exit\n\n");

        scanf("%d",&option);

        switch(option){
        case 1:
            printf("Enter the number of books:\n");
            scanf("%d",&n);
            enteredInfor(list,n);
            break;
        case 2:
            printList();
            break;
        case 3:
            sortList();
            break;
        case 4:
            searchTitle();
            break;
        case 5:
            searchAuthor();
            break;
        case 6:
            return 0;
        }
    }   while (option != 6);
    return 0;
}

void enteredInfor(Book list[], int n){
    FILE *fp = fopen("HUST.txt","w+");
    fprintf(fp,"%d\n",n);

    for(int i=0;i<n;i++){
        printf("Book's Name?");fflush(stdin);gets(list[i].book_name);
        printf("Author's Name?");gets(list[i].author_name);
        printf("Publisher?");gets(list[i].publisher);
        printf("Year of publication?");scanf("%d",&(list[i].year));
        printf("Price?");scanf("%lf",&(list[i].price));

        fprintf(fp,"%s\n",list[i].book_name);
        fprintf(fp,"%s\n",list[i].author_name);
        fprintf(fp,"%s\n",list[i].publisher);
        fprintf(fp,"%d\n",list[i].year);
        fprintf(fp,"%.1f\n",list[i].price);
        fprintf(fp,"\n");
    }
    fclose(fp);
    printf("Done!\n");
    return 0;
}

void printList(){

    FILE *fp = fopen("HUST.txt","r");

    int n;
    char line[80];
    int a;
    double b;
    fscanf(fp,"%d",&n);

    printf("The number of book is %d\n",n);

    printf("List of book :\n");
    for(int i=0;i<n;i++){
        fscanf(fp, "%s", line); printf("%-30s ", line);
        fscanf(fp, "%s", line); printf("%-30s ", line);
        fscanf(fp, "%s", line);
        fscanf(fp, "%d", &a); printf("%10d ", a);
        fscanf(fp, "%lf", &b); printf("%10g \n\n", b);
    }
    fclose(fp);

    return 0;
}

void sortList(){
    FILE *fp = fopen("HUST.txt", "r");

    int n;
    Book list[NMAX];

    fscanf(fp,"%d",&n);

    for(int i=0;i<n;i++){
        fscanf(fp,"%s",&list[i].book_name);
        fscanf(fp,"%s",&list[i].author_name);
        fscanf(fp,"%s",&list[i].publisher);
        fscanf(fp,"%d",&list[i].year);
        fscanf(fp,"%lf",&list[i].price);
    }

    fclose(fp);

    Book tmp;

    for(int i=0;i<n;i++){
        for(int j=+1;j<n;j++){
            if(list[i].year < list[j].year){
                tmp = list[i];
                list[i]=list[j];
                list[j]=tmp;
            }else if(list[i].year == list[j].year){
                if(list[i].price < list[j].price){
                    tmp = list[i];
                    list[i]=list[j];
                    list[j]=tmp;
                }
            }
        }
    }

    fp = fopen("HUST.txt","w");
    fprintf(fp,"%d\n",n);

    for(int i=0;i<n;i++){
        fprintf(fp,"%s\n",list[i].book_name);
        fprintf(fp,"%s\n",list[i].author_name);
        fprintf(fp,"%s\n",list[i].publisher);
        fprintf(fp,"%d\n",list[i].year);
        fprintf(fp,"%.1f\n",list[i].price);
        fprintf(fp,"\n");
    }
    fclose(fp);

    printList();
    return 0;
}

searchTitle(){
    FILE *fp = fopen("HUST.txt", "r");

    int n;
    Book list[NMAX];

    fscanf(fp,"%d",&n);

    for(int i=0;i<n;i++){
        fscanf(fp,"%s",&list[i].book_name);
        fscanf(fp,"%s",&list[i].author_name);
        fscanf(fp,"%s",&list[i].publisher);
        fscanf(fp,"%d",&list[i].year);
        fscanf(fp,"%lf",&list[i].price);
    }

    fclose(fp);

    char key[20];
    printf("Input the name of book: \n");
    fflush(stdin);
    gets(key);
    int count=0;
    for(int i=0;i<n;i++){
        if(strstr(list[i].book_name,key)){
            printf("%s,%s,%s\n",list[i].book_name,list[i].author_name,list[i].publisher);
            count ++;
        }
    }
    if(count == 0) printf("No book is found \n");
    return 0;
}

searchAuthor(){
    FILE *fp = fopen("HUST.txt", "r");

    int n;
    Book list[NMAX];

    fscanf(fp,"%d",&n);

    for(int i=0;i<n;i++){
        fscanf(fp,"%s",&list[i].book_name);
        fscanf(fp,"%s",&list[i].author_name);
        fscanf(fp,"%s",&list[i].publisher);
        fscanf(fp,"%d",&list[i].year);
        fscanf(fp,"%lf",&list[i].price);
    }

    fclose(fp);

    char key[20];
    Book found[200];
    int count = 0;

    fflush(stdin);
    gets(key);

    for(int i=0;i<n;i++){
        if(strcmp(list[i].author_name,key)==0){
            found[count] = list[i];
            count ++;
        }
    }
    if(count == 0){
        printf("No found this author \n");
    } else {
        printf("%s, ",key);
        for(int i=0;i<count;i++){
            printf("%s, ",found[i].book_name);
        }
        printf("%d\n",count);
    }
    return 0;
}
