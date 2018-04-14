#ifndef MIGRATION_OFFICE_PERSONMESSAGE_H
#define MIGRATION_OFFICE_PERSONMESSAGE_H

const int PETITION = 1;
const int RESPONSE = 2;

typedef struct person_message {
	long mtype;
	bool is_resident;
	unsigned int id;
    char* passport_id;
    int features_size;
    char** features;
} person_message;

#endif /* MIGRATION_OFFICE_PERSONMESSAGE_H */
