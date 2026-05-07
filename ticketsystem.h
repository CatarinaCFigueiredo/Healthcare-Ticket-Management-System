
/*------------Estruturas------------*/
//
//
//
// Estruturas data para obter a data e hora atual

typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct
{
    Data data; // Nesta estrutura será armazenada a data e a hora da estrutura Data (estrutura dentro de estrutura)
    int hora;
    int minuto;
    int segundo;
} DataHora;

// Estrutura para Consulta Marcada
typedef struct
{
    int num_seq;                  // Numero sequencial dos ticket
    DataHora dataHoraGerado;      // Data e hora quando os tickets foram gerados
    DataHora dataHoraAtendimento; // Data e hora de atendimento
    int balcao;                   // Balcão de atendimento
    char medico[50];              // Nome do médico
    char especialidade[50];       // Especialidade
    int gabinete;                 // Gabinete
    double valor;                 // Valor da consulta
    char *estado;                 // Variável para armazenar o estado do ticket
} TicketConsultaMarcada;

// Estrutura para Consulta de Urgência
typedef struct
{
    int num_seq;                  // Numero sequencial do ticket
    DataHora dataHoraGerado;      // Data e hora quando os tickets foram gerados§
    DataHora dataHoraAtendimento; // Data e hora de atendimento
    int balcao;                   // Balcão de atendimento
    int salaEnfermagem;           // Sala de enfermagem (Ticket de urgencia)
    char *estado;                 // Atendimento e Triagem
    int prioridade;               // Definir prioridades para atendimento de urgência

} TicketConsultaUrgencia;

/*------------Funções data/hora------------*/
//
//
// Função para imprimir data e hora
void imprimirDataHora(DataHora agora)
{
    printf("Data e hora: %d/%d/%d %d:%d:%d\n", agora.data.dia, agora.data.mes, agora.data.ano, agora.hora, agora.minuto, agora.segundo);
}
// Função para chamar data e hora atual
DataHora obterDataHora()
{
    time_t segundos;
    DataHora agora;

    time(&segundos);
    struct tm *tempo = localtime(&segundos);

    agora.data.dia = tempo->tm_mday;
    agora.data.mes = tempo->tm_mon + 1;
    agora.data.ano = tempo->tm_year + 1900;
    agora.hora = tempo->tm_hour;
    agora.minuto = tempo->tm_min;
    agora.segundo = tempo->tm_sec;

    return agora;
}

// Coversor de hora, minutos e segundos para segundos
double converter_date(DataHora dataHora)
{
    struct tm time = {0};

    time.tm_hour = dataHora.hora;
    time.tm_min = dataHora.minuto;
    time.tm_sec = dataHora.segundo;
    time.tm_year = dataHora.data.ano - 1900;
    time.tm_mon = dataHora.data.mes - 1;
    time.tm_mday = dataHora.data.dia;
    return mktime(&time);
}

// Conversor de segundos para horas minutos para o tempo de espera entre atendimento

void converte_segundos_minutos_horas(double hora_segundos)
{
    int segundos = (int)hora_segundos;
    int horas = (segundos / 3600);
    int minutos = (segundos % 3600) / 60;
    segundos %= 60;
    printf("%dh %dm %ds\n", horas, minutos, segundos);
}

/*------------Funções tickets------------*/
//
//
//
// Função para verificar se uma string contém apenas letras(médico, especialidade, etc)
int isAlphaString(const char *str)
{
    while (*str)
    {
        if (!isalpha(*str) && *str != ' ') // espaços entre palavras
        {
            return 0; // Retorna falso se encontrar um caractere não alfabético
        }
        str++;
    }
    return 1; // Retorna verdadeiro se todos os caracteres forem alfabéticos
}
// Função para Gerar Ticket de Consulta Marcada
void gerar_Ticket_Consulta_Marcada(int num_seq, TicketConsultaMarcada *ticket)
{
    ticket->num_seq = num_seq;
    ticket->dataHoraGerado = obterDataHora();
    ticket->estado = "Nao atendido."; // Inicialmente, o ticket de consulta marcada está não atendido
    printf("Ticket de consulta marcada gerado!\n");
    printf("Seq: %d\n", num_seq);
    imprimirDataHora(ticket->dataHoraGerado);
}

