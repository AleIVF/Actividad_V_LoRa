# Facultad de Telemática - EIyTD
## Actividad V: Sistema de Monitoreo Inalámbrico con LoRa SX1278, ESP32 y MQTT

* **Profesor:** Castellanos Berjan Esli  
* **Materia/Grupo:** 7°B  
* **Fecha:** Colima, Colima a 3 de Septiembre del 2026  

### Integrantes (Equipo)
* Contreras Corona Mario Abdel
* Guzmán Larios Juan Manuel
* Martinez Martinez Edgar Jésus
* López Barajas Fernando Alonso
* Vega Flores Alejandra Ixchel
* Virgen Esparza Luis Alberto

---

## 1. Objetivo General
Desarrollar e implementar un sistema de comunicación inalámbrica de largo alcance usando módulos LoRa SX1278 con Arduino UNO y ESP32, conectando los datos mediante Wi-Fi y MQTT a una página web para monitorear lecturas en tiempo real y analizar la cobertura en nuestro campus.

---

## 2. Objetivos Específicos
* Configurar la comunicación SPI y los parámetros radioeléctricos del módulo LoRa SX1278 en un Arduino UNO para transmitir datos en formato JSON activados mediante un botón físico.
* Implementar un gateway utilizando un ESP32 y un módulo SX1278 para recibir las tramas LoRa y registrar la potencia de la señal recibida (RSSI).
* Conectar el ESP32 a una red Wi-Fi y a un broker MQTT para publicar en tiempo real los datos recopilados por el receptor LoRa.
* Desarrollar una interfaz web local que se suscriba al broker MQTT mediante WebSockets para desplegar los registros en una tabla dinámica y exportarlos a un archivo CSV.
* Evaluar el rendimiento de la señal en diferentes puntos del campus para medir variaciones de RSSI y detectar posibles pérdidas de paquetes según la distancia y los obstáculos.

---

## 3. Competencias
* **Cableado e Interfaz SPI:** Conexión del módulo SX1278 a microcontroladores Arduino UNO y ESP32.
* **Programación en Arduino IDE:** Control de botones físicos, lectura de entradas y formato de datos en JSON.
* **Conectividad IoT:** Configuración de redes Wi-Fi y envío de mensajes mediante el protocolo MQTT.
* **Desarrollo Web Básico:** Creación de una página HTML/JS para mostrar datos en tiempo real y descargarlos en CSV.

---

