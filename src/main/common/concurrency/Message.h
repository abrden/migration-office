#ifndef MENSAJES_H_
#define MENSAJES_H_

#define	PETICION	1
#define	RESPUESTA	2
#define TEXT_SIZE	255


typedef struct message {
	long mtype;
	int id;
	char texto[TEXT_SIZE];
} mensaje;

#endif /* MENSAJES_H_ */
