# pigisland




Knabbel
- Knabbel linksonder bij standbeeld(rustplaats)
- Beweegt zich voort over de knopen van de graaf 
- Bewegen over rotsen kost 4 keer zoveel
- Wander state(knabbel begint vanuit de rustplaats in de wanderstate)
	- beweeg van knoop naar knoop in een willekeurige richting
	- is er een varken binnen 100 pixels ga naar de hunt state
- Hunt state(er is een varken binnen 100 pixels)
	- ga naar de varken die het meest dichtbij is
	- Is een varken binnen 50 pixels eet ze op
	- is er geen varken binnen 100 pixels ga naar de wander state
- Flee state(als de boot binnen 50 pixel bang komt ga naar de flee state)
	- Doe 10 stappen in een random richting.
 	- In de flee state eet geen varkens op.
- Tired state(als de haai 100 stappen heeft gedaan ga naar de tired state)
	- Ga terug naar het standbeeld. Geen varkens eten 

Varkens
- Beginnen met 100 op een willekeurige plek
- Zijn force driven entities en bewegen zich tevens voort aan de hand van flocking
- Bewegen zich vrij over de graaf(zijn dus niet gebonden aan knopen)
- Mogen op centrale zandeiland
- Mogen niet op gras eilanden of pieren
- Gaan dood als knabbel ze op eet
- Kan aan boord van de bood klimmen, wordt dan niet meer opgegeten door knabbel
- Genetisch algoritme bepaald tot hoever ze zich aangetrokken voelen door andere actoren op het scherm
	- initiele waarden staan in tabel 2 van eindopdracht.pdf
- De varkens worden geboren op het grasveld

Boot (Porcus Vencit)
- Begint op een van de afmeer plaatsen
- Beweegt zich voort over de knopen van de graaf
- Bewegen over rotsen kost 4 keer zoveel
- Beweegt in een willekeurige richting
- Begint met 100% lak
- Elke stap doet 1% lakschade
- Als de boot op 0% lak zit ga naar aanmeren
- Tijdens reizen om te aanmeren krijgt de boot geen lakschade 
- Waar de boot aanmeert wordt bepaald met kansen en beginnen met gelijke kansen
- De boot moet leren waar hij het beste kan aanmeren
- bij het aanmeren wordt de boot met een willekeurig voor die pier percentage gerepareerd

Eisen
- [ ] a*
- [ ] toestandsdiagrammen
- [ ] force driven-entities
- [ ] genetische algoritme
- [ ] leesbare code
