# Labo-de-langue
Remplacer le système Sanako actuel

Rap 4 8gb + écran 7" : https://www.getgoods.com/fr-fr/products/4620521/Raspberry-Pi-Touch-Kit-DIY-Raspberry-Pi-4-B-8-GB-4-x-1.5-GHz-avec-cran-tactile-avec-botier-avec-alimentation-avec-Noobs-OS.html

Adapteur USB C POE 5V/3A 
  - 46€ : https://amzn.eu/d/e3AAIGR
  - 12€ : https://amzn.eu/d/fcFKiYs

Installer MSYS2 (si ce n'est pas encore fait)
 - Si MSYS2 n'est pas installé, téléchargez-le depuis :
	https://www.msys2.org/
 - Installez-le, puis ouvrez MSYS2 MSYS et mettez-le à jour avec :
	pacman -Syu
 - Fermez puis rouvrez MSYS2 et exécutez à nouveau :
	pacman -Su
 - Ouvrez MSYS2 MinGW 64-bit (pas MSYS2 MSYS) et exécutez :
	pacman -S mingw-w64-x86_64-zeromq
 - Ajoutez les chemins suivants dans votre fichier .pro de Qt Creator :
	INCLUDEPATH += C:/msys64/mingw64/include
	LIBS += -LC:/msys64/mingw64/lib -lzmq
