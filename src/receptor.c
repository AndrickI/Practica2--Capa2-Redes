#include <stdio.h>
#include <pcap.h>

#define INTERFAZ "wlp5s0"

void recibir_paquete(
    unsigned char *argumentos,
    const struct pcap_pkthdr *header,
    const unsigned char *paquete)
{

    unsigned short etherType =
        (paquete[12] << 8) | paquete[13];

    if (etherType != 0x88B5)
    {
        return;
    }

    printf("\n=== TRAMA CAPA 2 RECIBIDA ===\n\n");

    printf("MAC Destino: ");

    for (int i = 0; i < 6; i++)
    {
        printf("%02X", paquete[i]);

        if (i < 5)
            printf(":");
    }

    printf("\n");

    printf("MAC Origen: ");

    for (int i = 6; i < 12; i++)
    {
        printf("%02X", paquete[i]);

        if (i < 11)
            printf(":");
    }

    printf("\n");

    printf("EtherType: 0x%04X\n", etherType);

    printf("Mensaje: ");

    for (int i = 14; i < header->len; i++)
    {
        printf("%c", paquete[i]);
    }

    printf("\n");
}

int main()
{

    char error[PCAP_ERRBUF_SIZE];

    pcap_t *handle = pcap_open_live(
        INTERFAZ,
        65536,
        1,
        1000,
        error);

    if (handle == NULL)
    {
        printf("Error al abrir interfaz: %s\n", error);
        return 1;
    }

    printf("Esperando tramas capa 2...\n");

    pcap_loop(
        handle,
        -1,
        recibir_paquete,
        NULL);

    pcap_close(handle);

    return 0;
}