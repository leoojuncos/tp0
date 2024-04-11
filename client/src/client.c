#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;
	/* ---------------- LOGGING ---------------- */

	log_create("tp0_log.log", "soy un log", 1, LOG_LEVEL_INFO);

	logger = iniciar_logger();

	log_info(logger, "Hola! Soy un log uWu");
	
	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */	

	config = iniciar_config();

 	valor = config_get_string_value(config, "CLAVE");

	ip = config_get_string_value(config, "IP");

	puerto = config_get_string_value(config, "PUERTO");
	
	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	// Loggeamos el valor de config
	
	log_info(logger, valor);
	log_info(logger, ip); // no importa
	log_info(logger, puerto); // no importa

	/* ---------------- LEER DE CONSOLA ---------------- */
	
	leer_consola(logger);
	
	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	
	enviar_mensaje(valor, conexion);

	// Armamos y enviamos el paquete
	
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config = config_create("cliente.config");
	if (nuevo_config == NULL) {
		perror("error config");
		exit(EXIT_FAILURE);
	}
	
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");
	log_info(logger, leido);
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	while(strcmp(leido, "") != 0) {
		free(leido);
		leido = readline("> ");
		log_info(logger, leido);
	}
	// ¡No te olvides de liberar las lineas antes de regresar!
	free(leido);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* mensaje;
	t_paquete* paquete;
	
	// Leemos y esta vez agregamos las lineas al paquete
	
	mensaje = readline("> ");

	if (strcmp(mensaje,"")==0){
    	printf("No se ingresaron datos al paquete");
		free(mensaje);
        return;
    }

	paquete = crear_paquete();
	
	while(strcmp(mensaje, "") != 0) {
		int tamanio_mensaje = strlen(mensaje) + 1;
		agregar_a_paquete(paquete,mensaje,tamanio_mensaje);
		
		free(mensaje);
		mensaje = readline("> ");
	}

	free(mensaje);
// ¡No te olvides de liberar las líneas y el paquete antes de regresar! Okis

	enviar_paquete(paquete, conexion);
	
	eliminar_paquete(paquete);

}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
		log_destroy(logger);
		config_destroy(config);
		liberar_conexion(conexion);
	
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
