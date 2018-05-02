import random
import string


def generate_features():
    eyes_f = ["large", "small", "narrow", "sharp", "squinty"]
    eyebrows_f = ["arched", "straight", "plucked", "sparse", "trim"]
    skin_f = ["dark brown", "pale", "light", "amber", "deep brown"]
    face_f = ["square", "round", "oval", "narrow", "wolfish"]
    hair_f = ["long", "short", "bald", "messy", "shoulder-length"]
    e_i = random.randint(0, 4)
    eb_i = random.randint(0, 4)
    s_i = random.randint(0, 4)
    f_i = random.randint(0, 4)
    h_i = random.randint(0, 4)

    return eyes_f[e_i] + " eyes," + eyebrows_f[eb_i] + " eyebrows," + skin_f[s_i] + " skin," + face_f[f_i] + " face," + \
           hair_f[h_i] + " hair"


def generate_passport():
    return ''.join(random.choice(string.ascii_uppercase) for _ in range(3)) + \
           ''.join(random.choice(string.digits) for _ in range(6))


# Fugitives
with open("resources/gen_fugitives_2.txt", "w") as f:
    f.write("id\n")
    for _ in range(100):
        f.write(str(random.randint(10000000, 40000000)) + '\n')

# Persons
with open("resources/gen_people_2.txt", "w") as f:
    f.write("timestamp,resident,id,passport_id,features\n")
    for _ in range(100):
        timestamp = str(random.randint(0, 10))
        resident = str(random.randint(0, 1))
        res_id = str(random.randint(10000000, 40000000)) if resident == '1' else ''
        passport = generate_passport() if resident == '0' else ''
        features = generate_features()
        person = ','.join([timestamp, resident, res_id, passport, features])
        f.write(person + '\n')

# Alerts

with open("resources/gen_alerts_2.txt", "w") as f:
    f.write("timestamp,del_timestamp,features\n")
    for _ in range(100):
        timestamp = random.randint(0, 10)
        del_timestamp = timestamp + random.randint(1, 10)
        features = generate_features()
        alert = ','.join([str(timestamp), str(del_timestamp), str(features)])
        f.write(alert + '\n')
