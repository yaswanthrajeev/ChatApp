#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *fp1,*fp2;
char record[100];
int  verify_header()
{
    char prog_name[10],verify_name[10];
    
    fscanf(fp1,"%s",record);

    printf("enter program name\t:");
   scanf("%s",verify_name);

    int i = 2;
    while(record[i] !='^')
    {
        prog_name[i-2]=record[i];
        i++;
    }
     prog_name[i] = '\0';
   
   if(strcmp(prog_name,verify_name)!=0)
   {
    printf("invalid program name\n");
    exit(0);
   }
   else{
    printf("program name :\t%s\n",prog_name);
   }
   
    fscanf(fp1,"%s",record);
}
int main()
{
    fp2=fopen("memory.txt","w");
    fp1=fopen("object.txt","r");

    verify_header();

    int starting_address;
    char address[10];
    
    while(record[0]!='E')
    {
        int i=2;
        while(record[i]!='^')
        {
            address[i-2]=record[i];
            i++;
        }
        printf("starting address :\t%s\n",address);
            starting_address=atoi(address);
        
        i+=4;
        while(i<strlen(record)-1)
        {
            if(record[i]!='^')
            {
                printf("%06d\t%c%c\n",starting_address,record[i],record[i+1]);
                fprintf(fp2,"%06d\t%c%c\n",starting_address,record[i],record[i+1]);
                starting_address++;
                i+=2;
            }
            else{
                i++;
            }

        }
        fprintf(fp2,"\n");
        printf("\n");
         fscanf(fp1,"%s",record);
    }
    fclose(fp1);
    fclose(fp2);
}