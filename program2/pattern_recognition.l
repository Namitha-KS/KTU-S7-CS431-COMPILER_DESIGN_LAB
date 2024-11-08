// analyser.l

%{
#include <stdio.h>
#include <string.h>

int count_real = 0;
int count_int = 0;
int count_abb = 0;
int count_ab = 0;
int div_zero = 0;
int j = 0, k = 0, l = 0; // Separate counters for each array
char abb[10][10];
char ab[10][10];
char bin_zero[10][10];
%}

%%

[+|-]?[0-9]+\.[0-9]+ { 
    ++count_real; 
    printf("Real number: %s\n", yytext); 
}

^[0|1]+$ { 
    int zero_count = 0;
    for (int i = 0; yytext[i] != '\0'; i++) {
        if (yytext[i] == '0') zero_count++;
    }
    if (zero_count % 3 == 0 && zero_count > 0) {
        strcpy(bin_zero[l++], yytext);
        ++div_zero;
        printf("Binary with divisible zeroes: %s\n", yytext);
    } else {
        printf("Binary (not divisible by 3 zeroes): %s\n", yytext);
    }
}

[+|-]?[0-9]+ { 
    ++count_int; 
    printf("Integer: %s\n", yytext); 
}

(a|b)*abb { 
    ++count_abb; 
    strcpy(abb[j++], yytext); 
    printf("Pattern ending in 'abb': %s\n", yytext);
}

(a|b)*ab { 
    ++count_ab; 
    strcpy(ab[k++], yytext); 
    printf("Pattern containing 'ab': %s\n", yytext);
}

[a-zA-Z]+ { 
    printf("Unrecognized token: %s\n", yytext); 
}

%%

int main() {
    yylex();
    
    printf("\nStrings ending with 'abb':\n");
    for (int a = 0; a < j; a++) {
        printf("%s\n", abb[a]);
    }
    
    printf("\nStrings containing 'ab' as a substring:\n");
    for (int a = 0; a < k; a++) {
        printf("%s\n", ab[a]);
    }
    
    printf("\nBinary strings with zeroes divisible by 3:\n");
    for (int a = 0; a < l; a++) {
        printf("%s\n", bin_zero[a]);
    }
    
    printf("\nNumber of real numbers: %d\n", count_real);
    printf("Number of integers: %d\n", count_int);
    printf("Strings with 'abb' as substring: %d\n", count_abb);
    printf("Strings with 'ab' as substring: %d\n", count_ab);
    printf("Binary strings with zeroes divisible by 3: %d\n", div_zero);
    
    return 0;
}
