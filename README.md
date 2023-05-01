
# The Great Competition : Fast One

Un jeu de course de voitures accessible mais rempli de challenge !
Roulez à toute vitesse dans votre bolide pour battre vos meilleurs temps !
## Auteurs

- SYLVESTRE Antonin : p2102667
- VITTORE Thomas : p2107970

ID du projet sur GitLab : 28198
## Fonctionnalités

- 5 niveaux inspirés de circuits emblématiques du sport automobile : 
    - Sakhir International Circuit (Barhaïn)
    - Autodromo Nazionale Monza (Italie)
    - Silverstone Circuit (Royaume-Uni)
    - Circuit de Spa-Francorchamps (Belgique)
    - Circuit de Monaco (Monaco)

- Un gameplay simple à prendre en main avec les 4 touches : accélérateur, frein, virage à gauche et à droite
- Des checkpoints à valider pour comptabiliser le tour
- Un challenge à relever : faire le meilleur temps possible en passant au travers de tous les checkpoints et sans se faire ralentir par l'herbe !
- Un éditeur de niveaux pour créer ses propes ciruits et les modifier à volonté
- Un menu paramètres avec des options réglables :
    - Le volume sonore de la musique
    - Le déplacement de la caméra par rapport à la voiture (pour donner un style arcade)
## Captures d'écran

### Menu du jeu
![Menu du jeu](https://media.discordapp.net/attachments/889998716067545098/1102586847168823336/menu.png?width=1247&height=686)

### Aperçu en jeu
![En jeu](https://media.discordapp.net/attachments/889998716067545098/1102586846883631196/jeu.png?width=1247&height=686)

### L'éditeur de niveaux
![Editeur de niveaux](https://media.discordapp.net/attachments/889998716067545098/1102586846543880222/editeur.png?width=1247&height=686)
## Contrôles

### En jeu

| Touche | Description                |
| :-------- | :------------------------- |
| Haut / Z | Accélérer |
| Bas / S | Freiner |
| Gauche / Q | Tourner à gauche |
| Droite / D | Tourner à droite |
| Echap / A | Quitter le jeu |

### Editeur

| Touche | Description                |
| :-------- | :------------------------- |
| Z | Déplacer le prop vers le haut |
| S | Déplacer le prop vers le bas |
| Q | Déplacer le prop vers la gauche |
| D | Déplacer le prop vers la droite |
| R | Tourner le prop |
| A | Prop suivant |
| E | Prop précédent |
| G | Supprimer le prop sélectionné |
| C | Sauvegarder le niveau |
| L | Charger un niveau existant |
| Echap | Quitter l'éditeur |

Pour placer un prop depuis le menu à gauche, cliquer sur la case souhaitée et maintenez appuyé en la glissant sur le terrain

Pour vous déplacer dans l'éditeur, glissez simplement avec la souris sur le terrain

### Paramètres

| Touche | Description                |
| :-------- | :------------------------- |
| Haut | Monter le volume |
| Bas | Baisser le volume |
| Gauche | Diminuer le déplacement de la caméra |
| Droite | Augmenter le déplacement de la caméra |
| Echap | Retour au menu principal |

## Commandes
Récupérer le projet (si vous disposez des droits) :

```bash
  git clone https://forge.univ-lyon1.fr/fantomas/test-project.git
```

Compiler en cas de besoin :

```bash
  make clean
  make
```

Lancer le jeu :
```bash
  bin/VroumSFML
```
## Architecture de l'archive

bin/ : Dossier de l'éxécutable à lancer

data/ : Dossier des ressources du jeu

  - data/circuits/ : Fichiers JSON contenant les circuits
  - data/fonts/ : Fichiers de police d'écriture
  - data/images/ : Images affichées sur le menu
  - data/props/ : Textures des props composant les circuits
  - data/sounds/ : Musiques du jeu
  - data/voitures/ : Textures liées à la voitures

doc/: Dossier de la documentation

obj/ : Dossier des fichirs objets compilés

src/ : Dossier du code source avec ses headers
## Ressources utilisées

Manipulation de fichiers JSON en C++ : [json by nlohmann](https://github.com/nlohmann/json)

Affichage graphique, musiques, chronomètres, etc. :  [SFML](https://www.sfml-dev.org/index-fr.php)