# P1 - Møder

![SP1S Logo](https://raw.githubusercontent.com/MadsBalslev/P1-project/main/docs/cooltext.gif?token=AB2OBDOLTQBD4BGRX66EOUS74GWZC)

Projekt om mødeplanlægning på 1. semester af Softwarestudiet 2020

## Beskrivelse
### Eksempel på prompt:

```sh
$ ./main.exe fil1.ics fil2.ics filn.ics
$ Indtast ønskede længde for møde i minutter> 120
$ Indtast to datoer mødet skal ligge imellem> 1/12/2020 7/12/2020
$ Magic is happening...
$ Mødet kan ligge den 4/12 klokken 12:30 - 14:30
```

Programmet kan evt. læse DESCRIPTION tagget på hvert event i `.ics` filen og evt. kigge efter: `$P2$` i beskrivelsen som fortæller at eventet har en prioritet på 2

## Features

ToDo liste:
- [x] Kan indlæse x antal .ics filer
  - [x] Kan parse indlæste filer og lagre det
    - [x] Den skal udfra en .ics event description kunne genkende prioriteringsniveauet. Som er formateret som `$px$` hvor x er en int. 
    - [x] Lagrer hver kalender for sig
- [x] Finde et hul i kalendrene indenfor et tidsrum/periode inputtet af brugeren og returnere dette til brugeren
  - [x] Hvis ikke det er muligt at finde et hul, skal programmet kunne rykke rundt på events baseret på prioritet og derved finde et tidspunkt.

### Stretch goals
- [ ] Kan generere nye .ics filer, som brugeren bare kan importere direkte ind i sin kalender

## Getting Started
Read the docs [here](https://madsbalslev.github.io/P1-project/)

### Dependencies

* Er der noget man skal have installeret først?

### Setup

* Nogle ændringer man skal lave? Evt. hvordan man indlæser en fil fra sin kalender

### Running the program

* cd into `/core` direcotry
* run makefile by writing `make` in the terminal
* Run program by writing `a [path to cal1] [path to cal2] [path to caln]`

## Authors

Programmet er skrevet og udviklet af:

- [Casper Ståhl](mailto:cstahl20@student.aau.dk)
- [Jonas Laumann Ørregaard](mailto:jarreg20@student.aau.dk)
- [Timm Ernst](mailto:ternst12@student.aau.dk)
- [Sathurrsan Jalareenleney](mailto:sjalar20@student.aau.dk)
- [Nicolai Kjøller Hansen](mailto:nkha20@student.aau.dk)
- [Mads Balslev](mailto:mbalsl20@student.aau.dk)


## Acknowledgments

Ting / referencer vi har brugt som er værd at acknowledge
