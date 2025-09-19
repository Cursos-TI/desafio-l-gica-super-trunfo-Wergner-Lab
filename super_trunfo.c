/*
 * super_trunfo.c
 *
 * Implementação do exercício: comparar duas cartas do Super Trunfo
 * com base em um único atributo numérico predefinido no código.
 *
 * Requisitos atendidos:
 * - Define duas cartas (pré-cadastradas no código)
 * - Calcula Densidade Populacional e PIB per capita
 * - Compara um atributo escolhido diretamente no código (macro COMPARE_ATTRIBUTE)
 * - Para Densidade Populacional: menor valor vence; para os demais: maior vence
 * - Exibe resultado claro e informativo
 *
 * Como usar:
 * - Alterar o atributo a ser comparado mudando a macro COMPARE_ATTRIBUTE
 *   (ver lista de atributos abaixo)
 * - Compilar: gcc -o super_trunfo super_trunfo.c
 * - Executar: ./super_trunfo
 *
 * Autor: (seu nome)
 * Data: (coloque a data)
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

/* Definição da estrutura Carta */
typedef struct {
    char estado[50];           // Estado (UF)
    char codigo[20];           // Código da carta
    char cidade[60];           // Nome da cidade
    long long populacao;       // População (int) - use long long para números grandes
    double area;               // Área (float) em km^2
    double pib;                // PIB (float) (mesma unidade para as duas cartas)
    int pontos_turisticos;     // Número de pontos turísticos (int)
} Carta;

/* Constantes para os atributos possíveis */
#define ATTR_POPULACAO       0
#define ATTR_AREA            1
#define ATTR_PIB             2
#define ATTR_DENSIDADE       3
#define ATTR_PIB_PER_CAPITA  4

/* ESCOLHA DO ATRIBUTO PARA COMPARAÇÃO
 * Altere esta macro para comparar outro atributo.
 * Exemplos:
 *   #define COMPARE_ATTRIBUTE ATTR_POPULACAO
 *   #define COMPARE_ATTRIBUTE ATTR_AREA
 *   #define COMPARE_ATTRIBUTE ATTR_PIB
 *   #define COMPARE_ATTRIBUTE ATTR_DENSIDADE
 *   #define COMPARE_ATTRIBUTE ATTR_PIB_PER_CAPITA
 */
#define COMPARE_ATTRIBUTE ATTR_POPULACAO

/* Funções utilitárias ----------------------------------------------------- */

/* Calcula densidade populacional (hab/km^2). Retorna -1 se área inválida (<= 0). */
double calcular_densidade(const Carta *c) {
    if (c->area <= 0.0) return -1.0;
    return (double)c->populacao / c->area;
}

/* Calcula PIB per capita. Retorna -1 se população inválida (<= 0). */
double calcular_pib_per_capita(const Carta *c) {
    if (c->populacao <= 0) return -1.0;
    return c->pib / (double)c->populacao;
}

/* Retorna o valor (em double) do atributo escolhido para comparação. */
double valor_atributo_para_comparar(const Carta *c, int atributo) {
    switch (atributo) {
        case ATTR_POPULACAO: return (double)c->populacao;
        case ATTR_AREA: return c->area;
        case ATTR_PIB: return c->pib;
        case ATTR_DENSIDADE: return calcular_densidade(c);
        case ATTR_PIB_PER_CAPITA: return calcular_pib_per_capita(c);
        default: return 0.0;
    }
}

/* Retorna o nome legível do atributo */
const char* nome_atributo(int atributo) {
    switch (atributo) {
        case ATTR_POPULACAO: return "População";
        case ATTR_AREA: return "Área (km^2)";
        case ATTR_PIB: return "PIB";
        case ATTR_DENSIDADE: return "Densidade Populacional (hab/km^2)";
        case ATTR_PIB_PER_CAPITA: return "PIB per capita";
        default: return "Atributo desconhecido";
    }
}

/* Indica se, para o atributo dado, o menor valor vence (apenas para densidade). */
int menor_valor_vencedor(int atributo) {
    return (atributo == ATTR_DENSIDADE) ? 1 : 0;
}

