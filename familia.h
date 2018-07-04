typedef struct _familia
{
    int codigo_f;
    char nome_f[50];
} INFO_FAMILIA;

/** 
 * @brief  lê o arquivo de famílias e salva em um vetor de struct de controle
 * @note   
 * @param  *f_total: tamanho total do vetor de struct de controle
 * @retval vetor de struct de controle
 */
INFO_FAMILIA *read_f(int *f_total);

/** 
 * @brief  ordena a listagem em ordem crescente (código de identificação)
 * @note   
 * @param  *familia: vetor struct de controle das famílias
 * @param  *f_total: tamanho total do vetor da struct de controle
 * @retval vetor da struct de controle ordenado
 */
INFO_FAMILIA *sort_familiasId(INFO_FAMILIA *familia, int *f_total);

/** 
 * @brief  ordena a listagem em ordem alfabética
 * @note   
 * @param  *familia: vetor struct de controle das famílias
 * @param  *f_total: tamanho total do vetor da struct de controle
 * @retval vetor da struct de controle ordenado
 */
INFO_FAMILIA *sort_familiasNome(INFO_FAMILIA *familia, int *f_total);

/** 
 * @brief  limpa o terminal de acordo com o sistema operacional
 *         usado pelo usuário
 * @note   
 * @retval None
 */
void clear_c();

/** 
 * @brief  inclui famílias no sistema escrevendo no arquivo diretamente
 * @note   
 * @param  *inclui_f: vetor de struct de controle para a adição de novas famílias
 * @param  *familia: vetor de struct de controle geral
 * @param  n_familia: variável de controle (quantidade de famílias inseridas
 *         no sistema desde a execução atual do programa)
 * @param  total_f: total de famílias já arquivadas no sistema
 * @retval None
 */
void incluir_familia(INFO_FAMILIA *inclui_f, INFO_FAMILIA *familia, int n_familia, int total_f);

/** 
 * @brief  lista as famílias e suas informações
 * @note   
 * @param  *familia: vetor de struct de controle
 * @param  *f_total: tamanho total do vetor de struct de controle
 * @retval None
 */
void listar_familia(INFO_FAMILIA *familia, int *f_total);

/** 
 * @brief  escreve no arquivo o que está contido no vetor de struct
 *         de controle
 * @note   
 * @param  *familia: vetor de struct de controle
 * @param  *f_total: tamanho total do vetor de struct de controle
 * @param  flag: valor retornado pela função excluir_familia
 * @retval None
 */
void write_f(INFO_FAMILIA *familia, int *f_total, int flag);

/** 
 * @brief  checa se o arquivo está vazio
 * @note   
 * @retval valor do indicador de posição do arquivo (se == 0, arquivo vazio)
 */
int checa_vazioF();

/** 
 * @brief  exclui uma família em conjunto com a função write_f
 * @note   
 * @param  *familia: vetor de struct de controle
 * @param  *f_total: tamanho total do vetor de struct de controle
 * @param  *planta: vetor de struct de controle de familias
 * @param  *p_total: tamanho total do vetor de struct de familias
 * @retval linha no arquivo correspondente à família que o usuário
 *         deseja deletar
 */
int excluir_familia(INFO_FAMILIA *familia, int *f_total, int *planta, int *p_total);

/** 
 * @brief  checa se existem plantas inseridas na família determinada
 * @note   
 * @param  *planta: vetor de struct de controle de familias
 * @param  codDeleta: cód. de família que o usuário deseja deletar
 * @param  *p_total: tamanho total do vetor de struct de familias
 * @retval
 */
int checa_planta(int *planta, int codDeleta, int *p_total);

/** 
 * @brief  inicialização do vetor de controle das plantas
 * @note   
 * @param  *p_total: tamanho total do vetor de controle das plantas
 * @retval vetor de controle inicializado
 */
int *read_planta(int *p_total);