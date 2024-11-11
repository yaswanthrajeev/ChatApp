#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
    FILE *fp1, *fp2, *fp3, *fp4, *fp5;
    fp1 = fopen("intermediate.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("symtab.txt", "r");
    fp4 = fopen("finaloutput.txt", "w");
    fp5 = fopen("object.txt", "w");
    
    if (!fp1 || !fp2 || !fp3 || !fp4 || !fp5) {
        printf("Error opening files.\n");
        return;
    }

    char label[10], opcode[10], operand[10], code[10], symbol[10], loc[10];
    int prevaddr, finaddr, start, length;

    // Read first line to find final address
    fscanf(fp1, "%s%s%s%s", loc, label, opcode, operand);
    while (strcmp(opcode, "END") != 0) {
        prevaddr = atoi(loc);
        fscanf(fp1, "%s%s%s%s", loc, label, opcode, operand);
    }
    finaddr = atoi(loc);
    fclose(fp1);

    // Re-open intermediate file to start reading from the beginning
    fp1 = fopen("intermediate.txt", "r");
    fscanf(fp1, "%s%s%s%s", loc, label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        fprintf(fp4, "%s\t%10s%10s%10s\t%s\n", loc, label, opcode, operand, "**");
        fprintf(fp5, "H^%s^%06d^%06X\n", label, atoi(operand), finaddr - atoi(operand));
        fprintf(fp5, "T^%06d,%06X", atoi(operand), prevaddr - atoi(operand));
        fscanf(fp1, "%s%s%s%s", loc, label, opcode, operand);
    }

    while (strcmp(opcode, "END") != 0) {
        if (strcmp(opcode, "BYTE") == 0) {
            fprintf(fp4, "%s\t%10s%10s%10s\t", loc, label, opcode, operand);
            length = strlen(operand) - 3;
            for (int i = 2; i < length + 2; i++) {
                fprintf(fp4, "%X", operand[i]);
                fprintf(fp5, "^%X", operand[i]);
            }
            fprintf(fp4, "\n");
        } else if (strcmp(opcode, "WORD") == 0) {
            fprintf(fp4, "%s\t%10s%10s%10s\t%06d\n", loc, label, opcode, operand, atoi(operand));
            fprintf(fp5, "^%06d", atoi(operand));
        } else if ((strcmp(opcode, "RESW") == 0 || strcmp(opcode, "RESB") == 0)) {
            fprintf(fp4, "%s\t%10s%10s%10s\n", loc, label, opcode, operand);
        } else {
            fprintf(fp4, "%s\t%10s%10s%10s\t", loc, label, opcode, operand);
            if (strcmp(opcode, "END") != 0) {
                rewind(fp2);
                fscanf(fp2, "%s%s", symbol, code);
                while (strcmp(symbol, opcode) != 0 && !feof(fp2)) {
                    fscanf(fp2, "%s%s", symbol, code);
                }
                fprintf(fp4, "%s", code);
                fprintf(fp5, "^%s", code);

                rewind(fp3);
                fscanf(fp3, "%s%s", symbol, code);
                while (strcmp(symbol, operand) != 0 && !feof(fp3)) {
                    fscanf(fp3, "%s%s", symbol, code);
                }
                fprintf(fp4, "%s\n", code);
                fprintf(fp5, "%s", code);
            }
        }

        // Read the next line
        fscanf(fp1, "%s%s%s%s", loc, label, opcode, operand);
    }

    // Print END record to both files
    fprintf(fp4, "%s\t%10s%10s%10s\n", loc, label, opcode, operand);
    fprintf(fp5, "\nE^%06d\n", start);

    // Close all file pointers
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
}
