# Migration Office [![Build Status](https://travis-ci.org/abrden/migration-office.svg?branch=master)](https://travis-ci.org/abrden/migration-office)

### Command line parameters
---
- **-p, --people** people_file  
People file
- **-a, --alerts** alerts_file  
Alerts file
- **-f, --fugitives** fugitives_file  
Fugitive ids file
- **-s, --stampers** stampers_number  
(Optional) Default stampers quantity is 5
- **-b, --booths** booths_number  
(Optional) Default booths quantity is 10
- **-d, --debug**  
(Optional) Debug mode
- **-l, --log** log_file  
(Optional) Choose a file to log, default log file is *log* located in the same dir as the office's executable

### Execution examples
---
#### Using defaults without log
```sh
$ ./migration_office ./migration_office -p ../resources/people.txt\
                                        -a ../resources/alerts.txt\
                                        -f ../resources/fugitives.txt
```
#### Using defaults with log
```sh
$ ./migration_office ./migration_office -p ../resources/people.txt\
                                        -a ../resources/alerts.txt\
                                        -f ../resources/fugitives.txt\
                                        -d
```
#### Customizing everything
```sh
$ ./migration_office ./migration_office -p ../resources/people.txt\
                                        -a ../resources/alerts.txt\
                                        -f ../resources/fugitives.txt\
                                        -b 4 -s 1\
                                        -d -l logex3
```

### Configuration files examples
---
- **People file**
```
timestamp,resident,id,passport_id,features
5,1,38464269,,tez blanca,ojos oscuros
2,0,1234567,PORTOÑOL123,tez blanca,ojos verdes,barbudo
```
- **Alerts file**
```
timestamp,del_timestamp,features
1,8,petiso,orejudo
4,9,gatuno
0,5,sombrero cónico
```
- **Fugitives file**
```
id
13641107
38464269
```

### License
---
GNU General Public License v3.0
