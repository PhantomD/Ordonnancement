# Ordonnancement

Problème : Flow-Shop. 

n job a réalisé sur m machines. Indisponibilités sur chaque machines (intervalle d'indisp sur la machine mi de la forme Si ti). 
On peut réaliser les taches soit avant Si ou après Ti.

Objectif : minimiser la somme des dates de fin (ci). 
On cherche un ordonnancement réalisable sans préemption (pas interruption). Chaque machine ne peut réaliser qu'une tâche a la fois.

Réaliser un programme en C avec 3 heuristiques de bon sens.
Un algorithme génétique et une méthode de branch and bound (Soit utiliser modele linéaire en nombre entier, soit créer notre propre B&B avec une liste chaînée)

Fournir programme + rapport (explique la démarche, le problème et les résultats) : Descriptif ! 
