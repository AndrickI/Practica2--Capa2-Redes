
---
Alumno : 
Marcial Ahedo Andrick Iorel - 321304074
---
# Práctica 2 — Capa 2
Implementación de comunicación.
 **Tramas Ethernet de Capa 2** utilizando la biblioteca **libpcap** .

## Descripción

Esta práctica implementa un emisor y un receptor que pueden construir, enviar y capturar tramas Ethernet directamente utilizando `libpcap`.

La trama utilizada contiene:

- Dirección MAC destino.
- Dirección MAC origen.
- Campo EtherType personalizado (`0x88B5`).
- Payload con el mensaje:

```
Hola Redes2027-1
```

---

# Requisitos


Instalar la biblioteca `libpcap`:

```bash
sudo apt update
sudo apt install libpcap-dev
```

---

# Estructura del proyecto

```
Practica2/
│
├── README.md
├── Makefile
│
└── src/
    ├── emisor.c
    └── receptor.c
```

---

# Compilación

Desde la carpeta principal del proyecto:

```bash
make
```

Esto genera los ejecutables:

```
emisor
receptor
```

Para limpiar los archivos generados:

```bash
make clean
```

---

# Configuración de red

Antes de ejecutar el programa es necesario conocer el nombre de la interfaz de red disponible.

Consultar interfaces:

```bash
ip link
```


La interfaz utilizada actualmente es:

```
wlp5s0
```

Se debera cambiar para poder probar el programa si es diferetne, modificar la constante:

```c
#define INTERFAZ "wlp5s0"
```

en los archivos:

```
src/emisor.c
src/receptor.c
```

---

# Dirección MAC

El emisor utiliza la dirección MAC de la tarjeta de red configurada actualmente:

```
74:DF:BF:E3:65:8B
```

Igualmente se debera cambiar. Esta dirección debe actualizarse con la MAC con el comando:

```bash
ip link
```

---

# Ejecución

Debido a que `libpcap` requiere permisos de captura de red, los programas deben ejecutarse con privilegios de administrador.

## Terminal 1 — Receptor

Ejecutar:

```bash
sudo ./receptor
```

El programa quedará esperando tramas:

```
Esperando tramas capa 2...
```

---

## Terminal 2 — Emisor

Ejecutar:

```bash
sudo ./emisor
```

El emisor construirá y enviará una trama Ethernet.

Ejemplo de salida:

```
=== ENVIANDO TRAMA CAPA 2 ===

MAC Destino: FF:FF:FF:FF:FF:FF
MAC Origen: 74:DF:BF:E3:65:8B
EtherType: 0x88B5
Mensaje: Hola Redes2027-1
Bytes enviados: 30
Trama enviada correctamente
```

---

# Recepción de la trama

Cuando el receptor detecta una trama con EtherType `0x88B5`, muestra la información recibida.

Ejemplo:

```
=== TRAMA CAPA 2 RECIBIDA ===

MAC Destino: FF:FF:FF:FF:FF:FF
MAC Origen: 74:DF:BF:E3:65:8B
EtherType: 0x88B5
Mensaje: Hola Redes2027-1
```

# Notas

- La práctica utiliza una trama Ethernet personalizada de Capa 2.
- El payload se transporta directamente dentro de la trama Ethernet.