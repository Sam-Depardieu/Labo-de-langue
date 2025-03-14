import zmq
import socket
import pyaudio

context = zmq.Context()

# 🔹 Socket PUB pour envoyer mute/unmute
pub_socket = context.socket(zmq.PUB)
pub_socket.bind("tcp://*:5555")  # Écoute sur le port 5555

# 🔹 Socket REQ-REP pour gérer l’état des élèves
rep_socket = context.socket(zmq.REP)
rep_socket.bind("tcp://*:5556")  # Écoute les demandes d'état

# 🔹 Socket PUB pour envoyer les données audio
audio_pub_socket = context.socket(zmq.PUB)
audio_pub_socket.bind("tcp://*:5557")  # Écoute sur le port 5557

# 🔹 Socket SUB pour recevoir les données audio des clients
audio_sub_socket = context.socket(zmq.SUB)
audio_sub_socket.setsockopt(zmq.SUBSCRIBE, b"")
audio_sub_socket.connect("tcp://localhost:5558")  # Connexion à la socket audio des clients

print("🔵 Serveur en attente des commandes Qt...")

# Paramètres audio
CHUNK = 1024
FORMAT = pyaudio.paInt16
CHANNELS = 1
RATE = 44100

audio = pyaudio.PyAudio()

# 🔹 Fonction pour capturer et envoyer l'audio
def send_audio():
    stream = audio.open(format=FORMAT, channels=CHANNELS,
                        rate=RATE, input=True,
                        frames_per_buffer=CHUNK)

    while True:
        data = stream.read(CHUNK)
        audio_pub_socket.send(data)

# 🔹 Fonction pour recevoir et jouer l'audio
def receive_audio():
    stream = audio.open(format=FORMAT, channels=CHANNELS,
                        rate=RATE, output=True,
                        frames_per_buffer=CHUNK)

    while True:
        data = audio_sub_socket.recv()
        stream.write(data)

import threading
send_audio_thread = threading.Thread(target=send_audio)
receive_audio_thread = threading.Thread(target=receive_audio)

send_audio_thread.start()
receive_audio_thread.start()

while True:
    # 🔹 Vérifie si Qt envoie une commande
    try:
        message = rep_socket.recv_string(flags=zmq.NOBLOCK)  # Vérifie si Qt envoie un message
        print(f"📩 Commande reçue de Qt : {message}")

        # 🔹 Envoie la commande à tous les élèves
        pub_socket.send_string(message)
        rep_socket.send_string("OK")

    except zmq.Again:
        pass  # Aucune commande reçue
