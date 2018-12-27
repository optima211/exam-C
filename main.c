#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

struct zach {
    char prname[20];
    int prmark;
};
struct spis {
    char surname[20];
    char group[20];
    struct zach spiszach[5];
    struct spis *prev;
    struct spis *next;
};

void createlist(void);
void viewlist(void);
void findGroup(void);
void load(void);
int GetRecords();

struct spis *head, *tail;

#define FILE_NAME "output.txt"

int main() {
    load();
    char c;
    while (1) {
        puts("1 - new list");
        puts("2 - view list");
        puts("3 - find group");
        puts("0 - exit");
        c = _getch();
        switch(c) {
            case '1':createlist();break;
            case '2':viewlist(); break;
            case '3':findGroup();break;
            case '0':return 0;
            default: printf("incorrect mode %d\n",c);
        }
        puts("");
    }
}

void createlist(void) {
    printf("\n Create new file? - Y/N");
    int c = _getch();
    if ((c == 'y') || (c == 'Y')){
    head = tail = NULL;
    FILE *output = fopen(FILE_NAME, "w");
    printf ("\nRecords: %d\n",GetRecords());}
}

void viewlist(void) {
    struct spis *p;
    int i;
    p = head;
    while(p != NULL){
        printf("\n%s %s\n",p->surname,p->group);
        for (i = 0;i < 5;i++)
            printf("%s:  %d\n",p->spiszach[i].prname,p->spiszach[i].prmark);
        printf("\n********************\n");
        p = p->next;
    }

}

void findGroup(void) {
    struct spis *p;
    int i;
    char groups[20];
    p = head;
    printf("\nEnter group:\n");
    scanf_s("%s", groups,20);
    while(p != NULL){

        if(strcmp(p->group, groups) == 0){
            printf("\n%s %s\n",p->surname,p->group);
        for (i = 0;i < 5;i++)
            printf("%s:  %d\n",p->spiszach[i].prname,p->spiszach[i].prmark);
        printf("\n********************\n");
    }
        p = p->next;
    }
    printf ("\nRecords: %d\n",GetRecords());
}

void load() {
    FILE *input;
    struct spis *p;
    input = fopen(FILE_NAME, "r");
    head = tail = NULL;
    if (input != NULL) {
        while (!feof(input)) {
            p = (struct spis *)malloc(sizeof(struct spis));
            fread(p, sizeof(struct spis), 1, input);
            if (feof(input))
                break;
            p->next = NULL;
            p->prev = tail;
            if (tail != NULL)
                tail->next = p;
            if (head == NULL)
                head = p;
            tail = p;
        }
        fclose(input);
    }
    printf ("\nRecords: %d\n",GetRecords());
}

int GetRecords() {
    int n = 0;
    struct spis *p;
    p = head;
    while(p != NULL) {
        n++;
        p = p->next;
    }
    return(n);
}
