typedef struct _planta
{
    char nomePlanta[50];
    char p_frutifera;
    float valor_venda;
    int numeroIdPlanta;
    int ano_plantio;
    int cod_familia;
} INFO_PLANTA;

/** 
 * @brief  função principal para alteração de dados
 * @note   
 * @param  *planta: vetor struct de controle das plantas
 * @param  *p_total: tamanho total do vetor da struct de controle
 * @retval vetor da struct de controle atualizado com valores alterados
 */
INFO_PLANTA *alterar_dados(INFO_PLANTA *planta, int *p_total, 
                            int *familia, int *f_total);

/** 
 * @brief  função de controle (leitura) do vetor de struct
 * @note   salva os valores do arquivo em um vetor
 * @param  *p_total: tamanho total do vetor da struct de controle
 * @retval inicialização/atualização do vetor de struct de controle
 */
INFO_PLANTA *read_e(int *p_total);

/** 
 * @brief  ordena a listagem em ordem crescente (código de identificação)
 * @note   
 * @param  *planta: vetor struct de controle das plantas
 * @param  *p_total: tamanho total do vetor da struct de controle
 * @retval vetor da struct de controle ordenado
 */
INFO_PLANTA *sort_plantasId(INFO_PLANTA *planta, int *p_total);

/** 
 * @brief  ordena a listagem em ordem alfabética
 * @note   
 * @param  *planta: vetor struct de controle das plantas
 * @param  *p_total: tamanho total do vetor da struct de controle
 * @retval vetor da struct de controle ordenado
 */
INFO_PLANTA *sort_plantasNome(INFO_PLANTA *planta, int *p_total);


/** 
 * @brief  vetor de controle do arquivo de famílias
 * @note   usado na função incluir_planta (checa se a família existe)
 * @param  *f_total: tamanho total do vetor de controle
 * @retval inicialização do vetor de controle de famílias
 */
int *read_familia(int *f_total);

/** 
 * @brief  checa se o arquivo está vazio
 * @note   
 * @retval valor do indicador de posição do arquivo (se == 0, arquivo vazio)
 */
int checa_vazioP();

/** 
 * @brief  checa se a família inserida usando a função incluir_planta
 *         existe no sistema
 * @note   
 * @param  *familia: vetor de struct de controle
 * @param  *inclui_p: vetor de controle que contém os dados inseridos 
 *         pelo usuário (função incluir_planta)
 * @param  *f_total: tamanho total do vetor de struct de controle de famílias
 * @param  n_planta: variável de controle (quantidade de plantas inseridas
 *         no sistema desde a execução atual do programa)
 * @retval valor booleano de acordo com a condicional (família inserida
 *         pelo usuário existe no sistema)
 */
int checa_familia(int *familia, INFO_PLANTA *inclui_p, int *f_total, int n_planta);

/** 
 * @brief  exclui uma planta em conjunto com a função write_p
 * @note   
 * @param  *planta: vetor de struct de controle
 * @param  *p_total: tamanho total do vetor de struct de controle
 * @retval linha no arquivo correspondente à planta que o usuário
 *         deseja deletar
 */
int exclui_planta(INFO_PLANTA *planta, int *p_total);

/** 
 * @brief  limpa o terminal de acordo com o sistema operacional
 *         usado pelo usuário
 * @note   
 * @retval None
 */
void clear_e();

/** 
 * @brief  lista as plantas e suas informações
 * @note   
 * @param  *planta: vetor de struct de controle
 * @param  *p_total: tamanho total do vetor de struct de controle
 * @retval None
 */
void listar_plantas(INFO_PLANTA *planta, int *p_total);

/** 
 * @brief  escreve no arquivo o que está contido no vetor de struct
 *         de controle
 * @note   
 * @param  *planta: vetor de struct de controle
 * @param  *p_total: tamanho total do vetor de struct de controle
 * @param  flagDeleta: valor retornado pela função exclui_planta
 * @retval None
 */
void write_p(INFO_PLANTA *planta, int *p_total, int flagDeleta);

/** 
 * @brief  exibe as informações de determinada planta, de acordo
 *         com o código de identificação inserido pelo usuário
 * @note   
 * @param  *planta: vetor de struct de controle
 * @param  *p_total: tamanho total do vetor de struct de controle
 * @retval None
 */
void consultar_p(INFO_PLANTA *planta, int *p_total);

/** 
 * @brief  complementares da função alterar_dados
 * @note   
 * @param  *planta: vetor de struct de controle
 * @param  flagPlanta: indica a posição da planta que está sendo alterada
 *         no vetor de struct
 * @retval None
 */
void altera_nome(INFO_PLANTA *planta, int flagPlanta);
void altera_numeroId(INFO_PLANTA *planta, int flagPlanta);
void altera_frutifera(INFO_PLANTA *planta, int flagPlanta);
void altera_anoPlantio(INFO_PLANTA *planta, int flagPlanta);
void altera_valorVenda(INFO_PLANTA *planta, int flagPlanta);
void altera_codigoFam(INFO_PLANTA *planta, int flagPlanta, int *familia, int *f_total);
/** 
 * @brief  inclui plantas no sistema escrevendo no arquivo diretamente
 * @note   
 * @param  *inclui_p: vetor de struct de controle para a adição de novas plantas
 * @param  *planta: vetor de struct de controle geral
 * @param  n_planta: variável de controle (quantidade de plantas inseridas
 *         no sistema desde a execução atual do programa)
 * @param  total_p: total de plantas já arquivadas no sistema
 * @param  *familia: vetor de struct de controle de famílias
 * @param  *f_total: tamanho total do vetor de struct de controle de famílias
 * @retval None
 */
void incluir_planta(INFO_PLANTA *inclui_p, INFO_PLANTA *planta, int n_planta,
                    int total_p, int *familia, int *f_total);
