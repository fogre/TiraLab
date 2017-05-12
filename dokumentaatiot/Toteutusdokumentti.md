#Toteutusdokumentti
##Yleisrakenne

Ohjelma rakentuu kolmen algoritmin ympärille:
* Verkon osoitteiden luominen
* Verkon generointi
* Reitin etsiminen luodusta verkosta

Joista osoitteiden luominen ja verkon generointi tapahtuvat samanaikaisesti

###Satunnaisen verkon generointi
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
sdfsdfsdfsdasdas
asdasd







