# P1 - Møder

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
- [ ] Kan indlæse x antal .ics filer
  - [ ] Kan parse indlæste filer og lagre det
    - [ ] Den skal udfra en .ics event description kunne genkende prioriteringsniveauet. Som er formateret som `$px$` hvor x er en int. 
    - [ ] Lagrer hver kalender for sig
- [ ] Finde et hul i kalendrene indenfor et tidsrum/periode inputtet af brugeren og returnere dette til brugeren
- [ ] Hvis ikke det er muligt at finde et hul, skal programmet kunne rykke rundt på events baseret på prioritet og derved finde et tidspunkt.

### Stretch goals
- [ ] Kan generere nye .ics filer, som brugeren bare kan importere direkte ind i sin kalender

## Getting Started

### Dependencies

* Er der noget man skal have installeret først?

### Setup

* Nogle ændringer man skal lave? Evt. hvordan man indlæser en fil fra sin kalender

### Executing program

* Hvordan man compiler programmet
* Step by step (Tænker vi får en makefile der håndterer det)
```sh
make planner
```

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
