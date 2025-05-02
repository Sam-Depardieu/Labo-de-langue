# Projet : Labo de Langue

## Contexte
Le Lycée Durzy souhaite développer une solution alternative au système Sanako pour leur laboratoire de langues. Le système actuel, vieillissant et coûteux, doit être remplacé par une solution innovante et économique basée sur des Raspberry Pi.

---

## Objectifs du projet
- Remplacer les stations de travail actuelles par des Raspberry Pi avec écrans tactiles.
- Proposer une interface simple et interactive pour les exercices multimédia (audio, vidéo, texte).
- Permettre l'enregistrement et le stockage des réponses des étudiants.
- Offrir un système de gestion centralisé pour les enseignants.
- Réduire les coûts de mise en œuvre et de maintenance.

---

## Fonctionnalités principales
### Interface Étudiant
- Connexion aux sessions d'exercices.
- Lecture et enregistrement audio/vidéo.
- Navigation intuitive sur écran tactile.
- Envoi des réponses à l'enseignant.

### Interface Enseignant
- Gestion des sessions (création, modification, suivi).
- Évaluation des réponses des étudiants.
- Communication et feedback en temps réel.

---

## Environnement technique
- **Matériel** :
  - Raspberry Pi 4 (4 Go ou 8 Go de RAM).
  - Écran tactile (7 à 10 pouces).
  - Switch réseau 48 ports PoE (ex. : NETGEAR GS748TPS).
  - [Adapteur USB C RJ45 POE 5V/3A](https://amzn.eu/d/fcFKiYs).
  - Adapteur USB Jac.

- **Logiciels** :
  - Développement d'interfaces avec Qt Framework (C++) ou Tkinter/Kivy (Python).
  - Gestion audio/vidéo avec PyAudio ou PortAudio.
  - Communication réseau via protocoles TCP/UDP.
  - OS : Raspberry Pi OS.

- **Base de données** :
  - Serveur MySQL pour stocker les réponses et les évaluations.

---

## Diagrammes UML et Gantt
Les diagrammes UML et le planning Gantt sont disponibles dans la documentation du projet.

---

## Équipe
- Étudiants : Jenarthan, Quentin, Clément, Sam.
- Encadrants : [Cendrine Arrondeau], [Amélie Malkatan], [Tofirk Soussi].

---

## Livrables attendus
- Application fonctionnelle pour étudiant et enseignant.
- Manuels d'installation et d'utilisation.
- Tests unitaires et d'intégration.
- Documents de recette.

---

## Planning
- Début du projet : 20 janvier 2025.
- Revue 1 : 24 février 2025.
- Revue 2 : 17 mars 2025.
- Revue 3 : 28 avril 2025.
- Fin du projet : 26 mai 2025.

---

## Contact
Pour toute question, veuillez contacter :  
- **Chef de projet** : [Sam Depardieu](samdepardieu@hotmail.com).  
- **Établissement** : Lycée Durzy, 23 rue Léonard de Vinci, 45700 Villemandeur.

---

## Informations complémentaires
Les ports réseaux suivant seront utilisé :  
- ``5557`` : envoie des commandes de l'interface prof->eleve et vice versa
- ``5558`` : envoie des consignes de la session en cours
- ``5559`` : envoie des commentaire/message aux interfaces élève
- ``5560`` : envoie des informations aux interfaces élève sous la forme de Json ({"nomEleve": "nom_eleve"}, {"nomProf", "nom_prof"})
- ``5561`` : envoie des nterfaces à ouvrir aux interfaces élèves (QCM, ecoute, video, ecoute_co, video_co, enregistrement)

---

# Mise en Place et Installation

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