// Função para Gerar Ticket de Consulta de Urgência

void gerar_Ticket_Consulta_Urgencia(int num_seq, TicketConsultaUrgencia *ticket)
{
    ticket->num_seq = num_seq;
    ticket->dataHoraGerado = obterDataHora();
    ticket->estado = "Nao atendido."; // Idem
    printf("Ticket de consulta de urgência gerado!\n");
    printf("Seq: %d\n", num_seq);
    imprimirDataHora(ticket->dataHoraGerado);
}

// Função para Atualizar Atendimento de tickets de consulta marcada
void registrar_a_Marcada(TicketConsultaMarcada *ticket)
{
    int balcao;
    printf("Selecione o balcão de atendimento (1 ou 2): ");
    scanf("%d", &balcao);

    // Verificar se o balcão é um dado do tipo inteiro e nao do tipo char

    while (getchar() != '\n')
    {
        printf("Erro: Insira um dado válido do tipo inteiro.\n");
        printf("Selecione o balcão de atendimento (1 ou 2): ");
        scanf("%d", &balcao);
    }
    while (balcao > 2 || balcao < 1)
    {
        if (balcao == 3)
        {
            printf("Erro: O balcão 3 não atende tickets de consulta marcada.\n");
            printf("Escolha o balcão de atendimento (1 ou 2): ");
            scanf("%d", &balcao);
        }
        else
        {
            printf("Erro: Escolha um balcão entre 1 e 2.\n");
            printf("Escolha o balcão de atendimento (1 ou 2): ");
            scanf("%d", &balcao);
        }
    }

    ticket->dataHoraAtendimento = obterDataHora();
    ticket->balcao = balcao;

    // Verificar se o nome do médico é um dado do tipo char

    printf("Médico: ");
    scanf("%s", ticket->medico);

    while (isAlphaString(ticket->medico) == 0)
    {
        printf("Erro: Insira um nome válido para o médico (apenas letras).\n");
        printf("Médico: ");
        scanf("%s", ticket->medico);
    }

    // Verificar se a especialidade é um dado do tipo char

    printf("Especialidade: ");
    scanf("%s", ticket->especialidade);

    while (isAlphaString(ticket->especialidade) == 0)
    {
        printf("Erro: Insira um nome válido para a especialidade (apenas letras).\n");
        printf("Especialidade: ");
        scanf("%s", ticket->especialidade);
    }

    // Verificar se o gabinete é um dado do tipo inteiro
    printf("Gabinete: ");
    scanf("%d", &ticket->gabinete);
    while (getchar() != '\n' || &ticket->gabinete <= 0)
    {
        printf("Erro: Insira um dado válido do tipo inteiro ou maior que zero.\n");
        printf("insira gabinete: ");
        scanf("%d", &ticket->gabinete);
    }

    // Verificar se o valor da consulta é um dado do tipo double
    printf("Valor da consulta: ");
    scanf("%lf", &ticket->valor);
    while (getchar() != '\n' || ticket->valor < 0)
    {
        printf("Erro: Insira um dado válido do tipo double ou maior que zero.\n");
        printf("insira valor: ");
        scanf("%2lf", &ticket->valor);
    }

    ticket->estado = "Atendido.";
    printf("Atendimento registrado para Ticket Nº %d no balcão %d.\n", ticket->num_seq, balcao);
}

