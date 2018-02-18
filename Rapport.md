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

\fakesection{Annexes}
\includepdf[pages={1-3}]{OP599_Series_datasheet_annotee.pdf}