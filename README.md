
# Lovebox DIY :love_letter:

Envie d'envoyer de l'amour à ton partenaire, où simplement quelqu'un que tu aime ? Tu as envie de créer ? Ce projet est fait pour toi !




## :shopping_cart: Liste des courses 
 - Wemos D1 Mini
   - [Wemos D1 Mini (cheap, cramé au bout de quelques semaine)](https://fr.aliexpress.com/item/1005006018009983.html?spm=a2g0o.productlist.main.1.710271d3t6g7PT&algo_pvid=52c3a6c4-c3f6-4a17-950a-76c54a03c795&algo_exp_id=52c3a6c4-c3f6-4a17-950a-76c54a03c795-0&pdp_npi=4%40dis%21EUR%2111.72%213.98%21%21%2188.68%21%21%402103854616982543426884123e755b%2112000035516008089%21sea%21FR%212732995892%21&curPageLogUid=zl0K3OJP8Vpz)
   - [Wemos D1 Mini (meilleure qualitée)](https://www.amazon.fr/AZDelivery-D1-Mini-d%C3%A9veloppement-compatible/dp/B01N9RXGHY/ref=sr_1_2?__mk_fr_FR=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=154GH4CHKZNO6&keywords=wemos+d1+mini+azdelivery&qid=1707475930&sprefix=wemos+d1+mini+azdelivery%2Caps%2C76&sr=8-2)
 - [Servo Moteurs](https://fr.aliexpress.com/item/1005005247828609.html?spm=a2g0o.order_list.order_list_main.5.47a45e5bRyADyd&gatewayAdapt=glo2fra)
 - [Photorésistance](https://fr.aliexpress.com/item/1005002388823502.html?spm=a2g0o.productlist.main.29.37cbc2577Uvttn&algo_pvid=6a61f0aa-da98-4b46-9889-7f2f25bc02dd&aem_p4p_detail=2023102510213610602311871836040000145130&algo_exp_id=6a61f0aa-da98-4b46-9889-7f2f25bc02dd-14&pdp_npi=4%40dis%21EUR%213.37%212.36%21%21%213.49%21%21%402103854616982544965095038e755b%2112000020473320432%21sea%21FR%212732995892%21&curPageLogUid=exgoV82lYTlB&search_p4p_id=2023102510213610602311871836040000145130_3)
 - [Écran OLED](https://fr.aliexpress.com/item/32957309383.html?spm=a2g0o.order_list.order_list_main.25.47a45e5bRyADyd&gatewayAdapt=glo2fra)
 - [Résistances](https://fr.aliexpress.com/item/1005005798073776.html?spm=a2g0o.order_list.order_list_main.40.47a45e5bRyADyd&gatewayAdapt=glo2fra)


## :label: Les étapes de création

1. [**Étape 1**](#globe_with_meridians-étape-1--créer-la-base-de-données-mongodb-et-lapi) : Créer la base de données MongoDB et l'API pour envoyer des messages et les récupérer. 
Je conseille [ce tuto](https://youtu.be/FkD_tf8vkfg?si=MpVTI8Q7_iVIJIDb) en anglais qui explique très bien comment réaliser cette étape : 

   - Créer une base de données dans le cloud MongoDB.
   - Créer une API pour pouvoir interroger cette base et lui envoyer des données.

2. [**Étape 2**](#robot-étape-2--réaliser-le-bot-telegram-et-lhéberger) : Réaliser le bot Telegram et l'héberger.
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

    
## :globe_with_meridians: Étape 1 : Créer la base de données MongoDB et l'API

Pour ça, je vous conseille de suivre [le tuto de MongoDB ](https://youtu.be/FkD_tf8vkfg?si=MpVTI8Q7_iVIJIDb). 

Mettez en place 2 HTTPS ENDPOINTS, un pour récupérer les messages et l'autre pour en envoyer. 

**Pour récupérer uniquement le dernier message, utilisez le code suivant dans la partie fonction, en remplaçant par le bon nom de base évidemment :**

```javascript
exports = function({ query, headers, body}, response) {

    const doc = context.services
    .get("mongodb-atlas")
    .db("Lovebox")
    .collection("messages")
    .find({})

    //Récupère uniquement le dernier message entré
    .sort({$natural: -1}) 
    .limit(1)

    .toArray();
    return doc;

};
```

## :robot: Étape 2 : Réaliser le bot Telegram et l'héberger
