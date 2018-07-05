typedef struct _usuario
{
	char login_u[50];
	char senha_u[50];
	char nome_u[50];
} INFO_USUARIO;

/** 
 * @brief  altera a senha do usuário logado
 * @note   
 * @param  *usuario: vetor de struct de controle
 * @param  *logado: variável que indica qual é o usuário logado
 * @retval 
 */
INFO_USUARIO *alterar_senha(INFO_USUARIO *usuario, int *logado);

/** 
 * @brief  ordena os usuários em ordem alfabética
 * @note   
 * @param  *usuario: vetor de struct de controle
 * @param  *total_u: tamanho total do vetor de struct de controle
 * @retval vetor de struct ordenado
 */
INFO_USUARIO *sort(INFO_USUARIO *usuario, int *total_u);

/** 
 * @brief  inicialização do vetor de struct de controle
 * @note   
 * @param  *u_total: tamanho total do vetor de struct de controle
 * @retval vetor de struct de controle inicializado
 */
INFO_USUARIO *read(int *u_total);

/** 
 * @brief  checa se o arquivo está vazio
 * @note   
 * @retval valor do indicador de posição do arquivo (se == 0, arquivo vazio)
 */
int checa_vazio();

/** 
 * @brief  processo de validação do usuário para acesso do sistema
 * @note   
 * @param  *usuario: vetor de struct de controle
 * @param  *total_u: tamanho total do vetor de struct de controle
 * @param  *logado: variável que indica qual é o usuário logado
 * @retval 1 para acesso permitido, 0 para acesso negado
 */
int login_acesso(INFO_USUARIO *usuario, int *total_u, int *logado);

/** 
 * @brief  exclui um usuario em conjunto com a função write
 * @note   
 * @param  *usuario: vetor de struct de controle
 * @param  *u_total: tamanho total do vetor de struct de controle
 * @retval linha no arquivo correspondente ao usuário que deseja deletar
 */
int deleta_usuario(INFO_USUARIO *usuario, int *u_total);

/** 
 * @brief  limpa o terminal de acordo com o sistema operacional
 *         usado pelo usuário
 * @note   
 * @retval None
 */
void clear();

/** 
 * @brief  criptografa a senha do usuário seguindo 3 passos
 * @note   passos para a criptografia:
 * 			1 - apenas caracteres hexadecimais (A-Z; a-z; 0-9) devem ser deslocados
 * 			três casas para a direita.
 * 			2 - deve ser trocado o conteúdo das posições pares com as ímpares
 * 			(pos. 0 é par). se a última pos. for par, não deverá ser alterada.
 * 			3 - espaços em branco são substituídos por '+' e vice-versa
 * @param  *senha: senha inserida pelo usuário
 * @retval None
 */
void criptografa_senha(char *senha);

/** 
 * @brief  lista os usuários cadastrados no sistema
 * @note   
 * @param  *usuario: vetor de struct de controle
 * @param  *u_total: tamanho total do vetor de struct de controle
 * @retval None
 */
void listar_usuario(INFO_USUARIO *usuario, int *u_total);

/** 
 * @brief  escreve no arquivo os dados presentes no vetor de struct
 * 			de controle
 * @note   
 * @param  *usuario: vetor de struct de controle
 * @param  *u_total: tamanho total do vetor de struct de controle
 * @param  flag_deleta: indicador de posição (qual linha no arquivo está o usuário
 * 			a ser deletado).
 * @retval None
 */
void write(INFO_USUARIO *usuario, int *u_total, int flag_deleta);

/** 
 * @brief  inclui um novo usuário no sistema
 * @note   
 * @param  *inclui: vetor de controle para a adição de novos usuários
 * @param  *usuario: vetor de struct de controle geral
 * @param  n_usuario: variável de controle (quantidade de usuários inseridos
 * 			no sistema desde o início da execução atual do programa)
 * @param  total: usado como varíavel de controle em determinados laços
 * 			(representa o total de usuários já cadastros no sistema)
 * @retval None
 */
void incluir_usuario(INFO_USUARIO *inclui, INFO_USUARIO *usuario,
					 int n_usuario, int total);
