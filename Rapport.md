# Du capteur à la mesure : rapport de projet
*Par Nathan Pfeffenn-Deganis et Raphaël Casimir, ING4-SE*

## Introduction
À venir.
[GitHub repo ici](https://github.com/raphaelcasimir/sensor-to-measure)

## Analyse de la datasheet du capteur OP599
Le capteur OP599 est un phototransistor qui est sensible aux longueurs d'onde infrarouges. L'avantage du phototransistor par rapport à la photodiode est qu'il est facilement possible de récupérer une tension en sortie sans composants actifs additionnels. Nous disposons de la variante OP599A.

### Caractéristiques mécaniques

*	Package T-1¾ avec base TO-18 (2 fils).\newline
	*Le package est l'apparence physique du composant, permettant de prévoir son montage dans le circuit. Ici, les deux fils du capteur sont espacés de 2.54mm, ce qui est l'espacement de pins standard sur une breadboard ou une Arduino.*
* Angle de réception directif de 20 degrés (10 degrés de chaque côté du centre).\newline
	*Il sera nécessaire de placer la partie bombée du capteur bien en face de l'émetteur.*
*	Le schéma et la photo montrent que le package est asymétrique et que le fil le plus long, du côté du rebord saillant, sera l'émetteur (pin 1) et l'autre le collecteur (pin 2) du phototransistor.\newline
	*Information indispensable pour monter le capteur dans le bon sens.*

### Caractéristiques électroniques

* Valeurs limites de voltage :
	- Collecteur-émetteur : 30V.\newline
	*Collecteur vers la tension d'alimentation, émetteur vers la masse. Nous utiliserons ce montage.*
	- Émetteur-collecteur : 5V.\newline
	*Émetteur vers la tension d'alimentation, collecteur vers la masse.*

* Ampérage consommé par le transistor en condition d'éclairage maximal : $I_{C(on)}
	\begin{cases}
	   min = 2.35 \text{ mA} \\
	   max = 3.85 \text{ mA}
  	\end{cases}$ \newline
  	*Sera utile pour dimentionner la résistance à utiliser dans le circuit du capteur. Nous pourrons aussi utiliser le graphique 2 de la partie performance de la datasheet (voir en annexe).* \newline

* Ampérage consommé par le transistor en condition d'éclairage minimal : $I_{CEO} = 100 \text{ nA}$ \newline
  	*Ne consomme presque aucun courant dans le noir*

* Réponse spectrale typique : plus de 80% de réponse relative entre 750 et 950 nm. \newline
	*L'émetteur produit justement un pic vers 850 nm, là ou la réponse est idéale (c'est donc un capteur adapté).*

* Voltage de saturation minimal : $V_{CE(SAT)} = 0.40 \text{ V}$ \newline
	*Nous utiliserons une alimentation 3.3V ou 5V donc suffisante pour saturer le transistor*

![Montage de type 1](phototransistor-common-collector.png "Circuit collecteur commun")


![Montage de type 2](phototransistor-common-emitter.png "Circuit émetteur commun")


Le transistor intégré est un NPN et il sera passant quant le capteur sera éclairé en infrarouge.
Si l'on veut que **la tension perçue en sortie monte quand le capteur est éclairé** il faudra utiliser le montage de **type 1**, si l'on veut qu'elle **baisse**, on utilisera le **type 2**.

## Conception de la chaine de mesure

Dans un premier temps nous avons décidé d'observer la sortie du capteur avec le montage de la figure 1, Rc valant 1.5 kilo Ohms.

Nous avons observé un signal numérique TTL, comme le montre la figure 3.

![Sortie du capteur sur un oscilloscope](capture_osc_1.bmp "Capture de la sortie du capteur sur un oscilloscope")

Le signal le plus court que le microcontrôleur aura à distinguer aura une période de 0.2 ms (5 kHz, un état haut de 0.1ms environ). Le temps de descente ou de montée étant d'une 40aine de microsecondes, la transition sera bien discernable de l'état haut ou bas (dure 5 fois moins longtemps).

La chaine de mesure nécessaire est alors très simple, présentée en figure 4.

![Diagramme-bloc de la chaine de mesure](measure_chain.png "Diagramme-bloc de la chaine de mesure")

L'émetteur envoie un signal lumineux infrarouge reçu par le capteur qui le transforme en signal électrique / niveaux logiques. Ensuite ce signal est transmis à un pin numérique du microcontrôleur, ce qui permet d'interpréter l'information selon le protocole de communication utilisé par l'émetteur. Enfin, l'information traitée, les caractères résultants sont envoyés via le module série du microcontrôleur sur le moniteur série d'un ordinateur par exemple.

Voici un premier jet de l'algorithme permettant de décoder le protocole de l'émetteur, et donc récupérer le message :

```c
// Algorithme / pseudo-code
int first = 0; // première valeur de  temps
int second =0; //// première valeur de  temps
int res = 1; /// valeur de l'écart
///ascii tableau de caractère ascii caractère ASCII
char Ch[100]; /// tableau tampon pour les caractères
int i = 0; /// incrémentation des chars 
int j= 0; /// incrémentation des bits
bool which = 0; /// choix de la valeur de temps
int ends = 0; /// choix de temps
int inPin;
void setup() {
// Input mode for the pin which will receive the signal inPin

}

void loop() {
  // Si nous n'avons pas reçu le signal de départ
  if (ends == 0){
  inPin = 1;
    if () // si la lecture du pin est à 0
       if (which == 0){  
          which = !which;
          first = micros()// first prend le temps depuis 0  
          }
        else{
          which = !which;
          second = micros();// second prend le temps depuis 0  
          end = second - first; // end récupère la valeur entre les deux derniers falling edge
          }
       if () // si end est compris entre deux valeur très proche de la période attendue entre le signal de départ et le premier bit du premier
       { ends = 1;
         }
  }
  //si le signal démarre
   if (ends == 1){
  inPin = 1;
    if () // si la lecture du pin est à 0
       if (which == 0){  
          which = !which;
          first = micros()// first prend le temps depuis 0  
          }
        else{
          which = !which;
          second = micros();// second prend le temps depuis 0  
          end = second - first; // end récupère la valeur entre les deux derniers falling edge
          }
       if () // si ends compris entre deux valeur très proche de la période attendue entre le dernier bit et le bit de départ 
       { ends = 2;
         }
        else if()//temps pour un 0
       {
         ascii[j] = 0;
         j++;
       }
       else if()//temps pour un 1
       {
         ascii[j] = 0;
         j++
       }
       else if()//temps pour un espace
       {
         j==0
         //Conversion de ascii dans char[i] grâce au code ascci donné en exemple dans un fichier arduino;
        i++; 
       }}
       if (ends ==2){
       //affichage du tableau de char avec serial  
       }


}

```

\fakesection{Annexes}
\includepdf[pages={1-3}]{OP599_Series_datasheet_annotee.pdf}