// Função para Atualizar Atendimento de tickets de consulta urgência
void registrar_a_Urgencia(TicketConsultaUrgencia *ticket)
{
    int balcao;
    ticket->balcao = 0; // Inicialmente sem atendimento

    // Verificar se o balcão é um dado do tipo inteiro e nao do tipo char
    printf("Selecione o balcão de atendimento: ");
    scanf("%d", &balcao);

    while (getchar() != '\n' || balcao < 1 || balcao > 3)
    {
        printf("Erro: Insira um dado válido do tipo inteiro.\n");
        printf("Selecione o balcão de atendimento: ");
        scanf("%d", &balcao);
    }

    // Verificar se a sala de enfermagem é um dado do tipo inteiro e nao do tipo char
    printf("Selecione a sala de enfermagem: ");
    scanf("%d", &ticket->salaEnfermagem);

    while (getchar() != '\n' || ticket->salaEnfermagem < 0)
    {
        printf("Erro: Insira um dado válido do tipo inteiro.\n");
        printf("Selecione a sala de enfermagem: ");
        scanf("%d", &ticket->salaEnfermagem);
    }
    ticket->dataHoraAtendimento = obterDataHora();
    ticket->balcao = balcao;
    ticket->estado = "Atendido.";
    printf("Atendimento registrado para Ticket Nº %d no balcão %d.\n", ticket->num_seq, balcao);
}
// Função para Atualizar ticket na triagem
void atendimento_triagem(TicketConsultaUrgencia *ticket)
{
    if (strcmp(ticket->estado, "Nao atendido.") == 0)
    {
        printf("O ticket ainda não foi atendido!\n");
    }
    else
    {
        if (strcmp(ticket->estado, "Triagem.") == 0)
        {
            printf("O ticket já passou pela triagem!\n");
        }
        else
        {
            // Verificar se a prioridade esta entre 1 e 4

            printf("Triagem registada para Ticket Nº %d.\n", ticket->num_seq);
            ticket->estado = "Triagem.";
            printf("Prioridade: 1 - Emergente, 2 muito urgente, 3 - urgente, 4 - pouco urgente\n");
            printf("Prioridade: ");
            scanf("%d", &ticket->prioridade);
            while (ticket->prioridade < 1 || ticket->prioridade > 4)
            {
                printf("Prioridade: ");
                scanf("%d", &ticket->prioridade);
            }
        }
    }
}

// Função para imprimir tickets de consulta marcada
void imprimir_Ticket_Consulta_Marcada(TicketConsultaMarcada *ticket)
{
    printf("_________________________________________\n");
    printf("Seq: %d\n", ticket->num_seq);
    imprimirDataHora(ticket->dataHoraGerado);
    printf("Estado: %s\n", ticket->estado);
    if (strcmp(ticket->estado, "Nao atendido.") != 0)
    {
        printf("Ultima atualizacao:\n");
        imprimirDataHora(ticket->dataHoraAtendimento);

        printf("Balcao: %d\n", ticket->balcao);
        printf("Medico: %s\n", ticket->medico);
        printf("Especialidade: %s\n", ticket->especialidade);
        printf("Gabinete: %d\n", ticket->gabinete);
        printf("Valor: %.2f\n", ticket->valor);
    }
}

// Função para imprimir tickets de consulta urgencia

void imprimir_Ticket_Consulta_Urgencia(TicketConsultaUrgencia *ticket)
{
    printf("_________________________________________\n");

    printf("Seq: %d\n", ticket->num_seq);
    imprimirDataHora(ticket->dataHoraGerado);
    printf("Estado: %s\n", ticket->estado);
    if (strcmp(ticket->estado, "Nao atendido.") != 0)
    {
        printf("Ultima atualizacao:\n");
        imprimirDataHora(ticket->dataHoraAtendimento);
        printf("Balcao: %d\n", ticket->balcao);
        printf("Sala Enfermagem: %d\n", ticket->salaEnfermagem);

        if (strcmp(ticket->estado, "Triagem.") == 0)
        {
            // Atribuir as prioridades
            if (ticket->prioridade == 1)
            {
                printf("Prioridade: Vermelho\n");
            }
            else if (ticket->prioridade == 2)
            {
                printf("Prioridade: Laranja\n");
            }
            else if (ticket->prioridade == 3)
            {
                printf("Prioridade: Amarelo\n");
            }
            else
            {
                printf("Prioridade: Verde\n");
            }
        }
    }
}

