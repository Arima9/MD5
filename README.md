######################################################

	* TAREA 04 / EQUIPO
	* ANDRES RIVERA MARQUEZ
	* GUSTAVO ALEJANDRO SOLORIO RAMOS

######################################################

El algoritmo MD5 (Message-Digest Algorithm 5) es un algoritmo de reducción criptográfico de 128 bits, crea un resumen con una clave única llamada “hash” que comprueba la integridad del archivo, ya que cualquier cambio mínimo en el archivo original puede arrojar una alteración del 50% del hash a comprobar.

### Directivas de preprocesador ###

En este código primeramente se definen (#define) las funciones auxiliares establecidas por el algoritmo para procesar el mensaje en 4 bloques de 16 palabras. [Lineas de código 16 a 19]

Asimismo, se define una función de corrimiento a la izquierda, la cual, dependiendo de qué iteración de cada bloque de 16 palabras de se encuentre, realizará un corrimiento conocido. [Lineas de código 22]

Como el algoritmo trabaja con un buffer de 128, viéndose éste como 4 registros de 32 bits (A, B, C y D) se crea un nuevo tipo de variable de tamaño específico para evitar problemas con el desbordamiento de la variable. [Linea 25]

### Lectura del archivo ###

Se asigna un puntero donde se empezará a guardar la ruta del archivo introducida por el usuario, con una función while se construye el vector de la ruta relativa, al cual se le pasa el valor guardado en la dirección de memoria del puntero, anteponiendo en los primeros 2 caracteres “./” para construir la ruta y al final se agregan los caracteres que indican el fin de archivo ‘\0’.

### Valores iniciales & Algoritmo MD5 ###

Se inicializan los valores de la matriz de corrimientos S; el vector de constantes K, donde el valor de K [i] esta definido como la parte entera del valor absoluto del seno de ‘ i ‘ multiplicado por 2^32.

Se inicializan el buffer de los hashes H0 – H3 con 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476 definidos por el algoritmo, expresados ya como Little endian en comparación con lo establecido por el algoritmo original.

### Particion en bloques del archivo & Algoritmo MD5 ###

Como el algoritmo trabaja con bloques de 512 bits y el mensaje puede ser mayor, se genera un bloque cada 448 bits leídos del archivo (a los cuales se le agregan los 64 de relleno con el 0x80 incluid) y el algoritmo se repetira tantas veces como bloques resulten de esta operacion.

El mensaje de 512 bits se guarda en el vector M, el cual almacena 16 datos de 32 bits cada uno en su forma de Little endian.

### Procesamiento del mensaje en bloques de 16 palabras ###

Se realiza el procesamiento del mensaje en 4 rondas de 16 palabras, donde se guardan los valores iniciales en variables auxiliares (AA, BB, CC, DD) para las ecuaciones; se aplican las funciones definidas en las directivas del preprocesador acorde a la ronda en que se encuentran (F para ronda 1, G para 2, H para 3 e I para 4), se le aplica el corrimiento acorde a la ronda y número de palabra que se está evaluando y se guarda su valor acumulativo en la variable auxiliar de B.
Una vez aplicadas las operaciones descritas, A toma el valor de DD, C toma el valor de B y D toma el valor de CC.

Estos pasos, como se repiten en 4 rondas para procesar las 16 palabras, dando un total de 64 iteraciones.

### Construcción del Hash ###

Una vez terminado el proceso, se le suman los valores de A, B, C y D a los hashes iniciales H0, H1, H2 y H3. En caso de existir más bloques se repite el proceso tomando como valores iniciales el acumulado hasta el momento para H0, H1, H2, H3.

### Mostrando el Hash ###

Realizado el proceso la cantidad de bloques necesario se implementa las funciones para mostrar en big endian los hases H0, H1, H2, H3 y el resultado se imprime en la consola.

