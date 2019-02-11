#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct phonebook
{
    char num[5][22],name[32],address[55],email[32],group[20];
    struct phonebook *next;
};
struct phonebook *addcontact(struct phonebook *start)
{
    system("cls");
    struct phonebook *newe, *cur=start, *prev= NULL;
    newe=(struct phonebook*)calloc(1,sizeof(struct phonebook));
    printf("Name: ");
    scanf("%s", newe->name);
    int j;
    char ch1, ch2,ch3, ch4,ch5;
    for(j=0; j<5; j++)
    {
        printf("Do you want to save a number?(Y/y) or (N/n)\n");
        ch1=getch();
        if(ch1=='Y' || ch1=='y')
        {
            printf("Number: ");
            scanf("%s", newe->num[j]);
        }

        else
            break;
    }
    for(j=0; j<1; j++)
    {
        printf("Do you want to save an address?(Y/y) or (N/n)\n");
        ch2=getch();
        if(ch2=='Y' || ch2=='y')
        {
            printf("Address: ");
            scanf("%s", newe->address);
        }
        else
            break;
    }
    for(j=0; j<1; j++)
    {
        printf("Do you want to save an e-mail?(Y/y) or (N/n)\n");
        ch3=getch();
        if(ch3=='Y' || ch3=='y')
        {
            printf("E-mail: ");
            scanf("%s", newe->email);
        }
        else
            break;
    }
    for(j=0; j<1; j++)
    {
        printf("Do you want to save a group?(Y/y) or (N/n)\n");
        ch4=getch();
        if(ch4=='Y' || ch4=='y')
        {
            printf("Group: ");
            scanf("%s", newe->group);
        }
        else
            break;
    }
//    while(cur!=NULL)
//    {
//        if(strcmp(cur->name, newe->name)>0)
//            break;
//        else
//        {
//            prev=cur;
//            cur=cur->next;
//        }
//    }
//    if(cur==start)
//        start=newe;
//    else
//    {
//        prev->next=newe;
//        newe->next=cur;
//    }
    newe->next = NULL;
    if(start == NULL)
        start = newe;
    else
    {
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = newe;
    }
    printf("\tYou have successfully added your contact.\n\n");
    printf("Press any key to continue\n");
    char d;
    d=getch();

    //store the contact within a file
    store(start);
    return start;
}
void store(struct phonebook *start)
{
    FILE *fp;
    struct phonebook *cur = start;
    if((fp=fopen("file.txt", "wb"))==NULL)
    {
        printf("Error");
        exit(1);
    }
    while(cur!=NULL)
    {
        fwrite(cur,sizeof(struct phonebook), 1, fp);
        cur = cur->next;
    }
    fclose(fp);
    return;
}
int searchmenu()
{
    int curpos=1;
    char ch=10;

    while(ch!=13)
    {
        system("cls");
        printf("Press up and down arrows to navigate the menu.\n");
        if(curpos==1)
        {
            printf("==>>\t1.SEARCH BY NAME\n");
            printf("\t2.Search by Group\n");
            printf("\t3.Back\n");
        }
        else if(curpos==2)
        {
            printf("\t1.Search by Name \n");
            printf("==>>\t2.SEARCH BY GROUP\n");
            printf("\t3.Back\n");
        }
        else
        {
            printf("\t1.Search by Name\n");
            printf("\t2.Search by Group\n");
            printf("==>>\t3.BACK\n");
        }
        ch=getch();
        if(ch==72)
            curpos--;
        else if(ch==80)
            curpos++;

        if(curpos==4)
            curpos=1;
        if(curpos==0)
            curpos=3;
    }
    return curpos;
}
void searchcontact(struct phonebook *start)
{
    int i, option=searchmenu();
    int flag=0;
    struct phonebook *cur=start;
    char inpname[110], inpgroup[110];
    if(option==1)
    {
        printf("Name:");
        scanf(" %s", inpname);
        while(cur!=NULL)
        {
            if(strcmp(cur->name,inpname)==0)
            {
                printf("Name: %s\n", cur->name);
                for(i=0; i<5 ; i++)
                {
                    if(cur->num[i][0]=='\0')
                        break;
                    printf("Phone Number: %s\n", cur->num[i]);
                }
                printf("Address: %s\n", cur->address);
                printf("Email: %s\n", cur->email);
                printf("Group Name: %s\n", cur->group);
                printf("\n\n");
                cur = cur->next;
                flag=1;
            }
            cur=cur->next;
        }
        if(flag==0)
            printf("The contact is not found.\n");
        printf("Press any key to continue\n");
        char d;
        d=getch();
    }
    else if(option==2)
    {
        printf("Group:");
        scanf(" %s", inpgroup);
        while(cur!=NULL)
        {
            if(strcmp(cur->group,inpgroup)==0)
            {
                printf("Name: %s\n", cur->name);
                for(i=0; i<5 ; i++)
                {
                    if(cur->num[i][0]=='\0')
                        break;
                    printf("Phone Number: %s\n", cur->num[i]);
                }

                printf("Address: %s\n", cur->address);
                printf("Email: %s\n", cur->email);
                printf("Group Name: %s\n", cur->group);
                printf("\n\n");
                cur = cur->next;
                flag=1;
            }
            cur=cur->next;
        }
        if(flag==0)
            printf("The contact is not found.\n");
        printf("Press any key to continue\n");
        char e;
        e=getch();
    }
    else
        menu();
    return;
}

