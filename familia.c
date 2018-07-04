#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "familia.h"

void menu_categoria()
{
    clear_c();
	int menu, total, n_familia = 0, flag_deleta = -1, menuSort;
    int *planta, total_p;
	//total = *total_c;
    INFO_FAMILIA *familia = read_f(&total);
    INFO_FAMILIA *inclui_f;
    planta = read_planta(&total_p);
    

    if(checa_vazioF() == 0)
    {
        printf("Ainda não há nenhuma família cadastrada!\n");
        printf("Para que possa prossiga, realize o cadastro:\n");
        incluir_familia(inclui_f, familia, n_familia, total);
    }
    
    

	//clear_c();
	printf("1 - Incluir família\n");
	printf("2 - Listar famílias\n");
	printf("3 - Excluir família\n");
	printf("0 - Voltar ao menu principal\n");
	scanf("%d", &menu);

	switch(menu)
	{
		case 1:
			clear_c();
			familia = read_f(&total);
			incluir_familia(inclui_f, familia, n_familia, total);
			total++;
			break;

		case 2:
            clear_c();
            familia = read_f(&total);
			
            printf("Ordenar famílias por:\n");
            printf("1 - Código de identificação (crescente)\n");
            printf("2 - Ordem alfabética\n");
            scanf("%d", &menuSort);
            if(menuSort == 1)
            {
                sort_familiasId(familia, &total);
            }
            else if(menuSort == 2)
            {
                sort_familiasNome(familia, &total);
            }

			listar_familia(familia, &total);
			break;

		case 3:
            familia = read_f(&total);
			flag_deleta = excluir_familia(familia, &total, planta, &total_p);
			break;

		case 0:
			clear_c();
			break;
	}
	familia = read_f(&total);
	write_f(familia, &total, flag_deleta);
}

void clear_c()
{
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");

    #endif
}

int checa_vazioF()
{
	FILE *arq;
	arq = fopen("familias.txt", "r");

	int size;
	if (arq != NULL) 
	{
	    fseek (arq, 0, SEEK_END);
	    size = ftell(arq);
    }
    return size;

    fclose(arq);
}

INFO_FAMILIA *read_f(int *f_total)
{
    FILE *arq;
    arq = fopen("familias.txt", "r");

    int c;
    char enter;
    *f_total = 0;


    INFO_FAMILIA *familia = malloc(sizeof(INFO_FAMILIA) * ((*f_total) + 1));

    while((c = fgetc(arq)) != EOF)
    {
        ungetc(c, arq);
        fscanf(arq, "%d %50[^\n]", &familia[(*f_total)].codigo_f, 
                                    familia[(*f_total)].nome_f);
        fscanf(arq, "%c", &enter);
        
        (*f_total)++;
        familia = realloc(familia, sizeof(INFO_FAMILIA) * ((*f_total) + 1));
    } 

    fclose(arq);
    return familia;
}

void incluir_familia(INFO_FAMILIA *inclui_f, INFO_FAMILIA *familia, int n_familia, int total_f)
{
    FILE *arq;
    arq = fopen("familias.txt", "a");

    char nome_fam[50];
    int codigo_fam, i;

    if(n_familia == 0)
    {
        inclui_f = malloc(sizeof(INFO_FAMILIA) * (n_familia + 1));
    }
    else
    {
        inclui_f = realloc(inclui_f, sizeof(INFO_FAMILIA) * (n_familia + 1));
    }

    printf("Insira o código da família a ser adicionada: ");
    scanf("%d", &inclui_f[n_familia].codigo_f);

    igual: i = 0;
    while(i < total_f)
    {
        if(inclui_f[n_familia].codigo_f == familia[i].codigo_f)
        {
            clear_c();
            printf("Já existe uma família cadastrada com o código inserido!\n");
            printf("Para prosseguir, insira o código desejado: ");
            scanf("%d", &inclui_f[n_familia].codigo_f);

            goto igual;
        }
        i++;
    }

    getchar();
    printf("Insira o nome da família a ser usado: ");
    scanf(" %50[^\n]", inclui_f[n_familia].nome_f);

    fprintf(arq, "%d\t%s\n", inclui_f[n_familia].codigo_f, inclui_f[n_familia].nome_f);

    clear_c();
    printf("Família cadastrada com sucesso!\n");

    n_familia++;

    free(inclui_f);

    fclose(arq);
}

