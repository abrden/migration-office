import random
import string


def generate_features():
    eyes_f = ["large", "small", "narrow", "sharp", "squinty"]
    eyebrows_f = ["arched", "straight", "plucked", "sparse", "trim"]
    skin_f = ["dark brown", "pale", "light", "amber", "deep brown"]
    face_f = ["square", "round", "oval", "narrow", "wolfish"]
    hair_f = ["long", "short", "bald", "messy", "shoulder-length"]
    i = random.randint(0, 4)

    return eyes_f[i] + " eyes," + eyebrows_f[i] + " eyebrows," + skin_f[i] + " skin," + face_f[i] + " face," + \
           hair_f[i] + " hair"


def generate_passport():
    return ''.join(random.choice(string.ascii_uppercase) for _ in range(3)) + \
           ''.join(random.choice(string.digits) for _ in range(6))


# Fugitives
with open("resources/gen_fugitives.txt", "w") as f:
    f.write("id\n")
    for _ in range(20):
        f.write(str(random.randint(10000000, 40000000)) + '\n')

# Persons
with open("resources/gen_people.txt", "w") as f:
    f.write("timestamp,resident,id,passport_id,features\n")
    for _ in range(20):
        timestamp = str(random.randint(0, 10))
        resident = str(random.randint(0, 1))
        res_id = str(random.randint(10000000, 40000000)) if resident == '1' else ''
        passport = generate_passport() if resident == '0' else ''
        features = generate_features()
        person = ','.join([timestamp, resident, res_id, passport, features])
        f.write(person + '\n')

# Alerts

with open("resources/gen_alerts.txt", "w") as f:
    f.write("timestamp,del_timestamp,features\n")
    for _ in range(20):
        timestamp = random.randint(0, 10)
        del_timestamp = timestamp + random.randint(1, 10)
        features = generate_features()
        alert = ','.join([str(timestamp), str(del_timestamp), str(features)])
        f.write(alert + '\n')