
# Lovebox DIY :love_letter:

Envie d'envoyer de l'amour à ton partenaire, où simplement quelqu'un que tu aime ? Tu as envie de créer ? Ce projet est fait pour toi !



![Photo de la lovebox](/assets/cover.jpg)
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

3. [**Étape 3**](#electric_plug-étape-3--tester-le-code-arduino-sur-lESP8266-avec-le-montage-sur-breadboard) : Tester le code Arduino sur l'ESP8266, avec le montage sur breadboard
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

1. Créer un Bot télégram en contactant @BotFather
    - Envoyer /newbot afin de commencer la création du bot.
    - Donner le nom du bot voulu
    - Donner le username, il doit être en minuscule et finir par bot

    BotFather vous renvois alors toutes les infos nécessaires afin de communiquer avec notre bot, ce qui nous intéresse ici est le **TOKEN**. Il est sous la forme `987654:AABBCClljjgggffgkk-abc`...


    BotFather vous communique également le lien de la conversation pour communiquer avec votre bot, cliquable sur le lien `t.me/NomDuBot`

2. Initier le bot Telegram
    - Télécharger le fichier telegram_bot.js ainsi que le package.json
        - Installer les packages avec un npm init dans le dossier ou se trouve le fichier telegram_bot.js et le package.json (avoir node js d'installé sur votre machine ainsi que npm)
    - Modifier le fichier telegram_bot.js avec le token donné par BotFather (line 8)
        ```javascript
        const bot = new Bot("VOTRE TOKEN ICI");
        ```
    - Modifier le fichier avec le lien vers votre API crée précédemment, le lien renseigné doit-être celui pour ajouter une entrée dans la base de données. (line 31)
        ```javascript
        fetch("https://le_lien_de_votre_API_ICI", requestOptions)
        ```
    - Entrez votre CHATID ligne 47 et 50 afin de restreindre qui peux envoyer un message ou non via le bot.
        ```js
        if(chatId != 'votre chat id ici, pour que vous soyez le seul à pouvoir envoyer un message'){

        ctx.reply("Tu ne peux pas utiliser ce bot !");
        console.log("refuse " + chatId);

        }else if(chatId == 'votre chat id ici, pour que vous soyez le seul à pouvoir envoyer un message') {

        await ctx.conversation.enter("newmess");
        console.log("accepted" + chatId);
        }
        });
        ```


    - Communiquer avec votre bot télégram et voir si il réponds, si il vous réponds, vérifier dans votre base de données si le message est bien rentré. Si c'est le cas, bravo ! Vous avez fait une bonne partie du travail.

3. Hébérger le bot afin d'y avoir accès 24H/24 et 7J/7.

    Pour cette étape, vous êtes libres d'utiliser le service que vous voulez, si vous disposez déjà d'un hébergeur proposant du nodeJS, c'est possible de passer par celui-ci. Sinon, je vous propose d'utiliser [AlwaysData](https://www.alwaysdata.com/), qui propose une offre gratuite à vie, avec 100mo de stockage. Ce qui est bien assez suffisant pour héberger notre petit fichier et ses dépendances.

Pour ça, rendez-vous sur le [site](https://www.alwaysdata.com/). Créez vous un compte.

1. Déposez vos fichiers grâce au FTP dans le dossier www.

1. Connectez-vous au SSH, lancez un npm init dans le bon dossier
1. Lancez ensuite un npm start et le bot devrais se lancer
1. Rendez-vous dans l'onglet Tâches planifiées sur AlwaysData et ajoutez une tâche tous les jours à minuit pour redémarrer le bot automatiquement. La commande est npm start


___Bravo, votre bot est hébergé !___ passons dès à présent au nerf de la guerre, l'arduino et l'éléctronique.
## :electric_plug: Étape 3 : Tester le code Arduino sur l'ESP8266, avec le montage sur breadboard
