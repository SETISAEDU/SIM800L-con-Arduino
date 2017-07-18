# SIM800L-con-Arduino
En este repositorio se encuentra el sketch de Arduino, librerias, documentacion y diagramas de conexión para poder utilizar el módulo SIM800L en modo SMS.

**Antes de iniciar, considere insertar una tarjeta SIM con saldo al módulo SIM800L para poder realizar el tutorial presentado acontinuacion**
![SIM800L](https://4.bp.blogspot.com/-UNZL0C_dAls/V_xTpl03-RI/AAAAAAAABJA/hmIwbw2N-msehKjWeSK5SYAPVbCZE4GZQCLcB/s1600/modulo-gsm-sim800l.jpg)

El módulo SIM800L es un modulo dedicado a las aplicaciones inalámbricas ya que puede ejecutar funciones que un telefono celular convencional puede hacer utilizando la red GSM. Dichas funciones pueden ser, el recibir o realizar llamadas, así como tambien el manejo de mensajes de texto SMS. 
Para esta oportunidad, el proyecto ha sido enfocado en la gestion de los mensajes de texto SMS.

# Diagrama de conexión
![alt text](https://raw.githubusercontent.com/SETISAEDU/SIM800L-con-Arduino/master/SIM800L_bb.jpg)

El diagrama presentado pretende demostrar 3 tipos de aplicaciones las cuales hacen uso de la funcion de gestion de los mensajes de texto del módulo SIM800L.

**Nota: antes de programar su placa ARDUINO, revise el sketch y coloque el numero de telefono destino de su preferencia**

# Aplicacion de seguridad con SIM800L
En el diagrama de conexion se simula por medio de un pulsador normalmente cerrado conectado a la línea llamada `objeto(1)`, el evento de cerrar o abrir una puerta. Cuando se detecta un cambio en el estado de la puerta, es decir si esta se ha abierto o cerrado, se le envía un comando AT al módulo SIM800L para enviar la alerta al número de teléfono que se encuentra en el sketch de ARDUINO.
el pulsador es normalmente cerrado debido a las siguientes razones:
- el sketch interpreta un estado en bajo como una puerta cerrada, notese que uno de los extremos del pulsador esta conectado a GND.
- el sketch interpreta al estado en alto (cuando se presiona el pulsador), como una puerta abierta.

![Aviso de seguridad cuando se abre una puerta](https://www.tecnoseguro.com/images/stories/General/Magnetico_en_Puerta.jpg)

por otra parte se tiene un LED conectado al `pin 8` del arduino, para poder visualizar la respuestar del sensor simulado ante los cambios en el estado de la linea del `objeto(1)`

# Aplicacion de control remoto con SIM800L
Gracias a que la SIM800L puede gestionar de manera independiente los mensajes de texto SMS, es muy facil realizar acciones de control a distancia; Simplemente enviando un mensaje de texto, desde cualquier dispositivo movil, al numero de la tarjeta SIM contenida en el módulo SIM800L, automaticamente el módulo enviará el mensaje via comunicacion serie a la placa ARDUINO en donde será procesado.

Para el caso de este proyecto, si se envía la palabra `APAGAR` o `Apagar` via SMS al número correspondiente de la SIM contenida en el modulo SIM800L, la linea llamada `dispositivo` se mantendrá en un estado lógico bajo, manteniendo apagado el LED azul del esquemático. Por otro lado al enviar la palabra `ENCENDER` o `Encender` la linea `dispositivo` entrará en estado lógico alto, manteniendo encendido el LED azul.

# Aplicacion de monitoreo de variables físicas con SIM800L
Con la ayuda del sensor DHT11 se pueden envíar alertas y notificaciones de las variables físicas de manera remota utilizando el módulo SIM800L.
El sensor DHT11 es un sensor de temperatura y humedad, el cual se utiliza en este proyecto para monitorear el ambiente de un area determinada y manejar los datos sensados de manera que se comparen con un límite específicado en el sketch de este repositorio.
En este caso al sobrepasar el límite de 30°C, la placa de desarrollo ARDUINO enviará un mensaje de alerta a la SIM800L y dicho módulo enviará el mensaje de alerta al número de destino.



