# Sensor-to-measure

Dépot qui contient le travail de **Nathan Pfeffenn-Deganis** et **Raphaël Casimir** pour le cours d'ING4-SE apprentis : du capteur à la mesure.

Des aides seront postées ici et/ou sur le wiki pour les autres groupes.

* Si vous avez briqué votre émetteur, j'ai extrait le firmware du nôtre. Vous pouvez faire :
	```bash
	avrdude -p m328p -P /dev/ttyUSB1 -c arduino -b 57600 -U flash:w:flash_hck.bin
	```
	Par exemple pour flasher le vôtre.