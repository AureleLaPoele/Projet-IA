# Projet-IA
Projet IA présenté par Aurèle et Miguel

Sommaire
1 FSM
2 Behavior Tree
3 GOAP

1 Méthode utilisée : FSM (Boo)

La méthode permet de comprendre la perception des PNJ.
Implémenter des comportements de patrouille et de poursuite.
Structurer l’IA d’un PNJ.

Comportement de l'ennemi :
Suivi du joueur : L'ennemi suit constamment la position du joueur, même à travers les murs.
Positionnement relatif : L'ennemi est toujours à une distance fixe du joueur et cherche à s'approcher de lui.
Arrêt lorsque le joueur se retourne : Si le joueur fait demi-tour ou s'arrête pour faire face à l'ennemi, ce dernier cesse de le suivre et reste immobile jusqu'à ce que le joueur se retourne.


2 Méthode utilisée : Behavior Tree (Monster)

Un Behavior Tree (BT) est une structure de données hiérarchique utilisée pour modéliser le comportement d'une intelligence artificielle (IA) dans un jeu vidéo. Contrairement aux machines à états finis, qui deviennent rapidement complexes avec de nombreux états et transitions, les BT offrent une approche plus modulaire et extensible.

Comportement de l'ennemi :
Suivi de pattern : L'ennemi suit un chemin ou possède un comportement pré-défini, comme une trajectoire fixe ou un cycle de mouvement.
Détection du joueur : Dès que l'ennemi repère le joueur, il interrompt son pattern et commence à poursuivre le joueur.
Attaque : Une fois à portée du joueur, l'ennemi attaque.

3 Méthode utilisée : GOAP (Chaser)
Le Goal-Oriented Action Planning (GOAP) est une approche puissante pour créer des agents capables de réaliser des comportements complexes et autonomes dans des jeux vidéo. En structurant les objectifs, actions et états, GOAP permet une grande flexibilité tout en offrant une approche systématique pour gérer les décisions des agents.

Comportement de l'ennemi :
Suivi du joueur : L'ennemi suit continuellement la position du joueur.
Proximité du joueur : Dès que l'ennemi est très proche du joueur , il change de couleur.
Alerte à un autre ennemi : L'ennemi communique la position du joueur au monster.