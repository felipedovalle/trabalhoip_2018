#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "usuario.h"
#include "familia.h"
#include "planta.h"

/*	
	*************** TODO *************** 
	-> Ano do plantio não pode ser negativo // PRONTO
	-> Todos os campos são obrigatórios // INCOMPLETO NA SEÇÃO DE PLANTAS
	-> Só é permitido excluir uma família se não houver plantas vinculados a ela. // PRONTO
	-> Análise de dados (Relatório HTML) // PRONTO
	-> Organizar os menus (ordem, etc) // PRONTO
	-> Alterar nomes de funções (ex: montarMenu) // PRONTO
	-> Alterar nome dos arquivos (ex: principal.c)
	-> Documentar código // 2/3 PRONTO
	-> Duas formas de sort (opção do menu listar) // PRONTO
	-> Organizar listagem (formato tabela)
	-> Alterar função checa_vazio para checar se o arquivo existe
	-> Criar função para alterar o código das famílias (em: elemento.c) // PRONTO
	************************************ 
*/

void montarMenu(INFO_USUARIO *usuario, int *total_u, int *logado);
void menu_usuario(INFO_USUARIO *usuario, int *total_u, int *logado);
void menu_categoria();
void menu_elementos();
INFO_USUARIO *checa_usuario();

int main()
{
	checa_usuario();
	return 0;
}

INFO_USUARIO *checa_usuario()
{
	int total = 0, usuario_logado = 0, n_usuario = 0, flag_deleta = -1;
	int checa;
	INFO_USUARIO *usuario = read(&total);
	INFO_USUARIO *inclui;

	usuario = read(&total);
	sort(usuario, &total);
	write(usuario, &total, flag_deleta);

	//free(usuario);

	while (1)
	{
		if (checa_vazio() == 0)
		{
			//clear();
			printf("Ainda não há usuários cadastrados no sistema!\n");
			printf("Para prosseguir, realize o cadastro:\n");
			incluir_usuario(inclui, usuario, n_usuario, total);

			//free(inclui);

			usuario = read(&total);
		}
		else
		{
			clear();
			usuario = read(&total);
			if (login_acesso(usuario, &total, &usuario_logado) == 1)
			{
				montarMenu(usuario, &total, &usuario_logado);
				return usuario;
			}
		}
	}
}

void analise_dados(INFO_FAMILIA *familia, INFO_PLANTA *planta,
				   int *tFamilias, int *tPlantas)
{
	FILE *arq;
	arq = fopen("relatorio.html", "w");

	int i, j, countQtd = 0;

	fprintf(arq, "<html>\n");
	fprintf(arq, "<head>\n");
	fprintf(arq, "\t<meta charset="
				 "UTF-8"
				 ">\n");
	fprintf(arq, "</head>\n");
	fprintf(arq, "<body>\n");
	fprintf(arq, "\t<h1>Análise de Dados</h1>\n\n");
	fprintf(arq, "\t<h2>Resumo por Família</h2>\n");
	fprintf(arq, "\t\t<ul>\n");

	i = 0;
	while (i < (*tFamilias))
	{
		fprintf(arq, "\t\t\t<li> Família %s: \n", familia[i].nome_f);
		for (j = 0; j < (*tPlantas); j++)
		{
			if (familia[i].codigo_f == planta[j].cod_familia)
			{
				countQtd++;
			}
		}
		fprintf(arq, "%d </li>\n", countQtd);
		countQtd = 0;
		i++;
	}
	fprintf(arq, "\t\t<ul>\n");
	fprintf(arq, "\t<hr/>\n\n");
	fprintf(arq, "\t<h2>Relação de plantas no sistema</h2>\n\n");
	fprintf(arq, "\t<table border="
				 "1"
				 ">\n");

	fprintf(arq, "\t\t<tr>\n");
	for (i = 0; i < (*tPlantas); i++)
	{
		fprintf(arq, "\t\t\t<td>Nome da planta: %s</td>\n", planta[i].nomePlanta);
	}
	fprintf(arq, "\t\t</tr>\n");

	fprintf(arq, "\t\t<tr>\n");
	for (i = 0; i < (*tPlantas); i++)
	{
		if (planta[i].p_frutifera == 'S')
		{
			fprintf(arq, "\t\t\t<td>Frutífera</td>\n");
		}
		else
		{
			fprintf(arq, "\t\t\t<td>Não frutífera</td>\n");
		}
	}
	fprintf(arq, "\t\t</tr>\n");

	fprintf(arq, "\t\t<tr>\n");
	for (i = 0; i < (*tPlantas); i++)
	{
		fprintf(arq, "\t\t\t<td>R$ %.2f</td>\n", planta[i].valor_venda);
	}
	fprintf(arq, "\t\t</tr>\n");

	fprintf(arq, "\t\t<tr>\n");
	for (i = 0; i < (*tPlantas); i++)
	{
		fprintf(arq, "\t\t\t<td>Número de identificação: %d</td>\n", planta[i].numeroIdPlanta);
	}
	fprintf(arq, "\t\t</tr>\n");

	fprintf(arq, "\t\t<tr>\n");
	for (i = 0; i < (*tPlantas); i++)
	{
		fprintf(arq, "\t\t\t<td>Ano de plantio: %d</td>\n", planta[i].ano_plantio);
	}
	fprintf(arq, "\t\t</tr>\n");

	fprintf(arq, "\t\t<tr>\n");
	for (i = 0; i < (*tPlantas); i++)
	{
		fprintf(arq, "\t\t\t<td>Código da família: %d</td>\n", planta[i].cod_familia);
	}
	fprintf(arq, "\t\t</tr>\n");
	fprintf(arq, "\t</table>\n");
	fprintf(arq, "</body>\n");
	fprintf(arq, "</html>\n");
}

void montarMenu(INFO_USUARIO *usuario, int *total_u, int *logado)
{
	int menu;
	int total, total_f, usuario_logado, totalFamilia, totalPlantas;
	total = *total_u;
	usuario_logado = *logado;

	INFO_FAMILIA *familia = read_f(&totalFamilia);
	INFO_PLANTA *planta = read_e(&totalPlantas);

	while (1)
	{
		printf("1 - Plantas\n");
		printf("2 - Famílias\n");
		printf("3 - Análise de dados\n");
		printf("4 - Controle de acesso\n");
		printf("0 - Sair\n");
		scanf("%d", &menu);

		switch (menu)
		{
		case 1:
			clear();
			menu_elementos();
			break;
		case 2:
			menu_categoria();
			break;

		case 3:
			familia = read_f(&totalFamilia);
			planta = read_e(&totalPlantas);
			analise_dados(familia, planta, &totalFamilia, &totalPlantas);
			clear();
			printf("Análise de dados completa!\n");
			break;

		case 4:
			menu_usuario(usuario, &total, &usuario_logado);
			break;

		case 0:
			exit(0);
		}
	}
}
