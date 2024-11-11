#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void display() {

    char str;
    FILE *fp1, *fp2, *fp3;   

    // 1. Input Table
    printf("\nThe contents of Input Table :\n\n");
    fp1 = fopen("input.txt", "r");
    str = fgetc(fp1);
    while (str != EOF) {
        printf("%c", str);
        str = fgetc(fp1);
    }
    fclose(fp1);

    //2. Output Table
    printf("\n\nThe contents of Output Table :\n\n");
    fp2 = fopen("intermediate.txt", "r");
    str = fgetc(fp2);
    while (str != EOF) {
        printf("%c", str);
        str = fgetc(fp2);
    }
    fclose(fp2);

    // 3. Symtable
    printf("\n\nThe contents of Symbol Table :\n\n");
    fp3 = fopen("symtab.txt", "r");
    str = fgetc(fp3);
    while (str != EOF) {
        printf("%c", str);
        str = fgetc(fp3);
    }
    fclose(fp3);
}void passone(char label[10], char opcode[10], char operand[10], char code[10], char mnemonic[3])
{
    FILE *fp1,*fp2,*fp3,*fp4,*fp5;
    int locctr,start,length;
    fp1=fopen("input.txt","r");
    fp2=fopen("optab.txt","r");
    fp3=fopen("symtab.txt","w");
    fp4=fopen("intermediate.txt","w");
    fp5=fopen("length.txt","w");

    if(strcmp(opcode,"START")==0)
    {
        start=atoi(operand);
        locctr=start;
        fprintf(fp4,"\t%s\t%s\t%s\n",label,opcode,operand);
        fscanf(fp1,"%s\t%s\t%s\t",label,opcode,operand);
    }
    else{
        locctr=0;
    }
    while(strcmp(opcode,"END")!=0)
    {
        fprintf(fp4,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        if(strcmp(label,"**")!=0)
        {
            fprintf(fp3,"%s\t%d\n",label,locctr);
        }
        fscanf(fp2,"%s\t%s\n",code,mnemonic);
        while(strcmp(code,"END")!=0)
        {
            if(strcmp(opcode,code)==0)
            {

                locctr+=3;
                break;
            }
        fscanf(fp2,"%s\t%s",code,mnemonic);
        }
        if(strcmp(opcode,"WORD")==0)
        {
            locctr+=3;
        }
        else if(strcmp(opcode,"RESW")==0)
        {
            locctr+=3*(atoi(operand));
        }
        else if(strcmp(opcode,"RESB"))
        {
            locctr+=atoi(operand);
        }
                else if(strcmp(opcode,"RESB"))
        {
            ++locctr;
        }
         fscanf(fp1,"%s\t%s\t%s\t",label,opcode,operand);
    }
     fprintf(fp4,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
     fclose(fp1);
     fclose(fp2);
     fclose(fp3);
     fclose(fp4);
     display();
     length=start-locctr;
     fprintf(fp5,"%d\n",length);
     printf("length is %d\n",length);
    
}

int main()
{
    char label[10],opcode[10],operand[10];
    char code[10],mnemonic[3];
    passone(label,opcode,operand,code,mnemonic);
    return 0;
}