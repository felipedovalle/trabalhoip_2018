#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "planta.h"
#define STR_MAX 50

void menu_elementos()
{
    int menu, total_p = 0, n_planta = 0, total_f, menuSort;
	int *familia, flagDeleta = - 1;
    INFO_PLANTA *inclui_p;
    INFO_PLANTA *planta = read_e(&total_p);
	familia = read_familia(&total_f);
 
    if(checa_vazioP() == 0)
    {
        printf("Ainda não há nenhuma planta cadastrada!\n");
        printf("Para que possa prossiga, realize o cadastro:\n");
        incluir_planta(inclui_p, planta, n_planta, total_p, familia, &total_f);
    }
 
    clear_e();
    printf("1 - Incluir planta\n");
    printf("2 - Consultar planta\n");
    printf("3 - Listar plantas\n");
    printf("4 - Excluir planta\n");
    printf("5 - Alterar planta\n");
    printf("0 - Voltar ao menu principal\n");
    scanf("%d", &menu);
 
    planta = read_e(&total_p);
    switch(menu)
    {
        case 1:
            incluir_planta(inclui_p, planta, n_planta, total_p, familia, &total_f);
            break;
 
        case 2:
            consultar_p(planta, &total_p);
            break;
 
        case 3:
            planta = read_e(&total_p);

            printf("Ordenar plantas por:\n");
            printf("1 - Número de identificação (crescente)\n");
            printf("2 - Ordem alfabética\n");
            scanf("%d", &menuSort);
            if(menuSort == 1)
            {
                sort_plantasId(planta, &total_p);
            }
            else if(menuSort == 2)
            {
                sort_plantasNome(planta, &total_p);
            }

            listar_plantas(planta, &total_p);
            break;
 
        case 4:
            flagDeleta = exclui_planta(planta, &total_p);
			write_p(planta, &total_p, flagDeleta);
            break;
 
        case 5:
            planta = alterar_dados(planta, &total_p, familia, &total_f);
			write_p(planta, &total_p, flagDeleta);
            break;
 
        case 0:
            clear_e();
            break;
    }
   	planta = read_e(&total_p);
    write_p(planta, &total_p, flagDeleta);
}

