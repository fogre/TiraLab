# Toteutusdokumentti
## Yleisrakenne

Ohjelma rakentuu kolmen algoritmin ympärille:
* Verkon osoitteiden luominen
* Verkon generointi
* Reitin etsiminen luodusta verkosta

joista osoitteiden luominen ja verkon generointi tapahtuvat samanaikaisesti.

### Satunnaisen verkon generointi
Satunnaisen verkon generointi pohjautuu seuraavalle funktiolle:
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
    tables = NULL;
    free(tables);
}
```
Funktio siis alustaa jokaisen luotavan taulukon (setupTable), asettaa niille satunnaisen osoitteen (setAddress) sekä liittää jokaisen solmun verkkoon (setDestinations). 

#### Verkon osoitteiden luominen
Verkon osoitteet ovat muotoa netmask.submask.identifier. Ensimmäinen solmu saa aina arvokseen 168.0.1 ja loput generoidaan sen pohjalta randomAddressGenerator funktion avulla. Funktio saa parametrikseen edellisen luodun verkon osoitteen arvot, joita se kasvattaa seuraavanlaisesti:
* identifier: edellisen solmun identifier + satunnainen luku 1-17
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
    int random = *id + (rand() % 17+1);
    *id = random;
    if(*id >= 1000){//correct id address and increase mask
        correctAddressIfItsOver1000(id);
        random = *mask + (rand() % 3+1);
        *mask = random;
        if(*mask >= 1000){//correct mask address and increace netmask by 1
            correctAddressIfItsOver1000(mask);
            *netmask = *netmask+1;
        }
    }
}

```
### Verkon generointi
Verkon generoinnissa aina viimeiseksi ja täten suurimman osoitteen saanut solmu linkitetään satunnaisesti 1-3 aikaisempaan solmuun. Pelkästään x viimeisintä solmua otetaan linkityksessä huomioon, joten verkkossa ei voi olla linkkejä yli x:n pienemän osoitteen omaavaan solmuun. 

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
	int random;
	int numberOfLinks = 0;
	int base = numberOfCreated-numberToLink;
	for(int j = 0; j < numberToLink; j++){
		random = rand() % 10+1;
		if(random > 7){
			setSingleDestination(table, &createdTables[base+j]);
			setSingleDestination(&createdTables[base+j], table);
			numberOfLinks++;
		}
		if(numberOfLinks > 3){
			break;
		}
	}//in case after the for there aren't any destinations set, we set one
	if(numberOfLinks == 0){
		random = rand() % numberToLink+1;
		setSingleDestination(table, &createdTables[base+random-1]);
		setSingleDestination(&createdTables[base+random-1], table);
	}
}

```

## Reitin etsiminen verkosta












