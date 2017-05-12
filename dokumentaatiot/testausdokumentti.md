# Testausdokumentti

Testit löytyvät tests kansiosta. Jokaiselle object luokalle on oma yksikkötesti tiedostonsa. Näiden lisäksi reititykselle on tehty integraatiotestejä sekä koko ohjelmaa testaava integraatiotesti performanceTest.

Yksikkötestit on tehty CMocka kirjaston avulla. Tests kansiosta löytyy scripti buildUnitTests.sh näiden rakentamiseen johon vaaditaan gcc ja CMocka kirjasto. 

performanceTest ei vaadi lähdekoodin lisäksi mitään muita kirjastoja ja sen rakentamiselle löytyy test kansiosta scipti buildPerformanceTest.sh

## Verkon generoinnin testaus

Verkon generoiti on testattu yksikkötesteillä sekä integraatiotestillä performanceTest. Reitinetsintä testaa myös verkon yhtenäistyyttä. 

## Reitinetsinnän testaus

routingTests luokassa on reitityksen yksikkötestit sekä laajempia sen toimivuuteen liittyviä testejä. Reititys on testattu tuhansia kertoja viimeiseen ja/tai satunnaiseen solmuun verkon koilla 100, 1000, 2000 sekä 2 000 000. Näissä kaikissa tapauksissa hopCountin arvo oli enintään verkon koko, joten näillä arvoilla reitinetsintä toimii ainakin ajassa O(|V|+|G|). 1000+ solmun verkoissa reitinetsintä toimi tuhansilla testikerroilla myöskin hopCountilla V/2, eli ajassa O(|V|/2 + |G|).

Yli 2 000 000 solmun verkkoja ei ole testattu. Alle 100 solmun verkoissa hopCount joka on verkon solmujen lukumäärä ei kaikissa tapauksissa riittänyt (n. 95% kyllä). Verkon solmujen lukumäärän ollessa kymmenen, hopCountin täytyy pahimmissa tapauksissa olla kaksinkertainen.

## performanceTest

Integraatiotesti luo 20 kertaa 100, 1000, 10000, 100000 ja 1 000 000 kokoisen verkon. Se laskee kullekkin keskimääräisen hopCountin solmuihin:
* solmujen lukumäärä/4 (amount/4)
* keskimmäiseen solmuun (amount/2)
* viimeiseen solmuun (amount-1)

<b>Useamman testin keskimääräiset tulokset:</b>

![HopCount](hopCount.png)

HopCount on siis noin:
* 6.8% verkon solmujen määrästä neljännekseen solmuun
* 13.3% verkon solmujen määrästä keskimmäiseen solmuun
* 26% verkon solmujen määrästä viimeiseen solmuun


## hopCount ja linkitettävien solmujen lukumäärä

Kun verkko luodaan, otetaan yksittäisen solmun linkityksessä huomioon pelkästään x kpl viimeisintä suurimman osoitteen omaavaa solmua. Perusarvona x = 6 ja tätä on käytetty kaikissa testeissä. Suurilla verkoilla x:n arvolla on luonnollisesti suurta vaikutusta reitinhakuun:

Verkon koko | x | hopCount
------------|---|---------
1 000 000 | 5 | 300 000
1 000 000 | 6 | 260 000
1 000 000 | 7 | 210 000
2 000 000 | 6 | 519 000
2 000 000 | 7 | 420 000
2 000 000 | 8 | 350 000
2 000 000 | 10 | 265 000

Pienemmillä arvoilla liian isosta x:n arvosta on kuitenkin haittaa. Kokeilun myötä x = 6 on ollut molemmilla ääripäillä toimiva vaihtoehto. Myöskään liian iso x ei olisi verkon dynamiikan kannalta järkevä.

Paras tapa jos jaksaisin / ehtisin koodata, olisi asettaa x:n arvo dynaamisesti suhteessa verkon kokoon.




