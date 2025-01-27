#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int romanoParaDecimal(char *romano) {
    int decimal = 0;
    int valorAnterior = 0;
    int valorAtual;

    for (int i = strlen(romano) - 1; i >= 0; i--) {
        char c = toupper(romano[i]); // Converte para maiúscula para ser case-insensitive
        switch (c) {
            case 'I': valorAtual = 1; break;
            case 'V': valorAtual = 5; break;
            case 'X': valorAtual = 10; break;
            case 'L': valorAtual = 50; break;
            case 'C': valorAtual = 100; break;
            case 'D': valorAtual = 500; break;
            case 'M': valorAtual = 1000; break;
            default: return -1; // Erro: símbolo inválido
        }

        if (valorAtual < valorAnterior) {
            decimal -= valorAtual;
        } else {
            decimal += valorAtual;
        }
        valorAnterior = valorAtual;
    }
    return decimal;
}

char *decimalParaRomano(int decimal) {
    if (decimal < 1 || decimal > 3999) { // Limite usual para romanos sem traço
        return "Número fora do intervalo (1-3999)";
    }

    char *romano = (char *)malloc(16 * sizeof(char)); // Aloca memória suficiente
    romano[0] = '\0'; // Inicializa como string vazia

    int valores[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char *simbolos[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    for (int i = 0; i < 13; i++) {
        while (decimal >= valores[i]) {
            strcat(romano, simbolos[i]);
            decimal -= valores[i];
        }
    }
    return romano;
}

int main() {
    char romano[16];
    int decimal;

    printf("Digite um número romano (ou um número decimal para converter para romano):\n");
    scanf("%s", romano);

    if (isdigit(romano[0])) { // Verifica se o input começa com um dígito, tratando como decimal
        decimal = atoi(romano);
        char *resultadoRomano = decimalParaRomano(decimal);
        printf("Romano: %s\n", resultadoRomano);
        free(resultadoRomano); // Libera a memória alocada
    } else {
        decimal = romanoParaDecimal(romano);
        if (decimal == -1) {
            printf("Erro: Símbolo romano inválido.\n");
        } else {
            printf("Decimal: %d\n", decimal);
        }
    }

    return 0;
}
