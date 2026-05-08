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

    printf("\n==============================================================\n");
    printf("\n");
    printf("-----------Welcome to the Ticket Management System!-----------\n");
    printf("\n==============================================================\n");
    printf("\n");

    do
    {
    printf("\n================== Ticket Management System ==================\n");
    printf("\n");
    printf("1. Generate Ticket - Scheduled Appointment\n");
    printf("______________________________________________________________\n");
    printf("\n");

    printf("2. Generate Ticket - Emergency Appointment\n");
    printf("______________________________________________________________\n");
    printf("\n");

    printf("3. Display Tickets\n");
    printf("______________________________________________________________\n");
    printf("\n");

    printf("4. Update Scheduled Appointment Ticket Service\n");
    printf("______________________________________________________________\n");
    printf("\n");

    printf("5. Update Emergency Appointment Ticket Service\n");
    printf("______________________________________________________________\n");
    printf("\n");

    printf("6. Triage\n");
    printf("______________________________________________________________\n");

    printf("\n============================ Reports ==========================\n");
    printf("\n");

    printf("7. Generate Report - Attended Ticket Volume\n");
    printf("______________________________________________________________\n");
    printf("\n");

    printf("8. Generate Report - Average Waiting Time\n");
    printf("______________________________________________________________\n");
    printf("\n");

    printf("9. Generate Report - Counter Productivity\n");
    printf("______________________________________________________________\n");
    printf("\n");

    printf("10. Generate Report - Scheduled Appointment Revenue\n");
    printf("______________________________________________________________\n");
    printf("\n");

    printf("11. Exit\n");
    printf("______________________________________________________________\n");
    printf("\n");

    printf("Select an option:\n");
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
                printf("Scheduled appointment queue is full!\n");
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
                printf("Emergency appointment queue is full!\n");
            }
            break;
        case 3:
            printf("---- Scheduled Appointment Tickets ----\n");
            for (int i = 0; i < numero_ticket_marcado; i++)
            {
                imprimir_Ticket_Consulta_Marcada(&marcados[i]);
            }
            printf("\n");
            printf("---- Emergency Appointment Tickets ----\n");
            for (int i = 0; i < numero_ticket_urgencia; i++)
            {
                imprimir_Ticket_Consulta_Urgencia(&urgencias[i]);
            }
            break;
        case 4:
            if (numero_ticket_marcado > 0)
            {
                printf("Enter the ticket sequence number: ");
                scanf("%d", &numeroTicket);

                // Verificar se o ticket é do tipo inteiro e não do tipo char

                while (getchar() != '\n' || numeroTicket <= 0)
                {
                    printf("Error: Please insert a valid integer.\n");
                    printf("Insert ticket sequence: ");
                    scanf("%d", &numeroTicket);
                }

                // Ciclo para verificar se o ticket existe

                while (numeroTicket > numero_ticket_marcado)
                {
                    printf("Ticket does not exist. Please enter a valid sequence number (menu option 3)\n");
                    scanf("%d", &numeroTicket);
                }
                if (strcmp(marcados[numeroTicket - 1].estado, "Nao atendido.") == 0)
                {
                    registrar_a_Marcada(&marcados[numeroTicket - 1]);
                }
                else
                {
                    printf("Ticket already attended.\n");
                }
            }
            else
            {
                printf("No tickets available for attendance.\n");
            }
            break;

        case 5:
            if (numero_ticket_urgencia > 0)
            {
                printf("Enter the ticket sequence number:");
                scanf("%d", &numeroTicket);

                // Verificar se o ticket é do tipo inteiro e não do tipo char

                while (getchar() != '\n' || numeroTicket <= 0)
                {
                    printf("Error: Please insert a valid integer or a number greater than zero.\n");
                    printf("Insert ticket sequence: ");
                    scanf("%d", &numeroTicket);
                }

                // Ciclo para verificar se o ticket existe e é um numero inteiro
                while (numeroTicket > numero_ticket_urgencia)

                {
                    printf("Ticket does not exist. Please enter a valid sequence number (menu option 3)\n");
                    scanf("%d", &numeroTicket);
                }
                if (strcmp(urgencias[numeroTicket - 1].estado, "Nao atendido.") == 0)
                {
                    registrar_a_Urgencia(&urgencias[numeroTicket - 1]);
                }
                else
                {
                    printf("Ticket already attended.\n");
                }
            }
            else
            {
                printf("No tickets available for attendance.\n");
            }
            break;
        case 6:
            if (numero_ticket_urgencia > 0)
            {
                printf("Insert ticket sequence:");
                scanf("%d", &numeroTicket);
                while (getchar() != '\n' || numeroTicket <= 0)
                {
                    printf("Error: Please insert a valid integer or a number greater than zero.\n");
                    printf("Insert ticket sequence: ");
                    scanf("%d", &numeroTicket);
                }
                while (numeroTicket > numero_ticket_urgencia)
                {
                    printf("Ticket does not exist. Please enter a valid sequence number (menu option 3)\n");
                    scanf("%d", &numeroTicket);
                }

                atendimento_triagem(&urgencias[numeroTicket - 1]);
            }
            else
            {
                printf("No tickets available for attendance.\n");
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
            printf("System closed...\n");
            break;
        default:
            printf("Invalid option, please select one of the previous options.\n");
        }
    } while (opcao != 11);

    return 0;
}