/*------------Funções dos Mapas------------*/
//
//
//
// Função para gerar mapas de volume de tickets atendidos, num intervalo de datas, verificar todos os tickets e ver quais é que se inserem no intervalo de datas
void gerar_mapa_volume_tickets_atendidos(TicketConsultaMarcada marcados[], TicketConsultaUrgencia urgencias[]) // Estes vetores já estão definidos no main
{

    int inicio_dia, fim_dia, inicio_mes, fim_mes, inicio_ano, fim_ano;
    int tamanho_marcados = 100;  // Tamanho do array de tickets de consulta marcada, vai percorrer no maximo até 100 tickets
    int tamanho_urgencias = 100; // IDEM mas para tickets de urgencia
    int conta_marcados = 0;      // Contador para contar quantos tickets de consulta marcada foram atendidos num intervalo de datas
    int conta_urgencias = 0;     // mesma coisa, mas para tickets de consulta urgência

    // Pedir as datas iniciais e finais para o utilizador (dia, mes e ano)
    printf("Insira o dia, mês e ano inicial: (DD MM AAAA)");
    scanf("%d%d%d", &inicio_dia, &inicio_mes, &inicio_ano);
    printf("Insira o dia, mês e ano final: (DD MM AAAA) ");
    scanf("%d%d%d", &fim_dia, &fim_mes, &fim_ano);

    // Verificar se a data inicial é anterior à data final
    while (inicio_ano > fim_ano || (inicio_ano == fim_ano && inicio_mes > fim_mes) || (inicio_ano == fim_ano && inicio_mes == fim_mes && inicio_dia > fim_dia))
    {
        printf("Defina um intervalo válido, por favor insira novamente.\n");
        printf("Insira o dia, mês e ano inicial: (DD MM AAAA)");
        scanf("%d%d%d", &inicio_dia, &inicio_mes, &inicio_ano);
        printf("Insira o dia, mês e ano final: (DD MM AAAA) ");
        scanf("%d%d%d", &fim_dia, &fim_mes, &fim_ano);
    }

    // Ciclo for para verificar se o ticket foi atendido no intervalo de datas

    for (int i = 0; i < tamanho_marcados; i++)
    {
        if ((marcados[i].dataHoraAtendimento.data.dia >= inicio_dia && marcados[i].dataHoraAtendimento.data.dia <= fim_dia) &&
            (marcados[i].dataHoraAtendimento.data.mes >= inicio_mes && marcados[i].dataHoraAtendimento.data.mes <= fim_mes) &&
            (marcados[i].dataHoraAtendimento.data.ano >= inicio_ano && marcados[i].dataHoraAtendimento.data.ano <= fim_ano))
        {
            conta_marcados++;
        }
    }
    for (int i = 0; i < tamanho_urgencias; i++)
    {
        if ((urgencias[i].dataHoraAtendimento.data.dia >= inicio_dia && urgencias[i].dataHoraAtendimento.data.dia <= fim_dia) &&
            (urgencias[i].dataHoraAtendimento.data.mes >= inicio_mes && urgencias[i].dataHoraAtendimento.data.mes <= fim_mes) &&
            (urgencias[i].dataHoraAtendimento.data.ano >= inicio_ano && urgencias[i].dataHoraAtendimento.data.ano <= fim_ano))
        {
            conta_urgencias++;
        }
    }
    // Verificação para saber se existem tickets atendidos no intervalo de datas
    if (conta_marcados == 0 && conta_urgencias == 0)
    {
        printf("Não há tickets atendidos neste intervalo.\n");
    }
    else
    {
        if (conta_marcados > 0)
        {
            printf("Nº de tickets atendidos consulta marcada entre %d/%d/%d e %d/%d/%d: %d\n", inicio_dia, inicio_mes, inicio_ano, fim_dia, fim_mes, fim_ano, conta_marcados);
        }
        else
            printf("Não há tickets de consulta marcada neste intervalo de datas.\n");

        if (conta_urgencias > 0)
        {
            printf("Nº de tickets atendidos consulta urgência entre %d/%d/%d e %d/%d/%d: %d\n", inicio_dia, inicio_mes, inicio_ano, fim_dia, fim_mes, fim_ano, conta_urgencias);
        }
        else
            printf("Não há tickets de consulta urgência neste intervalo de datas.\n");
    }
}

