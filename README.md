# Sensor-to-measure

Dépot qui contient le travail de **Nathan Pfeffenn-Deganis** et **Raphaël Casimir** pour le cours d'ING4-SE apprentis : du capteur à la mesure.

## Code

Comme vous le savez, le code fonctionne, vous pouvez tester votre montage avec et vous en inspirer.

## Émetteur

* Si vous avez briqué votre émetteur, j'ai extrait le firmware du nôtre. Vous pouvez faire :
	```bash
	avrdude -p m328p -P /dev/ttyUSB1 -c arduino -b 57600 -U flash:w:flash_hck.bin
	```
	Par exemple pour re-flasher le vôtre.
	
## Rapport

Le rapport est maintenant terminé. Il y a une version PDF et une en-ligne (fichier .md).