void clear_e()
{
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif
 
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

int checa_vazioP()
{
    FILE *arq;
    arq = fopen("plantas.txt", "r");
 
    int size;
    if (arq != NULL) 
    {
        fseek (arq, 0, SEEK_END);
        size = ftell(arq);
    }
    return size;
 
    fclose(arq);
}
 
INFO_PLANTA *read_e(int *p_total)
{
    FILE *arq;
    arq = fopen("plantas.txt", "r");
 
    int c;
    char enter;
    *p_total = 0;
 
    INFO_PLANTA *planta = malloc(sizeof(INFO_PLANTA) * ((*p_total) + 1));
 
    while((c = fgetc(arq)) != EOF)
    {
        ungetc(c, arq);
 
        fscanf(arq, "%50[^\t] %c %f %d %d %d", planta[(*p_total)].nomePlanta,
         &planta[(*p_total)].p_frutifera, &planta[(*p_total)].valor_venda,
         &planta[(*p_total)].numeroIdPlanta, &planta[(*p_total)].ano_plantio,
         &planta[(*p_total)].cod_familia);
 
        fscanf(arq, "%c", &enter);
 
        (*p_total)++;
 
        planta = realloc(planta, sizeof(INFO_PLANTA) * ((*p_total) + 1));
    }
    fclose(arq);
    return planta;
}

int *read_familia(int *f_total)
{
    FILE *arq;
    arq = fopen("familias.txt", "r");
 
    int c;
    char enter, buffer[STR_MAX];
    *f_total = 0;
 
    int *familia = malloc(sizeof(int) * ((*f_total) + 1));
 
    while((c = fgetc(arq)) != EOF)
    {
        ungetc(c, arq);
 
        fscanf(arq, "%d %50[^\n]", &familia[(*f_total)], buffer);
 
        fscanf(arq, "%c", &enter);
 
        (*f_total)++;
 
        familia = realloc(familia, sizeof(int) * ((*f_total) + 1));
    }
    fclose(arq);

    return familia;
}

int checa_familia(int *familia, INFO_PLANTA *inclui_p, int *f_total, int n_planta)
{
    int i;
    i = 0;

    while(i <= (*f_total))
    {
        if(familia[i] == inclui_p[n_planta].cod_familia)
        {
            return 1;
        }
        i++;
    }
    return 0;
}
 
void incluir_planta(INFO_PLANTA *inclui_p, INFO_PLANTA *planta, int n_planta,
                    int total_p, int *familia, int *f_total)
{
    FILE *arq;
    arq = fopen("plantas.txt", "a");
 
    char nomePlanta[STR_MAX], a_compara[STR_MAX], b_compara[STR_MAX];
    int codigo_fam, i, contaCampos = 0;
 
    if(n_planta == 0)
    {
        inclui_p = malloc(sizeof(INFO_PLANTA) * (n_planta + 1));
    }
    else
    {
        inclui_p = realloc(inclui_p, sizeof(INFO_PLANTA) * (n_planta + 1));
    }
 
    camposIncompletos2: printf("Insira o código da família da planta a ser adicionada: ");
    contaCampos = scanf("%d", &inclui_p[n_planta].cod_familia);
    while(1)
    {
        if(checa_familia(familia, inclui_p, f_total, n_planta) == 1)
            break;
        else if(checa_familia(familia, inclui_p, f_total, n_planta) == 0)
        {
            printf("É apenas permitido o cadastro de plantas em famílias já existentes.\n");
            printf("Insira o código da família da planta a ser adicionada: ");
            scanf("%d", &inclui_p[n_planta].cod_familia);
            break;
        }
    }
 
    // aninhamento de laços de repetição usando while e goto.
    // caso o nome da planta inserido não esteja presente no sistema,
    // o aninhamento é quebrado
    printf("Insira o nome da planta: ");
    contaCampos = scanf(" %50[^\n]", inclui_p[n_planta].nomePlanta) + (contaCampos);
    igual: strcpy(a_compara, inclui_p[n_planta].nomePlanta);
    i = 0;
    strcpy(b_compara, planta[i].nomePlanta);
    while(i < total_p)
    {
        if(strcmp(a_compara, b_compara) == 0)
        {
            clear_e();
            printf("Já existe uma planta cadastrada com o nome inserido!\n");
            printf("Para prosseguir, insira o nome desejado: ");
            scanf(" %50[^\n]", inclui_p[n_planta].nomePlanta);
 
            goto igual;
        }
        i++;
    }
 
    printf("Insira o código de identificação da planta a ser adicionada: ");
    contaCampos += scanf(" %d", &inclui_p[n_planta].numeroIdPlanta);
 
    igual_b: i = 0;
    while(i < total_p)
    {
        if(inclui_p[n_planta].numeroIdPlanta == planta[i].numeroIdPlanta)
        {
            clear_e();
            printf("Já existe uma planta cadastrada com o código inserido!\n");
            printf("Para prosseguir, insira o código desejado: ");
            scanf("%d", &inclui_p[n_planta].numeroIdPlanta);
 
            goto igual_b;
        }
        i++;
    }
 
    printf("Insira se a planta é frutífera ou não (S/N): ");
    contaCampos += scanf(" %c", &inclui_p[n_planta].p_frutifera);
    if(inclui_p[n_planta].p_frutifera != 'S' && inclui_p[n_planta].p_frutifera != 'N')
    {
        while(1)
        {
            printf("O dado inserido é inválido. Tente novamente (S/N): ");
            scanf(" %c", &inclui_p[n_planta].p_frutifera);
            if(inclui_p[n_planta].p_frutifera == 'S' || inclui_p[n_planta].p_frutifera == 'N')
                break;
        }
    }
 
    printf("Insira o valor de venda da planta: ");
    contaCampos += scanf(" %f", &inclui_p[n_planta].valor_venda);
 
    printf("Insira o ano de plantio da planta: ");
    contaCampos += scanf(" %d", &inclui_p[n_planta].ano_plantio);
    while(1)
    {
        if(inclui_p[n_planta].ano_plantio > 0)
        {
            break;
        }
        printf("\nNão são aceitos valores negativos para ano de plantio.\n");
        printf("Insira o ano de plantio da planta: ");
        scanf(" %d", &inclui_p[n_planta].ano_plantio);
    }

    if(contaCampos != 6)
    {
        printf("É obrigatório o preenchimento de todos os campos!\n");
		printf("Para continuar, refaça o cadastro:\n");
		goto camposIncompletos2;
    }
 
    fprintf(arq, "%s\t%c\t%.2f\t%d\t%d\t%d\n", inclui_p[n_planta].nomePlanta,
         inclui_p[n_planta].p_frutifera, inclui_p[n_planta].valor_venda,
         inclui_p[n_planta].numeroIdPlanta, inclui_p[n_planta].ano_plantio,
         inclui_p[n_planta].cod_familia);
 
    clear_e();
    printf("Planta cadastrada com sucesso!\n");
 
    n_planta++;
 
    free(inclui_p);
 
    fclose(arq);
}

INFO_PLANTA *sort_plantasId(INFO_PLANTA *planta, int *p_total)
{
    INFO_PLANTA temp;
    int i, j;

    for(i = 0; i < (*p_total); i++)
    {
        for(j = i + 1; j < (*p_total); j++)
        {
            if(planta[i].numeroIdPlanta > planta[j].numeroIdPlanta)
            {
                temp = planta[i];
                planta[i] = planta[j];
                planta[j] = temp;
            }
        }
    }
	return planta;
}

INFO_PLANTA *sort_plantasNome(INFO_PLANTA *planta, int *p_total)
{
    INFO_PLANTA temp;
    int i, j;

    for(i = 0; i < (*p_total); i++)
    {
        for(j = i + 1; j < (*p_total); j++)
        {
            if(strcasecmp(planta[i].nomePlanta, planta[j].nomePlanta) > 0)
            {
                temp = planta[i];
                planta[i] = planta[j];
                planta[j] = temp;
            }
        }
    }
	return planta;
}
 
void listar_plantas(INFO_PLANTA *planta, int *p_total)
{
    clear_e();
    int i = 0;

    while(i < (*p_total))
    {
        printf("%-10s\t%-5c\t%-5.2f\t%10d\t%-5d\t%-5d\n", planta[i].nomePlanta,
         planta[i].p_frutifera, planta[i].valor_venda,
         planta[i].numeroIdPlanta, planta[i].ano_plantio,
         planta[i].cod_familia);
        i++;
    }
}
 
int exclui_planta(INFO_PLANTA *planta, int *p_total)
{
    char nome[STR_MAX];
    int checaNome, codigoId, linhaFlag = 0, total, menu;
 
    total = *p_total;
 
    clear_e();
    printf("Deletar uma planta do sistema usando:\n");
    printf("1 - Nome da planta\n");
    printf("2 - Código de identificação da planta\n");
    scanf("%d", &menu);
 
    if(menu == 1)
    {
        printf("Insira o nome da planta: ");
        scanf("%s", nome);
        checaNome = strcmp(nome, planta[linhaFlag].nomePlanta);
 
        while(linhaFlag <= (*p_total))
        {
            if(checaNome == 0)
            {
                clear_e();
                printf("Planta %s deletada com sucesso!\n", planta[linhaFlag].nomePlanta);
 
                return linhaFlag;
            }
 
            linhaFlag++;
 
            checaNome = strcmp(nome, planta[linhaFlag].nomePlanta);
        }
        (*p_total)--;
    }
    else if(menu == 2)
    {
        printf("Insira o código de identificação da planta: ");
        scanf("%d", &codigoId);
        while(linhaFlag <= (*p_total))
        {
            if(codigoId == planta[linhaFlag].numeroIdPlanta)
            {
                clear_e();
                printf("Planta %s deletada com sucesso!\n", planta[linhaFlag].nomePlanta);
 
                return linhaFlag;
            }
            linhaFlag++;
        }
    }
}

void write_p(INFO_PLANTA *planta, int *p_total, int flagDeleta)
{
    FILE *arq;
    arq = fopen("plantas.txt", "w");
 
    int i = 0;
    while(i < (*p_total))
    {
        if(i != flagDeleta)
        {
            fprintf(arq, "%s\t%c\t%.2f\t%d\t%d\t%d\n", planta[i].nomePlanta,
                planta[i].p_frutifera, planta[i].valor_venda,
                planta[i].numeroIdPlanta, planta[i].ano_plantio,
                planta[i].cod_familia);
        }
        i++;
    }
    fclose(arq);
}
 
void consultar_p(INFO_PLANTA *planta, int *p_total)
{
    FILE *arq;
    arq = fopen("plantas.txt", "r");
 
    int i, codigoId;
 
    clear_e();
    printf("Insira o código de identificação da planta a ser consultada: ");
    scanf("%d", &codigoId);
 
    i = 0;
    while(i <= (*p_total))
    {
        if(codigoId == planta[i].numeroIdPlanta)
        {
            clear_e();
            printf("Nome da planta: %s\n", planta[i].nomePlanta);
            printf("Código de identificação da planta: %d\n", planta[i].numeroIdPlanta);
            printf("Código da família da planta: %d\n", planta[i].cod_familia);
            printf("Frutífera: ");
            if(planta[i].p_frutifera == 'S')
                printf("Sim\n");
            else
                printf("Não\n");
            printf("Ano de plantio: %d\n", planta[i].ano_plantio);
            printf("Valor de venda: R$ %.2f\n", planta[i].valor_venda);
            printf("=================================\n");
        }
        i++;
    }
}
 
void altera_nome(INFO_PLANTA *planta, int flagPlanta)
{
    char nome[STR_MAX];
 
    clear_e();
    printf("Insira o nome que substituirá o atual: ");
    scanf("%s", nome);
    printf("\n");
 

    strcpy(planta[flagPlanta].nomePlanta, nome);
    printf("Alteração realizada com sucesso!\n");
}

void altera_numeroId(INFO_PLANTA *planta, int flagPlanta)
{
    int numeroId;

    clear_e();
    printf("Insira o código que substituirá o atual: ");
    scanf("%d", &numeroId);
    printf("\n");

    planta[flagPlanta].numeroIdPlanta = numeroId;
    printf("Alteração realizada com sucesso!\n");
}

void altera_frutifera(INFO_PLANTA *planta, int flagPlanta)
{
    char frutifera;
 
    clear_e();
    printf("Insira se a planta é frutífera ou não (S/N): ");
    scanf(" %c", &frutifera);
    printf("\n");
 

    planta[flagPlanta].p_frutifera = frutifera;
    printf("Alteração realizada com sucesso!\n");
}

void altera_anoPlantio(INFO_PLANTA *planta, int flagPlanta)
{
    int anoPlantio;

    clear_e();
    printf("Insira o ano de plantio que substituirá o atual: ");
    scanf("%d", &anoPlantio);
    printf("\n");

    planta[flagPlanta].ano_plantio = anoPlantio;
    printf("Alteração realizada com sucesso!\n");
}

void altera_valorVenda(INFO_PLANTA *planta, int flagPlanta)
{
    float valorVenda;
    clear_e();
    printf("Insira o valor de venda que substituirá o atual: ");
    scanf("%f", &valorVenda);
    printf("\n");

    planta[flagPlanta].valor_venda = valorVenda;
    printf("Alteração realizada com sucesso!\n");
}

void altera_codigoFam(INFO_PLANTA *planta, int flagPlanta, int *familia, int *f_total)
{
    int codigoFamilia, i;

    clear_e();
    printf("Insira o código de família que substituíra o atual: ");
    scanf("%d", &codigoFamilia);

    i = 0;
    while(i <= (*f_total))
    {
        if(familia[i] == codigoFamilia)
        {
            planta[flagPlanta].cod_familia = codigoFamilia;
            printf("Alteração realizada com sucesso!\n");
            break;
        }
        else
        {
            printf("Código de família não existente no sistema. Tente novamente.\n");
        }
        printf("Insira o código de família que substituíra o atual: ");
        scanf("%d", &codigoFamilia);
        i++;
    }

}

INFO_PLANTA *alterar_dados(INFO_PLANTA *planta, int *p_total, int *familia, int *f_total)
{
    int i, codigoId, menu;
    int *flagDeleta;
 
    clear_e();
    printf("Insira o código de identificação da planta que deseja realizar alterações: ");
    scanf("%d", &codigoId);
 
    i = 0;
    while(i <= (*p_total))
    {
        if(codigoId == planta[i].numeroIdPlanta)
        {
            clear_e();
            printf("Nome da planta: %s\n", planta[i].nomePlanta);
            printf("Código de identificação da planta: %d\n", planta[i].numeroIdPlanta);
            printf("Código da família da planta: %d\n", planta[i].cod_familia);
            printf("Frutífera: ");
            if(planta[i].p_frutifera == 'S')
                printf("Sim\n");
            else
                printf("Não\n");
            printf("Ano de plantio: %d\n", planta[i].ano_plantio);
            printf("Valor de venda: R$ %.2f\n", planta[i].valor_venda);

            break;
        }
        i++;
    }
    printf("=================================\n");
    printf("Qual dado deseja modificar:\n");
    printf("1 - Nome da planta\n");
    printf("2 - Código de identificação da planta\n");
    printf("3 - Código da família da planta\n");
    printf("4 - Condição de dar frutos (S/N)\n");
    printf("5 - Ano de plantio\n");
    printf("6 - Valor de venda\n");
    scanf("%d", &menu);
 
    switch(menu)
    {
        case 1:
            altera_nome(planta, i);
            break;
        
        case 2:
            altera_numeroId(planta, i);
            break;

        case 3:
            altera_codigoFam(planta, i, familia, f_total);
            break;

        case 4:
            altera_frutifera(planta, i);
            break;

        case 5:
            altera_anoPlantio(planta, i);
            break;
        case 6:
            altera_valorVenda(planta, i);
            break;
    }
    return planta;
}