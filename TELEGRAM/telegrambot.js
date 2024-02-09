import fetch from "node-fetch";
import { Bot, Context, session, InlineKeyboard } from "grammy";
import {
    conversations,
    createConversation,
  } from "@grammyjs/conversations";

const bot = new Bot("VOTRE TOKEN ICI");
bot.use(session({ initial: () => ({}) }));
bot.use(conversations());


async function newmess(conversation, ctx) {
    await ctx.reply("Quel est le message à envoyer à la LoveBox💜 ?");
    const message = await conversation.form.text();
    await ctx.reply("Demande prise en compte : " + "\"" + message + "\" ⌛");

      var raw = JSON.stringify({
        "message": message
      });

      var requestOptions = {
        method: 'POST',
        headers: {
          "Content-Type": "application/json",
        },
        body: raw,
        redirect: 'follow'
      };

      fetch("https://le_lien_de_votre_API_ICI", requestOptions)
        .then(response => response.text())
        .then(result => console.log(result))
        .catch(error => console.log('error', error));

        ctx.reply("Message bien envoyé !✅");
        }

        

bot.use(createConversation(newmess));


bot.command("start", async (ctx) => {
  const chatId = ctx.chat.id
  console.log(chatId);
  if(chatId != 'votre chat id ici, pour que vous soyez le seul à pouvoir envoyer un message'){
    ctx.reply("Tu ne peux pas utiliser ce bot !");
    console.log("refuse " + chatId);
  }else if(chatId == 'votre chat id ici, pour que vous soyez le seul à pouvoir envoyer un message') {
    await ctx.conversation.enter("newmess");
    console.log("accepted" + chatId);
  }
  
  
});


bot.start();
console.log("test");