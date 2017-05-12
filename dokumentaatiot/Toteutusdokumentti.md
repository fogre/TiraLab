# Toteutusdokumentti

Ohjelma rakentuu kolmen algoritmin ympärille:
* Verkon osoitteiden luominen
* Verkon generointi
* Reitin etsiminen luodusta verkosta

joista osoitteiden luominen ja verkon generointi tapahtuvat samanaikaisesti.

## Satunnaisen verkon generointi
Verkko on suuntaamaton ja perustuu linkitettyihin listoihin, joissa jokaisella solmulla on lista saavutettavista solmuista. Satunnaisen verkon generointi pohjautuu seuraavalle funktiolle:
```
void createNetwork(ipTable ** tbls, int amount){
    ipTable * tables = *tbls;
    int addressNetmask = 168;
    int addressMask = 0;
    int addressId = 1;
    tables[0].netmask = addressNetmask;
    tables[0].identifier = addressId;
    tables[0].mask = addressMask;
    setupTable(&tables[0]);
    //create network:
    for(int i = 1; i < amount; i++){
        setupTable(&tables[i]);
        setAddress(&addressNetmask, &addressMask, &addressId, &tables[i]);
        setDestinations(&tables[i],tables, i);
    }
    ...
} 
```
Funktio siis alustaa jokaisen luotavan taulukon (setupTable), asettaa niille satunnaisen osoitteen (setAddress) sekä liittää jokaisen solmun verkkoon (setDestinations). 

#### Verkon osoitteiden luominen
Verkon osoitteet ovat muotoa netmask.submask.identifier. Ensimmäinen solmu saa aina arvokseen 168.0.1 ja loput generoidaan sen pohjalta randomAddressGenerator funktion avulla. Funktio saa parametrikseen edellisen luodun verkon osoitteen arvot, joita se kasvattaa seuraavanlaisesti:
* identifier: edellisen solmun identifier + satunnainen luku välillä 1-17
* Jos identifierin arvo on yli 999, korjataan arvo välille 1-999 ja kasvatetaan submaskin arvoa satunnaisella luvulla 1-3
* Jos uuden submaskin arvo on yli 999, korjataan sen arvo välille 1-999 ja kasvatetaan netmaskin arvoa yhdellä
```
void setAddress(int * netmask, int * mask, int * id, ipTable * table){
    randomAddressGenerator(netmask, mask, id);
    table->netmask = *netmask;
    table->mask = *mask;
    table->identifier = *id;
}

//function to generate a random IP address;
void randomAddressGenerator(int * netmask, int * mask, int * id){
    *id += random 1-17
    if(*id >= 1000){//correct id address and increase mask
        correctAddressIfItsOver1000(id);
        *mask += random 1-3
        if(*mask >= 1000){//correct mask address and increace netmask by 1
            correctAddressIfItsOver1000(mask);
            *netmask = *netmask+1;
        }
    }
}

```
#### Verkon generointi
Verkon generoinnissa aina viimeiseksi ja täten suurimman osoitteen saanut solmu linkitetään satunnaisesti 1-z, jossa z on kokonaisluku, aikaisempaan solmuun. Pelkästään x viimeisintä solmua otetaan linkityksessä huomioon, joten verkkossa ei voi olla linkkejä yli x:n pienemmän osoitteen omaavaan solmuun. 

```
void setDestinations(ipTable * table, ipTable * createdTables, int numberOfCreated){
	int numberToLink = x;
	//If there are fewer than numberToLink tables created, we need to limit the link amount 
	if(numberOfCreated <= numberToLink){
	   selectRandomDestinations(table, createdTables, numberOfCreated, numberOfCreated);
	}else{
	   //numberOfCreated more than numberToLink tables:
	   selectRandomDestinations(table, createdTables, numberOfCreated, numberToLink);
	}
}

void selectRandomDestinations(ipTable * table, ipTable * createdTables, int numberOfCreated, int numberToLink){
	int numberOfLinks = 0;
	int base = numberOfCreated-numberToLink;
	for(int j = 0; j < numberToLink; j++){
		random = rand() % 10+1;
		if(random > 7){
			setDestination;
			numberOfLinks++;
		}
		if(numberOfLinks > h){
			break;
		}
	}//in case after the for there aren't any destinations set, we set one
	if(numberOfLinks == 0){
		setDestination;
	}
}

```