struct phonebook *deletecontact(struct phonebook *start)
{
    int i, flag=0;
    char choice;
    char inpname[110];
    printf("Name:");
    scanf("%s", inpname);
    struct phonebook *cur=start, *prev=NULL;
    while(cur!=NULL)
    {
        if(strcmp(cur->name,inpname)==0)
        {
            break;
        }
        prev=cur;
        cur=cur->next;
    }
    if(cur!=NULL)
    {
        if(cur==start)
        {
            start=cur->next;
            free(cur);
            flag=1;
        }
        else
        {
            prev->next=cur->next;
            free(cur);
            flag=1;
        }
    }
    if(flag==1)
        printf("The contact has been deleted successfully.\n");
    printf("Press any key to continue.\n");
    char c;
    c=getch();
    return start;
}

void viewcontact(struct phonebook *start)
{
    struct phonebook *cur = start;
    int i;
    while (cur != NULL)
    {
        printf("Name: %s\n", cur->name);
        for(i=0; i<5 ; i++)
        {
            if(cur->num[i][0]=='\0')
                break;
            printf("Phone Number: %s\n", cur->num[i]);
        }

        printf("Address: %s\n", cur->address);
        printf("Email: %s\n", cur->email);
        printf("Group Name: %s\n", cur->group);
        printf("\n\n");
        cur = cur->next;
    }
    printf("Press any key to continue\n");
    char d;
    d=getch();
    return;
}
int menu()
{
    int curpos=1;
    char ch=10;

    while(ch!=13)
    {
        system("cls");
        printf("Press up and down arrows to navigate the menu.\n");
        if(curpos==1)
        {
            printf("==>>\t1.ADD NEW CONTACT\n");
            printf("\t2.View Contact\n");
            printf("\t3.Search Contact\n");
            printf("\t4.Delete Contact\n");
            printf("\t5.Exit\n");
        }
        else if(curpos==2)
        {
            printf("\t1.Add New Contact\n");
            printf("==>>\t2.VIEW CONTACT\n");
            printf("\t3.Search Contact\n");
            printf("\t4.Delete Contact\n");
            printf("\t5.Exit\n");
        }
        else if(curpos==3)
        {
            printf("\t1.Add New Contact\n");
            printf("\t2.View Contact\n");
            printf("==>>\t3.SEARCH CONTACT\n");
            printf("\t4.Delete Contact\n");
            printf("\t5.Exit\n");
        }
        else if(curpos==4)
        {
            printf("\t1.Add New Contact\n");
            printf("\t2.View Contact\n");
            printf("\t3.Search Contact\n");
            printf("==>>\t4.DELETE CONTACT\n");
            printf("\t5.Exit\n");
        }
        else
        {
            printf("\t1.Add New Contact\n");
            printf("\t2.View Contact\n");
            printf("\t3.Search Contact\n");
            printf("\t4.Delete Contact\n");
            printf("==>>\t5.EXIT\n");
        }
        ch=getch();
        if(ch==72)
            curpos--;
        else if(ch==80)
            curpos++;

        if(curpos==6)
            curpos=1;
        if(curpos==0)
            curpos=5;
    }
    return curpos;
}
struct phonebook *load(struct phonebook *start)
{
//    struct phonebook *start=NULL;
    struct phonebook *newc,  *cur=start;
    FILE *fp;
    fp=fopen("file.txt","rb");
    if(fp!=NULL)
    {
        while(1)
        {
            newc=(struct phonebook*)calloc(1,sizeof(struct phonebook));
            if(fread(newc, sizeof(struct phonebook),1, fp)!=1)
                break;

            newc->next = NULL;
            if(start == NULL)
                start = newc;
            else
            {
                cur=start;
                while (cur->next != NULL)
                    cur = cur->next;
                cur->next = newc;
            }
        }
    }
    else
    {
        printf("Error");
    }
    fclose(fp);
    return start;
}
int main()
{
    struct phonebook *start=NULL;
//    call the load function start=load()
    start=load(start);
    int i;

    while(1)
    {
        int option=menu();
        if(option==1)
            start=addcontact(start);
        else if(option==2)
            viewcontact(start);
        else if(option==3)
            searchcontact(start);
        else if(option==4)
            start=deletecontact(start);

        else
            break;
    }
    return 0;
}
