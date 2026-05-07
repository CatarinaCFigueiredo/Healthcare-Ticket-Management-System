#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "ticketsystem.h"

/*------------Main------------*/
//
//
int main()
{
    int opcao, numeroTicket = 0;
    TicketConsultaMarcada marcados[100];
    TicketConsultaUrgencia urgencias[100];
    int numero_ticket_marcado = 0, numero_ticket_urgencia = 0; // contar os tickets de consulta marcada e urgência

    printf("Bem-vindo ao Sistema de Tickets! A sequência de tickets será renovada.\n");

    do
    {
        printf("\n================== Sistema de Tickets ==================\n");
        printf("\n");
        printf("1. Gerar Ticket - Consulta Marcada\n");
        printf("________________________________________________________\n");
        printf("\n");
        printf("2. Gerar Ticket - Consulta Urgência\n");
        printf("________________________________________________________\n");
        printf("\n");
        printf("3. Exibir Tickets\n");
        printf("________________________________________________________\n");
        printf("\n");
        printf("4. Atualizar Atendimento de Tickets de Consulta Marcada\n");
        printf("________________________________________________________\n");
        printf("\n");
        printf("5. Atualizar Atendimento de Tickets de Consulta Urgência\n");
        printf("________________________________________________________\n");
        printf("\n");
        printf("6. Triagem\n");
        printf("________________________________________________________\n");
        printf("\n======================== Mapas =========================\n");
        printf("\n");
        printf("7. Gerar mapa de volume de tickets atendidos\n");
        printf("________________________________________________________\n");
        printf("\n");
        printf("8. Gerar mapa de médias de espera entre atendimento\n");
        printf("________________________________________________________\n");
        printf("\n");
        printf("9. Gerar mapa de produtividade de balcões\n");
        printf("________________________________________________________\n");
        printf("\n");
        printf("10. Gerar mapa de receitas de consultas marcadas\n");
        printf("________________________________________________________\n");
        printf("\n");
        printf("11. Sair\n");
        printf("________________________________________________________\n");
        printf("\n");
        printf("Selecione uma opção:\n");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            if (numero_ticket_marcado < 100)
            {
                gerar_Ticket_Consulta_Marcada(numero_ticket_marcado + 1, &marcados[numero_ticket_marcado]);
                numero_ticket_marcado++;
            }
            else
            {
                printf("Fila de consultas marcadas cheia!\n");
            }
            break;
        case 2:
            if (numero_ticket_urgencia < 100)
            {
                gerar_Ticket_Consulta_Urgencia(numero_ticket_urgencia + 1, &urgencias[numero_ticket_urgencia]);
                numero_ticket_urgencia++;
            }

            else
            {
                printf("Fila de urgências cheia!\n");
            }
            break;
        case 3:
            printf("---- Tickets de Consulta Marcada ----\n");
            for (int i = 0; i < numero_ticket_marcado; i++)
            {
                imprimir_Ticket_Consulta_Marcada(&marcados[i]);
            }
            printf("\n");
            printf("---- Tickets de Consulta de Urgência ----\n");
            for (int i = 0; i < numero_ticket_urgencia; i++)
            {
                imprimir_Ticket_Consulta_Urgencia(&urgencias[i]);
            }
            break;
        case 4:
            if (numero_ticket_marcado > 0)
            {
                printf("insira a sequencia de ticket: ");
                scanf("%d", &numeroTicket);

                // Verificar se o ticket é do tipo inteiro e não do tipo char

                while (getchar() != '\n' || numeroTicket <= 0)
                {
                    printf("Erro: Insira um dado válido do tipo inteiro.\n");
                    printf("insira a sequencia de ticket: ");
                    scanf("%d", &numeroTicket);
                }

                // Ciclo para verificar se o ticket existe

                while (numeroTicket > numero_ticket_marcado)
                {
                    printf("Ticket nao existe, insira sequencia válida\n");
                    scanf("%d", &numeroTicket);
                }
                if (strcmp(marcados[numeroTicket - 1].estado, "Nao atendido.") == 0)
                {
                    registrar_a_Marcada(&marcados[numeroTicket - 1]);
                }
                else
                {
                    printf("Ticket ja atendido\n");
                }
            }
            else
            {
                printf("Nenhum ticket disponível para atendimento.\n");
            }
            break;

        case 5:
            if (numero_ticket_urgencia > 0)
            {
                printf("insira a sequencia de ticket: ");
                scanf("%d", &numeroTicket);

                // Verificar se o ticket é do tipo inteiro e não do tipo char

                while (getchar() != '\n' || numeroTicket <= 0)
                {
                    printf("Erro: Insira um dado válido do tipo inteiro ou maior que zero.\n");
                    printf("insira a sequencia de ticket: ");
                    scanf("%d", &numeroTicket);
                }

                // Ciclo para verificar se o ticket existe e é um numero inteiro
                while (numeroTicket > numero_ticket_urgencia)

                {
                    printf("Ticket nao existe, insira sequencia válida\n");
                    scanf("%d", &numeroTicket);
                }
                if (strcmp(urgencias[numeroTicket - 1].estado, "Nao atendido.") == 0)
                {
                    registrar_a_Urgencia(&urgencias[numeroTicket - 1]);
                }
                else
                {
                    printf("Ticket ja atendido\n");
                }
            }
            else
            {
                printf("Nenhum ticket disponível para atendimento.\n");
            }
            break;
        case 6:
            if (numero_ticket_urgencia > 0)
            {
                printf("insira a sequencia de ticket: ");
                scanf("%d", &numeroTicket);
                while (getchar() != '\n' || numeroTicket <= 0)
                {
                    printf("Erro: Insira um dado válido do tipo inteiro ou maior que zero.\n");
                    printf("insira a sequencia de ticket: ");
                    scanf("%d", &numeroTicket);
                }
                while (numeroTicket > numero_ticket_urgencia)
                {
                    printf("Ticket nao existe, insira sequencia válida\n");
                    scanf("%d", &numeroTicket);
                }

                atendimento_triagem(&urgencias[numeroTicket - 1]);
            }
            else
            {
                printf("Nenhum ticket disponível para atendimento.\n");
            }
            break;
        case 7:
            gerar_mapa_volume_tickets_atendidos(marcados, urgencias);
            break;

        case 8:
            gerar_mapa_media_espera_atendimento(marcados, urgencias);
            break;
        case 9:
            gerar_mapa_p_balcoes(marcados, urgencias);
            break;
        case 10:
            gerar_mapa_receita_c_marcadas(marcados);
            break;
        case 11:
            printf("Sistema encerrado...\n");
            break;
        default:
            printf("Opção inválida, selecione uma das opções anteriores.\n");
        }
    } while (opcao != 11);

    return 0;
}