int *read_planta(int *p_total)
{
    FILE *arq;
    arq = fopen("plantas.txt", "r");
 
    char enter, buffer[50], buffer2;
    int c, buffer3, buffer4, idFamilia;
    float buffer5;
    *p_total = 0;
 
    int *planta = malloc(sizeof(int) * ((*p_total) + 1));
 
    while((c = fgetc(arq)) != EOF)
    {
        ungetc(c, arq);
 
        fscanf(arq, "%50[^\t] %c %f %d %d %d", buffer, &buffer2, &buffer5, &buffer3,
         &buffer4, &planta[(*p_total)]);
 
        fscanf(arq, "%c", &enter);
 
        (*p_total)++;
 
        planta = realloc(planta, sizeof(int) * ((*p_total) + 1));
    }
    fclose(arq);

    return planta;
}

int checa_planta(int *planta, int codDeleta, int *p_total)
{
    int i;
    i = 0;

    while(i <= (*p_total))
    {
        if(planta[i] == codDeleta)
        {
            return 1;
        }
        i++;
    }
    return 0;
}

void listar_familia(INFO_FAMILIA *familia, int *f_total)
{
    clear_c();
    int i = 0;
    while(i < (*f_total))
    {
        printf("%-10d\t%-10s\n", familia[i].codigo_f, familia[i].nome_f);
        i++;
    }
}

int excluir_familia(INFO_FAMILIA *familia, int *f_total, int *planta, int *p_total)
{
    int codigo_deleta, flag_deleta = 0, checa = 0;
    clear_c();
    
    familia: printf("Insira o código da família a ser deletada: ");
    scanf("%d", &codigo_deleta);

    if(checa_planta(planta, codigo_deleta, p_total) == 1)
    {
        printf("Não é possível deletar uma família se houver plantas nela cadastradas.\n");
        goto familia;
    }

    if(codigo_deleta == familia[flag_deleta].codigo_f)
    {
        checa = 1;
    }
    while(flag_deleta <= (*f_total))
    {
        if(checa == 1)
        {
            clear_c();
            printf("Família %s deletada com sucesso!\n", familia[flag_deleta].nome_f);
            return flag_deleta;
        }
        flag_deleta++;

        if(codigo_deleta == familia[flag_deleta].codigo_f)
        {
            checa = 1;
        }
    }
    if(checa == 0)
    {
        printf("Não há nenhuma família presente no sistema com o código inserido.\n");
    }
    (*f_total)--;
}

void write_f(INFO_FAMILIA *familia, int *f_total, int flag)
{
    FILE *arq;
    arq = fopen("familias.txt", "w");

    int i = 0;
    while(i < (*f_total))
    {
        if(i != flag)
        {
            fprintf(arq, "%d\t%s\n", familia[i].codigo_f, familia[i].nome_f);
        }
        i++;
    }
    fclose(arq);
}

INFO_FAMILIA *sort_familiasId(INFO_FAMILIA *familia, int *f_total)
{
    INFO_FAMILIA temp;
    int i, j;

    for(i = 0; i < (*f_total); i++)
    {
        for(j = i + 1; j < (*f_total); j++)
        {
            if(familia[i].codigo_f > familia[j].codigo_f)
            {
                temp = familia[i];
                familia[i] = familia[j];
                familia[j] = temp;
            }
        }
    }
	return familia;
}

INFO_FAMILIA *sort_familiasNome(INFO_FAMILIA *familia, int *f_total)
{
    INFO_FAMILIA temp;
    int i, j;

    for(i = 0; i < (*f_total); i++)
    {
        for(j = i + 1; j < (*f_total); j++)
        {
            if(strcasecmp(familia[i].nome_f, familia[j].nome_f) > 0)
            {
                temp = familia[i];
                familia[i] = familia[j];
                familia[j] = temp;
            }
        }
    }
	return familia;
}