/* Imprime dados resumidos da carta, incluindo densidade e PIB per capita */
void imprimir_resumo_carta(const Carta *c, int id) {
    printf("Carta %d - %s (%s)\n", id, c->cidade, c->estado);
    printf("  Código: %s\n", c->codigo);
    printf("  População: %lld\n", c->populacao);
    printf("  Área: %.2f km^2\n", c->area);
    printf("  PIB: %.2f\n", c->pib);
    printf("  Pontos turísticos: %d\n", c->pontos_turisticos);

    double dens = calcular_densidade(c);
    if (dens < 0.0) printf("  Densidade: área inválida para cálculo\n");
    else printf("  Densidade: %.2f hab/km^2\n", dens);

    double pibpc = calcular_pib_per_capita(c);
    if (pibpc < 0.0) printf("  PIB per capita: população inválida para cálculo\n");
    else printf("  PIB per capita: %.2f\n", pibpc);
}

/* Função principal -------------------------------------------------------- */
int main(void) {
    /* DUAS CARTAS PRE-DEFINIDAS (altere aqui os dados para testar) */
    Carta carta1 = {"SP", "C001", "São Paulo", 12300000LL, 1521.11, 700000000000.0, 20};
    Carta carta2 = {"RJ", "C002", "Rio de Janeiro", 6000000LL, 1182.00, 300000000000.0, 15};

    /* Exibir resumo e cálculos auxiliares */
    printf("=== Resumo das cartas ===\n\n");
    imprimir_resumo_carta(&carta1, 1);
    printf("\n");
    imprimir_resumo_carta(&carta2, 2);
    printf("\n");

    /* Preparar comparação */
    int atributo = COMPARE_ATTRIBUTE;
    const char *nomeAttr = nome_atributo(atributo);
    double v1 = valor_atributo_para_comparar(&carta1, atributo);
    double v2 = valor_atributo_para_comparar(&carta2, atributo);

    printf("Comparação de cartas (Atributo: %s):\n\n", nomeAttr);

    /* Tratar casos em que o valor é inválido (por exemplo, divisão por zero) */
    int v1_invalido = (v1 < 0.0);
    int v2_invalido = (v2 < 0.0);

    if (v1_invalido || v2_invalido) {
        printf("Um dos valores está inválido para o cálculo do atributo.\n");
        if (v1_invalido) printf("  Carta 1: valor inválido\n");
        if (v2_invalido) printf("  Carta 2: valor inválido\n");
        printf("Não é possível comparar este atributo nestas cartas.\n");
        return 0;
    }

    /* Mostrar valores usados na comparação */
    printf("Carta 1 - %s (%s): ", carta1.cidade, carta1.estado);
    if (atributo == ATTR_POPULACAO) printf("%.0f\n", v1);
    else if (atributo == ATTR_AREA) printf("%.2f km^2\n", v1);
    else if (atributo == ATTR_PIB) printf("%.2f\n", v1);
    else if (atributo == ATTR_DENSIDADE) printf("%.2f hab/km^2\n", v1);
    else if (atributo == ATTR_PIB_PER_CAPITA) printf("%.2f\n", v1);

    printf("Carta 2 - %s (%s): ", carta2.cidade, carta2.estado);
    if (atributo == ATTR_POPULACAO) printf("%.0f\n", v2);
    else if (atributo == ATTR_AREA) printf("%.2f km^2\n", v2);
    else if (atributo == ATTR_PIB) printf("%.2f\n", v2);
    else if (atributo == ATTR_DENSIDADE) printf("%.2f hab/km^2\n", v2);
    else if (atributo == ATTR_PIB_PER_CAPITA) printf("%.2f\n", v2);

    /* Lógica de comparação usando if / if-else */
    double eps = 1e-9; /* tolerância para igualdade em números de ponto flutuante */

    if (fabs(v1 - v2) <= eps) {
        printf("\nResultado: Empate técnico! Ambos os valores são iguais.\n");
    } else {
        int menor_vence = menor_valor_vencedor(atributo);
        int carta1_vence = 0;

        if (menor_vence) {
            /* menor valor vence (apenas para densidade) */
            if (v1 < v2) carta1_vence = 1; else carta1_vence = 0;
        } else {
            /* maior valor vence */
            if (v1 > v2) carta1_vence = 1; else carta1_vence = 0;
        }

        printf("\nResultado: ");
        if (carta1_vence) printf("Carta 1 (%s) venceu!\n", carta1.cidade);
        else printf("Carta 2 (%s) venceu!\n", carta2.cidade);
    }

    return 0;
}
