#ifndef MENSAJES_H_
#define MENSAJES_H_

const int PETITION = 1;
const int RESPONSE = 2;
const int TEXT_SIZE = 255;

typedef struct message {
	long mtype;
	int id;
	char texto[TEXT_SIZE];
} mensaje;

#endif /* MENSAJES_H_ */
