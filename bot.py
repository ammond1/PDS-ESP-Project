from dotenv import load_dotenv
import os
import telebot
import firebase_admin
from firebase_admin import credentials, db
import time

# Path to your Firebase Admin SDK private key file
cred = credentials.Certificate('REPLACE WITH PATH TO SDK FILE')

# Initialize Firebase Admin SDK
firebase_admin.initialize_app(cred, {
    'databaseURL': 'FIREBASE DATABASE URL LINK '  # Replace with your Firebase Realtime Database URL
})

load_dotenv()
BOT_TOKEN = os.environ.get('BOT_TOKEN')
bot = telebot.TeleBot(BOT_TOKEN)
ref = db.reference('noise_level')
listening = False

@bot.message_handler(commands=['start'])
def start(message):
    chatid = message.chat.id
    bot.send_message(chat_id=chatid, text='Listening...')
    global listening
    listening = True
    listen(chatid)
@bot.message_handler(commands=['stop'])
def stop(message):
    chatid = message.chat.id
    bot.send_message(chat_id=chatid, text='Stopping...')
    global listening
    listening = False

def listen(chatid):
    global listening
    while listening:
        ref = db.reference('noise_level')
        noise_level = ref.get()

        if noise_level >200:
            bot.send_message(chat_id=chatid, text= 'NOISY SIA')
        time.sleep(5)

bot.infinity_polling()
