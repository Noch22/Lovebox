
# Lovebox DIY :love_letter:

Envie d'envoyer de l'amour à ton partenaire, où simplement quelqu'un que tu aime ? Tu as envie de créer ? Ce projet est fait pour toi !




## Liste des courses

 - [Awesome Readme Templates](#tst)
 - [Awesome README](https://github.com/matiassingers/awesome-readme)
 - [How to write a Good readme](https://bulldogjob.com/news/449-how-to-write-a-good-readme-for-your-github-project)


## Les étapes de création

1. **Étape 1** : Créer la base de données MongoDB et l'API pour envoyer des messages et les récupérer. 
Je conseille [ce tuto](https://youtu.be/FkD_tf8vkfg?si=MpVTI8Q7_iVIJIDb) en anglais qui explique très bien comment réaliser cette étape : 

   - Créer une base de données dans le cloud MongoDB.
   - Créer une API pour pouvoir interroger cette base et lui envoyer des données.

2. **Étape 2** : Réaliser le bot Telegram et l'héberger.
    - Pour cette partie, tout le code est disponible dans le repository.
    - Créer un nouveau bot en contactant le BotFather et renseigner ses identifiants dans le fichier.
    - Héberger les fichiers du bot sur un service payant ou gratuit, possible d'utiliser [AlwaysData](https://www.alwaysdata.com/fr/) gratuitement.

3. **Étape 3** : Tester le code Arduino sur l'ESP8266, avec le montage sur breadboard
   - Réaliser le montage éléctronique sur breadboard (schémas disponibles).
   - Flasher le code Arduino sur l'ESP8266, ***avec le bon lien vers votre API MongoDB***
   - Tester d'envoyer un message pour voir si il s'affiche !

4. **Étape 4** : Imprimer la boite et le coeur en 3D !
   - Pour cette étape, tous les fichiers sont disponibles dans le dossier 3DPRINT, utiliser votre slicer préféré pour slicer les fichiers pour la bonne imprimante ! Il est également possible de les modifier si il ne conviennent pas, ___attention surtout au trou à l'arrière pour brancher le cable de l'ESP8266, il est un peu petit.___

5. **Étape 5** : Assembler le tout !
    - Et voici le moment de souder tous les composants entre eux, de bien isoler les soudures afin de tout entrer dans le boitier final ! 
    - Penser également à bien fixer le coeur sur le servomoteur, j'ai personnellement utilsé de la pate à fixe afin de pouvoir le retirer si jamais le servo venait à ne plus fonctionner.

    
## Étape 1 : Créer la base de données MongoDB et l'API

test
