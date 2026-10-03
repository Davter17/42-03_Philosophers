# philosophers - Proyecto de 42 School

Implementación del problema de los filósofos comensales usando hilos y mutexes en C.

## Descripción General

Este proyecto resuelve el clásico problema de los filósofos comensales, demostrando comprensión de programación concurrente, sincronización de hilos y prevención de deadlocks. Los filósofos alternan entre comer, dormir y pensar, compartiendo tenedores con sus vecinos.

## Reglas

- Los filósofos se sientan en una mesa circular con un tenedor entre cada par
- Cada filósofo necesita ambos tenedores (izquierdo y derecho) para comer
- Después de comer, duermen, luego piensan, y repiten
- Un filósofo muere si no come dentro del tiempo especificado
- La simulación se detiene cuando un filósofo muere o todos han comido el número requerido de veces

## Características

### Simulación
- Número configurable de filósofos (1-200)
- Tiempo de muerte, tiempo de comer y tiempo de dormir configurables
- Número opcional de comidas que cada filósofo debe comer
- Salida de estado en tiempo real con marcas de tiempo

### Seguridad de Hilos
- Protección por mutex para los tenedores (previene condiciones de carrera)
- Lock de impresión para salida sincronizada
- Lock de fin para terminación limpia de la simulación
- Prevención de deadlock mediante adquisición ordenada de mutexes

### Monitoreo
- Hilo observador de muerte monitorea todos los filósofos
- Hilo observador de victoria verifica completado de comidas
- Apagado limpio al finalizar la simulación

## Estructura del Proyecto

```
philosophers/
├── src/
│   ├── main.c              # Punto de entrada y gestión de hilos
│   ├── start.c             # Inicialización de simulación y parsing de argumentos
│   ├── routine.c           # Comportamiento del filósofo (comer, dormir, pensar)
│   ├── watchers.c          # Hilos de monitoreo de muerte y victoria
│   ├── utils.c             # Funciones de utilidad (ft_atoi, get_time, ft_calloc)
│   └── philo_utils.c       # Utilidades de simulación (free, print)
├── inc/
│   └── philosophers.h      # Header con estructuras y declaraciones
├── Makefile                # Configuración de compilación
└── .gitignore
```

## Compilación

### Compilación básica
```bash
make
```
Compila el programa de filósofos.

### Compilación limpia
```bash
make re
```
Elimina todos los archivos compilados y recompila todo.

### Limpieza
```bash
make clean    # Elimina el directorio obj/
make fclean   # Elimina obj/ y el binario philo
```

## Uso

```bash
./philo numero_de_filosofos tiempo_de_muerte tiempo_de_comer tiempo_de_dormir [numero_de_comidas]
```

### Argumentos
- `numero_de_filosofos`: Número de filósofos (1-200)
- `tiempo_de_muerte`: Tiempo en milisegundos antes de que un filósofo muera sin comer
- `tiempo_de_comer`: Tiempo en milisegundos que tarda en comer
- `tiempo_de_dormir`: Tiempo en milisegundos que tarda en dormir
- `numero_de_comidas` (opcional): Número de comidas que cada filósofo debe comer

### Ejemplos

```bash
# 4 filósofos, 310ms para morir, 200ms para comer, 100ms para dormir
./philo 4 310 200 100

# 5 filósofos con 5 comidas obligatorias cada uno
./philo 5 800 200 200 5

# 1 filósofo (caso especial - morirá solo)
./philo 1 800 200 200
```

### Formato de Salida

```
timestamp_ms id_filosofo accion
```

Acciones:
- `has taken a fork` - El filósofo recogió un tenedor
- `is eating` - El filósofo está comiendo
- `is sleeping` - El filósofo está durmiendo
- `is thinking` - El filósofo está pensando
- `died` - El filósofo murió (la simulación termina)
- `Philosophers have eaten.` - Todos los filósofos completaron las comidas requeridas

## Manejo de Errores

El programa valida todas las entradas:

- **Cantidad incorrecta de argumentos**: "Error" y salida
- **Números inválidos**: Rechaza valores no numéricos, negativos o cero
- **Demasiados filósofos**: Rechaza > 200 filósofos
- **Tiempos muy pequeños**: Rechaza tiempos de comer/dormir < 60ms (previene busy waiting)
- **Asignación de memoria**: Maneja fallos de malloc correctamente

## Detalles de Implementación

### Prevención de Deadlock
Los filósofos adquieren los tenedores en orden de dirección (dirección menor primero) para prevenir condiciones de espera circular.

### Sincronización de Hilos
- `print_lock`: Asegura que solo un filósofo imprima a la vez
- `end_lock`: Protege la flag `end_simulation`
- `eating`: Protege actualizaciones de `last_meal` y `meals_eaten`
- Mutexes de tenedores: Previenen que dos filósofos usen el mismo tenedor

### Casos Especiales
- **1 filósofo**: Toma un tenedor y espera (morirá - no hay segundo tenedor disponible)
- **Número par de filósofos**: Compartición óptima de tenedores
- **Número impar de filósofos**: Puede requerir más coordinación

## Calidad del Código

- Cumple con los estándares de norminette de 42 school
- Sin fugas de memoria (verificado con valgrind)
- Operaciones thread-safe con uso correcto de mutexes
- Separación limpia de responsabilidades
- Manejo correcto de errores y liberación de recursos

## Requisitos

- Compilador GCC
- Make
- Librería pthread (POSIX threads)
- Entorno tipo Unix (Linux, macOS o WSL)

## Autor

- **Mario Pico** (@Davter17)

## Licencia

Este proyecto forma parte del plan de estudios de 42 school y sigue sus directrices académicas.
