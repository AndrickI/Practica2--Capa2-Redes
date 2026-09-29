#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>

#define INTERFAZ "wlp5s0"

void imprimir_mac(unsigned char *mac)
{
    for (int i = 0; i < 6; i++)
    {
        printf("%02X", mac[i]);

        if (i < 5)
            printf(":");
    }
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

    unsigned char mac_destino[6] =
        {
            0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF};

    unsigned char mac_origen[6] =
        {
            0x74, 0xDF, 0xBF,
            0xE3, 0x65, 0x8B};

    char mensaje[] = "Hola Redes2027-1";

    unsigned char trama[1500];

    int posicion = 0;

    memcpy(trama + posicion, mac_destino, 6);
    posicion += 6;

    memcpy(trama + posicion, mac_origen, 6);
    posicion += 6;

    trama[posicion++] = 0x88;
    trama[posicion++] = 0xB5;

    memcpy(trama + posicion, mensaje, strlen(mensaje));
    posicion += strlen(mensaje);

    printf("=== ENVIANDO TRAMA CAPA 2 ===\n\n");

    printf("MAC Destino: ");
    imprimir_mac(mac_destino);

    printf("\n");

    printf("MAC Origen: ");
    imprimir_mac(mac_origen);

    printf("\n");

    printf("EtherType: 0x88B5\n");

    printf("Mensaje: %s\n", mensaje);

    printf("Bytes enviados: %d\n", posicion);

    if (pcap_sendpacket(handle, trama, posicion) != 0)
    {
        printf("Error enviando trama: %s\n",
               pcap_geterr(handle));

        pcap_close(handle);
        return 1;
    }

    printf("Trama enviada correctamente\n");

    pcap_close(handle);

    return 0;
}