// Função para gerar mapa de médias de espera entre atendimento, num intervalo de datas
void gerar_mapa_media_espera_atendimento(TicketConsultaMarcada marcados[], TicketConsultaUrgencia urgencias[])
{
    int inicio_dia, fim_dia, inicio_mes, fim_mes, inicio_ano, fim_ano;
    int tamanho_marcados = 100;
    int tamanho_urgencias = 100;
    float media_marcados = 0.0;  // Media de espera entre atendimento para tickets de consulta marcada
    float media_urgencias = 0.0; // mesma coisa, mas para tickets de consulta urgência
    int contador_marcados = 0;   // Contador para contar quantos tickets de consulta marcada foram atendidos num intervalo de datas
    int contador_urgencias = 0;  // Idem, mas para tickets de consulta urgências

    float atendimento_marcados = 0.0, gerado_marcados = 0.0, atendimento_urgencias = 0.0, gerado_urgencias = 0.0;

    // Pedir as datas iniciais e finais para o utilizador (dia, mes e ano)
    printf("Insira o dia, mês e ano inicial: ");
    scanf("%d%d%d", &inicio_dia, &inicio_mes, &inicio_ano);
    printf("Insira o dia, mês e ano final: ");
    scanf("%d%d%d", &fim_dia, &fim_mes, &fim_ano);

    // Verificar se a data inicial é anterior à data final
    while (inicio_ano > fim_ano || (inicio_ano == fim_ano && inicio_mes > fim_mes) || (inicio_ano == fim_ano && inicio_mes == fim_mes && inicio_dia > fim_dia))
    {
        printf("Defina um intervalo válido, por favor insira novamente.\n");
        printf("Insira o dia, mês e ano inicial: (DD MM AAAA)");
        scanf("%d%d%d", &inicio_dia, &inicio_mes, &inicio_ano);
        printf("Insira o dia, mês e ano final: (DD MM AAAA) ");
        scanf("%d%d%d", &fim_dia, &fim_mes, &fim_ano);
    }

    // Ciclo for para verificar se o ticket foi atendido no intervalo de datas

    for (int i = 0; i < tamanho_marcados; i++)
    {
        if ((marcados[i].dataHoraAtendimento.data.dia >= inicio_dia && marcados[i].dataHoraAtendimento.data.dia <= fim_dia) && // Contar os ticket marcados entre a data inicial e a data final, esta a verificar se a data do ticket esta entre a data inicial e a final
            (marcados[i].dataHoraAtendimento.data.mes >= inicio_mes && marcados[i].dataHoraAtendimento.data.mes <= fim_mes) &&
            (marcados[i].dataHoraAtendimento.data.ano >= inicio_ano && marcados[i].dataHoraAtendimento.data.ano <= fim_ano))
        {
            contador_marcados++;

            atendimento_marcados = converter_date(marcados[i].dataHoraAtendimento); // converter data de atendimento em time_t
            gerado_marcados = converter_date(marcados[i].dataHoraGerado);           // converter data de geracao em time_t
            media_marcados += difftime(atendimento_marcados, gerado_marcados);      // Calcular a diferença de tempo em segundos entre o momento de criação e o momento de atendimento
        }
    }
    for (int i = 0; i < tamanho_urgencias; i++)
    {
        if ((urgencias[i].dataHoraAtendimento.data.dia >= inicio_dia && urgencias[i].dataHoraAtendimento.data.dia <= fim_dia) &&
            (urgencias[i].dataHoraAtendimento.data.mes >= inicio_mes && urgencias[i].dataHoraAtendimento.data.mes <= fim_mes) &&
            (urgencias[i].dataHoraAtendimento.data.ano >= inicio_ano && urgencias[i].dataHoraAtendimento.data.ano <= fim_ano))
        {
            contador_urgencias++;
            atendimento_urgencias = converter_date(urgencias[i].dataHoraAtendimento);
            gerado_urgencias = converter_date(urgencias[i].dataHoraGerado);       // Contador para contar quantos tickets de consulta marcada foram atendidos num intervalo de datas
            media_urgencias += difftime(atendimento_urgencias, gerado_urgencias); // Calcular a diferença d                                                                              // "Contador" para contar quantos tickets de consulta urgência foram atendidos num intervalo de datas
        }
    }
    if (contador_marcados > 0)
    {
        media_marcados /= contador_marcados; // Calcular a média dividida pela quantidade de tickets atendidos
        printf("Media de espera entre atendimento para tickets de consulta marcada: ");
        converte_segundos_minutos_horas(media_marcados);
    }
    else
    {
        printf("Não há tickets de consulta marcada nas datas inseridas.\n");
    }
    if (contador_urgencias > 0)
    {
        media_urgencias /= contador_urgencias; // IDEM
        printf("Media de espera entre atendimento para tickets de consulta urgência: ");
        converte_segundos_minutos_horas(media_urgencias);
    }
    else
    {
        printf("Não há tickets de consulta urgência nas datas inseridas.\n");
    }
}
// Função para gerar mapas da produtividade dos balcões, num intervalo de datas
void gerar_mapa_p_balcoes(TicketConsultaMarcada marcados[], TicketConsultaUrgencia urgencias[])
{
    int inicio_dia, fim_dia, inicio_mes, fim_mes, inicio_ano, fim_ano;
    int inicio_segundo, fim_segundo;
    int tamanho_marcados = 100;
    int tamanho_urgencias = 100;
    int conta_marcados = 0;  // contar quantos tickets de consulta marcada foram atendidos num intervalo de datas
    int conta_urgencias = 0; // mesma coisa, mas para tickets de consulta urgência
    int balcao1 = 0;         // contar quantos tickets de consulta marcada foram atendidos no balcão 1 num intervalo de datas
    int balcao2 = 0;         // IDEM
    int balcao3 = 0;         // contar quantos tickets de consulta urgência foram atendidos no balcão 3 num intervalo de datas
    int tempo_passado = 0;   // variavel para calcular o tempo passado entre as duas datas

    printf("Insira o dia, mês e ano inicial: ");
    scanf("%d %d %d", &inicio_dia, &inicio_mes, &inicio_ano);
    printf("Insira o dia, mês e ano final: ");
    scanf("%d %d %d", &fim_dia, &fim_mes, &fim_ano);

    // Verificar se a data inicial é anterior à data final
    while (inicio_ano > fim_ano || (inicio_ano == fim_ano && inicio_mes > fim_mes) || (inicio_ano == fim_ano && inicio_mes == fim_mes && inicio_dia > fim_dia))
    {
        printf("Defina um intervalo válido, por favor insira novamente.\n");
        printf("Insira o dia, mês e ano inicial: (DD MM AAAA)");
        scanf("%d %d %d", &inicio_dia, &inicio_mes, &inicio_ano);
        printf("Insira o dia, mês e ano final: (DD MM AAAA) ");
        scanf("%d %d %d", &fim_dia, &fim_mes, &fim_ano);
    }

    tempo_passado = fim_dia - inicio_dia; // Assumindo que é no mesmo mes o intervalo de datas
    if (tempo_passado <= 0)
    {
        tempo_passado = 1;
    }

    // Ciclo for para verificar se o ticket foi atendido no intervalo de datas
    for (int i = 0; i < tamanho_marcados; i++)
    {
        if ((marcados[i].dataHoraAtendimento.data.dia >= inicio_dia && marcados[i].dataHoraAtendimento.data.dia <= fim_dia) &&
            (marcados[i].dataHoraAtendimento.data.mes >= inicio_mes && marcados[i].dataHoraAtendimento.data.mes <= fim_mes) &&
            (marcados[i].dataHoraAtendimento.data.ano >= inicio_ano && marcados[i].dataHoraAtendimento.data.ano <= fim_ano))
        {
            conta_marcados++;
            if (marcados[i].balcao == 1)
            {
                balcao1++;
            }
            if (marcados[i].balcao == 2)
            {
                balcao2++;
            }
        }
    }

    // IDEM para as urgências
    for (int i = 0; i < tamanho_urgencias; i++)
    {
        if ((urgencias[i].dataHoraAtendimento.data.dia >= inicio_dia && urgencias[i].dataHoraAtendimento.data.dia <= fim_dia) &&
            (urgencias[i].dataHoraAtendimento.data.mes >= inicio_mes && urgencias[i].dataHoraAtendimento.data.mes <= fim_mes) &&
            (urgencias[i].dataHoraAtendimento.data.ano >= inicio_ano && urgencias[i].dataHoraAtendimento.data.ano <= fim_ano))
        {
            conta_urgencias++;
            if (urgencias[i].balcao == 1)
            {
                balcao1++;
            }
            if (urgencias[i].balcao == 2)
            {
                balcao2++;
            }
            if (urgencias[i].balcao == 3)
            {
                balcao3++;
            }
        }
    }

    if (conta_marcados > 0)
    {
        printf("Produtividade do Balcao 1: %.2f tickets/dia\n", (float)balcao1 / tempo_passado);
        printf("Produtividade do Balcao 2: %.2f tickets/dia\n", (float)balcao2 / tempo_passado);
    }
    else
    {
        printf("Não há tickets de consulta marcada nas datas inseridas.\n");
    }

    if (conta_urgencias > 0)
    {
        printf("Produtividade do Balcao 3: %.2f tickets/dia\n", (float)balcao3 / tempo_passado);
    }
    else
    {
        printf("Não há tickets de consulta urgência nas datas inseridas.\n");
    }
    printf("balcao1: %d  balcao2: %d balcao3: %d", balcao1, balcao2, balcao3);
}

