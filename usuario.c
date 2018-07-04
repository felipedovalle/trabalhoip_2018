#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "usuario.h"
#define STR_MAX 50

void menu_usuario(INFO_USUARIO *usuario, int *total_u, int *logado)
{
	int menu, flag, flag_deleta = -1;
	int n_usuario = 0, total, usuario_logado;
	total = *total_u;
	INFO_USUARIO *inclui;
	usuario_logado = *logado;

	clear();
	printf("1 - Incluir usuario\n");
	printf("2 - Excluir usuario\n");
	printf("3 - Listar usuários (em ordem alfabética de nome)\n");
	printf("4 - Alterar senha do usuário\n");
	printf("0 - Voltar para o menu principal\n");
	scanf("%d", &menu);

	switch(menu)
	{
		case 1:
			clear();
			usuario = read(&total);
			incluir_usuario(inclui, usuario, n_usuario, total);
			usuario = read(&total);
			(*total_u)++;
			break;

		case 2:
			clear();
			usuario = read(&total);
			flag_deleta = deleta_usuario(usuario, &total);
			usuario = read(&total);
			break;

		case 3:
			clear();
			usuario = read(&total);
			sort(usuario, &total);
			write(usuario, &total, flag_deleta);
			listar_usuario(usuario, &total);
			break;

		case 4:
			usuario = read(&total);
			alterar_senha(usuario, &usuario_logado);
			break;

		case 0:
			clear();
			break;
	}
	write(usuario, &total, flag_deleta);
}

int checa_vazio()
{
	FILE *arq;
	arq = fopen("usuarios.txt", "r");

	int size;
	if (arq != NULL) 
	{
	    fseek (arq, 0, SEEK_END);
	    size = ftell(arq);
    }
    return size;

    fclose(arq);
}

