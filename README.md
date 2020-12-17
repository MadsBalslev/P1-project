# P1 - Møder

![SP1S Logo](https://raw.githubusercontent.com/MadsBalslev/P1-project/main/docs/cooltext.gif?token=AB2OBDOLTQBD4BGRX66EOUS74GWZC)

Projekt om mødeplanlægning på 1. semester af Softwarestudiet 2020

Programmet har fået sit navn, SP1S, da teksten man skriver for at beskrive prioritet, $P1$, minder lidt om dette, når man giver det en prioritet på 1.

## Beskrivelse
Programmet her, kan bruges til at finde fælles huller i flere kalendre, til planlægning af møder. Dette gør programmet ved at sammenligne `.ics`-filer, som en form for fil, der indeholder alt data fra en kalender.

Såfremt det ikke er muligt for programmet at finde et fælles hul i kalendrene, som er stort nok til det møde man vil finde plads til, så har programmet også mulighed for at læse en evt. prioritet ud fra `DESCRIPTION`-feltet i `.ics`-filerne. Dette giver programmet mulighed for at se bort fra begivnheder i kalendrene, som er mindre vigtige end mødet der planlægges.

### Eksempel på prompt:

```sh
$ ./a ./sample-ics-files/cal6.ics ./sample-ics-files/cal7.ics
$ Enter a priority for the event> 1
$ Enter estimated length of the event in minutes> 60
$ Enter how much buffer time should be in beginning and end of event in minutes> 10
$ Enter the earliest date the event can take place in the format: dd/mm/yyyy> 04/01/2021
$ Enter the latest date the event can take place in the format: dd/mm/yyyy> 10/01/2021
$ Enter the earliest time the event can take place in the format: HH:MM>  08:00
$ Enter the latest time the event can take place in the format: HH:MM>  16:00
$ Free slot found at: 07/01/2021 08:10
```

## Features

Feauture liste:
- [x] Kan indlæse x antal .ics filer
  - [x] Kan parse indlæste filer og lagre det nødvendige information
    - [x] Den skal udfra en .ics event description kunne genkende prioriteringsniveauet. Som er formateret som `$PX$` hvor X er en int. 
    - [x] Lagrer hver kalender for sig
- [x] Kan finde et hul i kalendrene indenfor et tidsrum/periode angivet af brugeren og returnerer det fundne hul
  - [x] Hvis ikke det er muligt at finde et hul, skal programmet kunne rykke rundt på events baseret på prioritet og derved finde et tidspunkt.

### Stretch goals
- [ ] Kan generere nye .ics filer, som brugeren bare kan importere direkte ind i sin kalender

## Getting Started
Dokumentatíon af de forskellige funktioner kan læses [her](https://madsbalslev.github.io/P1-project/).

### Opsætning

* Det er nødvendigt, for at kunne compile programmet, at man har [GCC](https://gcc.gnu.org/) installeret.
* Man skal på forhånd have en eller flere `.ics`-filer (dem man vil finde et tidsrum i) gemt på sin computer.
  * Vi har vedlagt nogle samplefiles som kan findes i mappen `./core/sample-ics-files`

### Sådan kører du programmet:

* cd ind i `/core` directory
* kør makefilen ved at skrive `make` i terminalen
* Kør programmet ved at skrive `./a [sti til cal1] [sti til cal2] [sti til caln]`

## Authors

Programmet er skrevet og udviklet af:

- [Casper Ståhl](mailto:cstahl20@student.aau.dk)
- [Jonas Laumann Ørregaard](mailto:jarreg20@student.aau.dk)
- [Timm Ernst](mailto:ternst12@student.aau.dk)
- [Sathurrsan Jalareenleney](mailto:sjalar20@student.aau.dk)
- [Nicolai Kjøller Hansen](mailto:nkha20@student.aau.dk)
- [Mads Balslev](mailto:mbalsl20@student.aau.dk)

Made with :heart: in Aalborg