Aikavaatimus verkon generoimiselle osoitteineen (ottamatta huomioon satunnaisten lukujen generointia) on O(nx) missä n on solmujen lukumäärä ja x kuinka monta edellistä solmua otetaan linkityksessä huomioon. Tilavaativuus on O(n).

## Reitin etsiminen verkosta
Reitinetsinnässä käytetään hyväksi verkon linkitetyn listan rakennetta. Solmusta saavutettavat "lapsisolmut" ovat taulukossa, jossa taulukon viimeinen alkio on aina suurimman osoitteen omaava. Toisiinsa linkitetyt solmut ovat toistensa "lapsia".

Algoritmille annetaan aloitussolmu ja osoite jota haetaan. Se hakee ahneasti lapsistaan aina isoimman osoitteen omaavaa solmua jossa ei ole käyty, ja jolla on enemmän kuin yksi lapsisolmu. Se etenee tällä tavoin, kunnes vastaan tulee osoite joka on suurempi kuin haettava osoite, tai jos sen kaikissa lapsisolmuissa on jo käyty. Tällöin, mikäli solmulla on käymättömiä lapsia joiden osoite on pienempi kuin haettava, se valitsee isoimman niistä. Muuten se valitsee tilanteen mukaisesti lapsisolmun jossa on käyty jo kerran tai kahdesti. 

Kun solmussa käydään, se merkataan joko numerolla 1 (käyty kerran), 2 (käyty kahdesti) tai 3 (umpikuja). Alussa kaikki solmut ovat merkitty arvolla 0 (käymätön). Näiden lisäksi algoritmi saa parametrinä kokonaisluvun hopCount, joka määrittää kuinka monta kertaa haku suoritetaan. 

```
traceRoute(ipTable* start, int hopCount, int netmask, int submask, int identifier){
	next = start;
	for(int h = 0; h < hopCount; h++){
	    next = getNextHop(next, netmask, submask, identifier);
	    if(next is the searched address){
	       printf(ADDRESS FOUND!);
	       return;
	    }
	}
	printf("Address not found!");
}

ipTable * getNextHop(ipTable * table, int net, int mask, int id){
	ipTable * nextDestination = NULL;
	for(int j = 0; j < table->AMOUNTofCHILDREN; j++){
	    if(The childnode has been visited already or its a dead end){
	       continue;
	     }
             //unvisited "child" found, check if it is the destination:
    	     nextDestination = unvisitedChild;
    	}
	}/*if nextDestination is still null, tables all destinations have been visited (there is a cycle).*/
	if(All children visited){
	  table->visited = 2 OR table->visited = 3;
	  SelectFromVisitedChildren()
	}else{
    	  table->visited=1;
   	  return nextDestination;
	}
}

```
Algoritmi toimii vain hauille, joissa haettava osoite on suurempi kuin lähtösolmun osoite. Sen aikavaativuus on pahimmassa tapauksessa ääretön, mikäli hopCount on ääretön ja haettava osoite ei ole olemassa:

O(hopCount + |G|) missä G on verkossa olevien linkkien lukumäärä. 

Tämän lisäksi mikäli haku halutaan suorittaa uudestaan, tulee solmujen visited kenttä nollata. Lopulliseksi aikavaatimuksesi tulee tällöin O(hopCount + |G| + n).

Main ja performanceTest luokissa hopCount on sama kuin verkon solmujen lukumäärä. Tämän on todettu löytävän olemassa olevan osoitteen aina, mikäli solmujen lukumäärä on välillä 100-2 000 000. Tästä lisää testidokumentaatiossa. Tilavaatimusta ei juuri ole. 

## Mitä voisi vielä parantaa:
* Refraktointi: Etenkin testiluokat kaipaisivat paljon refraktointia
* Reitin etsintä algoritmin parantaminen: haku isommasta pienempää.
* hopCount:in ja linkitettävien verkkojen lukumäärän määritteleminen dynaamisesti optimaallisen verkon luomiseksi.
* Main-luokan uudelleenkirjoittaminen