void clear()
{
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

void criptografa_senha(char *senha)
{	
	int n_testes, i = 0, j = 0;
	char temp;

	j = 0;
	while(j < strlen(senha))
	{
		if(isalpha(senha[j]) != 0 || isupper(senha[j]) != 0 || isdigit(senha[j]) != 0)
		{
			senha[j] += 3;
		}
		j++;
	}
	
	for(j = 0; j < strlen(senha); j += 2)
	{
		if(j == (strlen(senha) - 1))
		{
			break;
		}	
	    temp = senha[j];
	    senha[j] = senha[j + 1];
	    senha[j + 1] = temp;
    }

    j = 0;
	while(j < strlen(senha))
	{
		if(isspace(senha[j]) != 0)
		{
			senha[j] = '+';
		}
		else if(senha[j] == '+')
		{
			senha[j] = ' ';
		}
		j++;
	}
}

void incluir_usuario(INFO_USUARIO *inclui, INFO_USUARIO *usuario, int n_usuario, int total)
{
	FILE *arq;
	arq = fopen("usuarios.txt", "a");

	char senha[STR_MAX], nome[STR_MAX], login[STR_MAX];
	char compara_a[STR_MAX], compara_b[STR_MAX];
	int tam = 0, u_total, i, procura_igual, contaCampos = 0;
	
	if(n_usuario == 0)
	{
		inclui = malloc(sizeof(INFO_USUARIO) * (n_usuario + 1));
	}
	else
	{
		inclui = realloc(inclui, sizeof(INFO_USUARIO) * (n_usuario + 1));
	}

	printf("Insira o login a ser usado: ");
	scanf(" %50[^\n]", inclui[n_usuario].login_u);
	getchar();

	igual: strcpy(compara_a, inclui[n_usuario].login_u);
	i = 0;
	strcpy(compara_b, usuario[i].login_u);
	while(i < total)
	{
		if(strcmp(compara_a, compara_b) == 0)
		{
			clear();
			printf("Já existe um usuário com o login inserido!\n");
			printf("Para continuar, insira o login desejado: ");
			scanf("%s", inclui[n_usuario].login_u);
			getchar();
			goto igual;
		}
		i++;
		strcpy(compara_b, usuario[i].login_u);
	}

	senhaMin: printf("Insira a senha a ser usada (min. 3 digitos): ");
	scanf("%50[^\n]", senha);
	getchar();

	tam = strlen(senha);

	if(tam < 3)
	{
		printf("O tamanho mínimo para a senha é de 3 dígitos. Tente novamente.\n");
		goto senhaMin;
	}
	
	criptografa_senha(senha);

	strcpy(inclui[n_usuario].senha_u, senha);


	printf("Insira o nome do(a) usuario(a): ");
	scanf(" %50[^\n]", inclui[n_usuario].nome_u);
	getchar();

	fprintf(arq, "%s\t%s\t%s\n", inclui[n_usuario].login_u, inclui[n_usuario].senha_u, inclui[n_usuario].nome_u);

	printf("Usuario(a) cadastrado com sucesso!\n\n");

	n_usuario++;

	free(inclui);

	fclose(arq);
}

void listar_usuario(INFO_USUARIO *usuario, int *u_total)
{
	clear();
	int i = 0;
	while(i < (*u_total))
	{	
		printf("%-10s\t%-10s\t%-10s\n", usuario[i].login_u, usuario[i].senha_u, usuario[i].nome_u);
		i++;
	}	
}

int login_acesso(INFO_USUARIO *usuario, int *total_u, int *logado)
{
	FILE *arq;
	arq = fopen("usuarios.txt", "r");

	int tam = 0, c, i = 0;
	int senhaCheck, loginCheck;
	*logado = 0;
	char login[STR_MAX], senha[STR_MAX];

	printf("Login do usuario: ");
	scanf("%s", login);

	printf("Senha do usuario: ");
	scanf("%s", senha);

	criptografa_senha(senha);

	fscanf(arq, " %50[^\t] %50[^\t]%[^\n]", usuario[i].login_u, usuario[i].senha_u, usuario[i].nome_u);

	senhaCheck = strcmp(senha, usuario[i].senha_u);
	loginCheck = strcmp(login, usuario[i].login_u);

	while(i < (*total_u))
	{
		if(loginCheck == 0 && senhaCheck == 0)
		{
			clear();
			printf("Acesso autorizado!\n");
			printf("Bem vindo(a), %s\n", usuario[i].nome_u);
			printf("==========================\n");

			return 1;
		}
		fscanf(arq, "%50[^\t] %50[^\t]%[^\n]", usuario[i].login_u, usuario[i].senha_u, usuario[i].nome_u);
		
		(*logado)++;
		i++;
		
		senhaCheck = strcmp(senha, usuario[i].senha_u);
		loginCheck = strcmp(login, usuario[i].login_u);
	}

	printf("Acesso Negado!\n");
	printf("\n");

	fclose(arq);

	return 0;
}

INFO_USUARIO *read(int *u_total)
{
	FILE *arq;
	arq = fopen("usuarios.txt", "r");

	INFO_USUARIO *usuario;
	int c, valor = 0, i = 0;
	*u_total = 0;
	char enter;
	
	usuario = malloc(sizeof(INFO_USUARIO) * ((*u_total) + 1));

	while((c = fgetc(arq)) != EOF)
	{
		ungetc(c, arq);

		fscanf(arq, " %50[^\t] %50[^\t]%[^\n]", usuario[(*u_total)].login_u, 
											usuario[(*u_total)].senha_u, usuario[(*u_total)].nome_u);
		fscanf(arq, "%c", &enter);

		(*u_total)++;
		usuario = realloc(usuario, sizeof(INFO_USUARIO) * ((*u_total) + 1));
	}
	fclose(arq);
	return usuario;
}

void write(INFO_USUARIO *usuario, int *u_total, int flag_deleta)
{
	FILE *arq;
	arq = fopen("usuarios.txt", "w");

	int i = 0;
	while(i < (*u_total))
	{
		if(i != flag_deleta)
		{
			fprintf(arq, "%s\t%s%s\n", usuario[i].login_u, usuario[i].senha_u, usuario[i].nome_u);
		}
		i++;
	}
	fclose(arq);
}

int deleta_usuario(INFO_USUARIO *usuario, int *u_total)
{
	char nome[STR_MAX], login[STR_MAX], senha[STR_MAX];
	int loginCheck, linhaFlag = 0, total;

	total = *u_total;

	clear();
	printf("Insira o login do usuario a ser deletado: ");
	scanf("%s", login);

	loginCheck = strcmp(login, usuario[linhaFlag].login_u);

	while(linhaFlag <= (*u_total))
	{
		if(loginCheck == 0)
		{
			clear();
			printf("Usuário %s deletado com sucesso!\n", usuario[linhaFlag].nome_u);

			return linhaFlag;
		}

		linhaFlag++;

		loginCheck = strcmp(login, usuario[linhaFlag].login_u);
	}
	(*u_total)--;
}


INFO_USUARIO *alterar_senha(INFO_USUARIO *usuario, int *logado)
{
	char senha[STR_MAX];

	clear();
	printf("Digite a nova senha do(a) usuario(a) %s: ", usuario[(*logado)].nome_u);
	scanf("%s", senha);
	printf("\n");

	criptografa_senha(senha);
	printf("%s\n", senha);

	strcpy(usuario[(*logado)].senha_u, senha);

	printf("Senha alterada!\n");
	
	return usuario;
}

INFO_USUARIO *sort(INFO_USUARIO *usuario, int *total_u)
{
    INFO_USUARIO temp;
    int i, j;

    for(i = 0; i < (*total_u); i++)
	{
        for (j = i + 1; j < (*total_u); j++)
		{
            if (strcmp(usuario[i].nome_u, usuario[j].nome_u) > 0)
			{
                temp = usuario[i];
                usuario[i] = usuario[j];
                usuario[j] = temp;
            }
        }
    }
	return usuario;
}