// Fubção para gerar mapas de receitas de consultas marcadas num intervalo de datas
void gerar_mapa_receita_c_marcadas(TicketConsultaMarcada marcados[], TicketConsultaUrgencia urgencias[])
{
    int inicio_dia, fim_dia, inicio_mes, fim_mes, inicio_ano, fim_ano;
    int tamanho_marcados = 100;
    float receita = 0.0; // soma de todos os valores de todos os tickets de c/ marcada

    // IDEM - pedir as datas
    printf("Insira o dia, mês e ano inicial: ");
    scanf("%d %d %d", &inicio_dia, &inicio_mes, &inicio_ano);
    printf("Insira o dia, mês e ano final: ");
    scanf("%d %d %d", &fim_dia, &fim_mes, &fim_ano);

    // Verificar se a data inicial é anterior à data final
    while (inicio_ano > fim_ano || (inicio_ano == fim_ano && inicio_mes > fim_mes) || (inicio_ano == fim_ano && inicio_mes == fim_mes && inicio_dia > fim_dia))
    {
        printf("Defina um intervalo válido, por favor insira novamente.\n");
        printf("Insira o dia, mês e ano inicial: (DD MM AAAA) ");
        scanf("%d %d %d", &inicio_dia, &inicio_mes, &inicio_ano);
        printf("Insira o dia, mês e ano final: (DD MM AAAA) ");
        scanf("%d %d %d", &fim_dia, &fim_mes, &fim_ano);
    }

    // Ciclo for para verificar se o ticket foi atendido no intervalo de datas
    for (int i = 0; i < tamanho_marcados; i++)
    {
        if ((marcados[i].dataHoraAtendimento.data.dia >= inicio_dia && marcados[i].dataHoraAtendimento.data.dia <= fim_dia) &&
            (marcados[i].dataHoraAtendimento.data.mes >= inicio_mes && marcados[i].dataHoraAtendimento.data.mes <= fim_mes) &&
            (marcados[i].dataHoraAtendimento.data.ano >= inicio_ano && marcados[i].dataHoraAtendimento.data.ano <= fim_ano))
        {
            receita += marcados[i].valor; // operação para somar todos os valores de todos os tickets de consulta marcada dentro do intervalo de datas
        }
    }
    printf("Valor total de consultas marcadas entre %d/%d/%d e %d/%d/%d: %.2f€\n", inicio_dia, inicio_mes, inicio_ano, fim_dia, fim_mes, fim_ano, receita);
}