## 4. Tabla de Contenidos
1. [Objetivo General](#1-objetivo-general)
2. [Objetivos Específicos](#2-objetivos-específicos)
3. [Competencias](#3-competencias)
4. [Tabla de Contenidos](#4-tabla-de-contenidos)
5. [Descripción](#5-descripción)
6. [Requisitos](#6-requisitos)
7. [Instalación y Configuración](#7-instalación-y-configuración)
8. [Conexiones de Hardware](#8-conexiones-de-hardware)
9. [Parámetros Técnicos del SX1278](#9-parámetros-técnicos-del-sx1278)
10. [Uso y Ejemplos de Código](#10-uso-y-ejemplos-de-código)
11. [Resultados de Prueba](#11-resultados-de-prueba)
12. [Consideraciones Éticas y de Seguridad](#12-consideraciones-éticas-y-de-seguridad)
13. [Solución de Problemas](#13-solución-de-problemas)
14. [Contribuciones](#14-contribuciones)
15. [Referencias](#15-referencias)

---

## 5. Descripción
En el área de los entornos inteligentes y el Internet de las Cosas (IoT), resulta fundamental contar con tecnologías que permitan enviar datos de manera confiable a largas distancias sin depender de un consumo elevado de energía. Esta práctica nos permite comprender en la vida real cómo funciona el protocolo LoRa mediante el módulo SX1278, conectando un sensor transmisor remoto a una red Wi-Fi e Internet a través de un gateway con ESP32. Comprender esta arquitectura es clave para nuestro aprendizaje en la carrera, ya que simula escenarios reales como el monitoreo ambiental, la agricultura de precisión o las ciudades inteligentes, donde los dispositivos deben enviar información a un servidor central desde zonas donde no hay cobertura de red tradicional.

---

## 6. Requisitos

### Hardware Necesario
* Arduino UNO
* ESP32
* Módulo SX1278 (x2)
* Protoboard y cables jumpers
* Botón físico

### Software y Bibliotecas Requeridas
* Arduino IDE
* Broker MQTT (`broker.hivemq.com`)
* Librerías para Arduino IDE:
  * `LoRa`
  * `ArduinoJson`
  * `PubSubClient`

### Conocimientos Previos Imprescindibles
* Uso de entradas/salidas digitales y resistencia pull-up interna en Arduino.
* Manejo del bus de comunicación SPI (SCK, MOSI, MISO, CS).
* Formato de datos JSON básico.
* Conceptos de MQTT (publicar/suscribir) y WebSockets.
* HTML y JavaScript básico para mostrar datos en la web.

---

## 7. Instalación y Configuración

### Instalación de Librerías en Arduino IDE
1. Abre Arduino IDE y dirígete al menú `Programa` -> `Incluir Librería` -> `Administrar Bibliotecas...`.
2. En el buscador, localiza e instala las siguientes dependencias:
   * **LoRa**
   * **ArduinoJson**
   * **PubSubClient**

### Configuración del Entorno de Desarrollo para ESP32
1. Asegúrate de tener instalado el gestor de tarjetas ESP32 en Arduino IDE (`Archivo` -> `Preferencias` -> `Gestor de URLs Adicionales de Tarjetas`).
2. Selecciona tu modelo de placa (ej. *ESP32 Dev Module*) desde `Herramientas` -> `Placa` -> `esp32`.

### Configuración de Parámetros en el Código Transmisor (Arduino UNO)
1. Abre el boceto correspondiente al transmisor.
2. Define las iniciales de tu equipo dentro de la variable del programa.
3. Verifica la frecuencia del módulo en `LORA_BAND` (usa `433E6` para 433 MHz o `915E6` para 915 MHz).
4. Confirma la asignación de pines SPI y del botón.

### Configuración de Parámetros en el Código Gateway (ESP32)
1. Abre el boceto correspondiente al receptor.
2. Configura los datos de tu red de Internet inalámbrica (SSID y contraseña).
3. Establece la dirección del broker público y el puerto MQTT: `broker.hivemq.com` en el puerto `1883`.
4. Modifica el nombre del tema (*topic*) para que sea único para tu equipo.
5. Valida la asignación de pines SPI para el ESP32.

### Configuración de la Interfaz Web Local
1. Abre el archivo `.html` en un editor de código o texto.
2. Verifica que la variable del broker WebSocket apunte a `broker.hivemq.com` en el puerto correspondiente.
3. Asegúrate de que la variable `topic` tenga exactamente la misma cadena asignada en el código del ESP32.
4. Guarda el archivo y ábrelo directamente en tu navegador web de preferencia.

---

## 8. Conexiones de Hardware

### Transmisor (Arduino UNO -> LoRa SX1278)

| Señal de módulo | Pin de placa | Función |
| :--- | :--- | :--- |
| **VCC** | 3.3V | Alimentación del módulo |
| **GND** | GND | Tierra común |
| **NSS (CS)** | Pin 10 | Selección del chip (`csPin = 10`) |
| **MOSI** | Pin 11 | Salida de datos del Arduino al módulo |
| **MISO** | Pin 12 | Entrada de datos del módulo al Arduino |
| **SCK** | Pin 13 | Reloj de la comunicación SPI |
| **RST** | Pin 9 | Reinicio del módulo |
| **DIO0** | Pin 2 | Interrupción de datos |
| **Terminal 1 Botón** | Pin 4 | Lectura de entrada digital |
| **Terminal 2 Botón** | GND | Cierre del circuito |

### Gateway (ESP32 -> LoRa SX1278)

| Señal de módulo | Pin de placa | Función |
| :--- | :--- | :--- |
| **VCC** | 3.3 V | Alimentación de módulo |
| **GND** | GND | Tierra común |
| **NSS (CS)** | GPIO 5 | Selección de chip |
| **MOSI** | GPIO 23 | Salida de datos SPI |
| **MISO** | GPIO 19 | Entrada de datos SPI |
| **SCK** | GPIO 18 | Reloj de comunicación SPI |
| **RST** | GPIO 14 | Reinicio de módulo |
| **DIO0** | GPIO 26 | Interrupción de datos |

---

## 9. Parámetros Técnicos del SX1278

| Parámetro | Valor / Rango |
| :--- | :--- |
| **Frecuencia de operación** | 420 MHz a 450 MHz (frecuencia central común en 433 MHz) |
| **Voltaje de alimentación** | 1.8 V a 3.7 V (típicamente 3.3 V) |
| **Potencia de transmisión máxima** | +20 dBm (100 mW) |
| **Sensibilidad de recepción** | Hasta -148 dBm |
| **Alcance de comunicación** | Hasta 10–15 km en línea de vista (dependiendo de antena y entorno) |
| **Modulación** | LoRa (espectro ensanchado), FSK, GFSK, MSK, GMSK y OOK |
| **Interfaz de comunicación** | SPI |
| **Corriente en modo bajo consumo** | Menos de 1 µA en modo de suspensión (*sleep*) |

---

## 10. Uso y Ejemplos de Código

### Dónde va cada código
* **Para el Arduino UNO (Transmisor):** El código se carga a la placa seleccionando Arduino UNO y su puerto COM desde la IDE.
* **Para el ESP32 (Gateway):** El código se sube en una ventana aparte seleccionando la tarjeta ESP32 y su puerto COM.
* **Para la página web:** Se guarda el código en un archivo con extensión `.html` y se abre directamente en cualquier navegador.

### Qué se debe comentar en cada parte
* **Librerías y datos iniciales:** Explicar para qué sirve cada librería cargada y escribir qué hacen las variables principales (pines, frecuencia, red Wi-Fi y canal MQTT).
* **Inicio (`setup`):** Explicar cómo se preparan los pines, se inicia el monitor serie, se enciende el módulo LoRa y se conecta el ESP32 a Internet.
* **Programa principal (`loop`):** Comentar cómo detecta el botón el Arduino para no enviar datos repetidos por error, y cómo el ESP32 se queda escuchando los mensajes que van llegando.
* **Creación de mensajes (JSON):** Explicar cómo se arman los datos en el paquete de envío y cómo el ESP32 le agrega el dato de la fuerza de señal (RSSI).
* **Funciones de la web:** Detallar cómo la página se conecta a Internet para recibir los datos en tiempo real, los acomoda en la tabla y los descarga en formato CSV.

---

## 11. Resultados de Prueba

* **Monitor Serie del Transmisor (Arduino UNO):**
* **Monitor Serie del Gateway (ESP32):**
<img width="1600" height="900" alt="Imagen1" src="https://github.com/user-attachments/assets/734d7bfc-ad59-4440-8453-ba54aab322f8" />
* **Página Web en tiempo real:**
<img width="1600" height="900" alt="Imagen2" src="https://github.com/user-attachments/assets/a9c36548-b590-4b9c-b0a1-501456d7e9a3" />

---

## 12. Consideraciones Éticas y de Seguridad
* **Uso de bandas libres:** El chip opera en bandas de frecuencia libre (como 433MHz en el SX1278 o 868/915 MHz en variantes hermanas) que no requieren licencia de operador, pero sí obligan a respetar los límites de potencia y los tiempos de ocupación del canal (*Duty Cycle*) dictados por las normativas locales de telecomunicaciones.
* **Interferencia perjudicial:** Por ética técnica y legal, no debes modificar la ganancia ni saturar las frecuencias libres con transmisiones continuas que bloqueen los dispositivos de uso comunitario o de emergencia cercanos.
* **Privacidad de los datos:** Como la capa física LoRa transmite por aire sin cifrado nativo obligatorio a nivel de chip, es tu responsabilidad ética implementar protocolos de cifrado de datos (como AES-128) si transmites información sensible, privada o personal.

---

## 13. Solución de Problemas

| Problema | Causa típica | Estrategia de diagnóstico y solución |
| :--- | :--- | :--- |
| **El SX1278 no inicializa (`LoRa.begin()` devuelve `false`)** | Pines SPI o DIO0 mal cableados, o frecuencia configurada fuera del rango del módulo. | Verifica con multímetro continuidad en NSS, SCK, MOSI, MISO, RST y DIO0. Confirma que la frecuencia en el código (`433E6` / `915E6`) coincide con la banda física del módulo. |
| **No se reciben paquetes en el gateway aunque el transmisor "envía"** | SF, BW, CR o frecuencia distintos entre transmisor y receptor. | Imprime por Serial los parámetros configurados en ambos nodos y compáralos línea por línea; deben ser idénticos en los dos extremos. |
| **RSSI muy bajo (< -110 dBm) o con mucha variación** | Obstáculos, antena mal conectada/floja, o distancia excesiva para el SF usado. | Revisa la conexión de la antena (rosca/soldadura), prueba en línea de vista directa, y si persiste, aumenta el SF para ganar sensibilidad a costa de velocidad. |
| **Paquetes recibidos con datos corruptos o JSON incompleto** | Ruido en el enlace, colisiones, o buffer leído antes de completarse la recepción. | Valida el JSON con `deserializeJson()` antes de usarlo; si falla, descarta el paquete y regístralo como error en vez de publicarlo. |
| **El ESP32 no logra conectarse al broker MQTT** | Credenciales Wi-Fi incorrectas, broker caído, o puerto equivocado. | Revisa el Monitor Serie para el código de error (`client.state()`); prueba primero la conexión desde una app externa (MQTT Explorer) con las mismas credenciales. |
| **La página web no recibe datos por WebSocket** | El broker no tiene habilitado el puerto WebSocket, o la URL usada en el JS es incorrecta. | Confirma en la documentación del broker el puerto WS (normalmente distinto al 1883, ej. 8000/8083); revisa la consola del navegador (F12) para ver el error exacto de conexión. |
| **El botón genera varios incrementos con una sola pulsación** | Rebote (*bounce*) mecánico del botón sin control por software. | Agrega *debounce*: ignora nuevas lecturas durante ~200 ms tras detectar el flanco de bajada, o compara `millis()` desde la última pulsación válida. |
| **El Arduino UNO se reinicia o se cuelga al transmitir** | Consumo pico del SX1278 en TX excede lo que entrega el regulador de la placa. | Alimenta el módulo con una fuente externa de 3.3V regulada y añade un capacitor de desacoplo (100–470 µF) cerca del módulo. |

---

## 14. Contribuciones
Para proponer mejoras o correcciones a este proyecto, el equipo debe seguir este flujo de trabajo:

1. **Fork / respaldo del repositorio:** Cada integrante realiza un fork (o clona una copia) del repositorio principal a su propia cuenta o equipo, para trabajar sin afectar la rama `main` directamente.
2. **Creación de una rama descriptiva:** A partir de `main`, crear una rama nueva siguiendo la convención `tipo/breve-descripcion`, por ejemplo:
   * `fix/correccion-json` — corrección de errores.
   * `feature/soporte-varios-nodos` — nuevas funcionalidades.
   * `docs/actualizacion-readme` — cambios de documentación.
3. **Desarrollo del cambio:** Realizar las modificaciones manteniendo el estilo de comentarios y la separación de responsabilidades ya establecida en el proyecto (por ejemplo, no mezclar lógica de configuración con lógica de negocio).
4. **Verificación antes de subir cambios:** Compilar ambos sketches (transmisor y gateway) sin errores, y probar que la página web siga recibiendo datos correctamente.
5. **Apertura de Pull Request:** Subir la rama al repositorio remoto y abrir un Pull Request hacia `main`, describiendo claramente:
   * Qué problema resuelve o qué mejora introduce.
   * Cómo se probó el cambio.
6. **Revisión por pares:** Esperar la revisión y aprobación de al menos un integrante del equipo antes de fusionar (*merge*) los cambios a `main`.
7. **Actualización de documentación:** Si el cambio afecta el comportamiento del sistema (pines, parámetros LoRa, formato del JSON), actualizar también el README correspondiente en el mismo Pull Request.

---

## 15. Referencias
* Arduino. (s. f.). *Arduino Uno Rev3*. Arduino Official Store. Recuperado el 2 de septiembre de 2026, de https://store.arduino.cc/products/arduino-uno-rev3
* Espressif Systems. (2021). *ESP32 Series Datasheet*. Espressif Systems.
* Klaus, M. (2020, 24 de junio). *What is LoRa? A beginner’s guide (Part 1)*. Paessler Blog. https://blog.paessler.com/what-is-lora-a-beginners-guide-part-1
* LoRa Alliance. (2017). *LoRaWAN® 1.0.3 Specification*. LoRa Alliance.
* Semtech Corporation. (2015). *SX1278 LoRa Transceiver Datasheet* (Rev. F). Semtech Corporation.
* Semtech Corporation. (2016). *SX1278/79 LoRa Modem Design Guide*. Semtech Corporation.
